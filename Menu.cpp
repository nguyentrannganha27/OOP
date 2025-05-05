#include "Menu.h"
#include "Product.h"    // cần để biết về Product
#include <iostream>
#include <vector>       // cần để dùng vector

using namespace std;

void printMenu(const vector<Product>& dsSanPham) {
    cout << "\nMENU:\n";
    for (size_t i = 0; i < dsSanPham.size(); ++i) {
        cout << i + 1 << ". " << dsSanPham[i].ten
             << " - " << dsSanPham[i].gia << " do"
             << " (con  " << dsSanPham[i].soLuong << ")\n";
    }
    cout << dsSanPham.size() + 1 << ". Tra tien lai\n";
    cout << dsSanPham.size() + 2 << ". Nap tien them\n";
    cout << dsSanPham.size() + 3 << ". Thoat, tu dong tra tien lai\n";
}
