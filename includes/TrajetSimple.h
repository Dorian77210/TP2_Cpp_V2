/*************************************************************************
                            TrajetSimple  -  description
                              --------------------
   début                : 03/10/2019
   copyright            : (C) 2019 par Aleryc SERRANIA
*************************************************************************/

//---------- Interface de la classe <TrajetSimple> (fichier <TrajetSimple.h>) ------

#if ! defined ( TRAJETSIMPLE_H )
#define TRAJETSIMPLE_H
//--------------------------------------------------- Interfaces utilisées
#include "Trajet.h"
//------------------------------------------------------------- Constantes

// Identifiant pour l'écriture dans un fichier d'un trajet simple
const unsigned int TRAJET_SIMPLE_IDENTIFIANT = 1;

//------------------------------------------------------------------ Types
typedef enum {
    TRAIN, AUTO, BATEAU, AVION, VELO, MARCHE
} moyenDeTransport;

//------------------------------------------------------------------------
// Rôle de la classe <TrajetSimple>
// Un trajet simple est un trajet caractérisée par une ville de départ,
// une ville d'arrivée ainsi qu'un moyen de transport.
//------------------------------------------------------------------------
class TrajetSimple : public Trajet
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    virtual const char * VilleDepart () const;
    // Mode d'emploi :
    // Retourne la ville de départ.

    virtual const char * VilleArrivee () const;
    // Mode d'emploi :
    // Retourne la ville d'arrivée

    virtual void Afficher () const;
    // Mode d'emploi :
    // Format d'affichage :
    // « De {villeDepart} à {villeArrivee} en {moyenDeTransport} »

    virtual ostream & Serialize ( ostream & outStream ) const;
    // Mode d'emploi
    // Format d'affichage :
    // 1 {villeDepart};{villeArrivee};{moyenTransport}

    virtual bool Est ( const TypeTrajet type ) const;
    // Mode d'emploi :
    // Cette méthode permet de savoir si le trajet courant est un trajet simple ou compose
    // Elle renverra true si le type est égal à TRAJET_SIMPLE, sinon false

//------------------------------------------------- Surcharge d'opérateurs
    // Surcharge de l'opérateur de sortie de flux
    // Cette opérateur permet d'écrire un trajet simple dans un flux de sortie
    // comme par exemple un fichier ou la sortie standard
    // Le paramètre outStream correspond au flux de sortie dans lequel on va écrire
    // Le paramètre trajetSimple est le trajet simple qui sera écrit dans le flux de sortie
    friend ostream & operator << ( ostream & outStream, const TrajetSimple & trajetSimple );

//-------------------------------------------- Constructeurs - destructeur
    TrajetSimple ( 
        const char * laVilleDepart,
        const char * laVilleArrivee,
        moyenDeTransport leMoyenDeTransport );
    // Mode d'emploi :
    // Constructeur à partir de la ville de départ, la ville d'arrivée et
    // le moyen de transport donnés en paramètre.
    // Effectue une copie de la chaîne de caractères de laVilleDepart et
    // laVilleArrivee.

    virtual ~TrajetSimple ( );
    // Mode d'emploi :
    // Destructeur de la classe <TrajetSimple>
//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées
    void afficherMoyenDeTransport() const;
    // Affiche le moyen de transport d'une manière lisible.

//----------------------------------------------------- Attributs protégés
    char * _villeDepart;
    char * _villeArrivee;
    moyenDeTransport _moyenDeTransport;
};

//----------------------- Autres définitions dépendantes de <TrajetSimple>

#endif // TRAJETSIMPLE_H