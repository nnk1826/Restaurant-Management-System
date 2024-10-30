#ifndef TAKEAWAY_H
#define TAKEAWAY_H

#include "order.h"
#include "payment.h"
#include "cashPayment.h"
#include "cardPayment.h"
#include "customer.h"

#include <unordered_map>
#include <iostream>
#include <algorithm>
#include <limits>

class takeaway {
    protected:
        //Data members of takeaway class
        int takeawayID;
        std::unordered_map<int,order> orderList;
        payment* customerPayment;
    public:
        //Counter for IDs
        static int IDcounter;

        //Constructor
        takeaway();

        //Method for the class
        bool payBill(const std::vector<menuItem*>& menu, customer* customer);

        bool placeOrder(const std::vector<menuItem*>& menu);//Needs the itemID and its quantity to place an order

        double returnTotalAmount(const std::vector<menuItem*>& menu);//Matching orderItems to menuItems and increment the total accordingly

        void displayOrder(const std::vector<menuItem*>& menu);//Display the whole order list

        //Destructor
        ~takeaway();
};

#endif