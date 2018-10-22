#ifndef STATE_H
#define STATE_H


#include<iostream>
#include<map>
#include<vector>
#include<string>
#include<algorithm>
#include<numeric>

using namespace std;

class state
{
public:
	state();
	~state();
	const vector<vector<int> > & data()const { return m_data; }
	vector<vector<int> > & data(){ return m_data; }
	int hash();
	int winner()const { return m_winner; }
	bool is_end();
	state  next_state (int i, int j, int symbol)const;
	void print();
	int hash_value()const { return m_hash_value; }
	int row_num()const { return m_row_num; }
	int col_num()const { return m_column_num; }
private:
	int m_row_num=3;
	int m_column_num=3;
	//the board is represented by an n * n array,
	//1 represents a chessman of the player who moves first,
	//-1 represents a chessman of another player
	// 0 represents an empty position
	vector<vector<int> > m_data;
	int m_winner;
	int m_hash_value;
	bool m_is_end;

};




#endif // !STATE_H


