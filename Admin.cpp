#include "Admin.h"       // Thư viện chứa các hàm, biến liên quan đến quản trị viên
#include "Product.h"     // Thư viện định nghĩa lớp Product và các thao tác liên quan sản phẩm
#include "Money.h"       // Thư viện quản lý tiền, doanh thu, và các hàm liên quan
#include <iostream>      // Thư viện chuẩn để nhập/xuất dữ liệu
#include <limits>        // Thư viện dùng để lấy giới hạn của kiểu dữ liệu, hỗ trợ xóa bộ đệm nhập
#include <iomanip>       // Thư viện định dạng đầu ra
#include <algorithm>     // Thư viện chứa hàm transform (dùng để xử lý chuỗi, chuyển đổi)
#include <cctype>        // Thư viện xử lý ký tự, dùng hàm tolower chuyển chữ hoa thành chữ thường
#include "Promotion.h"
#include <ctime>
#include <conio.h>       // Cho _getch
#include <sstream>       // Cho std::ostringstream
using namespace std;

// Hàm ẩn mật khẩu khi nhập
string getHiddenPassword() {
    string password;
    char ch;
    while ((ch = _getch()) != '\r') { // Enter
        if (ch == '\b') {
            if (!password.empty()) {
                password.pop_back();
                cout << "\b \b";
            }
        } else {
            password += ch;
            cout << '*';
        }
    }
    cout << '\n';
    return password;
}

// Hàm chuyển time_t thành chuỗi ngày giờ dễ đọc
std::string formatTime(time_t rawTime) {
    std::tm* timeinfo = std::localtime(&rawTime);
    std::ostringstream oss;
    oss << std::put_time(timeinfo, "%d/%m/%Y %H:%M");
    return oss.str();
}

// Hàm trợ giúp chuyển chuỗi sang chữ thường
string toLowerCase(const string& str) {
    string result = str;
    transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

// Hàm nhập số nguyên hợp lệ với điều kiện giá trị nhập >= minValue
int getValidInput(int minValue, const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            if (value >= minValue) {
                return value;
            } else {
                cout << "Error: Input must be at least " << minValue << ".\n";
            }
        } else {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Please enter a valid number.\n";
        }
    }
}

