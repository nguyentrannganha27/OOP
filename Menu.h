#ifndef MENU_H        // Tránh đính kèm file này nhiều lần trong quá trình biên dịch
#define MENU_H

#include "Product.h"  // Bao gồm định nghĩa lớp Product để sử dụng trong menu
#include <vector>     // Sử dụng vector để chứa danh sách sản phẩm

class Menu {
public:
    // Hàm static để in ra menu sản phẩm hiện có
    static void printMenu(const std::vector<Product>& productList);
};

#endif                // Kết thúc chỉ thị tiền xử lý cho MENU_H
