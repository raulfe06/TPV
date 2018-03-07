#ifndef SRC_OMANAGER_H_
#define SRC_OMANAGER_H_

#include <vector>

/*
 *
 */
template<typename T>
class OManager {
public:
	OManager() :
			objs_() {
	}
	virtual ~OManager() {
		for( T* o : objs_ ) {
			delete o;
		}
	}
	T* getObject();
	virtual void initializeObject(T* o) = 0;
protected:
	std::vector<T*> objs_;
};

template<typename T>
inline T* OManager<T>::getObject() {
	typename std::vector<T*>::iterator it = objs_.begin();
	while ( it != objs_.end() && (*it)->isActive() ) {
		it++;
	}

	T* a = nullptr;
	if ( it == objs_.end() ) {
		a = new T();
		initializeObject(a);
		objs_.push_back(a);
	} else {
		a = *it;
	}

	return a;

}

#endif /* SRC_OMANAGER_H_ */
