#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>

struct Product {
    std::string ten;
    int gia;
    int soLuong;

    // Constructor để khởi tạo Product dễ dàng hơn
    Product(std::string t, int g, int s) : ten(t), gia(g), soLuong(s) {}
};

#endif
