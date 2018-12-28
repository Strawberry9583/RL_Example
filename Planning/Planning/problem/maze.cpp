#include"maze.h"


maze::maze() {
	
}

maze::~maze() {
}

pair<int,int> maze::move(const pair<int,int>& state, MAZE_ACTION_TYPE action) {
	pair<int, int> next_state;
	if (action == MAZE_ACTION_TYPE::UP) {
		 next_state=pair<int, int>(state.first-1, state.second );
	}
	else if (action == MAZE_ACTION_TYPE::DOWN) {
		next_state= pair<int, int>(state.first+1, state.second );
	}
	else if (action == MAZE_ACTION_TYPE::LEFT) {
		next_state= pair<int, int>(state.first, state.second-1 );
	}
	else if (action == MAZE_ACTION_TYPE::RIGHT) {
		next_state= pair<int, int>(state.first, state.second+1 );
	}
	//if encountered with obstacle, then stay.
	if (find(m_obstacle.begin(), m_obstacle.end(), next_state) == m_obstacle.end()) {
		next_state = state;
	}
	return next_state;
}
