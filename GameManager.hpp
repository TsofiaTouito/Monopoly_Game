// tsofiatouito2@gmail.com

using namespace std;

#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include "Board.hpp"
#include "Square.hpp"
#include "Player.hpp"
#include "SpecialCardSquare.hpp"



class GameManager{

    private:
    bool double_outcome {false};
    int double_counter {0};

    // Player managment functions :

    /* A function that move the player on the board by the dice roll result (steps variable)
       gets the new position and recognize the kind of the square */
    void move_player(Player* player, int steps);

    //Handle the player's landing based on the respective square's functionality 
    void handle_player_landing(Player* , StreetSquare& );

    //Handle the surprise card functionality
    void handle_surprise_card(Player* , SurpriseCard&);

    //Player buy a street
    void buy_street(Player*, StreetSquare&);

    //Player buy a street
    void buy_train(Player*, TrainSquare&);
    
    //Player buy a company
    void buy_company(Player*, CompanySquare&); 

    //Player buy an house
    void build_house(Player*, StreetSquare&,vector<StreetSquare&>&);

    //Playeer buy an hotel
    void build_hotel(Player*, StreetSquare&,vector<StreetSquare&>&);






    public:

    // Game flow managment :


    int roll_dice() {

        int dice1 = rand() % 6 + 1;   // Roll first die (1 to 6)
        int dice2 = rand() % 6 + 1;   // Roll second die (1 to 6)

        // The outcome is a double 
        if(dice1 == dice2){
            this->double_outcome = true;
            this->double_counter++;
        }
        return dice1 + dice2;
    }


/*
    // Start the game
    void start_game();

    // Advances to the next player’s turn.
    void next_turn();

    // Checks if the game is over
    bool is_over();

    // Returns the player whose turn it is.
    Player* get_current_player();

    // Manages a player going bankrupt.
    void handel_Nankruptcy(Player*);

    //Announces the winner and ends the game.
    void display_winner();

*/
};

