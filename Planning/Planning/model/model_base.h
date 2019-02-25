#ifndef MODEL_BASE_H
#define MODEL_BASE_H

#include"base.h"
#include"../definition/definition.h"
#include<map>
#include<vector>
#include<random>


template<typename state_type,typename action_type>
class model_base:public base {

public:

	model_base(){ m_random_engine.seed(0); };
	virtual ~model_base() {};
	virtual void feed(const state_type & state, const action_type & action, const state_type & next_state, double reward) {}
	virtual tuple<state_type,action_type,state_type,double> sample() {
		return make_tuple(state_type(), action_type(), state_type(), double()); 
	}

protected:

	//random numbers engines;
	default_random_engine m_random_engine;

};


#endif // !MODEL_BASE_H


