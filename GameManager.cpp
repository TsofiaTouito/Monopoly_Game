//tsofiatouito2@gmail.com

#include "GameManager.hpp"


void GameManager::move_player_idx(shared_ptr<Player> player, size_t index){

    //Gets the current position of the player & the square he is on
    Square& curr_square = board->get_square_by_position(player->get_position());

    //Calculate the new position by the dice roll result
    Square& new_square= board->get_square_by_index(index); // 40 squares is on the board

    int steps = index + curr_square.index;
    //Passing the starting square entitles you to NIS 200 
    //In porpuse to get the jail square, the player donsen't collect 200 NIS
    if(steps >= 40 && new_square.get_type() != "Go To Jail Square"){
        player->add_money(200);
    }

    // Create an sf::Vector2f from the new square's top-left corner
    sf::Vector2f new_position(new_square.square_area.left +10.f, new_square.square_area.top +10.f);

    //Set the player on the new square
    player->set_position(new_position);

    handle_player_landing(player, new_square, steps%40);

}



void GameManager::move_player(shared_ptr<Player>  player, int rollDice){

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
    handle_player_landing(player, new_square, rollDice);

    }


//---------------------------------------Handle player landing---------------------------------------------------------



void GameManager::handle_street_landing(shared_ptr<Player> player, StreetSquare& street){
    cout << player->get_name() <<" land in " << street.streetName <<endl;
    cout << "The amount of money you have is :" << player->get_money() <<endl;

        //In case the street has no owner
        if(!street.get_owner()){
            cout << "The street has no owner, would you like to buy it in: " << street.get_price() <<" NIS ? \n Enter: Y (for yes) or N (For no)" << endl;
            char ans;
            cin>>ans;//Get the input from the player

            if(ans == 'Y' ){
                //Player want to buy the street
                buy_street(player, street);
            }

            else{
                cout << "You decide to not buy ." <<endl;
            }
        }

        //If the owner of the street is player
        if(street.get_owner() = player){
            cout << "You are the owner of " << street.streetName << " ." << " Would you like to build an house or hotle ?" << endl;
            cout << "If you want to build an house enter A, If you want to build an hotel enter B, for none enter N ." <<endl;
            char ans;
            cin>>ans;

            vector<shared_ptr<StreetSquare>> allStreets = board->get_allStreets();

            if(ans == 'A'){
                cout << player->get_name() << " building an house ." << endl;
                build_house(player, street, allStreets);
            }

            if(ans == 'B'){
                cout << player->get_name() << " building an hotel ." << endl;
                build_hotel(player, street, allStreets);
            }

            else{
                //Player enter None
                cout << "You decide to not buy ." << endl;
            }
        }


        else{         
            /* Street already has an owner, then player must pay rent
            If the player cant afford the rent, definehim as bankrupt*/
            int rent = street.calc_rent();

            if(!player->can_afford(rent)){
                cout << "The player can't afford the rent price ." << endl;
                handle_nankruptcy_(player, street.get_owner());   
            }

            cout << player->get_name() << "Pay rent of :" << rent << "NIS , to " << street.get_owner()->get_name() << endl;
            player->pay_rent(street.get_owner(), rent);
        }
}



void GameManager::handle_train_landing(shared_ptr<Player> player, TrainSquare& train){

    cout << player->get_name() <<" land on Train square ." << endl;

        //In case the train has no owner
        if(!train.get_owner()){
            cout << "The amount of money you have is :" << player->get_money() <<endl;
            cout << "The train has no owner, would you like to buy it in: " << train.get_price() <<" NIS ? \n Enter: Y (for yes) or N (For no)" << endl;
            char ans;
            cin>>ans;//Get the input from the player

            if(ans == 'Y' ){
                //Player want to buy the train
                buy_train(player, train);
            }

            else{
                cout << "You decide to not buy ." <<endl;
            }

        }

        //If the owner of the train is player
        if(train.get_owner() = player){
            cout << "You are the owner of the Train . " << endl;    
        }

        else{
   
            /* The train already has an owner, then player must pay rent
            If the player cant afford the rent, define him as bankrupt*/
            int rent = train.calc_rent();
            cout << "You land on owned train, and must pay rent of :" << rent << "NIS" << endl;

            if(!player->can_afford(rent)){
                cout << "The player can't afford the rent price ." << endl;
                handle_nankruptcy_(player, train.get_owner());   
            }

            cout << player->get_name() << "Pay rent of :" << rent << "NIS , to " << train.get_owner()->get_name() << endl;
            player->pay_rent(train.get_owner(), rent);
        }

}



