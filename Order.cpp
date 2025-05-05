#include "Order.h"
#include "Tien.h"
#include <iostream>

using namespace std;

void orderItem(int option, vector<Product>& dsSanPham) {
    int n = dsSanPham.size();
    if (option >= 1 && option <= n) {
        Product& p = dsSanPham[option - 1];

        // Kiểm tra số lượng sản phẩm
        if (p.soLuong <= 0) {
            cout << "\nXin lỗi, " << p.ten << " đã hết hàng.\n";
            return;
        }

        // Kiểm tra tiền còn lại và thực hiện mua
        if (tien >= p.gia) {
            tien -= p.gia;
            p.soLuong--;  // Giảm số lượng sản phẩm
            cout << "\nBạn đã mua " << p.ten << " thành công!\n";
            cout << "Số dư còn lại: " << tien << " đô\n";
        } else {
            cout << "\nSố dư không đủ! Vui lòng nạp thêm tiền.\n";
        }
    } else if (option == n + 1) {
        // Trả lại tiền
        returnMoney();
    } else if (option == n + 2) {
        // Nạp thêm tiền
        getMoney();
    } else if (option == n + 3) {
        // Thoát chương trình và tự động trả lại tiền
        returnMoney();
        cout << "Thoát thành công!\n";
        return;  // Thay vì exit(0), dùng return để kết thúc chương trình
    } else {
        cout << "\nLựa chọn không hợp lệ! Vui lòng chọn lại.\n";
    }
}
