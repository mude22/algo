#include "table.h"

using namespace std;

Table::Table() :
	_nPersonnes(0), _poids(0), _listeCompagnies()
{	
}

void Table::ajouterCompagnie(Compagnie &c) {
	for (list<int>::iterator it=_listeCompagnies.begin(); it!=_listeCompagnies.end(); ++it) {
		if(c.getRelation(*it) == 2)
			_poids--;
		else if(c.getRelation(*it) == 3)
			_poids++;
	}
	_listeCompagnies.push_back(c.getIndex());
	_nPersonnes = _nPersonnes + c.getnParticipants();
	c.toggleAssis();
}

void Table::retirerCompagnie(Compagnie &c) {
	for (list<int>::iterator it=_listeCompagnies.begin(); it!=_listeCompagnies.end(); ++it) {
		if(c.getRelation(*it) == 2)
			_poids++;
		else if(c.getRelation(*it) == 3)
			_poids--;
	}
	_listeCompagnies.remove(c.getIndex());
	_nPersonnes = _nPersonnes - c.getnParticipants();
	c.toggleAssis();
}

bool Table::estPresent(const Compagnie &c) {
	for (list<int>::iterator it=_listeCompagnies.begin(); it!=_listeCompagnies.end(); ++it)
		if(*it == c.getIndex())
			return true;
	return false;
}

int Table::ajoutPossible(Compagnie &c) {
	int points = 0;
	for (list<int>::iterator it=_listeCompagnies.begin(); it!=_listeCompagnies.end(); ++it)
		switch(c.getRelation(*it)) {
			case 1:
				return -100;
				break;
			case 2:
				points++;
				break;
			case 3:
				points--;
				break;
		}
	return points;
}

int Table::findEnemy(Compagnie &c) {
	for (list<int>::iterator it=_listeCompagnies.begin(); it!=_listeCompagnies.end(); ++it)
		if (c.getRelation(*it) == 1)
			return *it;
	return -1;
}

int Table::getNbPersonnes() {
	return _nPersonnes;
}

int Table::getPoids() {
	return _poids;
}

std::ostream& operator<<(std::ostream& os, const Table& table) {
	if (!table._listeCompagnies.empty()){
		for (list<int>::const_iterator it=table._listeCompagnies.begin(); it!=table._listeCompagnies.end(); ++it)
			os << *it << " ";
		os << "(nbParticipants : " << table._nPersonnes << " ) (poids : " << table._poids/2 << " )" << std::endl;
	}
}

