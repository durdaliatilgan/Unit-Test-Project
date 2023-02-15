#ifndef MUSTERI_HPP
#define MUSTERI_HPP
#include <iostream>
using namespace std;
class Musteri {
public:
	int musteriID;
	string musteriAdi;
	bool uyelikDurumu;
	bool cuzdanDurumu;
	int aylikHarcama;
	int yorumSayisi;
	int urunCesidi;
	int islemTuru;

	int oncelikPuaniHesapla()const;
	bool operator>(const Musteri& obj)const;
};

int Musteri::oncelikPuaniHesapla()const {
	int oncelikPuani = 0;

	if (uyelikDurumu)
		oncelikPuani += 10;

	if (cuzdanDurumu)
		oncelikPuani += 15;

	if (aylikHarcama >= 4000)
		oncelikPuani += 15;
	else if (aylikHarcama >= 1000)
		oncelikPuani += 10;
	else if (aylikHarcama >= 100)
		oncelikPuani += 5;

	if (yorumSayisi >= 8)
		oncelikPuani += 10;
	else if (yorumSayisi >= 2)
		oncelikPuani += 5;

	if (urunCesidi >= 10)
		oncelikPuani += 15;
	else if (urunCesidi >= 6)
		oncelikPuani += 10;
	else if (urunCesidi >= 2)
		oncelikPuani += 5;

	return oncelikPuani;
}

bool Musteri::operator>(const Musteri& obj)const { 
	return oncelikPuaniHesapla() > obj.oncelikPuaniHesapla();
}
#endif
