1. Giải thích các loại tệp (File Extensions)

Hệ thống sử dụng các hậu tố tệp để phân loại vai trò trong quá trình kiểm tra tự động:

    .scm (Scheme Source Code):

        Đây là các tệp chứa mã nguồn chương trình.

        Ví dụ: lexer.scm (mã bạn viết), tokenize-tester.scm (mã của trường cung cấp để chạy kiểm tra).

    .in (Input):

        Chứa dữ liệu đầu vào là các đoạn mã Scheme thô mà Lexer hoặc Parser của bạn cần xử lý.

        Ví dụ: simple.in chứa các biểu thức đơn giản như (+ 1 2).

    .err (Error Input):

        Đây cũng là tệp đầu vào, nhưng chứa các mã "lỗi" cố ý (ví dụ: định danh sai quy tắc).

        Mục tiêu là để kiểm tra xem Lexer/Parser của bạn có nhận diện và báo lỗi (error) đúng như yêu cầu hay không.

    .expect (Expected Output):

        Đây là "đáp án mẫu". Nó chứa kết quả chuẩn mà chương trình của bạn nên in ra nếu mã của bạn chạy đúng.

2. Cách thức hoạt động của hệ thống Test

Quá trình kiểm tra diễn ra theo mô hình So sánh kết quả đầu ra:
Bước 1: Chạy chương trình với dữ liệu mẫu

Bạn sử dụng trình thông dịch plt-r5rs để chạy tệp tester, sau đó "bơm" dữ liệu từ tệp .in vào.

    Lệnh thực hiện: plt-r5rs tokenize-tester.scm < simple.in > simple.out

    Ở đây, simple.out là kết quả do mã của bạn tạo ra.

Bước 2: So sánh (Diff)

Hệ thống (hoặc bạn) sẽ so sánh tệp kết quả bạn vừa tạo (.out) với tệp đáp án mẫu (.expect).

    Lệnh thực hiện: diff simple.out simple.expect

    Nếu không có sự khác biệt, mã của bạn đã vượt qua bài test đó.
