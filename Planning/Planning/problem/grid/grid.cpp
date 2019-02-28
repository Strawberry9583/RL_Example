#include"grid.h"


grid::grid(int width,int height) :problem_base<GRID_STATE_TYPE, GRID_ACTION_TYPE>(),m_width(width),\
	m_height(height){
	//ini action set;
	m_actions.push_back(GRID_ACTION_TYPE::GRID_ACTION_UP);
	m_actions.push_back(GRID_ACTION_TYPE::GRID_ACTION_DOWN);
	m_actions.push_back(GRID_ACTION_TYPE::GRID_ACTION_LEFT);
	m_actions.push_back(GRID_ACTION_TYPE::GRID_ACTION_RIGHT);

	//ini state set & states2actions & states2rewads;
	for (int i = 0; i < m_height; ++i) {
		for (int j = 0; j < m_width; ++j) {
			//ini state set;
			m_states.emplace_back(j,i);
			////ini rewards of the states;
			//if (GRID_STATE_TYPE(i, j) == m_goal) {
			//	m_state2reward[GRID_STATE_TYPE(i, j)] = 1.0;
			//}
			//else {
			//	m_state2reward[GRID_STATE_TYPE(i, j)] = .0;
			//}
			////ini the action of the states;
			//if (m_obstacle.find(GRID_STATE_TYPE(i,j)) == m_obstacle.end()) {
			//	m_states2actions[GRID_STATE_TYPE(i, j)] = m_actions;
			//}
		}
	}
}

grid::~grid() {
}

void grid::initialize() {
	//the grid size;
	m_width = 9;
	m_height = 6;
	//the start&end point of the grid;
	//m_start = { 2,0 };
	//m_goal = { 0,8 };
	//the obstacle of the grid;
	//m_obstacle = { {1, 2},{2, 2},{3, 2},{0, 7},{1, 7},{2, 7},{4, 5} };
}

pair<GRID_STATE_TYPE,double> grid::next_state(const GRID_STATE_TYPE& state, const GRID_ACTION_TYPE  & action) {
	GRID_STATE_TYPE next_state;
	if (action == GRID_ACTION_TYPE::GRID_ACTION_UP) {
		 next_state=pair<int, int>(state.first, state.second-1 );
	}
	else if (action == GRID_ACTION_TYPE::GRID_ACTION_DOWN) {
		next_state= pair<int, int>(state.first, state.second+1 );
	}
	else if (action == GRID_ACTION_TYPE::GRID_ACTION_LEFT) {
		next_state= pair<int, int>(state.first-1, state.second );
	}
	else if (action == GRID_ACTION_TYPE::GRID_ACTION_RIGHT) {
		next_state= pair<int, int>(state.first+1, state.second );
	}
	//if encountered with obstacle, then stay.
	//if (find(m_obstacle.begin(), m_obstacle.end(), next_state) != m_obstacle.end()) {
	//	next_state = state;
	//}
	//double reward = 0.0;
	//return make_pair(next_state,m_state2reward.at(next_state));
	return make_pair(next_state, 0.);
}

//void grid::reset_obstacle(const set<pair<int, int>>& obstacle) {
//	m_obstacle = obstacle;
//}

//void grid::print_grid() {
//	for (int i = 0; i < m_height; ++i) {
//		for (int j = 0; j < m_width; ++j) {
//			if (find(m_obstacle.begin(), m_obstacle.end(), GRID_STATE_TYPE(i, j)) != m_obstacle.end()) {
//				cout << "#";
//			}
//			else if (GRID_STATE_TYPE(i, j) == m_start) {
//				cout << "S";
//			}
//			else if (GRID_STATE_TYPE(i, j) == m_goal) {
//				cout << "G";
//			}
//			else {
//				cout << "O";
//			}
//		}
//		cout << endl;
//	}
//}

//void grid::print_optimal_policy() {
//
//}
