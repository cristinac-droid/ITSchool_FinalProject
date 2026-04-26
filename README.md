# ITSchool_FinalProject
Proiect Final

This is a text-based adventure game, console-based, written in C++, in which the player explores a forest, interacts with characters, collects items in their inventory and uses them on occation, and unlocks achievements based on their decisions.

It's a branching narrative game, where the player decisions infleunce the final outcome - and you can get either a good or a bad ending.

It demonstrates core object-oriented programming concepts in C++, including:

Inheritance and polymorphism
Virtual Functions
Design patterns - Singleton pattern
Basic file I/O
STL containers (vector, list, unordered_map)
Error Handling

Game Flow:

Starting from the main menu, you can choose to play or quit the game.
Then, you get to create your character by inputting a few details and choosing from a list of options.
First thing afterwards, you get to choose between 3 different options: following the path ahead, following the stream or following the smoke.
You get to interact with various NPCs, collect and use items, unlock achievements, and finally reach a good or a bad ending.

Structure:

The core class is the Character class, with attributes such as name, age, race and gender and it has a virtual method speak().
The Player class inherits from Character, but it also has a health system, alive/dead state and achievement tracking.
The final NPC class has race-specific dialogue.

Inventory: 

Stores the name of the item and the quantity.
Using Singleton as a creation design pattern for the Inventory (only one instance exsits). It includes the following methods: addItem(), removeItem(), hasItem(), printItems().

The game is made up of several scenes, each of them impacting inventory, achievements and player survival.
The achievements are loaded from an external file called achievements.txt.
