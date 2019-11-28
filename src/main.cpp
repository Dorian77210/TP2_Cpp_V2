/*************************************************************************
                            main  -  description
                              --------------------
   début                : 03/10/2019
   copyright            : (C) 2019 par Aleryc SERRANIA et Kesly GASSANT
*************************************************************************/

//---------- Réalisation du module <main> (fichier main.cpp) -----

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système

#include <iostream>
#include <cstring>
using namespace std;

//------------------------------------------------------ Include personnel
#include "../includes/Catalogue.h"
#include "../includes/TrajetSimple.h"
#include "../includes/TrajetCompose.h"

///////////////////////////////////////////////////////////////////  PRIVE

//------------------------------------------------------------- Constantes
const unsigned int TAILLE_MAX_VILLE = 50;

//------------------------------------------------------------------ Types

//---------------------------------------------------- Variables statiques

//------------------------------------------------------ Fonctions privées
static void afficherMoyenDeTransport (
    moyenDeTransport leMoyenDeTransport )
{
    switch (leMoyenDeTransport)
    {
        case (TRAIN):
            cout << "Train";
            break;
        case (AUTO):
            cout << "Auto";
            break;
        case (BATEAU):
            cout << "Bateau";
            break;
        case (AVION):
            cout << "Avion";
            break;
        case (VELO):
            cout << "Velo";
            break;
        case (MARCHE):
            cout << "Marche";
            break;
    }
}

static void saisirVille ( 
    char * ville, 
    unsigned int maxLength, 
    const char * message = "Ville :" )
{
    cout << message << " (taille max: " << maxLength << ")" << endl;
    cin >> ville;
}

static void saisirMoyenDeTransport ( 
    moyenDeTransport & leMoyen, 
    const char * message = "Moyen de transport :" )
{
    int choixTransport;

    cout << message << endl;
    
    cout << "1. "; 
    afficherMoyenDeTransport(TRAIN);
    cout << endl;

    cout << "2. "; 
    afficherMoyenDeTransport(AUTO);
    cout << endl;

    cout << "3. "; 
    afficherMoyenDeTransport(BATEAU);
    cout << endl;

    cout << "4. "; 
    afficherMoyenDeTransport(AVION);
    cout << endl;

    cout << "5. "; 
    afficherMoyenDeTransport(VELO);
    cout << endl; string gt;

    cout << "6. "; 
    afficherMoyenDeTransport(MARCHE);
    cout << endl;

    cin >> choixTransport;

    switch (choixTransport)
    {
        case (1): leMoyen = TRAIN; break;
        case (2): leMoyen = AUTO; break;
        case (3): leMoyen = BATEAU; break;
        case (4): leMoyen = AVION; break;
        case (5): leMoyen = VELO; break;
        case (6): leMoyen = MARCHE; break;
        default: leMoyen = TRAIN; break;
    }
}

static void afficherCatalogue ( Catalogue & leCatalogue )
{
    leCatalogue.Afficher();
}

static void ajouterTrajetSimple ( Catalogue & leCatalogue )
{
    moyenDeTransport leMoyenDeTransport;
    char villeDepart[TAILLE_MAX_VILLE + 1];
    char villeArrivee[TAILLE_MAX_VILLE + 1];

    saisirVille(villeDepart, TAILLE_MAX_VILLE, "Ville de départ :");
    saisirVille(villeArrivee, TAILLE_MAX_VILLE, "Ville d'arrivée :");
    saisirMoyenDeTransport(leMoyenDeTransport, "Moyen de transport :");
    
    TrajetSimple *trajetSimple = new TrajetSimple(villeDepart, villeArrivee, leMoyenDeTransport);
    leCatalogue.AjouterTrajet(trajetSimple);
}

