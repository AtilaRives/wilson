#pragma once

#include "donnees.h"

// Initialisation d'un �l�ment de la structure produit avec une ligne du fichier d'entr�e
// ligne : ligne lue dans le fichier
// produitActuel : produit que l'on va initialiser
void initialisationStructure(string ligne, Produit* produitActuel);

// R�cup�ration d'un voisin de l'�tat actuel
// quantiteCommande : quantite de l'�tat actuel
// stockAlerte : stock alerte de l'�tat actuel
// variation : pourcentage de variation de la quantit� et du stock
// quantiteNouv : quantite du voisin trouv�
// stockNouv : stock du voisin trouv�
Etat* voisin(const Etat etatActuel, const int variation);

// Evaluation de l'�tat donn�
// produitActuel : produit sur lequel on va �valuer l'�tat
// stockAlerte : stock alerte de l'�tat � �valuer
// quantiteCommande : quantite de l'�tat � �valuer
double evaluation(Produit* produitActuel, const Etat etatActuel);