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
}