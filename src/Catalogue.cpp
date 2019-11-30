/*************************************************************************
                            Catalogue  -  description
                              --------------------
   début                : 03/10/2019
   copyright            : (C) 2019 par Aleryc SERRANIA et Kesly GASSANT
*************************************************************************/

//---------- Réalisation de la classe <Catalogue>
//                                         (fichier Catalogue.cpp) -------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système

#include <iostream>
#include <cstring>
#include <fstream>

//------------------------------------------------------ Include personnel
#include "../includes/Catalogue.h"
using namespace std;
//------------------------------------------------------------- Constantes

//---------------------------------------------------- Variables statiques

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
void Catalogue::AjouterTrajet ( const Trajet * t )
// Algorithme : aucun
{
    _trajets.AjouterTrajet(t);
} //----- Fin de AjouterTrajet

void Catalogue::Afficher () const
// Algorithme : boucle sur tous les trajets et invoque pour chacun
// sa méthode d'affichage.
{
    for (unsigned int i (1); i <= _trajets.NombreDeTrajets(); i++)
    {
        cout << i << " - ";
        _trajets.TrajetNumero(i)->Afficher();
        cout << endl;
    }
} //----- Fin de Afficher

bool Catalogue::ContientTrajets ( ) const
{
    return !_trajets.EstVide ( );
} // ------ Fin de ContientTrajets

CollectionTrajets * Catalogue::Rechercher ( 
    const char * villeDepart,
    const char * villeArrivee) const
// Algorithme : Boucle sur tous les trajet du catalogue et ajoute le
// trajet dans la collection si la ville de départ et la ville
// d'arrivée sont les mêmes
{
    CollectionTrajets * trajetsTrouves (new CollectionTrajets());

    for (unsigned int i (1); i <= _trajets.NombreDeTrajets(); i++)
    {
        const Trajet * trajetCourant = _trajets.TrajetNumero(i);
        if (strcmp(trajetCourant->VilleDepart(), villeDepart) == 0
        && strcmp(trajetCourant->VilleArrivee(), villeArrivee) == 0)
        {
            trajetsTrouves->AjouterTrajet(trajetCourant);
        }
    }

    return trajetsTrouves;
} //----- Fin de Rechercher

void Catalogue::RechercherComplet (
    const char * villeDepart,
    const char * villeArrivee,
    CollectionTrajets **& trajetsTrouves,
    unsigned int & nbTrajetsTrouves ) const
// Algorithme :
// Le principe de base est de parcourir toutes les combinaisons possibles
// de trajets.
// Pour ce faire, pour chaque trajet on divise la recherche en deux :
// on prend le trajet et on ne prends pas le trajet, et on réitère pour
// les projets suivants.
// De cette manière, on aura simuler le parcours d'un arbre binaire,
// qui, à chaque niveau de l'arbre décide de prendre ou ne pas prendre
// un trajet.
{
    const unsigned int TAILLE_MAX_DEF (10);
    unsigned int tailleMaxTrajets (TAILLE_MAX_DEF);
    const Trajet** uneCombinaison (
        new const Trajet*[_trajets.NombreDeTrajets()]
    );
    bool * pris ( new bool[_trajets.NombreDeTrajets()] );
    for (unsigned int i = 0; i < _trajets.NombreDeTrajets(); i++)
    {
        pris[i] = false;
    }

    trajetsTrouves = new CollectionTrajets*[tailleMaxTrajets];
    nbTrajetsTrouves = 0;

    for (unsigned int i = 1; i <= _trajets.NombreDeTrajets(); i++)
    {
        pris[i-1] = true;
        combinaison(
            villeDepart,
            villeArrivee,
            pris,
            i, // index du prochain à prendre
            uneCombinaison,
            0, // nombre de trajets dans la combinaison
            trajetsTrouves,
            tailleMaxTrajets,
            nbTrajetsTrouves
        );
        pris[i-1] = false;
    }



    delete[] uneCombinaison;
}

void Catalogue::Sauvegarder(string nomFichier, const CollectionTrajets &c)
{
    // ouvrir le fichier
    ofstream monFlux(nomFichier.c_str());

    if(monFlux)
    {
        // completer l'entete
        unsigned int nbTrajetSimple = this->_trajets.GetTotalParType(TRAJET_SIMPLE);
        unsigned int nbTrajetCompose= this->_trajets.GetTotalParType(TRAJET_COMPOSE);

        monFlux << nbTrajetSimple << " " << nbTrajetCompose << endl;

        // ajouter les trajets
        for (int i = 1; i <= this->_trajets.NombreDeTrajets(); ++i)
        {
            monFlux << i << " "; //index
            monFlux << static_cast<string>(*this->_trajets.TrajetNumero(i));
        }
    }
    else
    {
        cout << "ERREUR: Impossible d'ouvir le fichier" << endl;
    }
}

void Catalogue::Sauvegarder(string nomFichier)
{
  this->Sauvegarder(nomFichier, this->_trajets);
}

