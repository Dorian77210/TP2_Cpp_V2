/*************************************************************************
                            TTrajetSimple  -  description
                              --------------------
   début                : 09/10/2019
   copyright            : (C) 2019 par Aleryc SERRANIA et Kesly GASSANT
*************************************************************************/

//---------- Réalisation du module <TTrajetSimple> (fichier TTrajetSimple.cpp) -----

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>
using namespace std;

//------------------------------------------------------ Include personnel
#include "../../includes/test/TTrajetSimple.h"
#include "../../includes/TrajetSimple.h"

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
void testConstructeur()
{
    TrajetSimple t("A", "B", AUTO);
    t.Afficher();
    cout << endl;
    cout << t.VilleDepart() << endl;
    cout << t.VilleArrivee() << endl;
    // Devrait afficher :
    // De A à B en Auto
    // A
    // B
}

void testConstructeur2()
{
    TrajetSimple t("ABCDEFGH", "IJKLMNOP", BATEAU);
    t.Afficher();
    cout << endl;
    cout << t.VilleDepart() << endl;
    cout << t.VilleArrivee() << endl;
    // Devrait afficher :
    // De ABCDEFGH à IJKLMNOP en Bateau
    // ABCDEFGH
    // IJKLMNOP
}

void testConstructeur3()
{
    string data = "A;B;1";
    TrajetSimple t(data);

    t.Afficher();
    // devrait afficher:
    // De A à B en Train
}

void testConstructeurVillesCopiees()
{
    const char villeDepart[] = "A";
    const char villeArrivee[] = "B";
    TrajetSimple t(villeDepart, villeArrivee, BATEAU);
    cout << (t.VilleDepart() == villeDepart) << endl;
    cout << (t.VilleArrivee() == villeArrivee) << endl;
    // Devrait afficher :
    // 0
    // 0

}

int main()
{
    testConstructeur();
    testConstructeur2();
    testConstructeur3();
    testConstructeurVillesCopiees();
    return 0;
}