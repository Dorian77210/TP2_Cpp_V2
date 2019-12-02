/*************************************************************************
                            Trajet  -  description
                              --------------------
   début                : 03/10/2019
   copyright            : (C) 2019 par Aleryc SERRANIA
*************************************************************************/

//---------- Interface de la classe <Trajet> (fichier <Trajet.h>) ------

#if ! defined ( TRAJET_H )
#define TRAJET_H
//--------------------------------------------------- Interfaces utilisées
#include <iostream>
using namespace std;

//------------------------------------------------------------- Constantes

// Séparteur pour la sérailisation
const string DONNEES_SEPARATEUR = ";";

//------------------------------------------------------------------ Types

// enumération correspondant aux types de trajets
enum TypeTrajet { TRAJET_SIMPLE, TRAJET_COMPOSE };

const TypeTrajet TYPES_TRAJETS[2] = {
    TRAJET_SIMPLE, TRAJET_COMPOSE
};

//------------------------------------------------------------------------
// Rôle de la classe <Trajet>
// La classe trajet est une classe abstraite qui promet
// de donner une ville de départ, une ville d'arrivée et
// une manière d'afficher le trajet.
//------------------------------------------------------------------------
class Trajet
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    virtual const char * VilleDepart () const = 0;
    // Mode d'emploi :
    // Renvoie la ville de départ du trajet

    virtual const char * VilleArrivee () const = 0;
    // Mode d'emploi :
    // Renvoie la ville d'arrivée du trajet

    virtual void Afficher () const = 0;
    // Mode d'emploi :
    // Affiche le trajet sur la sortie standard.
    // Le format est définie dans les classes descendantes.

    virtual bool Est ( const TypeTrajet type ) const = 0;
    // Mode d'emploi
    // Cette methode permet de connaître le type d'un trajet sans avoir recours
    // aux casts. Elle sera redéfinie dans les classes TrajetSimple et TrajetCompose.

    //------------------------------------------------- Surcharge d'opérateurs
    virtual operator string( ) const = 0;
    // Mode d'emploi:
    // Methode qui permet de sérialiser un trajet.
    // Elle sera surchargée dans les classes enfants

    // Surcharge de l'opérateur de sortie de flux
    // Cette opérateur permet d'écrire un trajet dans un flux de sortie
    // comme par exemple un fichier ou la sortie standard
    // Le paramètre outStream correspond au flux de sortie dans lequel on va écrire
    // Le paramètre trajet est le trajet qui sera écrit dans le flux de sortie
    friend ostream & operator << ( ostream & outStream, const Trajet & trajet )
    {
        return outStream << static_cast<string>( trajet );
    }

    // Surcharge de l'opérateur += de la classe string
    // Cette méthode permet d'ajouter au string courant la sérialisation du trajet
    friend string operator + ( string data, const Trajet & trajet )
    {
        data += static_cast<string>(trajet);
        return data;
    }
//-------------------------------------------- Constructeurs - destructeur
    Trajet ( );
    // Mode d'emploi :
    // Constructeur par défaut de la classe <Trajet>

    virtual ~Trajet ( );
    // Mode d'emploi :
    // Destructeur de la classe <Trajet>

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés

};

//--------------------------- Autres définitions dépendantes de <Trajet>

#endif // TRAJET_H