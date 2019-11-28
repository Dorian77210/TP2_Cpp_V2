/*************************************************************************
                            TCollectionTrajets  -  description
                              --------------------
   début                : 09/10/2019
   copyright            : (C) 2019 par Aleryc SERRANIA et Kesly GASSANT
*************************************************************************/

//---------- Réalisation du module <TCollectionTrajets> (fichier TCollectionTrajets.cpp) -----

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>
using namespace std;

//------------------------------------------------------ Include personnel
#include "../../includes/test/TCollectionTrajets.h"
#include "../../includes/CollectionTrajets.h"
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
void testConstructeurDefaut()
{
    CollectionTrajets c;
    cout << c.NombreDeTrajets() << endl;
    // Devrait afficher :
    // 0

} //----- testConstructeurDefaut

void testConstructeurCopie()
{
    TrajetSimple t1("A", "B", AUTO);
    TrajetSimple t2("B", "D", BATEAU);
    TrajetSimple t3("E", "A", TRAIN);

    CollectionTrajets c;
    c.AjouterTrajet(&t1);
    c.AjouterTrajet(&t2);
    c.AjouterTrajet(&t3);

    CollectionTrajets copie(c);

    cout << (c.NombreDeTrajets() == copie.NombreDeTrajets()) << endl;
    cout << (c.TrajetNumero(1) == copie.TrajetNumero(1)) << endl;
    cout << (c.TrajetNumero(2) == copie.TrajetNumero(2)) << endl;
    cout << (c.TrajetNumero(3) == copie.TrajetNumero(3)) << endl;

    // Devrait afficher :
    // 1
    // 1
    // 1
    // 1

} //----- testConstructeurCopie

void testAjouterAuDessusTailleMax()
{
    TrajetSimple t1("A", "B", AUTO);
    TrajetSimple t2("B", "D", BATEAU);
    TrajetSimple t3("E", "A", TRAIN);
    TrajetSimple t4("A", "B", AUTO);
    TrajetSimple t5("B", "D", BATEAU);
    TrajetSimple t6("E", "A", TRAIN);

    CollectionTrajets c;
    c.AjouterTrajet(&t1);
    c.AjouterTrajet(&t2);
    c.AjouterTrajet(&t3);
    c.AjouterTrajet(&t4);
    c.AjouterTrajet(&t5);
    c.AjouterTrajet(&t6);

    cout << c.NombreDeTrajets() << endl;
    cout << (&t1 == c.TrajetNumero(1)) << endl;
    cout << (&t2 == c.TrajetNumero(2)) << endl;
    cout << (&t3 == c.TrajetNumero(3)) << endl;
    cout << (&t4 == c.TrajetNumero(4)) << endl;
    cout << (&t5 == c.TrajetNumero(5)) << endl;
    cout << (&t6 == c.TrajetNumero(6)) << endl;
    // Devrait afficher :
    // 6
    // 1
    // 1
    // 1
    // 1
    // 1
    // 1

} //----- testAjouterAuDessusTailleMax

int main () 
{
    testConstructeurDefaut();
    testConstructeurCopie();
    testAjouterAuDessusTailleMax();
    return 0;
}