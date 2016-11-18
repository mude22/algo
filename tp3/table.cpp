#include "table.h"

using namespace std;

Table::Table(int nPersonnes) :
	_nPersonnes(nPersonnes)
{	
}

void Table::ajouterCompagnie(const Compagnie &c) {
	_listeCompagnies.push_back(c.getIndex());
	_nPersonnes = _nPersonnes + c.getnParticipants();
}

void Table::retirerCompagnie(const Compagnie &c) {
	_listeCompagnies.remove(c.getIndex());
	_nPersonnes = _nPersonnes - c.getnParticipants();
}

bool Table::estPresent(const Compagnie &c) {
	for (list<int>::iterator it=_listeCompagnies.begin(); it!=_listeCompagnies.end(); ++it)
		if(*it == c.getIndex())
			return true;
	return false;
}



