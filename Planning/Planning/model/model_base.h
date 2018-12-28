#include"../definition.h"
#include<map>
#include<vector>
#include<random>

using namespace std;

class model_base {
public:
	model_base();
	~model_base();
	virtual void feed(STATE_TYPE, MAZE_ACTION_TYPE, STATE_TYPE, double) {};
	virtual SASR_QUADRUPLE sample() {};
protected:
	map<pair<STATE_TYPE, MAZE_ACTION_TYPE>, vector<STATE_TYPE, double>> m_model_data;
	default_random_engine m_random_engine;
};

model_base::model_base() {
	m_random_engine.seed(0);
}

model_base::~model_base() {
}