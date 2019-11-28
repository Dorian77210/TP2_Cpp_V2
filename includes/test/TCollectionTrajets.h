/*************************************************************************
                            TCollectionTrajets  -  description
                              --------------------
   début                : 09/10/2019
   copyright            : (C) 2019 par Aleryc SERRANIA et Kesly GASSANT
*************************************************************************/

//---------- Interface du module <TCollectionTrajets> (fichier TCollectionTrajets.h) ---------
#if ! defined ( TCOLLECTIONTRAJETS_H )
#define TCOLLECTIONTRAJETS_H

//------------------------------------------------------------------------
// Rôle du module <TCollectionTrajets>
// Tests de la classe <CollectionTrajets>
//
//------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////  INCLUDE
//--------------------------------------------------- Interfaces utilisées

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques
void testConstructeurDefaut();
// Mode d'emploi : Test le constructeur par défaut et vérifie
// qu'il n'y a aucun trajet dedans

void testConstructeurCopie();
// Mode d'emploi : Test le constructeur par copie

void testAjouterAuDessusTailleMax();
// Mode d'emploi : vérifie que la collection gère bien
// le réajustement du tableau dynamique des pointeurs sur trajets.

#endif // TCOLLECTIONTRAJETS_H