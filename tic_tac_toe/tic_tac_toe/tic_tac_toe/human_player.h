#ifndef HUMAN_PLAYER_H
#define HUMAN_PLAYER_H

#include"player.h"


class human_player: public player   {
public:
	human_player();
	~human_player();

	pair<int, int> act(map<int, state> & rhs);
	void set_symbol(int symbol);
	void set_state(state & rhs) { m_state = rhs; }

private:
	state m_state;
	map<char, pair<int, int> > m_input_key;
	int m_symbol = 1;
};
#endif