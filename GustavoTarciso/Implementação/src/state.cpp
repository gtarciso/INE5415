#include "state.hpp"
#include <iostream>
#include <string>

State::State() {
	this->nsymbol = 0;
	this->init = false;
	this->final = false;
}

State::State(int _nsymbol) {
	this->nsymbol = _nsymbol;
	this->init = false;
	this->final = false;
	this->transitions = new string*[_nsymbol];
	this->readFile();
}

State::State(string *_head, string **_transitions, int _nsymbol, bool _final){
	this->nsymbol = _nsymbol;
	this->init = false;
	this->final = _final;
	this->head = _head;
	this->transitions = _transitions;
}

string *State::getHead() {
	return this->head;
}

string **State::getTransitions() {
	return this->transitions;
}

bool State::getFinal() {
	return this->final;
}

void State::readFile() {
	char aux; // auxiliar to read from file
	int i, j;
	scanf("%c", &aux);
	if(aux == '-') {
		scanf("%c", &aux);
		if (aux == '>') {
			this->init = true;
			scanf("%c", &aux);
		}
	} 
	if(aux == '*') {
		this->final = true;
		scanf("%c", &aux);
	} 
	char _head[10];
	i = 0;
	if(aux == '\n')
		scanf("%c", &aux);
	while(aux != ' ') {
		_head[i] = aux;
		scanf("%c", &aux);
		i++;
	}
	this->head = new string(_head);
	char *transition;
	for (i = 0; i < this->nsymbol; i++) {
		transition = new  char[100];
		j = 0;
		aux = 'c'; // necessary to dont' ignore other states after find the first '}'
		while(aux != '}') {
			scanf("%c", &aux);
			if(aux == '\n')
				break;
			transition[j] = aux;
			j++;
			if( j == 1 && transition[j-1] == ' ') {
				j--;
			}
			if (aux == '-') // maintence the loop when don't transits to a state
				aux = '}';
			this->transitions[i] = new string(transition);
		}
	}
	// this scanf exists to get the \n in end of line, because I'm getting char, instead of other type that ignore \n
	if(aux != '\n')
		scanf("%c", &aux);
}

// this method fix any problem reading file
void State::newLine() {
	while(getc(stdin) != '\n')
		continue;
}

void State::printItself() {
	int i;
	if(this->final)
		cout << "*";
	if(this->init)
		cout << "->";
	cout << *(this->head);
	for(i = 0; i < this->nsymbol; i++)  
		cout <<  " " + *(this->transitions[i]);
	cout << endl;
}
