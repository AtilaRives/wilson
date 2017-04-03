#include "initialisation_wilson.h"

/* non definie
 *
 */





int main()
{
    cout << "Hello world!" << endl;


    /** Variables
    */
    string buffer_de_ligne;
    int i_cpt_nb_ligne =0;
   // int i_nombre_donnes=0;

    ifstream fichier_donees("c:\\Users\\atila\\Documents\\donneesventes.csv", ios::in);  // on ouvre le fichier en lecture

    if(!fichier_donees)
    {
        cerr << "Impossible d'ouvrir le fichier de données !" << endl;
    }


    //lire le nombres d'elements
    while(getline(fichier_donees, buffer_de_ligne))
    {
        i_cpt_nb_ligne++;
    }
    //creation du tableau d'elements
    Produit tab_produits[i_cpt_nb_ligne]; //on nb_ligne-1 élèments (la 1er ligne n'est pas un produit)

    //retour au debut du fichier
    fichier_donees.clear();
    fichier_donees.seekg(0,std::ios::beg);

    //parser les elements
    i_cpt_nb_ligne=0;
    //on saute la premiere ligne
    getline(fichier_donees, buffer_de_ligne);

    //on remplit nos structures
    while(getline(fichier_donees, buffer_de_ligne))
    {
        fnc_remplir_une_structure(buffer_de_ligne, &tab_produits[i_cpt_nb_ligne]);
        i_cpt_nb_ligne++;
    }
    //fermer le fichier
        fichier_donees.close();

    //innitialiser le couple de données dans le tableau
    for(int i = 0; i < i_cpt_nb_ligne - 1; i++){
        innitialisation_un_produit_quantite_stock_alerte(&tab_produits[i]);

    }

//    for (int i= 0; i<NB_PRODUITS;i++)
//    {
//        afficher_un_produits( &tab_produits[i]);
//    }


    //generer recuit
    float *temperature;
    temperature = new float;
    *temperature = TEMPERATURE_INNITIALE;


    for(int i = 0; i<NB_PRODUITS ; i++)
    {
        cout << " dans la boucle de generation" <<endl;
        (*temperature)=TEMPERATURE_INNITIALE;
        generer_le_recuit(&tab_produits[i], temperature, TEMPERATURE_VARIATION);
    }
    for (int i= 0; i<NB_PRODUITS;i++)
    {
        afficher_un_produits( &tab_produits[i]);
    }


    //ecrire fichier resultat


    //tableau de structure


    cout << "Goodbey world!" << endl;
    return 0;
}
