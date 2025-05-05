#include "Order.h"
#include "Gia.h"
#include "Tien.h"
#include <iostream>
#include <cstdlib>
using namespace std;

void orderItem(int option) {
    if (option >= 1 && option <= 4) {
        if (tien >= gia[option - 1]) {
            tien -= gia[option - 1];
            cout << "\nBạn đã mua thành công!\n";
            cout << "Số dư còn lại: " << tien << " đô\n";
        } else {
            cout << "\nSố dư không đủ! Vui lòng nạp thêm tiền.\n";
        }
    } else if (option == 5) {
        returnMoney();
    } else if (option == 6) {
        getMoney();
    } else if (option == 7) {
        returnMoney();
        cout << "Thoát thành công!\n";
        exit(0);
    } else {
        cout << "\nLựa chọn không hợp lệ! Vui lòng chọn lại.\n";
    }
}

