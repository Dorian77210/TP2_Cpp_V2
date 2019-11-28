/*************************************************************************
                            TrajetCompose  -  description
                              --------------------
   début                : 03/10/2019
   copyright            : (C) 2019 par Aleryc SERRANIA
*************************************************************************/

//---------- Interface de la classe <TrajetCompose> (fichier <TrajetCompose.h>) ------

#if ! defined ( TRAJETCOMPOSE_H )
#define TRAJETCOMPOSE_H
//--------------------------------------------------- Interfaces utilisées
#include "Trajet.h"
#include "CollectionTrajets.h"

//------------------------------------------------------------- Constantes

// Identifiant pour l'écriture dans un fichier d'un trajet composé
const unsigned int TRAJET_COMPOSE_IDENTIFIANT = 2;

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <TrajetCompose>
// Un TrajetCompose est une suite ordonnée de Trajets qui se suivent les  
// uns les autres. La ville d'arrivée d'un trajet doit être la ville de
// départ du trajet suivant.
//------------------------------------------------------------------------
class TrajetCompose : public Trajet
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    virtual const char * VilleDepart () const;
    // Mode d'emploi :
    // Renvoie la ville de départ du premier trajet.

    virtual const char * VilleArrivee () const;
    // Mode d'emploi :
    // Renvoie la ville d'arrivée du dernier trajet.

    virtual void Afficher () const;
    // Mode d'emploi :
    // Format d'affichage :
    // « {trajet1.Afficher()} - {trajet2.Afficher()} - ...»    

    virtual bool Est ( const TypeTrajet type ) const;
    // Mode d'emploi :
    // Cette méthode permet de savoir si le trajet courant est un trajet simple ou compose
    // Elle renverra true si le type est égal à TRAJET_COMPOSE, sinon false

//------------------------------------------------- Surcharge d'opérateurs
    virtual operator string ( ) const;
    // Donne une representation sérialisé d'un trajet composé
    // Mode d'emploi
    // Format:
    // 2 {villeDepart};{villeArrivee};{nbrTrajets}
    //  {trajetNumero1}
    // ...
    //  {trajetNumeroN}

//-------------------------------------------- Constructeurs - destructeur
    TrajetCompose ( const CollectionTrajets & composants );
    // Mode d'emploi :
    // Constructeur de la classe <TrajetCompose>.
    // Construit les trajets composants à partir d'une collection
    // de trajets.
    // 
    // Contrat de cohérence : la collection de trajets ne doit
    // pas être vide.

    TrajetCompose ( string & data );
    // Mode d'emploi
    // Constructeur de la classe <TrajetCompose>.
    // Construit les trajets à partir d'une chaîne de caractère data
    // La chaîne de caratère doit correspondre au format suivant :
    // "{villeDepart};{villeArrivee};{nbrDeTrajets}
    //   {trajet1}
    //   ...
    //   {trajet nrbDeTrajets}
    // ..."


    virtual ~TrajetCompose ( );
    // Mode d'emploi :
    // Destructeur de la classe <TrajetCompose>
    // Détruit les trajets composants ce trajet au passage.

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
    CollectionTrajets _trajets;
};

//---------------------- Autres définitions dépendantes de <TrajetCompose>

#endif // TRAJETCOMPOSE_H