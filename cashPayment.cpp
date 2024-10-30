#include "cashPayment.h"

cashPayment::cashPayment(std::string customerName, int contactNumber, int tableID, double totalAmount, const std::unordered_map<int, order> &orderList)
    : payment(customerName, contactNumber, tableID, totalAmount, orderList) {}

void cashPayment::generatePaymentID()
{
    paymentID = contactNumber - tableID;
}

bool cashPayment::printBill(const std::vector<menuItem*> &menu)
{
    std::stringstream billName;
    std::time_t timeNow = std::time(nullptr);

    billName << "CashBill_" << tableID << "_" << timeNow << ".txt";
    std::ofstream printFile(billName.str());

    if (!printFile)
    {
        std::cerr << "Billing file can't be opened" << std::endl;
        return false;
    }

    generatePaymentID();

    printFile << "PROJECT 37 DINING RECEIPT\n";
    printFile << "-------------------------\n";
    printFile << "Payment Number: " << paymentID << "\n";
    printFile << "Customer: " << customerName << "\n\n";
    printFile << "ORDER ITEMS:\n";

    for (const auto &[orderID, order] : orderList)
    {
        for (const auto &[itemID, quantity] : orderList[orderID].getOrderItems())
        {
            auto it = std::find_if(menu.begin(), menu.end(), [&](const menuItem *item)
                                   { return item->getItemID() == itemID; });

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
    printFile << std::fixed << std::setprecision(2);
    printFile << "TOTAL: $" << totalAmount << "\n";

    double discountRate = returningCustomersDiscount();
    double discountAmount = totalAmount * discountRate;
    printFile << "Discount: $" << discountAmount << "\n";
    printFile << "Payable: $" << (totalAmount - discountAmount) << "\n";
    printFile << "Paid by cash\n";

    return true;
}

int cashPayment::getPaymentID()
{
    return paymentID;
}

double cashPayment::returningCustomersDiscount()
{
    std::ifstream customers_info("customersInformation.txt");
    if (!customers_info)
    {
        std::cerr << "Unable to open customers information file" << std::endl;
        return 0.0;
    }

    int visitCount = 0;
    std::string line;
    while (std::getline(customers_info, line))
    {
        std::istringstream iss(line);
        std::string storedName;
        int storedContact;

        if (iss >> storedName >> storedContact)
        {
            if (storedName == customerName && storedContact == contactNumber)
            {
                visitCount++;
                if (visitCount >= 3)
                {
                    customers_info.close();
                    return 0.05;
                }
            }
        }
    }

    customers_info.close();
    return 0.0;
}