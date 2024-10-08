// tsofiatouito2@gmail.com


#ifndef GAMEMANAGER_HPP
#define GAMEMANAGER_HPP


using namespace std;

#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <algorithm>

#include "Board.hpp"
#include "Square.hpp"
#include "Player.hpp"
#include "GUI_Manager.hpp"



class GameManager{

    private:
    Board* board;
    
    int numOfPlayers;
    int currPlayerIdx;
    bool double_outcome {false};
    int double_counter {0};
    Drawable obj;      //Store the image path


    //------------------------landing handling----------------------------------
    

    sf::Vector2f calc_player_position(Player* player, Square& square);

    void handle_street_landing(Player*, StreetSquare&);

    void handle_train_landing(Player* , TrainSquare& );

    void handle_company_square(Player*, CompanySquare&, int);


    //Handle the player's landing based on the respective square's functionality 
    void handle_player_landing(Player* , Square& , int);



    //------------------------Player managment----------------------------------

    //Move the player to a specific square by her index
    void move_player_idx(Player*  , size_t);

    /* A function that move the player on the board by the dice roll result 
       gets the new position and recognize the kind of the square */
    void move_player(Player* , int );

    //Handle the surprise square 
    void handle_surprise_square(Player* ,SurpriseSquare&);

    //Handle the surprise card by the given index
    void handle_surprise_card(Player* , size_t);

    //Player buy a street
    void buy_street(Player*, StreetSquare&);

    //Player buy a street
    void buy_train(Player* , TrainSquare&);
    
    //Player buy a company
    void buy_company(Player*, CompanySquare&); 

    //Player buy an house
    void build_house(Player* , StreetSquare&,vector<StreetSquare*>&);

    //Playeer buy an hotel
    void build_hotel(Player* , StreetSquare&,vector<StreetSquare*>&);

    //roll the dice
    int roll_dice();


    //Enter the player in jail / get him out 
    void set_jail_state(Player*, bool);


    //------------------------Bankrupt handling--------------------------------

    //Handle nankruptcy as a result of getting to 0 NIS
    void handle_nankruptcy(Player*);

    //Handle nankruptcy as a result of lack of ability to pay for other player 
    void handle_nankruptcy_(Player*, Player*);
    

    //--------------------------Game flow managment--------------------------------

    public:
    //Constructor
    GameManager() : board(nullptr), numOfPlayers(0), currPlayerIdx(0) , obj(), gameStarted(false){};
    vector<Player*> players;
    bool gameStarted ;



    //-----------Turn Handling----------------
    //Play the turn of the current player
    void play_turn();

    //Returns true if the game is over
    bool is_over();

    //Announce the winner of the game
    void announce_winner(Player*);


    //----------------Initilize game-------------------------

    //Get the start position for locate the players on the start square
    sf::Vector2f get_start_position(int index);

    //Create the players objects
    void initialize_players(int , sf::RenderWindow& );

    //Initilize and draw the players on the board, the board – on the given window
    void initialize_game(sf::RenderWindow& window );

    // Start the game
    void start_game(sf::RenderWindow&);



};




#endif
