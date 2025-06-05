#ifndef TIEN_H       // Nếu chưa định nghĩa TIEN_H thì tiếp tục
#define TIEN_H       // Định nghĩa TIEN_H để tránh include nhiều lần

extern int totalRevenue;  // Biến toàn cục lưu tổng doanh thu hiện tại
extern int balance;       // Biến toàn cục lưu số tiền còn lại trong máy

// Hàm nhập tiền từ người dùng
int getMoney();

// Hàm in ra số dư hiện tại trong máy
void printCurrentBalance();

// Hàm trả lại tiền thừa cho người dùng
void returnMoney();

#endif // Kết thúc phần định nghĩa TIEN_H
