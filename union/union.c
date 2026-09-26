#include <stdio.h>
#include <stdint.h>

union uint32byte {
    uint32_t value;
    uint8_t byte[4];
};

// Ham nhan
void sendbyte(uint8_t a) {
    printf("Gui byte: 0x%02X\n", a);
};

uint8_t checksum(union uint32byte data) {
    uint8_t checksum = 0;
    for (int i = 0; i < 4; i++) {
        checksum += data.byte[i];
    }
    printf("Checksum bay gio la: 0x%02X\n", checksum);
    return checksum;
}

void print(uint8_t a, uint8_t b) {
    if (a == b) printf("Du lieu toan ven!\n");
    else printf("Du lieu loi!\n");
}

int main() {
    union uint32byte data;
    data.value = 0x12345678;
    printf("Gia tri goc: 0x%08X\n", data.value);
    uint8_t a = checksum(data);
    for (int i = 0; i < 4; i++) {
        sendbyte(data.byte[i]);
    }
    union uint32byte received = data;
    uint8_t b = checksum(received);
    print(a, b);
    received.byte[1] = 0xFF;
    uint8_t c = checksum(received);
    print(a, c);
    return 0;
}