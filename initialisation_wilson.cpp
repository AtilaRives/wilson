#include "initialisation_wilson.h"

// pas declarer

double evaluation(Produit* produitActuel, const int stockAlerte, const int quantiteCommande){
    produitActuel->quantiteCommande = stockAlerte;
    produitActuel->quantiteCommande = quantiteCommande;
    return 0;
}

Produit successeurTabou (Produit *truc){
    Produit plop = *truc;
    return plop;
}













//---------------------------------------------------------------------------------------


Produit tabTabou[NB_PRODUITS];
Produit tabRecuits[NB_PRODUITS];


void fnc_remplir_une_structure(string la_ligne, Produit *adr_produit){

    istringstream ligne_a_parser(la_ligne);
    string delimiter = ";";
    size_t pos = 0;


    //Produit
    pos = la_ligne.find(delimiter);
    adr_produit->nom=la_ligne.substr(0, pos);
    la_ligne.erase(0, pos + delimiter.length());

    //Categorie
    pos = la_ligne.find(delimiter);
    adr_produit->categorie=la_ligne.substr(0, pos);
    la_ligne.erase(0, pos + delimiter.length());

    //Stock_de_depart
    pos = la_ligne.find(delimiter);
    adr_produit->stockDepart = stoi(la_ligne.substr(0, pos));
    la_ligne.erase(0, pos + delimiter.length());


    //Demande_d1
    pos = la_ligne.find(delimiter);
    adr_produit->demandeMoyenne=stof(la_ligne.substr(0, pos));
    la_ligne.erase(0, pos + delimiter.length());

    //Croissance_par_jour
    pos = la_ligne.find(delimiter);
    adr_produit->croissanceJournaliere=stof(la_ligne.substr(0, pos));
    la_ligne.erase(0, pos + delimiter.length());

    //Mois_de_saisonnalite
    pos = la_ligne.find(delimiter);
    adr_produit->moisSaisonnalite=stoi(la_ligne.substr(0, pos));
    la_ligne.erase(0, pos + delimiter.length());

    //Saisonnalite
    pos = la_ligne.find(delimiter);
    adr_produit->variationSaisonnalite=stof(la_ligne.substr(0, pos));
    la_ligne.erase(0, pos + delimiter.length());

    //Variation_journaliere
    pos = la_ligne.find(delimiter);
    adr_produit->variationDemandeJournaliere=stoi(la_ligne.substr(0, pos));
    la_ligne.erase(0, pos + delimiter.length());

    //Delai_livraison
    pos = la_ligne.find(delimiter);
    adr_produit->delaiLivraison=stoi(la_ligne.substr(0, pos));
    la_ligne.erase(0, pos + delimiter.length());

    //Cout_de_lancement
    pos = la_ligne.find(delimiter);
    adr_produit->coutLancement=stoi(la_ligne.substr(0, pos));
    la_ligne.erase(0, pos + delimiter.length());

    //Taux_de_possession
    pos = la_ligne.find(delimiter);
    adr_produit->tauxPossession=stof(la_ligne.substr(0, pos));
    la_ligne.erase(0, pos + delimiter.length());

    //Prix_d_achat
    pos = la_ligne.find(delimiter);
    adr_produit->prixAchat=stoi(la_ligne.substr(0, pos));
    la_ligne.erase(0, pos + delimiter.length());

    //Pourcentage_perte
    pos = la_ligne.find(delimiter);
    adr_produit->tauxRupture=stof(la_ligne.substr(0, pos));
    la_ligne.erase(0, pos + delimiter.length());


}

void innitialisation_un_produit_quantite_stock_alerte(Produit *le_produit)
{
    le_produit->quantiteCommande = ceil(le_produit->demandeMoyenne * le_produit->delaiLivraison);
    le_produit->stockAlerte = le_produit->quantiteCommande*3;
}

void ecrire_un_fichier (Produit tab_produit[],  ofstream &fichier){

    fichier << "Produit;Pdc_stock_alerte;pdc_quantite" << endl;
    for(int i = 0 ; i< NB_PRODUITS-1; i++)
    {
        fichier << tab_produit[i].nom << ";"<< tab_produit[i].stockAlerte << ";" << tab_produit[i].quantiteCommande << endl;
    }
    fichier.close();
}



Produit successeurRecuit(Produit *adr_produit, float *temperature, float variation_temperature)
{
    Produit candidat = *adr_produit;
    //calcul du candidat recuit
    srand(time(NULL));
    int alea =rand() % 15 -15;
    float alea_K = (float) rand() / RAND_MAX;
    float bolzman = 0;

    candidat.quantiteCommande = adr_produit->quantiteCommande;
    candidat.stockAlerte = adr_produit->stockAlerte;

    double eval_ancien = evaluation(adr_produit, (const) adr_produit->quantiteCommande, (const) adr_produit->stockAlerte);
    double eval_candidat = 0;

    do
    {
        candidat.quantiteCommande = (adr_produit->quantiteCommande + adr_produit->quantiteCommande/100*alea);
        candidat.stockAlerte = (adr_produit->stockAlerte + adr_produit->stockAlerte/100*alea);

        eval_candidat = evaluation(adr_produit, (const) candidat.quantiteCommande, (const) candidat.stockAlerte);

        bolzman = ( exp (-(eval_ancien-eval_candidat) / *temperature) );

        alea =rand() % 15 -15;
        alea_K = (float) rand() / RAND_MAX;

        (*temperature) -= (*temperature) -variation_temperature;
        //(*temperature) =- (*temperature) * variation_temperature;




    }while(bolzman>alea_K && ( (*temperature)<TEMPERATURE_ARRET)) ;

    //si rien n'a été trouvé, renvoyer le "couple de donnée" innitial
    if( (*temperature)<TEMPERATURE_ARRET){
        return (*adr_produit);
    }

    return candidat;
}


