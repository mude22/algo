#ifndef COMPAGNIE_H
#define COMPAGNIE_H

#include <vector>

class Compagnie {
public:
	Compagnie(int nParticipant, int index, int n);
	
	int getIndex() const;
	int getnParticipants() const;
	bool isAssis() const;
	void toggleAssis();
	void ajouterRelation(int indexCompagnie, int type);
	int getRelation(int indexCompagnie);
private:
	int _nParticipants;
	int _index;
	bool _assis;
	
	// 0 = ok, 1 = non, 2 = j'aime, 3 = j'aime pas
	std::vector<int> _vecRelations;
};

#endif
