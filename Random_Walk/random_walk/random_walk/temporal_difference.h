#ifndef TEMPORAL_ALG_H
#define TEMPORAL_ALG_H

#include<random>
#include<vector>
#include<sstream>
#include<fstream>
#include"update_alg.h"

class temporal_difference :public update_alg{
public:
	temporal_difference();
	temporal_difference(size_t state_num, size_t episode);
	~temporal_difference();
	void train() override;
	void update_value()override;
	void record() override;
private:
	//set random seed;
	std::default_random_engine m_rand_generator;
	std::uniform_real_distribution<double> m_uni_real_rand;
	size_t m_num_state=7;
	size_t m_episode_num=100;//the episode num;
};





#endif // !TEMPORAL_ALG_H


