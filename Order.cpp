#include "Order.h"        // File header khai báo hàm orderItem
#include "Money.h"        // Quản lý tiền, biến balance, hàm getMoney, returnMoney
#include "Product.h"      // Định nghĩa struct/class Product
#include "Promotion.h"    // Định nghĩa struct/class PromoCode
#include "Invoice.h"      // Hàm in hóa đơn
#include <iostream>       // In xuất ra màn hình, nhập từ bàn phím
#include <vector>         // Dùng vector lưu danh sách sản phẩm, mã giảm giá
#include <limits>         // numeric_limits dùng cho xử lý input lỗi
#include <ctime>          // (Không dùng trong đoạn này, có thể bỏ)
extern int totalRevenue;  // Biến tổng doanh thu toàn cục khai báo ở file khác
extern int balance;       // Biến số dư tài khoản (tiền người dùng nạp)

using namespace std;      // Sử dụng namespace chuẩn

// Hàm xử lý đặt hàng, mua sản phẩm
// option: lựa chọn sản phẩm hoặc thao tác khác
// productList: danh sách sản phẩm
// promoList: danh sách mã giảm giá
void orderItem(int option, std::vector<Product>& productList, std::vector<PromoCode>& promoList) {
    int n = productList.size();  // Lấy số lượng sản phẩm hiện có

    // Nếu lựa chọn trong phạm vi danh sách sản phẩm
    if (option >= 1 && option <= n) {
        Product& p = productList[option - 1];  // Lấy tham chiếu sản phẩm chọn

        // Kiểm tra sản phẩm còn hàng không
        if (p.quantity <= 0) {
            cout << "\nSorry, " << p.name << " is out of stock.\n";
            return; // Thoát hàm nếu hết hàng
        }

        // Kiểm tra số dư tài khoản người dùng có đủ không
        if (balance <= 0) {
            cout << "\nSorry, you do not have enough balance to make a purchase.\n";
            return; // Thoát nếu không đủ tiền
        }

        cout << "\nCurrent balance: " << balance << " VND\n";  // Hiện số dư

        int qty;
        cout << "Enter quantity to purchase: ";  // Yêu cầu nhập số lượng muốn mua
        cin >> qty;

        // Xử lý lỗi nhập liệu: nếu nhập sai hoặc <=0
        if (cin.fail() || qty <= 0) {
            cin.clear(); // Xóa lỗi
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Bỏ qua dòng nhập lỗi
            cout << "Invalid quantity, please try again.\n";
            return; // Thoát
        }

        // Kiểm tra số lượng nhập có vượt quá tồn kho không
        if (qty > p.quantity) {
            cout << "Sorry, only " << p.quantity << " " << p.name << " left in stock.\n";
            return; // Thoát nếu không đủ hàng
        }

        int cost = qty * p.price;   // Tính tổng tiền chưa giảm giá
        int discount = 0;           // Khởi tạo biến giảm giá

        char hasPromo;              // Biến lưu lựa chọn có mã giảm giá không
        int time_1 = 3;             // Số lần thử nhập mã giảm giá tối đa

        // Vòng lặp hỏi nhập mã khuyến mãi
        while (true)
        {
            cout << "Do you have a promo code? (1 for yes / 2 for no): ";
            cin >> hasPromo;
            time_1 -= 1; // Giảm số lần thử nhập

            if (hasPromo == '1') {  // Nếu chọn nhập mã
                string inputCode;
                cout << "Enter promo code: ";
                cin >> inputCode;

                bool promoApplied = false;  // Biến kiểm tra mã hợp lệ

                // Duyệt qua danh sách mã khuyến mãi
                for (PromoCode& promo : promoList) {
                    // Nếu mã nhập đúng và còn hiệu lực
                    if (promo.code == inputCode && promo.isValid()) {
                        discount = (cost * promo.discountPercent) / 100; // Tính tiền giảm
                        promo.remainingUses--;  // Giảm số lần sử dụng còn lại của mã
                        cout << "Promo code applied! Discount: " << discount << " VND\n";
                        promoApplied = true;
                        break;  // Thoát vòng for
                    }
                }
                if (!promoApplied) {
                    cout << "Invalid or expired promo code.\n"; // Mã không hợp lệ
                }
                break; // Thoát vòng while dù có mã hợp lệ hay không
            }
            else if (hasPromo == '2') {  // Không nhập mã, thoát vòng while
                break;
            }
            else {  // Nhập sai lựa chọn
                if (time_1 == 0) {
                    cout <<"No promo code selected due to wrong selection 3 times"<< endl;
                    break; // Quá 3 lần nhập sai, thoát
                }
                cout << "Try again!!" << endl; // Yêu cầu nhập lại
            }
        }

        int finalCost = cost - discount;  // Tính tổng tiền phải trả sau giảm giá

        // Nếu số dư đủ để thanh toán
        if (balance >= finalCost) {
            balance -= finalCost;      // Trừ tiền trong tài khoản
            totalRevenue += finalCost; // Cộng tiền vào tổng doanh thu
            p.quantity -= qty;         // Giảm tồn kho sản phẩm

            cout << "\nPurchase successful: " << qty << " x " << p.name << "\n";
            cout << "Discount applied: " << discount << " VND\n";
            cout << "Remaining balance: " << balance << " VND\n";

            char printInvoice;
            int time = 3;  // Số lần thử hỏi in hóa đơn

            // Vòng lặp hỏi in hóa đơn
            while (true)
            {
                time -=1;  // Giảm số lần thử nhập

                cout << "Do you want to print the invoice? (1 for y/ 2 for n): ";
                cin >> printInvoice;

                if (printInvoice == '1') {  // In hóa đơn
                    printInvoiceDetails(p, qty, cost, discount);
                    break;
                }
                else if(printInvoice == '2') { // Không in hóa đơn, thoát vòng
                    break;
                }
                else {  // Nhập sai
                    if (time == 0) {
                        cout << "Invoice not printed due to wrong selection 3 times" << endl;
                        break;  // Quá 3 lần nhập sai thì thôi
                    }
                    cout <<"Try againnn!!"<< endl;
                }
            }
        } else {
            // Số dư không đủ, báo cho người dùng biết cần thêm bao nhiêu tiền
            cout << "\nInsufficient balance. You need " << (finalCost - balance) << " more VND.\n";
        }
    }
    // Nếu chọn option = n+1, thực hiện trả tiền thừa
    else if (option == n + 1) {
        returnMoney();
    }
    // Nếu chọn option = n+2, thực hiện nạp thêm tiền
    else if (option == n + 2) {
        getMoney();
    }
    else {  // Lựa chọn không hợp lệ
        cout << "\nInvalid choice. Please try again.\n";
    }
}
