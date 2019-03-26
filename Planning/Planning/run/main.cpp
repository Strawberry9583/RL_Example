#include"../model/simple_model.h"
#include"../update_alg/td_update/td_update.h"
#include"../problem/grid/grid.h"
#include"../problem/cliff_walking/cliff_walking.h"
#include"../problem/random_walk/random_walk.h"

#include<iostream>

void simple_model_test() {
	//test simple_model;
	simple_model<GRID_STATE_TYPE, GRID_ACTION_TYPE> grid_model;
	GRID_STATE_TYPE s0(0, 0);
	GRID_STATE_TYPE s1(1, 0);

	GRID_ACTION_TYPE a0 = GRID_ACTION_TYPE::GRID_ACTION_UP;
	GRID_ACTION_TYPE a1 = GRID_ACTION_TYPE::GRID_ACTION_DOWN;
	GRID_ACTION_TYPE a2 = GRID_ACTION_TYPE::GRID_ACTION_LEFT;
	GRID_ACTION_TYPE a3 = GRID_ACTION_TYPE::GRID_ACTION_RIGHT;

	grid_model.feed(s0, a0, s1, 0.0);
	grid_model.feed(s0, a0, s1, 1.0);
	grid_model.feed(s0, a0, s1, 2.0);
	grid_model.feed(s0, a1, s1, 0.0);
	grid_model.feed(s0, a1, s1, 0.0);
	grid_model.feed(s1, a1, s1, 0.0);
	for (int i = 0; i < 100; ++i) {
		auto sample0 = grid_model.sample();
		cout << std::get<0>(sample0).first << "  " << std::get<0>(sample0).second << "  "
			<< std::get<1>(sample0) << "  " << std::get<2>(sample0).first << "  " << std::get<2>(sample0).second
			<< "  " << std::get<3>(sample0) << endl;
	}

	auto sample1 = grid_model.sample();
	auto sample2 = grid_model.sample();
	auto sample3 = grid_model.sample();
	auto sample4 = grid_model.sample();
	auto sample5 = grid_model.sample();
}

void td_update_best_test() {
	map<GRID_STATE_TYPE, vector<GRID_ACTION_TYPE>> grid_state2actions;
	GRID_STATE_TYPE s0(0, 0);
	GRID_STATE_TYPE s1(1, 0);
	vector<GRID_ACTION_TYPE> actionset = { GRID_ACTION_TYPE::GRID_ACTION_UP,GRID_ACTION_TYPE::GRID_ACTION_DOWN,
		GRID_ACTION_TYPE::GRID_ACTION_LEFT,GRID_ACTION_TYPE::GRID_ACTION_RIGHT };
	grid_state2actions.insert(make_pair(s0, actionset));
	grid_state2actions[s1] = actionset;
	GRID_ACTION_TYPE a0 = GRID_ACTION_TYPE::GRID_ACTION_UP;
	GRID_ACTION_TYPE a1 = GRID_ACTION_TYPE::GRID_ACTION_DOWN;
	GRID_ACTION_TYPE a2 = GRID_ACTION_TYPE::GRID_ACTION_LEFT;
	GRID_ACTION_TYPE a3 = GRID_ACTION_TYPE::GRID_ACTION_RIGHT;

	map<pair<GRID_STATE_TYPE, GRID_ACTION_TYPE>, double> q_value;
	q_value.emplace(make_pair(s0, a0), 0);
	q_value.emplace(make_pair(s0, a1), 1.0);
	q_value.emplace(make_pair(s0, a2), 5);
	q_value.emplace(make_pair(s1, a0), 0);
	q_value.emplace(make_pair(s1, a1), 1.0);
	q_value.emplace(make_pair(s1, a2), 0.5);
	td_update<GRID_STATE_TYPE, GRID_ACTION_TYPE> td_update;
	td_update.set_state_actions(grid_state2actions);
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

void grid_test() {
	grid pro;
	//pro.print_grid();
 	auto temp = pro.next_state(GRID_STATE_TYPE(1, 1), GRID_ACTION_TYPE::GRID_ACTION_DOWN);
}

void random_walk_td_update_v_test() {
	random_walk random_walk;
	random_walk.initialize();
	td_update<RANDOM_WALK_STATE_TYPE, RANDOM_WALK_ACTION_TYPE> td_update;
	td_update.initialize(random_walk.states2actions());
	
	for (int i = 0; i < 5000; ++i) {
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

void cliff_walk_sarsa_test() {
	//ofstream ofile("./result/cliff_walking/sarsa_cliff_walking.csv");

	cliff_walking cliff_problem;
	cliff_problem.initialize();
	td_update<GRID_STATE_TYPE, GRID_ACTION_TYPE> td;
	td.initialize(cliff_problem.states2actions());
	for (int i = 0; i < 500; ++i) {
		double return_for_episode = 0.;

		GRID_STATE_TYPE s = cliff_problem.start();
		GRID_ACTION_TYPE a = td.epsilon_action(s, 0.1);
		while (s != cliff_problem.goal()) {
			auto next = cliff_problem.next_state(s, a);
			return_for_episode += next.second;
			GRID_ACTION_TYPE a_next = td.epsilon_action(next.first, 0.1);
			td.update_q(s, a, next.first, a_next, next.second);
			s = next.first;
			a = a_next;
		}
		cout << return_for_episode << endl;
		//ofile <<i<< return_for_episode << endl;
	}
	//ofile.close();
	//GRID_ACTION_TYPE a0 = GRID_ACTION_TYPE::GRID_ACTION_UP;
	//GRID_ACTION_TYPE a1 = GRID_ACTION_TYPE::GRID_ACTION_DOWN;
	//GRID_ACTION_TYPE a2 = GRID_ACTION_TYPE::GRID_ACTION_LEFT;
	//GRID_ACTION_TYPE a3 = GRID_ACTION_TYPE::GRID_ACTION_RIGHT;
	//auto next0 = cliff_problem.next_state(s0, a0);
	//auto next1 = cliff_problem.next_state(s0, a1);
	//auto next2 = cliff_problem.next_state(s0, a2);
	//auto next3 = cliff_problem.next_state(s0, a3);
}

void cliff_walk_q_learning_test() {
	//ofstream ofile("./result/cliff_walking/q_learning_cliff_walking.csv");
	cliff_walking cliff_problem;
	cliff_problem.initialize();
	td_update<GRID_STATE_TYPE, GRID_ACTION_TYPE> td;
	td.initialize(cliff_problem.states2actions());
	for (int i = 0; i < 500; ++i) {
		double return_for_episode = 0.;

		GRID_STATE_TYPE s = cliff_problem.start();
		
		while (s != cliff_problem.goal()) {
			GRID_ACTION_TYPE a = td.epsilon_action(s, 0.1);
			auto next = cliff_problem.next_state(s, a);
			return_for_episode += next.second;
			td.update_q(s, a, next.first, next.second);
			s = next.first;
		}
		cout << return_for_episode << endl;
		//ofile << i << return_for_episode << endl;
	}
	//ofile.close();
}

int main() {
	cliff_walk_sarsa_test();
	cliff_walk_q_learning_test();
	std::cin.get();
	return 0;
}