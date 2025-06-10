// ===== Các thư viện và file header cần thiết =====
#include "Admin.h"           // Khai báo class Admin và các hàm liên quan
#include "Product.h"         // Khai báo struct Product
#include "Moneymanager.h"    // Khai báo biến totalRevenue và các hàm tiền tệ
#include "Promotion.h"       // Khai báo struct PromoCode

#include <iostream>          // Nhập xuất dữ liệu
#include <limits>            // Giới hạn giá trị nhập vào
#include <iomanip>           // Định dạng xuất
#include <algorithm>         // Các hàm thuật toán (transform)
#include <cctype>            // Hàm xử lý ký tự
#include <ctime>             // Thời gian hệ thống
#include <conio.h>           // Đọc phím không cần Enter
#include <sstream>           // Dùng ostringstream để định dạng chuỗi

using namespace std;

// ===== Định nghĩa hằng số mật khẩu admin =====
const string Admin::ADMIN_PASSWORD = "admin123";

// ====== Các hàm tiện ích nội bộ ======

// Hàm nhập mật khẩu không hiển thị ký tự, thay bằng dấu *
string Admin::getHiddenPassword() {
    string password;
    char ch;
    while ((ch = _getch()) != '\r') {  // Lặp đến khi người dùng nhấn Enter
        if (ch == '\b') {  // Xử lý phím Backspace
            if (!password.empty()) {
                password.pop_back();
                cout << "\b \b";  // Xóa ký tự khỏi màn hình
            }
        } else {
            password += ch;
            cout << '*';  // In dấu * thay vì ký tự
        }
    }
    cout << '\n';
    return password;
}

// Hàm định dạng thời gian thành chuỗi dd/mm/yyyy hh:mm
string Admin::formatTime(time_t rawTime) {
    tm* timeinfo = localtime(&rawTime);
    ostringstream oss;
    oss << put_time(timeinfo, "%d/%m/%Y %H:%M");
    return oss.str();
}

// Hàm chuyển chuỗi thành chữ thường để so sánh không phân biệt hoa/thường
string Admin::toLowerCase(const string& str) {
    string result = str;
    transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

// Hàm nhập số nguyên hợp lệ ≥ minValue
int Admin::getValidInput(int minValue, const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value && value >= minValue) return value;
        cin.clear();  // Xóa lỗi
        cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Bỏ qua dòng sai
        cout << "Invalid input! Try again.\n";
    }
}

// ====== Các hàm thuộc lớp Admin ======

// Hàm xác thực mật khẩu admin, cho 3 lần thử
bool Admin::authenticate() {
    int attempts = 3;
    while (attempts--) {
        cout << "\nEnter admin password: ";
        string input = getHiddenPassword();
        if (input == ADMIN_PASSWORD) {
            time_t now = time(nullptr);
            cout << "Admin access granted at: " << formatTime(now) << "\n";
            return true;
        }
        cout << "Incorrect password! Attempts left: " << attempts << "\n";
    }
    cout << "Too many failed attempts. Access denied.\n";
    return false;
}

// Hiển thị menu quản trị viên và xử lý lựa chọn
void Admin::showMenu(vector<Product>& products, vector<PromoCode>& promoList) {
    while (true) {
        cout << "\n===== ADMIN MENU =====\n"
             << "1. Add product\n"
             << "2. Remove product\n"
             << "3. Edit product information\n"
             << "4. View total revenue\n"
             << "5. Add promo code\n"
             << "6. Remove promo code\n"
             << "7. Edit promo code\n"
             << "0. Exit\n"
             << "Choose an option: ";
        int choice;
        cin >> choice;
        if (cin.fail()) {
            cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid choice!\n";
            continue;
        }

        // Gọi hàm tương ứng theo lựa chọn
        switch (choice) {
            case 1: addProduct(products); break;
            case 2: removeProduct(products); break;
            case 3: modifyProduct(products); break;
            case 4: viewCurrentBalance(); break;
            case 5: addPromoCode(promoList); break;
            case 6: removePromoCode(promoList); break;
            case 7: editPromoCode(promoList); break;
            case 0: return;
            default: cout << "Invalid choice!\n";
        }
    }
}

// Thêm sản phẩm mới, hoặc cập nhật nếu đã tồn tại
void Admin::addProduct(vector<Product>& products) {
    string name;
    cout << "\nEnter new product name: ";
    cin.ignore();
    getline(cin, name);
    string lowerName = toLowerCase(name);

    // Tìm sản phẩm trùng tên
    for (Product& p : products) {
        if (toLowerCase(p.name) == lowerName) {
            cout << "Product exists: " << p.name << " - Price: " << p.price << " - Quantity: " << p.quantity << "\n";
            int time = 3;
            while (time--) {
                char choice;
                cout << "Update info? (1 for yes / 2 for no): ";
                cin >> choice;
                if (choice == '1') {
                    cin.ignore();
                    p.name = name;
                    p.price = getValidInput(10000, "Enter new price: ");
                    p.quantity = getValidInput(1, "Enter new quantity: ");
                    cout << "Product updated successfully!\n";
                    return;
                } else if (choice == '2') {
                    return;
                } else {
                    cout << "Try again!\n";
                }
            }
            cout << "Too many failed attempts.\n";
            return;
        }
    }

    // Nếu chưa tồn tại, thêm mới
    int price = getValidInput(10000, "Enter price: ");
    int qty = getValidInput(1, "Enter quantity: ");
    products.emplace_back(name, price, qty);
    cout << "Product added successfully!\n";
}

