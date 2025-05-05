#include "Menu.h"
#include <iostream>
using namespace std;

void printMenu(const vector<Product>& dsSanPham) {
    cout << "\nMENU:\n";
    for (size_t i = 0; i < dsSanPham.size(); ++i) {
        cout << i + 1 << ". " << dsSanPham[i].ten
             << " - " << dsSanPham[i].gia << " đô"
             << " (còn " << dsSanPham[i].soLuong << ")\n";
    }
    cout << dsSanPham.size() + 1 << ". Trả lại tiền\n";
    cout << dsSanPham.size() + 2 << ". Nạp thêm tiền\n";
    cout << dsSanPham.size() + 3 << ". Thoát và tự động trả tiền lại\n";
}
