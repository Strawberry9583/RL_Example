#include "temporal_difference.h"

temporal_difference::temporal_difference() {
}

temporal_difference::temporal_difference(size_t num_state,size_t episode) :update_alg(),m_num_state(num_state),
m_episode_num(episode),m_rand_generator(0), m_uni_real_rand(0.0, 1.0){
	m_name = "TD";
	m_value.resize(m_num_state);
	//the right and left state value is 1.0 and 0, respectively;
	//the other states value is 0.5;
	for (auto & i : m_value) {
		i = 0.5;
	}
	*m_value.rbegin() = 1.0;
	*m_value.begin() = 0.0;


}

temporal_difference::~temporal_difference() {
}

void temporal_difference::train() {
	//for batch learning record;
	vector<vector<double>> rewards;
	vector<vector<size_t>> trajetories;
	for (size_t i = 0; i < m_episode_num; ++i) {
		double error = 0.0;
		for (size_t i = 1; i < m_num_state - 1; ++i) {
			error += fabs(m_value[i] - (static_cast<double>(i) / 6.0));
		}
		cout << i << "  " << error << endl;
		update_value();

		if (!m_is_batch) {
			m_reward.clear();
			m_trajectory.clear();
		}
		else{
			//record rewards and trajectory for batche learning;
			rewards.push_back(m_reward);
			trajetories.push_back(m_trajectory);
			m_reward.clear();
			m_trajectory.clear();
			//keep updateing until updating converges;
			while (true) {
				vector<double> updates(m_num_state);
				//update for all recorded trajectories;
				for (int i = 0; i <trajetories.size(); ++i) {
					//update all states experienced;
					for (int j = 0; j < trajetories[i].size() - 1; ++j) {
						//calculate the error;
						//R(t+1) + gamma*( V(S(t+1)) - V(S(t))
						updates[trajetories[i][j]] += rewards[i][j] +
							m_value[trajetories[i][j + 1]] - m_value[trajetories[i][j]];
					}

				}
				//calculate the alpha*error; and update;
				double total_update = 0.0;
				for (size_t i = 1; i < updates.size()-1;++i) {
					updates[i] *= m_alpha;
					total_update += fabs(updates[i]);
					m_value[i] += updates[i];
				}
				//updating value is small, then update finished;
				if (total_update < 1e-3) {
					break;
				}
			}
		}
	}
}

void temporal_difference::update_value() {
	size_t front = m_num_state / 2;
	m_trajectory.push_back(front);
	m_reward.push_back(0.);
	size_t back;
	//set random seed;
	//std::default_random_engine rand_generator(time(nullptr));
	//std::uniform_real_distribution<double> uni_real_rand(0.0, 1.0);
	while (true) {
		back = front;
		double rand = m_uni_real_rand(m_rand_generator);
		//move to left or right randomly;
		if (rand < 0.5) {
			--front;
		}
		else {
			++front;
		}
		// record the trajectory and reward for batch learning;
		m_trajectory.push_back(front);
		//all reward is 0;
		double reward = 0.0;
		if (!m_is_batch) {
			//update the value according to TD(0) function;
			// V(S(t))<-- V(S(t))+ alpha*( R(t+1) + gamma*( V(S(t+1)) - V(S(t)) )
			m_value[back] = m_value[back]+ m_alpha*(reward + m_gamma*m_value[front] - m_value[back]);
		}
		// reach the terminal state;
		if (front == m_num_state - 1 || front == 0) {
			break;
		}
		//avoid updating the terminal state;
		m_reward.push_back(reward);
	}
}

void temporal_difference::record() {
	ofstream ofile;
	//transfer the int into string and add the filepath;
	stringstream stream;
	stream <<"../data/"<< m_name << "_"<<m_alpha<<"_" << m_episode_num << "_"<<m_num_state<<"_";
	if (m_is_batch) {
		stream << "batched.csv";
	}
	else {
		stream << "unbatched.csv";
	}
	string filename;
	stream >> filename;
	ofile.open(filename, ios::out);
	for (size_t i =1; i < m_num_state-1; ++i) {
		ofile << i << ',' << m_value[i] << endl;
	}
	ofile.close();
}
