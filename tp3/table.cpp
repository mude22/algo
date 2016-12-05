#include "table.h"

using namespace std;

Table::Table() :
	_nPerson(0), _poids(0), _listCompanies()
{	
}

void Table::addCompany(Compagnie &c) {
	for (list<int>::iterator it=_listCompanies.begin(); it!=_listCompanies.end(); ++it) {
		if(c.getRelationship(*it) == 2)
			_poids--;
		else if(c.getRelationship(*it) == 3)
			_poids++;
	}
	_listCompanies.push_back(c.getIndex());
	_nPerson = _nPerson + c.getnParticipants();
	c.toggleSit();
}

void Table::removeCompany(Compagnie &c) {
	for (list<int>::iterator it=_listCompanies.begin(); it!=_listCompanies.end(); ++it) {
		if(c.getRelationship(*it) == 2)
			_poids++;
		else if(c.getRelationship(*it) == 3)
			_poids--;
	}
	_listCompanies.remove(c.getIndex());
	_nPerson = _nPerson - c.getnParticipants();
	c.toggleSit();
}

int Table::addPossible(Compagnie &c) {
	int points = 0;
	for (list<int>::iterator it=_listCompanies.begin(); it!=_listCompanies.end(); ++it)
		switch(c.getRelationship(*it)) {
			case 1:
				return 100;
				break;
			case 2:
				points--;
				break;
			case 3:
				points++;
				break;
		}
	return points;
}

int Table::findEnemy(Compagnie &c) {
	for (list<int>::iterator it=_listCompanies.begin(); it!=_listCompanies.end(); ++it)
		if (c.getRelationship(*it) == 1)
			return *it;
	return -1;
}

int Table::getNbPerson() {
	return _nPerson;
}

int Table::getPoids() {
	return _poids;
}

void Table::clearTable() {
	_nPerson = 0;
	_poids = 0;
	_listCompanies.clear();
}
std::ostream& operator<<(std::ostream& os, const Table& table) {
	if (!table._listCompanies.empty()){
		for (list<int>::const_iterator it=table._listCompanies.begin(); it!=table._listCompanies.end(); ++it)
			os << *it << " ";
		os << std::endl;
	}
}

