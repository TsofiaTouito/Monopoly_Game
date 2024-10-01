//tsofiatouito2@gmail.com 


#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

using namespace std;

class Drawable{

    private:

    //Path to the player's images
    string path_to_player1 = "/home/user/Downloads/player1.png";
    string path_to_player2 = "/home/user/Downloads/player2.png";
    string path_to_player3 = "/home/user/Downloads/player3.png";
    string path_to_player4 = "/home/user/Downloads/player4.png";
    string path_to_player5 = "/home/user/Downloads/player5.png";
    string path_to_player6 = "/home/user/Downloads/player6.png";
    string path_to_player7 = "/home/user/Downloads/Player7.png";
    string path_to_player8 = "/home/user/Downloads/player8.png";
    
    public:

    std::string get_path_by_idx(int index) {
        
        switch (index) {
            case 1:
                return path_to_player1;
            case 2:
                return path_to_player2;
            case 3:
                return path_to_player3;
            case 4:
                return path_to_player4;
            case 5:
                return path_to_player5;
            case 6:
                return path_to_player6;
            case 7:
                return path_to_player7;
            case 8:
                return path_to_player8;
            default:
                return "Invalid index"; // Handle invalid index
        }
    }
};
