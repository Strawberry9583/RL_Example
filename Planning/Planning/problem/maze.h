#include"../definition.h"
#include<vector>
#include<string>
#include<map>
#include<algorithm>
using namespace std;

class maze {
public:
	maze();
	~maze();
	const pair<int, int> & goal() { return m_goal; }
	const pair<int, int> & start() { return m_start; }
	pair<int,int>  move(const pair<int,int> & state, MAZE_ACTION_TYPE action);
private:
	//the maze size;
	int m_width=9;
	int m_height=6;
	//the start&end point of the maze;
	pair<int,int> m_start = { 2,0 };
	pair<int,int> m_goal = { 0,8 };
	vector<MAZE_ACTION_TYPE> m_actions = 
		{MAZE_ACTION_TYPE::UP,MAZE_ACTION_TYPE::DOWN,MAZE_ACTION_TYPE::LEFT,MAZE_ACTION_TYPE::RIGHT};
	//the obstacle of the maze;
	vector<pair<int,int>> m_obstacle = { {1, 2},{2, 2},{3, 2},{0, 7},{1, 7},{2, 7},{4, 5} };

};

