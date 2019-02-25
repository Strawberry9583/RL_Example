#ifndef PROBLEM_BASE_H
#define PROBLEM_BASE_H

#include"../model/base.h"
#include<vector>
#include<map>

template<typename state_type,typename action_type>
class problem_base: public base{
public:
	problem_base() = default;
	virtual ~problem_base() {}
	void set_states(vector<state_type> & states) { m_states = states; }
	void set_actions(vector<action_type> & actions) { m_actions = actions; }
	void set_states2actions(map<state_type, vector<action_type> > & states2actions)
	{	m_states2actions = states2actions;}
	void set_states2reward(map<state_type, double> & states2rewards) 
	{	m_state2reward = states2rewards;}
	virtual pair<state_type,double> next_state(const state_type & state, const action_type & action)
	{ return make_pair(state_type(),0.); }


protected:
	//states set;
	vector<state_type> m_states;
	//overall action set;
	vector<action_type> m_actions;
	//action set conresponding to the state;
	map<state_type, vector<action_type>> m_states2actions;
	//reward conresponding to the the state;
	map<state_type, double> m_state2reward;
};



#endif // !PROBLEM_BASE_H

