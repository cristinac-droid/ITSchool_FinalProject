#include <iostream>
#include <list>
#include <memory>
#include <string>
#include <algorithm>

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

string genderToString(Gender gender) {
	switch (gender) {
	case MALE:
		return "MALE";
	case FEMALE:
		return "FEMALE";
	case OTHER:
		return "OTHER";
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

class InventoryItem {
private:
	string name;
	int quantity;

public:
	InventoryItem(const string& name, int quantity)
		: name(name), quantity(quantity) {}

	const string& getName() const {
		return name;
	}

	int getQuantity() const {
		return quantity;
	}

	void setQuantity(int q) {
		quantity = q;
	}

	void increaseQuantity(int amount) {
		quantity += amount;
	}

	bool operator==(const InventoryItem& other) const {
		return name == other.name;
	}
};

class Inventory {
private:
	list<InventoryItem> items;

	Inventory() {}
// disabling copy constructor and assignment operator
	Inventory(const Inventory&) = delete;
	Inventory& operator=(const Inventory&) = delete;

public:
	static Inventory& getInstance() {
		static Inventory instance;
		return instance;
	}

	void addItem(const string& name, int quantity) {
		for (auto& item : items) {
			if (item.getName() == name) {
				item.increaseQuantity(quantity);
				return;
			}
		}
		items.push_back(InventoryItem(name, quantity));
	}

	void removeItem(const string& name, int quantity) {
		for (auto it = items.begin(); it != items.end(); ++it) {
			if (it->getName() == name) {
				int newQty = it->getQuantity() - quantity;

				if (newQty > 0) {
					it->setQuantity(newQty);
				} else {
					items.erase(it);
				}
				return;
			}
		}
	}

	void printItems() const {
	    cout << endl << "Inventory Items: " << endl;
		for (const auto& item : items) {
			cout << item.getName() << " (x" << item.getQuantity() << ")" << endl;
		}
	}

	bool hasItem(const string& name) const {
		for (const auto& item : items) {
			if (item.getName() == name) {
				return true;
			}
		}
		return false;
	}
};

void readRace (Player* p) {
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

void readGender (Player* p) {
	unsigned char option;
	while(true) {
		cout << "Choose your character's gender: " << endl;
		cout << "1. " << genderToString(MALE) << endl;
		cout << "2. " << genderToString(FEMALE) << endl;
		cout << "3. " << genderToString(OTHER) << endl;
		cin >> option;
		switch (option) {
		case '1':
			p->setGender(MALE);
			break;
		case '2' :
			p->setGender(FEMALE);
			break;
		case '3' :
			p->setGender(OTHER);
			break;
		default:
			cout << "Invalid option." << endl;
			continue;
		}
		break;
	}
}

void createPlayer (Player* p) {
	string name;
	int age;
	cout << "Choose the name of your character: ";
	cin.ignore();
	getline(cin, name);
	p->setName(name);
	cout << "How old is your character? ";
	cin >> age;
	p->setAge(age);
	readRace(p);
	readGender(p);
}

void printPlayer (Player* _p) {
	cout << "Your name is " << _p->getName() << ". You are a(n) " << genderToString(_p->getGender()) <<
	     " " << raceToString(_p->getRace()) << " and you are " << _p->getAge() << " years old. ";
}

void pathScene() {
	int choice1;
	int choice2;
	int choice3;
	int choice4;

	cout << "There's a shiny little coin in the dirt. Pick it up?" << endl;
	cout << "1. Yes" << endl << "2. No" << endl << "Choice: " << endl;
	cin >> choice1;

	if (choice1 == 1) {
		cout << "You picked up the shiny coin." << endl;
		Inventory::getInstance().addItem("shiny coin", 1);
	}
	else if (choice1 == 2) {
		cout << "No wish for you." << endl;
	}

	cout << "You find a clearing with a deep dark well." << endl;

	if (Inventory::getInstance().hasItem("shiny coin")) {
		cout << "Make a wish?" << endl;
		cout << "1. Yes" << endl << "2. No" << endl << "Choice: " << endl;
		cin >> choice3;

		if (choice3 == 1) {
			cout << "You threw the coin in the well. What do you wish for?" << endl;
			Inventory::getInstance().removeItem("shiny coin", 1);
			cout << "1. Rotten fish" << endl << "2. Entrails." << endl << "Choice: " << endl;
			cin >> choice4;
			if (choice4 == 1) {
				Inventory::getInstance().addItem("Rotten fish", 1);
			}
			else if (choice4 == 2) {
				Inventory::getInstance().addItem("Entrails", 3);
			}
		}
		else if (choice3 == 2) {
			cout << "You're missing out on perfectly delicious entrails." << endl;
		}
	}
	else {
		cout << "Look inside?" << endl;
		cout << "1. Yes" << endl << "2. No" << endl << "Choice: " << endl;
		cin >> choice2;

		if (choice2 == 2) {
			cout << "Good choice. The abyss is calling." << endl;
			return;
		}
	}
}

void startScene() {
	int choice;

	cout << endl << "You are at a crossroads in a deep dark forest." << endl;
	cout << "1. Follow the path in front of you" << endl;
	cout << "2. Follow the stream" << endl;
	cout << "3. Follow the smoke, maybe there's people" << endl;
	cout << "Choose: ";
	cin >> choice;

	switch (choice) {
	case 1:
		pathScene();
		break;
	case 2:
		cout << "You follow the stream... (not implemented yet)" << endl;
		break;
	default:
		cout << "Invalid choice" << endl;
	}
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
			startScene();
			Inventory::getInstance().printItems();
			break;
		}
		else {
			cout << "Invalid choice." << endl;
		}
	}
	return 0;
}