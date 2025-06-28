#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <cmath>
#include <fstream>
#include "json.hpp"
#include "Fight.h"

std::map<std::string, Person> EnemyStats;
std::map<std::string, std::string> EnemyWeapon;

Person Reynar;

json WeaponEnemy = {
	{"Spider", "Venom_Fangs"},
	{"Abyss_Jellyfish", "Tentacle"},
	{"Mr_Mannera", "Silver_Cane"},
	{"Fire_Mage", "Inferno_Staff"},
	{"Light_Mage", "Holy_Scepter"},
	{"Giant", "Stone_Fist"},
	{"Dr_Diesel", "Industrial_Wrench"}
};

void LoadWeaponEnemy() {
	for (auto it = WeaponEnemy.begin(); it != WeaponEnemy.end(); ++it) {
		std::string name = it.key();
		std::string weapon = it.value();
		EnemyWeapon[name] = weapon;		
	}
}

void LoadEnemyCharacte() {
	std::ifstream input("EnemyCharacteristicsBase.json");
	json loadedData = json::parse(input);
	for (auto it = loadedData.begin(); it != loadedData.end(); ++it) {
		std::string weapon = it.key(); 
		json stats = it.value();        

		if (stats.is_array() && stats.size() >= 2) {
			std::pair<std::string, Person> stat;
			stat.first = weapon;
			Person LoadEnemy;
			for (int i = 0; i < stats.size(); i++) {
				LoadEnemy.LoadCaracte(stats[i], i + 1);
			}
			stat.second = LoadEnemy;
			EnemyStats[weapon] = LoadEnemy;
		}
	}
	input.close();
}

void LoadReynarCharacte() {
	std::ifstream input("Reynar.json");
	json loadedData = json::parse(input);
	for (auto it = loadedData.begin(); it != loadedData.end(); ++it) {
		std::string weapon = it.key();
		json stats = it.value();

		if (stats.is_array() && stats.size() >= 2) {
			Person LoadEnemy;
			for (int i = 0; i < stats.size(); i++) {
				Reynar.LoadCaracte(stats[i], i + 1);
			}
		}
	}
	input.close();
}


class Map{
private:
	Person MainHero;
	std::string NamePlace;
	std::map <std::string, Person> Enemys;
	int size;
	std::vector<std::vector<std::string>> Place;

public:
	Map(){}
	~Map(){}

	Map(int size_, std::vector<std::vector<std::string>> &Place_) {
		size = size_;
		Place.resize(size);
		Place = Place_;
	}

	void EnterSize(int size_) {
		size = size_;

	}

	void EnterName(std::string name) {
		NamePlace = name;
	}

	std::string GetName() {
		return NamePlace;
	}

	void EnterMainHero(Person Hero) {
		MainHero = Hero;
	}

	void EnterPlace(std::vector<std::vector<std::string>> &Place_) {
		Place = Place_;
	}

	void ResizeMap() {
		Place.resize(size, std::vector<std::string>(size));
	}

	Person GetPerson(std::string name) {
		return Enemys[name];
	}

	Person GetHero() {
		return MainHero;
	}

	void HeroGetLvl() {
		MainHero.GetLvl();
	}

	void SeeMap(int x, int y) {
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				if (x == i && y == j) {
					std::cout << "*" << " ";
				}
				else {
					std::cout << Place[i][j] << " ";
				}
			}
			std::cout << "\n";
		}
		std::cout << "|---------------------------------------------|" << "\n";
	}

	void LoadSquare(int x, int y) {
		Place[x][y] = "G";
	}

	void LoadRandomStat(int stats, int stat) {
		MainHero.LoadCaracte(stats, stat);
	}

	std::string SeeSquare(int x, int y) {
		return Place[x][y];
	}

	std::string FoundWeapon(std::string &name){
		if (EnemyWeapon.count(name) == 1) {
			return EnemyWeapon[name];
		}
		else {
			return "";
		}
	}
};

Map EnterMap(std::string &&name) {
	Map Edem;
	std::ifstream in(name);
	std::vector < std::vector < std::string>> s(10, std::vector<std::string>(10));
	if (in.is_open()) {
		std::string Char;
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				in >> Char;
				s[i][j] = Char;
			}
		}
	}
	Edem.EnterPlace(s);
	Edem.EnterSize(10);
	in.close();
	return Edem;
}

class Walking {
private:
	Map Place;
	Map PlaceEvent;
	int x = 9, y = 0;
	bool Leave = false;
	std::string variant;

public:
	Walking(){}
	~Walking(){}

