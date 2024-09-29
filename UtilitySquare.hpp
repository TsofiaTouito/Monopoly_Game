// tsofiatouito2@gmail.com
#ifndef UTILITYSQUARE_HPP
#define UTILITYSQUARE_HPP



#include <iostream>
#include <SFML/Graphics.hpp>
#include <map>
#include <string>
#include "Square.hpp"
#include "Player.hpp"



using namespace std;



class TrainSquare : public Square{

    private:

    Player* owner;
    int price {200} ;       //The train price


    public:
    TrainSquare(const std::string& name, int index, sf::FloatRect square_area) : Square(name, index,square_area ), owner(nullptr) {};



    Player* get_owner(){
        return this->owner;
    }



    void set_owner(Player* newOwner){
        this->owner = newOwner;
    }


    /*Calculate the rent price recpectively to the number of trains the owner have:
    One train = 50 , two trains = 100, three trains = 150, four trains = 200*/
    int calc_rent(Player* player){

        int res = player->train_num() * 50;   
        return res;
    }

    //Return the train price
    int get_price(){
        return this->price;
    }

};







class CompanySquare : public Square{   //For water & electric company square

    private:

    Player* owner;
    int companyPrice {150};    //The company price

    public:
    CompanySquare(const std::string& name, int index, sf::FloatRect square_area) : Square(name, index,square_area), owner(nullptr) {};

    void set_owner(Player* player){
        this->owner = player;
    }

    Player* get_owner(){
        return this->owner;
    }

    int get_price(){
        return this->companyPrice;
    }
    

};




class StartSquare : public Square{

    public:
    StartSquare(const std::string& name, int index, sf::FloatRect square_area) : Square(name, index,square_area ){};

};





class GoToJailSquare : public Square{  
    
    public:
    GoToJailSquare(const std::string& name, int index, sf::FloatRect square_area) : Square(name, index,square_area){};

};




class JailSquare : public Square{

    private:

    /*Key : is a pointer to the player object.
      Value : the number of turn the player in jail < 4*/
    map<Player*, int> playersInJail;  


    public:
    JailSquare(const std::string& name, int index, sf::FloatRect square_area) : Square(name, index,square_area ){};

};



class TaxSquare : public Square{

    private:
    int taxPrice {100};

    public:
    TaxSquare(const std::string& name, int index, sf::FloatRect square_area) : Square(name, index,square_area ){};

    int get_tax(){
        return this->taxPrice;
    }


};




class FreeParkingSquare : public Square{

    public:
    FreeParkingSquare(const std::string& name, int index, sf::FloatRect square_area) : Square(name, index,square_area ){};

};

#endif
