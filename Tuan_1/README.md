## Nội dung
Hướng dẫn
Yêu cầu:

Đọc một tệp văn bản (ví dụ: vanban.txt) và xây dựng bảng chỉ dẫn (Index) cho tệp.
Bảng chỉ dẫn liệt kê tất cả các từ xuất hiện trong văn bản, mỗi từ chỉ xuất hiện một lần, kèm theo số lần từ đó xuất hiện và danh sách số dòng mà từ đó xuất hiện.

Ví dụ:

answer 7, 8, 12, 15
ant      2, 4, 6
baby     7, 9, 21
cruel    2, 4, 5

Trên mỗi dòng: Đầu tiên là từ, sau đó là phần dãy số. Số đầu tiên là số lần xuất hiện của từ, các số tiếp theo là chỉ số dòng mà từ đó xuất hiện.
Chú ý
Định nghĩa từ:

Từ là chuỗi các ký tự chữ cái, được phân tách bởi khoảng trắng hoặc dấu phân cách.

Không phân biệt chữ hoa/chữ thường. Khi đưa vào chỉ mục, chuyển toàn bộ về chữ thường.

Sắp xếp:

Các từ trong chỉ mục phải được sắp xếp theo thứ tự từ điển (lexicographical order).

Cấu trúc dữ liệu:

Giả sử số lượng mục từ không quá lớn, có thể lưu toàn bộ vào một mảng.

Không đưa vào chỉ mục:

Các từ không có ý nghĩa tra cứu, được liệt kê trong tệp stopw.txt (mỗi từ một dòng). Tệp này nhỏ và có thể đọc toàn bộ vào một mảng.

Danh từ riêng, tức là những từ có chữ cái đầu viết hoa nhưng không đứng sau dấu chấm câu.

Lưu danh sách dòng:

Danh sách số dòng mà mỗi từ xuất hiện có thể lưu bằng một chuỗi ký tự.

Chi tiết download tại đây:

https://www.dropbox.com/scl/fi/hjys5wawpkrru0ejkbtmd/Bai1.zip?rlkey=feficjfto8ax3maw824xlty4d&dl=0

## Yêu cầu môi trường
- Hệ điều hành: Windows / Linux / macOS
- C/C++ compiler hỗ trợ C99 hoặc mới hơn
- CMake: phiên bản **3.20** (khuyến nghị)

## Hướng dẫn build bằng CMake
- git clone https://github.com/pdd04/CTD.git
- cd CTD
- mkdir build
- cd build
- cmake ..
- cmake --build .
  sau đó vào thư mục của tuần tương ứng để chạy file exe