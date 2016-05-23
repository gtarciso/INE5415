#include "automata.hpp"
#include "state.hpp"

#include <iostream>
#include <string>
#include <list>
#include <cmath>

using namespace std;

Automata::Automata() {
	this->epsilon = false;
}

Automata::Automata(bool _epsilon, int _nsymbol, int _nstates) {
	this->epsilon = _epsilon; // tell us if the automata is a epsilon closure automata
	if(this->epsilon) { // guarantee file's reading, cuz we need to read an extra "symbol" epsilon in file
		_nsymbol += 1;
	}
	this->nsymbol = _nsymbol; // number of symbols
	this->nstates = _nstates; // number of states
	this->nstatesFNA = _nstates; // number of states in original FNA, IT DOESN'T change
	this->states = new list<State*>; // list of states in automata
	this->statesEpsilon = new list<State*>; // list of states by epsilon
	this->finalStates = new string*[nstatesFNA];
	this->nFinal = 0; // a auxiliar flag to determine if the states created in conversion to DFA are final states
	this->generateFNA(); // converts the FNA inserted by file, in a DFA
	this->getFinal();	
	if(this->epsilon) {
		this->epsilonClos = epsilonClosure(); // get epsilon closure
		this->nsymbol -= 1; // guarantee that the automata have the right amount of states before we cut off epsilon transitions
	}
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

void Automata::generateDFA() {
	// Auxiliar variables
	int max = pow(2, this->nstatesFNA); // max value that the automata can assume is 2^n
	string *_head; 
	string *_heads[this->nstates];
	string **_auxHeads = new string*[max];
	int i, j;

	i = 0;
	// get auxiliar states head to compare and, if necessary, create new states 
	for(State *state : *(this->states)) {
		_heads[i] = state->getHead();
		_auxHeads[i] = state->getHead();
		i++;
	}

	// auxiliar integers to verify if a new state will be created
	int cont;

	// auxiliar string vectors to store transitions of states
	string **_tr, **_newtr;

	// here is where the magic happens :D
	for(State *state : *(this->states)) {
		_tr = state->getTransitions(); // get every state transitions to made a brand new state, if necessary
		for(i = 0; i < this->nsymbol; i++) {
			//this->flagFinal = false; // maintence the flag who tells to created state if it is a final state or not 
			cont = 0; // auxiliar variable to assegure that the created state is really a new state
			if (*_tr[i] == "-") { // guarantee that the algorithm doesn't create a state "-"
				cont = 1;
			}
			// this loop is just in case the transition assumes {b} and assegure that the algorithm doesn't recognize it as a new state
			for (j = 0; j < this->nstates; j++) {
				if(_tr[i]->size() == 3) {
					_tr[i]->erase(0, 1);
					_tr[i]->pop_back();
				}
				if(!(*_tr[i]).compare((*_auxHeads[j]))) { // if the new transitions doesn't exist in list of states, cont still zero
					cont++;	
				}
			}
			// here is where the state is properly created, when cont = 0
			if(cont == 0) {
				_head = _tr[i];
				_auxHeads[this->nstates] = _head;
				this->incrementNStates(this->nstates);
				_newtr = getNTrasitions(_heads, _head);
				// guarantee that only truly new states are added to the list
				this->states->push_back(new State(_head, _newtr, this->nsymbol, false, false));
				// if the actual state is the last one of the list, and don't exists another state to be created, end the loop
				if(cont > 0 && state->getHead() == this->states->back()->getHead())
					break;
			}
		}
	}
	setFinal();
}

// just a method to don't get lost with the value of number of states ;D
void Automata::incrementNStates(int _nstates) {
	this->nstates = _nstates + 1;
}

// this method get the transitions of the new state 
string **Automata::getNTrasitions(string **_heads, string *_head) {
	// more auxiliar variable
	int i, j, k;
	string **_transitions = new string*[this->nsymbol];
	string **_fnaStates = new string*[this->nstatesFNA];
	string **_tr, **_states;
	// a vector to store the heads of the original FNA
	_states = new string*[this->nstatesFNA];
	j = 0;
	// fill the vector with the heads!
	if(!this->epsilon) {
		for(i = 0; i < this->nstatesFNA; i++) {
			if(_head->find(*_heads[i]) != string::npos) {
				_states[j] = new string(*_heads[i]);
				j++;
			}
		}
	} else {
		i = 0;
		for(State *state : *(this->states)) {
			_fnaStates[i] = state->getHead();
			i++;
		}
		string *_newStatesAux = new string();
		for(i = 0; i < this->nstatesFNA; i++) {
			if(_head->find(*_fnaStates[i]) != string::npos) {
				*_newStatesAux += *(this->epsilonClos[i]);
			}
		}
		for(i = 0; i < this->nstatesFNA; i++) {
			if(_newStatesAux->find(*_fnaStates[i]) != string::npos) {
				_states[j] = new string(*_fnaStates[i]);
				j++;
			}
		}
	}
	// in this loop we get all the transitions that contais the FNA iterators heads, and join all in a string
	for(i = 0; i < this->nsymbol; i++) {
		string *_aux = new string();
		for(k = 0; k < j; k++) {
			for(State* state : *(this->states)) {
				if(*(state->getHead()) == *_states[k]) {
					_tr = state->getTransitions();
					*_aux += *_tr[i];
				}
			}
		}
		// here we cut all the trash in the string generated in the loop above
		if(!this->epsilon)
			_transitions[i] = getFormatedTransition(_aux, _heads);
		else
			_transitions[i] = getFormatedTransition(_aux, _fnaStates);
	}
	return _transitions;
}

// just a method to format the transition, removing some trash in the original string, and making a new transition
string *Automata::getFormatedTransition(string *_aux, string **_states) {
	int i;
	// auxiliar int, if this variable assumes zero at the end of the for below, then return "-"
	// because the transition by the symbol doesn't exists
	int cont = 0;
	// loop verifying if all the transitions found corresponds to "-"
	for(i = 0; i < this->nstatesFNA; i++) {
		if(_aux->find(*_states[i]) != string::npos) {
			cont++;
		}
	}
	// returning "-" as commented above
	if (cont == 0)
		return new string("-"); 
	string *_newtr = new string();
	*_newtr += "{";
	// here we get only the name of states find in the string with the transition, without repeat them
	for(i = 0; i < this->nstatesFNA; i++) {
		if(_aux->find(*_states[i]) != string::npos ) {
				*_newtr += *_states[i];
				*_newtr += ", ";
		}
	}
	// just to remove extra ", "
	// I though that was easier to adjust, instead of create a couple of if (/* condition */)
	_newtr->pop_back();
	_newtr->pop_back();

	*_newtr += "}";
	return _newtr;
}

/* ================================================================================================
 *                                    EPSILON CLOSURE METHODS
 * ================================================================================================
 */ 

 string **Automata::epsilonClosure() {
 	string **_closure = new string*[this->nstatesFNA];
 	string *_heads = new string[this->nstatesFNA];
 	string aux;
 	int i;
 	i = 0;
 	for(State *state : *(this->states)) {
 		string _auxState = *(state->getHead());
 		_heads[i] = _auxState;
 		_closure[i] = (state->getHead());
 		i++;
 	}
 	// maybe need to cut edges in string
 	for(i = 0; i < this->nstatesFNA; i++) {
 		_closure[i] = getClosure(_closure[i]);
 		_closure[i] = removeEquals(_closure[i], _heads);
 		
 		// remove later, just to check the epsilon closure
 	}
 	i = 0;
 	for(State *state : *(this->states)) {
 		state->setHead(new string(_heads[i]));
 		i++;
 	}
 	return _closure;
 }

 string *Automata::removeEquals(string *_aux, string *_heads) {
 	int i;
 	string *_auxString;
 	_auxString = new string();
 	*_auxString += "{";
 	for(i = 0; i < this->nstatesFNA; i++) {
 		if(_aux->find(_heads[i]) != string::npos) {
 			*_auxString += _heads[i];
 			*_auxString += ", ";
 		}
 	}
 	_auxString->pop_back();
 	_auxString->pop_back();
 	*_auxString += "}";
 	return _auxString;
 }

 string *Automata::getClosure(string *_aux) {
 	string **_tr;
 	int max_symbols = this->nsymbol-1;
 	int i;
 	for(i = 0; i < this->nstates; i++) {
 		for(State *state : *(this->states)) {
 			if(_aux->find(*(state->getHead())) != string::npos) {
 				_tr = state->getTransitions();
 				if(*_tr[max_symbols] == "-") {
 					return _aux;
 				}
 				if(_aux->find(*(state->getHead())) != _aux->rfind(*(state->getHead()))) {
 					return _aux;
 				}
 				*_aux += " ";
 				*_aux += *_tr[max_symbols];
 				string::iterator it;
 				for(it = _aux->begin(); it != _aux->end(); it++) {
 					if(*it == '{' || *it == '}' || *it == ',') {
 						it = _aux->erase(it);
 						if(it == _aux->end())
 							break;
 					}
 				}
 			}
 		}
 	}
 	return getClosure(_aux);
 }

void Automata::generateDFAEpsilon() {
	// push com nsymbol e flagfinal :D
	int i, cont, j;
	int countingHeads = 0;
	int max = pow(2, this->nstatesFNA); // max value that the automata can assume is 2^n
	string **_auxHeads = new string*[max];
	list<State*> *_DFAepsilon = new list<State*>;
	string *_head;
	string **_transitions, **_tr;

	_head = this->epsilonClos[0];
	_auxHeads[countingHeads] = _head;
	countingHeads++;
	string *_xhead = new string();
	_xhead = getEpsionTransition(_head);
	string **_newtr = getNTrasitions(_auxHeads, _xhead);
	// guarantee that only truly new states are added to the list
	_DFAepsilon->push_back(new State(_head, _newtr, this->nsymbol, false, true));

	for(State *state : *_DFAepsilon) {
		_tr = state->getTransitions();
		for(i = 0; i < this->nsymbol; i++) {
			//this->flagFinal = false;
			cont = 0;
			if (*_tr[i] == "-") { // guarantee that the algorithm doesn't create a state "-"
				cont = 1;
			}
			for (j = 0; j < countingHeads; j++) {
				if(!(*_tr[i]).compare((*_auxHeads[j]))) { // if the new transitions doesn't exist in list of states, cont still zero
					cont++;	
				}
			}
			if(cont == 0) {
				_head = _tr[i];
				_auxHeads[countingHeads] = _head;
				countingHeads++;
				_newtr = getNTrasitions(_auxHeads, _head);
				_DFAepsilon->push_back(new State(_head, _newtr, this->nsymbol, false, false));
				if(cont > 0 && state->getHead() == this->states->back()->getHead())
					break;
			}
		}
	}
	this->nstates = countingHeads;
	this->states = new list<State*>;
	this->states = _DFAepsilon;
	this->setFinal();
}

string *Automata::getEpsionTransition(string *_aux) {
	int i;
	string *_newHead = new string();
	string **_states = new string*[this->nstatesFNA];
	for(State *state : *(this->states)) {
		_states[i] = state->getHead();
		i++; 
	}
	for(i = 0; i < this->nstatesFNA; i++) {
		if(_aux->find(*(_states[i])) != string::npos) {
			string aux = *(this->epsilonClos[i]);
			*_newHead += aux;
		}
	}
	return _newHead;
}

void Automata::getFinal() {
	int i = 0;
	for(State *state : *(this->states)) {
		if(state->getFinal()) {
			string aux = *state->getHead();
			this->finalStates[i] = new string(aux);
			i++;
		}
	}
	this->nFinal = i;
}

void Automata::setFinal() {
	int i;
	for(State *state : *(this->states)) {
		state->setFinal(false);
	}
	for(State *state : *(this->states)) {
		for(i = 0; i < this->nFinal; i++) {
			string aux = *this->finalStates[i];
			if((state->getHead())->find(aux) != string::npos) {
				state->setFinal(true);
			}
		}
	}
}