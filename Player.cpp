// tsofiatouito2@gmail.com

#include "Player.hpp"



using namespace std;



// Define operator!= to compare pointers
bool Player::operator!=(const Player& other) const {
    return this != &other;  // Compare addresses
}


//------------------------------------Create player object------------------------------------------


string Player::get_name(){
    return this->name;
}



//-------------------------------------Money handeling of the player--------------------------------------


int Player::get_money() const{
    return this->money;
}


bool Player::sub_money(int amount){

    double res = this->money - amount;
    
    if(money < 1 && res == 0){  //At least 1 
        
        //call to gameManager observer for continiue handeling
        //delet the player
        this->is_bankrupt = true;
        return false;             //failed in subtract the amount of money
    }

    this->money -= amount;
    return true;  //for success 

}



bool Player::add_money(int amount){
    
    if(amount < 0){
        std::cout << "Can't add a negative number" << std::endl;
        return false;   //failed in add the amount of money
    }

    this->money += amount;
    return true;    //for success 
}



//Leaving the player with no less than one NIS
bool Player::can_afford(int num){

    return money > num;    
}




//gets: the owner to pay to, the amoubt of money the player needs to pay
bool Player::pay_rent(Player* owner, int rent){

    //Thw player will be bankrupt after the payment
    if(money - rent <= 0 ){

        is_bankrupt = true;   //call to observer to handle that
        return false;
    }
    
    //Subtract the rent from the player's money
    if(!this->sub_money(rent)){

        throw string("Failed in subtract the rent from the player .");
    }  

    //Pay the rent to the owner
    if(!owner->add_money(rent)){

        throw string("Failed in add the amount of the rent money to the owner .");
    } 
  
}




//-------------------------------Assets handling of the player---------------------------------------



size_t Player::train_num(){
    return this->ownedTrains.size();
}


void Player::add_train(TrainSquare& newTrain){
    this->ownedTrains.push_back(&newTrain);
}

void Player::add_street(StreetSquare& street){
    this->ownedStreets.push_back(&street);
}



//This methode checks if the payer oened all the street in the color group for house building
bool Player::owns_all_color(const string& colorGroup, const std::vector<StreetSquare*>& allStreets) const {
    // Loop through all the streets
    for (const auto& street : allStreets) {
        // Check if the street belongs to the same color group and if the player does not own it
        if (street->colorGroup == colorGroup && (street->get_owner() != this)) {
            return false;
        }
    }

    return true;
}




//A method that checks if the player can build house legaly
bool Player::can_build_balance(const string& colorGroup,  vector<StreetSquare*>& allStreets){

int minHouses = INT_MIN;
int maxHouses = INT_MAX;

    //Loop all the streets
    for(const auto& street : allStreets){

        if(street->colorGroup == colorGroup){

            //if the current minimal number of houses is bigger than 
            if(street->houses < minHouses){
                minHouses = street->houses;
            }

            if(street->houses > maxHouses){
                minHouses = street->houses;
            }
        }
    }

    return (maxHouses - minHouses <= 1); // Can build if difference is 1 or less

}



int Player::houses_in_owned(){
    
int houses = 0;

    //For all street in owned of the player, sum the number of houses
    for(StreetSquare* street :ownedStreets){
        if(street != nullptr){
        houses += street->houses_num();
        }
    }

return houses;
}




int Player::hotels_in_owned(){
    int hotels = 0;

    //For all street in owned of the player, sum the number of hotels
    for(auto& street :ownedStreets){
        hotels += street->hotel_num();   //return 1 in case of hotel
    }
    return hotels;
}




void Player::add_asset(sf::Shape* asset){

    assets.push_back(asset);
}



//--------------------------------------Jail handling----------------------------------------------------



bool Player::is_in_jail(){

    //if the player is in jail, less then 3 turns
    return this->in_jail && turnsInJail>0 && turnsInJail >= 3;

}



void Player::jail_state(bool val){
    this->in_jail = val; 
}



bool Player::get_jail_card(){
    return this->outOfJailCard;
}



void Player::set_jail_card(bool val){
    this->outOfJailCard = val;
}


//--------------------------------------Bankrupt handling----------------------------------------------



bool Player::is_Bankrupt(){
    return this->is_bankrupt;
}



void Player::move_assets(Player* other){

// Move the graphical assets (sf::Shape*)
for (auto& asset : this->assets) {
    other->assets.push_back(asset);
}
    this->assets.clear();

// Move owned streets
for (auto& street : this->ownedStreets) {
    other->ownedStreets.push_back(street);
}
    this->ownedStreets.clear();

// Move owned trains
for (auto& train : this->ownedTrains) {
       other->ownedTrains.push_back(train);
}
    this->ownedTrains.clear();

}



void Player::clear_properties(){
    
    this->assets.clear();
    this->ownedStreets.clear();
    this->ownedTrains.clear();
}



//------------------------------------Move player object-----------------------------------------------



//Initilze a player object for the start of the game 
void Player::init_player_vis(string path, sf::RenderWindow& window){


    //Open the player image
    if(!this->playerTexture.loadFromFile(path)){
        throw std::string("Player image failed to open .");
    }

    //enable to draw the player
    this->playerSprite.setTexture(this->playerTexture);
    window.draw(playerSprite);

}

const sf::Vector2f& Player::get_position() const{

    return this->playerSprite.getPosition();

}


void Player::set_position(const sf::Vector2f& new_position){

    this->playerSprite.setPosition(new_position);
}








