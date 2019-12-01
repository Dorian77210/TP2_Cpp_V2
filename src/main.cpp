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
#include <fstream>
#include <string>
#include <sstream>

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

//static void chargerFichier(Catalogue & catalogue )
//{

//}

static TypeTrajet selectionTypeTrajet()
{
    string buffer;
    unsigned int typeTrajet;
    cout << "Veuillez selectionné le type de trajet " << endl
         << "1. Trajet simple" << endl
         << "2. Trajet composé" << endl;
    cout << "Attention, en cas de mauvaise saisie, l'option 1 sera sélectionnée par défaut." << endl;

    getline(cin, buffer);
    stringstream choixStream(buffer);

    if (choixStream)
    {
        choixStream >> typeTrajet;
        switch (typeTrajet)
        {
        case 1:
            return TypeTrajet::TRAJET_SIMPLE;
            break;
        case 2:
            return TypeTrajet::TRAJET_COMPOSE;
            break;
        default:
            return TypeTrajet::TRAJET_SIMPLE;
            break;
        }
    }
    else
    {
        return TypeTrajet::TRAJET_SIMPLE;
    }
}

static unsigned int saisirIntervalSauvegarde(string type, unsigned int ValeurDefaut, unsigned int min, unsigned int max)
{
    string buffer;
    unsigned int interval = ValeurDefaut;
    cout << "Veuillez saisir l'interval de " << type << " :" << endl;
    cout << "Note: la valeur doit etre comprise entre " << min << " et "
         << max << endl;

    cout << "Note :  En cas de mauvaise saisir, la valeur " << ValeurDefaut << "sera automatiquement choisi " << endl;

    cin >> buffer;

    stringstream intervalSream(buffer);

    if(intervalSream >> interval)
    {
        if(interval > max || interval < min)
        {
            interval = ValeurDefaut;
            cout << "Valeur " << ValeurDefaut << "choisie par défaut" << endl;
        }
        return interval;
    }
    else
    {
        cout << "Valeur "<< ValeurDefaut << "choisie par défaut" << endl;
        return interval;
    }
   
}

static unsigned int saisirIntervalRestitution(string type, unsigned int ValeurDefaut, unsigned int min)
{
    string buffer;
    unsigned int interval = ValeurDefaut;
    cout << "Veuillez saisir l'interval de " << type << " :" << endl;
    cout << "Note: la valeur doit etre supérieur ou égale à " << min << endl;

    cout << "Note :  En cas de mauvaise saisir, la valeur " << ValeurDefaut << "sera automatiquement choisi " << endl;

    cin >> buffer;

    stringstream intervalSream(buffer);

    if (intervalSream >> interval)
    {
        if (interval < min)
        {
            interval = ValeurDefaut;
            cout << "Valeur " << ValeurDefaut << "choisie par défaut" << endl;
        }
        return interval;
    }
    else
    {
        cout << "Valeur " << ValeurDefaut << "choisie par défaut" << endl;
        return interval;
    }
}

