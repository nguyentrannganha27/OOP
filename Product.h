#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>  // Thư viện chuỗi để dùng std::string

// Định nghĩa lớp Product đại diện cho sản phẩm
class Product {
public:
    std::string name;  // Tên sản phẩm
    int price;         // Giá sản phẩm (đơn vị tiền tệ)
    int quantity;      // Số lượng sản phẩm hiện có trong kho

    // Constructor khởi tạo sản phẩm với tên, giá và số lượng
    Product(std::string n, int p, int q);

    // Phương thức tính tổng giá trị của sản phẩm trong kho (price * quantity)
    int getTotalPrice() const;
};

#endif
