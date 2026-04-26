# Project-DSA
================================
    HỆ THỐNG BÃI GIỮ XE
================================
1. Gửi xe
2. Trả xe
3. Xem danh sách chỗ trống
4. Thoát
================================

1. Gửi xe
Mô tả:
Khách hàng đưa xe vào bãi, hệ thống tự tìm vị trí trống gần nhất (theo thứ tự hàng A→Z, vị trí 1→m), ghi nhận thời gian vào, lưu thông tin xe.
Cấu trúc dữ liệu áp dụng:
- Linked list (danh sách chỗ trống) để lấy vị trí đầu tiên (O(1)).
- Hash table (tự cài, va chạm bằng linked list) để kiểm tra biển số trùng nhanh.
- Mảng 2D lưu trạng thái từng ô.
Giải thuật xử lý:
1. Nhập biển số.
2. Tra hash table: nếu đã tồn tại → báo lỗi "Xe đang ở trong bãi" và thoát.
3. Kiểm tra linked list chỗ trống: nếu rỗng → báo "Bãi đầy".
4. Lấy node đầu tiên từ linked list (layDau()) → được (hàng, vị trí).
5. Lấy thời gian hiện tại (time(0)).
6. Cập nhật mảng 2D tại [hàng][vị trí] = thông tin xe (biển số, thời gian).
7. Thêm vào hash table (key=biển số, value = hàng, vị trí, thời gian).
8. Ghi file.txt (ghi đè toàn bộ) để đồng bộ.
9. Xuất thông báo: "Xe đã gửi tại hàng X, vị trí Y. Thời gian vào: HH:MM:SS".
Đầu vào:
Biển số (string, không dấu cách, ví dụ "30A-12345")
Đầu ra:
Thông báo thành công hoặc lỗi, cập nhật file
Xử lý lỗi:
- Biển số đã có → báo lỗi, không gửi.
- Bãi đầy → báo lỗi.
- Lỗi ghi file → báo nhưng vẫn giữ dữ liệu trong bộ nhớ.

2. Trả xe
Mô tả
Khách trả xe, hệ thống tìm vị trí xe, tính tiền dựa trên thời gian gửi, giải phóng chỗ.
Cấu trúc dữ liệu áp dụng:
- Hash table để tra cứu nhanh vị trí và thời gian vào (O(1) trung bình).
- Linked list để thêm chỗ trống đã giải phóng (vào đúng thứ tự ưu tiên).
- Mảng 2D để xóa thông tin.
Giải thuật xử lý:
1. Nhập biển số.
2. Tra hash table: nếu không tìm thấy → báo "Không có xe này" và thoát.
3. Lấy được hàng, vị trí, thời gian vào.
4. Lấy thời gian hiện tại = thời gian ra.
5. Tính tiền (tinhTien(vao, ra)).
6. Xóa khỏi hash table.
7. Xóa mảng 2D tại ô đó (gán nullptr).
8. Thêm vị trí (hàng, vị trí) vào linked list chỗ trống (gọi them() – tự động chèn đúng thứ tự).
9. Ghi file.txt (ghi đè).
10. Xuất hóa đơn (biển số, thời gian vào/ra, tổng giờ, số tiền).
Đầu vào:
Biển số xe
Đầu ra:
 Hóa đơn chi tiết, cập nhật file
Xử lý lỗi:
- Không tìm thấy biển số → báo lỗi, không trả.
- Lỗi ghi file → báo nhưng dữ liệu bộ nhớ vẫn đã thay đổi.

3. Xem danh sách chỗ trống
Mô tả:
Nghiệp vụ, Hiển thị tất cả các vị trí trong bãi hiện chưa có xe, theo thứ tự ưu tiên (hàng A... vị trí 1...).
Cấu trúc dữ liệu áp dụng: 
Duyệt linked list DanhSachChoTrong (đã được sắp xếp sẵn). Không cần mảng 2D.
Giải thuật:
1. Gọi hàm hienThi() của linked list, nó duyệt từ đầu đến cuối, in ra từng node dạng "A1", "B3",...
2. Nếu linked list rỗng thì in "Bãi đã đầy, không còn chỗ trống".
Đầu vào: Không
Đầu ra:
 Danh sách chỗ trống (dạng: A1, A2, B5, ...)
Xử lý lỗi: Không có

CÁC HÀM BỔ TRỢ (không phải chức năng menu)
Hàm	Mô tả	Áp dụng DSA
tinhTien(time_t vao, time_t ra)	Tính tiền dựa trên chênh lệch thời gian (30 phút đầu 5k, mỗi giờ tiếp 10k)	Không đặc biệt, chỉ số học.
ghiFile(string tenFile)	Ghi toàn bộ trạng thái hiện tại (mảng 2D, hash table) ra file	Duyệt mảng 2D (O(n*m)).
docFile(string tenFile)	Đọc file và xây dựng lại cấu trúc dữ liệu	Tái tạo linked list và hash table.


FORMAT FILE DỮ LIỆU 
Cấu trúc tổng quát
<n> <m>
<bienso1> <hang1> <vitri1> <thoigian1>
<bienso2> <hang2> <vitri2> <thoigian2>
...
Quy tắc định dạng
Thành phần	Kiểu dữ liệu	Ghi chú
n	int	Số hàng (A → ...), 1 ≤ n ≤ 26
m	int	Số vị trí mỗi hàng, 1 ≤ m ≤ 99
bienso	string	Không có khoảng trắng, tối đa 15 ký tự
hang	char	Từ 'A' đến ký tự n - 1
vitri	int	Từ 1 đến m
thoigian	long long	Timestamp Unix (giây từ 1970)

VÍ DỤ CỤ THỂ:
3 2
30A-12345 A 1 1735000000
29B-67890 B 2 1735000100
Giải thích:
Bãi có 3 hàng (A, B, C), mỗi hàng 2 vị trí.
Xe 1: biển 30A-12345 ở A1, vào lúc 1735000000
Xe 2: biển 29B-67890 ở B2, vào lúc 1735000100
