#include <stdio.h>

#define BUFFER_SIZE 5

typedef struct {
    int buffer[BUFFER_SIZE];
    int head;
    int tail;
    int dem;
} CircularBuffer;

void push(CircularBuffer *cb, int value) {
    if (cb->dem < BUFFER_SIZE) {
        cb->buffer[cb->head] = value;
        cb->dem++;
        cb->head = (cb->head + 1) % BUFFER_SIZE;
    }
}

int pop (CircularBuffer *cb) {
    if (cb->dem == 0) return -1;
    int a = cb->buffer[cb->tail];
    cb->tail = (cb->tail + 1) % BUFFER_SIZE;
    cb->dem--;
    return a;
}

void print(int x) {
    printf("%d\n", x);
}

int main() {
    CircularBuffer cb = {0};
    push(&cb, 10);
    push(&cb, 20);
    push(&cb, 30);
    print(pop(&cb));
    push(&cb, 40);
    push(&cb, 50);
    push(&cb, 60);
    push(&cb, 70);
    for (int i = 0; i < 6; i++) {
        print(pop(&cb));
    }
    return 0;
}