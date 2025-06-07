#include "Menu.h"       // Bao gồm định nghĩa hàm Menu
#include "Product.h"    // Bao gồm định nghĩa lớp Product
#include <iostream>     // Sử dụng cout để hiển thị ra màn hình
#include <vector>       // Dùng vector để chứa danh sách sản phẩm
#include <iomanip>      // Dùng setw và left để căn chỉnh bảng hiển thị

using namespace std;

// Định nghĩa hàm static trong class Menu
void Menu::printMenu(const vector<Product>& dsSanPham) {
    // In tiêu đề menu
    cout << "\n========================================\n";
    cout << "             PRODUCT MENU               \n";
    cout << "========================================\n";

    // In tiêu đề cột: số thứ tự, tên sản phẩm, giá, số lượng còn lại
    cout << left << setw(5) << "No."           // Cột số thứ tự sản phẩm
         << setw(15) << "Product"              // Cột tên sản phẩm
         << setw(10) << "Price"                // Cột giá tiền
         << "Stock\n";                         // Cột số lượng tồn kho
    cout << "----------------------------------------\n";

    // In từng dòng sản phẩm từ vector
    for (size_t i = 0; i < dsSanPham.size(); ++i) {
        cout << left << setw(5) << i + 1                            // Số thứ tự
             << setw(15) << dsSanPham[i].name                      // Tên sản phẩm
             << setw(10) << dsSanPham[i].price                     // Giá tiền
             << dsSanPham[i].quantity << "\n";                     // Số lượng còn lại
    }

    // In các lựa chọn thêm bên dưới danh sách sản phẩm
    cout << "----------------------------------------\n";
    cout << left << setw(5) << dsSanPham.size() + 1 << "Return change\n";      // Lựa chọn trả lại tiền thừa
    cout << left << setw(5) << dsSanPham.size() + 2 << "Insert more money\n";  // Lựa chọn nạp thêm tiền
    cout << "========================================\n";
}
