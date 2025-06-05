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
#include <conio.h>    // _kbhit(), _getch()
#include <windows.h>  // Sleep()

using namespace std;

// Hàm chờ người dùng nhập phím trong khoảng timeoutSeconds giây
// Trả về true nếu có phím bấm, false nếu timeout
bool waitForInputWithTimeout(int timeoutSeconds) {
    time_t start = time(nullptr);
    while (difftime(time(nullptr), start) < timeoutSeconds) {
        if (_kbhit()) {   // Nếu có phím bấm
            _getch();     // Đọc và bỏ qua phím bấm
            return true;  // Người dùng thao tác, không timeout
        }
        Sleep(100); // Nghỉ 100ms tránh chiếm CPU
    }
    return false;  // Timeout không thao tác
}

// Hàm chờ người dùng nhập số nguyên có timeout, trả về true nếu nhập thành công
bool getIntInputWithTimeout(int &input, int timeoutSeconds) {
    time_t start = time(nullptr);
    string buffer;

    cout << "(You have " << timeoutSeconds << " seconds to input): ";
    while (difftime(time(nullptr), start) < timeoutSeconds) {
        if (_kbhit()) {
            char ch = _getch();
            if (ch == '\r') { // Enter
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
            }
            else if (ch == '\b') { // Backspace
                if (!buffer.empty()) {
                    buffer.pop_back();
                    cout << "\b \b";
                }
            }
            else if (isdigit(ch)) {
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
        {"JULY01", 15, 1, 1688160000},
        {"DISCOUNT10", 10, 1, time(nullptr) + 7 * 24 * 3600},
    };

    while (true) {
        cout << "\n==== VENDING MACHINE ====";
        cout << "\n1. View menu and purchase";
        // cout << "\n113. Admin mode";  // đây là giao diện ẩn, cho admin biết
        cout << "\nSelect an option (auto exit after 30s inactivity): ";

        int mainChoice;

        // Ở menu chính, đợi nhập số với timeout 30s
        if (!getIntInputWithTimeout(mainChoice, 30)) {
            cout << "\nNo input for 30 seconds. Machine going offline.\n";
            cout << "Press any key to turn on again...\n";

            // Đợi phím bất kỳ để bật lại
            while (!_kbhit()) {
                Sleep(100);
            }
            _getch(); // Bỏ qua phím bấm

            cout << "Machine is back online.\n";
            continue;  // Quay lại vòng lặp để in menu tiếp
        }

        switch (mainChoice) {
            case 113:
                if (authenticateAdmin()) {
                    showAdminMenu(productList);
                }
                break;

            case 1: {
                // Ở menu con: mỗi lần nhập option cũng có timeout 30s
                while (true) {
                    printMenu(productList);
                    cout << "Enter product option (0 to cancel): ";

                    int option;
                    if (!getIntInputWithTimeout(option, 30)) {
                        cout << "No input for 30 seconds. Returning to main menu...\n";
                        break; // Quay lại menu chính
                    }

                    if (option == 0) break;  // Thoát về menu chính

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
