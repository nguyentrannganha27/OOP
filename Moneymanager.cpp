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
    cout << "\nEnter the amount to insert ( >= 10000):  "; // Yêu cầu nhập số tiền
    cin >> inputAmount;

    // Kiểm tra nhập sai hoặc số tiền nhỏ hơn 10000
    if (cin.fail() || inputAmount < 10000) {
        cin.clear();                                // Xóa cờ lỗi
        cin.ignore(10000, '\n');                    // Bỏ qua dữ liệu lỗi trong buffer
        cout << " Invalid amount, please try again.\n"; // Thông báo lỗi
        return 0;                                   // Không cập nhật số dư
    }

    balance += inputAmount; //  Cộng tiền vào biến toàn cục balance
    cout << " Successfully inserted " << inputAmount << " VND.\n"; // Thông báo thành công
    return balance;         // Trả về số dư mới
}

// Hàm hiển thị số dư hiện tại
void MoneyManager::printCurrentBalance() {
    cout << "\n Current balance: " << balance << " VND\n"; // In ra số dư hiện tại
}

// Hàm trả lại tiền dư cho người dùng
void MoneyManager::returnMoney() {
    if (balance == 0) {
        cout << "  Error: No money to return!\n";       // Không có tiền để trả lại
    } else if (balance < 10000) {
        cout << "Error: no enough for returning condition!!\n"; // Số dư không đủ điều kiện trả lại
    } else {
        cout << "\n Returning: " << balance << " VND\n";        // In số tiền trả lại
        cout << " Change returned successfully.\n";             // Thông báo trả lại thành công
        balance = 0;                                            // Đặt lại số dư về 0
    }
}
