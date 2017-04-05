#pragma once

#include <iostream>
#include <fstream>
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
#define JOURSOUVRES 261

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
};

typedef struct Etat Etat;
struct Etat {
	string nom;
	int stockAlerte;
	int quantiteCommande;
};