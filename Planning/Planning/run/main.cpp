#include"../model/simple_model.h"
#include"../update_alg/td_update_base.h"
#include"../problem/maze.h"

#include<iostream>

void simple_model_test() {
	//test simple_model;
	simple_model<MAZE_STATE_TYPE, MAZE_ACTION_TYPE> maze_model;
	MAZE_STATE_TYPE s0(0, 0);
	MAZE_STATE_TYPE s1(1, 0);

	MAZE_ACTION_TYPE a0 = MAZE_ACTION_TYPE::UP;
	MAZE_ACTION_TYPE a1 = MAZE_ACTION_TYPE::DOWN;
	MAZE_ACTION_TYPE a2 = MAZE_ACTION_TYPE::LEFT;
	MAZE_ACTION_TYPE a3 = MAZE_ACTION_TYPE::RIGHT;

	maze_model.feed(s0, a0, s1, 0.0);
	maze_model.feed(s0, a0, s1, 1.0);
	maze_model.feed(s0, a0, s1, 2.0);
	maze_model.feed(s0, a1, s1, 0.0);
	maze_model.feed(s0, a1, s1, 0.0);
	maze_model.feed(s1, a1, s1, 0.0);
	for (int i = 0; i < 100; ++i) {
		auto sample0 = maze_model.sample();
		cout << std::get<0>(sample0).first << "  " << std::get<0>(sample0).second << "  "
			<< std::get<1>(sample0) << "  " << std::get<2>(sample0).first << "  " << std::get<2>(sample0).second
			<< "  " << std::get<3>(sample0) << endl;
	}

	auto sample1 = maze_model.sample();
	auto sample2 = maze_model.sample();
	auto sample3 = maze_model.sample();
	auto sample4 = maze_model.sample();
	auto sample5 = maze_model.sample();
}

void td_update_best_test() {
	map<MAZE_STATE_TYPE, vector<MAZE_ACTION_TYPE>> maze_state2actions;
	MAZE_STATE_TYPE s0(0, 0);
	MAZE_STATE_TYPE s1(1, 0);
	vector<MAZE_ACTION_TYPE> actionset = { MAZE_ACTION_TYPE::UP,MAZE_ACTION_TYPE::DOWN,MAZE_ACTION_TYPE::LEFT,\
	MAZE_ACTION_TYPE::RIGHT };
	maze_state2actions.insert(make_pair(s0, actionset));
	maze_state2actions[s1] = actionset;
	MAZE_ACTION_TYPE a0 = MAZE_ACTION_TYPE::UP;
	MAZE_ACTION_TYPE a1 = MAZE_ACTION_TYPE::DOWN;
	MAZE_ACTION_TYPE a2 = MAZE_ACTION_TYPE::LEFT;
	MAZE_ACTION_TYPE a3 = MAZE_ACTION_TYPE::RIGHT;

	map<pair<MAZE_STATE_TYPE, MAZE_ACTION_TYPE>, double> q_value;
	q_value.emplace(make_pair(s0, a0), 0);
	q_value.emplace(make_pair(s0, a1), 1.0);
	q_value.emplace(make_pair(s0, a2), 5);
	q_value.emplace(make_pair(s1, a0), 0);
	q_value.emplace(make_pair(s1, a1), 1.0);
	q_value.emplace(make_pair(s1, a2), 0.5);
	td_update_base<MAZE_STATE_TYPE, MAZE_ACTION_TYPE> td_update;
	td_update.set_state_actions(maze_state2actions);
	
	td_update.set_q_value(q_value);
	for (int i = 0; i < 100; ++i) {
		auto action0 = td_update.best_action(s0);
		auto action1 = td_update.epsilon_action(s0,0.1);
		cout << action0 << "  " << action1 << endl;;
	}

	auto action1 = td_update.best_action(s1);
	cout << action1 << endl;
}

void maze_test() {
	maze pro;
	pro.print_maze();
	auto temp = pro.next_state(MAZE_STATE_TYPE(1, 1), MAZE_ACTION_TYPE::DOWN);
}



int main() {
	maze_test();

	std::cin.get();
	return 0;
}