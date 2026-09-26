# Embedded – Nền tảng C/C++ cho lập trình nhúng

Đây là nơi mình lưu lại các bài tập tự luyện trong quá trình tự học nền tảng C/C++ trước khi bước vào lập trình vi điều khiển (STM32/ESP32). Lộ trình được mình tự thiết kế dựa trên các kỹ năng thực tế mà lập trình nhúng đòi hỏi: con trỏ, quản lý bộ nhớ, thao tác bit, struct/union và kiến trúc máy tính.

**Nguyên tắc học:** học đến đâu code tay đến đó — không đọc lý thuyết suông, mỗi khái niệm đều có bài tập tự kiểm tra để chứng minh đã hiểu, không chỉ "biết".

## Lộ trình 5 module (8 tuần)

| Module | Nội dung                                   | Tuần |
|--------|---------------------------------------------|------|
| 1      | Con trỏ (Pointers)                          | 1–2  |
| 2      | Cấp phát & quản lý bộ nhớ (Stack/Heap)      | 2–3  |
| 3      | Thao tác bit (Bitwise)                      | 3–4  |
| 4      | Struct / Union / tổ chức dữ liệu            | 4–5  |
| 5      | Kiến trúc máy tính & Memory Map             | 5–7  |
| —      | Mini-project tổng hợp                       | 8    |

## Cấu trúc thư mục

| Thư mục | Thuộc Module | Nội dung |
|---|---|---|
| `pointer/` | Module 1 – Con trỏ | Swap bằng con trỏ, duyệt mảng chỉ dùng con trỏ, mảng con trỏ hàm mô phỏng bảng lệnh, phân biệt `int *p` và `int **p` |
| `memory/`, `memory_leak/` | Module 2 – Quản lý bộ nhớ | Stack vs Heap, dangling pointer, double-free, quan sát memory leak |
| `circular_buffer/` | Module 2 – Quản lý bộ nhớ | Circular buffer cài bằng mảng tĩnh (không dùng heap) — cấu trúc phổ biến cho UART/sensor buffer |
| `bit_field/`, `1_bit_count/` | Module 3 – Thao tác bit | Macro SET/CLEAR/TOGGLE/CHECK bit, đếm số bit 1 trong một số nguyên |
| `status_shown/` | Module 3 – Thao tác bit | Mô phỏng thanh ghi trạng thái (set/clear bit tượng trưng bật/tắt LED, bật ngắt) |
| `padding/` | Module 4 – Struct/Union | Memory layout của struct, khái niệm padding/alignment |
| `union/` | Module 4 – Struct/Union | Dùng union chuyển đổi qua lại giữa float và 4 byte riêng lẻ |
| `volatile/` | Module 5 – Kiến trúc máy tính | Từ khóa `volatile`, mô phỏng con trỏ trỏ vào địa chỉ thanh ghi phần cứng (memory-mapped register) |
| `mini_project/` | Tuần 8 – Mini-project tổng hợp | Mô phỏng bộ điều khiển thiết bị giả lập: kết hợp struct + bit-field, con trỏ hàm, circular buffer, union — không dùng `malloc`/`new` khi chạy |
| `1+2+3+4/`, `1+2+3+4_hardcore/` | Khởi động | Bài tập làm quen vòng lặp, tính tổng cơ bản trước khi vào lộ trình chính |

## Công cụ sử dụng

- Trình biên dịch: `gcc` / `g++`
- Kiểm tra lỗi bộ nhớ: `valgrind`
- Tra cứu cú pháp: [cppreference.com](https://cppreference.com)

## Bước tiếp theo

Sau khi hoàn thành checklist tự đánh giá (hiểu con trỏ hàm, Stack/Heap, bitwise, padding/alignment, union, volatile, memory map), bước kế tiếp là chuyển sang lập trình vi điều khiển thật (STM32) — cấu hình GPIO/Ngắt/Timer/ADC bằng thao tác thanh ghi trực tiếp.
