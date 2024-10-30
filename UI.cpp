#include "UI.h"

std::stack<pageNavigation> UI::pageHistory;

void UI::mainPage(std::unordered_map<int, table> &tables, std::vector<menuItem *> &menu, std::unordered_map<int, customer *> &customers, std::unordered_map<int, customer *> &customersTakeaway)
{
    system("clear");
    std::cout << "==============================================\n";
    std::cout << " RESTAURANT MANAGEMENT\n";
    std::cout << "1. Dine In\n";
    std::cout << "2. Takeaway\n";
    std::cout << "3. Reservation\n";
    std::cout << "4. Edit Menu\n";
    std::cout << "5. Exit Program\n";
    std::cout << "==============================================\n";

    // Functions to print design stuff
    std::cout << "Choose an option: ";
    int cchoice;
    while (!(std::cin >> cchoice) || cchoice < 1 || cchoice > 5)
    {
        std::cin.clear();                                                   // Clear the error
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Remove invalid input
        std::cout << "Invalid input. Please choose again: ";
    }
    std::cout << "\n";

    // Options of dine in, takeaway, or make a reservation
    switch (cchoice)
    {
    case 1:
        dineInPage(tables, menu, customers, customersTakeaway);
        break;
    case 2:
        takeawayPage(tables, menu, customers, customersTakeaway);
        break;
    case 3:
        reservationPage(tables, menu, customers, customersTakeaway);
        break;
    case 4:
        menuEditorPage(tables, menu, customers, customersTakeaway);
        break;
    case 5:
        exitProgram();
        break;
    default:
        std::cout << "Invalid choice\n";
        break;
    }
}

void UI::dineInPage(std::unordered_map<int, table> &tables, std::vector<menuItem *> &menu, std::unordered_map<int, customer *> &customers, std::unordered_map<int, customer *> &customersTakeaway)
{
    // Assign the information the current page the user is on
    pageHistory.push(pageNavigation::DINE_IN_PAGE);

    int tableSelection;
    int cchoice;
    bool exitPage = false;

    // While loop until user leaves
    while (!exitPage)
    {
        std::cout << "\n==============================================\n";
        displayTableStatus(tables);
        std::cout << "Choose a table: ";
        while (!(std::cin >> tableSelection) || (tableSelection < 0) || (tableSelection > 12))
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Enter a valid choice: ";
        }
        std::cout << "\n";

        std::cout << "Table Options: \n";
        std::cout << "1. Display Menu\n";
        std::cout << "2. Add item\n";
        std::cout << "3. Display current Order\n";
        std::cout << "4. Pay Bill\n";
        std::cout << "5. Reset Table\n";
        std::cout << "6. Return to main page\n";
        std::cout << "7. Exit Program\n";
        std::cout << "-----------------------------------------------\n";
        std::cout << "Choose an option: ";

        while (!(std::cin >> cchoice) || (cchoice < 1) || (cchoice > 7))
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Enter a valid choice: ";
        }
        std::cout << "\n";

        table &currentTable = tables.at(tableSelection);
        switch (cchoice)
        {
        case 1:
            displayMenu(menu);
            break;
        case 2:
            currentTable.placeOrder(menu);                         // Place order for the table
            setCustomertoTable(tableSelection, customers, tables); // Assign the customer to the table
            break;
        case 3:
            currentTable.displayOrder(menu);
            break;
        case 4:
            if (!currentTable.getTableAvailability())
            {
                if (currentTable.payBill(menu))
                {
                    currentTable.resetTable(); // Reset table
                    if (customers.find(tableSelection) != customers.end())
                    {
                        customers.erase(tableSelection); // Clear up memory
                    }
                    break;
                }
                else
                {
                    break;
                }
            }
            else
            {
                std::cout << "Nobody is eating here." << std::endl;
                break;
            }
        case 5:
            if (!(tables[tableSelection].getTableAvailability()))
            { // Checking if the table is occupied
                currentTable.resetTable();

                delete customers[tableSelection]; // Memory clean
                customers.erase(tableSelection);
            }
            else
            {
                std::cout << "There's no one sitting here!!\n"; // LOL
            }
            break;
        case 6:
            exitPage = true;
            navigateTo(pageNavigation::MAIN_PAGE, tables, menu, customers, customersTakeaway);
            break;
        case 7:
            exitProgram();
            exitPage = true;
            break;
        default:
            std::cerr << "This should never be reached\n"; // PLACEHOLDER CASE SHOULD NEVER BE REACHED
            break;
        }
    }
}

