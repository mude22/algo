#include <iostream>
#include <vector>
#include <fstream>
#include <ctime>
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
    listeTables.reserve(n);
    for (int i = 0; i < n; ++i) {
      listeTables.push_back(Table());
    }

    // Initialisation des compagnies
    file >> n;
    
    listeCompagnies.reserve(n);
    int nParticipants;
    for (int i = 0; i < n; ++i) {
      file >> nParticipants;
      listeCompagnies.push_back(Compagnie(nParticipants, i, n));
    }

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
      if (printing == "1") {
        printResult(listeTables);
      }
    }
  }

  // Stop timer
  std::clock_t endTime;
  endTime = std::clock();

  
  if (time == "1") {
    std::cout << "Time: " << ((endTime - startTime) / (double)(CLOCKS_PER_SEC / 1000)) << std::endl;
  }

    return 0;
}
