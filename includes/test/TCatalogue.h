/*************************************************************************
                            TCatalogue  -  description
                              --------------------
   début                : 09/10/2019
   copyright            : (C) 2019 par Aleryc SERRANIA et Kesly GASSANT
*************************************************************************/

//---------- Interface du module <TCatalogue> (fichier TCatalogue.h) ---------
#if ! defined ( TCATALOGUE_H )
#define TCATALOGUE_H

//------------------------------------------------------------------------
// Rôle du module <TCatalogue>
// Tests de la classe <Catalogue>
//
//------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////  INCLUDE
//--------------------------------------------------- Interfaces utilisées

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques
void testConstructeur();
// Mode d'emploi : Test le constructeur par défaut et vérifie
// qu'il ne contient aucun trajet

void testAjouter();
// Mode d'emploi : Test la méthode d'ajout

void testRechercherSimpleAucun();
// Mode d'emploi : Test la méthode de recherche simple sur un trajet qui 
// n'existe pas

void testRechercherSimpleExiste();
// Mode d'emploi : Test la méthode de recherche simple sur un ou
// plusieurs trajets qui existent

void testRechercherCompletAucun();
// Mode d'emploi : Test la méthode de recherche complete sur un trajet qui 
// n'est pas possible

void testRechercherCompletExiste();
// Mode d'emploi : Test la méthode de recherche complete sur un trajet qui 
// demande une combinaison de plusieurs trajets.



#endif // TCATALOGUE_H