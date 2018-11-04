#ifndef RANDOM_WALK_H
#define RANDOM_WALK_H


#include<random>
#include<vector>
#include<memory>
#include<sstream>

#include"temporal_difference.h"
#include"montecarlo.h"



class random_walk {
private:
	size_t m_state_num ;//random walk state num, including two terminal state;
	std::unique_ptr<update_alg> m_update_alg;//the update Alg.;
	string m_alg_name;
	size_t m_episode;
	vector<double> m_true_value;
public:

	std::unique_ptr<update_alg> & alg() { return m_update_alg; }
	random_walk(string name,size_t state_num,size_t episode_num) ;
	void run(size_t run_num);
	void record();
};



#endif // !RANDOM_WALK_H
