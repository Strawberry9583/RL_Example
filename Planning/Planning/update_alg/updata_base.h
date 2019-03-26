#ifndef UPDATE_BASE_H
#define UPDATE_BASE_H

#include"../model/base.h"

#include<random>
#include<algorithm>
#include<map>
#include<iostream>
#include<vector>
#include<set>
#include<fstream>


template<typename state_type,typename action_type>
class update_base:public base {

public:

	update_base() :base(), m_learning_ratio(0.1) { m_random_engine.seed(0); };
	virtual ~update_base() {};

	//greedy action selecting;
	action_type best_action(const state_type & state) const{
		vector<pair<action_type, double> > action_set;
		for (auto & i : m_q_value) {
			if (i.first.first == state) {
				action_set.emplace_back(i.first.second, i.second);
			}
		}
		return max_element(action_set.begin(), action_set.end(), \
			[](const pair<action_type, double> & rhs1,const pair<action_type, double> & rhs2) \
			{return rhs1.second < rhs2.second; })->first;
	}
	//eplison_greedy action selecting;
	action_type epsilon_action(const state_type & state, double epsilon) {
		uniform_real_distribution<double> d_rand;

		if (d_rand(m_random_engine) < epsilon) {
			uniform_int_distribution<int> uni_int(0, m_state_actions.at(state).size() - 1);
			return m_state_actions[state][uni_int(m_random_engine)];
		}
		else {
			return best_action(state);
		}
	}
	//random action selecting;
	action_type random_action(const state_type & state) {
		uniform_int_distribution<int> uni_int(0,m_state_actions.at(state).size()-1);
		return m_state_actions[state][uni_int(m_random_engine)];
	}

	//bool is_state_occur(const state_type & state)const {
	//	//check whether the state_type is;
	//	for (auto & i : m_q_value) {
	//		if (i->first.first == state) {
	//			return true;
	//		}
	//	}
	//	return false;
	//}

	//interface of m_q_value;
	void set_q_value(const map <pair<state_type, action_type>,double> & q_value) {
		m_q_value = q_value;
	}
	void set_q_value(const state_type & state, const action_type & action, double q_value) {
		m_q_value[make_pair(state, action)] = q_value;
	}
	const map<pair<state_type, action_type>, double> & q_value() const { return m_q_value; }
	map<pair<state_type, action_type>, double>& q_value() { return m_q_value; }

	//interface of m_v_value;
	map<state_type, double> & v_value() { return m_v_value; }
	const map<state_type, double>& v_value()const { return m_v_value; }
	void set_v_value(const map<state_type, double> & v_value) { m_q_value = q_value; }
	//interface of m_state_actions;
	void set_state_actions(const map <state_type,vector<action_type> > & state2actions) {
		m_state_actions = state2actions;
	}
	const map<state_type, vector<action_type>> & state2actions() const { return state2actions; }
	map<state_type, vector<action_type>>& state2action2() { return state2actions; }
	void set_learning_ratio(double ratio) { m_learning_ratio = ratio; }
	double learning_ratio()const { return m_learning_ratio; }

	void initialize() {
		for (auto i = m_state_actions.begin(); i != m_state_actions.end(); ++i) {
			m_v_value[i->first] = 0.;
			for (auto & j : i->second) {
				m_q_value[make_pair(i->first, j)] = 0.;
			}
		}
	}
protected:
	//the state and its conresponding actions;
	map<state_type, vector<action_type> > m_state_actions;
	//the state_value;
	map<state_type, double> m_v_value;
	//the state_action value;
	map<pair<state_type, action_type>, double> m_q_value;
	//learning ratio;
	double m_learning_ratio;
	//random engine for learning alg.;
	default_random_engine m_random_engine;
};

#endif // !UPDATE_ALG_H

