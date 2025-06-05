#ifndef ORDER_H
#define ORDER_H

#include "Product.h"
#include "Promotion.h"
#include <vector>

// Khai báo biến toàn cục balance lưu số tiền hiện có trong máy
extern int balance;

// Hàm xử lý đơn hàng:
// - option: lựa chọn sản phẩm (số thứ tự trong menu)
// - productList: danh sách sản phẩm có sẵn
// - promoList: danh sách mã khuyến mãi
void orderItem(int option, std::vector<Product>& productList, std::vector<PromoCode>& promoList);

#endif
