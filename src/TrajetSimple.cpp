/*************************************************************************
                            TrajetSimple  -  description
                              --------------------
   début                : 03/10/2019
   copyright            : (C) 2019 par Aleryc SERRANIA et Kesly GASSANT
*************************************************************************/

//---------- Réalisation de la classe <TrajetSimple> 
//                                      (fichier TrajetSimple.cpp) -------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système

#include <iostream>
#include <cstring>
using namespace std;
//------------------------------------------------------ Include personnel
#include "../includes/TrajetSimple.h"

//------------------------------------------------------------- Constantes

//---------------------------------------------------- Variables statiques

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
const char * TrajetSimple::VilleDepart () const 
// Algorithme : Aucun
{
    return _villeDepart;
} //----- Fin de VilleDepart

const char * TrajetSimple::VilleArrivee () const
// Algorithme : Aucun
{
    return _villeArrivee;
} //----- Fin de VilleArrivee

void TrajetSimple::Afficher () const
// Algorithme : Aucun
{
    cout << "De " << _villeDepart 
        << " à " << _villeArrivee
        << " en ";
    afficherMoyenDeTransport();
} //----- Fin de Afficher

ostream & TrajetSimple::Serialize ( ostream & outStream ) const
{
    return operator<<(outStream, *this);
} // ----- Fin de Serialize

bool TrajetSimple::Est ( TypeTrajet type ) const
{
    return type == TRAJET_SIMPLE;
} // ----- Fin de Est

//------------------------------------------------- Surcharge d'opérateurs
ostream & operator << ( ostream & outStream, const TrajetSimple & trajet )
{
    outStream << TRAJET_SIMPLE_IDENTIFIANT 
              << " "
              << trajet._villeDepart 
              << ";" 
              << trajet._villeArrivee
              << ";"
              << trajet._moyenDeTransport
              << endl;
    return outStream;
} // ------- Fin de operator << (surcharge de l'opérateur de sortie)

//-------------------------------------------- Constructeurs - destructeur
TrajetSimple::TrajetSimple ( 
    const char * laVilleDepart,
    const char * laVilleArrivee,
    moyenDeTransport leMoyenDeTransport
) : Trajet(),
    _villeDepart (new char[strlen(laVilleDepart) + 1]),
    _villeArrivee (new char[strlen(laVilleDepart) + 1]),
    _moyenDeTransport (leMoyenDeTransport)
// Algorithme : Copie les tableau de laVilleDepart et laVilleArrivee 
{
#ifdef MAP
    cout << "Appel au constructeur de <TrajetSimple> (" 
        << laVilleDepart << " -> "
        << laVilleArrivee << ", ";
    afficherMoyenDeTransport() ;
    cout << ")" << endl;
#endif
    strcpy(_villeDepart, laVilleDepart);
    strcpy(_villeArrivee, laVilleArrivee);
} //----- Fin de TrajetSimple

TrajetSimple::~TrajetSimple ( )
// Algorithme : Aucun
{
#ifdef MAP
    cout << "Appel au destructeur de <TrajetSimple>" << endl;
#endif
    delete[] _villeDepart;
    delete[] _villeArrivee;
} //----- Fin de ~TrajetSimple

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
void TrajetSimple::afficherMoyenDeTransport() const
// Algorithme : Aucun
{
    switch (_moyenDeTransport)
    {
        case TRAIN:
            cout << "Train";
            break;
        case AUTO:
            cout << "Auto";
            break;
        case BATEAU:
            cout << "Bateau";
            break;
        case AVION:
            cout << "Avion";
            break;
        case VELO:
            cout << "Velo";
            break;
        case MARCHE:
            cout << "Marche";
            break;
    }    
}