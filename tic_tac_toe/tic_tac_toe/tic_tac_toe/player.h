#ifndef PLAYER_H
#define PLYAER_H




#include<vector>
#include<string>
#include<map>
#include<iostream>
#include<random>
#include<algorithm>
#include<fstream>
#include<time.h>

#include"state.h"


using namespace std;

class player
{
public:
	player(double step_size=0.1,double epsilon=0.1);
	~player();
	int symbol()const { return m_symbol; }
	int & symbol(){ return m_symbol; }
	//reset the states sequence, but keep the trained estimation;
	void reset();
	//append the states;
	void set_state( state & rhs);
	//initialize the symbol, states set and estimation;
	virtual void set_symbol(int symbol,map<int,state> & all_states);
	//update the estimation for every ecountered states;
	virtual void backup();
	//act according to the current estimations in eplison-greedy methond;
	virtual std::pair<int,int> act(map<int,state> & all_states);
	void save_policy();
	void load_policy();
protected:
	//From hash_value of state to state value; 
	map<int, double> m_estimation;
	//learning ratio;
	double m_step_size;
	//probability to explore;
	double m_epsilon;
	//the executed states of the player;
	vector<int> m_executed_states;
	//whether the executed stated is greedy;
	vector<bool> m_is_greedy;
	//the symbol for the player;
	int m_symbol;
};

#endif