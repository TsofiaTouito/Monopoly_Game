//tsofiatouito2@gmail.com 


#include "StreetSquare.hpp"




Player* StreetSquare::get_owner(){
    return this->owner;
}



void StreetSquare::set_owner(Player* newOwner){
    this->owner = newOwner;
}



//calaulate the rent price as a result of building houses/ hotels
int StreetSquare::calc_rent(){

    //If the street is empty from assets, pay the base rent
    if(houses == 0){
        return this->baseRentPrice;
    }

    //If there is no hotel in the street
    if(!this->hasHotel){
        double price = (this->rentWithHousePrice)*pow(2, houses -1);
    }

    //Exist hotel in the street
    else{
        return this->rentWithHotelPrice;
    }
}


//Abilitiy to buy a house in the street aspect
bool StreetSquare::can_build_house(Player* player){
        return (this->owner == player) && this->houses < 4 && !this->hasHotel;
    }



bool StreetSquare::can_build_hotel(Player* player){
    return (this->owner == player) && (this->houses == 4);
}
