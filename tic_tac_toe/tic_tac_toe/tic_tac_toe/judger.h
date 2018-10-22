#ifndef JUDGER_H
#define JUDGER_H

#include"human_player.h"


class judger {
public:
	judger(const human_player & human, const player & p2, map<int, state> & all_states);
	judger(const player & p1,const player & p2, map<int,state> & all_states);
	~judger();
	void reset();// reset for next round training;
	int play(map<int,state> & rhs);//return the winner of a game;
	void backup(player & p1, player & p2);
	void save_policy();
	int game(map<int,state> & rhs);
private:
	human_player m_human;
	player m_player1;
	player m_player2;
	int m_current_player;// symbol 1: player1, firstly; symbol -1: player2, secondly;
	int m_p1_symbol=1;
	int m_p2_symbol = -1;
	state m_current_state;
};



#endif // !JUDGER_H
