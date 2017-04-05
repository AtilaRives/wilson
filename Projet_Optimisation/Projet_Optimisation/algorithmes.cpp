#include "algorithmes.h"

// Recuit simulé
Etat* recuitSimule(Produit* produitActuel) {
	Etat* etatInitial = new Etat;
	etatInitial->quantiteCommande = produitActuel->demandeMoyenne * produitActuel->delaiLivraison;
	etatInitial->stockAlerte = etatInitial->quantiteCommande * 3;
	
	Etat* etatRetour = new Etat;
	etatRetour->quantiteCommande = produitActuel->demandeMoyenne * produitActuel->delaiLivraison;
	etatRetour->stockAlerte = etatRetour->quantiteCommande * 3;

	int temperature = produitActuel->stockDepart * 10;
	int variationTemp = 1;

	int nombreTests = 10;

	float alea_K;
	float bolzman = 0;

	double eval_ancien = evaluation(produitActuel, *etatRetour);
	double pireEval = 0.0;

	do {
		// Choix d'un voisin aléatoirement dans tous les voisins
		vector<Etat>* voisinsTrouves;
		voisinsTrouves = voisins(*etatRetour, 10);
		int random = rand() % voisinsTrouves->size();
		etatRetour = &voisinsTrouves->at(random);
		//

		// Evaluation du voisin trouvé x fois
		pireEval = evaluation(produitActuel, *etatRetour);
		for (int i = 0; i < nombreTests; i++) {
			double evalTest = evaluation(produitActuel, *etatRetour);
			if (evalTest > pireEval) {
				pireEval = evalTest;
			}
		}
		//

		bolzman = (exp(-(eval_ancien - pireEval) / temperature));

		alea_K = (float)rand() / RAND_MAX;

		temperature = temperature - variationTemp;

	} while (bolzman > alea_K && (temperature <= variationTemp));

	cout << produitActuel->nom << " : " << pireEval << endl;

	//si rien n'a été trouvé, renvoyer le "couple de donnée" initial
	if (temperature <= variationTemp) {
		return etatInitial;
	}

	return etatRetour;
}