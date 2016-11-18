#include "compagnie.h"

Compagnie::Compagnie(int nParticipants, int index) :
	_nParticipants(nParticipants), _index(index)
{
}

int Compagnie::getIndex() const{
	return _index;
}

int Compagnie::getnParticipants() const{
	return _nParticipants;
}
