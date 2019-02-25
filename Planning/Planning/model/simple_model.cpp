#include"simple_model.h"


simple_model::simple_model() :model_base() {
	
}

simple_model::~simple_model() {

}

void simple_model::feed(const STATE_TYPE  & state,const MAZE_ACTION_TYPE & action,const STATE_TYPE & next_state, double reward) {
	// S_A pair hasn't occurred.
	if (find(m_int2sa.begin(), m_int2sa.end(), make_pair(state, action)) == m_int2sa.end()) {
		m_int2sa.push_back(make_pair(state, action));
	}
	//add the SASR sequence into model;
	m_model_data[make_pair(state, action)].push_back(make_pair(next_state, reward));
}

SASR_QUADRUPLE simple_model::sample() {
	uniform_int_distribution<int> rand(0, m_int2sa.size());
	int s_a_idx = rand(m_random_engine);
	uniform_int_distribution<int> rand1(0,m_model_data[m_int2sa[s_a_idx]].size());
	int s_r_idx = rand(m_random_engine);
	return make_tuple(m_int2sa[s_a_idx].first,m_int2sa[s_a_idx].second,
		m_model_data[m_int2sa[s_a_idx]][s_r_idx].first,
		m_model_data[m_int2sa[s_a_idx]][s_r_idx].second);
}
