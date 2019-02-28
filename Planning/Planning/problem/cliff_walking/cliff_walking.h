#ifndef CLIFF_WALKING_H
#define CLIFF_WALKING_H

#include"../grid/grid.h"

class cliff_walking:public grid {
public:
	cliff_walking();
	~cliff_walking();
	//interface to member;
	const GRID_STATE_TYPE & goal() const { return m_goal; }
	GRID_STATE_TYPE & goal() { return m_goal; }
	const GRID_STATE_TYPE & start() const { return m_start; }
	GRID_STATE_TYPE & start() { return m_start; }
	void initialize()override;
	pair<GRID_STATE_TYPE, double>  next_state(const GRID_STATE_TYPE  & state, const GRID_ACTION_TYPE & action)override;

private:
	//the start&goal point of the grid;
	GRID_STATE_TYPE m_start;
	GRID_STATE_TYPE m_goal;
	//cliff position
	set<GRID_STATE_TYPE> m_cliff_set;
};



#endif // !CLIFF_WALKING

