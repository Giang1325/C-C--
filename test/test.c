#include <stdio.h>
#include <stdint.h>

typedef union {
    float value;
    uint8_t byte[4];
} uint32byte;

void sendbyte (uint8_t a) {
    printf ("Gui byte: 0x%02X\n", a);
}

void checksum (uint32byte data) {
    uint8_t checksum = 0;
    for (int i = 0; i < 4; i++) {
        checksum += data.byte[i];
    }
    printf ("Checksum hien tai la: 0x%02X\n", checksum);
}

int main () {
    uint32byte data;
    data.value = 24;
    printf ("Gia tri goc la: %.2f\n", data.value);
    for (int i = 0; i < 4; i++) {
        sendbyte (data.byte[i]);
    }
    checksum (data);
    return 0;
}