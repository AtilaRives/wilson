#include "algorithmes.h"

void main() {
	srand(time(NULL));

	ifstream fichierDonnees;

	Produit test;

	/*
	test.demandeMoyenne = 341;
	test.variationDemandeJournaliere = 9;
	test.croissanceJournaliere = 1;
	test.moisSaisonnalite = 7;
	test.variationSaisonnalite = -0.19;
	test.stockDepart = 4081;
	test.coutLancement = 276;
	test.prixAchat = 3;
	test.delaiLivraison = 5;
	test.tauxPossession = 0.2;
	test.tauxRupture = 0.5;
	*/
	
	test.demandeMoyenne = 300;
	test.variationDemandeJournaliere = 50;
	test.croissanceJournaliere = 0;
	test.moisSaisonnalite = 12;
	test.variationSaisonnalite = 0.50;
	test.stockDepart = 5573;
	test.coutLancement = 600;
	test.prixAchat = 60;
	test.delaiLivraison = 10;
	test.tauxPossession = 0.15;
	test.tauxRupture = 0.5;
	

	Etat etatTest;
	etatTest.quantiteCommande = test.demandeMoyenne * test.delaiLivraison;
	etatTest.stockAlerte = etatTest.quantiteCommande * 3;

	cout << "Etat initial : " << etatTest.quantiteCommande << "    " << etatTest.stockAlerte << endl;

	//etatTest.quantiteCommande = 3000;
	//etatTest.stockAlerte = 5000;

	for (int i = 0; i < 11; i++) {	
		cout << "Cout total : " << evaluation(&test, etatTest) << endl;
	}

	Etat* affiche;
	affiche = recuitSimule(&test);
	cout << "Quantite " << affiche->quantiteCommande << endl;
	cout << "Stock alerte " << affiche->stockAlerte << endl;

	/*
	vector<Etat>* voisinsTrouves;
	voisinsTrouves = voisins(etatTest, 3);

	cout << "Voisins : " << voisinsTrouves->size() << endl;

	for (int i = 0; i < voisinsTrouves->size(); i++) {
		Etat temp = voisinsTrouves->at(i);
		cout << "	Voisin " << i << " : " << endl
			<< "			Quantite : " << temp.quantiteCommande
			<< "			Stock : " << temp.stockAlerte << endl <<endl;
	}
	*/
}