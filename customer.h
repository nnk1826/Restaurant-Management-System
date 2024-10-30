#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
#include <iostream>

using namespace std;

class customer { //Class for individual customer, to create a personalized experience
    protected:
        //Personal information
        std::string name;
        int contactNumber;
    public:
        //Constructor when a new customer is using the app
        customer(string name, int contactNumber);
        
        //Getters for a customer information -> shown on the screen of the app
        string getName();
        int getContactNumber();

        ~customer();
};

#endif
