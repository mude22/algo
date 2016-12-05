#ifndef COMPAGNIE_H
#define COMPAGNIE_H

#include <vector>

class Compagnie {
public:
	Compagnie(int nParticipant, int index, int n);
	
	int getIndex() const;
	int getnParticipants() const;
	bool isSit() const;
	void toggleSit();
	void resetSit();
	void addRelationship(int indexCompany, int type);
	int getRelationship(int indexCompany);
private:
	int _nParticipants;
	int _index;
	bool _sit;
	
	// 0 = ok, 1 = non, 2 = j'aime, 3 = j'aime pas
	std::vector<int> _vecRelationships;
};

#endif
