#ifndef DEFINITION_H
#define DEFINITION_H

#include<tuple>

using namespace std;

enum MAZE_ACTION_TYPE {
	UP, DOWN, LEFT, RIGHT
};

typedef pair<int, int> MAZE_STATE_TYPE;

typedef tuple<MAZE_STATE_TYPE, MAZE_ACTION_TYPE, MAZE_STATE_TYPE, double> SASR_QUADRUPLE;


#endif // !DEFINITION_H

