#include "human_player.h"


human_player::human_player():  player() {
	m_input_key.insert(make_pair<char,pair<int,int>>('q', make_pair<int,int>(0, 0)));
	m_input_key.insert(make_pair<char, pair<int, int>>('w', make_pair<int, int>(0, 1)));
	m_input_key.insert(make_pair<char, pair<int, int>>('e', make_pair<int, int>(0, 2)));
	m_input_key.insert(make_pair<char, pair<int, int>>('a', make_pair<int, int>(1, 0)));
	m_input_key.insert(make_pair<char, pair<int, int>>('s', make_pair<int, int>(1, 1)));
	m_input_key.insert(make_pair<char, pair<int, int>>('d', make_pair<int, int>(1, 2)));
	m_input_key.insert(make_pair<char, pair<int, int>>('z', make_pair<int, int>(2, 0)));
	m_input_key.insert(make_pair<char, pair<int, int>>('x', make_pair<int, int>(2, 1)));
	m_input_key.insert(make_pair<char, pair<int, int>>('c', make_pair<int, int>(2,2)));
}

pair<int,int> human_player::act(map<int, state> & rhs) {
	m_state.print();
	cout << "input your position" << endl;
	char pos_char;
	cin >> pos_char;
	return m_input_key[pos_char];
}



void human_player::set_symbol(int symbol) {
	m_symbol = symbol;
}





human_player::~human_player() {
}


