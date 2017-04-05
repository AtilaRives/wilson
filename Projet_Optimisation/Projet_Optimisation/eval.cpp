#include "algorithmes.h"

void main() {
	srand(time(NULL));

	ifstream fichierDonnees;
	fichierDonnees.open("donneesventes.csv", ifstream::in);
	if (fichierDonnees.fail()) {
		cout << "ERREUR" << endl;
	}

	ofstream fichierTabou;
	fichierTabou.open("tabou.csv", ofstream::out | ios::trunc);
	if (fichierTabou.fail()) {
		cout << "ERREUR" << endl;
	}
	fichierTabou << "Produit;Pdc_stock_alerte;Pdc_quantite" << endl;
	fichierTabou.close();

	ofstream fichierRecuit;
	fichierRecuit.open("recuit.csv", ofstream::out | ios::trunc);
	if (fichierRecuit.fail()) {
		cout << "ERREUR" << endl;
	}
	fichierRecuit << "Produit;Pdc_stock_alerte;Pdc_quantite" << endl;
	fichierRecuit.close();

	string ligne;

	getline(fichierDonnees, ligne);

	while (!fichierDonnees.eof()) {
		getline(fichierDonnees, ligne);
		if (ligne != "") {
			Produit test;
			initialisationStructure(ligne, &test);

			Etat etatTest;
			etatTest.nom = test.nom;
			etatTest.quantiteCommande = test.demandeMoyenne * test.delaiLivraison;
			etatTest.stockAlerte = etatTest.quantiteCommande * 3;

			/*
			ofstream fichierTabou;
			fichierTabou.open("tabou.csv", ofstream::app);
			if (fichierTabou.fail()) {
				cout << "ERREUR" << endl;
			}
			
			// Résultat

			fichierTabou.close();
			*/

			ofstream fichierRecuit;
			fichierRecuit.open("recuit.csv", ofstream::app);
			if (fichierRecuit.fail()) {
				cout << "ERREUR" << endl;
			}
			// Résultat
			Etat* resultatRecuit;
			resultatRecuit = recuitSimule(&test);
			fichierRecuit << test.nom << ";" << resultatRecuit->stockAlerte << ";" << resultatRecuit->quantiteCommande << endl;
			//
			fichierRecuit.close();

		}
	}

	fichierDonnees.close();
}