#ifndef _AUTOMATA_
#define _AUTOMATA_

#include "state.hpp"

#include <iostream>
#include <string>
#include <list>

using namespace std;

class Automata {
private:
	list<State*> *states;
	bool epsilon;
	int nsymbol;
	int nstates;
	int nstatesFNA;

public:
	Automata();
	Automata(bool _epsilon, int _nsymbol, int _nstates);
	~Automata();

	void generateFNA();
	void printAutomata();
	void newLine();
	void generateFDA();
	void incrementNStates(int _nstates);
	string **getNTrasitions(string **_heads, string *_head);
	string *getFormatedTransition(string *_aux, string **_states);
};

#endif