#include "Product.h"
#include "Menu.h"
#include "Tien.h"
#include "Order.h"
#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<Product> dsSanPham = {
        {"Chó", 12, 5},
        {"Mèo", 14, 3},
        {"Gà", 87, 2},
        {"Dê", 45, 4}
    };

    int option;

    while (true) {
        printCurrentMoney();
        printMenu(dsSanPham);
        cout << "\nNhập lựa chọn của bạn: ";
        cin >> option;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Lựa chọn không hợp lệ! Vui lòng nhập lại.\n";
            continue;
        }

        orderItem(option, dsSanPham);
    }

    return 0;
}
