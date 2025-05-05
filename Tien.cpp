#include "Tien.h"
#include <iostream>
using namespace std;

int tien = 0;  // Biến toàn cục để lưu trữ số tiền

// Hàm nạp tiền
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
    cout << "Bạn đã nạp thành công " << nhaptien << " đô!" << endl;
    return tien;
}

// Hàm in số dư hiện tại
void printCurrentMoney() {
    cout << "\nSố dư hiện tại của bạn là: " << tien << " đô\n";
}

// Hàm trả lại tiền
void returnMoney() {
    cout << "\nSố tiền trả lại là: " << tien << " đô\n";
    cout << "Trả lại tiền thành công!\n";
    tien = 0;  // Đặt lại số tiền sau khi trả
}
