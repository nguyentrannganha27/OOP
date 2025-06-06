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
#include <conio.h>
#include <windows.h>

using namespace std;

bool waitForInputWithTimeout(int timeoutSeconds) {
    time_t start = time(nullptr);
    while (difftime(time(nullptr), start) < timeoutSeconds) {
        if (_kbhit()) {
            _getch();
            return true;
        }
        Sleep(100);
    }
    return false;
}

bool getIntInputWithTimeout(int &input, int timeoutSeconds) {
    time_t start = time(nullptr);
    string buffer;

    cout << "(You have " << timeoutSeconds << " seconds to input): ";
    while (difftime(time(nullptr), start) < timeoutSeconds) {
        if (_kbhit()) {
            char ch = _getch();

            if (ch == '\r') {
                if (!buffer.empty()) {
                    try {
                        input = stoi(buffer);
                        cout << endl;
                        return true;
                    } catch (...) {
                        cout << "\nInvalid number format, try again.\n";
                        buffer.clear();
                        cout << "(You have " << timeoutSeconds << " seconds to input): ";
                    }
                }
            } else if (ch == '\b') {
                if (!buffer.empty()) {
                    buffer.pop_back();
                    cout << "\b \b";
                }
            } else if (isdigit(ch)) {
                buffer.push_back(ch);
                cout << ch;
            }
        }
        Sleep(50);
    }

    cout << "\nTimeout! No input detected.\n";
    return false;
}

int main() {
    vector<Product> productList = {
        {"Coca", 10000, 5},
        {"7-Up", 11000, 3},
        {"C2", 12000, 2},
        {"Olong", 15000, 4}
    };

    vector<PromoCode> promoList = {
        {"DISCOUNT10", 10, 1, time(nullptr) + 7 * 24 * 3600}
    };

    while (true) {
        cout << "\n==== VENDING MACHINE ====";
        cout << "\n1. View menu and purchase";
        // cout << "\n113. Admin mode";
        cout << "\nSelect an option (auto exit after 30s inactivity): ";

        int mainChoice;

        if (!getIntInputWithTimeout(mainChoice, 30)) {
            cout << "\nNo input for 30 seconds. Machine going offline.\n";
            cout << "Press any key to turn on again...\n";
            while (!_kbhit()) {
                Sleep(100);
            }
            _getch();
            cout << "Machine is back online.\n";
            continue;
        }

        switch (mainChoice) {
            case 113:
                if (authenticateAdmin()) {
                    showAdminMenu(productList, promoList);
                }
                break;

            case 1: {
                while (true) {
                    printMenu(productList);
                    cout << "Enter product option (0 to cancel): ";

                    int option;
                    if (!getIntInputWithTimeout(option, 30)) {
                        cout << "No input for 30 seconds. Returning to main menu...\n";
                        break;
                    }

                    if (option == 0) {
                        if (balance >= 10000) {
                            returnMoney();
                            cout << "Refunded to the user.\n";
                        } else {
                            totalRevenue += balance;
                            cout << "Balance is considered as revenue: " << balance << " VND\n";
                            balance = 0;
                        }
                        break;
                    }

                    orderItem(option, productList, promoList);
                }
                break;
            }

            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