// ecrit le fichier "tabou" "mixte" "recuit" en fonction d'un tableau de données
void ecrire_resultat(Produit *tab_produit, const string mixte_recuit_tabou){

    if(mixte_recuit_tabou == "tabou"){
        ofstream fichier_tabou(url_resultat_tabou, ios::out | ios::trunc);
        if(!fichier_tabou){
            printf("Erreur à la creation du fichier tabou");
            exit(-2);
        }
        ecrire_un_fichier(tab_produit , fichier_tabou);
    }
    else if (mixte_recuit_tabou == "recuit")
    {
        ofstream fichier_recuit(url_resultat_tabou, ios::out | ios::trunc);
        if(!fichier_recuit){
            printf("Erreur à la creation du fichier tabou");
            exit(-2);
        }
        ecrire_un_fichier(tab_produit , fichier_recuit);

    }else if(mixte_recuit_tabou == "mixte")
    {
        ofstream fichier_mixte(url_resultat_tabou, ios::out | ios::trunc);
        if(!fichier_mixte){
            printf("Erreur à la creation du fichier tabou");
            exit(-2);
        }
        ecrire_un_fichier(tab_produit , fichier_mixte);
    }else
    {
        printf("Probleme de choix");
        exit(-2);
    }
}



void generer_resultat(Produit *tab_produit, const string mixte_recuit_tabou){

    float *temperature(0);
    temperature = new float;


    if(mixte_recuit_tabou == "tabou")
    {
        for(int i = 0; i<NB_PRODUITS ; i++)
        {
            generer_le_tabou(&tab_produit[i]);
        }
        ecrire_resultat(tab_produit, "tabou");

    }else if (mixte_recuit_tabou == "recuit")
    {
        for(int i = 0; i<NB_PRODUITS ; i++)
        {

            generer_le_recuit(&tab_produit[i], temperature, TEMPERATURE_ARRET);
        }
        ecrire_resultat(tab_produit, "recuit");

    }else if(mixte_recuit_tabou == "mixte")
    {
        for(int i = 0; i<NB_PRODUITS ; i++)
        {
            (*temperature)=TEMPERATURE_INNITIALE;
             generer_le_mixte(&tab_produit[i], temperature, TEMPERATURE_ARRET);
        }
        ecrire_resultat(tab_produit, "mixte");
    }else
    {
        cout << "Ereur dans le choix du generer resultat" << endl;
        exit(-4);
    }
}

void generer_le_tabou (Produit *ptr_produit)
{
       ptr_produit->nom = "warning";
}



void generer_le_mixte(Produit *ptr_produit, float *temperature, float variation_temperature)
{
    Produit tab_choix_voisins_recuits[TAILLE_TAB_SOLUTION];
    Produit tab_choix_voisins_tabou[TAILLE_TAB_SOLUTION];
    int i = 0;

    while (i<TAILLE_TAB_SOLUTION)
    {
        tab_choix_voisins_recuits[i] = successeurRecuit(ptr_produit, temperature, variation_temperature);
        tab_choix_voisins_tabou[i] = successeurTabou(ptr_produit);
    }

    *temperature = (float) TEMPERATURE_INNITIALE;
    Produit le_tabou = choix_du_meilleur_voisin(tab_choix_voisins_tabou);
    Produit le_recuit = choix_du_meilleur_voisin(tab_choix_voisins_recuits);

    if (evaluation(&le_tabou, le_tabou.stockAlerte, le_tabou.quantiteCommande > evaluation(&le_recuit, le_recuit.stockAlerte, le_recuit.quantiteCommande)))
    {
        *ptr_produit = le_tabou;
    }else
    {
         *ptr_produit = le_recuit;
    }
}


void generer_le_recuit(Produit *ptr_produit, float *temperature, float variation_temperature)
{
    Produit tab_choix_voisins_recuits[TAILLE_TAB_SOLUTION];
    int i = 0;

    while (i<TAILLE_TAB_SOLUTION)
    {
        tab_choix_voisins_recuits[i] = successeurRecuit(ptr_produit, temperature, variation_temperature);
    }

    *ptr_produit = choix_du_meilleur_voisin(tab_choix_voisins_recuits);
}

//tab_options et le tableau des potentiel voisin
Produit choix_du_meilleur_voisin(Produit *tab_options)
{
    Produit notre_choix = tab_options[0];


    double eval = evaluation(&tab_options[0], (const) tab_options[0].stockAlerte, (const) tab_options[0].quantiteCommande );

    for(int i = 1; i < TAILLE_TAB_SOLUTION-1 ; i++ ){
        if(eval < (evaluation(&notre_choix, (const) tab_options[i].stockAlerte, (const) tab_options[i].quantiteCommande ) ) )
        {
            eval =   (evaluation(&notre_choix, (const) tab_options[i].stockAlerte, (const) tab_options[i].quantiteCommande ) );
            notre_choix = tab_options[i];
        }
    }

    return notre_choix;
}





