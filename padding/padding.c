#include <stdio.h>

struct SensorPacket {
    unsigned char id;
    short temperature;
    short humidity;
    unsigned char checksum;
};

struct __attribute__((packed)) SensorPacketPacked {
    unsigned char id;
    short temperature;
    short humidity;
    unsigned char checksum;
};

int main(void) {
    printf("sizeof(SensorPacket) = %zu\n", sizeof(struct SensorPacket));
    printf("sizeof(SensorPacketPacked) = %zu\n", sizeof(struct SensorPacketPacked));
    return 0;
}