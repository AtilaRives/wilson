#pragma once

#include "donnees.h"

// Initialisation d'un élément de la structure produit avec une ligne du fichier d'entrée
// ligne : ligne lue dans le fichier
// produitActuel : produit que l'on va initialiser
void initialisationStructure(string ligne, Produit* produitActuel);

// Récupération d'un voisin de l'état actuel
// quantiteCommande : quantite de l'état actuel
// stockAlerte : stock alerte de l'état actuel
// variation : pourcentage de variation de la quantité et du stock
// quantiteNouv : quantite du voisin trouvé
// stockNouv : stock du voisin trouvé
Etat* voisin(const Etat etatActuel, const int variation);

// Evaluation de l'état donné
// produitActuel : produit sur lequel on va évaluer l'état
// stockAlerte : stock alerte de l'état à évaluer
// quantiteCommande : quantite de l'état à évaluer
double evaluation(Produit* produitActuel, const Etat etatActuel);