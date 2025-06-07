#ifndef ADMIN_H
#define ADMIN_H

#include "Product.h"
#include "Promotion.h"
#include <vector>
#include <string>

// Lớp Admin chịu trách nhiệm xử lý chức năng của quản trị viên
class Admin {
private:
    // Mật khẩu quản trị viên (mặc định, bạn có thể định nghĩa trong Admin.cpp)
    static const std::string ADMIN_PASSWORD;

    // ======== Các hàm hỗ trợ dùng nội bộ ========

    // Hàm nhập mật khẩu nhưng không hiển thị ra màn hình
    static std::string getHiddenPassword();

    // Định dạng thời gian (time_t) thành chuỗi dễ đọc
    static std::string formatTime(time_t rawTime);

    // Chuyển chuỗi về chữ thường (để so sánh không phân biệt hoa thường)
    static std::string toLowerCase(const std::string& str);

    // Hàm nhập số nguyên hợp lệ, có giới hạn nhỏ nhất
    static int getValidInput(int minValue, const std::string& prompt);

public:
    // ======== Các hàm xử lý chính ========

    // Xác thực quyền quản trị viên bằng mật khẩu
    static bool authenticate();

    // Hiển thị menu dành cho quản trị viên
    static void showMenu(std::vector<Product>& products, std::vector<PromoCode>& promoList);

    // ======== Quản lý sản phẩm ========

    // Thêm sản phẩm mới vào danh sách
    static void addProduct(std::vector<Product>& products);

    // Xóa sản phẩm khỏi danh sách
    static void removeProduct(std::vector<Product>& products);

    // Sửa thông tin sản phẩm (giá, số lượng, tên)
    static void modifyProduct(std::vector<Product>& products);

    // Xem số dư và doanh thu hiện tại của máy
    static void viewCurrentBalance();

    // ======== Quản lý mã khuyến mãi ========

    // Thêm mã khuyến mãi mới
    static void addPromoCode(std::vector<PromoCode>& promoList);

    // Xóa mã khuyến mãi
    static void removePromoCode(std::vector<PromoCode>& promoList);

    // Chỉnh sửa mã khuyến mãi
    static void editPromoCode(std::vector<PromoCode>& promoList);
};

#endif // ADMIN_H
