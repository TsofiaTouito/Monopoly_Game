//tsofiatouito2@gmail.com

#include "GameManager.hpp"



void GameManager::move_player_idx(Player* player, size_t index){

    //Gets the current position of the player & the square he is on
    Square& curr_square = board->get_square_by_position(player->get_position());

    //Calculate the new position by the dice roll result
    Square& new_square= board->get_square_by_index(index); // 40 squares is on the board


    //Passing the starting square entitles you to NIS 200 
    //In porpuse to get the jail square, the player donsen't collect 200 NIS
    if(index + curr_square.index >= 40 && new_square.get_type() != "Go To Jail Square"){
        player->add_money(200);
    }

    // Create an sf::Vector2f from the new square's top-left corner
    sf::Vector2f new_position(new_square.square_area.left +10.f, new_square.square_area.top +10.f);

    //Set the player on the new square
    player->set_position(new_position);

    handle_player_landing(player, new_square);

}



void GameManager::move_player(Player* player, int rollDice){

    //Gets the current position of the player & the square he is on
    Square& curr_square = board->get_square_by_position(player->get_position());

    //Calculate the new position by the dice roll result
    Square& new_square= board->get_square_by_index((curr_square.index + rollDice)%40); // 40 squares is on the board


    //Passing the starting square entitles you to NIS 200
    if(curr_square.index + rollDice >= 40){ 
        player->add_money(200);
    }

    // Create an sf::Vector2f from the new square's top-left corner
    sf::Vector2f new_position(new_square.square_area.left +10.f, new_square.square_area.top +10.f);

    // Move the player to the new square's position
    player->set_position(new_position);

    //handle the square functionality
    handle_player_landing(player, new_square);

    }




//Handle the player's landing based on the respective square's functionality 
void handle_player_landing(Player* , Square& );



//Handle the surprise card functionality
void GameManager::handle_surprise_square(Player* player,SurpriseSquare& surprise){
    
    //Gets a random index to dynamically select a surprise card
    size_t index = surprise.get_card_index();

    //Perform the card method
    handle_surprise_card(player, index);

}


void GameManager::handle_surprise_card(Player* player, size_t index){
        
    switch(index){
            
        case 0:
        //0. Advance to Go (Collect $200) & Go (or Start) square index = 0
        move_player_idx(player, 0);
        break;


        case 1:
        //1. Bank pays you dividend of $50, change the amount to NIS
        int dollar = 4;
        int NIS_sum = dollar*50;
        player->add_money(NIS_sum);
        break;


        case 2:
        //2. Go back 3 spaces

        //Gets the current position of the player & the square he is on
        Square& curr_square = board->get_square_by_position(player->get_position());
        size_t new_index = (curr_square.index - 3)%40;    //go back 3 squares

        move_player_idx(player, new_index);
        break;
        


        case 3:
        //3. Go directly to Jail – do not pass Go, do not collect 200 NIS
        move_player_idx(player, 10);     //& Jail square index = 0
        break;


        case 4:
        //4. Make general repairs on all your property – For each house pay 25 NIS – For each hotel 100 NIS
        int houses_price = player->houses_in_owned()*25;
        player->sub_money(houses_price);   //Pay for the houses

        int hotels_price = player->hotels_in_owned()*100;
        player->sub_money(hotels_price);   //Pay for the hotels
        break;


        case 5:
        //5. Pay poor tax of 15 NIS
        player->sub_money(15);
        break;


        case 6:
        //6. Take a trip to Reading Railroad – If you pass Go collect 200 NIS
        move_player_idx(player, 5);       //Reading Railroad square index = 5
        break;


        case 7:
        //7. Take a walk on the Boardwalk – Advance token to Boardwalk
        move_player_idx(player, 39);      //Boardwalk square index = 5
        break;


        case 8:
        //8. You have been elected Chairman of the Board – Pay each player 50 NIS
        /* for(int i= 0 ; i < this->numOfPlayers ; i++){
            if(players[i] != player){
              player->pay_rent(50, players[i]);
            }
        }*/

        break;


        case 9:
        //9. Your building loan matures – Collect $150
        int dollar = 4;
        int sum = dollar*150;
        player->add_money(sum);
        break;


        case 10:
        //10. Get out of Jail Free – This card may be kept until needed or traded
        player->set_jail_card();
        //Get the player out_of_jail
        break;

        case 11:
        //11. Advance to Illinois Ave. – If you pass Go, collect 200 NIS
        move_player_idx(player, 24);        //Illinois Ave square index = 24
        break;


        case 12:
        //12. Advance to St. Charles Place – If you pass Go, collect 200 NIS
        move_player_idx(player, 11);        //St. Charles Place square index = 11
        break;


        case 13:
        //13. You are assessed for street repairs – 40 NIS per house, 115 NIS per hotel
          int houses_price = player->houses_in_owned()*40;
        player->sub_money(houses_price);   //Pay for the houses

        int hotels_price = player->hotels_in_owned()*115;
        player->sub_money(hotels_price);   //Pay for the hotels

        break;


        case 14:
        //14. Get into jail
        //player in jail
        break;


        case 15:
        //15.Go to Free Parking – If you pass Go, collect 200 NIS
        move_player_idx(player, 20);      //St. Charles Place square index = 20
        break;

    }

}




