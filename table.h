#ifndef TABLE_H
#define TABLE_H

#include "order.h"
#include "payment.h"
#include "cashPayment.h"
#include "cardPayment.h"
#include "customer.h"

#include <unordered_map>
#include <iostream>
#include <algorithm>
#include <limits>

class table {
    protected:
        //Data members of table class
        int tableID;
        int tableCapacity;
        bool tableAvailability;
        customer* customerAssigned;
        std::unordered_map<int,order> orderList;
        payment* customerPayment;
    public:
        //Method for the class
        table();
        table(int ID, int capacity);


        bool payBill(const std::vector<menuItem*>& menu);
        bool placeOrder(const std::vector<menuItem*>& menu);//Needs the menu
        double returnTotalAmount(const std::vector<menuItem*>& menu);//Matching orderItems to menuItems and increment the total accordingly
        bool checkAvailability(int capacity); //Check if the table is available for the required amount of people
        void markAvailable();//Empty the availability status
        void reserveTable(customer* customer);//Reserve a table for a customer
        void displayOrder(const std::vector<menuItem*>& menu);//Display the whole order list
        void resetTable();

        //Setters and getters
        int getTableID() const;
        int getTableCapacity() const;
        bool getTableAvailability() const;
        void setCustomer(customer* customer);

        //Destructor
        ~table();
};
#endif 