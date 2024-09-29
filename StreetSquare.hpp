//tsofiatouito2@gmail.com

#include <iostream>
#include <SFML/Graphics.hpp>
#include <map>
#include <string>
#include <cmath>
#include "Square.hpp"
#include "Player.hpp"


using namespace std;


class StreetSquare : public Square {

    private:

    Player* owner;                      // Pointer to the street owner
    string streetName;                  // The name of the street (written on the board)
    int baseRentPrice {75};             // The base rent price before house's building
    int rentWithHousePrice {85};        // Rent price with one house
    int rentWithHotelPrice {550};       // Rent price with hotel
    int streetPrice {250};              // The street's price
    int housePrice {100};               // House price
    int hotelPrice {500};               //Hotel price
    int houses {0};                     // Number of houses
    bool hasHotel {false};              // True if a hotel exists on the street

    public:
    string colorGroup;                  // Color group of the street

    // Constructor
    StreetSquare(const std::string& name, int index, sf::FloatRect square_area, const std::string& street, const std::string& color)
        : Square(name, index, square_area), streetName(street), colorGroup(color), owner(nullptr) {}



    //Method that checks if the street has an owner
    Player* get_owner();

    //Set new owner
    void set_owner(Player*);

    //Return the price of the street
    int get_price();

    int get_house_price();

    int get_hotel_price();

    void set_hotel();

    //calaulate and return the rent price as a result of building houses/ hotels
    int calc_rent();

    //Method that checks whether an house can be built
    bool can_build_house(Player* );

    //Method that checks whether an hotel can be built
    bool can_build_hotel(Player*);

    //Promote the amount of the houses in the street after building
    void promote_houses();

    int houses_num();

    int hotel_num();


};

