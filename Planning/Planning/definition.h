
enum MAZE_ACTION_TYPE {
	UP,DOWN,LEFT,RIGHT
};

typedef pair<int, int> STATE_TYPE;

typedef tuple<STATE_TYPE, MAZE_ACTION_TYPE, STATE_TYPE, double> SASR_QUADRUPLE;

