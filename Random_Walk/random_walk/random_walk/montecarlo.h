#ifndef MONTERCARLO
#define MONTERCARLO


#include<sstream>
#include<fstream>
#include<vector>
#include<random>

#include"update_alg.h"

class montecarlo :public update_alg {
public:
	montecarlo();
	montecarlo(size_t state_num, size_t episode);
	~montecarlo();
	void train() override;
	void update_value()override;
	void record() override;
private:
	//set random seed;
	std::default_random_engine m_rand_generator;
	std::uniform_real_distribution<double> m_uni_real_rand;
	size_t m_num_state = 7;
	size_t m_episode_num = 100;//the episode num;
};


#endif // !MONTERCORLO