void UI::takeawayPage(std::unordered_map<int, table> &tables, std::vector<menuItem *> &menu, std::unordered_map<int, customer *> &customers, std::unordered_map<int, customer *> &customersTakeaway)
{
    pageHistory.push(pageNavigation::TAKEAWAY_PAGE); // Page tracker

    std::cout << "\n==============================================\n";

    std::string name;
    int contact;

    // Demurely ask for information from customers
    std::cout << "Customer's name: ";
    std::cin >> name;
    std::cout << "Contact: ";

    while (!(std::cin >> contact)) // Input validation
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input. Enter a valid choice: ";
    }
    std::cout << "\n";

    customer *newCustomer = new customer(name, contact);

    // Temporarily stores customer in a container
    customersTakeaway[takeaway::IDcounter] = newCustomer; // static ID track

    takeaway *newTakeaway = new takeaway();
    int cchoice;

    bool exitPage = false; // To keep opening the current page in case of displaying functions
    while (!exitPage)
    {
        std::cout << "Takeaway Options: \n";
        std::cout << "1. Display Menu\n";
        std::cout << "2. Add item\n";
        std::cout << "3. Display current Order\n";
        std::cout << "4. Pay Bill\n";
        std::cout << "5. Return to main page\n";
        std::cout << "6. Exit Program\n";
        std::cout << "-----------------------------------------------\n";
        std::cout << "Choose an option: ";

        while (!(std::cin >> cchoice) || (cchoice < 1) || (cchoice > 6)) // Input validation
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Enter a valid choice: ";
        }
        std::cout << "\n";

        switch (cchoice)
        {
        case 1:
            displayMenu(menu);
            break;
        case 2:
            newTakeaway->placeOrder(menu);
            break;
        case 3:
            newTakeaway->displayOrder(menu);
            break;
        case 4:
            if (newTakeaway->payBill(menu, newCustomer))
            {

                delete customersTakeaway[takeaway::IDcounter];
                customersTakeaway.erase(takeaway::IDcounter); // DELETE MEMORY

                break;
            }
            else
            {
                break;
            };
        case 5:
            exitPage = true;
            navigateTo(pageNavigation::MAIN_PAGE, tables, menu, customers, customersTakeaway);
            break;
        case 6:
            exitPage = true;
            exitProgram();
            break;
        default:
            std::cerr << "THIS SHOULDN'T BE PRINTED OUT PERIOD!\n";
            break;
        }
    }
}

void UI::reservationPage(std::unordered_map<int, table> &tables, std::vector<menuItem *> &menu,
                         std::unordered_map<int, customer *> &customers,
                         std::unordered_map<int, customer *> &customersTakeaway)
{
    pageHistory.push(pageNavigation::RESERVATION_PAGE);

    bool exitPage = false;
    while (!exitPage)
    {
        std::cout << "\n==============================================\n";
        std::cout << "1. Make Reservation \n";
        std::cout << "2. Check Reservation \n";
        std::cout << "3. Exit Program\n";
        std::cout << "-----------------------------------------------\n";
        std::cout << "Choose an option: ";

        std::string choice;
        std::cin >> choice;
        std::cout << std::endl;

        if (choice == "1")
        {
            std::string name;
            int capacity;
            std::string date_input;
            std::string time_input;

            std::cout << "Enter customer's name: ";
            std::cin >> name;

            std::cout << "Enter total capacity: ";
            while (!(std::cin >> capacity))
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid input. Enter a valid capacity: ";
            }

            while (true)
            {
                std::cout << "Enter date (format: YYYY-MM-DD): ";
                std::cin >> date_input;

                std::cout << "Enter time (format: HH:MM:SS): ";
                std::cin >> time_input;
                std::cout << std::endl;

                // Combine date and time into a single string
                std::string date_time = date_input + " " + time_input;

                // Validate input format
                struct tm tm
                {
                };
                if (strptime(date_time.c_str(), "%Y-%m-%d %H:%M:%S", &tm) == nullptr)
                {
                    std::cout << "Invalid format. Please enter the date in the format: YYYY-MM-DD and time in the format: HH:MM:SS" << std::endl;
                }
                else
                {
                    static double id = 1; // Initialize ID counter
                    reservation *newReservation = new reservation(name, id++, capacity, time_input, date_input);
                    delete newReservation;
                    // Consider storing newReservation somewhere or managing its lifetime
                    break;
                }
            }
        }
        else if (choice == "2")
        {
            std::string cname;
            std::cout << "Enter Customer's Name: ";
            std::cin >> cname;

            // Create a temporary reservation object to call the bookingConfirmation method
            reservation tempReservation(cname, 0, 0, "", "");         // Dummy instance since you're only checking the reservation
            bool result = tempReservation.bookingConfirmation(cname); // Call the method from the instance

            if (result)
            {
                dineInPage(tables, menu, customers, customersTakeaway);
                break;
            }
            else
            {
                std::cout << "No reservation has been made under this name.\n";
            }
        }
        else if (choice == "3")
        {
            exitPage = true;
            exitProgram();
            break;
        }
        else
        {
            std::cout << "Invalid choice. Please input a valid choice.\n";
        }
    }
}