	Walking(Map Walking_, int x_, int y_) {
		Place = Walking_;
		x = x_;
		y = y_;
	}

	void EnterPlace(Map Place_) {
		Place = Place_;
	}

	void LoadEnemy() {
		LoadEnemyCharacte();
		LoadReynarCharacte();
		LoadWeaponEnemy();
	}

	void CreatePlaceEvent() {
		std::vector<std::vector<std::string>> s(10, std::vector<std::string> (10));
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				if (Place.SeeSquare(i, j)[0] == 'F') {
					s[i][j] = "F";
				}
				else if (Place.SeeSquare(i, j)[0] == 'E') {
					s[i][j] = "E";
				}
				else if (Place.SeeSquare(i, j)[0] == 'G') {
					s[i][j] = "G";
				}
				else if (Place.SeeSquare(i, j)[0] == 'L') {
					s[i][j] = "L";
				}
			}
		}
		PlaceEvent.EnterPlace(s);
		PlaceEvent.EnterSize(10);
	}

	void InfoWalk() {
		std::cout << "Enter Right, Left, Up, Down to go this square" << "\n";
		std::cout << "|---------------------------------------------|" << "\n";
	}



	int Walk(){
		LoadEnemy();
		while (Leave != true) {

			PlaceEvent.SeeMap(x, y);
			InfoWalk();
			std::cin >> variant;

			if (variant == "Right" || variant == "right") {
				if(y<9){
					y += 1;
				}
				else {
					std::cout << "\n";
					std::cout << "|------------------------------------------|" << "\n";
					std::cout << "The boundary of the World has been reached" << "\n";
					std::cout << "|------------------------------------------|" << "\n";
					std::cout << "\n";
				}
			}
			else if (variant == "Left" || variant == "left") {
				if (y > 0) {
					y -= 1;
				}
				else {
					std::cout << "\n";
					std::cout << "|---------------------------------|" << "\n";
					std::cout << "This Is The Border Of The World!!!" << "\n";
					std::cout << "|---------------------------------|" << "\n";
					std::cout << "\n";
				}
			}
			else if (variant == "Up" || variant == "up") {
				if (x > 0) {
					x -= 1;
				}
				else {
					std::cout << "\n";
					std::cout << "|---------------------------------|" << "\n";
					std::cout << "This Is The Border Of The World!!!" << "\n";
					std::cout << "|---------------------------------|" << "\n";
					std::cout << "\n";
				}
			}
			else if (variant == "Down" || variant == "down") {
				if (x < 9) {
					x += 1;
				}
				else {
					std::cout << "\n";
					std::cout << "|---------------------------------|" << "\n";
					std::cout << "This Is The Border Of The World!!!" << "\n";
					std::cout << "|---------------------------------|" << "\n";
					std::cout << "\n";
				}
			}
			else {
				std::cout << "\n";
				std::cout << "|------------------|" << "\n";
				std::cout << "Enter correct word!" << "\n";
				std::cout << "|------------------|" << "\n";
				std::cout << "\n";
			}

			if (Place.SeeSquare(x, y)[0] == 'L') {
				std::string str = Place.SeeSquare(x, y);
				str.erase(0, 1);
				if(str == "Swagastrion"){
					return 1;
				}
				else if (str == "Lestrigon") {
					return 2;
				}
				else if (str == "Edem") {
					return 3;
				}
				else if (str == "Alfhaim") {
					return 4;
				}
			}

			else if (PlaceEvent.SeeSquare(x, y) == "E") {
				std::random_device rd;
				std::mt19937 gen(rd());
				std::uniform_int_distribution<int> dist(1, 67);

				int RandomStat = dist(gen) % 5 - 2;
				int Stat = dist(gen)%4+1;
				Reynar.LoadCaracte(RandomStat, Stat);
				Reynar.SeeStats(true);
			}

			else if (PlaceEvent.SeeSquare(x, y) == "F") {
				std::string str = Place.SeeSquare(x, y);
				str.erase(0, 1);
				Fight Heros(Reynar, EnemyStats[str]);
				bool result = Heros.fight();
				if (result == 1) {
					Reynar.GetLvl();
					Reynar.SeeStats(true);
					std::string answer = Place.FoundWeapon(str);
					if (answer != "") {
						Reynar.EnterItemInventory(answer);
					}
				}
				else {
					return 5;
				}
			}
			Place.LoadSquare(x, y);
			PlaceEvent.LoadSquare(x, y);
		}
	}
};


