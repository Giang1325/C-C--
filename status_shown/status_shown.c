#include <stdio.h>
#include <stdint.h>

#define set_bit(x, n) ((x) |= ((1U) << (n)))
#define clear_bit(x, n) ((x) &= ~((1U) << (n)))
#define toggle_bit(x, n) ((x) ^= ((1U) << (n)))
#define check_bit(x, n) (((x) >> (n)) & (1U))

void bp(uint8_t x) {
    for (int i = 7; i >=0; i--) {
        printf("%d", check_bit(x, i));
        if(i == 4) printf(" ");
    }
    printf("\n");
}

void hien_thi(uint8_t x) {
    printf("LED: %s; ", check_bit(x, 0) ? "ON" : "OFF");
    printf("INTERRUPT: %s; ", check_bit(x, 1) ? "ON" : "OFF");
    printf("ERROR: %s\n", check_bit(x, 7) ? "ON" : "OFF");
}

void res(uint8_t x) {
    bp(x);
    hien_thi(x);
}

int main() {
    uint8_t flags = 0; // Bit 0: LED; Bit 1: INTERRUPT; Bit 7: ERROR
    //bp(flags);
    //hien_thi(flags);
    res(flags);
    set_bit(flags, 0);
    set_bit(flags, 1);
    set_bit(flags, 7);
    //bp(flags);
    //hien_thi(flags);
    res(flags);
    toggle_bit(flags, 1);
    clear_bit(flags, 7);
    res(flags);
    return 0;
}
