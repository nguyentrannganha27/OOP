#ifndef ORDER_H              // Tránh đụng độ định nghĩa lặp (include guard)
#define ORDER_H

#include "Product.h"         // Bao gồm định nghĩa lớp Product
#include "Promotion.h"       // Bao gồm định nghĩa lớp PromoCode
#include <vector>            // Sử dụng std::vector cho danh sách sản phẩm và mã khuyến mãi

// Khai báo biến toàn cục balance lưu số tiền hiện có trong máy
extern int balance;          // Biến toàn cục lưu số dư tiền mà người dùng đã nạp vào máy

// Hàm xử lý đơn hàng:
// - option: lựa chọn sản phẩm (số thứ tự trong menu)
// - productList: danh sách sản phẩm có sẵn
// - promoList: danh sách mã khuyến mãi
void orderItem(int option, std::vector<Product>& productList, std::vector<PromoCode>& promoList);

#endif  // Kết thúc phần định nghĩa ORDER_H
