# Makefile rules

```makefile
make debug # options -g and -D MAP and create `debug` binary file
make release # no debug options and create `release` binary file
make clean # erase executable and obj files
```

# Spécification techniques de chaque méthode

```cpp
class Catalogue;
```

```cpp
Catalogue ();
```
Constructeur par défaut. Rien de spécial.

```cpp
void AjouterTrajet (const Trajet * t);
```
Permet d’ajouter un trajet dans le catalogue.
Contrat de cohérence : le trajet doit être un trajet valide (pour un trajet composé ville d’arrivée d’un trajet doit être la ville de départ du suivant)

```cpp
void Afficher () const;
```

Affiche tous les trajets du catalogue.
Format d’affichage :

`{<num element>} - {trajet.Affichage()}`


```cpp
CollectionTrajets * Rechercher (const char * villeDepart, const char * villeArrivee) const;
```
Retourne tous les trajet dont la ville de départ et la ville d’arrivée sont celles données en paramètre.
La collection trajetsTrouves sera alloué dynamiquement dans la méthode et devra donc être libérés plus tard dans le programme en dehors de celle-ci.
```cpp
class Trajet;
```

```cpp
virtual const char * VilleDepart () const = 0;
```
Renvoie la ville de départ du trajet.

```cpp
virtual const char * VilleArrivee () const = 0 ;
```
Renvoie la ville d’arrivée du trajet.

```cpp
virtual void Afficher () const  = 0;
```
Affiche le trajet sur la sortie standard. Le format est définie dans les classes descendantes de celle-ci.


```cpp
class TrajetSimple : public Trajet;
```

```cpp
TrajetSimple(const char * laVilleDepart, const char * laVilleArrivee, moyenDeTransport leMoyen);
```
Constructeur de la classe trajet simple. Rien de spécial.

```cpp
virtual const char * VilleDepart () const;
```
Retourne la ville de départ.

```cpp
virtual const char * VilleArrivee () const;
```
Retourne la ville d’arrivee.

```cpp
virtual void Afficher () const;
```
Format d’affichage :
`« De {villeDepart} à {villeArrivee} en {moyenDeTransport} »`


```cpp
class TrajetCompose : public Trajet;
```

```cpp
TrajetCompose ( CollectionTrajets composants ) ;
```
Constructeur de la classe TrajetCompose.
Construit un trajet à partir d'une copie profonde d'une collection
de trajets.

```cpp
virtual const char * VilleDepart () const;
```
Retourne la ville de départ du premier trajet.

```cpp
virtual const char * VilleArrivee () const;
```
Retourne la ville d’arrivee du dernier trajet.

```cpp
virtual void Afficher () const;
```
Format d’affichage :
`« {trajet1.Afficher()} - {trajet2.Afficher()} - ...»`

```cpp
class CollectionTrajets; 
```

```cpp
CollectionTrajets ();
```
Constructeur par défaut. Les éléments de la collection sont des pointeurs sur Trajet et sont stockés dans un tableau dynamique de taille maximale définie par une constante.
La collection est vide et par conséquent la taille courante est de 0.
Les éléments sont ordonnés par ordre d'ajout grâce à la méthode AjouterTrajet.

```cpp
CollectionTrajets ( const CollectionTrajets & source );
```
Constructeur par copie de la classe CollectionTrajets
Construit une collection pleine à partir d'une autre collection.
Sa taille courante est la même que la taille de la collection passée en paramètre.

```cpp
void AjouterTrajet (const Trajet * trajet);
```
Ajoute un trajet dans la collection. Ce trajet se trouve à la suite du dernier trajet ajouter à la collection.
Contrat de cohérence : La ville de départ du trajet ajouté doit être la même que la ville d'arrivée du dernier trajet ajouté dans la collection.

```cpp
unsigned int NombreDeTrajets () const;
```
Retourne la taille courante de la collection et donc le nombre de trajets.

```cpp
const Trajet * TrajetNumero(unsigned int numero) const
```
Retourne le numero-ieme trajet dans la collection de trajets
(1 = premier trajet, ..., taille courante = NombreDeTrajets() = dernier trajet).
Contrat de performance : Si la collection est vide, cette méthode ne doit pas être appelé. Le numéro doit être compris entre 1 et la valeur retournée par NombreDeTrajets() incluse.

Version 2
