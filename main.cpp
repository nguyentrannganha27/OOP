#include "Product.h"
#include "Menu.h"
#include "Tien.h"
#include "Order.h"
#include "Promotion.h"
#include "Invoice.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <ctime>

using namespace std;

int main() {
    // Sample products
    vector<Product> productList = {
        {"Coca", 10000, 5},
        {"7-Up", 11000, 3},
        {"C2", 12000, 2},
        {"Olong", 15000, 4}
    };

    // Sample promo codes
    vector<PromoCode> promoList = {
        {"JULY01", 15, 1, 1688160000},  // Expired: 1/7/2023
        {"DISCOUNT10", 10, 1, time(nullptr) + 7 * 24 * 3600},  // Valid: 7 days from now
        // {"SALE20", 20, 2, 1746048000}  // Valid: 1/7/2025
    };

    int option;

    while (true) {
        printCurrentBalance();  // Show current balance

        printMenu(productList);  // Show product menu

        cout << "\nEnter your choice: ";
        cin >> option;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid choice, please select again.\n";
            continue;
        }

        if (option == productList.size() + 1) {
            returnMoney();  // Return money if chosen
        } else if (option == productList.size() + 2) {
            getMoney();  // Add money to account if chosen
        } else if (option >= 1 && option <= productList.size()) {
            orderItem(option, productList, promoList);  // Handle the order
        } else {
            cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
