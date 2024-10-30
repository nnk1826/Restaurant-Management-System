#include "table.h"

table::table() : tableID(0), tableCapacity(0), tableAvailability(true) {};

table::table(int ID, int capacity) : tableID(ID), tableCapacity(capacity), tableAvailability(true)
{
    customerPayment = nullptr;
};

bool table::payBill(const std::vector<menuItem *> &menu)
{
    int paymentMethod;
    double totalAmount = returnTotalAmount(menu);

    std::cout << "Pay by cash(1) or card(2) ? ";
    while (!(std::cin >> paymentMethod) || (paymentMethod < 1) || (paymentMethod > 2))
    {
        std::cin.clear();                                                   // Clear the error
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Remove invalid input
        std::cout << "Invalid input. Enter again: ";
    }
    std::cout << "\n";

    switch (paymentMethod)
    {
    case 1:
        customerPayment = new cashPayment(customerAssigned->getName(), customerAssigned->getContactNumber(), tableID, totalAmount, orderList);
        break;
    case 2:
        customerPayment = new cardPayment(customerAssigned->getName(), customerAssigned->getContactNumber(), tableID, totalAmount, orderList);
        break;
    default:
        std::cout << "Invalid choice" << std::endl;
        return false; // Return false for invalid payment method
    }

    // Store the result of printBill and use it once
    bool billPrinted = customerPayment->printBill(menu);

    if (billPrinted)
    {
        std::cout << "Bill is paid successfully.\n";
        return true;
    }
    else
    {
        std::cerr << "Bill is not paid.\n";
        return false;
    }
}

bool table::placeOrder(const std::vector<menuItem *> &menu)
{ // Methods that instantiate an order object and allow user to order.
    // Create a new order item every time initated and its orderID;
    order newOrder;

    // Create an order ID
    int orderID;
    if (orderList.empty())
    {
        orderID = 1; // For first ever order at that table
    }
    else
    {
        orderID = orderList.size() + 1; // For any order
    }

    // Create a prompt to ask for new item until the customer say stop
    bool orderLoop = true;

    while (orderLoop)
    {
        // For customer to order each item
        int itemID;
        int quantity;

        // Input validation - prevent invalid input types
        std::cout << "\n---Add Item---\n";
        std::cout << "Enter menu item ID: ";
        while (!(std::cin >> itemID))
        {
            std::cin.clear();                                                   // Clear the error
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Remove invalid input
            std::cout << "Invalid input. Enter item ID again: ";
        }

        // Input validation - prevent invalid input types
        std::cout << "Amount: ";
        while (!(std::cin >> quantity) || quantity < 0)
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid quantity. Enter a valid quantity: ";
        }
        std::cout << "\n";

        // Find the item name using itemID
        auto it = std::find_if(menu.begin(), menu.end(), [itemID](const menuItem *item)
                               { return item->getItemID() == itemID; });

        if (it != menu.end())
        {
            const std::string &itemName = (*it)->getItemName();

            if (newOrder.addToOrder(itemID, quantity, menu))
            {
                std::cout << "Added " << quantity << " unit(s) of " << itemName << " successfully.\n";
            }
            else
            {
                std::cout << "Item not found in the menu.\n";
            }
        }
        else
        {
            std::cout << "Item ID not found.\n";
        }

        int cchoice;
        std::cout << "\nDo you want to: \n(1) Remove the item from order (2) Add more items (3) Exit and submit the order? \n";
        std::cout << "Your choice: ";

        while (!(std::cin >> cchoice) || (cchoice < 1 || cchoice > 3))
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid choice. Choose again (1, 2, 3): ";
        }
        std::cout << "\n";

        // Different proceedings dependent on the customer's choice
        switch (cchoice)
        {
        case 1:
        { // Wrap in a block
            int removeQuantity;
            std::cout << "How many to remove? ";
            while (!(std::cin >> removeQuantity) || removeQuantity < 0)
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid input. Enter a valid amount to remove: ";
            }
            std::cout << "\n";

            auto it = std::find_if(menu.begin(), menu.end(), [itemID](const menuItem *item)
                                   { return item->getItemID() == itemID; });

            if (it != menu.end())
            {
                const std::string &itemName = (*it)->getItemName();

                if (newOrder.removeFromOrder(itemID, removeQuantity))
                {
                    std::cout << "Removed " << removeQuantity << " unit(s) of " << itemName << " successfully.\n";
                }
                else
                {
                    std::cout << "Unsuccessful Remove.\n";
                }
            }
            else
            {
                std::cout << "Item ID not found.\n";
            }
            break;
        }
        case 2:
            break;
        case 3:
            orderLoop = false;
            break;
        default:
            break;
        }
    }

    orderList[orderID] = newOrder;
    return true;
}

double table::returnTotalAmount(const std::vector<menuItem *> &menu)
{
    double totalAmount = 0;

    // Range iterations through the unordered map to calculate the subtotal of each orders and then sum them up
    for (const auto &[orderID, order] : orderList)
    {
        totalAmount += orderList[orderID].returnTotalAmount(menu);
    }
    return totalAmount;
}

bool table::checkAvailability(int capacity)
{
    if ((capacity <= this->getTableCapacity()) && this->getTableAvailability())
    { // Has to be big enough and available at the same time
        return true;
    }
    else
    {
        return false;
    }
}; // Check if the table is available for the required amount of people

void table::markAvailable()
{
    this->tableAvailability = true;
}; // Empty the availability status

void table::reserveTable(customer *customer)
{
    this->customerAssigned = customer;
    tableAvailability = false;
}; // Reserve a table for a customer

void table::displayOrder(const std::vector<menuItem *> &menu)
{
    for (const auto &[orderID, order] : orderList)
    {

        std::cout << "Order Number: " << orderID << "\n"; // Printing out every order ID

        for (const auto &[itemID, quantity] : orderList[orderID].getOrderItems())
        { // Iterate through every order object to print out

            // Search for the menu item corresponding to the itemID
            auto it = std::find_if(menu.begin(), menu.end(), [itemID](const menuItem *item)
                                   { return item->getItemID() == itemID; });

            // If the item is found, print the name and quantity
            if (it != menu.end())
            {
                std::cout << (*it)->getItemName() << ": " << quantity << "\n";
            }
            else
            {
                std::cout << "Item ID: " << itemID << " Quantity: " << quantity << std::endl;
            }
        }
    }
}; // Display the whole order list

int table::getTableID() const
{
    return this->tableID;
};

int table::getTableCapacity() const
{
    return this->tableCapacity;
};

bool table::getTableAvailability() const
{
    return this->tableAvailability;
};

void table::setCustomer(customer *customer)
{
    this->customerAssigned = customer;
}

void table::resetTable()
{
    orderList.clear();      // Clear the list of orders
    markAvailable();        // Set to available
    delete customerPayment; // Reset the pointer of payment method
    delete customerAssigned;
}

table::~table()
{
}