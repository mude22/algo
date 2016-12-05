#include "compagnie.h"

Compagnie::Compagnie(int nParticipants, int index, int n) :
	_nParticipants(nParticipants), _index(index), _assis(false), _vecRelations(n, 0)
{
}

int Compagnie::getIndex() const{
	return _index;
}

int Compagnie::getnParticipants() const{
	return _nParticipants;
}

bool Compagnie::isAssis() const{
	return _assis;
}

void Compagnie::ajouterRelation(int indexCompagnie, int type) {
	_vecRelations[indexCompagnie] = type;
}

int Compagnie::getRelation(int indexCompagnie) {
	return _vecRelations[indexCompagnie];
}

void Compagnie::toggleAssis() {
	_assis = !_assis;
}

void Compagnie::resetAssis() {
	_assis = false;
}
