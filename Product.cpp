#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>

struct Product {
    std::string ten;
    int gia;
    int soLuong;

    Product(std::string t, int g, int s) : ten(t), gia(g), soLuong(s) {}

    // Hàm tính giá trị tổng của sản phẩm
    int getTotalPrice() const {
        return gia * soLuong;
    }
};

#endif

