#include "Order.h"
#include "Tien.h"
#include <iostream>
#include <cstdlib>
using namespace std;

// Bỏ const ở đây
void orderItem(int option, vector<Product>& dsSanPham) {
    int n = dsSanPham.size();
    if (option >= 1 && option <= n) {
        Product& p = dsSanPham[option - 1];

        if (p.soLuong <= 0) {
            cout << "\nxin loi, " << p.ten << " da het hang\n";
            return;
        }

        if (tien >= p.gia) {
            tien -= p.gia;
            p.soLuong--;
            cout << "\nban da muua " << p.ten << " thanh cong!\n";
            cout << "so du con lai: " << tien << " đô\n";
        } else {
            cout << "\nso du khong du, vui long nap them\n";
        }
    } else if (option == n + 1) {
        returnMoney();
    } else if (option == n + 2) {
        getMoney();
    } else if (option == n + 3) {
        returnMoney();
        cout << "thoat thanh cong!\n";
        exit(0);
    } else {
        cout << "\nlua chon khong hop le, chon lai\n";
    }
}
