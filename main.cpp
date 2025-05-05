#include "Gia.h"
#include "Tien.h"
#include "Menu.h"
#include "Order.h"
#include <iostream>
using namespace std;

int main() {
    int option;

    while (true) {
        printCurrentMoney();
        printMenu();
        cout << "\nNhập lựa chọn của bạn: ";
        cin >> option;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Lựa chọn không hợp lệ! Vui lòng nhập lại.\n";
            continue;
        }

        orderItem(option);
    }

    return 0;
}
