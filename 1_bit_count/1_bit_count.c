#include <stdio.h>
#include <stdint.h>

//#define set_bit(x, n) ((x) |= (1U << (n)))
//#define clear_bit(x, n) ((x) &= (1U << (n)))
//#define toggle_bit(x, n) ((x) ^= (1U << (n)))
#define check_bit(x, n) (((x) >> (n)) & 1U)

int count_bit(uint8_t x) {
    int count = 0;
    for (int i = 7; i >= 0; i--) {
        if (check_bit(x, i)) count++;
    }
    return count;
}

int count_bit_fast(uint8_t x) {
    int count = 0;
    while (x != 0) {
        x = x & (x - 1);
        count ++;
    }
    return count;
}

int main() {
    uint8_t flags;
    printf("Nhap so can dem (0 - 255): ");
    scanf("%hhu", &flags);
    int res1 = count_bit(flags);
    printf("So bit 1 dem thuong la %d\n", res1);
    int res2 = count_bit_fast(flags);
    printf("So bit 1 dem nhanh la: %d", res2);
    return 0;
}