#ifndef GRID_H
#define GRID_H

#include"../problem_base.h"
#include"../../definition/definition.h"
#include<vector>
#include<string>
#include<map>
#include<algorithm>
#include<iostream>
#include<set>

using namespace std;

class grid :public problem_base<GRID_STATE_TYPE,GRID_ACTION_TYPE> {
public:
	grid(int width=12,int height=4);
	virtual ~grid();
	void initialize()override;
	pair<GRID_STATE_TYPE,double>  next_state(const GRID_STATE_TYPE  & state, const GRID_ACTION_TYPE & action)override;

	//void reset_obstacle(const set<pair<int, int>> & obstacle);
	//void print_grid();
	//void print_optimal_policy();
private:

protected:
	//the grid size;
	int m_width ;
	int m_height ;

	//the obstacle of the grid;
	//set<GRID_STATE_TYPE> m_obstacle;
	
};



#endif // 


