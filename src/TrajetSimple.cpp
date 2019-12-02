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

bool TrajetSimple::Est ( TypeTrajet type ) const
{
    return type == TRAJET_SIMPLE;
} // ----- Fin de Est

//------------------------------------------------- Surcharge d'opérateurs
TrajetSimple:: operator string ( ) const
{
    string buffer = 
              to_string ( TRAJET_SIMPLE_IDENTIFIANT ) 
              + " "
              + string( _villeDepart )
              + ";" 
              + string( _villeArrivee )
              + ";"
              + to_string( _moyenDeTransport )
              + "\n";

    return buffer;
} // ------- Fin de operator string (surcharge de string)

//-------------------------------------------- Constructeurs - destructeur
TrajetSimple::TrajetSimple ( 
    const char * laVilleDepart,
    const char * laVilleArrivee,
    moyenDeTransport leMoyenDeTransport
) : Trajet(),
    _villeDepart (new char[strlen(laVilleDepart) + 1]),
    _villeArrivee (new char[strlen(laVilleArrivee) + 1]),
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

TrajetSimple::TrajetSimple( string & data )
// Algorithme : manipulation de chaînes de caractères
{
    #ifdef MAP
        cout << "Appel au constructeur de <TrajetSimple> (" << data << ")" << endl;
    #endif

    string buffer;
    // récupération de la ville de départ
    size_t virguleIndex = data.find_first_of ( DONNEES_SEPARATEUR ), retourALigneIndex;

    // traitement de la ville de depart
    buffer = data.substr(0, virguleIndex);
    _villeDepart = new char [ buffer.length() + 1 ];
    strcpy ( _villeDepart, buffer.c_str() );

    // traitement de la ville d'arrivee
    data = data.substr(virguleIndex + 1);
    virguleIndex = data.find_first_of( DONNEES_SEPARATEUR );
    buffer = data.substr(0, virguleIndex);
    _villeArrivee = new char [ buffer.length() + 1 ];
    strcpy( _villeArrivee, buffer.c_str() );

    // traitement du moyen de transport
    data = data.substr(virguleIndex + 1);
    retourALigneIndex = data.find_first_of ( "\n" );
    buffer = data.substr( 0, retourALigneIndex );
    unsigned int moyenDeTransportIndex ( stoul ( buffer ) );

    data = data.substr ( retourALigneIndex + 1 );

    _moyenDeTransport = LISTE_MOYEN_DE_TRANSPORTS [ moyenDeTransportIndex ];
} // ---- Fin de TrajetSimple

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