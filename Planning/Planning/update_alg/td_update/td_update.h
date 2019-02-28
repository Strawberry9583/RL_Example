#ifndef TD_UPDATE_H
#define TD_UPDATE_H

#include"../updata_base.h"


template<typename state_type,typename action_type>
class td_update :public update_base<state_type,action_type> {

public:
	td_update() :update_base<state_type, action_type>(),m_dicount_factor(1.0) {}

	virtual ~td_update() {}

	void initialize(map<state_type, vector<action_type> > state_actions) { 
		this->m_state_actions = state_actions;
		update_base<state_type, action_type>::initialize();
	}

	// on_policy TD(0) control alg. update (Sarsa)
	void update_q(const state_type & state, const action_type & action, const state_type & next_state, 
		const action_type & next_aciton,double r) {
		//class template can resolve the elements of its superclass;
		this->m_q_value[make_pair(state,action)] += this->m_learning_ratio*
			(r+m_dicount_factor*this->m_q_value[make_pair(next_state,next_aciton)]-this->m_q_value[make_pair(state,action)]);
	}

	// TD(0) predication alg. for state_value;
	void update_v(const state_type & state,const state_type & next_state,double r) {
		//this->m_v_value[state] +=0.01*(r + m_dicount_factor*this->m_v_value[next_state] - this->m_v_value[state]);
		this->m_v_value[state] +=this->m_learning_ratio*(r + m_dicount_factor*this->m_v_value[next_state] - this->m_v_value[state]);
	}
	
private:
	double m_dicount_factor;
};



#endif // !Q_LEARNING_H

