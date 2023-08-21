#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <fstream>

namespace MonsterGame { // Namespace for the game entities

    // Base class for all game entities
    class Entity {
    protected:
        //Member variable
        std::string name;
        int health;
        int damage;

    public:
        // Default constructor
        //Member initialization
        Entity() : name("Unnamed"), health(0) {}

        // Parameterized constructor
        Entity(const std::string& _name, int _health)
            : name(_name), health(_health) {}

        // Copy constructor
        Entity(const Entity& other) : name(other.name), health(other.health) {}

        // Destructor
        virtual ~Entity() {}

        //Inline
        inline const std::string& getName() const {
            return name;
        }

        int getHealth() const {
            return health;
        }

        void set_damage(int value)
        {
            damage = value;
        }

        // (dynamic) polymorphism
        virtual void takeDamage(int amount) {
            health -= amount;
            //Setter
            set_damage(amount);
            if (isDefeated()) {
                std::cout << getName() << " has been defeated!" << std::endl;
            }
        }

        //Member function
        int generateRandomDamage() const {
            return 1 + (rand() % 10); // Generates a random value between 1 and 10
        }

        // Polymorphic function demonstrating dynamic polymorphism
        // Call-by-reference
        virtual void attack(Entity& target) {
            int damageDealt = generateRandomDamage();
            //Getter
            std::cout << getName() << " attacks " << target.getName() << " for " << damageDealt << " damage!" << std::endl;
            target.takeDamage(damageDealt);
            std::cout << target.getName() << "'s health: " << target.getHealth() << std::endl;
        }

        bool isDefeated() const {
            return health <= 0;
        }

        void heal(int amount) {
            health += amount;
            std::cout << getName() << " is healed for " << amount << " health!" << std::endl;
            std::cout << getName() << "'s health: " << getHealth() << std::endl;
        }
    };

    // Derived class for characters
    class Character : public Entity {
    public:

        // Default constructor
        Character() : Character("Character", 0) {}

        // Copy constructor
        Character(const Character& other) {}
        
        // Call-by-reference
        using Entity::Entity;
        virtual void attack(Entity& target) override {
            Entity::attack(target);
        }

        virtual void performHealing(int amount = 20) {
            // By default, characters do not have a healing ability
            std::cout << getName() << " cannot perform healing." << std::endl;
        }

    };

    // Derived class for warriors
    class Warrior : public Character {
    public:
         // Default constructor
        Warrior() : Character("Unnamed Warrior", 150) {}

        // Parameterized constructor
        // Constructor forwarding
        Warrior(const std::string& _name)
            : Character(_name, 150) {}

        void attack(Entity& target) override {
            std::cout << getName() << " swings his sword!" << std::endl;
            Entity::attack(target);
        }

        // Destructor
        ~Warrior() {
            std::cout << "Warrior " << getName() << " has been destroyed!" << std::endl;
        }
    };

    // Derived class for mages
    class Mage : public Character {
    public:
        // Parameterized constructor
        Mage(const std::string& _name)
            : Character(_name, 100) {}

        void attack(Entity& target) override {
            std::cout << getName() << " casts a spell!" << std::endl;
            Entity::attack(target);
        }

        //Default value
        void performHealing(int amount = 20) override {
            heal(amount); // Mage can perform healing by restoring 20 health
        }

        // Destructor
        ~Mage() {
            std::cout << "Mage " << getName() << " has been destroyed!" << std::endl;
        }
    };

    // Derived class for monsters
    class Monster : public Entity {
    public:
        using Entity::Entity;
        void attack(Entity& target) override {
            Entity::attack(target);
        }
    };

} // End of namespace MonsterGame

int main() {
    //nullptr
    bool player_won;
    srand(time(nullptr));

    std::cout << "Welcome to the RPG game!" << std::endl;

    // Instantiate characters and monsters
    // Memory alloc
    MonsterGame::Warrior* warrior = new MonsterGame::Warrior(); // Using default constructor
    MonsterGame::Mage* mage = new MonsterGame::Mage("Mage");

    //Container class
    std::vector<MonsterGame::Monster> monsters = {
        MonsterGame::Monster("Goblin", 50),
        MonsterGame::Monster("Orc", 80)
    };

    // Choose player character
    std::cout << "Choose your character: (1) Warrior or (2) Mage: ";
    int choice;
    std::cin >> choice;

    //nullptr
    MonsterGame::Character* player = nullptr;

    if (choice == 1) {
        player = warrior;
    } else if (choice == 2) {
        player = mage;
    } else {
        std::cout << "Invalid choice. Exiting." << std::endl;
        return 1;
    }

    // Display chosen character
    std::cout << "You have chosen " << player->getName() << "." << std::endl;

    std::cout << "Welcome to the game! You encounter monsters:" << std::endl;
    for (const MonsterGame::Monster& monster : monsters) {
        std::cout << monster.getName() << std::endl;
    }

    while (!monsters.empty() && !player->isDefeated()) {
        // Check if all monsters are defeated or if the player is defeated
        if (std::all_of(monsters.begin(), monsters.end(), [](const MonsterGame::Monster& monster) { return monster.isDefeated(); })) {
            std::cout << "Congratulations! You have defeated all monsters." << std::endl;
            player_won = true;
            break;
        } else if (player->isDefeated()) {
            std::cout << "Unfortunately, " << player->getName() << " has been defeated." << std::endl;
            player_won = false;
            break;
        }

        std::cout << "Choose your action: (1) Attack, (2) Heal, or (3) Quit: ";
        std::cin >> choice;

        if (choice == 1) {
            for (MonsterGame::Monster& monster : monsters) {
                if (!monster.isDefeated()) {
                    player->attack(monster);
                    if (!monster.isDefeated()) {
                        monster.attack(*player);
                        std::cout << std::endl;
                    }
                }
            }
        } else if (choice == 2) {
            player->performHealing();
        } else if (choice == 3) {
            std::cout << "You chose to reschedule the fight and went home." << std::endl;
            break;
        } else {
            std::cout << "Invalid choice. Please choose again." << std::endl;
        }
    }

    // Save winner to a text file
    std::ofstream outFile("winner.txt");
    if (outFile.is_open()) {
        if(player_won) {
            outFile << "Winner: " << player->getName() << std::endl;
        }
        else {
         outFile << "The monsters won!" << std::endl;   
        }
        outFile.close();
        std::cout << "Winner saved to winner.txt" << std::endl;
    } else {
        //Execption handeling
        std::cerr << "Unable to open file for writing." << std::endl;
    }

     // Clean up memory
    delete warrior;
    delete mage;

    return 0;
}
