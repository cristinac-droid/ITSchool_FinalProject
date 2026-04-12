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

string raceToString(Race race) {
	switch (race) {
	case HUMAN:
		return "HUMAN";
	case FAIRY:
		return "FAIRY";
	case ELF:
		return "ELF";
	case SPIDER:
		return "SPIDER";
	default:
		return "UNKNOWN";
	}
}

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
	Character () {}

	void setName(string name) {
		this->name = name;
	}
	void setAge(int age) {
		this->age = age;
	}
	void setRace(Race race) {
		this->race = race;
	}
	void setGender(Gender gender) {
		this->gender = gender;
	}

	string getName() {
		return this->name;
	}
	int getAge() {
		return this->age;
	}
	Race getRace() {
		return this->race;
	}
	Gender getGender() {
		return this->gender;
	}
};

class Player : public Character {
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
	Player () : Character () {
		health = 100;
	}
};

class NPC : public Character {
public:
	NPC (
	    string _name,
	    unsigned int _age,
	    Race _race,
	    Gender _gender) : Character (_name, _age, _race, _gender) {
		cout << _name << "spawns." << endl;
	}
};

void createPlayer (Player* p) {
	string name;
	int age;
	cout << "Choose the name of your character: ";
	cin >> name;
	p->setName(name);
	cout << "How old is your character?";
	cin >> age;
	p->setAge(age);
	unsigned char option;
	while(true) {
		cout << "Choose type of character: " << endl;
		cout << "1. " << raceToString(HUMAN) << endl;
		cout << "2. " << raceToString(FAIRY) << endl;
		cout << "3. " << raceToString(ELF) << endl;
		cout << "4. " << raceToString(SPIDER) << endl;
		cin >> option;
		switch (option) {
		case '1':
			p->setRace(HUMAN);
			break;
		case '2' :
			p->setRace(FAIRY);
			break;
		case '3' :
			p->setRace(ELF);
			break;
		case '4' :
			p->setRace(SPIDER);
			break;
		default:
			cout << "Invalid option." << endl;
			continue;
		}
		break;
	}
}

void printPlayer (Player* _p) {
	cout << "Player's name is " << _p->getName() << " You are a " << _p->getGender() <<
	     " " << raceToString(_p->getRace()) << " and you are " << _p->getAge() << " years old. ";
}

int main () {
	Player* playermain = new Player();

	int choice;
	while(1) {
		cout << "=== GAME MENU ===" << endl;
		cout << "1. Play" << endl;
		cout << "2. Exit" << endl;
		cout << "Choose: ";
		cin >> choice;

		if (choice == 2) {
			return 0;
		}
		else if (choice == 1) {
			createPlayer(playermain);
			printPlayer(playermain);
			break;
		}
		else {
			cout << "Invalid choice." << endl;
		}
	}
	return 0;
}