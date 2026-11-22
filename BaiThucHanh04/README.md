BÀI TẬP THỰC HÀNH OOP

HỆ THỐNG QUẢN LÝ BÃI ĐỖ XE

GIAI ĐOẠN 4

Chủ đề: Kế thừa (Inheritance), Lớp Cơ sở Trừu tượng (Abstract Base Class), Hàm Ảo (Virtual Functions), Hàm Ảo Thuần túy (Pure Virtual Functions), Con trỏ Đa hình (Polymorphic Pointers) và Destructor Ảo (Virtual Destructor).

1 MỤC TIÊU & YÊU CẦU KỸ THUẬT

• Mục tiêu: Tái cấu trúc (Refactor) lớp Vehicle đơn lẻ ở các giai đoạn trước thành cây kế thừa đa hình, tách riêng từng loại phương tiện (Car, Motorcycle, Bicycle) thành các lớp con cụ thể. Sử dụng con trỏ đa hình để tự động hóa việc tính phí đỗ xe và hiển thị thông tin mà không cần dùng các câu lệnh rẽ nhánh if-else hay switch-case theo loại xe.

• Hạn chế bắt buộc (Strict Constraints):

    1. LỚP CƠ SỞ TRỪU TƯỢNG (ABSTRACTBASECLASS): LớpVehicle phải đóng vai trò là lớp cơ sở trừu tượng, chứa ít nhất một Hàm ảo thuần túy (Pure Virtual Function). Bắt buộc không thể khởi tạo trực tiếp đối tượng thuộc lớp Vehicle (Vehicle v → Báo lỗi biên dịch).
    2. DESTRUCTOR ẢO (VIRTUAL DESTRUCTOR): Lớp cơ sở Vehicle bắt buộc phải khai báo Destructor ảo (virtual ~Vehicle()). Điều này đảm bảo khi hủy một con trỏ lớp cơ sở (Vehicle*), Destructor của lớp con tương ứng (Car, Motorcycle, Bicycle) sẽ được tự động kích hoạt đầy đủ để tránh rò rỉ bộ nhớ.
    3. TỪ KHÓA override VÀ final: Tất cả các phương thức ghi đè ở lớp con phải sử dụng từ khóa override (chuẩn C++11) để biên dịch viên kiểm tra tính đúng đắn của prototype.
    4. CON TRỎ ĐA HÌNH: Lớp ParkingLot tiếp tục quản lý mảng con trỏ động Vehicle** vehicles, trong đó mỗi phần tử Vehicle* có thể trỏ tới bất kỳ đối tượng lớp con nào (Car, Motorcycle, hoặc Bicycle).

2 CẤU TRÚC VÀ THIẾT KẾ NÂNG CẤP CÁC LỚP (CLASS SPECIFICATIONS)

2.1 Lớp 1: Lớp cơ sở trừu tượng Vehicle

• Thuộc tính (protected):

– int vehicleID: Mã định danh xe.

– int entryTime: Giờ vào bãi (0–23).

– int parkingDuration: Số giờ đỗ (1–23).

• Phương thức (public):

– Constructor nhận tham số: Vehicle(int id, int entry, int duration).

– Destructor ảo: virtual ~Vehicle() {}.

– Getters/Setters cho các thuộc tính chung.

– Hàm ảo thuần túy tính phí: virtual double calculateFee() const = 0;

– Hàm ảo thuần túy hiển thị: virtual void display() const = 0;

– Hàm ảo thuần túy lấy tên loại xe: virtual std::string getType() const = 0;

2.2 Các Lớp con kế thừa (Car, Motorcycle, Bicycle) 

Lớp Car (Kế thừa public Vehicle)

• Thuộc tính bổ sung (private): int numberOfSeats (Số chỗ ngồi, ví dụ: 4, 7 chỗ).

• Phương thức:

– Constructor khởi tạo thuộc tính chung + thuộc tính riêng numberOfSeats.

– double calculateFee() const override: Đơn giá cơ bản $6.00/giờ, áp dụng quy tắc giờ cao điểm (+30% trong 2h đầu) và giờ thấp điểm (-5% trong 2h đầu,-10% từ h3 trở đi).

– void display() const override: In thông tin xe + số chỗ ngồi.

– std::string getType() const override: Trả về "Car". 

Lớp Motorcycle (Kế thừa public Vehicle)

• Thuộc tính bổ sung (private): int engineCapacity (Dung tích xi-lanh phân khối: cc).

• Phương thức:

– Constructor khởi tạo thuộc tính chung + engineCapacity.

– double calculateFee() const override: Đơn giá cơ bản $4.00/giờ, áp dụng công thức điều chỉnh giá theo giờ cao điểm/thấp điểm.

– void display() const override: In thông tin xe + dung tích phân khối.

– std::string getType() const override: Trả về "Motorcycle".

