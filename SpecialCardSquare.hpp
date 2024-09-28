//tsofiatouito2@gmail.com

#include <random>
#include "Square.hpp"




class SurpriseCard{

    private:
    string content;    //the content of the card

    public:

};





class SurpriseSquare : public Square{

    private:

    vector<SurpriseCard&> surpriseCards;


    public:
    SurpriseSquare(const std::string& name, int index, sf::FloatRect square_area) : Square(name, index,square_area ){};


    SurpriseCard& get_random_card(){

        //Get random index 
        random_device rd;     //non-deterministic random number
        mt19937 gen(rd());    

        uniform_int_distribution<> distr(0, this->surpriseCards.size()-1);

        int randomIndex = distr(gen);

        return this->surpriseCards[randomIndex];

    }


};
