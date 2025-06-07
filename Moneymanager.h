#ifndef MONEYMANAGER_H          // Nếu chưa được định nghĩa MONEYMANAGER_H thì định nghĩa
#define MONEYMANAGER_H          // Định nghĩa hằng bảo vệ tránh include lặp

// Lớp MoneyManager quản lý các thao tác liên quan đến tiền
class MoneyManager {
public:
    static int getMoney();                 // Nhận tiền người dùng đưa vào và cập nhật số dư
    static void returnMoney();            // Trả lại tiền dư cho người dùng
    static void printCurrentBalance();    // In ra số dư hiện tại trong máy
};

// Khai báo biến toàn cục để quản lý số dư và tổng doanh thu
extern int balance;           // Số tiền người dùng hiện có trong máy
extern int totalRevenue;      // Tổng doanh thu thu được từ bán hàng

#endif    // Kết thúc MONEYMANAGER_H
