#ifndef SIMPLE_MODEL_H
#define SIMPLE_MODEL_H

#include"model_base.h"

template<typename state_type,typename action_type>
class simple_model :public model_base<state_type, action_type> {
public:
	simple_model() :model_base<state_type, action_type>(){};
	~simple_model() {};

	void feed(const state_type & state, const action_type & action, const state_type & next_state, double reward) {
		// S_A pair hasn't occurred.
		if (find(m_int2sa.begin(), m_int2sa.end(), make_pair(state, action)) == m_int2sa.end()) {
			m_int2sa.push_back(make_pair(state, action));
		}
		//add the SASR sequence into model;
		m_model_data[make_pair(state, action)].push_back(make_pair(next_state, reward));
	};

	tuple<state_type, action_type, state_type, double> sample() {
		uniform_int_distribution<int> rand(0, m_int2sa.size()-1);
		int s_a_idx = rand(this->m_random_engine);
		uniform_int_distribution<int> rand1(0, m_model_data[m_int2sa[s_a_idx]].size()-1);
		int s_r_idx = rand1(this->m_random_engine);
		return make_tuple(m_int2sa[s_a_idx].first, m_int2sa[s_a_idx].second,
			m_model_data[m_int2sa[s_a_idx]][s_r_idx].first,
			m_model_data[m_int2sa[s_a_idx]][s_r_idx].second);
	};
private:
	//record the S_A pair happend;
	vector<pair<state_type, action_type>> m_int2sa;
	//record the SASR sequences;
	map<pair<state_type, action_type>, vector<pair<state_type, double>>> m_model_data;
};




#endif // !SIMPLE_MODEL_H