void UI::menuEditorPage(std::unordered_map<int, table> &tables, std::vector<menuItem *> &menu, std::unordered_map<int, customer *> &customers, std::unordered_map<int, customer *> &customersTakeaway)
{
    pageHistory.push(pageNavigation::MENU_EDITOR_PAGE); // Page tracker
    std::cout << "\n==============================================\n";

    int cchoice;
    bool exitPage = false;

    while (!exitPage)
    {
        std::size_t itemID;
        std::string itemName;
        double price;

        std::cout << "1. Edit Item \n";
        std::cout << "2. Remove Item\n";
        std::cout << "3. Return to main page\n";
        std::cout << "4. Exit program\n";

        std::cout << "-----------------------------------------------\n";
        std::cout << "Choose an option: ";

        // Input validation
        while (!(std::cin >> cchoice) || (cchoice < 1) || (cchoice > 4))
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Enter a valid choice: ";
        }

        std::cout << "\n";
        switch (cchoice)
        {
        case 1:
            displayMenu(menu);
            std::cout << "\n";

            std::cout << "Enter item ID: ";
            while (!(std::cin >> itemID) || (itemID < 0) || itemID > menu.size())
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid input. Enter a valid item ID: ";
            }
            std::cout << "\n";
            std::cout << "Enter new item name: ";
            while (std::cin >> itemName && itemName.empty())
            {
                std::cout << "Item name cannot be empty. Enter a valid item name: ";
            }

            std::cout << "\n";
            std::cout << "Enter new price: ";
            while (true)
            {
                std::cin >> price;

                if (std::cin.fail() || price <= 0)
                {
                    std::cin.clear();                                                   // Reset the error state
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
                    std::cout << "Invalid input. Enter a valid price: ";
                }
                else
                {
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear any leftover characters in the buffer
                    break;                                                              // Valid input received
                }
            }

            std::cout << std::endl;

            menuItem::updateItem(menu, itemID, itemName, price);
            break;
        case 2:
            displayMenu(menu);

            std::cout << "Enter item ID: ";
            while (!(std::cin >> itemID) || (itemID < 0 || itemID >= menu.size()))
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid input. Enter a valid item ID: ";
            }
            menuItem::deleteItem(menu, itemID);
            std::cout << std::endl;
            break;
        case 3:
            exitPage = true;
            navigateTo(pageNavigation::MAIN_PAGE, tables, menu, customers, customersTakeaway);
            break;
        case 4:
            exitPage = true;
            exitProgram();
            break;
        default:
            std::cout << "This should never be printed\n";
            break;
        }
    }
}

