#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>

struct Product {
    std::string name;
    int price;
    int quantity;

    Product(std::string n, int p, int q) : name(n), price(p), quantity(q) {}

    // Function to calculate total value of this product in stock
    int getTotalPrice() const {
        return price * quantity;
    }
};

#endif
