//tsofiatouito2@gmail.com

#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>
#include <cmath>
#include <memory>
#include "Square.hpp"
#include "Player.hpp"


using namespace std;


class StreetSquare : public Square {

    private:

    shared_ptr<Player> owner;           // Pointer to the street owner
    int baseRentPrice {75};             // The base rent price before house's building
    int rentWithHousePrice {85};        // Rent price with one house
    int rentWithHotelPrice {550};       // Rent price with hotel
    int streetPrice {250};              // The street's price
    int housePrice {100};               // House price
    int hotelPrice {500};               //Hotel price
    bool hasHotel {false};              // True if a hotel exists on the street

    public:
    string streetName;                  // The name of the street (written on the board)
    string colorGroup;                  // Color group of the street

    int houses {0};                     // Number of houses
    // Constructor
    StreetSquare(const std::string& name, int index, sf::FloatRect square_area, const std::string& street, const std::string& color)
        : Square(name, index, square_area), streetName(street), colorGroup(color), owner(nullptr) {}



    //Method that checks if the street has an owner
    shared_ptr<Player> get_owner();

    //Set new owner
    void set_owner(shared_ptr<Player>);

    //Return the price of the street
    int get_price();

    int get_house_price();

    int get_hotel_price();

    void set_hotel();

    //calaulate and return the rent price as a result of building houses/ hotels
    int calc_rent();

    //Method that checks whether an house can be built
    bool can_build_house(shared_ptr<Player> );

    //Method that checks whether an hotel can be built
    bool can_build_hotel(shared_ptr<Player>);

    //Promote the amount of the houses in the street after building
    void promote_houses();

    int houses_num();

    int hotel_num();


};

