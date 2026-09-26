#include <stdio.h>
#include <stdint.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define fake_hw_size 256

uint8_t fake_hw_memory[fake_hw_size];

#define control_reg_offset 0x00
#define status_reg_offset 0x04
#define temp_reg_offset 0x08

volatile uint8_t *control_reg = &fake_hw_memory[control_reg_offset];
volatile uint8_t *status_reg = &fake_hw_memory[status_reg_offset];
volatile uint8_t *temp_reg = &fake_hw_memory[temp_reg_offset];

#define set_bit(reg, bit) (*(reg) |= ((1U) << (bit)))
#define clear_bit(reg, bit) (*(reg) &= ~((1U) << (bit)))
#define check_bit(reg, bit) (((*(reg)) >> (bit)) & (1U))

#define fan_enable 0
#define target_speed_shift 1
#define target_speed_mask 0x07

#define fan_running 0
#define overheat_flag 1
#define stall_flag 2
#define data_ready 3

#define set_field(reg, shift, mask, value) (*(reg) = (*(reg) & ~((mask) << (shift))) | (((value) & (mask)) << (shift)))

void cmd_enable_fan (int newvalue) {
    if (newvalue != 0) set_bit (control_reg, fan_enable);
    else clear_bit (control_reg, fan_enable); 
}

void cmd_set_speed (int newvalue) {
    if (newvalue >= 0 && newvalue <= 7) set_field (control_reg, target_speed_shift, target_speed_mask, newvalue);
}

typedef void (*cmd_func_t)(int);
cmd_func_t cmd_table[2] = {cmd_enable_fan, cmd_set_speed};

typedef struct {
    uint8_t temperature;
    uint8_t fan_run;
    uint8_t overheat;
    uint8_t stall;
} logEntry;

#define buffer_size 16

typedef struct {
    logEntry buffer[buffer_size];
    int index;
    int logcount;
} CircularBuffer;

void addlog (CircularBuffer *cb, logEntry log) {
    cb->buffer[cb->index] = log;
    cb->index = (cb->index + 1) % buffer_size;
    if (cb->logcount < buffer_size) cb->logcount++;
}

volatile int hw_done = 0;

void* hardware_simulator(void* arg) {
    for (int cycle = 0; cycle < 8; cycle++) {
        int fanenable = check_bit (control_reg, fan_enable);
        int target_speed = (*(control_reg) >> (target_speed_shift)) & (target_speed_mask);
        
        int temp = *temp_reg;
        int delta = rand() % 3 + 1;
        if (fanenable) temp -= delta;
        else temp += delta;

        if (temp < 0) temp = 0;
        if (temp > 255) temp = 255;

        if (temp >= 80) set_bit (status_reg, overheat_flag);
        else clear_bit (status_reg, overheat_flag);

        *temp_reg = (uint8_t)temp;

        if (rand() % 8 == 0) set_bit (status_reg, stall_flag);
        else clear_bit (status_reg, stall_flag);

        int overheat = check_bit (status_reg, overheat_flag);
        int stall = check_bit (status_reg, stall_flag);

        if (fanenable && !overheat && !stall) set_bit (status_reg, fan_running);
        else clear_bit (status_reg, fan_running);

        set_bit (status_reg, data_ready);

        usleep((rand() % 50000) + 10000);
    }
    hw_done = 1;
    return NULL;
}

int main () {
    srand(time(NULL));

    CircularBuffer cb_data;
    CircularBuffer *cb = &cb_data;
    cb->index = 0;
    cb->logcount = 0;

    pthread_t hw_thread;
    *temp_reg = 79;
    pthread_create (&hw_thread, NULL, hardware_simulator, NULL);

    cmd_table[0](1);
    cmd_table[1](3);
    usleep(20000);
    cmd_table[1](6);
    cmd_table[0](0);

    while (1) {
        if(check_bit (status_reg, data_ready)) {
            logEntry log;
            log.temperature = *temp_reg;
            log.fan_run = check_bit (status_reg, fan_running);
            log.overheat = check_bit (status_reg, overheat_flag);
            log.stall = check_bit (status_reg, stall_flag);

            addlog(cb, log);
            printf ("temp = %3d   fan_run = %d   overheat = %d   stall = %d\n", log.temperature, log.fan_run, log.overheat, log.stall);
            clear_bit (status_reg, data_ready);
        }
        else {
            if (hw_done) break;
            //usleep (1000);
        }
    }
    pthread_join (hw_thread, NULL);
    return 0;
}