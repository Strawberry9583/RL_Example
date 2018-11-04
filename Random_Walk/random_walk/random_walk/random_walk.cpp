#include "random_walk.h"


random_walk::random_walk(string alg_name, size_t state_num, size_t episode_num) : m_alg_name(alg_name),
m_state_num(state_num),m_episode(episode_num) {
	if (alg_name=="TD") {
		m_update_alg = std::unique_ptr<update_alg>(new temporal_difference(state_num,m_episode));
	}
	else if(alg_name=="MC") {
		m_update_alg = std::unique_ptr<update_alg>(new montecarlo(state_num, m_episode));
	}
	//else(alg_name == "MC") {
	//	m_update_alg = std::unique_ptr<update_alg>(new montecarlo(state_num, m_episode));
	//}
	//initialize the true value of the state;
	for (size_t i = 0; i < m_state_num; ++i) {
		m_true_value.push_back(static_cast<double>(i) / (m_state_num - 1));
	}
	//out put the true value of random_walk state;
	stringstream ss;
	ss <<"../data/"<< m_alg_name << "_true_value_" << m_state_num << ".csv";
	string filename;
	ss >> filename;
	ofstream ofile(filename, std::ios::out);
	for (size_t i = 1; i < m_true_value.size()-1;++i) {
		ofile << i << "," << m_true_value[i] << endl;
	}
	ofile.close();
}

void random_walk::run(size_t run_num) {
	if (run_num==1) {
		m_update_alg->train();
	}
	else {
		size_t run = 0;
		while (run<run_num) {
			//reset the value;
			//the right and left state value is 1.0 and 0, respectively;
			//the other states value is 0.5;
			for (auto & i : m_update_alg->value()) {
				i = 0.5;
			}
			*m_update_alg->value().rbegin() = 1.0;
			*m_update_alg->value().begin() = 0.0;
			m_update_alg->train();

		}

	}

}

void random_walk::record() {
	m_update_alg->record();
}

