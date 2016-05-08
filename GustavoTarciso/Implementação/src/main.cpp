#include "state.hpp"

#include <iostream>
#include <string>
#include <list>

list<State*> *FNAtoFDA(list<State*> *_states);

void printAutomata(list<State*> *_states);

int main() {
	int _nsymbols, _nstates, _epsilon;
	list<State*> *states = new list<State*>;
	scanf("%d %d %d", &_nsymbols, &_nstates, &_epsilon);
	int i;
	if(_epsilon > 0) {
		for(i = 0; i < _nstates; i++) {
			states->push_back(new State(_nsymbols, true));
		} 
		_nsymbols += 1;
	} else {
		for(i = 0; i < _nstates; i++) {
			states->push_back(new State(_nsymbols, false));
		}
	}
	printAutomata(states);
	return 0;
}

list<State*> *FNAtoFDA(list<State*> *_states) {
	return _states;
}

void printAutomata(list<State*> *_states) {
	std::list<State*>::iterator it = _states->begin();
	for(; it != _states->end(); ++it) {
		(*it)->printItself();
	}
}