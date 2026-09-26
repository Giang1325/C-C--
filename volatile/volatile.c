#include <stdio.h>
#include <pthread.h>   // thư viện thread
#include <unistd.h>     // để dùng sleep()

int hardware_flag = 0;

// Hàm này sẽ chạy trên thread phụ — luôn có dạng void* tên_hàm(void* arg)
void* ham_chay_tren_thread_phu(void* arg) {
    sleep(2);                    // giả lập "chờ phần cứng xử lý" mất 2 giây
    hardware_flag = 1;
    printf ("Thread phu: Da doi gia tri!\n");
    return NULL;
}

int main(void) {
    pthread_t thread_id;   // biến định danh cho thread phụ

    // Tạo và CHẠY NGAY thread phụ — 4 tham số: 
    // &thread_id (nơi lưu id), NULL (dùng cấu hình mặc định),
    // tên hàm sẽ chạy trên thread đó, NULL (không truyền tham số vào hàm)
    pthread_create(&thread_id, NULL, ham_chay_tren_thread_phu, NULL);

    // Code ở đây chạy NGAY LẬP TỨC, KHÔNG chờ thread phụ chạy xong
    // → đúng như main() thật không "chờ" ngắt, nó chạy song song
    while (hardware_flag == 0) {}

    printf ("Main: Da phat hien thay doi, thoat vong lap!\n");

    pthread_join(thread_id, NULL);  // chờ thread phụ chạy xong hẳn rồi mới cho main() kết thúc
                                      // (chỉ cần dòng này ở CUỐI chương trình, để không thoát sớm)
    return 0;
}