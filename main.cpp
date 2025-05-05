#include "Product.h"
#include "Menu.h"
#include "Tien.h"
#include "Order.h"
#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<Product> dsSanPham = {
        {"coca", 12, 5},
        {"7-up", 14, 3},
        {"C2", 87, 2},
        {"o long", 45, 4}
    };

    int option;

    while (true) {
        printCurrentMoney();
        printMenu(dsSanPham);
        cout << "\nnhap lua chon cua ban: ";
        cin >> option;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "lua chon khong hop le, vui long chon lai.\n";
            continue;
        }

        orderItem(option, dsSanPham);
    }

    return 0;
}