static void sauvegarder ( Catalogue & catalogue )
{
    string nomFichier, buffer = "";
    int choix;
    bool enTrainDeChoisir;

    // on check si le catalogue est vide
    if ( !catalogue.ContientTrajets ( ) )
    {
        cout << "Le catalogue est vide." << endl;
        return;
    }

    cout << "Quel sera le nom de votre fichier ? " << endl;
    cin >> nomFichier;
    cin.clear ( );
    cin.ignore ( 80, '\n' );

    // on check si le fichier existe deja
    ifstream stream ( nomFichier.c_str() );
    if ( stream.good ( ) )
    {
        // le fichier existe déjà, on propose à l'utilisateur de l'écraser ou non

        enTrainDeChoisir = true;

        while ( enTrainDeChoisir )
        {
            cout << "Le fichier " << nomFichier << " existe déjà. Voulez-vous l'écraser ?" << endl;
            cout << "1. Oui \t 2. Non" << endl;
            getline ( cin, buffer );

            stringstream choixStream ( buffer );
            if ( ( choixStream >> choix ) )
            {
                if ( choix == 1 ) 
                {
                    enTrainDeChoisir = false;
                } else if ( choix == 2 )
                {
                    return; // on quitte la fonction
                } else
                {
                    cout << "Le choix que vous avez fait est invalide. Veuillez saisir le nombre 1 pour écraser votre fichier ou 2 si vous ne voulez pas l'écraser" << endl;
                }
            } else
            {
                cout << "Le choix que vous avez fait est invalide. Veuillez saisir le nombre 1 pour écraser votre fichier ou 2 si vous ne voulez pas l'écraser" << endl;
            }
        }
    }

    // on propose à l'utilisateur les différentes options de sauvegarde
    cout << "Nous allons procéder à la sauvegarde de votre catalogue. Voici les choix possibles : " << endl
        << "1. Sans critère de sélection (sauvegarde complète du catalogue)" << endl
        << "2. Selon le type de trajets (Simple ou Composé)" << endl
        << "3. Selon la ville de départ et/ou d'arrivée" << endl
        << "4. Selon une sélection de trajets (sauvegarde des trajets d'une borne inférieure à une borne supérieure)" << endl;
    cout << "Attention, en cas de mauvaise saisie, l'option 1 sera sélectionnée par défaut." << endl;
        
    enTrainDeChoisir = true;

    while ( enTrainDeChoisir )
    {
        cout << "Quelle option choisissez vous ?" << endl;
        getline ( cin, buffer );

        stringstream choixStream ( buffer );
        if ( ( choixStream >> choix ) )
        {
            if ( choix == 1 )
            {
                cout << "Sauvegarde par défaut choisie." << endl;
                catalogue.Sauvegarder(nomFichier);
                enTrainDeChoisir = false;
            } else if ( choix == 2 )
            {
                cout << "Sauvegarde par type de trajets choisie." << endl;
                // TODO : ajout d'une fonction pour séléctionner le type de trajet
                TypeTrajet trajetChoisi;
                trajetChoisi = selectionTypeTrajet();
                catalogue.Sauvegarder(nomFichier, trajetChoisi);
                enTrainDeChoisir = false;
            } else if ( choix == 3 )
            {
                cout << "Sauvegarde selon une ville de départ et/ou d'arrivée choisie." << endl;
                cout << "Attention : si les deux villes saisies sont vides, la sauvegarde par défaut sera utilisée" << endl;
                // TODO : ajout d'une fonction pour séléctionner la ville de départ et d'arrivés
                string depart = "";
                string arrivee = "";

                cout << "Saisissez la ville de départ. Note: laisser le champs vide si vous ne voulez pas de ville de depart";
                cin >> depart;

                cout << "Saisissez la ville d'arrivée. Note: laisser le champs vide si vous ne voulez pas de ville de depart" << endl;
                cin >> arrivee;

                if ( arrivee.empty() && depart.empty() )
                {
                    catalogue.Sauvegarder( nomFichier );
                } else 
                {
                    catalogue.Sauvegarder(nomFichier, depart, arrivee);
                }

                enTrainDeChoisir = false;
            } else if ( choix == 4 )
            {
                cout << "Sauvegarde selon une séléction de trajets par un intervalle choisie." << endl;

                unsigned int debut = saisirIntervalSauvegarde("debut", 1, 1, catalogue.NombreTrajets());
                unsigned int fin = saisirIntervalSauvegarde("fin", catalogue.NombreTrajets(), debut, catalogue.NombreTrajets());

                catalogue.Sauvegarder(nomFichier, debut, fin);
                enTrainDeChoisir = false;
            }
        } else
        {
            cout << "Sauvegarde par défaut choisie." << endl;
            choix = 1;
            catalogue.Sauvegarder(nomFichier);
            enTrainDeChoisir = false;
        }
    }
}


