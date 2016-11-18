#ifndef COMPAGNIE_H
#define COMPAGNIE_H

class Compagnie {
public:
	Compagnie(int nParticipant, int index);
	
	int getIndex() const;
	int getnParticipants() const;
private:
	int _nParticipants;
	int _index;
};

#endif
