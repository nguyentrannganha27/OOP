
# 💻 Hệ Thống Quản Lý Máy Bán Hàng – Đồ Án Lập Trình Hướng Đối Tượng (C++)

## 📝 Giới thiệu
Đây là đồ án môn học lập trình hướng đối tượng (OOP) sử dụng ngôn ngữ C++. Dự án mô phỏng một hệ thống máy bán hàng thông minh với các chức năng quản lý sản phẩm, xử lý đơn hàng, tính hóa đơn, áp dụng mã khuyến mãi và theo dõi doanh thu. Chương trình được thiết kế với kiến trúc hướng đối tượng nhằm tăng tính mở rộng, dễ bảo trì và dễ nâng cấp.

---

## 🎯 Mục tiêu của dự án
- Vận dụng các nguyên lý OOP: đóng gói, phân tách module, quản lý dữ liệu bằng class.
- Mô phỏng quy trình bán hàng và quản lý sản phẩm tương tự thực tế.
- Hỗ trợ giao diện điều khiển dễ sử dụng, thân thiện với người dùng.
- Cung cấp quyền truy cập dành riêng cho quản trị viên.

---

## 🔧 Tính năng nổi bật
- Đăng nhập bằng tài khoản quản trị.
- Quản lý sản phẩm: thêm, sửa, xóa.
- Quản lý mã khuyến mãi linh hoạt.
- Tạo đơn hàng, tính tổng tiền có áp dụng giảm giá.
- In hóa đơn chi tiết cho khách hàng.
- Theo dõi và thống kê doanh thu, số dư hiện tại của máy bán hàng.

---

## 📂 Cấu trúc thư mục

```
OOP-main/
│
├── main.cpp                # Hàm main, khởi động chương trình
├── Admin.{cpp,h}          # Chức năng quản trị hệ thống
├── Product.{cpp,h}        # Quản lý thông tin sản phẩm
├── Order.{cpp,h}          # Xử lý đơn hàng và giỏ hàng
├── Invoice.{cpp,h}        # In và hiển thị hóa đơn
├── Promotion.{cpp,h}      # Áp dụng và quản lý mã khuyến mãi
├── Moneymanager.{cpp,h}   # Quản lý số dư và doanh thu
├── Menu.{cpp,h}           # Giao diện menu người dùng
├── README.md              # Tài liệu mô tả dự án
```

---

## 🚀 Hướng dẫn biên dịch và chạy chương trình

### ⚙️ Yêu cầu hệ thống:
- Trình biên dịch C++ (G++, MSVC, Code::Blocks, v.v.)
- Hệ điều hành: Windows, Linux hoặc macOS

### 📦 Lệnh biên dịch (dùng terminal):
```bash
g++ main.cpp Admin.cpp Product.cpp Order.cpp Invoice.cpp Promotion.cpp Moneymanager.cpp Menu.cpp -o vending_machine
```

### ▶️ Chạy chương trình:
```bash
./vending_machine
```

---

## 📈 Hướng phát triển tương lai
- Lưu và đọc dữ liệu từ file (ví dụ: `products.txt`, `orders.txt`).
- Giao diện người dùng bằng thư viện đồ họa như SFML hoặc Qt.
- Thêm chức năng thống kê theo ngày/tháng/năm.
- Phân quyền nâng cao cho nhiều loại tài khoản người dùng.

---
