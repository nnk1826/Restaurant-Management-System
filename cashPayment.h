#ifndef CASHPAYMENT_H
#define CASHPAYMENT_H

#include "payment.h"

class cashPayment : public payment{
    public:
        cashPayment(std::string customerName, int contactNumber, int tableID,double totalAmount,const std::unordered_map<int,order>& orderList);
        void generatePaymentID();
        bool printBill(const std::vector<menuItem*>& menu);
        int getPaymentID();
        double returningCustomersDiscount();
};

#endif 