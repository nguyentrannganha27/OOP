#include "Order.h"              // File header khai báo hàm orderItem
#include "Moneymanager.h"       // Quản lý tiền: balance, getMoney, returnMoney
#include "Product.h"            // Định nghĩa lớp Product
#include "Promotion.h"          // Định nghĩa lớp PromoCode
#include "Invoice.h"            // Hàm in hóa đơn
#include <iostream>             // Sử dụng cin, cout
#include <vector>               // Dùng vector để lưu danh sách
#include <limits>               // Dùng numeric_limits để xử lý lỗi nhập liệu
#include <ctime>                // Không sử dụng, có thể bỏ nếu cần

extern int totalRevenue;        // Tổng doanh thu (khai báo ở nơi khác)
extern int balance;             // Biến toàn cục lưu số dư tài khoản

using namespace std;            // Sử dụng không gian tên chuẩn

// Hàm xử lý đặt hàng, mua sản phẩm
void orderItem(int option, std::vector<Product>& productList, std::vector<PromoCode>& promoList) {
    int n = productList.size();  // Lấy số lượng sản phẩm hiện có

    // Nếu lựa chọn là một sản phẩm hợp lệ
    if (option >= 1 && option <= n) {
        Product& p = productList[option - 1];  // Lấy sản phẩm tương ứng

        // Kiểm tra hàng còn không
        if (p.quantity <= 0) {
            cout << "\nSorry, " << p.name << " is out of stock.\n";
            return;
        }

        // Kiểm tra người dùng đã nạp tiền chưa
        if (balance <= 0) {
            cout << "\nSorry, you do not have enough balance to make a purchase.\n";
            return;
        }

        cout << "\nCurrent balance: " << balance << " VND\n";

        int qty;
        cout << "Enter quantity to purchase: ";
        cin >> qty;

        // Xử lý nhập lỗi hoặc số lượng không hợp lệ
        if (cin.fail() || qty <= 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid quantity, please try again.\n";
            return;
        }

        // Kiểm tra số lượng tồn kho
        if (qty > p.quantity) {
            cout << "Sorry, only " << p.quantity << " " << p.name << " left in stock.\n";
            return;
        }

        int cost = qty * p.price;    // Tổng chi phí gốc
        int discount = 0;            // Mặc định không giảm giá

        char hasPromo;               // Người dùng có mã khuyến mãi không
        int time_1 = 3;              // Số lần thử nhập mã khuyến mãi

        while (true) {
            cout << "Do you have a promo code? (1 for yes / 2 for no): ";
            cin >> hasPromo;
            time_1--;

            if (hasPromo == '1') {
                string inputCode;
                cout << "Enter promo code: ";
                cin >> inputCode;

                bool promoApplied = false;

                for (PromoCode& promo : promoList) {
                    if (promo.code == inputCode && promo.isValid()) {
                        discount = (cost * promo.discountPercent) / 100;
                        promo.remainingUses--;
                        cout << "Promo code applied! Discount: " << discount << " VND\n";
                        promoApplied = true;
                        break;
                    }
                }

                if (!promoApplied) {
                    cout << "Invalid or expired promo code.\n";
                }

                break;
            } else if (hasPromo == '2') {
                break;
            } else {
                if (time_1 == 0) {
                    cout << "No promo code selected due to wrong selection 3 times" << endl;
                    break;
                }
                cout << "Try again!!" << endl;
            }
        }

        int finalCost = cost - discount;

        if (balance >= finalCost) {
            balance -= finalCost;
            totalRevenue += finalCost;
            p.quantity -= qty;

            cout << "\nPurchase successful: " << qty << " x " << p.name << "\n";
            cout << "Discount applied: " << discount << " VND\n";
            cout << "Remaining balance: " << balance << " VND\n";

            char printInvoice;
            int time = 3;

            while (true) {
                time--;
                cout << "Do you want to print the invoice? (1 for y/ 2 for n): ";
                cin >> printInvoice;

                if (printInvoice == '1') {
                    Invoice::printInvoiceDetails(p, qty, cost, discount);
                    break;
                } else if (printInvoice == '2') {
                    break;
                } else {
                    if (time == 0) {
                        cout << "Invoice not printed due to wrong selection 3 times" << endl;
                        break;
                    }
                    cout << "Try againnn!!" << endl;
                }
            }
        } else {
            cout << "\nInsufficient balance. You need " << (finalCost - balance) << " more VND.\n";
        }
    }
    // Trường hợp người dùng chọn "trả lại tiền"
    else if (option == n + 1) {
        MoneyManager::returnMoney();
    }
    // Trường hợp người dùng chọn "nạp thêm tiền"
    else if (option == n + 2) {
        MoneyManager::getMoney();
    }
    // Lựa chọn không hợp lệ
    else {
        cout << "\nInvalid choice. Please try again.\n";
    }
}
