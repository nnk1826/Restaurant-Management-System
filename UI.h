#ifndef UI_H
#define UI_H

#include <iostream>
#include <stack> 

#include "table.h"
#include "reservation.h"
#include "takeaway.h"
#include "order.h"
#include "payment.h"
#include "cashPayment.h"
#include "cardPayment.h"
#include "customer.h"
#include "menuItem.h"
#include "foodItem.h"
#include "veganItem.h"
#include "nonVeganItem.h"
#include "drinkItem.h"
#include "alcFreeDrink.h"
#include "alcoholDrink.h"

enum class pageNavigation{
    MAIN_PAGE,
    DINE_IN_PAGE,
    TAKEAWAY_PAGE,
    RESERVATION_PAGE,
    MENU_EDITOR_PAGE,
};

class UI {
    public:
        //Tracker for page user is on
        static std::stack<pageNavigation> pageHistory;

        //Pages for the program
        void mainPage(std::unordered_map<int,table>& tables, std::vector<menuItem*>& menu, std::unordered_map<int,customer*>& customers,std::unordered_map<int,customer*>& customersTakeaway);
        void dineInPage(std::unordered_map<int,table>& tables, std::vector<menuItem*>& menu,std::unordered_map<int,customer*>& customers,std::unordered_map<int,customer*>& customersTakeaway);
        void takeawayPage(std::unordered_map<int,table>& tables, std::vector<menuItem*>& menu,std::unordered_map<int,customer*>& customers,std::unordered_map<int,customer*>& customersTakeaway);
        void reservationPage(std::unordered_map<int,table>& tables, std::vector<menuItem*>& menu, std::unordered_map<int,customer*>& customers,std::unordered_map<int,customer*>& customersTakeaway);
        void menuEditorPage(std::unordered_map<int,table>& tables, std::vector<menuItem*>& menu, std::unordered_map<int,customer*>& customers,std::unordered_map<int,customer*>& customersTakeaway);

        //Internal functions
        void exitProgram(void);
        void displayMenu(std::vector<menuItem*>& menu);
        void displayTableStatus(const std::unordered_map<int,table>& tables);
        // void checkReservation(void);
        void setCustomertoTable(int tableID,std::unordered_map<int,customer*>& customers,std::unordered_map<int,table>& tables);
        void navigateTo(pageNavigation page, std::unordered_map<int,table>& tables, std::vector<menuItem*>& menu,std::unordered_map<int,customer*>& customers,std::unordered_map<int,customer*>& customersTakeaway);

        //Pages navigation
        void goBack(std::unordered_map<int,table>& tables, std::vector<menuItem*>& menu, std::unordered_map<int,customer*>& customers,std::unordered_map<int,customer*>& customersTakeaway);   
};

#endif