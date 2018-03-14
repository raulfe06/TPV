#include "Observable.h"

Observable::Observable() : observers_() {

}

Observable::~Observable() {
	// TODO Auto-generated destructor stub
}

void Observable::send(Message* msg) {
	for( Observer* o : observers_ ) {
		o->receive(msg);
	}


}

void Observable::registerObserver(Observer* o) {
	observers_.push_back(o);
}

void Observable::removeObserver(Observer * o)
{
	auto it =  observers_.begin();
	while (it != observers_.end() && *it != o) {
		it++;
	}
	if (it != observers_.end()) observers_.erase(it);
}
