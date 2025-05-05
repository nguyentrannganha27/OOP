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
            cout << "\nXin lỗi, " << p.ten << " đã hết hàng.\n";
            return;
        }

        if (tien >= p.gia) {
            tien -= p.gia;
            p.soLuong--;
            cout << "\nBạn đã mua " << p.ten << " thành công!\n";
            cout << "Số dư còn lại: " << tien << " đô\n";
        } else {
            cout << "\nSố dư không đủ! Vui lòng nạp thêm tiền.\n";
        }
    } else if (option == n + 1) {
        returnMoney();
    } else if (option == n + 2) {
        getMoney();
    } else if (option == n + 3) {
        returnMoney();
        cout << "Thoát thành công!\n";
        exit(0);
    } else {
        cout << "\nLựa chọn không hợp lệ! Vui lòng chọn lại.\n";
    }
}
