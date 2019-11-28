/*************************************************************************
                            TrajetCompose  -  description
                              --------------------
   début                : 03/10/2019
   copyright            : (C) 2019 par Aleryc SERRANIA et Kesly GASSANT
*************************************************************************/

//--Réalisation de la classe <TrajetCompose> 
//                                     (fichier TrajetCompose.cpp) -------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système

#include <iostream>
using namespace std;

//------------------------------------------------------ Include personnel
#include "../includes/TrajetCompose.h"
#include "../includes/TrajetSimple.h"
#include "../includes/CollectionTrajets.h"

//------------------------------------------------------------- Constantes

//---------------------------------------------------- Variables statiques

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
const char * TrajetCompose::VilleDepart () const
// Algorithme : Aucun
{
    return _trajets.TrajetNumero(1)->VilleDepart();
} //----- Fin de VilleDepart

const char * TrajetCompose::VilleArrivee () const
// Algorithme : Aucun
{
    return _trajets.TrajetNumero(_trajets.NombreDeTrajets())->VilleArrivee();

} //----- Fin de VilleArrivee

void TrajetCompose::Afficher () const
// Algorithme : Affiche le premier trajet puis affiche tous les autres en 
// préfixant un tiret pour chacun.
{
    if (_trajets.NombreDeTrajets() >= 1)
    {
        _trajets.TrajetNumero(1)->Afficher();
        
        for(unsigned int i (2); i <= this-> _trajets.NombreDeTrajets() ; i++)
        {
            cout << " - ";
            _trajets.TrajetNumero(i)->Afficher();
        }
    }
    
} //----- Fin de Afficher

bool TrajetCompose::Est ( const TypeTrajet type ) const 
{
    return type == TRAJET_COMPOSE;
} // ----- Fin de Est

//------------------------------------------------- Surcharge d'opérateurs
TrajetCompose:: operator string ( ) const
{
    CollectionTrajets trajets = _trajets;
    unsigned int tailleCollection = trajets.NombreDeTrajets( ), i;
    string buffer;

    // ecriture des informations concernant le trajet composé
    buffer += to_string ( TRAJET_COMPOSE_IDENTIFIANT )
            + " "
            + string ( VilleDepart ( ) )
            + DONNEES_SEPARATEUR
            + string ( VilleArrivee() )
            + DONNEES_SEPARATEUR
            + to_string ( tailleCollection )
            + "\n\t";

    // ecriture des trajets qui composent le trajet composé
    for( i = 1; i <= tailleCollection; i++)
    {
        const Trajet* trajet = trajets.TrajetNumero(i);

        buffer += " " + *trajet;
    }

    return buffer;
} // ---- Fin de l'opérateur << ( surcharge de l'opérateur de flux de sortie)

//-------------------------------------------- Constructeurs - destructeur
TrajetCompose::TrajetCompose ( const CollectionTrajets & composants ) :
    Trajet (), _trajets (composants)
// Algorithme : Aucun
{
#ifdef MAP
    cout << "Appel au constructeur de <TrajetCompose> (nbTrajets : " 
        << composants.NombreDeTrajets() << ")" << endl;
#endif
    _trajets.Ajuster();
} //----- Fin de TrajetCompose

TrajetCompose::TrajetCompose ( string & data ) : _trajets ( )
// Algorithme : manipulation de chaîne de caratères
{
    #ifdef MAP
        cout << "Appel au constructeur de <TrajetCompose> (" << data << ")" << endl;
    #endif

    // declaration des variables locales
    string buffer;
    size_t virguleIndex = data.find_first_of ( DONNEES_SEPARATEUR );
    size_t retourALigneIndex, espaceIndex;
    unsigned int typeTrajet;
    const Trajet *trajetCourant;

    // on skip la ville de depart et la ville d'arrivee
    data = data.substr ( virguleIndex + 1 );
    virguleIndex = data.find_first_of ( DONNEES_SEPARATEUR );
    data = data.substr ( virguleIndex + 1 );

    // on retrouve le nombre de trajets
    retourALigneIndex = data.find_first_of ( '\n' );
    buffer = data.substr ( 0, retourALigneIndex );
    unsigned int nbrTrajets = stoul ( buffer );

    data = data.substr ( retourALigneIndex + 1 );
    for ( unsigned int i ( 0 ); i < nbrTrajets; i++ )
    {
        // on recupere le type de trajets
        espaceIndex = data.find_first_of( " " );
        buffer = data.substr( 0, espaceIndex );
        typeTrajet = stoul ( buffer );
        data = data.substr ( espaceIndex + 1 );

        if ( typeTrajet == TRAJET_SIMPLE_IDENTIFIANT ) 
        {
            trajetCourant = new TrajetSimple ( data );
        } else 
        {
            trajetCourant = new TrajetCompose ( data );
        }

        _trajets.AjouterTrajet ( trajetCourant );
    }
} // ----- Fin de TrajetCompose

TrajetCompose::~TrajetCompose ( )
// Algorithme : Boucle sur tous les objets de la collection
// pour les détruire.
{
    for(unsigned int i (1); i <= _trajets.NombreDeTrajets(); i++)
    {
        delete _trajets.TrajetNumero(i);
    }

#ifdef MAP
    cout << "Appel au destructeur de <TrajetCompose>" << endl;
#endif
} //----- Fin de ~TrajetCompose

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
