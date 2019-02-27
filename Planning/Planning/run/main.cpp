#include"../model/simple_model.h"
#include"../update_alg/td_update.h"
#include"../problem/maze.h"
#include"../problem/random_walk.h"

#include<iostream>

void simple_model_test() {
	//test simple_model;
	simple_model<MAZE_STATE_TYPE, MAZE_ACTION_TYPE> maze_model;
	MAZE_STATE_TYPE s0(0, 0);
	MAZE_STATE_TYPE s1(1, 0);

	MAZE_ACTION_TYPE a0 = MAZE_ACTION_TYPE::MAZE_ACTION_UP;
	MAZE_ACTION_TYPE a1 = MAZE_ACTION_TYPE::MAZE_ACTION_DOWN;
	MAZE_ACTION_TYPE a2 = MAZE_ACTION_TYPE::MAZE_ACTION_LEFT;
	MAZE_ACTION_TYPE a3 = MAZE_ACTION_TYPE::MAZE_ACTION_RIGHT;

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
	vector<MAZE_ACTION_TYPE> actionset = { MAZE_ACTION_TYPE::MAZE_ACTION_UP,MAZE_ACTION_TYPE::MAZE_ACTION_DOWN,
		MAZE_ACTION_TYPE::MAZE_ACTION_LEFT,MAZE_ACTION_TYPE::MAZE_ACTION_RIGHT };
	maze_state2actions.insert(make_pair(s0, actionset));
	maze_state2actions[s1] = actionset;
	MAZE_ACTION_TYPE a0 = MAZE_ACTION_TYPE::MAZE_ACTION_UP;
	MAZE_ACTION_TYPE a1 = MAZE_ACTION_TYPE::MAZE_ACTION_DOWN;
	MAZE_ACTION_TYPE a2 = MAZE_ACTION_TYPE::MAZE_ACTION_LEFT;
	MAZE_ACTION_TYPE a3 = MAZE_ACTION_TYPE::MAZE_ACTION_RIGHT;

	map<pair<MAZE_STATE_TYPE, MAZE_ACTION_TYPE>, double> q_value;
	q_value.emplace(make_pair(s0, a0), 0);
	q_value.emplace(make_pair(s0, a1), 1.0);
	q_value.emplace(make_pair(s0, a2), 5);
	q_value.emplace(make_pair(s1, a0), 0);
	q_value.emplace(make_pair(s1, a1), 1.0);
	q_value.emplace(make_pair(s1, a2), 0.5);
	td_update<MAZE_STATE_TYPE, MAZE_ACTION_TYPE> td_update;
	td_update.set_state_actions(maze_state2actions);
	for (int i = 0; i < 100; ++i) {
		cout << td_update.random_action(s0) << endl;
	}

	td_update.set_q_value(q_value);
	for (int i = 0; i < 100; ++i) {
		auto action0 = td_update.best_action(s0);
		auto action1 = td_update.epsilon_action(s0,0.1);
		cout << action0 << "  " << action1 << endl;;
		cout << td_update.q_value()[make_pair(s0,a0)] << endl;
		cout << td_update.q_value()[make_pair(s1, a1)] << endl;
		td_update.update_q(s0, a0, s1, a1, 0.1);
		cout << td_update.q_value()[make_pair(s0, a0)] << endl;
		
	}

	auto action1 = td_update.best_action(s1);
	cout << action1 << endl;
}

void maze_test() {
	maze pro;
	pro.print_maze();
 	auto temp = pro.next_state(MAZE_STATE_TYPE(1, 1), MAZE_ACTION_TYPE::MAZE_ACTION_DOWN);
}

void random_walk_td_update_v_test() {
	random_walk random_walk;
	random_walk.initailize();
	td_update<RANDOM_WALK_STATE_TYPE, RANDOM_WALK_ACTION_TYPE> td_update;
	td_update.initialize(random_walk.states2actions());
	
	for (int i = 0; i < 50000; ++i) {
		//restart the state;
		RANDOM_WALK_STATE_TYPE state = random_walk.start();
		//if not terminal, then go on;
		while (find(random_walk.terminal().begin(),random_walk.terminal().end(),state)== random_walk.terminal().end()){
			//get random action: left or right;
			RANDOM_WALK_ACTION_TYPE action = td_update.random_action(state);
			auto next = random_walk.next_state(state, action);
			td_update.update_v(state, next.first, next.second);
			state = next.first;
		}
		for (auto &i : td_update.v_value()) {
			cout << i.second << "  ";
		}
		cout << endl;
	}
	
}

int main() {
	random_walk_td_update_v_test();
	td_update_best_test();
	std::cin.get();
	return 0;
}