//Player buy a street
void GameManager::buy_street(Player* buyer, StreetSquare& street){

    if(street.square_type != "Street Square"){
        cout << "The square is'nt a StreetSquare ." << endl;
        return;
    }

    if(street.get_owner() != nullptr){
        cout << "The street already has an owner ." << endl;
        return;
    }

    int streetPrice = street.get_price();

    if(!buyer->can_afford(streetPrice)){
        cout << "The buyer can't afford the street price ." << endl;
        return;
    }

    //The street doesn't have an owner and the buyer can afford the purchase

    buyer->sub_money(streetPrice);  //Pay for the street
    buyer->add_street(street);      //Add the street to the buyer list of street he owned
    
    //Set the buyer to be the owner of the street
    street.set_owner(buyer);        

}






//Player buy a train
void GameManager::buy_train(Player* buyer, TrainSquare& train){

    if(train.square_type != "Train Square"){
        cout << "The square is'nt a TrainSquare ." << endl;
        return;
    }

    if(train.get_owner() != nullptr){
        cout << "The train already has an owner ." << endl;
        return;
    }

    int trainPrice = train.get_price();

    if(!buyer->can_afford(trainPrice)){
        cout << "The buyer can't afford the train price ." << endl;
        return;
    }

    //The train doesn't have an owner and the buyer can afford the purchase

    buyer->sub_money(trainPrice);  //Pay for the train
    buyer->add_train(train);      //Add the train to the buyer list of trains he owned
    
    //Set the buyer to be the owner of the train
    train.set_owner(buyer);        

}
    



//Player buy a company
void buy_company(Player* buyer, CompanySquare& company){

    //Check if the company already have an owner
    if(company.get_owner() != nullptr){
        cout << "The company already has an owner ." << endl;
        return;
    }

    int companyPrice = company.get_price();

    //Check if the buyer can afford the purchase
    if(!buyer->can_afford(companyPrice)){
        cout << "The buyer can't afford the company price ." << endl;
        return;
    }

    //The company doesn't have an owner and the buyer can afford the purchase
    //Pay for the company
    buyer->sub_money(companyPrice);  
    
    //Set the buyer to be the owner of the company
    company.set_owner(buyer);        

}





//Player buy an house
void build_house(Player* buyer, StreetSquare& street,vector<StreetSquare&>& allStreets){

    //Checks whether an house can be built & the buyer is the owner of the street
    if(!street.can_build_house(buyer)){
        cout << "Can't build an house in this street. " << endl;
        return;
    }

    //Checks if the buyer have all the streets in color group -> condition for building an house
    if(!buyer->owns_all_color(street.colorGroup, allStreets)){
        cout << "The buyer dosn't have all the streets in color group ." << endl;
        return;
    }

    //Checks if the buyer can build the house in balance 
    if(!buyer->can_build_balance(street.colorGroup, allStreets)){
        cout << "The Player can't build in balance ." << endl;
        return;
    }

    //The buyer is the owner of the street & he can build an house in balance & owned all color group

    int housePrice = street.get_house_price();

    if(!buyer->can_afford(housePrice)){
        cout << "The buyer can't afforn the house price .";
        return;
    }

    //The buyer can afford the purches
    buyer->sub_money(housePrice);

    /* board->draw_house(buyer, street) --> draw the asset on board in the player color */

    street.promote_houses();
}







//Player buy an hotel
void build_hotel(Player* buyer, StreetSquare& street,vector<StreetSquare&>& allStreets){

    //Checks if the buyer is the the owner of the street & the street owned 4 houses in his ownership
    if(street.can_build_hotel(buyer)){
        cout << "The buyer can't build an hotel ." << endl;
    }


    int hotelPrice = street.get_hotel_price();

    if(!buyer->can_afford(hotelPrice)){
        cout << "The buyer can't afforn the hotel price .";
        return;
    }

    //The buyer can afford the purches
    buyer->sub_money(hotelPrice);

    /* board->draw_hotel(buyer, street) --> draw the asset on board in the player color */
    
    //Update the street object that hotel has been build
    street.set_hotel();

}

