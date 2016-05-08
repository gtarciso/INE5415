#ifndef _STATE_
#define _STATE_

#include <iostream>
#include <string>

using namespace std;

class State {
private:
	string *head; // state head
	string **transitions;
	bool init;
	bool final;
	bool epsilon;
	int symbol; // number of transitions in each state

public:
	State();
	State(int _symbol, bool _epsilon);

	/*
	 * getters and setters
	 */

	string *getHead();
	string **getTransitions();

	void readFile();
	void newLine();
	void printItself();
};

#endif