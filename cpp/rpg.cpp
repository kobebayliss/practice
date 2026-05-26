#include <iostream>
#include <random>
#include <string>

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
	virtual void attack(Character& target) = 0;
	virtual void takeDamage(int damage) { health -= damage; }
	virtual std::string currentStatus() { return type + " " + name + " is at " + std::to_string(health) + "hp."; }
	bool isAlive() { return health > 0; }
	std::string getName() { return name; }
};

class Warrior : public Character {
public:
	Warrior(std::string name) : Character("Warrior", name, 100, 600) {};
	~Warrior() { std::cout << "Destructing Warrior..." << std::endl; }
	void attack(Character& target) override {
		if (!target.isAlive()) {
			std::cout << target.getName() + " is already dead." << std::endl;
			return;
		}
		target.takeDamage(damage);
		std::cout << name + " attacked " + target.getName() + " dealing " + std::to_string(damage) + " damage." << std::endl;
		if (!target.isAlive()) {
			std::cout << name + " killed " + target.getName() + "!" << std::endl;
		}
	}
	void takeDamage(int damage) override { health -= (damage * 0.8); }
};

class Mage : public Character {
	int mana = 1000;

public:
	Mage(std::string name) : Character("Mage", name, 120, 500) {};
	~Mage() { std::cout << "Destructing Mage..." << std::endl; }
	void attack(Character& target) override {
		mana -= 200;
		if (mana <= 0) {
			std::cout << name + " is out of mana!" << std::endl;
			return;
		}
		if (!target.isAlive()) {
			std::cout << target.getName() + " is already dead." << std::endl;
			return;
		}
		target.takeDamage(damage);
		std::cout << name + " attacked " + target.getName() + " dealing " + std::to_string(damage) + " damage." << std::endl;
		if (!target.isAlive()) {
			std::cout << name + " killed " + target.getName() + "!" << std::endl;
		}
	}
};

class Archer : public Character {
public:
	Archer(std::string name) : Character("Archer", name, 100, 500) {};
	~Archer() { std::cout << "Destructing Archer..." << std::endl; }
	void attack(Character& target) override {
		if (!target.isAlive()) {
			std::cout << target.getName() + " is already dead." << std::endl;
			return;
		}
		float total_damage;
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<double> dis(0.0, 1.0);
		if (dis(gen) <= 0.2) {
			total_damage = 1.25 * damage;
		} else {
			total_damage = damage;
		}
		target.takeDamage(total_damage);
		std::cout << name + " attacked " + target.getName() + " dealing " + std::to_string(total_damage) + " damage." << std::endl;
		if (!target.isAlive()) {
			std::cout << name + " killed " + target.getName() + "!" << std::endl;
		}
	}
};

class Goblin : public Character {
public:
	Goblin() : Character("Goblin", "Larry", 150, 300) {};
	~Goblin() { std::cout << "Destructing Goblin..." << std::endl; }
	void attack(Character& target) override {
		if (!target.isAlive()) {
			std::cout << target.getName() + " is already dead." << std::endl;
			return;
		}
		target.takeDamage(damage);
		std::cout << name + " attacked " + target.getName() + " dealing " + std::to_string(damage) + " damage." << std::endl;
		if (!target.isAlive()) {
			std::cout << name + " killed " + target.getName() + "!" << std::endl;
		}
	}
};

class Troll : public Character {
public:
	Troll() : Character("Troll", "Perry", 75, 1000) {};
	~Troll() { std::cout << "Destructing Troll..." << std::endl; }
	void attack(Character& target) override {
		if (!target.isAlive()) {
			std::cout << target.getName() + " is already dead." << std::endl;
			return;
		}
		target.takeDamage(damage);
		std::cout << name + " attacked " + target.getName() + " dealing " + std::to_string(damage) + " damage." << std::endl;
		if (!target.isAlive()) {
			std::cout << name + " killed " + target.getName() + "!" << std::endl;
		}
	}
};

int main() {
	Warrior w1("Jon");
	Mage m1("Sam");
	Archer a1("Jam");
	Goblin g1;
	Troll t1;

	std::cout << "=== RPG Battle Test ===" << std::endl;
	std::cout << w1.currentStatus() << std::endl;
	std::cout << m1.currentStatus() << std::endl;
	std::cout << a1.currentStatus() << std::endl;
	std::cout << g1.currentStatus() << std::endl;
	std::cout << t1.currentStatus() << std::endl;

	std::cout << "\n-- Round 1 --" << std::endl;
	g1.attack(w1);
	t1.attack(w1);
	w1.attack(g1);
	m1.attack(g1);
	a1.attack(g1);
	std::cout << w1.currentStatus() << std::endl;
	std::cout << m1.currentStatus() << std::endl;
	std::cout << a1.currentStatus() << std::endl;
	std::cout << g1.currentStatus() << std::endl;
	std::cout << t1.currentStatus() << std::endl;

	std::cout << "\n-- Round 2 --" << std::endl;
	m1.attack(t1);
	m1.attack(t1);
	a1.attack(t1);
	std::cout << w1.currentStatus() << std::endl;
	std::cout << m1.currentStatus() << std::endl;
	std::cout << a1.currentStatus() << std::endl;
	std::cout << g1.currentStatus() << std::endl;
	std::cout << t1.currentStatus() << std::endl;

	std::cout << "\n-- Round 3 --" << std::endl;
	w1.attack(g1);
	m1.attack(t1);
	m1.attack(t1);
	a1.attack(t1);
	std::cout << w1.currentStatus() << std::endl;
	std::cout << m1.currentStatus() << std::endl;
	std::cout << a1.currentStatus() << std::endl;
	std::cout << g1.currentStatus() << std::endl;
	std::cout << t1.currentStatus() << std::endl;
	return 0;
}
