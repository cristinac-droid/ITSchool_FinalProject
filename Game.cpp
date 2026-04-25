#include <iostream>
#include <list>
#include <memory>
#include <string>
#include <algorithm>
#include <vector>
#include <map>
#include <limits>
#include <fstream>
#include <sstream>
#include <unordered_map>

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

int safeInput() {
	int x;
	cin >> x;

	if (cin.fail()) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		throw runtime_error("Invalid input.");
	}
	return x;
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

	virtual void speak(Character* other) {
		cout << "..." << endl;
	}

	virtual ~Character() {}
};

class Player : public Character {
	int health;
	vector<string> reachedAchievements;
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
public:
	vector<string> getReachedAchievements() {
		return this->reachedAchievements;
	}
	void setReachedAchievements(vector<string> reachedAchievements) {
		this->reachedAchievements = reachedAchievements;
	}
	void addAchievement(string code) {
		this->reachedAchievements.push_back(code);
		cout << "New Achievement Unlocked: " << code << endl;
	}
	void speak(Character* other) override {
		cout << "I'll be the hero of your story!" << endl;
	}
};

class NPC : public Character {
public:
	NPC (
	    string _name,
	    unsigned int _age,
	    Race _race,
	    Gender _gender) : Character (_name, _age, _race, _gender) {
		cout << endl << _name << " spawns." << endl;
	}
	void speak(Character* other) override {
		cout << endl << "Welcome to the forest, " << other->getName() << "! What would you like to do?" << endl;
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
		cout << endl << "Choose type of character: " << endl;
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
		cout << endl << "Choose your character's gender: " << endl;
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
	cout << endl << "Choose the name of your character: ";
	cin.ignore();
	getline(cin, name);
	p->setName(name);
	cout << endl << "How old is your character? ";
	cin >> age;
	p->setAge(age);
	readRace(p);
	readGender(p);
}

void printPlayer (Player* _p) {
	cout << endl << "Your name is " << _p->getName() << ". You are a(n) " << genderToString(_p->getGender()) <<
	     " " << raceToString(_p->getRace()) << " and you are " << _p->getAge() << " years old. ";
}

void coinScene(Player* player) {
	int choice;
	while(true) {
		cout << endl << "There's a shiny little coin in the dirt. Pick it up?" << endl;
		cout << "1. Yes" << endl << "2. No" << endl << "Choice: " << endl;
		try {
			choice = safeInput();

			if (choice == 1) {
				cout << endl << "You picked up the shiny coin." << endl;
				Inventory::getInstance().addItem("shiny coin", 1);
				break;
			}
			else if (choice == 2) {
				cout << endl << "No wish for you." << endl;
				break;
			}
			else {
				cout << "Invalid option." << endl;
			}
		}
		catch (...) {
			cout << "Invalid input!" << endl;

		}
	}
}

void wishChoiceScene(Player* player) {
	int choice2;

	while(true) {
		cout << endl << "You threw the coin in the well. What do you wish for?" << endl;

		cout << "1. Rotten fish" << endl << "2. Daisies." << endl << "Choice: " << endl;

		try {
			choice2 = safeInput();

			if (choice2 == 1) {
				Inventory::getInstance().addItem("Rotten fish", 1);
				break;
			}
			else if (choice2 == 2) {
				Inventory::getInstance().addItem("Daisies", 3);
				break;
			}
			else {
				cout << "Invalid option." << endl;
			}
		}
		catch (...) {
			cout << "Invalid input!" << endl;
		}
	}
}

void wishScene(Player* player) {
	int choice1;

	while(true) {
		cout << "Make a wish?" << endl;
		cout << "1. Yes" << endl << "2. No" << endl << "Choice: " << endl;

		try {
			choice1 = safeInput();

			if (choice1 == 1) {
				cout << endl << "You threw the coin in the well." << endl;
				Inventory::getInstance().removeItem("shiny coin", 1);

				wishChoiceScene(player);
				break;
			}
			else if (choice1 == 2) {
				cout << endl << "You're missing out on perfectly delicious rotten fish." << endl;
				break;
			}
			else {
				cout << "Invalid option." << endl;
			}
		}
		catch (...) {
			cout << "Invalid input!" << endl;
		}
	}
}

void emptyWellScene(Player* player) {
	int choice;
	int choice2;

	while(true) {
		cout << endl << "Look inside?" << endl;
		cout << "1. Yes" << endl << "2. No" << endl << "Choice: ";

		try {
			choice = safeInput();

			if (choice == 1) {
				cout << endl << "The darkness is alluring. Jump?" << endl;
				cout << endl<< "1. Yes" << endl << "2.No" << endl << "Choice: ";

				choice2 = safeInput();

				if (choice2 == 1) {
					cout << endl << "You fell and broke your legs. No way out." << endl;
					cout << "They never found your body." << endl;
					player->addAchievement("Death");
					break;
				}

				cout << endl << "Are you sure?" <<endl;
				cout << "1. I'm jumping" << endl << "2. Yes, I'm sure" << endl << "Choice: ";

				choice = safeInput();

				if (choice == 1) {
					cout << endl << "You fell and broke your legs. No way out." << endl;

					player->addAchievement("Death");
					break;
				}
			}
			else if (choice == 2) {
				cout << endl << "Good choice. The abyss is calling." << endl;
				break;
			}
			else {
				cout << "Invalid option." << endl;
			}
		}
		catch (...) {
			cout << "Invalid input!" << endl;
		}
	}
}

void wellScene(Player* player) {
	cout << endl << "You find a clearing with a deep dark well." << endl;

	if (Inventory::getInstance().hasItem("shiny coin")) {
		wishScene(player);
	}
	else {
		emptyWellScene(player);
	}
}

void pathScene(Player* player) {
	coinScene(player);
	wellScene(player);
}

void startScene(Player* player) {
	while(true) {
		cout << endl << "You are at a crossroads in a deep dark forest." << endl;

		NPC guide("Forest Spirit", 100, FAIRY, OTHER);
		guide.speak(player);

		int choice;

		cout << "1. Follow the path in front of you" << endl;
		cout << "2. Follow the stream" << endl;
		cout << "3. Follow the smoke, maybe there's people" << endl;
		cout << "Choose: ";

		try {
			choice = safeInput();

			switch (choice) {
			case 1:
				pathScene(player);
				break;
			case 2:
				cout << "You follow the stream... (not implemented yet)" << endl;
				break;
			default:
				cout << "Invalid choice" << endl;
			}

			break;
		}
		catch (...) {
			cout << "Invalid input!" << endl;
		}
	}
}

void loadAchievements(unordered_map<string, string>& achievements) {
	ifstream file("achievements.txt");

	if (!file.is_open()) {
		cout << "Error opening achievements file." << endl;
		return;
	}

	string line;

	while (getline(file, line)) {
		stringstream ss(line);
		string key;
		string value;

		// Read key from file (before comma)
		getline(ss, key, ',');

		// Read value from file (rest of the line)
		getline(ss, value);

		achievements[key] = value;
	}

	file.close();
}

void printAllAchievements(
    const unordered_map<string, string>& achievements,
    Player* player) {

	cout << endl << "=== ACHIEVEMENTS ===" << endl;

	vector<string> reached = player->getReachedAchievements();

	// Reached achievements
	cout << endl << "Unlocked:" << endl;
	for (const auto& pair : achievements) {
		for (const string& code : reached) {
			if (pair.first == code) {
				cout << pair.first << " - " << pair.second << endl;
			}
		}
	}

	// Missing achievements
	cout << endl << "Locked:" << endl;
	for (const auto& pair : achievements) {
		bool found = false;

		for (const string& code : reached) {
			if (pair.first == code) {
				found = true;
				break;
			}
		}

		if (!found) {
			cout << pair.first << " - ???" << endl;
		}
	}
}

int main () {
	Player* playermain = new Player();
	unordered_map<string, string> achievements;
	int choice;

	while(true) {
		cout << "=== GAME MENU ===" << endl;
		cout << "1. Play" << endl;
		cout << "2. Exit" << endl;
		cout << "Choose: ";

		try {
			choice = safeInput();

			if (choice == 2) {
				return 0;
			}
			else if (choice == 1) {
				createPlayer(playermain);
				loadAchievements(achievements);
				printPlayer(playermain);
				startScene(playermain);
				Inventory::getInstance().printItems();
				printAllAchievements(achievements, playermain);
				break;
			}
			else {
				cout << "Invalid choice." << endl;
			}
		}
		catch (...) {
			cout << "Invalid input!" << endl;
		}
	}
	return 0;
}