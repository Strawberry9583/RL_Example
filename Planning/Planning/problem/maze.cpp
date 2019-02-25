#include"maze.h"


maze::maze() :problem_base<MAZE_STATE_TYPE, MAZE_ACTION_TYPE>(){
	//ini action set;
	m_actions.push_back(MAZE_ACTION_TYPE::UP);
	m_actions.push_back(MAZE_ACTION_TYPE::DOWN);
	m_actions.push_back(MAZE_ACTION_TYPE::LEFT);
	m_actions.push_back(MAZE_ACTION_TYPE::RIGHT);

	//ini state set & states2actions & states2rewads;
	for (int i = 0; i < m_height; ++i) {
		for (int j = 0; j < m_width; ++j) {
			//ini state set;
			m_states.emplace_back(i, j);
			//ini rewards of the states;
			if (MAZE_STATE_TYPE(i, j) == m_goal) {
				m_state2reward[MAZE_STATE_TYPE(i, j)] = 1.0;
			}
			else {
				m_state2reward[MAZE_STATE_TYPE(i, j)] = .0;
			}
			//ini the action of the states;
			if (find(m_obstacle.begin(), m_obstacle.end(), MAZE_STATE_TYPE(i, j)) == m_obstacle.end()) {
				m_states2actions[MAZE_STATE_TYPE(i, j)] = m_actions;
			}
		}
	}

}

maze::~maze() {
}

pair<MAZE_STATE_TYPE,double> maze::next_state(const MAZE_STATE_TYPE& state, const MAZE_ACTION_TYPE  & action) {
	MAZE_STATE_TYPE next_state;
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
	if (find(m_obstacle.begin(), m_obstacle.end(), next_state) != m_obstacle.end()) {
		next_state = state;
	}
	double reward = 0.0;
	return make_pair(next_state,m_state2reward.at(next_state));
}

void maze::reset_obstacle(const vector<pair<int, int>>& obstacle) {
	m_obstacle = obstacle;
}

void maze::print_maze() {
	for (int i = 0; i < m_height; ++i) {
		for (int j = 0; j < m_width; ++j) {
			if (find(m_obstacle.begin(), m_obstacle.end(), MAZE_STATE_TYPE(i, j)) != m_obstacle.end()) {
				cout << "#";
			}
			else if (MAZE_STATE_TYPE(i, j) == m_start) {
				cout << "S";
			}
			else if (MAZE_STATE_TYPE(i, j) == m_goal) {
				cout << "G";
			}
			else {
				cout << "O";
			}
		}
		cout << endl;
	}
}
