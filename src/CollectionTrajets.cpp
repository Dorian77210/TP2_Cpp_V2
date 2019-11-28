/*************************************************************************
                            CollectionTrajets  -  description
                              --------------------
   début                : 03/10/2019
   copyright            : (C) 2019 par Aleryc SERRANIA et Kesly GASSANT
*************************************************************************/

//---------- Réalisation de la classe <CollectionTrajets> 
//                                 (fichier CollectionTrajets.cpp) -------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>

//------------------------------------------------------ Include personnel
#include "../includes/CollectionTrajets.h"
//------------------------------------------------------------- Constantes

//---------------------------------------------------- Variables statiques

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
void CollectionTrajets::AjouterTrajet ( const Trajet * trajet )
// Algorithme : Si le nombre d'element courant est égal à la taille
// maximale du tableau, on créé un nouveau tableau assez grand
{

    if(_nbElementMax <= _nbElementCourant) // tableau pas assez grand
    {
        // Création d'un nouveau tableau assez grand
        _nbElementMax *= FACTEUR_AJUSTEMENT;
        const Trajet** nouveauTab = new const Trajet*[_nbElementMax];

        // Copie les éléments de l'ancien tableau dans le nouveau
        for (unsigned int i = 0; i < _nbElementCourant; i++)
        {
            nouveauTab[i] = _elements[i];
        }

        // Détruit l'ancien tableau
        delete []_elements;
        _elements = nouveauTab;

    }

    _elements[_nbElementCourant] = trajet;
    _nbElementCourant++;

} // ----- Fin de AjouterTrajet

unsigned int CollectionTrajets::NombreDeTrajets () const
// Algorithme : Aucun
{
    return _nbElementCourant;
}

const Trajet * CollectionTrajets::TrajetNumero ( unsigned int numero ) const
// Algorithme : Aucun
{
    return _elements[numero - 1];
}

void CollectionTrajets::Ajuster ( )
// Algorithme : Aucun
{
    if (_nbElementCourant == _nbElementMax) 
        return;

    _nbElementMax = _nbElementCourant;
    const Trajet** nouveauTab = new const Trajet*[_nbElementMax];

    // Copie les éléments de l'ancien tableau dans le nouveau
    for (unsigned int i = 0; i < _nbElementCourant; i++)
    {
        nouveauTab[i] = _elements[i];
    }

    // Détruit l'ancien tableau
    delete [] _elements;
    _elements = nouveauTab;
}

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur
CollectionTrajets::CollectionTrajets ( const CollectionTrajets & source ) : 
    _elements (new const Trajet*[source._nbElementCourant]),
    _nbElementMax (source._nbElementMax),
    _nbElementCourant (source._nbElementCourant)
// Algorithme : Aucun
{   
#ifdef MAP
    cout << "Appel au constructeur par copie de <CollectionTrajets>" << endl;
#endif

    for (unsigned int i (0); i < _nbElementCourant; i++)
    {
        _elements[i] = source._elements[i];
    }
    
} //----- Fin de CollectionTrajets

CollectionTrajets::CollectionTrajets () :
    _elements (new const Trajet*[TAILLE_MAX]),
    _nbElementMax (TAILLE_MAX),
    _nbElementCourant (0)
// Algorithme : Aucun
{   
#ifdef MAP
    cout << "Appel au constructeur par défaut de <CollectionTrajets>" << endl;
#endif
} //----- Fin de CollectionTrajets



CollectionTrajets::~CollectionTrajets ( )
// Algorithme : Aucun
//
{
#ifdef MAP
    cout << "Appel au destructeur de <CollectionTrajets>" << endl;
#endif

    delete []_elements;

} //----- Fin de ~CollectionTrajets

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