// To go to assigned pages
void UI::navigateTo(pageNavigation page, std::unordered_map<int, table> &tables, std::vector<menuItem *> &menu, std::unordered_map<int, customer *> &customers, std::unordered_map<int, customer *> &customersTakeaway)
{
    switch (page)
    {
    case pageNavigation::MAIN_PAGE:
        mainPage(tables, menu, customers, customersTakeaway);
        break;
    case pageNavigation::DINE_IN_PAGE:
        dineInPage(tables, menu, customers, customersTakeaway);
        break;
    case pageNavigation::RESERVATION_PAGE:
        reservationPage(tables, menu, customers, customersTakeaway);
        break;
    case pageNavigation::MENU_EDITOR_PAGE:
        menuEditorPage(tables, menu, customers, customersTakeaway);
        break;
    case pageNavigation::TAKEAWAY_PAGE:
        takeawayPage(tables, menu, customers, customersTakeaway);
        break;
    }
}

void UI::displayTableStatus(const std::unordered_map<int, table> &tables)
{
    for (int i = 1; i < 5; i++)
    {
        const table &currentTable = tables.at(i);
        std::cout << "Table " << i << ": ";
        std::cout << (currentTable.getTableAvailability() == 1 ? "Available" : "Occupied") << ", ";
        std::cout << "Capacity: " << currentTable.getTableCapacity();
        std::cout << "\n";
    } // Table with capacity 2

    for (int i = 5; i < 9; i++)
    {
        const table &currentTable = tables.at(i);
        std::cout << "Table " << i << ": ";
        std::cout << (currentTable.getTableAvailability() == 1 ? "Available" : "Occupied") << ", ";
        std::cout << "Capacity: " << currentTable.getTableCapacity();
        std::cout << "\n";
    } // Table with capacity 4

    for (int i = 9; i < 11; i++)
    {
        const table &currentTable = tables.at(i);
        std::cout << "Table " << i << ": ";
        std::cout << (currentTable.getTableAvailability() == 1 ? "Available" : "Occupied") << ", ";
        std::cout << "Capacity: " << currentTable.getTableCapacity();
        std::cout << "\n";
    } // Table with capacity 6

    for (int i = 11; i < 13; i++)
    {
        const table &currentTable = tables.at(i);
        std::cout << "Table " << i << ": ";
        std::cout << (currentTable.getTableAvailability() == 1 ? "Available" : "Occupied") << ", ";
        std::cout << "Capacity: " << currentTable.getTableCapacity();
        std::cout << "\n";
    } // Table with capacity 8
}

void UI::exitProgram()
{
    std::cout << "Thanks for visiting. See you later!\n";
    std::cout << "Developed by Nhat Khang, Phi Hoang, Jaishv Hirenbhai\n";
    exit(0);
}

void UI::goBack(std::unordered_map<int, table> &tables, std::vector<menuItem *> &menu, std::unordered_map<int, customer *> &customers, std::unordered_map<int, customer *> &customersTakeaway)
{
    if (!pageHistory.empty())
    {
        pageNavigation previousPage = pageHistory.top();
        pageHistory.pop();                                                    // Pop to the previous page
        navigateTo(previousPage, tables, menu, customers, customersTakeaway); // Navigate to that page
    }
    else
    {
        std::cout << "You are already on the main page!" << std::endl;
        mainPage(tables, menu, customers, customersTakeaway);
    }
}

void UI::displayMenu(std::vector<menuItem *> &menu)
{
    std::cout << "\n================= MENU =================\n";
    for (const auto &menuItem : menu)
    {
        if (menuItem != nullptr)
        {
            menuItem->getDescription(); // Display the description of the menu item
        }
    }
    std::cout << "=========================================\n";
}

void UI::setCustomertoTable(int tableID, std::unordered_map<int, customer *> &customers, std::unordered_map<int, table> &tables)
{
    // Check if the table is available
    if (tables[tableID].getTableAvailability())
    {
        std::string name;
        int contact;

        std::cout << "Enter customer's name: ";
        std::cin >> name;
        std::cout << "Enter contact Number: ";
        while (!(std::cin >> contact))
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Enter a valid number: ";
        }

        customer *newCustomer = new customer(name, contact);
        customers[tableID] = newCustomer;          // Attach customers to a specific table
        tables[tableID].reserveTable(newCustomer); // Add the customer object to table
    }
    else
    {
        std::cout << "Update order on table " << tableID << ".\n";
    }

    // Set them to table using a table ID
    //  customer* newCustomer = new customer(name,contact);
    //  customers[tableID] = newCustomer;//Attach customers to a specific table
    //  tables[tableID].reserveTable(newCustomer);//Add the customer object to table
}
