#ifndef ADMIN_H  // Nếu chưa định nghĩa ADMIN_H thì tiếp tục
#define ADMIN_H  // Định nghĩa ADMIN_H để tránh include nhiều lần

#include "Product.h"    // Bao gồm định nghĩa lớp Product
#include <vector>       // Sử dụng vector để quản lý danh sách sản phẩm
#include <string>       // Sử dụng string để quản lý chuỗi

const std::string ADMIN_PASSWORD = "admin123";  // Mật khẩu mặc định cho admin

// Hàm xác thực mật khẩu admin, trả về true nếu đúng
bool authenticateAdmin();

// Hiển thị menu quản trị và xử lý các lựa chọn
void showAdminMenu(std::vector<Product>& products);

// Thêm sản phẩm mới vào danh sách
void addProduct(std::vector<Product>& products);

// Xóa sản phẩm khỏi danh sách
void removeProduct(std::vector<Product>& products);

// Sửa thông tin sản phẩm có trong danh sách
void modifyProduct(std::vector<Product>& products);

// Xem lịch sử bán hàng (chưa triển khai trong file hiện tại)
void viewSalesHistory();

// Xem tổng doanh thu hiện tại
void viewCurrentBalance();

#endif  // Kết thúc phần định nghĩa ADMIN_H
