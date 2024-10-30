#include "UI.h"

#include <iostream>
#include <stdlib.h>
#include <stdio.h> 
#include <vector>
#include <limits>

using namespace std;

int main(){
    //Initialize UI
    UI programUI;
    
    //Initializing a data member, tables, menu and customers
    std::unordered_map<int,table> tables;
    std::unordered_map<int,customer*> customers;
    std::unordered_map<int,customer*> customersTakeaway;
    std::vector<menuItem*> menu;

    //Make tables
    for (int i = 1; i < 5; i++){
        tables[i] = table(i, 2);
    }//Table with capacity 2

    for(int i = 5; i < 9; i++){
        tables[i] = table(i,4);
    }//Table with capacity 4

    for(int i = 9; i < 11 ; i++){
        tables[i] = table(i,6);
    }//Table with capacity 6

    for (int i = 11; i <13; i++){
        tables[i] = table(i,8);
    }//Table with capacity 8

    //Menu
    // Create Non-Vegan Food items
    menuItem::createItem(menu, new nonVeganItem("Pho Bo", 1, 12.99, "Mild"));
    menuItem::createItem(menu, new nonVeganItem("Chicken Biryani", 2, 10.99, "Mild"));
    menuItem::createItem(menu, new nonVeganItem("Pad Thai with Shrimp", 3, 11.99, "Medium"));
    menuItem::createItem(menu, new nonVeganItem("Beef Rendang", 4, 14.99, "Medium"));
    menuItem::createItem(menu, new nonVeganItem("Korean BBQ Short Ribs", 5, 15.99, "Medium"));
    menuItem::createItem(menu, new nonVeganItem("Chicken Satay", 6, 9.99, "Medium"));
    menuItem::createItem(menu, new nonVeganItem("Peking Duck", 7, 18.99, "Mild"));
    menuItem::createItem(menu, new nonVeganItem("Malaysian Laksa", 8, 13.99, "Medium"));

    // Create Vegan Food items
    menuItem::createItem(menu, new veganItem("Tofu Banh Mi", 9, 8.99, "Mild"));
    menuItem::createItem(menu, new veganItem("Vegetable Biryani", 10, 9.99, "Spicy"));
    menuItem::createItem(menu, new veganItem("Vegan Pad Thai", 11, 9.99, "Medium"));
    menuItem::createItem(menu, new veganItem("Vegan Pho", 12, 10.99, "Mild"));
    menuItem::createItem(menu, new veganItem("Indonesian Gado-Gado", 13, 8.99, "Mild"));
    menuItem::createItem(menu, new veganItem("Stir-fried Bok Choy and Mushrooms", 14, 8.99, "Mild"));
    menuItem::createItem(menu, new veganItem("Thai Green Curry (Vegetable)", 15, 9.99, "Spicy"));

    // Create Alcoholic Drinks
    menuItem::createItem(menu, new alcoholDrink("Vietnamese Mojito", 16, 7.99, 0.0f, {"White rum", "Mint", "Lime juice", "Soda water"}));
    menuItem::createItem(menu, new alcoholDrink("Thai Basil Margarita", 17, 8.99, 0.0, {"Tequila", "Thai basil", "Lime juice", "Triple sec"}));
    menuItem::createItem(menu, new alcoholDrink("Indian Spiced Old Fashioned", 18, 9.99, 0.0, {"Bourbon", "Indian chai syrup", "Bitters"}));
    menuItem::createItem(menu, new alcoholDrink("Lychee Martini", 19, 8.99, 0.0, {"Vodka", "Lychee liqueur", "Lychee juice"}));
    menuItem::createItem(menu, new alcoholDrink("Singapore Sling", 20, 9.99, 0.0, {"Gin", "Cherry brandy", "Pineapple juice"}));
    menuItem::createItem(menu, new alcoholDrink("Mango Mai Tai", 21, 8.99, 0.0, {"Rum", "Mango puree", "Lime juice", "Orange liqueur"}));
    menuItem::createItem(menu, new alcoholDrink("Lemongrass Gin & Tonic", 22, 7.99, 0.0, {"Gin", "Lemongrass", "Tonic water"}));
    menuItem::createItem(menu, new alcoholDrink("Asian Pear Saketini", 23, 9.99, 0.0, {"Sake", "Asian pear juice", "Vodka"}));
    menuItem::createItem(menu, new alcoholDrink("Pineapple Whiskey Sour", 24, 8.99, 0.0, {"Whiskey", "Pineapple juice", "Lemon juice", "Egg white"}));

    // Create Non-Alcoholic Drinks
    menuItem::createItem(menu, new alcFreeDrink("Thai Iced Tea", 25, 4.99, 0.0, {"Black tea", "Condensed milk", "Spices"}));
    menuItem::createItem(menu, new alcFreeDrink("Coconut Water Lemonade", 26, 4.99, 0.0, {"Coconut water", "Lemon juice", "Sugar"}));
    menuItem::createItem(menu, new alcFreeDrink("Vietnamese Iced Coffee", 27, 4.99, 0.0, {"Coffee", "Condensed milk", "Ice"}));
    menuItem::createItem(menu, new alcFreeDrink("Ginger Lemon Soda", 28, 3.99, 0.0, {"Ginger", "Lemon", "Soda water"}));
    menuItem::createItem(menu, new alcFreeDrink("Lemongrass & Mint Cooler", 29, 4.99, 0.0, {"Lemongrass", "Mint", "Lime", "Soda"}));
    menuItem::createItem(menu, new alcFreeDrink("Tamarind Soda", 30, 3.99, 0.0, {"Tamarind", "Lime", "Soda water"}));

    //Main program flow
    //Options choosing
    programUI.mainPage(tables,menu,customers,customersTakeaway);
    return 0;
}