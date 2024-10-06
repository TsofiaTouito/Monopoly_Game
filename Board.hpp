//tsofiatouito2@gamail.com
#ifndef BOARD_HPP
#define BOARD_HPP


#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory> 

#include "Square.hpp"
#include "SquareFactory.hpp"

using namespace std;

class Board {

    private:
    sf::Texture boardTexture;
    sf::Sprite  boardSprite;
    static Board* singletonBoard;                //Singleton instance
    vector<Square*> squares;          //represent the squares on board
    vector<StreetSquare*> allStreets;
    Board();    
                                     //private constructor for Singleton

                                     
    ~Board() {
        for (auto square : squares) {
            delete square; // Free each Square
        }
        for (auto street : allStreets) {
            delete street; // Free each StreetSquare
        }
        squares.clear();      // Clear the vector
        allStreets.clear();  // Clear the vector
    }


    
    public:

    // Static method to get the singleton instance
    static Board* get_instance();

    //Method that draw the board on the accepted window
    void render(sf::RenderWindow& window);

    //Return the square by the given position on board
    Square& get_square_by_position(const sf::Vector2f& position) ;

    Square& get_square_by_index(int) ;


    vector<StreetSquare*>& get_allStreets();


};



#endif
