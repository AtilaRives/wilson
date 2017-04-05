#include "algorithmes.h"

// Recuit simulé
Etat* recuitSimule(Produit* produitActuel) {
	Etat* etatMeilleur= new Etat;
	etatMeilleur->quantiteCommande = produitActuel->demandeMoyenne * produitActuel->delaiLivraison;
	etatMeilleur->stockAlerte = etatMeilleur->quantiteCommande * 3;
	
	int nombreTests = 10;

	double pireEvalMeilleur = evaluation(produitActuel, *etatMeilleur);
	for (int i = 0; i < nombreTests; i++) {
		double evalTest = evaluation(produitActuel, *etatMeilleur);
		if (evalTest > pireEvalMeilleur) {
			pireEvalMeilleur = evalTest;
		}
	}
	
	Etat* etatRetour = new Etat;
	etatRetour->quantiteCommande = produitActuel->demandeMoyenne * produitActuel->delaiLivraison;
	etatRetour->stockAlerte = etatRetour->quantiteCommande * 2;

	double temperature = etatRetour->quantiteCommande * 3;
	double temperatureMin = 1;
	double variationTemp = 1;

	

	double r = 0.0;
	double bolzman = 0.0;

	// Evaluation du voisin trouvé x fois
	double pireEvalAncien = evaluation(produitActuel, *etatRetour);
	for (int i = 0; i < nombreTests; i++) {
		double evalTest = evaluation(produitActuel, *etatRetour);
		if (evalTest > pireEvalAncien) {
			pireEvalAncien = evalTest;
		}
	}
	//

	double pireEval = 0.0;
	int cpt = 0;

	while (temperature > temperatureMin) {
			// Choix d'un voisin aléatoirement dans tous les voisins
			Etat* nouveauVoisin = voisin(*etatRetour, 5);
			//

			// Evaluation du voisin trouvé x fois
			pireEval = evaluation(produitActuel, *nouveauVoisin);
			for (int i = 0; i < nombreTests; i++) {
				double evalTest = evaluation(produitActuel, *nouveauVoisin);
				if (evalTest > pireEval) {
					pireEval = evalTest;
				}
			}
			//

			r = (double)rand() / RAND_MAX;

			double temp = pireEvalAncien;
			double erreur = pireEvalAncien - pireEval;

			if (erreur > 0) {
				etatRetour = nouveauVoisin;
				pireEvalAncien = pireEval;
				
				if (pireEval < pireEvalMeilleur) {
					etatMeilleur = nouveauVoisin;
					pireEvalMeilleur = pireEval;
				}
			}
			else {
				bolzman = exp(erreur / temperature);
				if (bolzman > r) {
					etatRetour = nouveauVoisin;
					pireEvalAncien = pireEval;
				}
			}
			//cout << " Ancien etat : " << temp << " nouvel etat : " << pireEval << " erreur : " << erreur << " temperature : " << temperature << " bolzman : " << bolzman << endl;
		temperature = temperature - variationTemp;

		cpt++;
	}

	cout << produitActuel->nom << " : " << pireEval << " cpt : " << cpt << endl;

	return etatMeilleur;
}

// Tabou
Etat* tabou(Produit* produitActuel) {
	return NULL;
}