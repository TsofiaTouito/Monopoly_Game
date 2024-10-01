//tsofiatouito2@gmail.com

#include <random>
#include "Square.hpp"



class SurpriseSquare : public Square{

    private:

    //Calculate random index 
    int get_random_index();

    public:
    SurpriseSquare(const std::string& name, int index, sf::FloatRect square_area) : Square(name, index,square_area ){};

    //Returns a random index to dynamically select a surprise card
    size_t get_card_index();

};
