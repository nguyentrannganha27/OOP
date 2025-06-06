#ifndef PROMOTION_H
#define PROMOTION_H

#include <string>   // Dùng std::string cho mã khuyến mãi
#include <ctime>    // Dùng time_t để quản lý thời gian hết hạn
#include <iomanip>  // std::put_time
#include <sstream>  // std::ostringstream
class PromoCode {
public:
    std::string code;          // Mã khuyến mãi (ví dụ: "SALE10")
    int discountPercent;       // Phần trăm giảm giá (ví dụ: 10 tương ứng 10%)
    int remainingUses;         // Số lượng voucher còn lại có thể sử dụng
    int totalUses;             // Tổng số lượng voucher đã phát hành ban đầu
    time_t expirationTime;     // Thời gian hết hạn mã khuyến mãi (dưới dạng timestamp)

    // Hàm kiểm tra mã còn hiệu lực hay không (được khai báo ở đây, định nghĩa bên cpp)
    bool isValid();

    // Hàm áp dụng mã khuyến mãi: nhận mã nhập vào, giá sản phẩm, số lượng, 
    // trả về số tiền được giảm, đồng thời cập nhật số lượng còn lại nếu thành công
    int applyPromoCode(const std::string& enteredCode, int productPrice, int qty);

    // Constructor khởi tạo mã khuyến mãi với các thông tin
    PromoCode(std::string c, int discount, int total, time_t expiry) : 
        code(c), discountPercent(discount), remainingUses(total), totalUses(total), expirationTime(expiry) {}
};

#endif
