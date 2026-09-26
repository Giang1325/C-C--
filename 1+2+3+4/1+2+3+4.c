#include <stdio.h>
#include <stdint.h>

#define buffer_size 8

typedef struct {
    uint8_t power : 1;
    uint8_t mode : 2;
    uint8_t fault : 1;
    uint8_t led : 2;
    uint8_t speed : 2;
} ControlBit;

typedef union {
    ControlBit bits;
    uint8_t raw;
} ControlRegister;

int setpower (ControlRegister *reg, int newvalue) {
    if (newvalue == 0 || newvalue == 1 ) {
        reg->bits.power = newvalue;
        return reg->bits.power;
    }
    else {
        printf("Gia tri khong hop le!\n");
        return -1;
    }
}

int setmode (ControlRegister *reg, int newvalue) {
    if(newvalue >= 0 && newvalue <= 3) {
        reg->bits.mode = newvalue;
        return reg->bits.mode;
    }
    else {
        printf("Gia tri khong hop le!\n");
        return -1;
    }
}

int setfault (ControlRegister *reg, int newvalue) {
    if(newvalue == 0 || newvalue == 1) {
        reg->bits.fault = newvalue;
        return reg->bits.fault;
    }
    else {
        printf("Gia tri khong hop le!\n");
        return -1;
    }
}
int setled (ControlRegister *reg, int newvalue) {
    if(newvalue >= 0 && newvalue <= 3) {
        reg->bits.led = newvalue;
        return reg->bits.led;
    }
    else {
        printf("Gia tri khong hop le!\n");
        return -1;
    }
}

int setspeed (ControlRegister *reg, int newvalue) {
    if(newvalue >= 0 && newvalue <= 3) {
        reg->bits.speed = newvalue;
        return reg->bits.speed;
    }
    else {
        printf("Gia tri khong hop le!\n");
        return -1;
    }
}

typedef struct {
    int buffer[buffer_size];
    int index;
    int logcount;
} CircularBuffer;

void addlog (CircularBuffer *cb, int commandID) {
    cb->buffer[cb->index] = commandID;
    cb->index = (cb->index + 1) % buffer_size;
    if(cb->logcount < buffer_size) cb->logcount++;
}

void printlog (CircularBuffer *cb) {
    const char *tenLenh[] = {"Power", "Mode", "Fault", "Led", "Speed"};
    for (int i = 0; i < cb->logcount; i++) {
        int id = cb->buffer[i];
        if (id >= 0) printf("Log thu %d: Lenh %s - Thanh cong!\n", i, tenLenh[id]);
        else {
            int choice = -id - 1;
            printf ("Log thu %d: Lenh %s - That bai!\n", i, tenLenh[choice]);
        }
    }
}

uint8_t checksum (ControlRegister *reg) {
    uint8_t checksum = 0;
    checksum = reg->raw;
    printf("Checksum bay gio la: 0x%02X\n", checksum);
    return checksum;
}

void print (uint8_t a, uint8_t b) {
    if (a == b) printf("Du lieu khong bi thay doi!\n");
    else printf("Du lieu da bi thay doi!\n");
}

int main() {
    ControlBit bits;
    ControlRegister reg_data;
    ControlRegister *reg = &reg_data;
    reg->raw = 0x09;
    printf("Gia tri goc la: 0x%02X\n", reg->raw);
    uint8_t a = checksum (reg);

    CircularBuffer cb_data;
    CircularBuffer *cb = &cb_data;
    cb->index = 0;
    cb->logcount  = 0;

    int (*arr[])(ControlRegister*, int) = {setpower, setmode, setfault, setled, setspeed};

    int soLenh;
    printf("Nhap so lenh can chay: ");
    scanf("%d", &soLenh);

    for (int lan = 0; lan < soLenh; lan++) {
        int choice, newvalue;
        do {
            printf("Chon ham 0(setpower), 1(setmode), 2(setfault), 3(setled), 4(setspeed): ");
            scanf("%d", &choice);
            if(choice < 0 || choice > 4) printf("Gia tri khong hop le! Vui long chon lai!\n");
        } while (choice < 0 || choice > 4);

        printf("Nhap gia tri moi: ");
        scanf("%d", &newvalue);

        int res = arr[choice](reg, newvalue);
        int logID = (res == -1) ? -choice - 1 : choice;
        addlog(cb, logID);
        printf("Gia tri hien tai: %d\n", res);
    }
    
    printf("---Cac log da chay---\n");
    printlog(cb);

    uint8_t b = checksum(reg);
    print(a, b);
    return 0;
}