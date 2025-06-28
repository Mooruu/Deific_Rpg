#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <string_view>

using json = nlohmann::json;

std::map<std::string, std::string> Items;

std::map <std::string, std::pair<int, int>> WeaponCharacte;

void LoadWeaponCharacte() {
	std::ifstream input("WeaponCharacteristicsBase.json");
	json loadedData = json::parse(input);
	for (auto it = loadedData.begin(); it != loadedData.end(); ++it) {
		std::string weapon = it.key();
		json stats = it.value();

		if (stats.is_array() && stats.size() >= 2) {
			std::pair<int, int> stat;
			stat.first = stats[0].get<int>();
			stat.second = stats[1].get<int>();
			WeaponCharacte[weapon] = stat;
		}
	}
	input.close();
}

int binpoisk(std::string item, std::vector < std::pair < std::string, int>> inventory) {
	int l = 0, r = inventory.size() - 1, midl = (r+l)/2;
	while (r - l > 1) {
		midl = (r + l) / 2;
		if (inventory[midl].first > item) {
			r = midl;
		}
		else {
			l = midl;
		}
	}
	if (inventory[midl].first == item) {
		return midl;
	}
	else if (inventory[r].first == item) {
		return r;
	}
	else if (inventory[l].first == item) {
		return l;
	}
	else {
		return -1;
	}
}

class Inventory {

private:
	
	std::map <std::string, int> inventory;

public:

	Inventory(){}
	~Inventory(){}


	std::map <std::string, int> GetInventory() {
		return inventory;
	}//эффективность

	void EnterInventory(std::string name){
		if (!inventory[name]) {
			inventory[name] = 1;
		}
		else {
			inventory[name] += 1;
		}
	}

	void DeleteItem(std::string &item) {
		if (inventory[item] == 1) {
			inventory.erase(item);
		}
		else if (inventory[item] >1){
			inventory[item] -= 1;
		}
		else {
			std::cout << "You haven't get this item" << "\n";
			std::cout << "|---------------------------------------------|" << "\n";
		}
	}

	void SeeInventory() {
		std::cout << "You Inventory:" << "\n";
		if(inventory.size() == 0){
			std::cout << "Empty" << "\n";
		}
		else {
			for (auto& s : inventory) {
				std::cout << s.first << " :" << s.second << " slots" << "\n";
			}
		}
		std::cout << "|---------------------------------------------|" << "\n";
	}

	bool CheckItem(std::string& name) {
		if (!inventory[name]) {
			return 0;
		}
		else {
			return 1;
		}
	}
};

class Person {

private:

	int health = 0;
	int power = 0;
	int armor = 0; 
	int evasion = 0; 
	int evasioncoef = 1;
	int TurnCoef;
	Inventory inventory;
	std::string weapon = "No";

public:

	Person(){}
	~Person(){}

	Person(int health_, int power_, int armor_, int evasion_, Inventory inventory_, std::string weapon_) {
		health = health_;
		power = power_;
		armor = armor_;
		evasion = evasion_;
		inventory = inventory_;
		weapon = weapon_;
	}

	void Loadweapon(std::string weapon_) {
		weapon = weapon_;
	}
	
	void LoadCaracte(int stat, int variant) {
		if (variant == 1) {
			health += stat;
		}
		else if (variant == 2) {
			power += stat;
		}
		else if (variant == 3) {
			armor += stat;
		}
		else if (variant == 4) {
			evasion += stat;
		}
	}

	void CopyHero(Person Clone) {
		health = Clone.GetHealth();
		power = Clone.GetPower();
		armor = Clone.GetArmor();
		evasion = Clone.GetEvasion();
		inventory = Clone.GetInventory();
		weapon = Clone.GetWeapon();
	}

	void DeleteItemInventory(std::string& item) {
		inventory.DeleteItem(item);
	}

	void SeeItemInventory() {
		inventory.SeeInventory();
	}

	void EnterItemInventory(std::string& item) {
		inventory.EnterInventory(item);
	}

	std::string GetWeapon() {
		return weapon;
	}

	void EnterEvasioncoef() {
		evasioncoef = 2;
	}

	void DownEvasioncoef() {
		evasioncoef = 1;
	}

	void EnterHealth(int newhealth) {
		health = newhealth;
	}

	int GetEvasioncoef() {
		return evasioncoef;
	}

	void EnterTurnCoef(int Turn) {
		TurnCoef = Turn + 2;
	}

	void SeeInventory() {
		inventory.SeeInventory();
	}
	
	void DeleteItem(std::string item) {
		inventory.DeleteItem(item);
	}

	void SeeStats(bool who) {
		if (who == true) {
			std::cout << "Reynar has: " << health << " health, " << power << " power, " << armor << " armor, " << evasion << " evasion." << "\n";
		}
		else {
			std::cout << "Enemy has: " << health << " health, " << power << " power, " << armor << " armor, " << evasion << " evasion." << "\n";
		}
	}

	void CheckTurnCoef(int Turn) {
		if (TurnCoef <= Turn) {
			evasioncoef = 1;
		}
	}

	int GetTurnCoef() {
		return TurnCoef;
	}

	bool CheckInventory(std::string &name) {
		return inventory.CheckItem(name);
	}

	int GetHealth() {
		return health;
	}

	int GetPower() {
		return power;
	}

	int GetArmor() {
		return armor;
	}

	int GetEvasion() {
		return evasion;
	}

	Inventory GetInventory() {
		return inventory;
	}

	void EnterWeapon(std::string &name) {
		LoadWeaponCharacte();
		if (weapon == "No") {
			weapon = name;
			power += WeaponCharacte[name].first;
			armor += WeaponCharacte[name].second;
		}
		else {
			power -= WeaponCharacte[weapon].first;
			armor -= WeaponCharacte[weapon].second;
			weapon = name;
			power += WeaponCharacte[name].first;
			armor += WeaponCharacte[name].second;
		}
	}


	void GetLvl() {
		std::string choice;
		std::cout << "What you want to up?" << "\n";
		std::cout << "Health, attack, armor, evasion?" << "\n";
		std::cin >> choice;
		if (choice == "attack" || choice == "Attack") {
			power++;
		}
		else if (choice == "Armor" || choice == "armor") {
			armor++;
		}
		else if (choice == "Evasion" || choice == "evasion") {
			evasion = std::min(100, evasion+2);
		}
		else if (choice == "Health" || choice == "health") {
			health += 2;
		}

	}
};