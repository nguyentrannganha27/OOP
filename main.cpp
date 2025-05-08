#include "Product.h"
#include "Menu.h"
#include "Tien.h"
#include "Order.h"
#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<Product> productList = {
        {"Coca", 10000, 5},
        {"7-Up", 11000, 3},
        {"C2", 12000, 2},
        {"Olong", 15000, 4}
    };

    int option;

    while (true) {
        // Sửa tên hàm thành printCurrentBalance
        printCurrentBalance();  // Đảm bảo tên hàm đúng

        printMenu(productList);

        cout << "\nEnter your choice: ";
        cin >> option;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid choice, please select again.\n";
            continue;
        }

        orderItem(option, productList);
    }

    return 0;
}
