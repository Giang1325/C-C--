#include <stdio.h>
#include <stdint.h>

#define buffer_size 8

typedef struct {
    uint8_t direction : 1;
    uint8_t speedLevel : 3;
    uint8_t overheat : 1;
    uint8_t stallError : 1;
    uint8_t running : 1;
    uint8_t mode : 1;
} MotorBit;

typedef union {
    MotorBit bits;
    uint8_t raw;
} MotorStatus;

int setdirection (MotorStatus *ms, int newvalue) {
    if (newvalue == 0 || newvalue == 1) {
        ms->bits.direction = newvalue;
        return ms->bits.direction;
    }
    else {
        printf ("Gia tri khong hop le!\n");
        return -1;
    }
}

int setspeedLevel (MotorStatus *ms, int newvalue) {
    if (newvalue >= 0 && newvalue <= 7) {
        ms->bits.speedLevel = newvalue;
        return ms->bits.speedLevel;
    }
    else {
        printf ("Gia tri khong hop le!\n");
        return -1;
    }
}

int setoverheat (MotorStatus *ms, int newvalue) {
    if (newvalue == 0 || newvalue == 1) {
        ms->bits.overheat = newvalue;
        return ms->bits.overheat;
    }
    else {
        printf ("Gia tri khong hop le!\n");
        return -1;
    }
}

int setstallError (MotorStatus *ms, int newvalue) {
    if (newvalue == 0 || newvalue == 1) {
        ms->bits.stallError = newvalue;
        return ms->bits.stallError;
    }
    else {
        printf ("Gia tri khong hop le!\n");
        return -1;
    }
}

int setrunning (MotorStatus *ms, int newvalue) {
    if (newvalue == 0) {
        ms->bits.running = newvalue;
        return ms->bits.running;
    }
    else if (newvalue == 1) {
        ms->bits.running = (ms->bits.overheat == 1 || ms->bits.stallError == 1) ? 0 : 1;
        if (ms->bits.running == 0) return -1;
        else return ms->bits.running;
    }
    else {
        printf ("Gia tri khong hop le!\n");
        return -1;
    }
}

int setmode (MotorStatus *ms, int newvalue) {
    if (newvalue == 0 || newvalue == 1) {
        ms->bits.mode = newvalue;
        return ms->bits.mode;
    }
    else {
        printf ("Gia tri khong hop le!\n");
        return -1;
    }
}

typedef struct {
    int commandID;
    int value;
} command;

typedef struct {
    int commandID;
    int value;
    int success;
} logEntry;

typedef struct {
    logEntry buffer[buffer_size];
    int  index;
    int logcount;
} CircularBuffer;

void addlog (CircularBuffer *cb, logEntry log) {
    cb->buffer[cb->index] = log;
    cb->index = (cb->index + 1) % buffer_size;
    if (cb->logcount < buffer_size) cb->logcount ++;
}

const char* tenLenh[] = {"Direction", "SpeedLevel", "Overheat", "StallError", "Running", "Mode"};

void printlog (CircularBuffer *cb) {
    for (int i = 0; i < cb->logcount; i++) {
        logEntry log = cb->buffer[i];
        if (log.success) printf ("%d, Log thu %d: Lenh %s sau update la %d - Thanh cong!\n", i + 1, i + 1, tenLenh[log.commandID], log.value);
        else printf ("%d, Log thu %d: Lenh %s sau update la %d - That bai!\n", i + 1, i + 1, tenLenh[log.commandID], log.value);        }
}

int getCurrentValue (MotorStatus *ms, int commandID) {
    switch (commandID) {
        case 0: return ms->bits.direction;
        case 1: return ms->bits.speedLevel;
        case 2: return ms->bits.overheat;
        case 3: return ms->bits.stallError;
        case 4: return ms->bits.running;
        case 5: return ms->bits.mode;
        default: return -1;
    }
}

uint8_t checksum (MotorStatus *ms) {
    uint8_t checksum = 0;
    checksum = ms->raw;
    printf ("Gia tri checksum hien tai la: 0x%02X\n", checksum);
    return checksum;
}

void print (uint8_t a, uint8_t b) {
    if (a == b) printf ("Du lieu khong thay doi!\n");
    else printf ("Du lieu da thay doi!\n");
}

int main () {
    MotorBit bits;
    MotorStatus ms_data;
    MotorStatus *ms = &ms_data;
    ms->raw = 0x24;
    printf ("Gia tri goc: 0x%02X\n", ms->raw);
    uint8_t a = checksum (ms);

    CircularBuffer cb_data;
    CircularBuffer *cb = &cb_data;
    cb->index = 0;
    cb->logcount = 0;

    int (*arr[])(MotorStatus*, int) = {setdirection, setspeedLevel, setoverheat, setstallError, setrunning, setmode};

    command danhsachLenh[] = {
        {0, 1},
        {1, 7},
        {2, 1},
        {3, 0},
        {4, 1},
        {5, 1},
    };

    int soLenh = sizeof (danhsachLenh) / sizeof (danhsachLenh[0]);

    for (int lan = 0; lan < soLenh; lan++) {
        int choice = danhsachLenh[lan].commandID;
        int newvalue = danhsachLenh[lan].value;

        int res = arr[choice](ms, newvalue);
        logEntry log;
        log.commandID = choice;
        log.value = (res != -1) ? res : getCurrentValue (ms, choice);
        log.success = (res != -1);

        addlog (cb, log);
        printf ("%d, Ket qua goi lenh %s la: %d\n", lan + 1, tenLenh[choice], res);
    }

    printf ("---Log cac lenh da chay---\n");
    printlog(cb);

    uint8_t b = checksum (ms);
    print(a, b);
    return 0;
}