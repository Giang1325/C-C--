#include <stdio.h>
#include <stdlib.h>

void saoChep(void **pp, const void *nguon, int soByte) {
    char *ptr = malloc(soByte);
    const char *nguonByte = (const char *) nguon;
    for (int i = 0; i < soByte; i++) {
        ptr[i] = nguonByte[i];
    }
    *pp = ptr;
}

int main() {
    int x = 12345;
    int *banSao = NULL;
    saoChep((void**)&banSao, &x, sizeof(int));   // ← thêm lại (void**) ở đây
    printf("Gia tri ban sao: %d\n", *banSao);
    printf("Gia tri x goc: %d\n", x);
    free(banSao);
    return 0;
}