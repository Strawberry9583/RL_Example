#ifndef maze_h
#define maze_h

#include"problem_base.h"
#include"../definition/definition.h"
#include<vector>
#include<string>
#include<map>
#include<algorithm>
#include<iostream>

using namespace std;

class maze :public problem_base<MAZE_STATE_TYPE,MAZE_ACTION_TYPE> {
public:
	maze();
	~maze();
	const MAZE_STATE_TYPE & goal() { return m_goal; }
	const MAZE_STATE_TYPE & start() { return m_start; }
	pair<MAZE_STATE_TYPE,double>  next_state(const MAZE_STATE_TYPE  & state, const MAZE_ACTION_TYPE & action);
	void reset_obstacle(const vector<pair<int, int>> & obstacle);
	void print_maze();

private:
	//the maze size;
	int m_width = 9;
	int m_height = 6;
	//the start&end point of the maze;
	MAZE_STATE_TYPE m_start = { 2,0 };
	MAZE_STATE_TYPE m_goal = { 0,8 };
	//the obstacle of the maze;
	vector<MAZE_STATE_TYPE> m_obstacle = { {1, 2},{2, 2},{3, 2},{0, 7},{1, 7},{2, 7},{4, 5} };
	
};



#endif // !maze_h


