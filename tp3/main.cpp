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
		int nTables;
		int nCompagnies;
		
		file >> nTables;
		// Initialisation des tables
		vector<Table> listeTables;
		listeTables.reserve(nTables);
		for (int i = 0; i < nTables; ++i) {
			listeTables.push_back(0);
		}
		// Initialisation des compagnies
		file >> nCompagnies;
		vector<Compagnie> listeCompagnies;
		listeCompagnies.reserve(nCompagnies);
		int nParticipants;
		for (int i = 0; i < nCompagnies; ++i) {
			cin >> nParticipants;
			listeCompagnies.push_back(Compagnie(nParticipants));
		}
		
	}
    return 0;
}
