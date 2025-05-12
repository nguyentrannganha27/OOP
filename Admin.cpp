#include "Admin.h"
#include "Product.h"
#include "Money.h"
#include <iostream>
#include <limits>
#include <iomanip>
#include <algorithm>  // for transform
#include <cctype>     // for tolower

using namespace std;

// Helper to convert string to lowercase
string toLowerCase(const string& str) {
    string result = str;
    transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

// Function to get a valid integer input (with a minimum value check)
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

// Function to authenticate the admin
bool authenticateAdmin() {
    string input;
    cout << "\nEnter admin password: ";
    cin >> input;

    if (input == ADMIN_PASSWORD) {
        return true;
    }

    cout << "Incorrect password!\n";
    return false;
}

// Show the admin menu
void showAdminMenu(vector<Product>& products) {
    while (true) {
        cout << "\n===== ADMIN MENU =====";
        cout << "\n1. Add product";
        cout << "\n2. Remove product";
        cout << "\n3. Edit product information";
        cout << "\n4. View total revenue";
        cout << "\n0. Exit";
        cout << "\nChoose an option: ";

        int choice;
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid choice!\n";
            continue;
        }

        switch (choice) {
            case 1:
                addProduct(products);
                break;
            case 2:
                removeProduct(products);
                break;
            case 3:
                modifyProduct(products);
                break;
            case 4:
                viewCurrentBalance();
                break;
            case 0:
                if (balance > 10000) {
                    returnMoney();  // Refund if balance > 10,000 VND
                    cout << "Refunded to the user.\n";
                } else {
                    totalRevenue += balance;
                    cout << "Balance is considered as revenue: " << balance << " VND\n";
                    balance = 0;
                }
                return;
            default:
                cout << "Invalid choice!\n";
        }
    }
}

// Add a product
void addProduct(vector<Product>& products) {
    string name;
    cout << "\nEnter new product name: ";
    cin.ignore();  // Clear any previous leftover newline character
    getline(cin, name);  // Read the full name including spaces
    string lowerName = toLowerCase(name);

    for (Product& p : products) {
        if (toLowerCase(p.name) == lowerName) {
            cout << "A product with the same name (case-insensitive) already exists.\n";
            cout << "Current: " << p.name << " - Price: " << p.price << " - Quantity: " << p.quantity << "\n";
            cout << "Do you want to update its information? (y/n): ";
            char choice;
            cin >> choice;

            if (choice == 'y' || choice == 'Y') {
                cin.ignore();  // Clear the newline character after the choice input

                p.name = name;

                // Validate price input
                int price = getValidInput(10000, "Enter new price (greater than 10000 to update): ");
                p.price = price;

                // Validate quantity input
                int quantity = getValidInput(1, "Enter new quantity (greater than 1 to update): ");
                p.quantity = quantity;

                cout << "Product updated successfully!\n";
            }
            return;
        }
    }

    // Validate price input
    int price = getValidInput(10000, "Enter product price (greater than 10000): ");
    // Validate quantity input
    int quantity = getValidInput(1, "Enter quantity (greater than 1): ");

    products.push_back(Product(name, price, quantity));
    cout << "Product added successfully!\n";
}

// Remove a product
void removeProduct(vector<Product>& products) {
    cout << "\nCurrent product list:\n";
    for (size_t i = 0; i < products.size(); ++i) {
        cout << i + 1 << ". " << products[i].name << "\n";
    }

    cout << "Select the product number to delete (0 to cancel): ";
    int choice;
    cin >> choice;

    if (choice > 0 && choice <= static_cast<int>(products.size())) {
        products.erase(products.begin() + choice - 1);
        cout << "Product removed successfully!\n";
    }
}

// Modify product information
void modifyProduct(vector<Product>& products) {
    cout << "\nCurrent product list:\n";
    for (size_t i = 0; i < products.size(); ++i) {
        cout << i + 1 << ". " << products[i].name
             << " - Price: " << products[i].price
             << " - Quantity: " << products[i].quantity << "\n";
    }

    cout << "Select the product number to edit (0 to cancel): ";
    int choice;
    cin >> choice;

    if (choice > 0 && choice <= static_cast<int>(products.size())) {
        Product& p = products[choice - 1];

        cout << "Enter new name (Enter to keep current): ";
        cin.ignore();
        string newName;
        getline(cin, newName);
        if (!newName.empty()) p.name = newName;

        // Edit price with validation
        int newPrice = getValidInput(0, "Enter new price (0 to keep current): ");
        if (newPrice > 0) p.price = newPrice;

        // Edit quantity with validation
        int newQty = getValidInput(-1, "Enter new quantity (-1 to keep current): ");
        if (newQty >= 0) p.quantity = newQty;

        cout << "Product updated successfully!\n";
    }
}

// View the current balance (total revenue)
void viewCurrentBalance() {
    extern int totalRevenue;  // Using the revenue variable from another file
    cout << "\nTotal revenue: " << totalRevenue << " VND\n";
}
