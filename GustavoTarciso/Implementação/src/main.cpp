
#include "state.hpp"
#include "automata.hpp"

using namespace std;

int main() {
	Automata *machine, *_aux;
	_aux = new Automata();
	int nstates, nsymbols, epsilon;
	scanf("%d %d %d", &nsymbols, &nstates, &epsilon);
	_aux->newLine();
	if(epsilon > 0) {
		machine = new Automata(true, nsymbols, nstates);
	} else {
		machine = new Automata(false, nsymbols, nstates);
	}
	machine->generateFDA();
	machine->printAutomata();
}