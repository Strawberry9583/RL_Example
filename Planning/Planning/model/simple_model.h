#include"model_base.h"

class simple_model:public model_base {
public:
	simple_model();
	~simple_model();
	virtual void feed(STATE_TYPE, MAZE_ACTION_TYPE, STATE_TYPE, double);
	virtual SASR_QUADRUPLE sample();
private:

};

