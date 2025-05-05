#include "Tien.h"
#include <iostream>
using namespace std;

int tien = 0;

int getMoney() {
    int nhaptien;
    cout << "Nhập số tiền bạn muốn nạp vào: ";
    cin >> nhaptien;

    if (cin.fail() || nhaptien <= 0) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Số tiền không hợp lệ! Vui lòng nhập lại.\n";
        return 0;
    }

    tien += nhaptien;
    cout << "Bạn đã nạp thành công " << nhaptien << " đô!\n";
    return tien;
}

void printCurrentMoney() {
    cout << "\nSố dư hiện tại của bạn là: " << tien << " đô\n";
}

void returnMoney() {
    cout << "\nSố tiền trả lại là: " << tien << " đô\n";
    cout << "Trả lại tiền thành công!\n";
    tien = 0;
}
