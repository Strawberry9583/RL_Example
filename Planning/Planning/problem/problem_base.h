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
	virtual void initialize() {}
	void set_states(vector<state_type> & states) { m_states = states; }
	vector<state_type> & states() { return m_states; }
	const vector<state_type> & states()const { return m_states; }
	void set_actions(vector<action_type> & actions) { m_actions = actions; }
	vector<action_type> & actions(){ return m_actions; }
	const vector<action_type> & actions()const { return m_actions; }
	void set_states2actions(map<state_type, vector<action_type> > & states2actions)
	{	m_states2actions = states2actions; }
	map<state_type, vector<action_type> > & states2actions() { return m_states2actions; }
	const map<state_type, vector<action_type> > & states2actions()const { return m_states2actions; }
	void set_states2reward(map<state_type, double> & states2rewards) 
	{	m_state2reward = states2rewards;}
	map<state_type, double> & states2rewards() { return states2rewards; }
	const map<state_type, double> & states2rewards()const { return states2rewards; }

	virtual pair<state_type,double> next_state(const state_type & state, const action_type & action)
	{ return make_pair(state_type(),0.); }

protected:
	//states set;
	vector<state_type> m_states;
	//overall action set;
	vector<action_type> m_actions;
	//action set conresponding to the state;
	map<state_type, vector<action_type>> m_states2actions;
	//returns conresponding to the the state;
	map<state_type, double> m_state2reward;
};



#endif // !PROBLEM_BASE_H

