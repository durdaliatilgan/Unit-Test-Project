#ifndef TEMSILCI_HPP
#define TEMSILCI_HPP
#include <iostream>
using namespace std;

class Temsilci {
public:
	int temsilciID;
	string temsilciAdi;
	Temsilci(int = 0, string = "");
};

Temsilci::Temsilci(int id, string ad) {
	temsilciID = id;
	temsilciAdi = ad;
}
#endif
