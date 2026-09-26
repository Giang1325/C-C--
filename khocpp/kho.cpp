#include <iostream>
using namespace std;

void saoChep (void **pp, const void *nguon, int soByte) {
    char *ptr = new char[soByte];
    const char *nguonByte = (const char *) nguon;
    for (int i = 0; i < soByte; i++) {
        ptr[i] = nguonByte[i];   
    }
    *pp = ptr;
}

int main() {
    int x = 12345;
    int *banSao = nullptr;
    saoChep ((void**)&banSao, (const void*)&x, sizeof(int));
    cout << "Gia tri ban sao: " << *banSao << endl;
    cout << "Gia tri x goc: " << x << endl;
    delete[] (char *) banSao;
    return 0;
}