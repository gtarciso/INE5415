#include "state.hpp"

#include <iostream>
#include <string>
#include <list>

list<State*> *FNAtoFDA(list<State*> *_states);

void printAutomata(list<State*> *_states, int _nsymbols);

int main() {
	int _nsymbols, _nstates, _epsilon;
	list<State*> *states = new list<State*>;
	scanf("%d %d %d", &_nsymbols, &_nstates, &_epsilon);
	int i;
	if(_epsilon > 0) {
		for(i = 0; i < _nstates; i++) {
			states->push_back(new State(_nsymbols, true));
		} 
	} else {
		for(i = 0; i < _nstates; i++) {
			states->push_back(new State(_nsymbols, false));
		}
	}
	printAutomata(states, _nsymbols);
	return 0;
}

list<State*> *FNAtoFDA(list<State*> *_states) {
	return _states;
}

void printAutomata(list<State*> *_states, int _nsymbols) {
	int j;
	std::list<State*>::iterator it = _states->begin();
	for(; it != _states->end(); ++it) {
		cout << (*it)->getHead();
		string **_tr;
		_tr = (*it)->getTransitions();
		for (j = 0; j < _nsymbols; j++) {
			cout << _tr[j]; 
		}
		cout << endl;
		delete _tr;
	}
}