#include <iostream>
#include <vector>
#include <fstream>

#include "table.h"
#include "compagnie.h"

using namespace std;

int main(int argc, char* argv[]) {

    string fileName = argv[1];

	fstream file(fileName.c_str());
	
	if (file.is_open()) {
		int n;
		
		file >> n;
		// Initialisation des tables
		vector<Table> listeTables;
		listeTables.reserve(n);
		for (int i = 0; i < n; ++i) {
			listeTables.push_back(0);
		}
		// Initialisation des compagnies
		file >> n;
		vector<Compagnie> listeCompagnies;
		listeCompagnies.reserve(n);
		int nParticipants;
		for (int i = 0; i < n; ++i) {
			cin >> nParticipants;
			listeCompagnies.push_back(Compagnie(nParticipants, i));
		}
		vector<pair<int, int> > liste1;
		liste1.reserve(n);
		for (int i = 0; i < n; ++i) {
			cin >> compagnieA >> compagnieB;
			liste1.push_back(pair<int, int>(compagnieA, compagnieB));
		}
		
		// Initialisation liste2 (souhaitant être assis à la même table)
		file >> n;
		vector<pair<int, int> > liste2;
		liste2.reserve(n);
		for (int i = 0; i < n; ++i) {
			cin >> compagnieA >> compagnieB;
			liste2.push_back(pair<int, int>(compagnieA, compagnieB));
		}
		
		// Initialisation liste3 (souhaitant ne pas être assis à la même table)
		file >> n;
		vector<pair<int, int> > liste3;
		liste3.reserve(n);
		for (int i = 0; i < n; ++i) {
			cin >> compagnieA >> compagnieB;
			liste3.push_back(pair<int, int>(compagnieA, compagnieB));
		}
	}
    return 0;
}
