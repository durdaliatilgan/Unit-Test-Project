#ifndef HEPSI_HARRANDA_HPP
#define HEPSI_HARRANDA_HPP
#include <fstream>
#include <sstream>
#include "Musteri.hpp"
#include "Temsilci.hpp"
#include "Queue.hpp"
#include "Heap.hpp"
#include "Gorusme.hpp"
#include "AVL.hpp"

class HepsiHarranda {
	List<Temsilci> temsilciler;
	Queue<Temsilci> temsilciQueue;
	MaxHeap<Musteri> cyss;
	AVL<Gorusme> gorusmeler;
	List<Gorusme> devamEdenGorusmeler;
	int gorusme_identifier;

	void musteriKayitEkle(const Musteri& musteri) ;
	Musteri siradakiMusteriyiGetir();
	int gorusmeSuresiHesapla(const Musteri& musteri);
	
	
	void gorusmeYap(const Saat& saat);

public:
	HepsiHarranda() ;
	Temsilci getTemsilci(int id) ;
	Temsilci siradakiTemsilciGetir();
	void temsilciEkle(const Temsilci& temsilci) ;
	void musterileriDosyadanOku(const string& file);
	void simulate();
	void gorusmeListele();
};

void HepsiHarranda::musteriKayitEkle(const Musteri& musteri) {
	cyss.enqueue(musteri);
}

Musteri HepsiHarranda::siradakiMusteriyiGetir() {
	return cyss.dequeue();
}

int HepsiHarranda::gorusmeSuresiHesapla(const Musteri& musteri) {
	int gorusmeSuresi = 0;
	switch (musteri.islemTuru) {
		case 1:
			gorusmeSuresi += 3;
			break;
		case 2:
			gorusmeSuresi += 8;
			break;
		case 3:
			gorusmeSuresi += 7;
			break;
		case 4:
			gorusmeSuresi += 6;
			break;
		case 5:
			gorusmeSuresi += 4;
			break;
	}

	int oncelikPuani = musteri.oncelikPuaniHesapla();
	if (oncelikPuani >= 40)
		gorusmeSuresi += 5;
	else if (oncelikPuani >= 15)
		gorusmeSuresi += 3;
	return gorusmeSuresi;
}

Temsilci HepsiHarranda::getTemsilci(int id) {
	Node<Temsilci>* temp = temsilciler.begin();
	while (temp) {
		if (temp->data.temsilciID == id)
			return temp->data;
		temp = temp->next;
	}
	return Temsilci(-1,"");
}

Temsilci HepsiHarranda::siradakiTemsilciGetir() {
	Temsilci temsilci = temsilciQueue.front();
	temsilciQueue.dequeue();
	return temsilci;
}


void HepsiHarranda::gorusmeYap(const Saat& saat) {
	Temsilci temsilci = siradakiTemsilciGetir();
	Musteri musteri = siradakiMusteriyiGetir();
	Gorusme gorusme;
	gorusme.gorusmeID = gorusme_identifier++;
	gorusme.temsilciID = temsilci.temsilciID;
	gorusme.musteriID = musteri.musteriID;
	gorusme.oncelikPuani = musteri.oncelikPuaniHesapla();
	gorusme.gorBaslama = saat;
	gorusme.gorusmeSuresi = gorusmeSuresiHesapla(musteri);
	gorusme.gorBitis = saat + gorusme.gorusmeSuresi * 60;
	devamEdenGorusmeler.push_back(gorusme);
}


HepsiHarranda::HepsiHarranda() {
	gorusme_identifier = 1;
}

void HepsiHarranda::temsilciEkle(const Temsilci& temsilci) {
	temsilciler.push_back(temsilci);
	temsilciQueue.enqueue(temsilci);
}
	
void HepsiHarranda::musterileriDosyadanOku(const string& file) {
	fstream f(file.c_str(),ios::in);
	string line;
	Musteri musteri;
	while (getline(f,line)) {
		stringstream ss;
		int index = line.find(",");
		musteri.musteriID = std::stoi(line.substr(0, index));
		line.erase(0, index + 1);
		index = line.find(",");
		musteri.musteriAdi = line.substr(0, index);
		line.erase(0, index + 1);
		while ((index = line.find(",")) != string::npos) {
			ss << line.substr(0, index) << " ";
			line.erase(0, index + 1);
		}
		ss << line;
		ss >> musteri.uyelikDurumu >> musteri.cuzdanDurumu >> musteri.aylikHarcama >> musteri.yorumSayisi >> musteri.urunCesidi >> musteri.islemTuru;
		musteriKayitEkle(musteri);
	}

}

void HepsiHarranda::simulate() {
	Saat saat(9,0,0);
	int saatDegisimi = 1;
	while (!cyss.isEmpty() || !devamEdenGorusmeler.isEmpty()) {
		Node<Gorusme>* temp = devamEdenGorusmeler.begin();
		while (temp) {
			if (temp->data.gorBitis.toplamSaniye() == saat.toplamSaniye()) {
				Gorusme gorusme = temp->data;
				gorusmeler.insert(gorusme);
				temsilciQueue.enqueue(getTemsilci(gorusme.temsilciID));
				temp = devamEdenGorusmeler.erase(temp);
			}
			else
				temp = temp->next;
		}
		
		while (!cyss.isEmpty() && !temsilciQueue.isEmpty()) {
			gorusmeYap(saat);
		}
		saat += saatDegisimi;
	}
}

void HepsiHarranda::gorusmeListele() {
	gorusmeler.inorder();
}
#endif
