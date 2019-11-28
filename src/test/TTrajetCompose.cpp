/*************************************************************************
                            TTrajetCompose  -  description
                              --------------------
   début                : 09/10/2019
   copyright            : (C) 2019 par Aleryc SERRANIA et Kesly GASSANT
*************************************************************************/

//---------- Réalisation du module <TTrajetCompose> (fichier TTrajetCompose.cpp) -----

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>
using namespace std;

//------------------------------------------------------ Include personnel
#include "../../includes/test/TTrajetCompose.h"
#include "../../includes/TrajetCompose.h"
#include "../../includes/TrajetSimple.h"
#include "../../includes/CollectionTrajets.h"

///////////////////////////////////////////////////////////////////  PRIVE

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//---------------------------------------------------- Variables statiques

//------------------------------------------------------ Fonctions privées
//static type nom ( liste de paramètres )
// Mode d'emploi :
//
// Contrat :
//
// Algorithme :
//
//{
//} //----- fin de nom

//////////////////////////////////////////////////////////////////  PUBLIC

//---------------------------------------------------- Fonctions publiques
void testUnSeulTrajet()
{
    Trajet * t1 = new TrajetSimple("A", "B", AVION);
    CollectionTrajets ct;
    ct.AjouterTrajet(t1);
    TrajetCompose tc (ct);
    cout << tc.VilleDepart() << endl;
    cout << tc.VilleArrivee() << endl;
    tc.Afficher();
    cout << endl;
    // Devrait afficher :
    // A
    // B
    // De A à B en Avion
}

void testPlusieursTrajets()
{
    Trajet * t1 = new TrajetSimple("A", "B", AVION);
    Trajet * t2 = new TrajetSimple("B", "E", TRAIN);
    Trajet * t3 = new TrajetSimple("E", "A", BATEAU);
    CollectionTrajets ct;
    ct.AjouterTrajet(t1);
    ct.AjouterTrajet(t2);
    ct.AjouterTrajet(t3);

    TrajetCompose tc (ct);
    cout << tc.VilleDepart() << endl;
    cout << tc.VilleArrivee() << endl;
    tc.Afficher();
    cout << endl;
    // Devrait afficher :
    // A
    // A
    // De A à B en Avion - De B à E en Train - De E à A en Bateau
}

int main ()
{
    testUnSeulTrajet();
    testPlusieursTrajets();
    return 0;
}