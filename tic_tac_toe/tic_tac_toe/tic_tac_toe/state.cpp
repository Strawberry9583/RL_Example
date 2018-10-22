#include"state.h"

state::state():m_data(m_row_num,vector<int>(m_column_num,0)){

}

state::~state(){
}

//compute the hash value for one state, it's unique
int state::hash(){
	m_hash_value = 0;
	for (auto i = m_data.begin(); i != m_data.end(); ++i) {
		for (auto j = (*i).begin(); j != (*i).end(); ++j) {
			int temp = *j;
			if (temp == -1) {
				temp = 2;
			}
			m_hash_value = m_hash_value * 3 + temp;
		}
	}
	return m_hash_value;
}



bool state::is_end(){

	vector<int> results;
	//check for rows;
	for (auto & i : m_data) {
		results.push_back(std::accumulate(i.begin(), i.end(), 0));
	}
	//check for columns;
	int total_abs = 0;
	for (int i = 0; i < m_data.size(); ++i) {
		int temp_sum = 0;
		for (int j = 0; j < m_data.size(); ++j) {
			temp_sum += m_data[j][i];
			total_abs += abs(m_data[i][j]);
		}
		results.push_back(temp_sum);
	}
	results.push_back(0);
	//check for diagnals;
	for (int i = 0; i < m_data.size(); ++i) {
		*(results.end() - 1) += m_data[i][i];
	}
	results.push_back(0);
	for (int i = m_data.size() - 1, j = 0; j < m_data.size(); ++j, --i) {
		*(results.end() - 1) += m_data[i][j];
	}
	//check the winner;
	for (auto i = results.begin(); i != results.end(); ++i) {
		if ((*i) == 3) {
			m_winner = 1;
			m_is_end = true;
			return m_is_end;
		}
		if ((*i) == -3) {
			m_winner = -1;
			m_is_end = true;
			return m_is_end;
		}
	}
	//check the tie;
	if (total_abs == m_data.size()*m_data.size()) {
		m_winner = 0;
		m_is_end = true;
		return m_is_end;
	}
	// game goes on;
	m_is_end = false;
	return m_is_end;
}

state  state::next_state (int i, int j, int symbol)const{
	state next_state=*this;
	next_state.data()[i][j] = symbol;
	return next_state;
}

void state::print(){
	for (int i = 0; i < m_data.size(); ++i) {

		for (int j = 0; j < m_data.size(); ++j) {
			if (m_data[i][j] == 1) {
				cout << "*";
			}
			else if (m_data[i][j] == -1) {
				cout << "x";
			}
			else {
				cout << "0";
			}
		}
		cout << endl;
	}
}



