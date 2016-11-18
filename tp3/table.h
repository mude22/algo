#ifndef TABLE_H
#define TABLE_H

#include <list>

#include "compagnie.h"

class Table {
	public:
		Table(int nPersonnes);
		void ajouterCompagnie(const Compagnie &c);
		void retirerCompagnie(const Compagnie &c);
		bool estPresent(const Compagnie &c);
    private:
		int _nPersonnes;
		std::list<int> _listeCompagnies;
};

#endif
