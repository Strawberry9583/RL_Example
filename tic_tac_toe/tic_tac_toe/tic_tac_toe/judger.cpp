#include"judger.h"

judger::judger(const human_player & human, const player & p2, map<int, state>& all_states) {
	//load all states into player  estimations;
	m_player2 = p2;
	m_player2.symbol() = -1;
}

judger::judger(const player & p1,const player & p2, map<int,state> & rhs):m_player1(p1),m_player2(p2) {
	//load all states into player  estimations;
	m_player1.set_symbol(m_p1_symbol, rhs);
	m_player2.set_symbol(m_p2_symbol, rhs);
}

judger::~judger() {
}

void judger::reset() {
	m_player1.reset();
	m_player2.reset();
}

int judger::play(map<int,state> & rhs) {
	this->reset();
	state current_state;
	m_player1.set_state(current_state);
	m_player2.set_state(current_state);
	//to be alternative for player1 and player2;
	bool is_player1 = true;
	//continue until resulting winner;
	while (1) {
		if (is_player1) {
			auto temp = m_player1.act(rhs);
			state next_state = current_state.next_state(temp.first, temp.second, m_p1_symbol);
			current_state = next_state;
			is_player1 = !is_player1;
		}
		else {
			auto temp = m_player2.act(rhs);
			state next_state = current_state.next_state(temp.first, temp.second, m_p2_symbol);
			current_state = next_state;
			is_player1 = !is_player1;
		}
		
		if (current_state.is_end()) {
			m_player1.set_state(current_state);
			m_player2.set_state(current_state);
			return current_state.winner();
		}
		else {
			m_player1.set_state(current_state);
			m_player2.set_state(current_state);
		}

		
	}
}

void judger::backup(player & p1,player & p2) {
	//p1 = m_player1;
	//p2 = m_player2;
	m_player1.backup();
	m_player2.backup();
}

void judger::save_policy() {
	m_player1.save_policy();
	m_player2.save_policy();
}

int judger::game(map<int, state>& rhs) {
	this->reset();
	state current_state;
	m_human.set_state(current_state);
	m_player2.set_state(current_state);
	//to be alternative for player1 and player2;
	bool is_player1 = true;
	//continue until resulting winner;
	while (1) {
		if (is_player1) {
			auto temp = m_human.act(rhs);
			state next_state = current_state.next_state(temp.first, temp.second, m_p1_symbol);
			current_state = next_state;
			is_player1 = !is_player1;
		}
		else {
			auto temp = m_player2.act(rhs);
			state next_state = current_state.next_state(temp.first, temp.second, m_p2_symbol);
			current_state = next_state;
			is_player1 = !is_player1;
		}

		if (current_state.is_end()) {
			m_human.set_state(current_state);
			m_player2.set_state(current_state);
			return current_state.winner();
		}
		else {
			m_human.set_state(current_state);
			m_player2.set_state(current_state);
		}


	}
}
