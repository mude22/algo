#include <iostream>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include <cmath>
#include "table.h"
#include "compagnie.h"

using namespace std;

vector<Compagnie> listeCompagnies;
vector<Table> listeTables;

float calculEcartType() {
	int somme = 0;
	for(int i = 0; i < listeTables.size(); i++) {
		somme += listeTables[i].getNbPersonnes();
	}
	float moyenne = somme/(float)listeTables.size();
	
	float total = 0, ecart, variance;
	
	for(int i = 0; i < listeTables.size(); i++) {
		ecart = listeTables[i].getNbPersonnes() - moyenne;
		total += ecart*ecart;
	}
	
	variance = total / (float)listeTables.size();
	return (sqrt(variance));
}

int calculPoids() {
	int poids = 0;
	for(int i = 0; i < listeTables.size(); i++) {
		poids += listeTables[i].getPoids();
	}
	// divisé en deux parce qu'on le calcule deux fois
	return poids/2;
}

void printResult(vector<Table> &lTable) {
	cout << "---------- RESULTAT ----------" << endl;
	for (int i = 0; i < lTable.size(); i++) {
		cout << lTable[i];
	}
	cout << "fin" << endl;
	cout << "Écart-type : " << calculEcartType() << endl;
	cout << "Poids : " << calculPoids() << endl;
}

void doChange(int indexCompagnie) {
	int indexTable = rand()%listeTables.size();
	int compagnieToRemove = -1;
	do {
		compagnieToRemove = listeTables[indexTable].findEnemy(listeCompagnies[indexCompagnie]);
		if (compagnieToRemove != -1)
			listeTables[indexTable].retirerCompagnie(listeCompagnies[compagnieToRemove]);
	} while (compagnieToRemove != -1);	
	listeTables[indexTable].ajouterCompagnie(listeCompagnies[indexCompagnie]);
}

int main(int argc, char* argv[]) {

    string fileName = argv[1];

	fstream file(fileName.c_str());
	
	if (file.is_open()) {
		int n;

		file >> n;
		cout << "nTable : " << n << endl;
		// Initialisation des tables
		listeTables.reserve(n);
		for (int i = 0; i < n; ++i) {
			listeTables.push_back(Table());
		}
		cout << "Table done" << endl;
		// Initialisation des compagnies
		file >> n;
		cout << "nCompagnie : " << n << endl;
		
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
		int nbIteration = 0;
		while(nbIteration < 2){
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
					if (bestPoints != -100) {
						listeTables[bestIndexTable].ajouterCompagnie(listeCompagnies[i]);
					} else {
						doChange(i);
					}
				}
			}
			nbIteration++;
			printResult(listeTables);
		}
	}
    return 0;
}
