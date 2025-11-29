# Tuần 2 - Scanner

## Nội dung
- Bài 1 : Hoàn thành code trong mục TODO
Link code: https://www.dropbox.com/scl/fi/81ntztalmvg83nub64tmi/Bai2.zip?rlkey=hw1ggfvu465g5kt6wq7j78o48&e=1&dl=0

- Bài 2:  Chỉnh sửa code để cập nhật thêm các yêu cầu sau
  - Thêm kiểu dữ liệu string, phép toán lấy phần dư vào từ vựng KPL
  - Thêm kiểu comment mới : Nếu // sẽ là comment đến cuối dòng, tương tự C++
  - Thêm kiểu dữ liệu bytes
  - Thêm phép toán lấy mũ **. Ví dụ: 2**10 thể hiện 2^10
  - hêm từ khóa REPEAT và UNTIL cho cấu trúc lệnh REPEAT <statement> UNTIL <condition>;

## Yêu cầu môi trường
- Hệ điều hành: Windows / Linux / macOS
- C/C++ compiler hỗ trợ C99 hoặc mới hơn
- CMake: phiên bản 3.20 (khuyến nghị)

## Hướng dẫn build and run
- git clone https://github.com/pdd04/CTD.git
- cd CTD
- mkdir build
- cd build
- cmake ..
- cmake --build .
- cd Tuan_2
- ./scanner.exe test\\[ten_file_kpl].kpl
