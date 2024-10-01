//tsofiatouito2@gmail.com 


#include "StreetSquare.hpp"




shared_ptr<Player> StreetSquare::get_owner(){
    return this->owner;
}



void StreetSquare::set_owner(shared_ptr<Player> newOwner){
    this->owner = newOwner;
}




int StreetSquare::get_price(){
    return this->streetPrice;
}

int StreetSquare::get_house_price(){
    return this->housePrice;
}

int StreetSquare::get_hotel_price(){
    return this->hotelPrice;
}

void StreetSquare::set_hotel(){
    this->hasHotel = true;
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
bool StreetSquare::can_build_house(shared_ptr<Player> player){
        return (this->owner == player) && this->houses < 4 && !this->hasHotel;
    }



bool StreetSquare::can_build_hotel(shared_ptr<Player> player){
    return (this->owner == player) && (this->houses == 4) && !this->hasHotel;
}


void StreetSquare::promote_houses(){
    this->houses++;
}

int StreetSquare::houses_num(){
    return this->houses;
}


int StreetSquare::hotel_num(){
    return hasHotel ? 1 : 0;
}
