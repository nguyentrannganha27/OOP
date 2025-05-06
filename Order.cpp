#include "Order.h"
#include "Tien.h"
#include "Product.h"
#include <iostream>
#include <vector>
#include <limits>
#include <cstdlib>
using namespace std;

// Cập nhật để cho phép nhập số lượng muốn mua
void orderItem(int option, vector<Product>& dsSanPham) {
    int n = dsSanPham.size();
    if (option >= 1 && option <= n) {
        Product& p = dsSanPham[option - 1];

        if (p.soLuong <= 0) {
            cout << "\nxin loi, " << p.ten << " da het hang\n";
            return;
        }

        int qty;
        cout << "Nhap so luong muon mua: ";
        cin >> qty;
        if (cin.fail() || qty <= 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "So luong khong hop le, vui long thu lai.\n";
            return;
        }
        if (qty > p.soLuong) {
            cout << "Xin loi, chi con " << p.soLuong << " " << p.ten << " trong kho.\n";
            return;
        }

        int cost = qty * p.gia;
        if (tien >= cost) {
            tien -= cost;
            p.soLuong -= qty;
            cout << "\nBan da mua " << qty << " " << p.ten << " thanh cong!\n";
            cout << "So du con lai: " << tien << " do\n";
        } else {
            cout << "\nSo du khong du. Ban can nap them " << (cost - tien) << " do.\n";
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
