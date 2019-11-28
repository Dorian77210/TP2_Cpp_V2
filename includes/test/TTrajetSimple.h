/*************************************************************************
                            TTrajetSimple  -  description
                              --------------------
   début                : 09/10/2019
   copyright            : (C) 2019 par Aleryc SERRANIA et Kesly GASSANT
*************************************************************************/

//---------- Interface du module <TTrajetSimple> (fichier TTrajetSimple.h) ---------
#if ! defined ( TTRAJETSIMPLE_H )
#define TTRAJETSIMPLE_H

//------------------------------------------------------------------------
// Rôle du module <TTrajetSimple>
// Tests de la classe <TrajetCompose>
//
//------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////  INCLUDE
//--------------------------------------------------- Interfaces utilisées

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques
void testConstructeur();
// Test du constructeur de TrajetSimple

void testConstructeur2();
// Test du constructeur de TrajetSimple

void testConstructeur3();
// Test du constructeur de TrajetSimple

void testConstructeurVillesCopiees();
// Test du constructeur : vérifie que les villes sont bien
// copiées dans le constructeur

#endif // TTRAJETSIMPLE_H