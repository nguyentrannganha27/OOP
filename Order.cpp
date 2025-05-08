#include "Order.h"
#include "Tien.h"
#include "Product.h"
#include <iostream>
#include <vector>
#include <limits>
#include <cstdlib>
using namespace std;

// Updated to allow quantity selection when purchasing
void orderItem(int option, vector<Product>& productList) {
    int n = productList.size();
    if (option >= 1 && option <= n) {
        Product& p = productList[option - 1];

        if (p.quantity <= 0) {
            cout << "\nSorry, " << p.name << " is out of stock.\n";
            return;
        }

        int qty;
        cout << "Enter quantity to purchase: ";
        cin >> qty;
        if (cin.fail() || qty <= 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << " Invalid quantity, please try again.\n";
            return;
        }
        if (qty > p.quantity) {
            cout << " Sorry, only " << p.quantity << " " << p.name << " left in stock.\n";
            return;
        }

        int cost = qty * p.price;
        if (balance >= cost) {
            balance -= cost;
            p.quantity -= qty;
            cout << "\n Purchase successful: " << qty << " x " << p.name << "\n";
            cout << " Remaining balance: " << balance << " VND\n";
        } else {
            cout << "\n Insufficient balance. You need " << (cost - balance) << " more VND.\n";
        }
    } else if (option == n + 1) {
        returnMoney();
    } else if (option == n + 2) {
        getMoney();
    } else {
        cout << "\n Invalid choice. Please try again.\n";
    }
}
