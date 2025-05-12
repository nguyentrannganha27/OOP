#include "Order.h"
#include "Money.h"
#include "Product.h"
#include "Promotion.h"
#include "Invoice.h"
#include <iostream>
#include <vector>
#include <limits>
#include <ctime>
extern int totalRevenue;
using namespace std;

void orderItem(int option, std::vector<Product>& productList, std::vector<PromoCode>& promoList) {
    int n = productList.size();
    if (option >= 1 && option <= n) {
        Product& p = productList[option - 1];

        // Kiểm tra nếu sản phẩm hết hàng
        if (p.quantity <= 0) {
            cout << "\nSorry, " << p.name << " is out of stock.\n";
            return;
        }

        // Kiểm tra nếu số dư tài khoản không đủ
        if (balance <= 0) {
            cout << "\nSorry, you do not have enough balance to make a purchase.\n";
            return;
        }

        // Hiển thị số dư hiện tại trước khi mua
        cout << "\nCurrent balance: " << balance << " VND\n";

        int qty;
        cout << "Enter quantity to purchase: ";
        cin >> qty;

        // Kiểm tra số lượng nhập vào
        if (cin.fail() || qty <= 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << " Invalid quantity, please try again.\n";
            return;
        }

        // Kiểm tra số lượng có trong kho
        if (qty > p.quantity) {
            cout << " Sorry, only " << p.quantity << " " << p.name << " left in stock.\n";
            return;
        }

        int cost = qty * p.price;  // Tính tổng giá trị
        int discount = 0;          // Khởi tạo giá trị khuyến mãi

        // Kiểm tra mã khuyến mãi
        char hasPromo;
        cout << "Do you have a promo code? (y/n): ";
        cin >> hasPromo;

        if (hasPromo == 'y' || hasPromo == 'Y') {
            string inputCode;
            cout << "Enter promo code: ";
            cin >> inputCode;

            // Kiểm tra mã khuyến mãi
            for (PromoCode& promo : promoList) {
                if (promo.code == inputCode && promo.isValid()) {
                    discount = (cost * promo.discountPercent) / 100;
                    promo.remainingUses--;  // Giảm số lượng voucher còn lại
                    cout << "Promo code applied! Discount: " << discount << " VND\n";
                    break;
                }
            }

            if (discount == 0) {
                cout << "Invalid or expired promo code.\n";
            }
        }

        int finalCost = cost - discount;  // Tính tổng số tiền cần thanh toán sau khi áp dụng khuyến mãi

        if (balance >= finalCost) {
            balance -= finalCost;  // Cập nhật số dư sau khi thanh toán
            totalRevenue += finalCost;
            p.quantity -= qty;  // Cập nhật số lượng sản phẩm trong kho
            cout << "\n Purchase successful: " << qty << " x " << p.name << "\n";
            cout << " Discount applied: " << discount << " VND\n";
            cout << " Remaining balance: " << balance << " VND\n";

            // Hỏi người dùng có muốn in hóa đơn không
            char printInvoice;
            cout << "Do you want to print the invoice? (y/n): ";
            cin >> printInvoice;

            if (printInvoice == 'y' || printInvoice == 'Y') {
                printInvoiceDetails(p, qty, cost, discount);  // Gọi hàm in hóa đơn từ Invoice.cpp
            }
        } else {
            cout << "\n Insufficient balance. You need " << (finalCost - balance) << " more VND.\n";
        }
    } else if (option == n + 1) {
        returnMoney();  // Hoàn tiền nếu chọn mục này
    } else if (option == n + 2) {
        getMoney();  // Thêm tiền vào tài khoản nếu chọn mục này
    }
    else {
        cout << "\n Invalid choice. Please try again.\n";
    }
}