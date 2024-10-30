#include "payment.h"

payment::payment(std::string customerName, int contactNumber, int tableID, double totalAmount, const std::unordered_map<int, order>& orderList)
    : customerName(customerName), contactNumber(contactNumber), tableID(tableID), totalAmount(totalAmount), orderList(orderList) {}
