#include "automata.hpp"
#include "state.hpp"

#include <iostream>
#include <string>
#include <list>

using namespace std;

Automata::Automata() {
	this->epsilon = false;
}

Automata::Automata(bool _epsilon, int _nsymbol, int _nstates) {
	this->epsilon = _epsilon;
	if(this->epsilon)
		_nsymbol += 1;
	this->nsymbol = _nsymbol;
	this->nstates = _nstates;
	this->nstatesFNA = _nstates;
	this->states = new list<State*>;
	this->generateFNA();
}


// generate a FNA from file
void Automata::generateFNA() {
	int i;
	for(i = 0; i < this->nstates; i++) {
		states->push_back(new State(this->nsymbol));
	}
}

// this method fix any problem reading file
void Automata::newLine() {
	while(getc(stdin) != '\n')
		continue;
}

void Automata::printAutomata() {
	for(State* state : *(this->states)) {
		state->printItself();
	}
}

void Automata::generateFDA() {
	string *_head;
	string *_heads[this->nstates];
	string **_auxHeads = new string*[100]; // change
	int i, j;
	i = 0;
	for(State *state : *(this->states)) {
		_heads[i] = state->getHead();
		_auxHeads[i] = state->getHead();
		i++;
	}
	int cont;
	string **_tr, **_newtr;
	for(State *state : *(this->states)) {
		_tr = state->getTransitions();
		state->printItself();
		for(i = 0; i < this->nsymbol; i++) {
			cont = 0;
			if (*_tr[i] == "-") { // guarantee that the algorithm doesn't create a state "-"
				cont = 1;
			}
			for (j = 0; j < this->nstates; j++) {
				if(_tr[i]->size() == 3) {
					_tr[i]->erase(0, 1);
					_tr[i]->pop_back();
				}
				//cout << *_auxHeads[j] << endl;
				//cout << *_tr[i] << endl;
				if(!(*_tr[i]).compare((*_auxHeads[j]))) { // if the new transitions doesn't exist in list of states, create new state
					cont++;	
				}
			}
			if(cont == 0) {
				_head = _tr[i];
				//cout << *_head << endl;
				_auxHeads[this->nstates] = _head;
				this->incrementNStates(this->nstates);
				_newtr = getNTrasitions(_heads, _head);
			}
		}
		this->states->push_back(new State(_head, _newtr, this->nsymbol));
	}
}

void Automata::incrementNStates(int _nstates) {
	this->nstates = _nstates + 1;
}

string **Automata::getNTrasitions(string **_heads, string* _head) {
	int i, j, k;
	cout << *_head << endl;
	for(i = 0; i < this->nstatesFNA; i++) {
		//cout << *_heads[i] << endl;
	}
	string **_transitions = new string*[this->nsymbol];
	string **_tr, **_states;
	_states = new string*[this->nstatesFNA];
	j = 0;
	//int _hsize = (*_heads)->size();
	for(i = 0; i < this->nstatesFNA; i++) {
		if(_head->find(*_heads[i]) != string::npos) {
			_states[j] = new string(*_heads[i]);
			cout << *_states[j] << endl;
			j++;
		}
	}

	for(i = 0; i < this->nsymbol; i++) {
		string *_aux = new string();
		for(k = 0; k < j; k++) {
			for(State* state : *(this->states)) {
				if(*(state->getHead()) == *_states[k]) {
					_tr = state->getTransitions();
					//cout << *_tr[i] << endl;
					*_aux += *_tr[i];
					//cout << *_tr[i] << endl;
					//cout << "chegou aqui" << endl;
				}
			}
		} // não passar daqui com a transição
		//cout << *_aux << endl;
		_transitions[i] = getFormatedTransition(_aux, _heads);
		//cout << *_transitions[i] << endl;
	}
	cout << endl;
	return _transitions;
}

string *Automata::getFormatedTransition(string *_aux, string **_states) {
	int i;
	cout << *_aux << endl;
	string *_newtr = new string();
	*_newtr += "{";
	for(i = 0; i < this->nstatesFNA; i++) {
		if(_aux->find(*_states[i]) != string::npos) {
			//cout << *_states[i] << endl;
			*_newtr += *_states[i];
			*_newtr += ", ";
		}
	}
	_newtr->pop_back();
	_newtr->pop_back();
	*_newtr += "}";
	cout << *_newtr << endl;
	return _newtr;
}