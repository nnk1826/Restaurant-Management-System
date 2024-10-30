#ifndef CARDPAYMENT_H
#define CARDPAYMENT_H

#include "payment.h"

class cardPayment : public payment
{
public:
    cardPayment(std::string customerName, int contactNumber, int tableID, double totalAmount, const std::unordered_map<int, order> &orderList);
    void generatePaymentID();
    bool printBill(const std::vector<menuItem*> &menu);
    int getPaymentID();
    double returningCustomersDiscount();
};

#endif