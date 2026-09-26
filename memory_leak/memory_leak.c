#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("Chuong trinh se tu dong cap phat va TINH TOAN 50 lan lien tuc,\n");
    printf("MOI LAN deu quen delete de ban quan sat leak qua Task Manager.\n");
    printf("Mo Task Manager, tim tien trinh nay, roi nhan Enter de bat dau...\n");
    getchar();

    int n = 5000000; // 5 trieu phan tu, de moi lan leak du lon de thay ro tren Task Manager

    // VONG LAP NGOAI MOI: chay lai toan bo khoi code cu cua ban 50 lan
    for (int lan = 0; lan < 50; lan++) {

        float* arr = malloc(n * sizeof(float)); // cap phat - GIONG code cu cua ban

        float sum = 0;
        for (int i = 0; i < n; i++) {
            arr[i] = i % 100; // THAY THE cin >> arr[i] bang gia tri tu sinh, khong can nhap tay
            sum += arr[i];
        }
        float mid = sum / n;

        float max = arr[0];
        for (int j = 0; j < n; j++) {
            if (max < arr[j]) max = arr[j];
        }

        // KHONG GOI delete[] arr; O DAY -> day chinh la cho tao ra leak co tinh

        printf("Lan %d: trung binh = %f, max = %f da lam mat ~ %zu MB tren Heap\n", lan + 1, mid, max, (n * sizeof(float)) / (1024*1024));
    }

    printf("Xong 50 lan. Kiem tra Task Manager: RAM chuong trinh nay la bao nhieu?\n");
    printf("Nhan Enter de ket thuc chuong trinh (RAM se duoc OS thu hoi het khi thoat)...\n");
    getchar();

    return 0;
}