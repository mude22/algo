#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <ctime>
#include <stdlib.h>
#include <cmath>
#include "table.h"
#include "compagnie.h"

using namespace std;

vector<Compagnie> listCompanies;
vector<Table> listTables;
float scoreToBeat = 0;
int nbSit = 0;

float calculEcartType() {
	int sum = 0;
	for(int i = 0; i < listTables.size(); i++) {
		sum += listTables[i].getNbPerson();
	}
	float average = sum/(float)listTables.size();

	float total = 0, gap, variance;

	for(int i = 0; i < listTables.size(); i++) {
		gap = listTables[i].getNbPerson() - average;
		total += gap*gap;
	}

	variance = total / (float)listTables.size();
	return (sqrt(variance));
}

int calculPoids() {
  int poids = 0;
  for(int i = 0; i < listTables.size(); i++) {
    poids += listTables[i].getPoids();
  }
  // divisé en deux parce qu'on le calcule deux fois
  return poids/2;
}

void printResult() {
	for (int i = 0; i < listTables.size(); i++) {
		cout << listTables[i];
	}
	cout << "fin" << endl;
}

void clearTables() {
	for (int i = 0; i < listTables.size(); i++) {
		listTables[i].clearTable();
	}	
}

void resetCompanies() {
	for (int i = 0; i < listCompanies.size(); i++) {
		listCompanies[i].resetSit();
	}
}

void doChange(int indexCompany) {
	int indexTable = rand()%listTables.size();
	int companyToRemove = -1;
	do {
		companyToRemove = listTables[indexTable].findEnemy(listCompanies[indexCompany]);
		if (companyToRemove != -1) {
			nbSit--;
			for (int i = 0; i < listCompanies.size(); i++) {
				if (listCompanies[i].getIndex() == companyToRemove) {
					listTables[indexTable].removeCompany(listCompanies[i]);
				}
			}
		}
	} while (companyToRemove != -1);
	nbSit++;	
	listTables[indexTable].addCompany(listCompanies[indexCompany]);
}

int main(int argc, char* argv[]) {
  
	std::string fileName = argv[1];
	std::string printing = argv[2];
	std::string time = argv[3];

	// Start timer
	std::clock_t startTime;
	startTime = std::clock();

	fstream file(fileName.c_str());

	if (file.is_open()) {
		int n;

		file >> n;
		// Initialisation des tables
		listTables.reserve(n);
		for (int i = 0; i < n; ++i) {
			listTables.push_back(Table());
		}

		// Initialisation des compagnies
		file >> n;
		
		listCompanies.reserve(n);
		int nParticipants;
		for (int i = 0; i < n; ++i) {
			file >> nParticipants;
			listCompanies.push_back(Compagnie(nParticipants, i, n));
		}

		// Initialisation relation 1 (ne pouvant pas être assis à la même table)
		file >> n;
		int companyA, companyB;
		for (int i = 0; i < n; ++i) {
			file >> companyA >> companyB;
			listCompanies[companyA].addRelationship(companyB, 1);
			listCompanies[companyB].addRelationship(companyA, 1);
		}

		// Initialisation relation 2 (souhaitant être assis à la même table)
		file >> n;
		for (int i = 0; i < n; ++i) {
			file >> companyA >> companyB;
			listCompanies[companyA].addRelationship(companyB, 2);
			listCompanies[companyB].addRelationship(companyA, 2);
		}

		// Initialisation relation 3 (souhaitant ne pas être assis à la même table)
		file >> n;
		for (int i = 0; i < n; ++i) {
			file >> companyA >> companyB;
			listCompanies[companyA].addRelationship(companyB, 3);
			listCompanies[companyB].addRelationship(companyA, 3);
		}

		// Algorithme
		std::clock_t nowTime;
		nowTime = std::clock();
		
		while(((nowTime - startTime) / (double)(CLOCKS_PER_SEC)) < 20){
			random_shuffle(listCompanies.begin(), listCompanies.end());
			do {
				for (int i = 0; i < listCompanies.size(); i++) {
					if (!listCompanies[i].isSit()) {
						int bestIndexTable = 0;
						int bestPoints = 100;
						for (int j = 0; j < listTables.size(); j++) {
							int points = listTables[j].addPossible(listCompanies[i]);
							if (points < bestPoints) {
								bestPoints = points;
								bestIndexTable = j;
							}
						}
						if (bestPoints != 100) {
							listTables[bestIndexTable].addCompany(listCompanies[i]);
							nbSit++;
						} else {
							doChange(i);
						}
					}
				}
			} while (nbSit < listCompanies.size());
			
			nbSit = 0;
			
			float scoreIteration = calculEcartType() + calculPoids();
			if (scoreToBeat == 0 || scoreToBeat > scoreIteration) {
				scoreToBeat = scoreIteration;
				if (printing == "1") {
					printResult();
				}
			}
			
			clearTables();
			resetCompanies();
			nowTime = std::clock();
		}
	}

	// Stop timer
	std::clock_t endTime;
	endTime = std::clock();

  
	if (time == "1") {
		std::cout << "Time: " << ((endTime - startTime) / (double)(CLOCKS_PER_SEC)) << std::endl;
	}

	return 0;
}
