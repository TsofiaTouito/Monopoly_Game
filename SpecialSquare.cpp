// tsofiatouito2@gmail.com


#include "SpecialSquare.hpp"




int SurpriseSquare::get_random_index(){

    //Get random index 
    random_device rd;     //non-deterministic random number
    mt19937 gen(rd());    

    uniform_int_distribution<> distr(0, 15); //15 options for surprise card

    int randomIndex = distr(gen);

    return randomIndex;
}



//Returns a random index to dynamically select a surprise card
size_t SurpriseSquare::get_card_index(){
        
    int randomIndex = get_random_index();

    return randomIndex;
}


