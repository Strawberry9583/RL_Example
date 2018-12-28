#include"simple_model.h"


simple_model::simple_model() :model_base() {

}

simple_model::~simple_model() {

}

void simple_model::feed(STATE_TYPE, MAZE_ACTION_TYPE, STATE_TYPE, double) {
}

SASR_QUADRUPLE simple_model::sample() {
	return SASR_QUADRUPLE();
}
