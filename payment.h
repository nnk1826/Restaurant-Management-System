#ifndef PAYMENT_H
#define PAYMENT_H

#include <vector>
#include <unordered_map>
#include <fstream>
#include <string>
#include <sstream>
#include <ctime>
#include <iostream>
#include <algorithm>
#include <iomanip>

#include "order.h"
#include "menuItem.h"

class payment {
protected:
    int paymentID;
    std::string customerName;
    int contactNumber;
    int tableID;
    double totalAmount;
    std::unordered_map<int, order> orderList;

public:
    payment(std::string customerName, int contactNumber, int tableID, double totalAmount, const std::unordered_map<int, order>& orderList);   

    virtual void generatePaymentID() = 0; // Based on customer contactNumber and tableID
    virtual bool printBill(const std::vector<menuItem*>& menu) = 0; // Needs to pass the orderList into the function
    virtual int getPaymentID() = 0;
    virtual double returningCustomersDiscount() = 0; // Check if the customer is new or returning and give them a 5% discount for 3 or more returns
    virtual ~payment() {}
};

#endif