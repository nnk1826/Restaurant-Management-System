#include "cardPayment.h"

cardPayment::cardPayment(std::string customerName, int contactNumber, int tableID, double totalAmount, const std::unordered_map<int, order> &orderList)
    : payment(customerName, contactNumber, tableID, totalAmount, orderList) {}

void cardPayment::generatePaymentID()
{ // Generate a unique payment ID for every customer
    this->paymentID = contactNumber - tableID;
};

bool cardPayment::printBill(const std::vector<menuItem *> &menu)
{
    // Create a unique file name using tableID and current time
    std::stringstream billName;
    std::time_t timeNow = std::time(nullptr);

    billName << "CardBill_" << tableID << "_" << timeNow; // Create a name for the file
    std::ofstream printFile(billName.str());

    // Create a unique payment ID and error handling
    generatePaymentID();

    // Error checking if the file can't be opened
    if (!printFile)
    {
        std::cerr << "Billing file can't be open" << std::endl;
        return false;
    }

    // Content of the Bill
    printFile << "PROJECT 37 DINING RECEIPT" << std::endl;
    printFile << "-------------------------" << std::endl;
    printFile << "Payment Number: " << paymentID << std::endl;
    printFile << "Customer: " << customerName << std::endl;

    // Matching and printing every item in every order object
    printFile << "ORDER ITEMS: " << std::endl;
    for (const auto &[orderID, order] : orderList)
    { // Iterate throught every order items inside orderList
        for (const auto &[itemID, quantity] : orderList[orderID].getOrderItems())
        { // Iterate through every order object to print out

            // Search for the menu item corresponding to the itemID
            auto it = std::find_if(menu.begin(), menu.end(), [&](const menuItem *item)
                                   { return item->getItemID() == itemID; });

            // If the item is found, print the name and quantity
            if (it != menu.end())
            {
                printFile << (*it)->getItemName() << ": " << quantity << "\n";
            }
            else
            {
                printFile << "Item ID: " << itemID << " Quantity: " << quantity << "\n";
            }
        }
    }
    printFile << "-------------------------\n";
    printFile << "TOTAL: $" << totalAmount << "\n";

    // Calculate and print customer discounts
    double discount = returningCustomersDiscount();
    printFile << "Discount: " << totalAmount * discount << "\n";
    printFile << "Payable: $" << totalAmount - (totalAmount * discount) << "\n";
    printFile << "Paid by card\n";

    printFile.close();

    return true;
}

int cardPayment::getPaymentID()
{
    return this->paymentID;
};

double cardPayment::returningCustomersDiscount()
{
    // Method to give 5% discount for returning customers of 3 times or more
    int visitCount = 0;

    std::ifstream customers_info;
    customers_info.open("customersInformation.txt");

    std::string line;

    while (getline(customers_info, line))
    { // While loop to count the number of times a customer visitted
        std::istringstream iss(line);
        std::string storedName;
        int storedContact;

        // Read name and contact number from the file
        if (iss >> storedName >> storedContact)
        {
            // Check if both name and number match
            if (storedName == customerName && storedContact == contactNumber)
            {
                visitCount++;
            }
        }
    }

    if (visitCount >= 3)
    {
        return 0.05;
    }
    else if (visitCount < 3)
    {
        return 0.0;
    }
    return 0;
}