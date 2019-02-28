#ifndef  RANDOM_WALK_H
#define random_WALK_H

#include"../problem_base.h"
#include"../../definition/definition.h"
#include<vector>
#include<string>
#include<map>
#include<algorithm>
#include<iostream>
#include<numeric>



class random_walk: public problem_base<RANDOM_WALK_STATE_TYPE, RANDOM_WALK_ACTION_TYPE> {
public:

	random_walk(int states_num =11);
	~random_walk();
	void initialize()override;
	RANDOM_WALK_STATE_TYPE & start() { return m_start; }
	const RANDOM_WALK_STATE_TYPE & start() const { return m_start; }
	vector<RANDOM_WALK_STATE_TYPE> & terminal() { return m_terminal; }
	const vector<RANDOM_WALK_STATE_TYPE> & terminal()const  { return m_terminal; }
	pair<RANDOM_WALK_STATE_TYPE, double> next_state(const RANDOM_WALK_STATE_TYPE & state, const RANDOM_WALK_ACTION_TYPE & action)override;


private:
	int m_states_num;
	RANDOM_WALK_STATE_TYPE m_start;
	RANDOM_WALK_STATE_TYPE m_left_end;
	RANDOM_WALK_STATE_TYPE m_right_end;
	vector<RANDOM_WALK_STATE_TYPE> m_terminal;
};




#endif // ! RANDOM_WALK_H


