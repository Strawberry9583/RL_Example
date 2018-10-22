#include"player.h"


player::player(double step_size,double epsilon){
	m_step_size = step_size;
	m_epsilon = epsilon;
}

player::~player(){

}

void player::reset(){
	m_executed_states.clear();
	m_is_greedy.clear();
}

void player::set_state( state & rhs){
	m_executed_states.push_back(rhs.hash());
	m_is_greedy.push_back(true);
}

void player::set_symbol(int symbol,  map<int,state> & all_states){
	m_symbol = symbol;
	// initialize the estimation set;
	for (auto & i : all_states) {
		if (i.second.is_end()) {
			if (i.second.winner() == symbol) {
				m_estimation.insert(make_pair(i.first, 1.0));
			}
			else if (i.second.winner() == -symbol) {
				m_estimation.insert(make_pair(i.first, 0.0));
			}
			//it's a tie;
			else {
				m_estimation.insert(make_pair(i.first, 0.5));
			}
		}
		// the initial state value is non-heuristic, which is 0.5;
		else {
			m_estimation.insert(make_pair(i.first, 0.5));
		}
	}

}

void player::backup(){
	//for (auto rit=m_executed_states.rbegin()+1; rit!=m_executed_states.rend(); ++rit) {
	//	// update the estimation value of states in reverse orders;
	//	//without multiplied by m_greedy;
	//	double td_error = m_estimation[(*rit) + 1] - m_estimation[*rit];
	//	m_estimation[*rit] += m_step_size*td_error;
	//}
	for (int i = m_executed_states.size() - 2; i > -1; --i) {
		double td_error = m_estimation[m_executed_states[i + 1]] - m_estimation[m_executed_states[i]];
		td_error *= m_is_greedy[i];
		m_estimation[m_executed_states[i]] += m_step_size*td_error;
	}
	for (auto & i : m_executed_states) {
		cout << i << "  ";
	}
	cout << endl;
}

std::pair<int,int> player::act(map<int,state> & all_states) {

	//the first is action position, the second is idx of the next state;
	vector<pair<pair<int, int>,int> > next_position;
	//get all feasible position to play;
	for (int i = 0; i < state().row_num(); ++i) {
		for (int j = 0; j < state().col_num(); ++j) {
			//the position is empty, so piece can be put;
			state current_state = all_states[*m_executed_states.rbegin()];
			if (current_state.data()[i][j] == 0) {
				state next_one = current_state.next_state(i, j, m_symbol);
				next_position.emplace_back(make_pair(i, j), next_one.hash());
			}
		}
	}
	//epsilon greedy method to choose one next position;
	std::default_random_engine rand_generator(time(nullptr));
	std::uniform_int_distribution<int> uniform_int_distr(0,next_position.size()-1);
	std::uniform_real_distribution<double> uniform_double_distr(0.0,1.0);
	double rand = uniform_double_distr(rand_generator);
	//non-greddy;
	if (rand < m_epsilon) {
		int rand_int=uniform_int_distr(rand_generator);
		//m_executed_states.push_back(next_position[rand_int].second);
		*m_is_greedy.rbegin() = false;
		return next_position[rand_int].first;
	}
	//greedy method;
	else {//find the action with larget estimation;
		//to capture the m_estimation;
		auto estimation = m_estimation;
		auto greedy_action=max_element(next_position.begin(),next_position.end(),
			[=](const std::pair<pair<int,int>,int> & rhs1,const std::pair<pair<int,int>,int> & rhs2) {
			return m_estimation[rhs1.second] < m_estimation[rhs2.second]; });
		return greedy_action->first;
	}


}

void player::save_policy() {
	//save the trained estimation;
	string filename;
	if (m_symbol == 1) {
		filename = "policy_1.txt";
	}
	else {
		filename = "policy_2.txt";
	}
	ofstream ofile(filename);
	for (auto & i : m_estimation) {
		ofile << i.first << "  " << i.second << endl;
	}
	ofile.close();
}

void player::load_policy() {
	string filename;
	if (m_symbol == 1) {
		filename = "policy_1.txt";
	}
	else {
		filename = "policy_2.txt";
	}
	//read the policy;
	ifstream ifile(filename);
	pair<int, double> temp_pair;
	while (ifile) {
		ifile >> temp_pair.first >> temp_pair.second;
		m_estimation.insert(temp_pair);
	}
	ifile.close();
}
