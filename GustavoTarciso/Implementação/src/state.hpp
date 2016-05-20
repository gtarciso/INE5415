#ifndef _STATE_
#define _STATE_

#include <iostream>
#include <string>

using namespace std;

class State {
private:
	string *head;
	string **transitions;
	bool init;
	bool final;
	int nsymbol;

public:
	State();
	State(int _nsymbol);
	State(string *_head, string **_transitions, int _nsymbol, bool _final);
	~State();

/*
 * ============= GETTERS AND SETTERS ============
 */ 

 	string *getHead();
 	string **getTransitions();
 	bool getFinal();
 	void setHead(string *_head);

/*
 * ==============================================
 */

 	void readFile();
 	void newLine();
 	void printItself();

};

#endif