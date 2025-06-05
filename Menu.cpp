#include "Menu.h"
#include "Product.h"
#include <iostream>
#include <vector>
#include <iomanip> // Dùng setw và left để căn chỉnh bảng

using namespace std;

// Hàm in ra danh sách sản phẩm dưới dạng menu
void printMenu(const vector<Product>& dsSanPham) {
    // In phần tiêu đề bảng
    cout << "\n========================================\n";
    cout << "             PRODUCT MENU               \n";
    cout << "========================================\n";
    
    // In các tiêu đề cột với căn trái, rộng từng cột cụ thể
    cout << left << setw(5) << "No."          // Số thứ tự
         << setw(15) << "Product"            // Tên sản phẩm
         << setw(10) << "Price"              // Giá
         << "Stock\n";                       // Số lượng tồn kho
    cout << "----------------------------------------\n";

    // Duyệt qua danh sách sản phẩm để in từng dòng chi tiết
    for (size_t i = 0; i < dsSanPham.size(); ++i) {
        cout << left << setw(5) << i + 1                // Số thứ tự bắt đầu từ 1
             << setw(15) << dsSanPham[i].name           // Tên sản phẩm
             << setw(10) << dsSanPham[i].price          // Giá sản phẩm
             << dsSanPham[i].quantity << "\n";          // Số lượng trong kho
    }

    // In các tùy chọn bổ sung ở cuối menu
    cout << "----------------------------------------\n";
    cout << left << setw(5) << dsSanPham.size() + 1 << "Return change\n";  // Trả lại tiền thừa
    cout << left << setw(5) << dsSanPham.size() + 2 << "Insert more money\n"; // Nạp thêm tiền
    cout << "========================================\n";
}