// Hàm xác thực mật khẩu quản trị viên
bool authenticateAdmin() {
    int attempts = 3;
    while (attempts--) {
        string input;
        cout << "\nEnter admin password: ";
        input = getHiddenPassword();

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
void showAdminMenu(vector<Product>& products, vector<PromoCode>& promoList) {
    while (true) {
        cout << "\n===== ADMIN MENU =====";
        cout << "\n1. Add product";               // Thêm sản phẩm
        cout << "\n2. Remove product";            // Xóa sản phẩm
        cout << "\n3. Edit product information";  // Chỉnh sửa thông tin sản phẩm
        cout << "\n4. View total revenue";        // Xem tổng doanh thu
        cout << "\n5. Add promo code";
        cout << "\n6. Remove promo code";
        cout << "\n7. Edit promo code";
        cout << "\n0. Exit";                       // Thoát menu admin
        cout << "\nChoose an option: ";

        int choice;
        cin >> choice;

        if (cin.fail()) {  // Kiểm tra nhập lựa chọn hợp lệ
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid choice!\n";   // Thông báo lỗi
            continue;                      // Yêu cầu nhập lại
        }

        // Xử lý lựa chọn menu
        switch (choice) {
            case 1:
                addProduct(products);  // Thêm sản phẩm mới
                break;
            case 2:
                removeProduct(products);  // Xóa sản phẩm
                break;
            case 3:
                modifyProduct(products);  // Sửa thông tin sản phẩm
                break;
            case 4:
                viewCurrentBalance();     // Xem doanh thu hiện tại
                break;
            case 5:
                addPromoCode(promoList);
            break;
            case 6:
                removePromoCode(promoList);
            break;
            case 7:
                editPromoCode(promoList);
            break;
            case 0:
                return;
            default:
                cout << "Invalid choice!\n";  // Lựa chọn không hợp lệ
        }
    }
}

// Hàm thêm sản phẩm mới hoặc cập nhật sản phẩm đã tồn tại
void addProduct(vector<Product>& products) {
    string name;
    cout << "\nEnter new product name: ";
    cin.ignore();  // Xóa ký tự newline còn tồn đọng trong bộ đệm trước khi getline
    getline(cin, name);  // Nhập tên sản phẩm có thể chứa dấu cách
    string lowerName = toLowerCase(name);  // Chuyển tên nhập thành chữ thường để so sánh không phân biệt hoa thường

    // Kiểm tra sản phẩm trùng tên (không phân biệt hoa thường)
    for (Product& p : products) {
        if (toLowerCase(p.name) == lowerName) {
            cout << "A product with the same name (case-insensitive) already exists.\n";
            cout << "Current: " << p.name << " - Price: " << p.price << " - Quantity: " << p.quantity << "\n";
            char choice;
            int time = 3;  // Giới hạn số lần nhập sai

            while (true)
            {
                cout << "Do you want to update its information? (1 for yes/2 for no): ";
                cin >> choice;
                time -=1;

                if (choice == '1') {
                    cin.ignore();  // Xóa newline sau khi nhập lựa chọn

                    p.name = name;  // Cập nhật tên sản phẩm

                    // Nhập giá mới, giá phải lớn hơn 10,000
                    int price = getValidInput(10000, "Enter new price (greater than 10000 to update): ");
                    p.price = price;

                    // Nhập số lượng mới, số lượng >= 1
                    int quantity = getValidInput(1, "Enter new quantity (greater than 1 to update): ");
                    p.quantity = quantity;

                    cout << "Product updated successfully!\n";
                    return;
                }
                else if(choice == '2') {
                    return;  // Không cập nhật, thoát hàm
                }
                else {
                    if (time == 0 ) {
                        cout << "Selected wrong 3 times, please select action again" << endl;
                        return;
                    }
                    cout << "Try again!!" << endl;
                }
            }
        }
    }

    // Nếu sản phẩm chưa tồn tại, nhập giá và số lượng mới
    int price = getValidInput(10000, "Enter product price (greater than 10000): ");
    int quantity = getValidInput(1, "Enter quantity (greater than 1): ");

    products.push_back(Product(name, price, quantity));  // Thêm sản phẩm mới vào danh sách
    cout << "Product added successfully!\n";
}

// Hàm xóa sản phẩm theo số thứ tự
void removeProduct(vector<Product>& products) {
    cout << "\nCurrent product list:\n";
    for (size_t i = 0; i < products.size(); ++i) {
        cout << i + 1 << ". " << products[i].name << "\n";  // Hiển thị danh sách sản phẩm hiện có
    }

    cout << "Select the product number to delete (0 to cancel): ";
    int choice;
    cin >> choice;

    if (cin.fail()) {  // Kiểm tra nhập hợp lệ
        cin.clear(); // reset trạng thái lỗi của cin
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // xóa bộ đệm nhập
        cout << "Invalid input. Please enter a valid number.\n";
        return;  // hoặc bạn có thể yêu cầu nhập lại
    }

    if (choice == 0) {  // Hủy xóa
        cout << "Delete canceled.\n";
        return;
    }

    // Nếu số chọn hợp lệ, xóa sản phẩm
    if (choice > 0 && choice <= static_cast<int>(products.size())) {
        products.erase(products.begin() + choice - 1);
        cout << "Product removed successfully!\n";
    } else {
        cout << "Invalid choice, please try again.\n";  // Lựa chọn không hợp lệ
    }
}

// Hàm sửa thông tin sản phẩm theo số thứ tự
void modifyProduct(vector<Product>& products) {
    cout << "\nCurrent product list:\n";
    for (size_t i = 0; i < products.size(); ++i) {
        cout << i + 1 << ". " << products[i].name
             << " - Price: " << products[i].price
             << " - Quantity: " << products[i].quantity << "\n";  // Hiển thị danh sách sản phẩm
    }

    cout << "Select the product number to edit (0 to cancel): ";
    int choice;
    cin >> choice;

    if (cin.fail()) {  // Kiểm tra nhập hợp lệ
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid choice, please try again.\n";
        return;
    }

    if (choice == 0) {  // Hủy sửa
        cout << "Edit canceled.\n";
        return;
    }

    // Nếu lựa chọn hợp lệ thì cho phép sửa
    if (choice > 0 && choice <= static_cast<int>(products.size())) {
        Product& p = products[choice - 1];  // Tham chiếu tới sản phẩm được chọn

        cout << "Enter new name (Enter to keep current): ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Xóa bộ đệm trước khi getline
        string newName;
        getline(cin, newName);  // Nhập tên mới, nếu để trống thì giữ nguyên
        if (!newName.empty()) p.name = newName;

        // Sửa giá, nhập 0 để giữ nguyên giá cũ
        int time_2 = 3;
while (true)
{
    time_2 -= 1;

    int newPrice = getValidInput(0, "Enter new price (0 to keep current): ");
    
    if (newPrice == 0) {
        // Keep current price and exit loop
        break;
    }

    if (newPrice >= 10000) {
        p.price = newPrice;
        break;
    } else {
        if (time_2 == 0) {
            cout << "Maximum attempts reached. Keeping current price." <<endl;
            break;
        }
        cout << "Try again!!" << endl;
    }
}
        // Sửa số lượng, nhập -1 để giữ nguyên
        int time_3 = 3;
        while (true)
        {
        time_3 -=1;
        int newQty = getValidInput(-1, "Enter new quantity (-1 to keep current): ");
        if (newQty >= 1) {
            p.quantity = newQty;
            break;
        }
        else if (newQty == -1)
        {
            break;
        }
        else {
        if (time_3 == 0) {
            cout << "Maximum attempts reached. Keeping current quantity." <<endl;
            break;
        }
        cout << "Try again!!" << endl;
    }
}
        


        cout << "Product updated successfully!\n";
    } else {
        cout << "Invalid choice, please try again.\n";  // Lựa chọn không hợp lệ
    }
}

// Hàm hiển thị tổng doanh thu hiện tại
void viewCurrentBalance() {
    extern int totalRevenue;  // Sử dụng biến tổng doanh thu khai báo ở file khác
    cout << "\nTotal revenue: " << totalRevenue << " VND\n";
}
void addPromoCode(std::vector<PromoCode>& promoList) {
    std::string code;
    int discount, uses, daysValid;

    std::cout << "Enter promo code: ";
    std::cin >> code;

    // Nhập phần trăm giảm hợp lệ (1–100)
    while (true) {
        std::cout << "Discount percent (1-100): ";
        if (std::cin >> discount && discount >= 1 && discount <= 100) break;

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    // Nhập số lần sử dụng (>=1)
    while (true) {
        std::cout << "Number of uses: ";
        if (std::cin >> uses && uses > 0) break;

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    // Nhập số ngày hiệu lực (>=1)
    while (true) {
        std::cout << "Valid for how many days from now? ";
        if (std::cin >> daysValid && daysValid > 0) break;

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    time_t expiry = time(nullptr) + daysValid * 86400;
    promoList.push_back(PromoCode(code, discount, uses, expiry));
    std::cout << "Promo code added.\n";
}


void removePromoCode(std::vector<PromoCode>& promoList) {
    if (promoList.empty()) {
        std::cout << "No promo codes available.\n";
        return;
    }

    std::cout << "\n=== List of Promo Codes ===\n";
    for (size_t i = 0; i < promoList.size(); ++i) {
        const auto& p = promoList[i];
        std::cout << i + 1 << ". Code: " << p.code
          << " | Discount: " << p.discountPercent << "%"
          << " | Uses left: " << p.remainingUses
          << " | Expires: " << formatTime(p.expirationTime) << "\n";

    }

    int choice;
    while (true) {
        std::cout << "Enter the number of the promo code to remove (0 to cancel): ";
        if (std::cin >> choice) {
            if (choice == 0) {
                std::cout << "Cancelled.\n";
                return;
            }
            if (choice > 0 && choice <= static_cast<int>(promoList.size())) {
                promoList.erase(promoList.begin() + (choice - 1));
                std::cout << "Promo code removed.\n";
                return;
            } else {
                std::cout << "Invalid choice. Try again.\n";
            }
        } else {
            std::cin.clear();  // Xóa trạng thái lỗi
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Bỏ qua dữ liệu lỗi
        }
    }
}


void editPromoCode(std::vector<PromoCode>& promoList) {
    if (promoList.empty()) {
        std::cout << "No promo codes available.\n";
        return;
    }

    std::cout << "\n=== Promo Codes List ===\n";
    for (size_t i = 0; i < promoList.size(); ++i) {
        const auto& p = promoList[i];
        std::cout << i + 1 << ". Code: " << p.code
          << " | Discount: " << p.discountPercent << "%"
          << " | Uses left: " << p.remainingUses
          << " | Expires: " << formatTime(p.expirationTime) << "\n";

    }

    int choice;
    while (true) {
        std::cout << "Enter the number of the promo code to edit (0 to cancel): ";
        if (std::cin >> choice) {
            if (choice == 0) {
                std::cout << "Cancelled.\n";
                return;
            }
            if (choice > 0 && choice <= static_cast<int>(promoList.size())) {
                PromoCode& p = promoList[choice - 1];

                int discount;
                while (true) {
                    std::cout << "New discount percent (1-100): ";
                    if (std::cin >> discount && discount >= 1 && discount <= 100) {
                        break;
                    }
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Invalid discount percent. Try again.\n";
                }

                int uses;
                while (true) {
                    std::cout << "New remaining uses (>= 0): ";
                    if (std::cin >> uses && uses >= 0) {
                        break;
                    }
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Invalid number of uses. Try again.\n";
                }

                p.discountPercent = discount;
                p.remainingUses = uses;

                std::cout << "Promo code updated.\n";
                return;
            } else {
                std::cout << "Invalid choice. Try again.\n";
            }
        } else {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}
