#include "Product.h"
#include "Menu.h"
#include "Money.h"
#include "Order.h"
#include "Promotion.h"
#include "Invoice.h"
#include "Admin.h"  
#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <ctime>
using namespace std;
int main() {
    vector<Product> productList = {
        {"Coca", 10000, 5},
        {"7-Up", 11000, 3},
        {"C2", 12000, 2},
        {"Olong", 15000, 4}
    };
    vector<PromoCode> promoList = {
        {"JULY01", 15, 1, 1688160000},
        {"DISCOUNT10", 10, 1, time(nullptr) + 7 * 24 * 3600},
    };
while (true) {
    cout << "\n==== VENDING MACHINE ====";
    cout << "\n1. View menu and purchase";
    cout << "\n2. Admin mode";
    cout << "\nSelect an option: ";
    
    int mainChoice;
    cin >> mainChoice;

    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input! Please enter a number.\n";
        continue;
    }

    switch (mainChoice) {
        case 2:
            if (authenticateAdmin()) {
                showAdminMenu(productList);
            }
            break;
        case 1: {
            while (true) {
                printMenu(productList);
                cout << "Enter product option (0 to cancel): ";
                int option;
                cin >> option;
                
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid input! Please enter a number.\n";
                    continue;
                }
                
                if (option == 0) break;  // Thoát về menu chính
                
                orderItem(option, productList, promoList);
            }
            break;
        }
        default:
            cout << "Invalid choice. Please try again.\n";
    }
}}