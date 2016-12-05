#include "compagnie.h"

Compagnie::Compagnie(int nParticipants, int index, int n) :
	_nParticipants(nParticipants), _index(index), _sit(false), _vecRelationships(n, 0)
{
}

int Compagnie::getIndex() const{
	return _index;
}

int Compagnie::getnParticipants() const{
	return _nParticipants;
}

bool Compagnie::isSit() const{
	return _sit;
}

void Compagnie::addRelationship(int indexCompany, int type) {
	_vecRelationships[indexCompany] = type;
}

int Compagnie::getRelationship(int indexCompany) {
	return _vecRelationships[indexCompany];
}

void Compagnie::toggleSit() {
	_sit = !_sit;
}

void Compagnie::resetSit() {
	_sit = false;
}
