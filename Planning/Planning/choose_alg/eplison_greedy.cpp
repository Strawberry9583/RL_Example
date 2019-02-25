//#include"epsilon_greedy.h"
//
//epsilon_greedy::epsilon_greedy() {
//}
//
//epsilon_greedy::~epsilon_greedy() {
//}
//
//MAZE_ACTION_TYPE epsilon_greedy::choose_action(const map<pair<STATE_TYPE, MAZE_ACTION_TYPE>, double> & q_value, const STATE_TYPE & state) {
//	vector<pair<MAZE_ACTION_TYPE, double>> action_set;
//	//get all possible actions;
//	for (auto & i : q_value) {
//		if (i.first.first == state ){
//			action_set.emplace_back(i.first.second, i.second);
//		}
//	}
//	default_random_engine ran_engine;
//	ran_engine.seed(0);
//	uniform_real_distribution<double> distr_float(0., 1.);
//	uniform_int_distribution<int> distr_int(0, action_set.size());
//	double explore_pro = distr_float(ran_engine);
//	//if rand<eplison, then explore;
//	if (explore_pro < m_eplison) {
//		return action_set[distr_int(ran_engine)].first;
//	}
//	//choose the action with largest q_value;
//	else {
//		auto choice = max_element(action_set.begin(), action_set.end(), \
//			[](const pair<MAZE_ACTION_TYPE, double> & rhs1, const pair<MAZE_ACTION_TYPE, double> & rhs2)\
//		{return rhs1.second < rhs2.second; });
//		return choice->first;
//	}
//}
