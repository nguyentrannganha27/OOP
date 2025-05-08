#include "Menu.h"
#include "Product.h"
#include <iostream>
#include <vector>
#include <iomanip> // for setw, left

using namespace std;

void printMenu(const vector<Product>& dsSanPham) {
    // In ra tiêu đề chỉ một lần
    cout << "\n========================================\n";
    cout << "             PRODUCT MENU               \n";
    cout << "========================================\n";
    
    // Cột thông tin sản phẩm
    cout << left << setw(5) << "No."
         << setw(15) << "Product"
         << setw(10) << "Price"
         << "Stock\n";
    cout << "----------------------------------------\n";

    // In danh sách sản phẩm
    for (size_t i = 0; i < dsSanPham.size(); ++i) {
        cout << left << setw(5) << i + 1
             << setw(15) << dsSanPham[i].name
             << setw(10) << dsSanPham[i].price
             << dsSanPham[i].quantity << "\n";
    }

    // Các lựa chọn cuối cùng
    cout << "----------------------------------------\n";
    cout << left << setw(5) << dsSanPham.size() + 1 << "Return change\n";
    cout << left << setw(5) << dsSanPham.size() + 2 << "Insert more money\n";;
    cout << "========================================\n";
}