void GameManager::handle_company_square(shared_ptr<Player> player, CompanySquare& company, int diceRoll){

        //In case the company has no owner
        if(!company.get_owner()){
            cout << "The amount of money you have is :" << player->get_money() <<endl;
            cout << "The company has no owner, would you like to buy it in: " << company.get_price() <<" NIS ? \n Enter: Y (for yes) or N (For no)" << endl;
            char ans;
            cin>>ans;//Get the input from the player

            if(ans == 'Y' ){
                //Player want to buy the company
                buy_company(player, company);
            }

            else{
                cout << "You decide to not buy ." <<endl;
            }

        }

        //If the owner of the train is player
        if(company.get_owner() = player){
            cout << "You are the owner of the company . " << endl;    
        }

        else{
   
            /* The company already has an owner, then player must pay rent of : dice roll result*10
            If the player cant afford the rent, define him as bankrupt*/
            int rent = diceRoll*10;
            cout << "You land on owned company, and must pay rent of :" << rent << "NIS" << endl;

            if(!player->can_afford(rent)){
                cout << "The player can't afford the rent price ." << endl;
                handle_nankruptcy_(player, company.get_owner());   
            }

            cout << player->get_name() << "Pay rent of :" << rent << "NIS , to " << company.get_owner()->get_name() << endl;
            player->pay_rent(company.get_owner(), rent);
        }
}






//Handle the player's landing based on the respective square's functionality 
void GameManager::handle_player_landing(shared_ptr<Player>  player, Square& square, int diceRoll){

    if(square.get_type() == "Street Square"){
        
        StreetSquare& street = dynamic_cast<StreetSquare&>(square);
        handle_street_landing(player, street);
        return;
    }

    if(square.get_type() == "Train Square"){
        
        TrainSquare& train = dynamic_cast<TrainSquare&>(square); 
        handle_train_landing(player, train);
        return;
    }


    if(square.get_type() == "Surprise Square"){
        
        SurpriseSquare& surprise = dynamic_cast<SurpriseSquare&>(square); 
        handle_surprise_square(player, surprise);
        return;
    }


    if(square.get_type() == "Free Parking Square"){
        cout<< player->get_name() <<" land in free parking square, end's player turn. ";
        return;
    }


    if(square.get_type() == "Company Square"){
        cout<< player->get_name() <<" land in free Company square .";

        CompanySquare& company = dynamic_cast<CompanySquare&>(square); 
        handle_company_square(player, company, diceRoll);
    }



    if(square.get_type() == "Tax Square"){

        cout<< player->get_name() <<" land in free Company square .";

        TaxSquare& tax = dynamic_cast<TaxSquare&>(square); 
        
            if(!player->can_afford(tax.get_tax())){
                cout << "The player can't afford the tax price ." << endl;
                handle_nankruptcy(player);   
            }
            else{
                cout << player->get_name() << "Pay tax of : 100 NIS ." << endl;
                player->sub_money(tax.get_tax());
            }
    }


    if(square.get_type() == "Jail Square"){
        cout << player->get_name() << "land on jail square ." << endl;
    }
    
    if(square.get_type() == "Go to Jail Square"){

        cout << player->get_name() << "land on go to jail square ." << endl;
    
        //sent player to jail
        set_jail_state(player, true);
    }

    if(square.get_type() == "Start Square"){
        cout << player->get_name() << "land on Start square ." << endl;
    }


}


//Handle the surprise card functionality
void GameManager::handle_surprise_square(shared_ptr<Player> player, SurpriseSquare& surprise){
    
    //Gets a random index to dynamically select a surprise card
    size_t index = surprise.get_card_index();

    //Perform the card method
    handle_surprise_card(player, index);

}


