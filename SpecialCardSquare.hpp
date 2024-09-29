//tsofiatouito2@gmail.com

#include <random>
#include <unordered_map>
#include "Square.hpp"




class SurpriseCard{

    private:
    const string content;    //the content of the card

    public:
    SurpriseCard(const string& data) : content(data) {};

    string get_content() const;

};





class SurpriseSquare : public Square{

    private:

    vector<SurpriseCard&> surpriseCards;

    //Calculate random index 
    int get_random_index();

    public:
    SurpriseSquare(const std::string& name, int index, sf::FloatRect square_area) : Square(name, index,square_area ){};

    //Returns a random index to dynamically select a surprise card
    size_t get_card_index();

    //Get thee card by the given index
    SurpriseCard& get_card(int index);


};
