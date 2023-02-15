#ifndef GORUSME_HPP
#define GORUSME_HPP
#include "Saat.hpp"

class Gorusme {
public:
	int gorusmeID;
	int musteriID;
	int temsilciID;
	int oncelikPuani;
	int gorusmeSuresi;
	Saat gorBaslama;
	Saat gorBitis;

	bool operator<(const Gorusme&)const ;
	friend ostream& operator<<(ostream&, const Gorusme&);
};

bool Gorusme::operator<(const Gorusme& obj)const {
	return gorusmeSuresi < obj.gorusmeSuresi;
}

ostream& operator<<(ostream& out, const Gorusme& obj) {
	out << obj.gorusmeID << " | " 
		<< obj.musteriID << " | " 
		<< obj.oncelikPuani << " | " 
		<< obj.gorusmeSuresi << " dakika | " 
		<< obj.gorBaslama;
	return out;
}

#endif
