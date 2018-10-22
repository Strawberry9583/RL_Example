#include"global.h"



void global::get_all_state() {
	state sta;
	int symbol = 1;
	m_all_states.emplace(std::make_pair(sta.hash(), sta));
	dfs_state(sta, symbol);
}

void global::train(int epochs) {
	player player1(0.1,0.1);
	player player2(0.1,0.1);
	judger jdg(player1, player2,m_all_states);
	double player1_win = 0.0;
	double player2_win = 0.0;
	double player_tie = 0.0;
	for (int i = 1; i < epochs+1; ++i) {
		int winner = jdg.play(m_all_states);
		if (jdg.play(m_all_states) == 1) {
			player1_win += 1.0;
		}
		else if(winner==-1) {
			player2_win += 1.0;
		}
		else if (winner == 0) {
			player_tie += 1.0;
		}
		cout <<"epochs:  "<<i<< "   player1:  " << player1_win / double(i) << "   " << "player2:  " << player2_win / double(i) <<"  tie: "<<player_tie/(double)i<< endl;
		jdg.backup(player1, player2);
		//player1.backup();
		//player2.backup();

		jdg.reset();

	}
	jdg.save_policy();
}

void global::dfs_state( state & current_sta,int symbol) {
	for (int i = 0; i < m_row_num; ++i) {
		for (int j = 0; j < m_column_num; ++j) {
			if (current_sta.data()[i][j] == 0) {
				state next_sta = current_sta.next_state(i, j, symbol);
				if (m_all_states.find(next_sta.hash())==m_all_states.end()) {
					m_all_states.insert(std::make_pair(next_sta.hash(), next_sta));
					if (!next_sta.is_end()) {
						dfs_state(next_sta, -symbol);
					}
					else {
						return;
					}
					
				}
			}

		}
	}
}


void global::game() {
	while (1) {
		human_player player1;
		player player2(0, 0);
		player2.load_policy();
		judger jdg(player1, player2,m_all_states);	
		int winner = jdg.game(m_all_states);
		if (winner == 1) {
			cout << "You win" << endl;
		}
		else {
			cout << "You lose" << endl;
		}

	}
}
