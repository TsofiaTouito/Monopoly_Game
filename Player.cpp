// tsofiatouito2@gmail.com

#include "Player.hpp"




//------------------------------------Create player object------------------------------------------

//Initilze a player object for the start of the game 
void Player::init_player(std::string name, std::string path_to_img){

    //create a player object amount of money: 1,500
    Player(name, 1500);


    //Open the player image
    if(!this->playerTexture.loadFromFile(path_to_img)){
        throw std::string("Player image failed to open .");
    }

    //enable to draw the player
    this->playerSprite.setTexture(this->playerTexture);
    
}



//-------------------------------------Money handeling of the player--------------------------------------




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
void Player::pay_rent(Player* owner, int rent){

    //Thw player will be bankrupt after the payment
    if(money - rent <= 0 ){

        is_bankrupt = true;   //call to observer to handle that
        return;
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


//
void Player::pay_company_tax(int diceRoll, Player* owner){

    //Calculate the tax 
    int tax = diceRoll*10;

    //Pay to the owner of the company
    this->pay_rent(owner, tax);
}


//-------------------------------Assets handling of the player---------------------------------------



size_t Player::train_num(){
    return this->ownedTrain.size();
}


void Player::add_train(TrainSquare& newTrain){
    this->ownedTrain.push_back(newTrain);
}

void Player::add_street(StreetSquare& street){
    this->ownedStreets.push_back(street);
}


//This methode checks if the payer oened all the street in the color group for house building

bool Player::owns_all_color(const string& colorGroup, const vector<StreetSquare&>& allStreets) const{
    
    //Loop all the streets 
    for(const auto& street :allStreets){

         //The player is'nt own all the streets in these color group
        if(street->colorGroup == colorGroup && street->owner != this){
            return false;  
        }

    }

    return true;

}



//A method that checks if the player can build house legaly
bool Player::can_build_balance(const string& colorGroup,  const vector<StreetSquare&>& allStreets){

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

return maxHouses - minHouses;

}



int Player::houses_in_owned(){
    int houses = 0;

    //For all street in owned of the player, sum the number of houses
    for(StreetSquare& street :ownedStreets){
        houses += street.houses_num();
    }

    return houses;
}




int Player::hotels_in_owned(){
    int hotels = 0;

    //For all street in owned of the player, sum the number of hotels
    for(StreetSquare& street :ownedStreets){
        hotels += street.hotel_num();   //return 1 in case of hotel
    }
    return hotels;
}





//--------------------------------------Jail handling----------------------------------------------------


bool Player::get_jail_card(){
    return this->outOfJailCard;
}

void Player::set_jail_card(){
    this->outOfJailCard = true;
}



//------------------------------------Move player object-----------------------------------------------

const sf::Vector2f& Player::get_position() const{

    return this->playerSprite.getPosition();

}


void Player::set_position(const sf::Vector2f& new_position){

    this->playerSprite.setPosition(new_position);
}








