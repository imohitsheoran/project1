#ifndef GAME_HPP
#define GAME_HPP

#include <string>
#include <iostream>
#include <algorithm>
#include <random>
#include <vector>

struct Player {
    std::string name;
    int cash = 100;
    char selectedCard;

    std::string getName() { return name; }
    int getCash() { return cash; }
};

enum Card {
    KING,
    MINISTER,
    POLICE,
    THIEF
};

class Game {
public:
    char A[4] = {'K', 'M', 'P', 'T'};
    Player players[4];

    void initializePlayers() {
        for (int i = 0; i < 4; ++i) {
            std::cout << "Enter name for Player " << (i + 1) << ": ";
            std::cin >> players[i].name;
            players[i].cash = 100; // Initialize with default cash value
        }
    }

    void shuffleCard(char *A, int size) {
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(A, A + size, g);
    }

    void checkCondition(char selectedCard, Player &player) {
        switch (selectedCard) {
            
        case 'K':
                player.cash+=50;
            break;
        case 'M':
                
                player.cash += 30;
            break;
        case 'P':
            
                player.cash += 10;
            break;
        case 'T':
            
                player.cash -= 10;
            break;
        default:
            std::cout << "Invalid card selected.\n";
            break;
        }
        
    }

    void play() {
        shuffleCard(A, 4);
        displayBanner();

        for (int i = 0; i < 4; ++i) {
            std::cout << players[i].getName() << ", select a card number (1-4): ";
            int cardIndex;
            std::cin >> cardIndex;

            while (cardIndex < 1 || cardIndex > 4) {
                std::cout << "Invalid choice. Please select a card number between 1 and 4: ";
                std::cin >> cardIndex;
            }

            players[i].selectedCard = A[cardIndex - 1];
        }
        displayBottomBanner();

        Player *king = nullptr, *minister = nullptr, *thief = nullptr;

        for (int i = 0; i < 4; ++i) {
            if (players[i].selectedCard == 'K') {
                king = &players[i];
            } else if (players[i].selectedCard == 'M') {
                minister = &players[i];
            } else if (players[i].selectedCard == 'T') {
                thief = &players[i];
            }
        }

        if (king && minister) {
            displayBanner();
            std::cout << "\t King: " << king->getName()  << "\t";
            std::cout << "\t Minister: " << minister->getName() << "\n\n";

            std::cout << minister->getName() << ", guess the Thief's card: ";
            char guessedCard;
            std::cin >> guessedCard;
            displayBottomBanner();

            if (thief && guessedCard == thief->selectedCard) {
                std::cout<<"\n";
                displayBanner();
                std::cout<<"\n";
                std::cout << "Correct guess! Here are the results:\n";
                displayBottomBanner();
            } else {
                std::cout<<"\n";
                displayBanner();
                std::cout<<"\n";
                std::cout << "Wrong guess! Exchanging cards between Minister and Thief.\n";
                if (minister && thief) {
                    std::swap(minister->selectedCard, thief->selectedCard);
                }
                displayBottomBanner();
            }
        }
        for (int i = 0; i < 4; ++i) {
            checkCondition(players[i].selectedCard, players[i]);
        }
        std::cout<<"\n";
        displayBanner();
        std::cout<<"\n";
        std::cout << "Final Results:\n\n";
        std::cout<< "PLAYER\t"<<"\tCARD\t"<<"\tCASH\n\n";

        for (int i = 0; i < 4; ++i) {
            
            std::cout << players[i].getName() << "\t\t" << players[i].selectedCard
                      << "\t\t" << players[i].getCash() << "\n\n";
        }

        int continueCount = 0;
        for (int i = 0; i < 4; ++i) {
            std::cout << players[i].getName() << ", do you want to continue the game? (yes/no): ";
            std::string choice;
            std::cin >> choice;

            if (choice == "yes") {
                ++continueCount;
            }
        }

        if (continueCount > 2) {
            std::cout << "More than 2 players want to continue. Resuming the game...\n";
            play();
        } else {
            std::cout << "Less than or equal to 2 players want to continue. Game Over. Thanks for playing!\n";
        }
    }

    void displayBanner() {
        std::cout << R"(
             C   R   O   W   N     A   N   D     C   H   A   O   S
        )" << "\n";
        std::cout << "---------------------------------------------------------------------------\n";
    }

    void displayBottomBanner(){
        std::cout << "---------------------------------------------------------------------------\n";
    }

    void Start() {
        displayBanner();
        initializePlayers();
        displayBottomBanner();
        play();
    }
};

#endif