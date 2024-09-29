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
    Board* board;
    int numOfPlayers;
    bool double_outcome {false};
    int double_counter {0};

    // Player managment functions :

    //Move the player to a specific square by her index
    void GameManager::move_player_idx(Player* , size_t);

    /* A function that move the player on the board by the dice roll result 
       gets the new position and recognize the kind of the square */
    void move_player(Player* , int );

    //Handle the player's landing based on the respective square's functionality 
    void handle_player_landing(Player* , Square& );

    //Handle the surprise square 
    void handle_surprise_square(Player* ,SurpriseSquare&);

    //Handle the surprise card by the given index
    void handle_surprise_card(Player*, size_t);

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