static void ajouterTrajetCompose ( Catalogue & leCatalogue )
{
    CollectionTrajets trajets;
    moyenDeTransport leMoyenDeTransport;
    char villeDepart[TAILLE_MAX_VILLE + 1];
    char villeArrivee[TAILLE_MAX_VILLE + 1];

    saisirVille(villeDepart, TAILLE_MAX_VILLE, "Ville de départ :");
    
    while (true)
    {
        saisirVille(villeArrivee, TAILLE_MAX_VILLE, 
            "Ville suivante (tapez `stop` pour arrêter) :");

        if (strcmp(villeArrivee, "stop") == 0)
            break;

        saisirMoyenDeTransport(leMoyenDeTransport, "Moyen de transport :");

        trajets.AjouterTrajet(
            new TrajetSimple(
                villeDepart, 
                villeArrivee, 
                leMoyenDeTransport
            )
        );

        strcpy(villeDepart, villeArrivee);
    }

    if (trajets.NombreDeTrajets() > 0)
    {
        TrajetCompose *trajetCompose = new TrajetCompose(trajets);
        leCatalogue.AjouterTrajet(trajetCompose);
    }
}

static void rechercherTrajet ( Catalogue & leCatalogue )
{
    char villeDepart[TAILLE_MAX_VILLE + 1];
    char villeArrivee[TAILLE_MAX_VILLE + 1];

    saisirVille(villeDepart, TAILLE_MAX_VILLE, "Ville de départ :");
    saisirVille(villeArrivee, TAILLE_MAX_VILLE, "Ville d'arrivée :");

    CollectionTrajets * trajetsTrouves (
        leCatalogue.Rechercher(villeDepart, villeArrivee)
    );

    cout << "Résultat : " << endl;
    for (unsigned int i (1); i <= trajetsTrouves->NombreDeTrajets(); i++)
    {
        cout << i << " - ";
        trajetsTrouves->TrajetNumero(i)->Afficher();
        cout << endl;
    }

    delete trajetsTrouves;
}

static void rechercherCompletTrajet ( Catalogue & leCatalogue )
{
    char villeDepart[TAILLE_MAX_VILLE + 1];
    char villeArrivee[TAILLE_MAX_VILLE + 1];

    saisirVille(villeDepart, TAILLE_MAX_VILLE, "Ville de départ :");
    saisirVille(villeArrivee, TAILLE_MAX_VILLE, "Ville d'arrivée :");

    CollectionTrajets ** trajetsTrouves;
    unsigned int nbTrajetsTrouves;

    leCatalogue.RechercherComplet(villeDepart, villeArrivee, trajetsTrouves, nbTrajetsTrouves);

    // Affichage des résultats
    cout << "Résultat : " << endl;
    for (unsigned int i (0); i < nbTrajetsTrouves; i++)
    {
        cout << i + 1;
        for (unsigned int j (1); j <= trajetsTrouves[i]->NombreDeTrajets(); j++)
        {
            cout << " - ";
            trajetsTrouves[i]->TrajetNumero(j)->Afficher();
        }
        cout << endl;
    }

    // Destruction des collections
    for (unsigned int i (0); i < nbTrajetsTrouves; i++)
    {
        delete trajetsTrouves[i];
    }

    delete[] trajetsTrouves;
}

//////////////////////////////////////////////////////////////////  PUBLIC

//---------------------------------------------------- Fonctions publiques
int main ()
{
    int choixMenu;
    Catalogue leCatalogue;

    while (true)
    {
        cout << "Menu :" << endl;
        cout << "\t1. Afficher le catalogue" << endl;
        cout << "\t2. Ajouter un trajet simple" << endl;
        cout << "\t3. Ajouter un trajet composé" << endl;
        cout << "\t4. Rechercher un trajet" << endl;
        cout << "\t5. Rechercher un trajet (complet)" << endl;
        cout << "\t0. Quitter" << endl;

        cin >> choixMenu;
        if (cin.eof()) {
            choixMenu = 0;
        }

        switch (choixMenu)
        {
            case 1:
                afficherCatalogue(leCatalogue);
                break;
            case 2:
                ajouterTrajetSimple(leCatalogue);
                break;
            case 3:
                ajouterTrajetCompose(leCatalogue);
                break;
            case 4:
                rechercherTrajet(leCatalogue);
                break;
            case 5:
                rechercherCompletTrajet(leCatalogue);
                break;
            case 0:
                return 0;
        }
    }
    return 0;
}