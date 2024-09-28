// tsofiatouito2@gmail.com

#include <iostream>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include <limits.h>

#include "Square.hpp"

using namespace std;

class Player{

    private:
    string name;                 //The name of the player 
    int money;                //Represent the amount of money the player have
    bool in_jail;                // True if the player is in Jail
    bool is_bankrupt;            // True if the player is in bankrupt

    vector<StreetSquare&> ownedStreets;   //Referance to owned street squares
    vector<TrainSquare&>  ownedTrain;      //Referance to owned train squares

    sf::Texture playerTexture;    //SFML variables
    sf::Sprite  playerSprite;



    //Constructor
    Player(std::string name, double money) : name(name), money(money), in_jail(false), is_bankrupt(false){};

    

    public:

    //Build a player object in the start of the game
    void init_player(std::string name,std::string path_to_img);


    bool sub_money(int);

    bool add_money(int);

    //Checks if the player can afford to subtract the given amount of money without quite
    bool can_afford(int);


    /*Player pay the rent for landing on other player asset
    Gets a pointer to the player object, and the amount to  */
    void pay_rent(Player* , int);

    //pay tax for landing on tax square that has owner
    void pay_company_tax(int, Player*);

    //Return the number of train the player have
    size_t train_num();

    //Add train to the vector after buy
    void add_train(TrainSquare&);

    bool owns_all_color(const string& , const vector<StreetSquare&>& ) const;

    bool can_build_balance(const string& ,  const vector<StreetSquare&>& );

    bool is_in_jail();

    void set_in_jail();

    bool is_Bankrupt();



    //Get the current position of the player
    const sf::Vector2f& get_position() const;

    //Set a new position for the player according to the dice roll
    void set_position(const sf::Vector2f& new_position);


};

