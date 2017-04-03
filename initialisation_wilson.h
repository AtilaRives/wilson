#ifndef INITIALISATION_WILSON_H_INCLUDED
#define INITIALISATION_WILSON_H_INCLUDED


/** Includes
*/
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>



using namespace std;


#define url_resultat_tabou  "%userprofile%\\Documents\\resultat_tabou.txt"
#define url_resultat_recuit  "%userprofile%\\Documents\\resultat_recuit.txt"
#define url_resultat_mixte  "%userprofile%\\Documents\\resultat_mixte.txt"
#define url_donnees "%userprofile%\\Documents\\donneesventes.csv"

#define NB_PRODUITS 160
#define TEMPERATURE_INNITIALE 500
#define TEMPERATURE_VARIATION 0.5
#define TEMPERATURE_ARRET 0.1
#define TAILLE_TAB_SOLUTION 3


/*
Produit;Categorie;Stock_de_depart;Demande_d1;Croissance_par_jour;Mois_de_saisonnalite;
Saisonnalite;Variation_journaliere;
Delai_livraison;Cout_de_lancement;Taux_de_possession;Prix_d_achat;Pourcentage_perte
C001;C;4081;341;1;7;-0,19;9;5;276;0,2;3;0,5
*/
typedef struct Produit Produit;
struct Produit {
    string nom;
    string categorie;

    int stockDepart;

    float demandeMoyenne;
    float croissanceJournaliere;
    int moisSaisonnalite;
    float variationSaisonnalite;
    int variationDemandeJournaliere;

    int delaiLivraison;
    int coutLancement;

    float tauxPossession;
    int prixAchat;
    float tauxRupture;

    int stockAlerte;
    int quantiteCommande;
};


Produit successeurRecuit(Produit *adr_produit, float *temperature, float variation_temperature);
void fnc_remplir_une_structure(string la_ligne, Produit *adr_produit);
void ecrire_un_fichier (Produit tab_produit[],  ofstream &fichier);
double evaluation(Produit* produitActuel, const int stockAlerte, const int quantiteCommande);
void innitialisation_un_produit_quantite_stock_alerte(Produit *le_produit);

void generer_le_mixte(Produit *ptr_produit, float *temperature, float variation_temperature);
void generer_le_recuit(Produit *ptr_produit, float *temperature, float variation_temperature);
void generer_le_tabou (Produit *ptr_produit);

Produit choix_du_meilleur_voisin(Produit *tab_options);


void afficher_un_produits( Produit *a_afficher);


#endif // INITIALISATION_WILSON_H_INCLUDED
