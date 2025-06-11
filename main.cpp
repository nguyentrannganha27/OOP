#include "Product.h"
#include "Menu.h"
#include "Moneymanager.h"
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

// ===== Hàm chờ nhập phím trong một khoảng thời gian =====
bool waitForInputWithTimeout(int timeoutSeconds) {
    time_t start = time(nullptr);
    while (difftime(time(nullptr), start) < timeoutSeconds) {
        if (_kbhit()) {
            _getch();
            return true;
        }
        Sleep(100);  // Giảm tải CPU
    }
    return false;
}

// ===== Hàm nhập số nguyên có giới hạn thời gian =====
bool getIntInputWithTimeout(int& input, int timeoutSeconds) {
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

// ===== Hàm chính =====
int main() {
    // Danh sách sản phẩm mặc định
    vector<Product> productList = {
        {"Coca", 10000, 5},
        {"7-Up", 11000, 3},
        {"C2", 12000, 2},
        {"Olong", 15000, 4}
    };

    // Danh sách mã khuyến mãi mặc định
    vector<PromoCode> promoList = {
        {"DISCOUNT10", 10, 1, time(nullptr) + 7 * 24 * 3600}
    };

    // Vòng lặp chính của máy bán hàng
    while (true) {
        cout << "\n==== VENDING MACHINE ====\n";
        cout << "1. View menu and purchase\n";
        // cout << "113. Admin mode\n";  // Có thể bật nếu cần
        cout << "Select an option (auto exit after 30s inactivity): ";

        int mainChoice;

        // Nếu không nhập trong 30s thì tự tắt
        if (!getIntInputWithTimeout(mainChoice, 30)) {
            cout << "\nNo input for 30 seconds. Machine going offline.\n";
            cout << "Press any key to turn on again...\n";
            while (!_kbhit()) Sleep(100);
            _getch();
            cout << "Machine is back online.\n";
            continue;
        }

        switch (mainChoice) {
            case 113: {  // Chế độ quản trị viên
                Admin admin;
                if (admin.authenticate()) {
                    admin.showMenu(productList, promoList);
                }
                break;
            }

            case 1: {  // Người dùng mua hàng
                while (true) {
                    Menu::printMenu(productList);
                    cout << "Enter product option (0 to cancel): ";

                    int option;
                    if (!getIntInputWithTimeout(option, 30)) {
                        cout << "No input for 30 seconds. Returning to main menu...\n";
                        break;
                    }

                    if (option == 0) {
                        if (balance > 0) {
                            MoneyManager::returnMoney();
                        } else {
                            cout << "No balance to return.\n";
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
}
