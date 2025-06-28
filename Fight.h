#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <cmath>
#include <fstream>
#include "Person.h"
#include <ctime>
#include <random> 

using json = nlohmann::json;


class Fight {

private:

	Person MainHero;
	Person Enemy;

public:

	Fight() {}
	~Fight() {}
	
	Fight(Person &MainHero_, Person &Enemy_) {
		MainHero = MainHero_;
		Enemy = Enemy_;
	}

	void InfoInventory() {
		std::cout << "What you want do with Item?" << "\n";
		std::cout << "See all inventory --- See" << "\n";
		std::cout << "Enter weapon -- name weapon" << "\n";
	}

	void Attack(Person &First, Person &Second, bool who) {

		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> dist(1, 100);

		int RandomAttack = dist(gen)%5;
		int Formula = First.GetPower() + RandomAttack - Second.GetArmor();
		int RandomEvasion = dist(gen);

		if (RandomEvasion <= Second.GetEvasion() * Second.GetEvasioncoef()) {
			if (who == 1) {
				std::cout << "Your attack = " << Formula << ", but he Evasion" << "\n";
				std::cout << "|---------------------------------------------|" << "\n";
			}
			else {
				std::cout << "Enemy attack = " << Formula << ", but he Evasion" << "\n";
				std::cout << "|---------------------------------------------|" << "\n";
			}
		}
		else if (Formula > 0) {
			Second.EnterHealth(Second.GetHealth() - Formula);
			if (who == 1) {
				std::cout << "Your attack " << Formula << ". Enemy has " << Second.GetHealth() << " Health" << "\n";
				std::cout << "|---------------------------------------------|" << "\n";
			}
			else {
				std::cout << "Enemy attack " << Formula << ". Hero has " << Second.GetHealth() << " Health" << "\n";
				std::cout << "|---------------------------------------------|" << "\n";
			}
		}
		else {

			if (who == 1) {
				std::cout << "You hasn't get some attack" << "\n";
				std::cout << "|---------------------------------------------|" << "\n";
			}

			else {
				std::cout << "Enemy hasn't get some attack" << "\n";
				std::cout << "|---------------------------------------------|" << "\n";
			}
		}
	}

	void Info() {
		std::cout << "you can chase some variants:" << "\n";
		std::cout << "Attack enenmy --- 'Attack'" << "\n";
		std::cout << "Increase the chance of evasion --- 'Evasion'" << "\n";
		std::cout << "Open inventory --- 'Inventory'" << "\n";
		std::cout << "|---------------------------------------------|" << "\n";
	}

	void Turn(Person &First, Person &Second, int step, bool who) {//bool
		if (who == true) {
			std::string choice;
			Info();
			std::cin >> choice;
			if (choice == "Attack" || choice == "attack") {
				Attack(First, Second, who);
			}
			else if (choice == "Evasion" || choice == "evasion") {
				std::cout << "You double your Evasion" << "\n";
				First.EnterEvasioncoef();
			}
			else if (choice == "Inventory" || choice == "inventory") {
				First.SeeInventory();
				InfoInventory();
				std::string variant;
				std::cin >> variant;
				if (variant == "See") {
					First.SeeInventory();
				}
				else {
					bool answer = First.CheckInventory(variant);
					if(answer == true){
						First.EnterWeapon(variant);
					}
					else {
						std::cout << "Enter correct answer" << "\n";
						std::cout << "|---------------------------------------------|" << "\n";
					}
				}
				Turn(First, Second, step, who);
			}
			else {
				std::cout << "Enter correct answer" << "\n";
				std::cout << "|---------------------------------------------|" << "\n";
			}
		}
		else {
			int EnemyFight = rand() % 2;
			if (EnemyFight == 1) {
				std::cout << "Enemy double his Evasion" << "\n";
				Enemy.EnterEvasioncoef();
			}
			else {
				Attack(First, Second, who);
			}
		}
	}

	bool fight() {
		MainHero.SeeStats(true);
		Enemy.SeeStats(false);
		int CheckTurn = rand() % 2, step = 0;
		if (CheckTurn % 2 == 0) {
			while (MainHero.GetHealth() > 0 && Enemy.GetHealth() > 0) {
				step++;
				MainHero.CheckTurnCoef(step);
				Turn(MainHero, Enemy, step, 1);
				if (MainHero.GetHealth() > 0 && Enemy.GetHealth() > 0) {
					Enemy.CheckTurnCoef(step);
					Turn(Enemy, MainHero, step, 0);
				}
			}
		}
		else {
			while (MainHero.GetHealth() > 0 && Enemy.GetHealth() > 0) {
				step++;
				Turn(Enemy, MainHero, step, 0);
				if (MainHero.GetHealth() > 0 && Enemy.GetHealth() > 0) {
					Turn(MainHero, Enemy, step, 1);
				}
			}
		}
		if (MainHero.GetHealth() < 0) {
			return 0;
		}
		else {
			return 1;
		}
	}

	void FightResult(bool result) { //bool 
		if (result == 0) {
			//game_restart();
		}
	}
};


