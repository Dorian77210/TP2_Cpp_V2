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

#include <iostream>
#include <cstddef>
using namespace std;

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
} // ----- Fin de Ajuster

void CollectionTrajets::Erase ( )
// Algorithme : Aucun
{
    for ( unsigned int i ( 0 ); i < _nbElementCourant; i++ )
    {
        _elements [ i ] = nullptr;
    }
} // ----- Fin de Erase

CollectionTrajets CollectionTrajets::GetTrajetsParType ( const TypeTrajet type ) const
// Algorithme : aucun
{
    CollectionTrajets collectionTrajets;
    const Trajet* trajetCourant;

    for ( unsigned int i ( 0 ); i < _nbElementCourant; i++ )
    {
        trajetCourant = _elements [ i ];
        if ( trajetCourant->Est ( type ) )
        {
            collectionTrajets.AjouterTrajet ( trajetCourant );
        }
    }

    return collectionTrajets;
} // ------ Fin de GetTrajetsParType

CollectionTrajets CollectionTrajets::GetTrajetsParVilles ( const string depart, const string arrivee ) const
// Algorithme : aucun
{
    CollectionTrajets collectionTrajets;
    const Trajet *trajetCourant;
    const char *trajetCourantDepart, *trajetCourantArrivee;

    for ( unsigned int i ( 0 ); i < _nbElementCourant; i++ ) 
    {
        trajetCourant = _elements [ i ];
        trajetCourantDepart = trajetCourant->VilleDepart ();

        if ( depart.empty ( ) )
        {
            trajetCourantArrivee = trajetCourant->VilleArrivee ( );
            if ( arrivee.compare ( trajetCourantArrivee ) == 0 )
            {
                collectionTrajets.AjouterTrajet ( trajetCourant );
            }   
        } else if ( arrivee.empty ( ) )
        {
            trajetCourantDepart = trajetCourant->VilleDepart ( );
            if ( depart.compare ( trajetCourantDepart ) == 0 )
            {
                collectionTrajets.AjouterTrajet ( trajetCourant );
            }
        } else
        {
            trajetCourantDepart = trajetCourant->VilleDepart ( );
            trajetCourantArrivee = trajetCourant->VilleArrivee ( );
            if ( ( depart.compare ( trajetCourantDepart ) == 0 ) && ( arrivee.compare ( trajetCourantArrivee ) == 0 ) )
            {
                collectionTrajets.AjouterTrajet ( trajetCourant );
            }
        }
    }

    return collectionTrajets;
} // --- Fin de GetTrajetsParVilles

CollectionTrajets CollectionTrajets::GetTrajetsParIntervalle ( const unsigned int borneInf, const unsigned int borneSup ) const
// Algorithme : aucun
{
    CollectionTrajets collectionTrajets;
    const Trajet *trajetCourant;

    for ( unsigned int i ( borneInf ); i <= borneSup; i++ )
    {
        trajetCourant = TrajetNumero ( i );
        collectionTrajets.AjouterTrajet ( trajetCourant );
    }

    return collectionTrajets;
} // ---- Fin de GetTrajetsParIntervalle

unsigned int CollectionTrajets::GetTotalParType ( const TypeTrajet type ) const
{
    unsigned int total ( 0 );
    const Trajet *trajetCourant;

    for ( unsigned int i ( 0 ); i < _nbElementCourant; i++ )
    {
        trajetCourant = _elements [ i ];
        if ( trajetCourant->Est ( type ) )
        {
            total++;
        }
    }

    return total;
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
