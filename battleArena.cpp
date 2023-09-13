// 3/18/2023
// This program uses inheritance and polymorphism to create a battling game between different creatures

#include <iostream>

using namespace std;

//The base class
class Creature {
private:
	int strength;
	int hitpoints;
	string creatureName;

public:
	Creature();
	Creature(int newStrength, int newHit);

	void setStrength(int s) { strength = s; }
	int getStrength() { return strength; };

	void setHitPoints(int h) { hitpoints = h; }
	int getHitPoints() { return hitpoints; };
	
	//Virtual functions in the base class
	virtual int getDamage();
	virtual string getSpecies() { return "Unknown"; }

};

//Derived class 1
class Human : public Creature {
private:
	string creatureName;

public:
	Human() : Creature(), creatureName("Human") {}
	Human(int newStrength, int newHit) :
		Creature(newStrength, newHit), creatureName("Human") {}

	int getDamage();
	string getName() { return creatureName; }

};

// Derived class 2
class Elf : public Creature {
private:
	string creatureName;

public:
	Elf() {
		creatureName = "Elf";
	}
	Elf(int newStrength, int newHit) :
		Creature(newStrength, newHit), creatureName("Elf") {}

	int getDamage();
	string getName() { return creatureName; }

};

// Derived class 3 AND base class 2
class Demon : public Creature {
private:
	string creatureName;

public:
	Demon() {
		creatureName = "Demon";
	}
	Demon(int newStrength, int newHit) :
		Creature(newStrength, newHit), creatureName("Demon") {}

	virtual int getDamage();
	string getName() { return creatureName; }

};

// Derived class 4
class Cyberdemon : public Demon {
private:
	string creatureName;

public:
	Cyberdemon() {
		creatureName = "Cyberdemon";
	}

	Cyberdemon(int newStrength, int newHit) :
		Demon(newStrength, newHit), creatureName("Cyberdemon") {}

	int getDamage();
	string getName() { return creatureName; }

};

//Derived class 5
class Balrog : public Demon {
private:
	string creatureName;

public:
	Balrog() {
		creatureName = "Balrog";
	}
	
	Balrog(int newStrength, int newHit) :
		Demon(newStrength, newHit), creatureName("Balrog") {}

	int getDamage();
	string getName() { return creatureName; }

};

//FUNCTION PROTOTYPE
void battleArena(Creature& creature1, Creature& creature2);

int main() {
	srand(static_cast<int>(time(NULL)));

	Human human1(30, 10);
	human1.getDamage();
	cout << endl;

	Elf elf1;
	elf1.getDamage();
	cout << endl;

	Balrog balrog1(50, 50);;
	balrog1.getDamage();
	cout << endl;

	Cyberdemon cdemon(30, 40);
	cdemon.getDamage();
	cout << endl;

	Elf elf2(50, 50);
	Balrog balrog2(50, 50);

	cout << endl;
	battleArena(elf2, balrog2);
}

Creature::Creature() {
	strength = 10;
	hitpoints = 10;
}

Creature::Creature(int newStrength, int newHit) {
	strength = newStrength;
	hitpoints = newHit;
}

int Creature::getDamage() {
	int damage;

	damage = (rand() % strength) + 1;
	
	return damage;
}

int Human::getDamage() {
	int damage = Creature::getDamage();

	cout << creatureName << " attacks for "
		<< damage << " points!" << endl;

	return damage;
}

int Elf::getDamage() {
	int damage = Creature::getDamage();

	cout << creatureName << " attacks for "
		<< damage << " points!" << endl;

	if ((rand() % 10) == 0)
	{
		cout << "Magical attack inflicts " << damage
			 << " additional damage points!" << endl;
		damage = damage * 2;
	}

	return damage;
}

int Demon::getDamage() {
	int damage = Creature::getDamage();

	if ((rand() % 100) < 5)
	{
		damage = damage + 50;
		cout << "Demonic attack inflicts 50 "
			 << " additional damage points!" << endl;
	}

	return damage;
}

int Cyberdemon::getDamage() {
	int damage = Demon::getDamage();

	cout << creatureName << " attacks for "
		 << damage << " points!" << endl;

	return damage;
}

int Balrog::getDamage() {
	int totalDamage = Demon::getDamage();

	cout << creatureName << " attacks for "
		 << totalDamage << " points!" << endl;

	int damage = Creature::getDamage();
	cout << "Balrog speed attack inflicts " << damage
		 << " additional damage points!" << endl;

	totalDamage += damage;

	return totalDamage;
}

void battleArena(Creature& creature1, Creature& creature2) {
	while (creature1.getHitPoints() > 0 && creature2.getHitPoints() > 0) {

		int damage = 0;
		int hP;

		damage = creature1.getDamage();
		hP = creature2.getHitPoints() - damage;

		creature2.setHitPoints(hP);

		cout << "Creature 2 has " << creature2.getHitPoints()
			 << " hit points." << endl;

		if(creature2.getHitPoints() < 0)
		{
			break;
		}

			damage = creature2.getDamage();
			hP = creature1.getHitPoints() - damage;

			creature1.setHitPoints(hP);

			cout << "Creature 1 has " << creature1.getHitPoints()
				<< " hit points." << endl;
	}

	if (creature1.getHitPoints() <= 0 && creature2.getHitPoints() <= 0) {
		cout << "Creature 2 has " << creature2.getHitPoints()
			 << " hit points." << endl;
		
		cout << endl << "Tie!" << endl;
	}
	else if (creature1.getHitPoints() > 0)
	{
		cout << endl << "Creature 1 wins!" << endl;
	}
	else
	{
		cout << endl << "Creature 2 wins!" << endl;
	}

	cout << "Press any key to continue...";
	cin.get();
}

/*
SAMPLE RUN:

Human attacks for 23 points!

Elf attacks for 5 points!

Balrog attacks for 46 points!
Balrog speed attack inflicts 23 additional damage points!

Cyberdemon attacks for 28 points!


Elf attacks for 13 points!
Creature 2 has 37 hit points.
Balrog attacks for 36 points!
Balrog speed attack inflicts 5 additional damage points!
Creature 1 has 9 hit points.
Elf attacks for 45 points!
Creature 2 has -8 hit points.

Creature 1 wins!
Press any key to continue...

C:\CIS22B Code\assignment7\x64\Debug\assignment7.exe (process 24000) exited
with code 0.
To automatically close the console when debugging stops, enable Tools->Options
->Debugging->Automatically close the console when debugging stops.
Press any key to close this window . . .

*/