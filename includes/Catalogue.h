/*************************************************************************
                            Catalogue  -  description
                              --------------------
   début                : 03/10/2019
   copyright            : (C) 2019 par Aleryc SERRANIA et Kesly GASSANT
*************************************************************************/

//---------- Interface de la classe <Catalogue> (fichier <Catalogue.h>) ------

#if ! defined ( CATALOGUE_H )
#define CATALOGUE_H

//--------------------------------------------------- Interfaces utilisées
#include "Trajet.h"
#include "CollectionTrajets.h"
#include <string>

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <Catalogue>
// La classe Catalogue permet de gérer des trajets et de
// rechercher des trajets permettant de partir d'une ville
// de départ jusqu'à une ville d'arrivée
//------------------------------------------------------------------------
class Catalogue
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    void AjouterTrajet ( const Trajet * unTrajet );
    // Mode d'emploi :
    // Permet d'ajouter le trajet unTrajet dans le catalogue.
    // Le trajet doit être alloué dynamiquement en dehors de cette
    // méthode avant d'être ajouté. Après son ajout, c'est l'instance
    // de Catalogue qui gère la destruction de ce trajet.
    // Contrat de cohérence :
    // Le trajet doit être un trajet valide (pour un trajet composé,
    // la ville d'arrivée d'un trajet doit être la ville de départ
    // du suivant.)

    void Afficher () const;
    // Mode d'emploi :
    // Affiche tous les trajets du catalogue.
    // Format d'affichage :
    // {num} - {trajet.Affichage()}

    bool ContientTrajets ( ) const;
    // Mode d'emploi :
    // Permet de savoir si le catalogue contient des trajets dans la collection.
    // Elle renverra true si la collection est vide, sinon false 

    CollectionTrajets * Rechercher ( 
        const char * villeDepart, 
        const char * villeArrivee) const;
    // Mode d'emploi :
    // Retourne tous les trajet dont la ville de départ
    // et la ville d’arrivée sont celles données respectivement
    // en paramètre.
    //
    // La collection de trajets sera alloué dynamiquement
    // dans la méthode et devra donc être libérés plus tard dans
    // le programme.

    void RechercherComplet (
        const char * villeDepart,
        const char * villeArrivee,
        CollectionTrajets **& trajets,
        unsigned int & nbTrajets ) const;
    // Mode d'emploi :
    // Retourne toutes les combinaisons de trajets dont villeDepart
    // est la même ville de départ du premier trajet et villeArrivee
    // est la même ville d'arrivée que le dernier trajet.
    // Le paramètre de sortie trajets contiendra toutes les combinaions
    // et nbTrajets contiendra le nombre de combinaison.
    //
    // Le tableau trajets est alloué dynamiquement dans la méthode
    // et devra donc être libérés plus tard dans le programme. Les
    // éléments du tableau trajets sont aussi alloués dynamiquement
    // et devront aussi être libérés.

    void Sauvegarder(string nomFichier);
    // Mode d'emploi :
    // Permet de sauvegarder l'entièreté du catalogue.
    // Cette méthode utilisera la méthode sauvegarder(const Collection & collection) afin
    // de finaliser la sauvegarde dans le fichier ayant pour nom celui passé en paramètre.

    void Sauvegarder(string nomFichier, TypeTrajet type);
    // Mode d'emploi : 
    // Permet de sauvegarder le catalogue en le filtrant selon le type de
    // trajets.
    // Cette méthode utilisera la méthode sauvegarder(const Collection & collection) afin
    // de finaliser la sauvegarde dans le fichier ayant pour nom celui passé en paramètre.

    void Sauvegarder(string nomFichier, string depart, string arrivee);
    // Mode d'emploi :
    // Cette méthode permet de sauvegarder le catalogue en le filtrant selon
    //le la ville depart et une ville de fin.
    // Cette méthode utilisera la méthode sauvegarder(const Collection & collection) afin
    // de finaliser la sauvegarde dans le fichier ayant pour nom celui passé en paramètre.

    void Sauvegarder(string nomFichier, unsigned int debut, unsigned int fin);
    // Mode d'emploi :
    // Cette méthode permet de sauvegarder le catalogue en le filtrant selon
    // l'intervalle [debut fin]. Tous les trajets du catalogue qui ont leur position
    // dans cette intervalle seront sauvegardés.
    // Cette méthode utilisera la méthode sauvegarder(const Collection & collection) afin
    // de finaliser la sauvegarde dans le fichier ayant pour nom celui passé en paramètre.
    
    void Restituer(string nomFichier);
    // Mode d'emploi :
    // Cette méthode permet de restituer l'ensemble des trajets
    // présents dans le fichier ayant pour nom celui passé en paramètre. 
    // Elle fera appel à la méthode
    // restituerCollectionEntiere pour récupérer les données des trajets.

    void Restituer(string nomFichier, TypeTrajet type);
    // Mode d'emploi :
    // Cette méthode permet de restituer les trajets du type donné en paramètre
    // qui proviennent du fichier nomFichier. Cette méthode fera appel
    // à la méthode restituerCollectionEntiere pour récupérer l'ensemble des trajets
    // dans le fichier passé en paramètre et appliquera ensuite 
    // un filtre par rapport au type de trajet passé en paramètre.
    
    void Restituer(string nomFichier, string depart, string arrivee);
    // Mode d'emploi :
    // Cette méthode permet de restituer les trajets qui proviennent du fichier 
    // nomFichier en fonction d'un départ et d'une arrivée. Cette méthode fera appel
    // à la méthode restituerCollectionEntiere pour récupérer l'ensemble des trajets
    // dans le fichier passé en paramètre et appliquera ensuite un filtre par rapport
    // au départ et à l'arrivée.
    
    void Restituer(string nomFichier, unsigned int debut, unsigned int fin);
    // Mode d'emploi :
    // Cette méthode permet de restituer les trajets qui proviennent du fichier
    // nomFichier en fonction d'un intervalle. Cette méthode fera appel
    // à la méthode restituerCollectionEntiere pour récupérer l'ensemble des trajets
    // dans le fichier passé en paramètre et appliquera ensuite un filtre par rapport
    // à l'intervalle.

    unsigned int NombreTrajets();
    // Mode d'emploi :
    // Permet de récupérer le nombre de trajets qui composent le catalogue courant.
    // Elle appelle la méthode NombreTrajets de sa collection de trajets.

    //------------------------------------------------- Surcharge d'opérateurs

    //-------------------------------------------- Constructeurs - destructeur
    Catalogue ( );
    // Mode d'emploi :
    // Constructeur par défaut de la classe <Catalogue> avec
    // aucun trajet.

    virtual ~Catalogue ( );
    // Mode d'emploi :
    // Destructeur de la classe <Catalogue>
//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées
    void combinaison(
        const char * villeDepart,
        const char * villeArrivee,
        bool * pris,
        unsigned int indexAPrendre,
        const Trajet** uneCombinaison,
        unsigned int tailleCombinaison,
        CollectionTrajets **& trajetsTrouves,
        unsigned int tailleMaxTrajets,
        unsigned int & nbTrajetsTrouves) const;

    void sauvegarder( string nomFichier, const CollectionTrajets & colelction );
    // Mode d'emploi :
    // Cette méthode permet de sauvegarder une collection de trajet dans un
    // fichier passé en paramètre.

    CollectionTrajets* restituerCollectionEntiere(string nomFichier);
    // Mode d'emploi :
    // Cette méthode permet de restituer l'ensemble des trajets contenus dans 
    // le fichier nomFichier. En cas d'erreur de lecture, un nullptr sera 
    // renvoyé. S'il n'y a pas d'erreurs, la méthode retournera la collection de trajets
    // associée au fichier nomFichier.

//----------------------------------------------------- Attributs protégés
    CollectionTrajets _trajets;

};

//-------------------------- Autres définitions dépendantes de <Catalogue>

#endif // CATALOGUE_H
