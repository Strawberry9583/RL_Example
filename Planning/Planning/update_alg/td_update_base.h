#ifndef TD_UPDATE_BASE_H
#define TD_UPDATE_BASE_H

#include"updata_base.h"

template<typename state_type,typename action_type>
class td_update_base :public update_base<state_type,action_type> {

public:
	td_update_base() :update_base<state_type, action_type>() {}
	virtual ~td_update_base() {}

	virtual void update_q(const state_type & state, const action_type & action, const state_type & next_state, double r) {
		
	}

	virtual void update_v() {}
	
private:
	void update_q_() {}
};



#endif // !Q_LEARNING_H

