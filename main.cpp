#include "Product.h"
#include "Menu.h"
#include "Money.h"
#include "Order.h"
#include "Promotion.h"
#include "Invoice.h"
#include "Admin.h"  
#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <ctime>
#include <conio.h>    // Dùng cho _kbhit(), _getch()
#include <windows.h>  // Dùng cho Sleep()

using namespace std;

// Hàm chờ người dùng nhập phím trong khoảng thời gian timeoutSeconds (giây)
// Nếu trong khoảng thời gian này có phím bấm thì trả về true,
// nếu không có phím bấm (timeout) thì trả về false
bool waitForInputWithTimeout(int timeoutSeconds) {
    time_t start = time(nullptr);  // Lấy thời gian bắt đầu
    while (difftime(time(nullptr), start) < timeoutSeconds) {  // vòng lặp chờ trong khoảng timeout
        if (_kbhit()) {   // Kiểm tra xem có phím bấm không
            _getch();     // Đọc phím bấm rồi bỏ qua (không hiển thị)
            return true;  // Có thao tác, trả về true
        }
        Sleep(100); // Nghỉ 100ms tránh dùng CPU quá nhiều
    }
    return false;  // Hết timeout, không có phím bấm => false
}

// Hàm nhập số nguyên từ người dùng có giới hạn thời gian timeoutSeconds (giây)
// Trả về true nếu người dùng nhập số thành công trong thời gian, false nếu timeout
bool getIntInputWithTimeout(int &input, int timeoutSeconds) {
    time_t start = time(nullptr);
    string buffer;  // Buffer lưu chuỗi ký tự nhập vào

    cout << "(You have " << timeoutSeconds << " seconds to input): ";
    while (difftime(time(nullptr), start) < timeoutSeconds) {
        if (_kbhit()) {  // Nếu có phím bấm
            char ch = _getch();  // Đọc ký tự

            if (ch == '\r') { // Phím Enter
                if (!buffer.empty()) {  // Nếu buffer không rỗng
                    try {
                        input = stoi(buffer);  // Chuyển chuỗi thành số nguyên
                        cout << endl;
                        return true;  // Nhập thành công
                    } catch (...) {
                        // Nếu chuyển chuỗi thành số bị lỗi (vd nhập chữ)
                        cout << "\nInvalid number format, try again.\n";
                        buffer.clear();  // Xóa buffer để nhập lại
                        cout << "(You have " << timeoutSeconds << " seconds to input): ";
                    }
                }
            }
            else if (ch == '\b') { // Phím Backspace
                if (!buffer.empty()) {
                    buffer.pop_back();  // Xóa ký tự cuối cùng trong buffer
                    cout << "\b \b";   // Xóa ký tự trên màn hình console
                }
            }
            else if (isdigit(ch)) {  // Nếu ký tự là số
                buffer.push_back(ch);  // Thêm vào buffer
                cout << ch;            // Hiển thị ký tự vừa nhập
            }
        }
        Sleep(50);  // Nghỉ 50ms để tránh dùng CPU quá mức
    }

    // Nếu hết timeout mà không nhập gì hợp lệ
    cout << "\nTimeout! No input detected.\n";
    return false;
}

int main() {
    // Khởi tạo danh sách sản phẩm với tên, giá và số lượng tồn kho
    vector<Product> productList = {
        {"Coca", 10000, 5},
        {"7-Up", 11000, 3},
        {"C2", 12000, 2},
        {"Olong", 15000, 4}
    };

    // Khởi tạo danh sách mã khuyến mãi với code, % giảm, số lần dùng còn lại, và thời hạn kết thúc (timestamp)
    vector<PromoCode> promoList = {
        {"JULY01", 15, 1, 1688160000},
        {"DISCOUNT10", 10, 1, time(nullptr) + 7 * 24 * 3600},  // Mã này có hạn dùng 7 ngày kể từ hiện tại
    };

    while (true) {
        // In ra menu chính
        cout << "\n==== VENDING MACHINE ====";
        cout << "\n1. View menu and purchase";
        // cout << "\n113. Admin mode";  // Menu ẩn dành cho admin
        cout << "\nSelect an option (auto exit after 30s inactivity): ";

        int mainChoice;

        // Đợi người dùng nhập số với thời gian timeout 30 giây
        if (!getIntInputWithTimeout(mainChoice, 30)) {
            cout << "\nNo input for 30 seconds. Machine going offline.\n";
            cout << "Press any key to turn on again...\n";

            // Đợi người dùng bấm phím bất kỳ để bật máy lại
            while (!_kbhit()) {
                Sleep(100);
            }
            _getch(); // Đọc và bỏ qua phím bấm

            cout << "Machine is back online.\n";
            continue;  // Quay lại vòng lặp in menu chính
        }

        // Xử lý lựa chọn menu chính
        switch (mainChoice) {
            case 113:
                // Nếu nhập 113 thì vào chế độ admin, yêu cầu xác thực
                if (authenticateAdmin()) {
                    showAdminMenu(productList);  // Hiển thị menu admin
                }
                break;

            case 1: {
                // Vào menu mua hàng
                while (true) {
                    printMenu(productList);  // In danh sách sản phẩm
                    cout << "Enter product option (0 to cancel): ";

                    int option;
                    if (!getIntInputWithTimeout(option, 30)) {
                        cout << "No input for 30 seconds. Returning to main menu...\n";
                        break; // Hết thời gian nhập -> quay lại menu chính
                    }

                    if (option == 0) break;  // Nếu nhập 0 thì thoát về menu chính

                    // Thực hiện đặt hàng sản phẩm được chọn
                    orderItem(option, productList, promoList);
                }
                break;
            }

            default:
                // Nếu nhập lựa chọn không hợp lệ
                cout << "Invalid choice. Please try again.\n";
        }
    }
    return 0;
}
