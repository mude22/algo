#ifndef TABLE_H
#define TABLE_H

#include <list>
#include <iostream>

#include "compagnie.h"

class Table {
	public:
		Table();
		void addCompany(Compagnie &c);
		void removeCompany(Compagnie &c);
		int addPossible(Compagnie &c);
		int findEnemy(Compagnie &c);
		int getNbPerson();
		int getPoids();
		void clearTable();
		friend std::ostream& operator<<(std::ostream &os, const Table &table);
    private:
		int _nPerson;
		int _poids;
		std::list<int> _listCompanies;
};

#endif
