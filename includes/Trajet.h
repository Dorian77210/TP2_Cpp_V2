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

//------------------------------------------------------------------ Types
enum TypeTrajet { TRAJET_SIMPLE, TRAJET_COMPOSE };
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

    virtual ostream & Serialize ( ostream & outStream ) const = 0;
    // Mode d'emploi:
    // Ecrit dans le flux outStream une version sérialisé du trajet courant
    // Le format d'écriture dépend des classes filles

    virtual bool Est ( const TypeTrajet type ) const = 0;
    // Mode d'emploi
    // Cette methode permet de connaître le type d'un trajet sans avoir recours
    // aux casts. Elle sera redéfinie dans les classes TrajetSimple et TrajetCompose.

//------------------------------------------------- Surcharge d'opérateurs

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