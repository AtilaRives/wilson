#include "traitement.h"

// Initialisation d'un élément de la structure produit avec une ligne du fichier d'entrée
void initialisationStructure(string ligne, Produit* produitActuel) {

	string delimiter = ";";
	size_t pos = 0;

	//Produit
	pos = ligne.find(delimiter);
	produitActuel->nom = ligne.substr(0, pos);
	ligne.erase(0, pos + delimiter.length());

	//Categorie
	pos = ligne.find(delimiter);
	produitActuel->categorie = ligne.substr(0, pos);
	ligne.erase(0, pos + delimiter.length());

	//Stock_de_depart
	pos = ligne.find(delimiter);
	produitActuel->stockDepart = stoi(ligne.substr(0, pos));
	ligne.erase(0, pos + delimiter.length());

	//Demande_d1
	pos = ligne.find(delimiter);
	produitActuel->demandeMoyenne = stoi(ligne.substr(0, pos));
	ligne.erase(0, pos + delimiter.length());

	//Croissance_par_jour
	pos = ligne.find(delimiter);
	produitActuel->croissanceJournaliere = stof(ligne.substr(0, pos));
	ligne.erase(0, pos + delimiter.length());

	//Mois_de_saisonnalite
	pos = ligne.find(delimiter);
	produitActuel->moisSaisonnalite = stoi(ligne.substr(0, pos));
	ligne.erase(0, pos + delimiter.length());

	//Saisonnalite
	pos = ligne.find(delimiter);
	produitActuel->variationSaisonnalite = stof(ligne.substr(0, pos));
	ligne.erase(0, pos + delimiter.length());

	//Variation_journaliere
	pos = ligne.find(delimiter);
	produitActuel->variationDemandeJournaliere = stoi(ligne.substr(0, pos));
	ligne.erase(0, pos + delimiter.length());

	//Delai_livraison
	pos = ligne.find(delimiter);
	produitActuel->delaiLivraison = stoi(ligne.substr(0, pos));
	ligne.erase(0, pos + delimiter.length());

	//Cout_de_lancement
	pos = ligne.find(delimiter);
	produitActuel->coutLancement = stoi(ligne.substr(0, pos));
	ligne.erase(0, pos + delimiter.length());

	//Taux_de_possession
	pos = ligne.find(delimiter);
	produitActuel->tauxPossession = stof(ligne.substr(0, pos));
	ligne.erase(0, pos + delimiter.length());

	//Prix_d_achat
	pos = ligne.find(delimiter);
	produitActuel->prixAchat = stoi(ligne.substr(0, pos));
	ligne.erase(0, pos + delimiter.length());

	//Pourcentage_perte
	pos = ligne.find(delimiter);
	produitActuel->tauxRupture = stof(ligne.substr(0, pos));
	ligne.erase(0, pos + delimiter.length());
}

// Récupération d'un voisin de l'état actuel
Etat* voisin(const Etat etatActuel, const int variation) {
	Etat* retour = new Etat;

	int alea = rand() % (variation - (-1 * variation)) + (-1 * variation);
	retour->quantiteCommande = etatActuel.quantiteCommande + etatActuel.quantiteCommande * (alea / 100.0);

	alea = rand() % (variation - (-1 * variation)) + (-1 * variation);
	retour->stockAlerte = etatActuel.stockAlerte + etatActuel.stockAlerte * (alea / 100.0);

	return retour;
}

// Evaluation de l'état donné
double evaluation(Produit* produitActuel, const Etat etatActuel) {

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
	int commandes[JOURSOUVRES];
	int nombreCommandes = 0;

	// Coût total
	double coutTotal = 0.0;

	for (int i = 0; i < JOURSOUVRES; i++) {
		int demandeJournaliere = 0;
		double coutRuptureJournaliere = 0.0;
		double coutStockageJournalier = 0.0;
		double rupture = 0.0;
		int livraison = 0;
		int commande = 0;
		int lancement = 0;
		double alea = 0.0;

		// Demande Journalière
		alea = (double)rand() / RAND_MAX;
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
			demandeJournaliere = produitActuel->demandeMoyenne + (int)(alea * (produitActuel->variationDemandeJournaliere * 2 + 1) -
				produitActuel->variationDemandeJournaliere + (produitActuel->croissanceJournaliere * i));
		}
		//

		// Réception journalière
		for (int j = 0; j < JOURSOUVRES; j++) {
			if (commandes[j] == i) {
				stock = stock + etatActuel.quantiteCommande;
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
		if (stockFictif <= etatActuel.stockAlerte) {
			commandes[nombreCommandes] = i + produitActuel->delaiLivraison;
			nombreCommandes++;
			lancement = produitActuel->coutLancement;
			coutLancementTotal = coutLancementTotal + lancement;
			commande = etatActuel.quantiteCommande;
			stockFictif = stockFictif + commande;
		}
		//
	}

	// Cout total
	coutTotal = coutLancementTotal + coutRuptureTotal + coutStockageTotal;
	//

	return coutTotal;
}