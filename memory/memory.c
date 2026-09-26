#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("So luong gia tri do duoc la bao nhieu? ");
    int n;
    scanf("%d", &n);
    float* arr = malloc(n * sizeof(float));
    float sum = 0;
    for (int i = 0; i < n; i++) {
        printf("Nhap gia tri thu %d: ", i + 1);
        scanf("%f", &arr[i]);
        sum += arr[i];
    }
    float mid = sum / n;
    printf("Gia tri trung binh hien tai la: %f\n\n", mid);
    float max = arr[0];
    for (int j = 0; j < n; j++) {
        if (max < arr[j]) max = arr[j];
    }
    printf("Gia tri lon nhat hien tai la: %f", max);
    free(arr);
    return 0;
}