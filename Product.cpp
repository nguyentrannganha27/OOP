#include "Product.h"  // Bao gồm định nghĩa lớp Product

//  Hàm khởi tạo (constructor) của lớp Product
// - n: tên sản phẩm
// - p: giá sản phẩm
// - q: số lượng tồn kho
Product::Product(std::string n, int p, int q) : name(n), price(p), quantity(q) {}

//  Phương thức tính tổng giá trị của sản phẩm còn trong kho
// - Trả về: giá tiền * số lượng
int Product::getTotalPrice() const {
    return price * quantity;
}
