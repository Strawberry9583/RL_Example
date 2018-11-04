#include"random_walk.h"


int main() {
	random_walk rw("TD", 7, 1000);
	rw.alg()->set_batch(true);
	rw.alg()->set_alpha(0.001);
	rw.run(1);
	rw.record();
	vector<double> alpha = { 0.01,0.05,0.1 };
	for (int i = 0; i < alpha.size(); ++i) {
		
	}
	cin.get();
	//FILE * gp = _popen("gnuplot ../random_walk/draw.plt", "w");
	//if (gp == NULL) {
	//	cout << "Failure" << endl;
	//}
	//else {
	//	cout << "plot  '../data/TD_200000_unbatched.csv' using 1:2 '%lf,%lf' \n";
	//	fprintf(gp, "draw.plot \n");
	//	fprintf(gp, "set title 'state value' \n set xlabel 'state'\n set ylabel 'value'\n");
	//	fprintf(gp, "gnuplot draw.plot");
	//	fprintf(gp, "plot  '../data/TD_200000_unbatched.csv' \n");
	//	fprintf(gp, "plot sin(x) \n");
	//	fprintf(gp, "set datafile separator ','\n");
	//	fprintf(gp, "set terminal png \n");
	//	fprintf(gp, "set output \"temp.png\" \n");
	//	fprintf(gp, "set xlabel 'x' \n");
	//	fprintf(gp, "set ylabel 'y' \n");
	//	fprintf(gp, "plot 'TD_200000_unbatched' using 1:2 \"%lf,%lf\"");
	//	fprintf(gp, "pause mouse\n");
	//	_pclose(gp);
	//	system("pause");
	//}




}