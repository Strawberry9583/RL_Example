#ifndef UPDATE_ALG_H
#define UPDATE_ALG_H

#include<iostream>
#include<string>
#include<sstream>
#include<vector>
#include<random>
#include<time.h>
#include<fstream>
#include<memory>
#include<stdio.h>


using namespace std;


class update_alg {
public:
	update_alg() {}
	virtual ~update_alg() {};
	double alpha()const { return m_alpha; }
	void set_alpha(double alpha) { m_alpha = alpha; }
	vector<double> & value() { return m_value; }
	const vector<double> & value() const { return m_value; }
	vector<double> & reward() { return m_reward;}
	const vector<double>& reward()const { return m_reward; }
	vector<size_t>& trajectory() { return m_trajectory; }
	const vector<size_t> & trajectory()const { return m_trajectory; }
	const string & name()const { return m_name; }
	string & name() { return m_name; }
	void set_batch(bool is_batch) { m_is_batch = is_batch; }
	virtual void update_value() {}// update value for one episode;
	virtual void train() {}//train for optimal value;
	virtual void record() {}//output the value;
protected:
	double m_alpha=0.01;// learning ratio;
	bool m_is_batch=false;// using batch learning or not;
	vector<double> m_value;//the update value;
	vector<size_t> m_trajectory;//the experienced state;
	vector<double> m_reward;
	double m_gamma = 1.0;//the discount ratio;
	string m_name;//the name of the used Alg., such as TD, MC...;
};




#endif // !UPDATE_ALG_H