void Catalogue::Sauvegarder(string nomFichier, TypeTrajet type)
{
    this->Sauvegarder(nomFichier, this->_trajets.GetTrajetsParType(type));
}

void Catalogue::Sauvegarder(string nomFichier, string depart, string arrivee)
{
    this->Sauvegarder(nomFichier, this->_trajets.GetTrajetsParVilles(depart, arrivee));
}

void Catalogue::Sauvegarder(string nomFichier, unsigned int debut, unsigned int fin)
{
    this->Sauvegarder(nomFichier, this->_trajets.GetTrajetsParIntervalle(debut, fin));
}

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur
Catalogue::Catalogue () : _trajets()
// Algorithme : Aucun
{
#ifdef MAP
    cout << "Appel au constructeur par défaut de <Catalogue>" << endl;
#endif
} //----- Fin de Catalogue

Catalogue::~Catalogue ( )
// Algorithme : boucle sur les trajets de la collection pour les
// détruire.
{
#ifdef MAP
    cout << "Appel au destructeur de <Catalogue>" << endl;
#endif

    for(unsigned int i (1); i <= _trajets.NombreDeTrajets(); i++)
    {
        delete _trajets.TrajetNumero(i);
    }
} //----- Fin de ~Catalogue

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
void Catalogue::combinaison(
    const char * villeDepart,
    const char * villeArrivee,
    bool * pris,
    unsigned int indexAPrendre,
    const Trajet** uneCombinaison,
    unsigned int tailleCombinaison,
    CollectionTrajets **& trajetsTrouves,
    unsigned int tailleMaxTrajets,
    unsigned int & nbTrajetsTrouves ) const
// Algorihtme :
// Si on décide de ne pas prendre le trajet courant, on passe
// au trajet suivant (qu'on doit ou ne doit pas prendre).
// Si on décide de prendre le trajet courant, il y a deux cas :
//  - Cas général : vérifier que la ville de départ du trajet courant
//    est la même que la ville d'arrivée du dernier trajet de
//    la combinaison, sinon on arrête la récursivité.
//  - Cas particulier : il n'y a aucun trajet dans la combinaison,
//    on vérifie que la ville de départ du trajet courant est la
//    même que celle demandée  en paramètre, sinon on arrête la
//    récursivité.
// Dans tous les cas, si la ville d'arrivée du trajet courant
// (celui ajouté) est la même que la ville d'arrivée donnée en
// paramètre, on ajoute la combinaison de trajet dans notre
// tableau de collection de trajets `trajetsTrouves` : c'est
// un trajet qui répond à la demande.
// S'il n'y a plus de trajets à ajouter, la récursivité s'arrête.
{
    // vérification de la cohésion entre trajet précédent et
    // trajet courant
    if (tailleCombinaison == 0)
    {
        if (strcmp(_trajets.TrajetNumero(indexAPrendre)->VilleDepart(),
        villeDepart) != 0)
            return;
    }
    else
    {
        if (strcmp( _trajets.TrajetNumero(indexAPrendre)->VilleDepart(),
        uneCombinaison[tailleCombinaison-1]->VilleArrivee()) != 0)
            return;
    }

    // ajout du trajet dans la combinaison
    uneCombinaison[tailleCombinaison] = _trajets.TrajetNumero(indexAPrendre);
    tailleCombinaison++;

    // si la combinaison de trajets répond à la demande,
    // on l'ajoute dans notre tableau.
    const Trajet * premier ( uneCombinaison[0] );
    const Trajet * dernier ( uneCombinaison[tailleCombinaison-1] );
    if (strcmp(villeDepart, premier->VilleDepart()) == 0
    && strcmp(villeArrivee,dernier->VilleArrivee()) == 0)
    {
        if (nbTrajetsTrouves >= tailleMaxTrajets)
        {
            tailleMaxTrajets += tailleMaxTrajets;
            CollectionTrajets** nouvTableau (
                new CollectionTrajets*[tailleMaxTrajets]
            );

            for (unsigned int i (0); i < nbTrajetsTrouves; i++)
            {
                nouvTableau[i] = trajetsTrouves[i];
            }

            delete[] trajetsTrouves;
            trajetsTrouves = nouvTableau;
        }

        trajetsTrouves[nbTrajetsTrouves] = new CollectionTrajets;
        for (unsigned int i = 0; i < tailleCombinaison; i++)
        {
            trajetsTrouves[nbTrajetsTrouves]
                ->AjouterTrajet(uneCombinaison[i]);
        }
        nbTrajetsTrouves++;
    }

    for (unsigned int i = 1; i <= _trajets.NombreDeTrajets(); i++)
    {
        if (!pris[i-1])
        {
            pris[i-1] = true;
            combinaison(
                villeDepart,
                villeArrivee,
                pris,
                i, // index du prochain à prendre
                uneCombinaison,
                tailleCombinaison,
                trajetsTrouves,
                tailleMaxTrajets,
                nbTrajetsTrouves
            );
            pris[i-1] = false;
        }
    }
}
