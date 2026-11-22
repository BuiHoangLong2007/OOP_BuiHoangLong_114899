BÀI TẬP THỰC HÀNH OOP

HỆ THỐNG QUẢN LÝ BÃI ĐỖ XE

GIAI ĐOẠN 5 (BÀI KẾT THÚC)

Chủ đề: StandardTemplateLibrary (std::vector), Con trỏ thông minh (std::unique_ptr), Nguyên lý RAII, Đọc/Ghi Tệp văn bản (<fstream>), và Xử lý Ngoại lệ (try-catch).

1 MỤC TIÊU & YÊU CẦU KỸ THUẬT

• Mục tiêu: Hoàn thiện Hệ thống Quản lý Bãi đỗ xe theo chuẩn C++ hiện đại (Modern C++). Thay thế toàn bộ quản lý bộ nhớ thủ công ở Giai đoạn 3 & 4 bằng Con trỏ thông minh (std::unique_ptr) và Container chuẩn (std::vector), đồng thời bổ sung tính năng lưu trữ dữ liệu lâu dài thông qua Đọc/Ghi Tệp ParkingLotInfo.txt.

• Hạn chế bắt buộc (Strict Constraints):

    1. NGUYÊN LÝ RAII & TỰ ĐỘNG HÓA QUẢN LÝ BỘ NHỚ: Tuyệt đối KHÔNG sử dụng con trỏ thô (raw pointers), không dùng các toán tử quản lý thủ công new / delete. Mọi bộ nhớ động của đối tượng đa hình phải được đóng gói trong std::unique_ptr và quản lý tự động theo nguyên lý RAII (Resource Acquisition Is Initialization).
    2. CONTAINER CHUẨN: Sử dụng std::vector làm cấu trúc dữ liệu lưu trữ chính cho cả danh sách bãi đỗ xe và danh sách phương tiện.
    3. ĐỌC/GHI FILE VĂN BẢN (FILE I/O): Tích hợp hai thư viện <fstream> (ifstream, ofstream) để nạp trạng thái ban đầu của hệ thống từ tệp ParkingLotInfo.txt khi khởi động và ghi lại toàn bộ dữ liệu ra tệp khi lưu/thoát.
    4. XỬ LÝ NGOẠI LỆ (EXCEPTIONHANDLING): Sử dụng các khối try - catch và các lớp ngoại lệ chuẩn (std::invalid_argument, std::runtime_error) để bắt và xử lý các lỗi dữ liệu (ví dụ: file không tồn tại, định dạng dữ liệu trong file bị sai, giá trị đầu vào vượt ngưỡng).

2 CẤU TRÚC VÀ THIẾT KẾ HOÀN THIỆN CÁC LỚP (CLASS SPECIFICATIONS)

2.1 Lớp trừu tượng Vehicle và các lớp con (Car, Motorcycle, Bicycle)

• Giữ nguyên cấu trúc Kế thừa & Đa hình từ Giai đoạn 4.

• Bổ sung phương thức ảo phục vụ việc ghi file:– virtual std::string toFileFormat() const = 0;:Trả về chuỗi định dạng văn bản chuẩn của xe để ghi ra tệp ParkingLotInfo.txt.

2.2 Lớp ParkingLot (Quản lý đa hình bằng Con trỏ thông minh & Vector)

• Thuộc tính (private):

– int parkID, char size, int capacity.

– std::vector<std::unique_ptr<Vehicle» vehicles: Danh sách chứa các con trỏ thông minh sở hữu độc quyền đối tượng xe.

• Phương thức (public):

– Tự động hóa Destructor: Không cần viết Destructor hay Rule of Three nữa, vì std::vector và std::unique_ptr sẽ tự động giải phóng toàn bộ đối tượng xe khi bãi đỗ bị hủy.

– bool addVehicle(std::unique_ptr<Vehicle> v): Nhận quyền sở hữu đối tượng xe thông qua std::move().

– bool removeVehicle(int vID): Tìm xe theo ID và xóa phần tử khỏi vector bằng vehicles.erase().

– const std::vector<std::unique_ptr<Vehicle»& getVehicles() const: Trảvề tham chiếu hằng tới danh sách xe để duyệt dữ liệu.

2.3 Lớp SystemInterface (Tích hợp File I/O và Xử lý Ngoại lệ)

• Thuộc tính (private):

– std::vector<ParkingLot> parkingLots: Danh sách các bãi đỗ xe trong hệ thống.

• Phương thức (public):

– void loadFromFile(const std::string& filename):

∗ Mở tệp ParkingLotInfo.txt bằng std::ifstream.

∗ Đọc từng dòng, bóc tách chuỗi (parsing string) để khởi tạo các đối tượng ParkingLot và các con trỏ std::unique_ptr<Vehicle> tương ứng (Car, Motorcycle, Bicycle).

