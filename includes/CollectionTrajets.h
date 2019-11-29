/*************************************************************************
                            CollectionTrajets  -  description
                              --------------------
   début                : 03/10/2019
   copyright            : (C) 2019 par Aleryc Serrania
*************************************************************************/

//---------- Interface de la classe <CollectionTrajets> (fichier <CollectionTrajets.h>) ------

#if ! defined ( COLLECTIONTRAJETS_H )
#define COLLECTIONTRAJETS_H
//--------------------------------------------------- Interfaces utilisées
#include "Trajet.h"

//------------------------------------------------------------- Constantes
const unsigned int TAILLE_MAX = 5;
const unsigned int FACTEUR_AJUSTEMENT = 2;
//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <CollectionTrajets>
// La classe CollectionTrajets permet d'ordonner des pointeurs
// sur des instances de Trajet dans un tableau dynamique.
// Elle propose des services d'ajout de trajets après sa construction.
// Elle ne s'occupe que du stockage des pointeurs sur trajet,
// la destruction des objets devra être assurée par la partie
// qui utilise la collection.
//------------------------------------------------------------------------
class CollectionTrajets
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    void AjouterTrajet ( const Trajet * trajet );
    // Mode d'emploi :
    // Ajoute un trajet dans la collection.
    // Ce trajet se trouve à la suite du dernier trajet ajouté à la
    // collection.
    //
    // Contrat de cohérence :
    // La ville de départ du trajet ajouté doit être la même que la ville 
    // d'arrivée du dernier trajet dans la collection.

    unsigned int NombreDeTrajets () const;
    // Mode d'emploi :
    // Renvoie la taille courante de la collection et donc le nombre
    // de trajets.

    const Trajet * TrajetNumero ( unsigned int numero ) const;
    // Mode d'emploi :
    // Renvoie le numero-ieme trajet de la collection de trajets
    // (1 = premier trajet, ..., nombre de trajets = dernier trajet)
    // 
    // Contrat de performance :
    // Si la collection est vide, cette méthode ne doit pas être 
    // appelée. Le numéro doit être compris entre 1 et le nombre de 
    // trajets de la collection inclus.

    void Ajuster ( );
    // Mode d'emploi :
    // Reajuste le tableau dynamique afin que la taille maximale
    // devienne égale à la taille courante.

    void Erase ( void );
    // Mode d'emploi
    // Cette méthode permet remplacer l'ensemble des trajets dans le tableau de trajets
    // par un nullptr
    // Elle sera utilisée dans le cas où nous ne voulons pas supprimer les trajets de la collection

    CollectionTrajets GetTrajetsParType ( const TypeTrajet type ) const;
    // Mode d'emploi :
    // Cette méthode permet de filtrer la collection courante de trajets en fonction
    // du type de trajet
    // Elle sera utilisée lors de l'écriture des trajets en fonction du type de trajets
    // choisi par l'utilisateur

    CollectionTrajets GetTrajetsParVilles ( const string depart, const string arrivee = "" ) const;
    // Mode d'emploi :
    // Cette méthode permet de filtrer la collection courante de trajets en fonction
    // de la ville de départ et de la ville d'arrivée
    // Si la ville d'arrivée est vide, elle ne sera pas pris en compte dans le filtrage

    CollectionTrajets GetTrajetsParIntervalle( const unsigned int borneInf, const unsigned int borneMax) const;
    // Mode d'emploi :
    // Cette méthode permet de filtrer la collection cpurante de trajets en fonction
    // d'une borne inférieure et d'une borne supérieure.
    //
    // Constrat de performance :
    // La collection courante de trajets ne doit pas être vide
    // La borne inférieure doit être comprise entre 0 et la taille de la collection
    // La borne supérieure doit être comprise entre la borne inférieure et la taille de la collection
    // Les bornes inférieure et supérieure peuvent être égales, auquel cas la collection filtrée ne contiendra
    // qu'un seul trajet

    unsigned int GetTotalParType ( const TypeTrajet type ) const;
    // Mode d'emploi :
    // Cette méthode permet de récupérer le nombre de trajets en fonction de leur type

    inline bool EstVide ( ) const
    {
        return _nbElementCourant == 0;
    }
    // Mode d'emploi :
    // Permet de savoir si la collection contient des trajetst ou non
    // Le calcul se fait en comparant la taille courante à 0 ( _nbElementCourant == 0)

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur
    CollectionTrajets ( );
    // Mode d'emploi :
    // Constructeur par défaut de la classe <CollectionTrajets>
    // Les éléments de la collection sont des pointeurs sur Trajet et sont
    // rangés dans un tableau dynamique de taille maximale définie par une
    // constante.
    // La collection est vide et par conséquent le nombre de trajet est de 
    // 0 après la construction.
    // Les éléments sont ordonnés par ordre d'ajout grâce à la méthode
    // AjouterTrajet.

    CollectionTrajets ( const CollectionTrajets & source );
    // Mode d'emploi :
    // Constructeur par copie de la classe <CollectionTrajets>
    // Sa taille courante est la même que la taille de la collection
    // à copier.
    // Elle ne copie pas les trajets pointés par les pointeurs
    // de la collection

    virtual ~CollectionTrajets ( );
    // Mode d'emploi :
    // Destructeur de la classe <CollectionTrajets>

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
    const Trajet** _elements;
    unsigned int _nbElementMax;
    unsigned int _nbElementCourant;
};

//------------------ Autres définitions dépendantes de <CollectionTrajets>

#endif // COLLECTIONTRAJETS_H