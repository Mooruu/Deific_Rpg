#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include "json.hpp"
#include <cmath>
#include "Map.h"

Map Swagastrion = EnterMap("Swagastrion.txt");
Map Edem = EnterMap("Edem.txt");
Map Alfhaim = EnterMap("Alfhaim.txt");
Map Lestrigon = EnterMap("Lestrigon.txt");

void RestartMap() {
	Swagastrion = EnterMap("Swagastrion.txt");
	Edem = EnterMap("Edem.txt");
	Alfhaim = EnterMap("Alfhaim.txt");
	Lestrigon = EnterMap("Lestrigon.txt");
}

using json = nlohmann::json;

void StartGame() {
	int variant = 1;
	bool leave = false;
	Walking Place;
	while (leave != true) {
		if (variant == 1) {
			Place.EnterPlace(Swagastrion);
		}
		else if (variant == 2) {
			Place.EnterPlace(Edem);
		}
		else if (variant == 3) {
			Place.EnterPlace(Alfhaim);
		}
		else if (variant == 4) {
			Place.EnterPlace(Lestrigon);
		}
		else if (variant == 5) {
			RestartMap();
			StartGame();
			break;
		}
		Place.CreatePlaceEvent();
		variant = Place.Walk();
	}
}

int main()
{
	StartGame();
}
