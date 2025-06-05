#include "Admin.h"       // Thư viện chứa các hàm, biến liên quan đến quản trị viên
#include "Product.h"     // Thư viện định nghĩa lớp Product và các thao tác liên quan sản phẩm
#include "Money.h"       // Thư viện quản lý tiền, doanh thu, và các hàm liên quan
#include <iostream>      // Thư viện chuẩn để nhập/xuất dữ liệu
#include <limits>        // Thư viện dùng để lấy giới hạn của kiểu dữ liệu, hỗ trợ xóa bộ đệm nhập
#include <iomanip>       // Thư viện định dạng đầu ra
#include <algorithm>     // Thư viện chứa hàm transform (dùng để xử lý chuỗi, chuyển đổi)
#include <cctype>        // Thư viện xử lý ký tự, dùng hàm tolower chuyển chữ hoa thành chữ thường

using namespace std;

// Hàm trợ giúp chuyển chuỗi sang chữ thường
string toLowerCase(const string& str) {
    string result = str;
    transform(result.begin(), result.end(), result.begin(), ::tolower);  // chuyển từng ký tự thành chữ thường
    return result;
}

// Hàm nhập số nguyên hợp lệ với điều kiện giá trị nhập >= minValue
int getValidInput(int minValue, const string& prompt) {
    int value;
    while (true) {
        cout << prompt;   // Hiển thị yêu cầu nhập
        if (cin >> value) {   // Nếu nhập thành công kiểu số nguyên
            if (value >= minValue) {   // Kiểm tra điều kiện >= minValue
                return value;           // Trả về giá trị hợp lệ
            } else {
                cout << "Error: Input must be at least " << minValue << ".\n";  // Thông báo lỗi nếu nhỏ hơn minValue
            }
        } else {  // Nếu nhập không hợp lệ (không phải số)
            cin.clear();  // Xóa trạng thái lỗi của cin
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Xóa hết dữ liệu còn trong bộ đệm nhập
            cout << "Invalid input! Please enter a valid number.\n";  // Thông báo lỗi nhập
        }
    }
}

// Hàm xác thực mật khẩu quản trị viên
bool authenticateAdmin() {
    string input;
    cout << "\nEnter admin password: ";  // Yêu cầu nhập mật khẩu admin
    cin >> input;

    if (input == ADMIN_PASSWORD) {  // So sánh với mật khẩu định nghĩa sẵn
        return true;   // Nếu đúng trả về true
    }

    cout << "Incorrect password!\n";  // Nếu sai, thông báo lỗi
    return false;
}

// Hiển thị menu quản trị viên và xử lý lựa chọn
void showAdminMenu(vector<Product>& products) {
    while (true) {
        cout << "\n===== ADMIN MENU =====";
        cout << "\n1. Add product";               // Thêm sản phẩm
        cout << "\n2. Remove product";            // Xóa sản phẩm
        cout << "\n3. Edit product information";  // Chỉnh sửa thông tin sản phẩm
        cout << "\n4. View total revenue";        // Xem tổng doanh thu
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
            case 0:
                // Khi thoát, nếu còn tiền dư > 10,000 thì trả lại người dùng, nếu không thì tính thành doanh thu
                if (balance > 10000) {
                    returnMoney();  // Trả tiền thừa
                    cout << "Refunded to the user.\n";
                } else {
                    totalRevenue += balance;  // Cộng số dư vào doanh thu
                    cout << "Balance is considered as revenue: " << balance << " VND\n";
                    balance = 0;  // Reset số dư
                }
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
        int newPrice = getValidInput(0, "Enter new price (0 to keep current): ");
        if (newPrice >= 10000) p.price = newPrice;

        // Sửa số lượng, nhập -1 để giữ nguyên
        int newQty = getValidInput(-1, "Enter new quantity (-1 to keep current): ");
        if (newQty >= 0) p.quantity = newQty;

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
