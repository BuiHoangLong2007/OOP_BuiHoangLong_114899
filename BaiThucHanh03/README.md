BÀI TẬP THỰC HÀNH OOP

HỆ THỐNG QUẢN LÝ BÃI ĐỖ XE

GIAI ĐOẠN 3

Chủ đề: Quản lý Bộ nhớ Động (Dynamic Memory Allocation), Con trỏ Thô (Raw Pointers), Destructor, Quy tắc Ba (Rule of Three), và Tự động Mở rộng Sức chứa (Dynamic Resizing).

1 MỤC TIÊU & YÊU CẦU KỸ THUẬT

• Mục tiêu: Nâng cấp hệ thống ở Giai đoạn 2 bằng cách thay thế toàn bộ mảng tĩnh bằng mảng cấp phát động thông qua con trỏ, cho phép bãi đỗ và hệ thống tự động co giãn sức chứa linh hoạt lúc runtime mà không bị giới hạn bởi kích thước cố định ban đầu.

• Hạn chế bắt buộc (Strict Constraints):

    1. QUẢN LÝ BỘ NHỚ THỦ CÔNG:Bắt buộc sử dụng con trỏ thô (*), toán tử cấp phát động new và giải phóng bộ nhớ delete / delete[]. (Chưa dùng std::vector hay con trỏ thông minh std::unique_ptr, hai khái niệm này dành cho Giai đoạn 5).
    2. QUY TẮC BA (RULE OF THREE): Tất cả các lớp quản lý bộ nhớ động (ParkingLot, SystemInterface) bắt buộc phải cài đặt 3 phương thức đặc biệt:
    – Destructor (~Class()): Thu hồi toàn bộ vùng nhớ heap đã cấp phát khi đối tượng bị hủy.
    – Copy Constructor (Class(const Class&)): Thực hiện Sao chép sâu (Deep Copy) khi khởi tạo đối tượng mới từ đối tượng cũ.
    – CopyAssignmentOperator (operator=): ThựchiệnSao chép sâu (Deep Copy) khi gán hai đối tượng cho nhau.
    3. AN TOÀN CON TRỎ: Mọi con trỏ chưa trỏ tới vùng nhớ hợp lệ phải được gán giá trị nullptr. Sau khi delete, lập tức gán lại về nullptr để tránh lỗi Dangling Pointer (con trỏ lơ lửng).
    4. CHỐNG RÒ RỈ BỘ NHỚ (NO MEMORY LEAK): Khi chương trình kết thúc hoặc khi xóa bãi/xe, toàn bộ bộ nhớ cấp phát động phải được giải phóng hoàn toàn.

2 CẤU TRÚC VÀ THIẾT KẾ NÂNG CẤP CÁC LỚP (CLASS SPECIFICATIONS)

2.1 Lớp 1: Vehicle (Tối ưu hóa truyền tham chiếu)

• Thuộc tính (private): vehicleID, vehicleType, entryTime, parkingDuration, parkingFee.

• Phương thức (public): Getters/Setters, calculateFee(), display().

2.2 Lớp 2: ParkingLot (Quản lý mảng con trỏ xe cấp phát động)

• Thuộc tính (private):

– int parkID: Mã định danh bãi đỗ.

– char size: Kích thước bãi (’S’, ’M’, ’L’).

– int capacity: Sức chứa tối đa hiện tại (Khởi tạo ban đầu: S = 1, M = 2, L = 3).

– int currentVehicleCount: Số xe hiện có trong bãi.

– Vehicle** vehicles: Mảng con trỏ động cấp phát trên Heap. Đây là con trỏ trỏ tới một mảng các con trỏ Vehicle* (hoặc Vehicle* vehicles cấp phát mảng đối tượng động).

• Phương thức (public):

– Constructor: ParkingLot(int id, char s) 

— Cấp phát động mảng con trỏ: vehicles = new Vehicle*[capacity], khởi tạo tất cả các ô bằng nullptr.

– Destructor (~ParkingLot()): Tự động duyệt giải phóng từng đối tượng xe delete vehicles[i] và giải phóng mảng con trỏ delete[] vehicles.

– Copy Constructor & Operator=: Cài đặt thuật toán sao chép sâu toàn bộ danh sách xe.

