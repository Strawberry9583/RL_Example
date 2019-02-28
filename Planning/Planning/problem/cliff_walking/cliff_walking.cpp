#include"cliff_walking.h"

cliff_walking::cliff_walking():grid() {

}

cliff_walking::~cliff_walking() {
}

void cliff_walking::initialize() {
	m_width = 12;
	m_height = 4;
	//set start and goal state;
	m_start = GRID_STATE_TYPE(0,3);
	m_goal = GRID_STATE_TYPE(11, 3);
	//set cliff in the bottom of the grid map;
	for (int i = 1; i < 11; ++i) {
		m_cliff_set.insert(GRID_STATE_TYPE(i,3));
	}
	//set m_state2actions;
	for (int i = 0; i < m_width; ++i) {
		for (int j = 0; j < m_height; ++j) {
			//non-cliff state and non-goal state has full action set; 
			if (m_cliff_set.find(GRID_STATE_TYPE(i, j)) == m_cliff_set.end()) {
				m_states2actions[GRID_STATE_TYPE(i, j)] = m_actions;
			}
		}
	}
}

pair<GRID_STATE_TYPE, double> cliff_walking::next_state(const GRID_STATE_TYPE & state, const GRID_ACTION_TYPE & action) {
	//move as grid map in normal way;
	auto next = grid::next_state(state, action);
	//check next_state is cliff;
	if (m_cliff_set.find(next.first) != m_cliff_set.end()) {
		next.first = m_start;
		next.second = -100.;
	}
	//check the boundary;
	else {
		if (next.first.first < 0) {
			next.first.first = 0;
		}
		else if (next.first.first > 11) {
			next.first.first = 3;
		}
		else if (next.first.second < 0) {
			next.first.second = 0;
		}
		else if (next.first.second > 3) {
			next.first.second = 3;
		}
		next.second = -1.;
	}
	return next;
}


