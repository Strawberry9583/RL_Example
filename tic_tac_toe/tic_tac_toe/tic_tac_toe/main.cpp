#include"global.h"



int main() {

	global glo;
	glo.get_all_state();
	//glo.train(100000);
	glo.game();
	cin.get();
	return 0;
}