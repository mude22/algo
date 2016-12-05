#ifndef TABLE_H
#define TABLE_H

#include <list>
#include <iostream>

#include "compagnie.h"

class Table {
	public:
		Table();
		void ajouterCompagnie(Compagnie &c);
		void retirerCompagnie(Compagnie &c);
		int ajoutPossible(Compagnie &c);
		int findEnemy(Compagnie &c);
		int getNbPersonnes();
		int getPoids();
		void clearTable();
		friend std::ostream& operator<<(std::ostream &os, const Table &table);
    private:
		int _nPersonnes;
		int _poids;
		std::list<int> _listeCompagnies;
};

#endif
