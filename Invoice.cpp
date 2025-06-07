#include "Invoice.h"    // Bao gồm định nghĩa hàm in hóa đơn từ file Invoice.h
#include <iostream>     // Thư viện dùng để xuất dữ liệu ra màn hình bằng cout

using namespace std;

extern int balance;      // Biến toàn cục đại diện cho số dư còn lại sau giao dịch (khai báo ở nơi khác)
extern int totalRevenue; // Biến toàn cục lưu tổng doanh thu (khai báo ở nơi khác)

// Hàm in chi tiết hóa đơn cho 1 sản phẩm sau khi mua
void Invoice::printInvoiceDetails(const Product& p, int qty, int totalCost, int discount) {
    int amountPaid = totalCost - discount;  // Tính số tiền khách thực phải trả sau khi trừ khuyến mãi

    cout << "\n===== Invoice =====\n";                           // In tiêu đề hóa đơn
    cout << "Product: " << p.name << "\n";                      // In tên sản phẩm
    cout << "Quantity: " << qty << "\n";                        // In số lượng mua
    cout << "Price per item: " << p.price << " VND\n";          // In giá của từng món hàng
    cout << "Total cost (before discount): " << totalCost << " VND\n";  // In tổng giá trị trước khi giảm giá
    cout << "Discount: " << discount << " VND\n";               // In số tiền được giảm giá
    cout << "Amount paid: " << amountPaid << " VND\n";          // In số tiền khách phải thanh toán
    cout << "Remaining balance: " << balance << " VND\n";       // In số dư tiền trong máy (sau giao dịch)
    cout << "===================\n";                            // In đường phân cách cuối hóa đơn
}
