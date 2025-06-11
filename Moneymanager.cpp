#include "Moneymanager.h"     // Bao gồm định nghĩa lớp MoneyManager
#include <iostream>           // Thư viện cho cin, cout
using namespace std;

// Định nghĩa đúng biến toàn cục
int balance = 0;              // Biến toàn cục lưu trữ số dư hiện tại
int totalRevenue = 0;         // Biến toàn cục lưu trữ tổng doanh thu

//  Không cần khai báo static trong cpp này nữa

// Hàm nhận tiền từ người dùng và cập nhật số dư
int MoneyManager::getMoney() {
    int inputAmount;
    cout << "\nEnter the amount to insert (>= 10000 and divisible by 1000): ";
    cin >> inputAmount;

    // Kiểm tra lỗi nhập, số tiền < 10000 hoặc không chia hết cho 1000
    if (cin.fail() || inputAmount < 10000 || inputAmount % 1000 != 0) {
        cin.clear();                               // Xóa cờ lỗi nhập
        cin.ignore(10000, '\n');                   // Bỏ qua dữ liệu lỗi
        cout << " Invalid amount, must be >= 10000 and divisible by 1000. Please try again.\n";
        return 0;
    }

    balance += inputAmount; // Cộng tiền vào biến toàn cục balance
    cout << " Successfully inserted " << inputAmount << " VND.\n";
    return balance;
}



// Hàm hiển thị số dư hiện tại
void MoneyManager::printCurrentBalance() {
    cout << "\n Current balance: " << balance << " VND\n"; // In ra số dư hiện tại
}

// Hàm trả lại tiền dư cho người dùng
void MoneyManager::returnMoney() {
    if (balance == 0) {
        cout << "  Error: No money to return!\n"; // Không có tiền để trả lại
    } else {
        int returned = (balance / 1000) * 1000; // Phần tiền chẵn được trả lại
        int lost = balance % 1000;             // Phần tiền lẻ bị nuốt

        cout << "\n Returning: " << returned << " VND\n";
        if (lost > 0) {
            cout << " Note: " << lost << " VND was not returned and has been kept by the machine.\n";
            totalRevenue += lost; //  Cộng phần tiền lẻ vào doanh thu
        }
        cout << " Change returned successfully.\n";
        balance = 0;
    }
}