void GameManager::handle_surprise_card(shared_ptr<Player> player, size_t index){
        
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

        GameManager::move_player_idx(player, new_index);
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
        player->set_jail_card(true);
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
void GameManager::buy_street(shared_ptr<Player> buyer, StreetSquare& street){

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
void GameManager::buy_train(shared_ptr<Player> buyer, TrainSquare& train){


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
void GameManager::buy_company(shared_ptr<Player>  buyer, CompanySquare& company){

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
void GameManager::build_house(shared_ptr<Player> buyer, StreetSquare& street,vector<shared_ptr<StreetSquare>> allStreets){

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
void GameManager::build_hotel(shared_ptr<Player> buyer, StreetSquare& street,vector<shared_ptr<StreetSquare>> allStreets){

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




//----------------------------------------------Jail handling-------------------------------------------------------

void GameManager::set_jail_state(shared_ptr<Player> player, bool state){
    
    //If the player have the jail card, we don't send him to jail
    if(player->get_jail_card() && state){
        player->set_jail_card(false);    //update the card usage
        player->jail_state(false);       //Jail state of the player is false
        return;
    }

    //Set the new state
    player->jail_state(state);

    //If we set the player in jail, then move him to the jail square
    if(state && player->get_jail_card()){
        move_player_idx(player, 10);  //move the player to jail square (index 10)
    }

}

//-------------------------------------------Nankruptcy handle---------------------------------------------------




void GameManager::handle_nankruptcy(shared_ptr<Player> player){

    cout<< player->get_name() << " is bankrupt ." <<endl;

    // Handle player's properties (auction, return to the bank, etc.)
    player->clear_properties(); 

    // Remove the player from the game
    auto it = remove(this->players.begin(), this->players.end(), player);

    if (it != this->players.end()) {
        this->players.erase(it);
    }

}





void GameManager::handle_nankruptcy_(shared_ptr<Player> bankruptPlayer, shared_ptr<Player> player){


    cout<< bankruptPlayer->get_name() << " is bankrupt ." <<endl;
    
    //All the assets of the bankrupt player is move to the player who owns the debt
    bankruptPlayer->move_assets(player);

    // Remove the player from the game
    auto it = remove(this->players.begin(), this->players.end(), player);

    if (it != this->players.end()) {
        this->players.erase(it);
    }

}




//----------------------------------------------Turn Handling-----------------------------------------------------
  
  
  
  
int GameManager::roll_dice() {

    int dice1 = rand() % 6 + 1;   // Roll first die (1 to 6)
    int dice2 = rand() % 6 + 1;   // Roll second die (1 to 6)

    // The outcome is a double 
    if(dice1 == dice2){
        this->double_outcome = true;
        this->double_counter++;
    }
    return dice1 + dice2;
}




void GameManager::play_turn(){

    //Get the corrent player 
    shared_ptr<Player> currPlayer = players[currPlayerIdx];
    cout << "Current player turn: " << currPlayer->get_name() << endl;

    if(currPlayer->is_in_jail()){

        if(currPlayer->turnsInJail <= 3){

            //Promote the turns the player is in jail
            currPlayer->turnsInJail++;

            cout << "The player now is in jail for "<< currPlayer->turnsInJail << " turns .";
            cout << "Promot the turn to the next player ." << endl;

            //Promote the turn to the next player
            currPlayerIdx = (currPlayerIdx + 1) % players.size();
            return;
        }

        //The player get out from jail in this turn
        else if(currPlayer->turnsInJail > 3){

            int diceRoll = roll_dice();
                
            //Condition to get out from jail : Pay 50 NIS or double dice roll outcome
            if(!currPlayer->can_afford(50) && !double_outcome){
                cout << "the player can't afford the price to get out from jail and the outcome isn't double . " << endl;
                //The player must leave the game
                handle_nankruptcy(currPlayer);
            }

            if(double_outcome || currPlayer->sub_money(50)){
                set_jail_state(currPlayer, false);
            }
        }

    }

    //The corrent player isn't in jail || release now from jail
    else{
        
        //roll the dice
        int diceRoll = roll_dice();

        //move the player according to the roll dice result and handle landing
        move_player(currPlayer, diceRoll);

        //In the 3 time the outcom is double, the player sent into jail
        if(double_counter >= 3){
            set_jail_state(currPlayer, true);
        }

        //Another turn for the current player
        if(double_outcome && double_counter != 3){
            double_counter++;
            cout << currPlayer->get_name() <<" entitled to another turn ." << endl;
        }

        //Promote the corrent player index
        else{
            currPlayerIdx = (currPlayerIdx + 1) % players.size();
        }
    }

}




bool GameManager::is_over(){

bool win = false;
shared_ptr<Player> winner;

    //Player win if he is the only one that left in the game
    if(this->players.size() ==1){
        win = true;
        announce_winner(players[0]);
    }

    //Player win if he have 4000 amount of money
    for( auto player : this->players){

        if(player->get_money() >= 4000){
            winner = player;
            win = true;
            announce_winner(player);
        }
    }
    
return win;
}



void GameManager::announce_winner(shared_ptr<Player> player){
    cout << player->get_name() << " is the winner of the game !" <<endl;

    players.clear();
}



//-------------------------------------------Game initilization-----------------------------------------------------



void GameManager::initialize_players(int numOfPlayers){


    for(int i = 1 ; i <= numOfPlayers ; i++){
        string name = "Player " + to_string(i);   //Name of the player is by his index

        shared_ptr<Player> player = make_shared<Player>(name, 1500);      //Initilize the player object 
        player->init_player_vis(this->obj.get_path_by_idx(i));
        players.push_back(player);
    }

}





//Initilize and draw the players on the board, the board – on the given window
void GameManager::initialize_game(sf::RenderWindow& window ){

    //Creats / get the instance of the board 
    board->get_instance();

    //Draw the board on the given window
    board->render(window);
/*
    //Set the players the start position
    for(int i = 0 ; i < players.size() ; i++){
        players[i]->set_position()

    }

*/


}




void GameManager::start_game(sf::RenderWindow& gameWindow){

    cout << "Please enter the number of players :" << endl;
    cin >> this->numOfPlayers;

    // Initilize the player object & the game board
    initialize_players(this->numOfPlayers);
    initialize_game(gameWindow);

}

