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
	list<State*> *statesEpsilon;
	bool epsilon;
	bool flagFinal;
	int nsymbol;
	int nstates;
	int nstatesFNA;
	string **epsilonClos;

public:
	Automata();
	Automata(bool _epsilon, int _nsymbol, int _nstates);
	~Automata();

	void generateFNA();
	void printAutomata();
	void newLine();
	void generateDFA();
	void incrementNStates(int _nstates);
	string **getNTrasitions(string **_heads, string *_head);
	string *getFormatedTransition(string *_aux, string **_states);

	/*
	 * EPSILON CLOSURE METHODS
	 */

	string **epsilonClosure();
	string *getClosure(string *_aux);
	void generateDFAEpsilon();
	string *getEpsionTransition(string *_aux);
	string *removeEquals(string *_aux, string *_heads);
};

#endif