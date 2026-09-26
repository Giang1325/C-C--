#include <stdio.h>

int cong(int a, int b) {return a + b;}
int tru(int a, int b) {return a - b;}
int nhan(int a, int b) {return a * b;}

int main() {
    int (*arr[])(int, int) = {cong, tru, nhan};
    int x, y, choice;
    printf("Nhap 2 so: ");
    scanf("%d %d", &x, &y);
    do {
        printf("Chon phep tinh (0: cong, 1: tru, 2: nhan): ");
        scanf("%d", &choice);
        if (choice < 0 || choice > 2) printf("Lua chon khong hop le! Vui long chon lai.");
    } while (choice < 0 || choice > 2);
    printf("Ket qua: %d", arr[choice](x, y));
    return 0;
}