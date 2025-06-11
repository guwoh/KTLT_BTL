# Hệ Thống Quản Lý Thư Viện

Hệ thống quản lý thư viện cho phép quản lý sách và việc mượn/trả sách. Hệ thống được viết bằng C++ và sử dụng lưu trữ dữ liệu dưới dạng binary và text.

## Cấu Trúc Thư Mục

```
.
├── data/               # Thư mục chứa dữ liệu
│   ├── books.bin      # File binary chứa thông tin sách và phiếu mượn
│   ├── books.txt      # File text chứa thông tin sách
│   └── borrowers.txt  # File text chứa thông tin người mượn
├── include/           # Thư mục chứa các file header
│   ├── book.h         # Định nghĩa lớp Book
│   ├── borrowSlip.h   # Định nghĩa lớp BorrowSlip
│   ├── borrowableBook.h # Định nghĩa lớp BorrowableBook
│   ├── library.h      # Định nghĩa lớp Library
│   └── io.h          # Định nghĩa các hàm I/O
└── src/              # Thư mục chứa mã nguồn
    ├── book.cpp      # Triển khai lớp Book
    ├── borrowSlip.cpp # Triển khai lớp BorrowSlip
    ├── borrowableBook.cpp # Triển khai lớp BorrowableBook
    ├── library.cpp   # Triển khai lớp Library
    ├── io.cpp        # Triển khai các hàm I/O
    └── main.cpp      # Hàm main và menu chính
```

## Các Lớp Chính (CLASS)

### 1. Book (Sách)
- Lớp cơ sở cho các loại sách
- Chứa thông tin cơ bản: ID, tiêu đề, tác giả, số lượng
- Các phương thức:
  - `getId()`: Lấy ID sách
  - `getTitle()`: Lấy tiêu đề sách
  - `getAuthor()`: Lấy tác giả
  - `getQuantity()`: Lấy số lượng sách
  - `display()`: Hiển thị thông tin sách

### 2. BorrowSlip (Phiếu Mượn)
- Quản lý thông tin mượn sách
- Chứa thông tin: ID sách, tên người mượn, ngày mượn, ngày trả
- Các phương thức:
  - `getBorrowerName()`: Lấy tên người mượn
  - `getBorrowDate()`: Lấy ngày mượn
  - `getReturnDate()`: Lấy ngày trả
  - `isBookReturned()`: Kiểm tra sách đã trả chưa
  - `returnBook(returnDate)`: Đánh dấu sách đã trả
    - Cập nhật ngày trả sách
    - Đánh dấu trạng thái đã trả
  - `display()`: Hiển thị thông tin phiếu mượn

### 3. BorrowableBook (Sách Có Thể Mượn)
- Kế thừa từ lớp Book
- Quản lý việc mượn/trả sách
- Các phương thức:
  - `borrowBook()`: Cho mượn sách
  - `returnBook(borrowerName, returnDate)`: Nhận trả sách
    - Tìm phiếu mượn chưa trả của người mượn
    - Gọi `BorrowSlip::returnBook` để đánh dấu đã trả
    - Tăng số lượng sách lên 1
    - Trả về true nếu thành công, false nếu không tìm thấy phiếu mượn
  - `getBorrowSlipCount()`: Lấy số lượng phiếu mượn
  - `getBorrowSlips()`: Lấy danh sách phiếu mượn
  - `addBorrowSlip()`: Thêm phiếu mượn mới

### 4. Library (Thư Viện)
- Quản lý toàn bộ thư viện
- Các phương thức:
  - `addBook()`: Thêm sách mới
  - `removeBook()`: Xóa sách
  - `findBook()`: Tìm sách theo ID
  - `getBookCount()`: Lấy số lượng sách
  - `getAllBooks()`: Lấy danh sách tất cả sách
  - `displayAllBooks()`: Hiển thị tất cả sách
  - `displayBorrowHistory()`: Hiển thị lịch sử mượn/trả

### 5. IO (Input/Output)
- Quản lý việc đọc/ghi dữ liệu
- Các phương thức:
  - `loadData()`: Đọc dữ liệu từ file
  - `saveData()`: Lưu dữ liệu vào file

## Cấu Trúc Dữ Liệu

### File Binary (books.bin)
```
[Số lượng sách]
[Thông tin sách 1]
  - ID (int)
  - Độ dài tiêu đề (int)
  - Tiêu đề (char[])
  - Độ dài tác giả (int)
  - Tác giả (char[])
  - Số lượng (int)
  - Số lượng phiếu mượn (int)
  [Thông tin phiếu mượn 1]
    - Độ dài tên người mượn (int)
    - Tên người mượn (char[])
    - Độ dài ngày mượn (int)
    - Ngày mượn (char[])
    - Độ dài ngày trả (int)
    - Ngày trả (char[])
    - Trạng thái trả (bool)
  [Thông tin phiếu mượn 2]
  ...
[Thông tin sách 2]
...
```

### File Text (books.txt)
```
=== DANH SACH SACH ===
ID: [id]
Ten sach: [title]
Tac gia: [author]
So luong: [quantity]
-------------------
```

### File Text (borrowers.txt)
```
=== DANH SACH NGUOI MUON ===
Sach ID: [id]
Ten sach: [title]
  Nguoi muon: [borrower]
  Ngay muon: [borrow_date]
  Trang thai: [Da tra/Chua tra]
  Ngay tra: [return_date] (nếu đã trả)
  -------------------
-------------------
```

## Cách Sử Dụng

1. Chạy chương trình:

biên dịch : g++ book.cpp  borrowSlip.cpp  borrowableBook.cpp  library.cpp  main.cpp io.cpp -o run

chạy : ./run

2. Menu chính cung cấp các chức năng:
   - Thêm sách mới
   - Xóa sách
   - Hiển thị tất cả sách
   - Mượn sách
   - Trả sách
   - Xem lịch sử mượn/trả
   - Thoát

3. Dữ liệu được tự động lưu khi thoát chương trình và được tải khi khởi động.

## Lưu ý
- Thư mục `data` sẽ được tự động tạo khi chạy chương trình
- Dữ liệu được lưu dưới dạng binary để tối ưu hiệu suất và text để dễ đọc
- Mỗi sách có một ID duy nhất
- Mỗi phiếu mượn gắn với một sách cụ thể