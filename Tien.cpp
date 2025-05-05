#include "Tien.h"
#include <iostream>
using namespace std;

int tien = 0;  // Biến toàn cục để lưu trữ số tiền

// Hàm nạp tiền
int getMoney() {
    int nhaptien;
    cout << "nhap so tien mun nao vao: ";
    cin >> nhaptien;

    if (cin.fail() || nhaptien <= 0) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "so tien khong hop le, vui long chon lai.\n";
        return 0;
    }

    tien += nhaptien;
    cout << "ban da nap thanh cong" << nhaptien << " do" << endl;
    return tien;
}

// Hàm in số dư hiện tại
void printCurrentMoney() {
    cout << "\nso du hien tai la:  " << tien << " do\n";
}

// Hàm trả lại tiền
void returnMoney() {
    cout << "\nso tien tra lai la:  " << tien << " đo\n";
    cout << "Tra tien lai thanh cong!\n";
    tien = 0;  // Đặt lại số tiền sau khi trả
}
