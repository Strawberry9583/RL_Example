#ifndef GLOBAL_H
#define GLOBAL_H


#include<cmath>

#include"judger.h"

class global {
private:
	map<int,state> m_all_states;
	int m_row_num = 3;
	int m_column_num = 3;
	void dfs_state(state & current_sta,int symbol);
	
public:

	void get_all_state();
	void train(int epochs);
	void game();
};

#endif // !GLOBAL_H
