#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>
#include "customer.h"

using namespace std;

customer::customer(string name, int contactNumber){
            //Convert customer name to UPPERCASE to eliminate syntax mismatching when searching for returning customers;
            for (char& c : name) {
                c = std::toupper(c);  // Apply toupper to each character
            }
            
            //Opening the textfile database to write information into it
            ofstream customer_Info;
            customer_Info.open("customersInformation.txt",ios::app); //Open the textfile in appending mode without overwriting it
            if (customer_Info.is_open()) {
                customer_Info << name << " " << contactNumber << "\n";  // Append the customer's info
                customer_Info.close();
            } else {
                std::cout << "Error: Could not open file for writing customer information." << std::endl;
            }
            this->name = name;
            this->contactNumber = contactNumber;
};
        
//Getters for a customer information -> shown on the screen of the app
string customer::getName(){
    return this->name;
};

int customer::getContactNumber(){
    return this->contactNumber;
};

customer::~customer(){

}
