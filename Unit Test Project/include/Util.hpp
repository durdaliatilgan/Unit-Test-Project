#ifndef UTIL_HPP
#define UTIL_HPP

template<class T>
void swap_t(T& lhs, T& rhs) {
	T temp = lhs;
	lhs = rhs;
	rhs = temp;
}

template<class T>
T min(const T& lhs, const T& rhs) {
	return lhs < rhs ? lhs : rhs;
}

template<class T>
class Less {
public:
	bool operator()(const T& lhs, const T& rhs)const;
};

template<class T>
bool Less<T>::operator()(const T& lhs, const T& rhs)const {
	return lhs < rhs;
}


template<class T>
class Greater {
public:
	bool operator()(const T& lhs, const T& rhs)const;
};

template<class T>
bool Greater<T>::operator()(const T& lhs, const T& rhs)const {
	return lhs > rhs;
}


template<class T>
T min_t(const T& lhs,const T& rhs){
	return lhs  < rhs ? lhs : rhs;
}

#endif
