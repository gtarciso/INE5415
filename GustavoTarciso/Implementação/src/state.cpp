#include "state.hpp"
#include <iostream>
#include <string>

State::State() {
	this->symbol = 0;
}

State::State(int _symbol, bool _epsilon) {
	if (_epsilon)
		_symbol += 1;
	this->symbol = _symbol;
	this->epsilon = _epsilon;
	this->transitions = new string*[_symbol];
	this->readFile();
}

/*
 * Getters and setters
 */

string *State::getHead() {
	return this->head;
}

string **State::getTransitions() {
	return this->transitions;
}

/*
 * read input file and generate FNA
 */

void State::readFile() {
	char _aux;
	char _saux[1];
	int i, j;
	scanf("%c", &_aux);
	_saux[0] = _aux;
	this->head = new string(_saux);
	for(i = 0; i < this->symbol; i++) {
		char _transition[100]; // 
		j = 0;
		while(_aux != '}') {
			scanf("%c", &_aux);
			_transition[j] = _aux;
			j++;
			if(_aux == '-') // maintence the loop when don't have transitions by a symbol
				_aux = '}';
		}
		this->transitions[i] = new string(_transition);
	}
	State::newLine();
}

/*
 * fix any problem with scanf
 */

void State::newLine() {
	while(getc(stdin) != '\n')
		continue;
}

void State::printItself() {
	int i;
	cout << *(this->head);
	for (i = 0; i < this->symbol; i++) {
		cout << *(this->transitions[i]);
	}
	cout << endl;
}

