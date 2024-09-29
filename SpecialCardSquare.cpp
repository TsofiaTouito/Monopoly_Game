// tsofiatouito2@gmail.com


#include "SpecialCardSquare.hpp"





string SurpriseCard::get_content() const {
    return this->content;
}


//----------------------------------------SurpriseSquare class implementation--------------------------------



int SurpriseSquare::get_random_index(){

    //Get random index 
    random_device rd;     //non-deterministic random number
    mt19937 gen(rd());    

    uniform_int_distribution<> distr(0, this->surpriseCards.size()-1);

    int randomIndex = distr(gen);

    return randomIndex;
}



//Returns a random index to dynamically select a surprise card
size_t SurpriseSquare::get_card_index(){
        
    int randomIndex = get_random_index();

    return randomIndex;
}



SurpriseCard& SurpriseSquare::get_card(int index){
    return this->surpriseCards[index];
}



