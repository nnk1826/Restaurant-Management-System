#include "takeaway.h"

int takeaway::IDcounter = 1;


takeaway::takeaway()
{
    customerPayment = nullptr;
    takeawayID = takeaway::IDcounter++;
};

bool takeaway::payBill(const std::vector<menuItem *> &menu,  customer* customer)
{
    int paymentMethod;

    double totalAmount = returnTotalAmount(menu);

    std::cout << "Pay by cash(1) or card(2) ? ";
    std::cin >> paymentMethod;
    std::cout << std::endl;

    switch (paymentMethod)
    { // To ask user which method of payment to use
    case 1:
        customerPayment = new cashPayment(customer->getName(), customer->getContactNumber(),0, totalAmount, orderList);
        break;
    case 2:
        customerPayment = new cardPayment(customer->getName(), customer->getContactNumber(),0,totalAmount, orderList);
        break;
    default:
        std::cout << "Invalid choice" << std::endl;
        return false;
    }

    // Checking if printBill() functions correctly
    if (customerPayment->printBill(menu))
    {
        std::cout << "Bill is paid successfully.\n";
        return true;
    }
    else if (!customerPayment->printBill(menu))
    {
        std::cerr << "Bill is not paid.\n";
        return false;
    }
    return false; //Safeguarding
};

bool takeaway::placeOrder(const std::vector<menuItem *> &menu) {
    order newOrder;
    int orderID = takeaway::IDcounter++;
    bool orderLoop = true;

    while (orderLoop) {
        int itemID;
        int quantity;

        std::cout << "Enter menu item ID: ";
        while (!(std::cin >> itemID)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Enter item ID again: ";
        }

        std::cout << "Amount: ";
        while (!(std::cin >> quantity)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid quantity. Enter a valid quantity: ";
        }
        std::cout << "\n";

        // Find the item name using itemID
        auto it = std::find_if(menu.begin(), menu.end(), [itemID](const menuItem *item) {
            return item->getItemID() == itemID;
        });

        if (it != menu.end()) {
            const std::string &itemName = (*it)->getItemName();

            if (newOrder.addToOrder(itemID, quantity, menu)) {
                std::cout << "Added " << quantity << " unit(s) of " << itemName << " successfully.\n";
            } else {
                std::cout << "Item not found in the menu.\n";
            }
        } else {
            std::cout << "Item ID not found.\n";
        }

        int cchoice;
        std::cout << "\nDo you want to:\n(1) Remove the item from order (2) Add more items (3) Exit and submit the order? \n";
        std::cout << "Your choice: ";
        std::cout << std::endl;

        while (!(std::cin >> cchoice) || (cchoice < 1 || cchoice > 3)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid choice. Choose again (1, 2, 3): ";
        }

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
};

double takeaway::returnTotalAmount(const std::vector<menuItem *> &menu)
{
    double totalAmount = 0;

    // Range iterations through the unordered map to calculate the subtotal of each orders and then sum them up
    for (const auto &[orderID, order] : orderList)
    {
        totalAmount += orderList[orderID].returnTotalAmount(menu);
    }
    return totalAmount;
}

void takeaway::displayOrder(const std::vector<menuItem *> &menu)
{
    for (const auto &[orderID, order] : orderList)
    {

        std::cout << "Order ID: " << orderID << std::endl; // Printing out every order ID

        for (const auto &[itemID, quantity] : orderList[orderID].getOrderItems())
        { // Iterate through every order object to print out

            // Search for the menu item corresponding to the itemID
            auto it = std::find_if(menu.begin(), menu.end(), [&](const menuItem *item)
                                   { return item->getItemID() == itemID; });

            // If the item is found, print the name and quantity
            if (it != menu.end())
            {
                std::cout << (*it)->getItemName() << ": " << quantity << std::endl;
            }
            else
            {
                std::cout << "Item ID: " << itemID << " Quantity: " << quantity << std::endl;
            }
        }
    }
};

takeaway::~takeaway()
{
    delete customerPayment;
}