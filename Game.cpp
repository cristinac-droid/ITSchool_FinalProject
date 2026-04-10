#include <iostream>
#include <list>
#include <memory>

using namespace std;

enum Race {
    HUMAN,
    FAIRY,
    ELF,
    SPIDER,
};

enum Gender {
    MALE,
    FEMALE,
    OTHER,
};

class Character {
private:
    string name;
    unsigned int age;
    Race race;
    Gender gender;
public:
    Character (
        string _name,
        unsigned int _age,
        Race _race,
        Gender _gender) :
        name(_name),
        age(_age),
        race(_race),
        gender(_gender) {}
};

class Player : Character {
    int health;
public:
Player (
        string _name,
        unsigned int _age,
        Race _race,
        Gender _gender) : Character(_name, _age, _race, _gender) {
            health = 100;
        cout << "Player " << _name << " created" << endl;
        }
};

class NPC : Character {
public:
NPC (
        string _name,
        unsigned int _age,
        Race _race,
        Gender _gender) : Character (_name, _age, _race, _gender) {
        cout << _name << "spawns." << endl;
        }
};

int main () {
    Player* playermain = new Player ("PlayerMain", 35, HUMAN, FEMALE);
    return 0;

int choice;

    do {
        cout << "\n=== GAME MENU ===\n";
        cout << "1. Play\n";
        cout << "2. Options\n";
        cout << "3. Exit\n";
        cout << "Choose: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Starting game...\n";
                break;

            case 2: {
                int difficulty;
                cout << "\n-- Options --\n";
                cout << "1. Easy\n";
                cout << "2. Medium\n";
                cout << "3. Hard\n";
                cout << "Choose difficulty: ";
                cin >> difficulty;

                switch (difficulty) {
                    case 1:
                        cout << "Easy selected\n";
                        break;
                    case 2:
                        cout << "Medium selected\n";
                        break;
                    case 3:
                        cout << "Hard selected\n";
                        break;
                    default:
                        cout << "Invalid difficulty\n";
                }
                break;
            }

            case 3:
                cout << "Exiting game...\n";
                break;

            default:
                cout << "Invalid choice\n";
        }

    } while (choice != 3);

    return 0;
}
