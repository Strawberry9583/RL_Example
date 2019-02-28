#include"random_walk.h"



random_walk::random_walk(int states_num): problem_base<RANDOM_WALK_STATE_TYPE, RANDOM_WALK_ACTION_TYPE>(),\
m_states_num(states_num) {
}



random_walk::~random_walk() {
}

void random_walk::initialize() {
	//set states;
	m_states.resize(m_states_num);
	iota(m_states.begin(), m_states.end(), 0);
	//set terminal/start states;
	m_left_end = 0;
	m_right_end = m_states_num - 1;
	m_start = m_states_num / 2;
	m_terminal.push_back(m_left_end);
	m_terminal.push_back(m_right_end);
	//set actions set;
	m_actions.push_back(RANDOM_WALK_ACTION_LEFT);
	m_actions.push_back(RANDOM_WALK_ACTION_RIGHT);
	//set actions for each state;
	for (auto & i : m_states) {
		if (i != m_left_end && i != m_right_end) {
			m_states2actions[i] = m_actions;
		}
	}
}

pair<RANDOM_WALK_STATE_TYPE, double> random_walk::next_state(const RANDOM_WALK_STATE_TYPE & state, const RANDOM_WALK_ACTION_TYPE & action) {
	RANDOM_WALK_STATE_TYPE cur_state;
	if (action == RANDOM_WALK_ACTION_TYPE::RANDOM_WALK_ACTION_LEFT) {
		cur_state = state - 1;
	}
	else {
		cur_state = state + 1;
	}
	if (cur_state == m_right_end) {
		return make_pair(cur_state, 1.);
	}
	else {
		return make_pair(cur_state, 0.);
	}
}