static void restituer(Catalogue &catalogue)
{
    string nomFichier, buffer = "";
    int choix;


    cout << "Quel est le nom de votre fichier ? " << endl;
    cin >> nomFichier;
    cin.clear();
    cin.ignore(80, '\n');

    // on check si le fichier existe deja
    ifstream stream(nomFichier.c_str());

    
    while(!stream.good())
    {
        cout << "Le fichier " << nomFichier << " n'existe pas. Veuillez saisir un autre nom de fichier ?" << endl;
        stream.open(nomFichier.c_str());
        cin >> nomFichier;
        cin.clear();
        cin.ignore(80, '\n');
    }
 
    // restitution 

    // on propose à l'utilisateur les différentes options de restution
    cout << "Nous allons procéder à la sauvegarde de votre catalogue. Voici les choix possibles : " << endl
         << "1. Sans critère de sélection (sauvegarde complète du catalogue)" << endl
         << "2. Selon le type de trajets (Simple ou Composé)" << endl
         << "3. Selon la ville de départ et/ou d'arrivée" << endl
         << "4. Selon une sélection de trajets (sauvegarde des trajets d'une borne inférieure à une borne supérieure)" << endl;
    cout << "Attention, en cas de mauvaise saisie, l'option 1 sera sélectionnée par défaut." << endl;

    
    cout << "Quelle option choisissez vous ?" << endl;
    getline(cin, buffer);

    stringstream choixStream(buffer);
    if ((choixStream >> choix))
    {

        switch (choix)
        {
            case 1:
                cout << "Restitution par défaut choisie." << endl;
                catalogue.restituer(nomFichier);         
                break;
            case 2:
                cout << "Restitution par type de trajets choisie." << endl;
                TypeTrajet trajetChoisi;
                trajetChoisi = selectionTypeTrajet();
                catalogue.restituer(nomFichier, trajetChoisi);
                break;
            case 3:
            {
                cout << "Restitution selon une ville de départ et/ou d'arrivée choisie." << endl;
                // TODO : ajout d'une fonction pour séléctionner la ville de départ et d'arrivés
                string villeDep = "";
                string villeArr = "";

                    cout << "Saisissez la ville de départ. Note: laisser le champs vide si vous ne voulez pas de ville de depart"<<endl;
                    cin >> villeDep;

                    if (villeDep == "")
                    {
                        cout << "Veuillez saisir la ville d'arrivée" << endl;
                    }
                    else
                    {
                        cout << "Veuillez saisir la ville d'arrivée. Note: laisser le champs vide si vous ne voulez pas de ville de depart" << endl;
                    }

                    cin >> villeArr;

                    catalogue.restituer(nomFichier, villeDep, villeArr);
                    
                    break;
            }
            case 4:
            {
                cout << "Sauvegarde selon une séléction de trajets par un intervalle choisie." << endl;

                unsigned int debut = saisirIntervalRestitution("debut", 1, 1);
                unsigned int fin = saisirIntervalRestitution("fin", debut, debut);
                catalogue.restituer(nomFichier, debut,fin);
                break;
            }
            default:
            {
                cout << "Restitution par défaut choisie." << endl;
                catalogue.restituer(nomFichier);     
                break;
            }
        }

    }
    else
    {
        cout << "restittution par défaut choisie." << endl;
        
    }
    
}

//////////////////////////////////////////////////////////////////  PUBLIC

//---------------------------------------------------- Fonctions publiques
int main ()
{
    int choixMenu;
    Catalogue leCatalogue;
    /*string to = ("A;Marseille;2");
    TrajetSimple *t  = new TrajetSimple(to);
    leCatalogue.AjouterTrajet(t);
    leCatalogue.Afficher();
    */

    while (true)
    {
        cout << "Menu :" << endl;
        cout << "\t1. Afficher le catalogue" << endl;
        cout << "\t2. Ajouter un trajet simple" << endl;
        cout << "\t3. Ajouter un trajet composé" << endl;
        cout << "\t4. Rechercher un trajet" << endl;
        cout << "\t5. Rechercher un trajet (complet)" << endl;
        cout << "\t6. Sauvegarder le catalogue courant" << endl;
        cout << "\t7. Restituer le catalogue courant" << endl;
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
            case 6:
                sauvegarder ( leCatalogue );
                break;
            case 7:
                restituer(leCatalogue);
                break;
            case 0:
                return 0;
        }
    }
    return 0;
}