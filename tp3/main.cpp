#include <iostream>
#include <vector>
#include <fstream>

#include "table.h"
#include "compagnie.h"

using namespace std;

void printResult(vector<Table> &lTable) {
	cout << "---------- RESULTAT ----------" << endl;
	for (int i = 0; i < lTable.size(); i++) {
		cout << lTable[i];
	}
	cout << "fin" << endl;
}
int main(int argc, char* argv[]) {

    string fileName = argv[1];

	fstream file(fileName.c_str());
	
	if (file.is_open()) {
		int n;

		file >> n;
		cout << "nTable : " << n << endl;
		// Initialisation des tables
		vector<Table> listeTables;
		listeTables.reserve(n);
		for (int i = 0; i < n; ++i) {
			listeTables.push_back(0);
		}
		cout << "Table done" << endl;
		// Initialisation des compagnies
		file >> n;
		cout << "nCompagnie : " << n << endl;
		vector<Compagnie> listeCompagnies;
		listeCompagnies.reserve(n);
		int nParticipants;
		for (int i = 0; i < n; ++i) {
			file >> nParticipants;
			listeCompagnies.push_back(Compagnie(nParticipants, i, n));
		}
		cout << "Compagnie done" << endl;
		// Initialisation liste1 (ne pouvant pas être assis à la même table)
		file >> n;
		vector<pair<int, int> > liste1;
		liste1.reserve(n);
		int compagnieA, compagnieB;
		for (int i = 0; i < n; ++i) {
			file >> compagnieA >> compagnieB;
			liste1.push_back(pair<int, int>(compagnieA, compagnieB));
			listeCompagnies[compagnieA].ajouterRelation(compagnieB, 1);
			listeCompagnies[compagnieB].ajouterRelation(compagnieA, 1);
		}
		cout << "Liste1 done" << endl;
		// Initialisation liste2 (souhaitant être assis à la même table)
		file >> n;
		vector<pair<int, int> > liste2;
		liste2.reserve(n);
		for (int i = 0; i < n; ++i) {
			file >> compagnieA >> compagnieB;
			liste2.push_back(pair<int, int>(compagnieA, compagnieB));
			listeCompagnies[compagnieA].ajouterRelation(compagnieB, 2);
			listeCompagnies[compagnieB].ajouterRelation(compagnieA, 2);
		}
		cout << "Liste2 done" << endl;
		// Initialisation liste3 (souhaitant ne pas être assis à la même table)
		file >> n;
		vector<pair<int, int> > liste3;
		liste3.reserve(n);
		for (int i = 0; i < n; ++i) {
			file >> compagnieA >> compagnieB;
			liste3.push_back(pair<int, int>(compagnieA, compagnieB));
			listeCompagnies[compagnieA].ajouterRelation(compagnieB, 3);
			listeCompagnies[compagnieB].ajouterRelation(compagnieA, 3);
		}
		cout << "Liste3 done" << endl;
		
		// Algo
		for (int i = 0; i < listeCompagnies.size(); i++) {
			if (!listeCompagnies[i].isAssis()) {
				int bestIndexTable = 0;
				int bestPoints = -100;
				for (int j = 0; j < listeTables.size(); j++) {
					int points = listeTables[j].ajoutPossible(listeCompagnies[i]);
					if (points > bestPoints) {
						bestPoints = points;
						bestIndexTable = j;
					}
				}
				if (bestPoints != -100)
					listeTables[bestIndexTable].ajouterCompagnie(listeCompagnies[i]);
			}
		}
		printResult(listeTables);
	}
    return 0;
}
