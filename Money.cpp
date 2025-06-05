#include "Money.h"   // include header định nghĩa hàm và biến
#include <iostream>
using namespace std;

// Khai báo và khởi tạo biến toàn cục lưu tổng doanh thu và số dư hiện tại
int totalRevenue = 0; 
int balance = 0;  

// Hàm nhập tiền vào máy
int getMoney() {
    int inputAmount;
    cout << "\nEnter the amount to insert ( >= 10000):  ";
    cin >> inputAmount;

    // Kiểm tra nhập liệu có hợp lệ và số tiền >= 10,000 không
    if (cin.fail() || inputAmount < 10000) {
        cin.clear();                       // Xóa trạng thái lỗi của cin
        cin.ignore(10000, '\n');           // Xóa bộ đệm nhập
        cout << " Invalid amount, please try again.\n";
        return 0;                         // Trả về 0 nếu nhập không hợp lệ
    }

    balance += inputAmount;               // Cộng thêm tiền vào số dư hiện tại
    cout << " Successfully inserted " << inputAmount << " VND.\n";
    return balance;                      // Trả về số dư mới
}

// Hàm in ra số dư hiện tại
void printCurrentBalance() {
    cout << "\n Current balance: " << balance << " VND\n";
}

// Hàm trả lại tiền thừa cho người dùng
void returnMoney() {
    if (balance == 0) {
        cout << "  Error: No money to return!\n";   // Không có tiền để trả lại
    } else if (balance < 1000) {
        cout << "Error: no enough for returning conditon!!" << "\n"; // Tiền quá nhỏ không thể trả
    } else {
        cout << "\n Returning: " << balance << " VND\n";
        cout << " Change returned successfully.\n";
        balance = 0;  // Reset số dư sau khi trả tiền
    }
}
