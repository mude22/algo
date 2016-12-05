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
	
	// 0 = Sans opinon
	// 1 = Je ne peux pas être assis avec
	// 2 = J'aimerais être assis avec 
	// 3 = Je ne préfère pas être assis avec
	std::vector<int> _vecRelationships;
};

#endif
