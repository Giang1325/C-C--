#include <stdio.h>
#include <stdint.h>

typedef struct {
    uint8_t led : 1;
    uint8_t interrupt : 1;
    uint8_t mode : 2;
    uint8_t reserved : 3;
    uint8_t error : 1;
} controlBit;

typedef union {
    controlBit bits;
    uint8_t raw;
} controlRegister;

void print(uint8_t x, const char *c) {
    printf("%s: %d\n", c, x);
}

int main() {
    controlRegister data1;
    data1.raw = 0;
    data1.bits.led = 1;
    data1.bits.mode = 2;
    printf("Gia tri tho la: 0x%02X\n", data1.raw);
    controlRegister data2;
    data2.raw = 0x85;
    printf("Voi %s la 0x%02X, ta co cac field sau:\n", "data.raw", data2.raw);
    print(data2.bits.led, "data2.bits.led");
    print(data2.bits.mode, "data2.bits.mode");
    print(data2.bits.error, "data2.bits.error");
    return 0;
}