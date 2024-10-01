//tsofiatouito2@gmail.com
#ifndef SQUARE_HPP
#define SQUARE_HPP


#include <iostream>
#include <SFML/Graphics.hpp>
#include <memory>
#include "UtilitySquare.hpp"
#include "StreetSquare.hpp"
#include "SpecialSquare.hpp"

using namespace std;

class Square {

    public:

    std::string square_type;     //Square type name 
    int index;                   //Index of the slot (0 to 39)
    sf::FloatRect square_area;   //Defines the area on the image for this slot

    Square(const std::string& type, int index, sf::FloatRect square_area) : square_type(type), index(index),square_area(square_area) {};

    virtual ~Square() = default;

    const string get_type(){
        return square_type;
    }

};




class SquareFactory{

    public:
    SquareFactory(){}

    //Create in runtime the asked square
    unique_ptr<Square> create_square(const std::string type,int index ,sf::FloatRect square_area, const std::vector<std::string>& extra_args ){

        if(type == "Street Square"){
            return make_unique<StreetSquare>(type, index, square_area, extra_args[0], extra_args[1]);
        }

        if(type == "Train Square"){
            return make_unique<TrainSquare>(type, index, square_area);
        }

        if(type == "Jail Square"){
            return make_unique<JailSquare>(type, index, square_area);
        }

        if(type == "Start Square"){
            return make_unique<StartSquare>(type, index, square_area);
        }


        if(type == "Go To Jail Square"){
            return make_unique<GoToJailSquare>(type, index, square_area);
        }


        if(type == "Surprise Square"){
            return make_unique<SurpriseSquare>(type, index, square_area);
        }


        if(type == "Tax Square"){
            return make_unique<TaxSquare>(type, index, square_area);
        }


        if(type == "Free Parking Square"){
            return make_unique<FreeParkingSquare>(type, index, square_area);
        }


        if(type == "Company Square Square"){
            return make_unique<CompanySquare>(type, index, square_area);
        }


        std::cout << "Failed in recognize the kind of the square ." << endl;
        return nullptr;

    }

};

#endif
