#include "Invoice.h"    // Bao gồm định nghĩa hàm in hóa đơn
#include <iostream>     // Sử dụng cout để xuất thông tin

using namespace std;
extern int balance;      // Biến balance khai báo ở nơi khác, dùng để hiển thị số dư còn lại

// Hàm in chi tiết hóa đơn cho 1 sản phẩm
void printInvoiceDetails(const Product& p, int qty, int totalCost, int discount) {
    int amountPaid = totalCost - discount;  // Tính số tiền thực tế khách phải trả sau khi trừ khuyến mãi

    cout << "\n===== Invoice =====\n";                     // Tiêu đề hóa đơn
    cout << "Product: " << p.name << "\n";                // Tên sản phẩm
    cout << "Quantity: " << qty << "\n";                   // Số lượng mua
    cout << "Price per item: " << p.price << " VND\n";    // Giá mỗi sản phẩm
    cout << "Total cost (before discount): " << totalCost << " VND\n";  // Tổng tiền trước khuyến mãi
    cout << "Discount: " << discount << " VND\n";          // Số tiền được giảm giá
    cout << "Amount paid: " << amountPaid << " VND\n";     // Số tiền khách thực trả
    cout << "Remaining balance: " << balance << " VND\n";  // Số dư còn lại trong máy (nếu có)
    cout << "===================\n";                         // Kết thúc phần hóa đơn
}