// Xóa sản phẩm theo số thứ tự
void Admin::removeProduct(vector<Product>& products) {
    if (products.empty()) {
        cout << "No products available.\n";
        return;
    }
    for (size_t i = 0; i < products.size(); ++i)
        cout << i + 1 << ". " << products[i].name << "\n";

    cout << "Select product number to remove (0 to cancel): ";
    int choice;
    cin >> choice;
    if (cin.fail() || choice < 0 || choice > static_cast<int>(products.size())) {
        cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid choice.\n";
        return;
    }
    if (choice == 0) return;

    products.erase(products.begin() + (choice - 1));
    cout << "Product removed.\n";
}

// Chỉnh sửa thông tin sản phẩm
void Admin::modifyProduct(vector<Product>& products) {
    if (products.empty()) {
        cout << "No products available.\n";
        return;
    }
    for (size_t i = 0; i < products.size(); ++i)
        cout << i + 1 << ". " << products[i].name << " - Price: " << products[i].price << " - Quantity: " << products[i].quantity << "\n";

    cout << "Select product to edit (0 to cancel): ";
    int choice;
    cin >> choice;
    if (cin.fail() || choice < 0 || choice > static_cast<int>(products.size())) {
        cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid choice.\n";
        return;
    }
    if (choice == 0) return;

    Product& p = products[choice - 1];
    cin.ignore();
    cout << "Enter new name (Enter to keep): ";
    string name;
    getline(cin, name);
    if (!name.empty()) p.name = name;

    int newPrice, attempts = 3;
    while (attempts--) {
        newPrice = getValidInput(0, "Enter new price (0 to keep): ");
        if (newPrice == 0) break;
        if (newPrice >= 10000) {
            p.price = newPrice;
            break;
        }
        cout << "Try again!\n";
    }

    int newQty;
    attempts = 3;
    while (attempts--) {
        newQty = getValidInput(-1, "Enter new quantity (-1 to keep): ");
        if (newQty == -1) break;
        if (newQty >= 1) {
            p.quantity = newQty;
            break;
        }
        cout << "Try again!\n";
    }
    cout << "Product updated.\n";
}

// Hiển thị tổng doanh thu hiện tại
void Admin::viewCurrentBalance() {
    cout << "\nTotal revenue: " << totalRevenue << " VND\n";
}

// Thêm mã khuyến mãi mới
void Admin::addPromoCode(vector<PromoCode>& promoList) {
    string code;
    int discount, uses, days;
    cout << "Enter promo code: ";
    cin >> code;

    discount = getValidInput(1, "Discount percent (1-100): ");
    while (discount > 100) discount = getValidInput(1, "Discount percent (1-100): ");

    uses = getValidInput(1, "Number of uses: ");
    days = getValidInput(1, "Valid for how many days from now? ");
    time_t expiry = time(nullptr) + days * 86400;  // Tính thời gian hết hạn (đơn vị: giây)

    promoList.emplace_back(code, discount, uses, expiry);
    cout << "Promo code added.\n";
}

// Xóa mã khuyến mãi
void Admin::removePromoCode(vector<PromoCode>& promoList) {
    if (promoList.empty()) {
        cout << "No promo codes.\n";
        return;
    }
    for (size_t i = 0; i < promoList.size(); ++i)
        cout << i + 1 << ". Code: " << promoList[i].code
             << " | Discount: " << promoList[i].discountPercent
             << "% | Uses left: " << promoList[i].remainingUses
             << " | Expires: " << formatTime(promoList[i].expirationTime) << "\n";

    int choice;
    cout << "Enter number to remove (0 to cancel): ";
    cin >> choice;
    if (choice == 0) return;
    if (choice > 0 && choice <= static_cast<int>(promoList.size())) {
        promoList.erase(promoList.begin() + (choice - 1));
        cout << "Promo code removed.\n";
    } else {
        cout << "Invalid choice.\n";
    }
}

// Chỉnh sửa thông tin mã khuyến mãi
void Admin::editPromoCode(vector<PromoCode>& promoList) {
    if (promoList.empty()) {
        cout << "No promo codes.\n";
        return;
    }
    for (size_t i = 0; i < promoList.size(); ++i)
        cout << i + 1 << ". Code: " << promoList[i].code
             << " | Discount: " << promoList[i].discountPercent
             << "% | Uses left: " << promoList[i].remainingUses
             << " | Expires: " << formatTime(promoList[i].expirationTime) << "\n";

    int choice;
    cout << "Enter number to edit (0 to cancel): ";
    cin >> choice;
    if (choice == 0) return;
    if (choice > 0 && choice <= static_cast<int>(promoList.size())) {
        PromoCode& p = promoList[choice - 1];
        p.discountPercent = getValidInput(1, "New discount (1_100): ");
        while (p.discountPercent > 100) p.discountPercent = getValidInput(1, "New discount (1_100): ");
        p.remainingUses = getValidInput(0, "New number of uses: ");
        cout << "Promo code updated.\n";
    } else {
        cout << "Invalid choice.\n";
    }
}