∗ Nếu không tìm thấy tệp hoặc dữ liệu bị hỏng, quăng ngoại lệ std::runtime_error để chương trình xử lý an toàn.– void saveToFile(const std::string& filename) const:

∗ Mở tệp bằng std::ofstream.

∗ Duyệt qua danh sách parkingLots và vehicles để ghi lại trạng thái hiện tại của hệ thống theo đúng cấu trúc mẫu.

– void runMenu(): Bao bọc các thao tác người dùng trong các khối try - catch để chương trình không bao giờ bị crash đột ngột.

3 ĐỊNH DẠNG TỆP DỮ LIỆU ParkingLotInfo.txt

Tệp dữ liệu lưu trữ thông tin bãi đỗ và phương tiện theo cấu trúc phân cấp:
    
    PARKING_LOT 101 L
    CAR 1001 8 3 4
    MOTORCYCLE 2002 9 2 150
    BICYCLE 3003 14 1 1
    PARKING_LOT 102 M
    CAR 1004 16 2 7
    
• Dòng PARKING_LOT: Chứa [ID Bãi đỗ] [Kích thước: S/M/L].

• Dòng Phương tiện: Chứa[Loại xe: CAR/MOTORCYCLE/BICYCLE][Vehicle ID][Giờ vào] [Thời lượng đỗ] [Thuộc tính riêng].

4 QUY TẮC XỬ LÝ NGOẠI LỆ (EXCEPTIONHANDLING RULES)

1. Lỗi Đầu vào (Invalid Input): Khi người dùng nhập sai kiểu dữ liệu hoặc giờ vào bãi ngoài khoảng 0–23, ném ngoại lệ std::invalid_argument("Gio vao bai khong hop le!").

2. Lỗi Tệp tin (File Error):Khimởfilekhôngthànhcông, némstd::runtime_error("Khong the mo tep ParkingLotInfo.txt!").

3. Bắt Ngoại lệ tại Menu: Hàm runMenu() sử dụng khối try-catch tổng quát:

    try {
    // Thao tac nguoi dung
    } catch (const std::exception& e) {
    std::cout << "[LOI␣HE␣THONG]:␣" << e.what() << "\n";
    }

5 DANH SÁCH CHỨC NĂNG MENU HOÀN CHỈNH (MAIN MENU)

Chương trình hiển thị menu 10 chức năng tích hợp đầy đủ:

1. Tạo Bãi đỗ xe mới: Thêm vào std::vector<ParkingLot>.

2. Thêmxevàobãiđỗ:Khởitạođốitượngbằngstd::make_unique<Car/Motorcycle/Bicycle>() và đưa vào bãi đỗ.

3. Xóa một Bãi đỗ xe: Xóa khỏi vector bãi đỗ.

4. Lấy xe ra khỏi bãi đỗ: Xóa khỏi vector xe trong bãi.

5. Hiển thị danh sách tất cả Bãi đỗ xe.

6. Hiển thị danh sách xe theo bãi cụ thể.

7. Liệt kê xe theo loại phương tiện.

8. Tóm tắt phí đỗ xe trung bình: Sử dụng thuật toán duyệt vector kết hợp Đa hình.

9. Đọc dữ liệu từ Tệp (Chức năng 9): Nạp dữ liệu từ ParkingLotInfo.txt vào hệ thống.

10. Xuất dữ liệu ra Tệp & Thoát (Chức năng 10): Lưu toàn bộ trạng thái hệ thống vào ParkingLotInfo.txt và kết thúc chương trình.

TỔNG KẾT CHUỖI 5 GIAI ĐOẠN PHÁT TRIỂN DỰ ÁN C++ OOP

Giai đoạn ___ Kiến thức C++ Hướng đối tượng trọng tâm ___Thuộc tính lưu trữ dữ liệu

Giai đoạn 1 ___ Đóng gói (Encapsulation), Getters/Setters, Class ___ Các biến đơn lẻ (Vehicle v1, v2, v3)

Giai đoạn 2 ___ Quản lý Tập hợp, Kích thước Logic vs Vật lý ___ Mảng tĩnh cố định (Vehicle vehicles)

Giai đoạn 3 ___ Con trỏ, Bộ nhớ Heap, Rule of Three, Resizing ___ Mảng con trỏ cấp phát động (Vehicle** vehicles)

Giai đoạn 4 ___ Kế thừa (Inheritance), Đa hình (Polymorphism) ___ Con trỏ Lớp cơ sở trừu tượng (Vehicle*)

Giai đoạn 5 ___ Modern C++(RAII, std::vector, std::unique_ptr, File I/O) ___ Container chuẩn & Con
trỏ thông minh
4
