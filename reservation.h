#ifndef RESERVATION_H
#define RESERVATION_H

#include <iostream>
#include <string>
#include <vector>

class reservation {
protected:
    double reservationID;
    int reservationCapacity;
    std::string reserverName;
    std::string time;
    std::string date;

public:
    // Constructor
    reservation(const std::string& name, double id, int capacity, std::string time, std::string date);

    // Booking confirmation method
    bool bookingConfirmation(const std::string& name);
    ~reservation() = default;
};

#endif
