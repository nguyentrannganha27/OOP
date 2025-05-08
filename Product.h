#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>

struct Product {
    std::string name;
    int price;
    int quantity;

    // Constructor for convenient Product initialization
    Product(std::string n, int p, int q) : name(n), price(p), quantity(q) {}
};

#endif