– void resize(int newCapacity): Hàm nội bộ tự động cấp phát mảng con trỏ mới với newCapacity, sao chép các con trỏ cũ sang mảng mới, giải phóng mảng cũ delete[] và cập nhật lại capacity.

– bool addVehicle(const Vehicle& v): Thêm xe vào ô trống. Nếu bãi đã đầy (currentVehicleCount == capacity), tự động gọi resize(capacity * 2)trước khi thêm.

– bool removeVehicle(int vID): Tìm xe theo ID, gọi delete vehicles[i], dồn mảng con trỏ và gán vị trí cuối cùng về nullptr.

2.3 Lớp 3: SystemInterface (Quản lý danh sách bãi đỗ bằng Bộ nhớ Động)

• Thuộc tính (private):

– int lotCapacity: Sức chứa bãi đỗ tối đa hiện tại của hệ thống (Khởi tạo = 5).

– int currentLotCount: Số lượng bãi đỗ hiện có trong hệ thống.

– ParkingLot** parkingLots: Mảng con trỏ động chứa các bãi đỗ xe.

• Phương thức (public):

– Constructor: Cấp phát động mảng bãi đỗ: parkingLots = new ParkingLot*[lotCapacity].

– Destructor (~SystemInterface()): Giải phóng toàn bộ các bãi đỗ delete parkingLots[i] và thu hồi mảng delete[] parkingLots.

– void resizeSystem(int newCapacity): Mở rộng sức chứa bãi đỗ của hệ thống khi vượt quá lotCapacity.

– void runMenu(): Điều khiển menu tương tác và quản lý vòng đời ứng dụng.

3 THUẬT TOÁN BỘ NHỚ & TÍNH NĂNG NÂNG CẤP

1. Thuật toán Tự động Mở rộng Sức chứa (Dynamic Resizing Algorithm):

• Khi thêm một xe vào bãi đầy, hệ thống không báo lỗi đầy bãi nữa mà tự động nhân đôi capacity (capacity = capacity * 2), tạo mảng mới, chép dữ liệu cũ sang và tiếp tục nhận xe mới.

2. Cơ chế Xóa dữ liệu An toàn (Safe Deletion):

• Khi xóa một xe khỏi bãi đỗ:

(a) Thu hồi bộ nhớ của đối tượng xe: delete vehicles[index];

(b) Dồn tất cả các con trỏ phía sau sang bên trái 1 vị trí.

(c) Gán ô con trỏ cuối cùng về nullptr: vehicles[currentVehicleCount- 1] = nullptr;

(d) Giảm currentVehicleCount đi 1.

3. Kiểm tra Rò rỉ Bộ nhớ (Memory Leak Check):

• Tất cả các khối lệnh new bắt buộc phải có khối lệnh delete tương ứng. Đảm bảo khi người dùng chọn Thoát chương trình (Option 9), Destructor của SystemInterface được kích hoạt để dọn dẹp sạch sẽ 100% bộ nhớ Heap.

4 DANH SÁCH CHỨC NĂNG MENU(MAIN MENU)

1. Tạo Bãi đỗ xe mới: Nhập parkID và size. Tự động gọi resizeSystem() nếu danh sách bãi đỗ đã đầy.

2. Thêm xe vào bãi đỗ: Nhập thông tin xe. Tự động mở rộng sức chứa của bãi đỗ nếu bãi đã đầy.

3. Xóa một Bãi đỗ xe: Tìm bãi đỗ, gọi delete parkingLots[i], dồn mảng con trỏ bãi đỗ và cập nhật số lượng.

4. Lấy xe ra khỏi bãi đỗ: Giải phóng bộ nhớ xe bằng delete, dồn mảng con trỏ xe trong bãi tương ứng.

5. Hiển thị danh sách tất cả Bãi đỗ xe: Duyệt mảng con trỏ, bỏ qua các ô nullptr.

6. Hiển thị danh sách xe theo bãi cụ thể: In thông tin chi tiết các xe đang được quản lý bởi con trỏ trong bãi.

7. Liệt kê xe theo loại phương tiện: Duyệt toàn bộ cây con trỏ trong hệ thống để lọc dữ liệu.

8. Tóm tắt phí đỗ xe trung bình: Tính toán phí trung bình dựa trên danh sách xe động.

9. Thoát chương trình: Giải phóng toàn bộ bộ nhớ Heap và kết thúc ứng dụng.
