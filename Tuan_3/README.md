# Tuần 3 - Parser

## Nội dung
- Bài 1 : Đọc slide và hoàn thiện code cho parser (Các mục đã được đánh dấu TODO)
  - link bài gốc: https://github.com/pdd04/CTD/commit/b50674881eadc0f6875b129a7bcca79571b75a4b

- Bài 2:  Modify chương trình để có thể hoàn thành thêm các yêu cầu sau:
    - Thêm cú pháp repeat <statement> until <condition>
    - Thêm lệnh gán nhiều biến dạng x,y,z := <expression1>,<expression2>,<expression3>

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
- cd Tuan_3
- ./parser.exe test\\[ten_file_kpl].kpl