Lớp Bicycle (Kế thừa public Vehicle)

• Thuộc tính bổ sung (private): bool isElectric (Xe đạp điện hay xe đạp thường).

• Phương thức:

– Constructor khởi tạo thuộc tính chung + isElectric.

– double calculateFee() const override: Đơn giá cơ bản $2.00/giờ, áp dụng công thức điều chỉnh giá theo giờ cao điểm/thấp điểm.

– void display() const override: In thông tin xe + loại xe đạp.

– std::string getType() const override: Trả về "Bicycle".

2.3 Lớp 2: ParkingLot (Áp dụng Cơ chế Đa hình- Dynamic Binding)

• Thuộc tính (private):

– int parkID, char size, int capacity, int currentVehicleCount.

– Vehicle** vehicles: Mảng các con trỏ trỏ tới lớp cơ sở Vehicle*.

• Phương thức (public):

– Giữ nguyên cơ chế cấp phát/giải phóng bộ nhớ động và resize() từ Giai đoạn 3.

– Điểm nâng cấp Đa hình: Trong hàm displayLotInfo() hoặc tính tổng phí, chỉ cần duyệt qua mảng con trỏ và gọi trực tiếp vehicles[i]->calculateFee() hoặc vehicles[i]->display(). Trình biên dịch C++ sẽ tự động tra bảng VTable (Virtual Table) để gọi đúng phương thức của lớp con tương ứng (Car, Motorcycle, hoặc Bicycle).

2.4 Lớp 3: SystemInterface (Khởi tạo đối tượng Đa hình)

• Thuộctính(private):ParkingLot** parkingLots,int lotCapacity,int currentLotCount.

• Phương thức (public):

– Khi người dùng chọn thêm xe mới, dựa vào loại xe người dùng chọn (’C’, ’M’, ’B’), chương trình sẽ cấp phát động đối tượng con tương ứng:

∗ Ví dụ: Vehicle* newVehicle = new Car(id, entry, duration, seats);

∗ Sau đó truyền con trỏ newVehicle nàyvào phương thức parkingLot->addVehicle(newVehicle)

3 ƯU ĐIỂM CỦA MÔ HÌNH ĐA HÌNH TRONG C++ (POLYMORPHISM ADVANTAGES)

1. Nguyên lý Open/Closed (SOLID Principles):

• Hệ thống "Mở cho việc mở rộng, Đóng cho việc sửa đổi". Nếu sau này bãi đỗ xe muốn nhận thêm loại xe mới (ví dụ: ElectricScooter hoặc Truck), ta chỉ cần tạo thêm lớp con mới kế thừa từ Vehicle mà không cần sửa đổi bất kỳ dòng code nào trong lớp ParkingLot hay thuật toán tính phí hiện có.

2. Loại bỏ Mã trùng lặp (Clean Code):

• Lớp ParkingLot không còn tồn tại các đoạn mã switch(vehicleType) dài dòng. Tất cả được tự động hóa thông qua cơ chế Dynamic Binding lúc chương trình chạy (Runtime).

3. An toàn Bộ nhớ với Virtual Destructor:

• Lệnh delete vehicles[i] trong ParkingLot sẽ tự động kích hoạt theo đúng thứ tự: Destructor lớp con → Destructor lớp cơ sở ~Vehicle(), đảm bảo giải phóng hoàn toàn các thuộc tính riêng của lớp con.

4 DANH SÁCH CHỨC NĂNG MENU (MAIN MENU)

1. Tạo Bãi đỗ xe mới: Tạo bãi đỗ với mảng con trỏ động.

2. Thêm xe vào bãi đỗ: Cho phép chọn loại xe (1. Car, 2. Motorcycle, 3. Bicycle). Nhập các thuộc tính chung và thuộc tính riêng từng loại xe, khởi tạo đối tượng kế thừa bằng new và lưu con trỏ vào bãi đỗ.

3. Xóa một Bãi đỗ xe: Giải phóng bãi đỗ và toàn bộ cây con trỏ xe bên trong bãi.

4. Lấy xe ra khỏi bãi đỗ: Kích hoạt Destructor ảo để xóa xe an toàn.

5. Hiển thị danh sách tất cả Bãi đỗ xe: Sử dụng đa hình để hiển thị thông tin từng xe.

6. Hiển thị danh sách xe theo bãi cụ thể: In chi tiết phương tiện bằng phương thức ảo display().

7. Liệt kê xe theo loại phương tiện:SosánhchuỗitrảvềtừphươngthứcảogetType().

8. Tóm tắt phí đỗ xe trung bình: Gọi hàm ảo calculateFee() đa hình để tính toán phí cho từng loại xe.

9. Thoát chương trình: Dọn dẹp bộ nhớ toàn bộ cây con trỏ đa hình.
