#ifndef MENU_H  // Nếu chưa định nghĩa MENU_H thì tiếp tục
#define MENU_H  // Định nghĩa MENU_H để tránh include nhiều lần

#include "Product.h"       // Bao gồm định nghĩa lớp Product
#include <vector>          // Sử dụng vector để quản lý danh sách sản phẩm

// Hàm in ra danh sách menu sản phẩm
// Tham số truyền vào là vector các sản phẩm, không thay đổi dữ liệu (const)
void printMenu(const std::vector<Product>& productList);

#endif  // Kết thúc phần định nghĩa MENU_H
