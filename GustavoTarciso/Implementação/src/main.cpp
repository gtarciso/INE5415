#include "state.hpp"

#include <iostream>
#include <string>

int main() {
	int _nsymbols, _nstates, _epsilon;
	//linked list <States>
	scanf("%d %d %d", &_nsymbols, &_nstates, &_epsilon);
	int i;
	if(_epsilon > 0) {
		for(i = 0; i < _nstates; i++) {
			new State(_nsymbols, true);	
		} 
	} else {
		for(i = 0; i < _nstates; i++) {
			new State(_nsymbols, false);
		}
	}
	return 0;
}