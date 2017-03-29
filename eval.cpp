#include <iostream>
#include <string>
#include <vector>

#include <time.h>

#define JANVIER 22
#define FEVRIER 42
#define MARS 64
#define AVRIL 85
#define MAI 108
#define JUIN 129
#define JUILLET 151
#define AOUT 174
#define SEPTEMBRE 194
#define OCTOBRE 217
#define NOVEMBRE 239
#define DECEMBRE 260

using namespace std;

typedef struct Produit Produit;
struct Produit {
	string nom;
	string categorie;

	int stockDepart;

	int demandeMoyenne;
	double croissanceJournaliere;
	int moisSaisonnalite;
	double variationSaisonnalite;
	int variationDemandeJournaliere;

	int delaiLivraison;
	int coutLancement;

	double tauxPossession;
	int prixAchat;
	double tauxRupture;

	int stockAlerte;
	int quantiteCommande;
};

double evaluation(Produit* produitActuel, const int stockAlerte, const int quantiteCommande) {
	int joursOuvres = 261;

	// Stock Départ
	int stock = produitActuel->stockDepart;
	int stockFictif = produitActuel->stockDepart;

	// Coût de lancement total
	double coutLancementTotal = 0.0;

	// Coût de stockage total
	double coutStockageTotal = 0.0;

	// Coût de rupture total
	double coutRuptureTotal = 0.0;

	// Commandes
	int commandes[261];
	int nombreCommandes = 0;

	// Coût total
	double coutTotal = 0.0;

	for (int i = 0; i < joursOuvres; i++) {
		int demandeJournaliere = 0;
		double coutRuptureJournaliere = 0.0;
		double coutStockageJournalier = 0.0;
		double rupture = 0.0;
		int livraison = 0;
		int commande = 0;
		int lancement = 0;
		double alea = 0.0;
		
		// Demande Journalière
			alea = (double) rand() / RAND_MAX;
			if ((i <= JANVIER) && (produitActuel->moisSaisonnalite == 1)) {
				demandeJournaliere = (produitActuel->demandeMoyenne + (int)(alea * (produitActuel->variationDemandeJournaliere * 2 + 1) -
					produitActuel->variationDemandeJournaliere + (produitActuel->croissanceJournaliere * i)) * (1 + produitActuel->variationSaisonnalite));
			}
			else if ((i > JANVIER) && (i <= FEVRIER) && (produitActuel->moisSaisonnalite == 2)) {
				demandeJournaliere = (produitActuel->demandeMoyenne + (int)(alea * (produitActuel->variationDemandeJournaliere * 2 + 1) -
					produitActuel->variationDemandeJournaliere + (produitActuel->croissanceJournaliere * i)) * (1 + produitActuel->variationSaisonnalite));
			}
			else if ((i > FEVRIER) && (i <= MARS) && (produitActuel->moisSaisonnalite == 3)) {
				demandeJournaliere = (produitActuel->demandeMoyenne + (int)(alea * (produitActuel->variationDemandeJournaliere * 2 + 1) -
					produitActuel->variationDemandeJournaliere + (produitActuel->croissanceJournaliere * i)) * (1 + produitActuel->variationSaisonnalite));
			}
			else if ((i > MARS) && (i <= AVRIL) && (produitActuel->moisSaisonnalite == 4)) {
				demandeJournaliere = (produitActuel->demandeMoyenne + (int)(alea * (produitActuel->variationDemandeJournaliere * 2 + 1) -
					produitActuel->variationDemandeJournaliere + (produitActuel->croissanceJournaliere * i)) * (1 + produitActuel->variationSaisonnalite));
			}
			else if ((i > AVRIL) && (i <= MAI) && (produitActuel->moisSaisonnalite == 5)) {
				demandeJournaliere = (produitActuel->demandeMoyenne + (int)(alea * (produitActuel->variationDemandeJournaliere * 2 + 1) -
					produitActuel->variationDemandeJournaliere + (produitActuel->croissanceJournaliere * i)) * (1 + produitActuel->variationSaisonnalite));
			}
			else if ((i > MAI) && (i <= JUIN) && (produitActuel->moisSaisonnalite == 6)) {
				demandeJournaliere = (produitActuel->demandeMoyenne + (int)(alea * (produitActuel->variationDemandeJournaliere * 2 + 1) -
					produitActuel->variationDemandeJournaliere + (produitActuel->croissanceJournaliere * i)) * (1 + produitActuel->variationSaisonnalite));
			}
			else if ((i > JUIN) && (i <= JUILLET) && (produitActuel->moisSaisonnalite == 7)) {
				demandeJournaliere = (produitActuel->demandeMoyenne + (int)(alea * (produitActuel->variationDemandeJournaliere * 2 + 1) -
					produitActuel->variationDemandeJournaliere + (produitActuel->croissanceJournaliere * i)) * (1 + produitActuel->variationSaisonnalite));
			}
			else if ((i > JUILLET) && (i <= AOUT) && (produitActuel->moisSaisonnalite == 8)) {
				demandeJournaliere = (produitActuel->demandeMoyenne + (int)(alea * (produitActuel->variationDemandeJournaliere * 2 + 1) -
					produitActuel->variationDemandeJournaliere + (produitActuel->croissanceJournaliere * i)) * (1 + produitActuel->variationSaisonnalite));
			}
			else if ((i > AOUT) && (i <= SEPTEMBRE) && (produitActuel->moisSaisonnalite == 9)) {
				demandeJournaliere = (produitActuel->demandeMoyenne + (int)(alea * (produitActuel->variationDemandeJournaliere * 2 + 1) -
					produitActuel->variationDemandeJournaliere + (produitActuel->croissanceJournaliere * i)) * (1 + produitActuel->variationSaisonnalite));
			}
			else if ((i > SEPTEMBRE) && (i <= OCTOBRE) && (produitActuel->moisSaisonnalite == 10)) {
				demandeJournaliere = (produitActuel->demandeMoyenne + (int)(alea * (produitActuel->variationDemandeJournaliere * 2 + 1) -
					produitActuel->variationDemandeJournaliere + (produitActuel->croissanceJournaliere * i)) * (1 + produitActuel->variationSaisonnalite));
			}
			else if ((i > OCTOBRE) && (i <= NOVEMBRE) && (produitActuel->moisSaisonnalite == 11)) {
				demandeJournaliere = (produitActuel->demandeMoyenne + (int)(alea * (produitActuel->variationDemandeJournaliere * 2 + 1) -
					produitActuel->variationDemandeJournaliere + (produitActuel->croissanceJournaliere * i)) * (1 + produitActuel->variationSaisonnalite));
			}
			else if ((i > NOVEMBRE) && (i <= DECEMBRE) && (produitActuel->moisSaisonnalite == 12)) {
				demandeJournaliere = (produitActuel->demandeMoyenne + (int)(alea * (produitActuel->variationDemandeJournaliere * 2 + 1) -
					produitActuel->variationDemandeJournaliere + (produitActuel->croissanceJournaliere * i)) * (1 + produitActuel->variationSaisonnalite));
			}
			else {
				demandeJournaliere = produitActuel->demandeMoyenne + (int) (alea * (produitActuel->variationDemandeJournaliere * 2 + 1) - 
					produitActuel->variationDemandeJournaliere + (produitActuel->croissanceJournaliere * i));
			}
		//
		
		// Réception journalière
			for (int j = 0; j < 261; j++) {
				if (commandes[j] == i) {
					stock = stock + quantiteCommande;
				}
			}
		//

		// Demandes dans le stock
			if ((stock - demandeJournaliere) <= 0) {
				stockFictif = stockFictif - stock;
				rupture = stock - demandeJournaliere;
				stock = 0;
			}
			else {
				stock -= demandeJournaliere;
				stockFictif -= demandeJournaliere;
				rupture = 0;
			}
		//

		// Cout de rupture de stock
			if (rupture != 0) {
				coutRuptureJournaliere = (rupture * produitActuel->prixAchat * produitActuel->tauxRupture) * (-1);
				coutRuptureTotal = coutRuptureTotal + coutRuptureJournaliere;
			}
		// Cout de stockage journalier
			else {
				if ((i % 5) == 4) {
					coutStockageTotal = coutStockageTotal + ((stock * produitActuel->prixAchat * produitActuel->tauxPossession) / 365) * 3;
				}
				else {
					coutStockageTotal = coutStockageTotal + ((stock * produitActuel->prixAchat * produitActuel->tauxPossession) / 365);
				}
			}
		//

		// Commande journalière
			if (stockFictif <= stockAlerte) {
				commandes[nombreCommandes] = i + produitActuel->delaiLivraison ;
				nombreCommandes++;
				lancement = produitActuel->coutLancement;
				coutLancementTotal = coutLancementTotal + lancement;
				commande = quantiteCommande;
				stockFictif = stockFictif + commande;
			}
		//
	}

	// Cout total
		coutTotal = coutLancementTotal + coutRuptureTotal + coutStockageTotal;
	//
	
	return coutTotal;
}

void main() {
	
	Produit test;

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

	srand(time(NULL));

	for (int i = 0; i < 11; i++) {
		cout << "Cout total : " << evaluation(&test, 2980, 1460) << endl;
	}
}