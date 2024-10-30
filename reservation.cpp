#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <ctime>
#include <cctype>
#include "reservation.h"

using namespace std;

// Constructor
reservation::reservation(const std::string& name, double id, int capacity, std::string time, std::string date)
    : reservationID(id), reservationCapacity(capacity), reserverName(name), time(time), date(date) {
    
    // Convert customer name to UPPERCASE to eliminate syntax mismatching when searching for returning customers.
    for (char& c : reserverName) {
        c = std::toupper(c);  // Apply toupper to each character
    }

    // Opening the text file database to write information into it
    ofstream reservation_Info("reservationInformation.txt", ios::app); // Open the text file in appending mode without overwriting it
    if (reservation_Info.is_open()) {
        reservation_Info << reserverName << " " << reservationID << " " << reservationCapacity << " " 
                         << date << " " << time << "\n";  // Append the customer's info
        reservation_Info.close();
    } else {
        cerr << "Error: Could not open the file for writing.\n";
    }
    this->reserverName = name;
    this->reservationID = id;
    this->reservationCapacity = capacity;
    this->time = time;
    this->date = date;
}

bool reservation::bookingConfirmation(const std::string& name) {
    std::ifstream file("reservationInformation.txt");  // Open the file for reading
    if (!file.is_open()) {
        std::cerr << "Error: Could not open the file for reading.\n";
        return false;
    }

    std::string line;
    std::string upperName = name;
    for (char& c : upperName) {
        c = std::toupper(c);
    }

    bool found = false;

    while (std::getline(file, line)) {  // Read the file line by line
        std::istringstream iss(line);
        std::string reserverName;
        iss >> reserverName;  // Extract only the name part

        // Convert extracted name to uppercase for comparison
        for (char& c : reserverName) {
            c = std::toupper(c);
        }

        if (reserverName == upperName) {  // Compare only names
            std::cout << "Reservation confirmed for " << name << ".\n";
            found = true;
            break;  // Exit loop once found
        }
    }

    file.close();  // Close the file after reading

    if (!found) {
        std::cout << "Reservation not found for " << name << ".\n";
    }

    return found;  // Return true if the name was found and confirmed
}