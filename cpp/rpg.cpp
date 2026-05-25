#include <iostream>

class Character {
protected:
	std::string type;
	std::string name;
	double damage;
	int health;

public:
	Character(std::string type, std::string name, double damage, int health) {
		this->type = type;
		this->name = name;
		this->damage = damage;
		this->health = health;
	}
	virtual ~Character() { std::cout << "Destructing Character..." << std::endl; }
	virtual void attack() = 0;
	virtual void takeDamage(int damage) { health -= damage; }
	virtual std::string currentStatus() { return type + " " + name + " is at " + std::to_string(health) + "hp."; }
	bool isAlive() { return health != 0; }
	std::string getName() { return name; }
};

class Warrior : public Character {
public:
	Warrior(std::string name) : Character("Warrior", name, 100, 600) {};
	~Warrior() { std::cout << "Destructing Warrior..." << std::endl; }
	void attack() override {
		// implement attack logic
	}
	void takeDamage(int damage) override { health -= (damage * 0.8); }
};

class Mage : public Character {
	int mana;

public:
	Mage(std::string name) : Character("Mage", name, 120, 500) {};
	~Mage() { std::cout << "Destructing Mage..." << std::endl; }
	void attack() override {
		// implement attack logic with mana costs
	}
};

class Archer : public Character {
public:
	Archer(std::string name) : Character("Archer", name, 100, 500) {};
	~Archer() { std::cout << "Destructing Archer..." << std::endl; }
	void attack() override {
		// implement attack logic with 25% crit chance
	}
};

int main() {
	Warrior w1("Jon");
	Mage m1("Sam");
	Archer a1("Jam");
	std::cout << w1.currentStatus() << std::endl;
	std::cout << m1.currentStatus() << std::endl;
	std::cout << a1.currentStatus() << std::endl;
	return 0;
}
