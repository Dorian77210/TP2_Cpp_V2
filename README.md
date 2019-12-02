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

nbTrajetSimple  nbTrajetCompose

Index type Départ ; arrivée ; moyenTranport / nbTrajet ;


Améliorations possibles : 

-	Gérer les chaines de caractères avec « string »
-	Entrée sortie pour les trajets
-	Surcharge operateur << et >>
-	Gérer les erreurs d’entrée (formatage)
-	Catalogue vide
-	Ajouter un paramètre pour savoir si le trajet est nouveau ou non

Fonctionnalités :

-	Menue de sauvegarde ou de restitution 
-	Sauvegarde fichier
-	Lire fichier
-	Filtres de recherche
- méthode pour recupérer le nombre de trajet simple et compose
- méthode dans la classe Trajet "Est" 
-Vider catalogue


Format du fichier de sauvegarde
Pour les trajets simples : 
N 1 {villeDepart};{villeArrivee};{moyenTransport}

Pour les trajets composés
N 2 {villeDepart};{villeArrivee}
    {trajets simples ou composés}

Vider catalogue



Idées pour le rapport :

# I. Sauvegarde des trajets

## 1. Présentation

La sauvegarde des trajets est une des principales fonctionnalités que nous avons développé durant cette deuxième phase. Elle permet de garder une trace de l'ensemble des trajets dans le catalogue de l'application courante. Une méthode Sauvegarder dans la classe Catalogue permet de sauvegarder une collection passé en paramètre. C'est donc cette méthode qui sera appelée lors des différents types de sauvegarde. Nous avons décidé d'avoir une seule méthode "générique" qui réalise vraiment la sauvegarde dans le fichier afin d'éviter la duplication de code. 
Lorsque l'utilisateur demande de sauvegarder le catalogue courant, nous lui demandons premièrement le nom de fichier de sauvegarde. Ensuite, on regarde si le fichier donné existe déjà, auquel cas on lui demande si il veut l'écraser. En fonction de son choix, le menu va lors lui présenter l'ensemble des sauvegardes prises en charge par l'application. C'est donc à ce moment que l'utilisateur va pouvoir choisir ce qui lui convient le mieux.

## 2. Types de sauvegarde

### a. Sauvegarde sans critère de sélection
Lors de la sauvegarde sans critère de sélection, l'application va appeler la méthode de signature sauvegarder(string nomFichier) qui va elle-même appeler la méthode "générique" de sauvegarde. Ce type de sauvegarde ne fait aucun tri sur la collection actuelle de trajets. Elle se content seulement de prendre en compte la collection courante et de la sauvegarder.

### b. Sauvegarde par type de trajets
Avant de sauvegarder les trajets, l'application va d'abords demander à l'utilisateur de faire le choix du type de trajets à sauvegarder. Si l'utilisateur saisit une mauvaise, le type de trajets choisi par défaut est les trajets simples.
Lors de la sauvegarde par type de trajets, l'application va appeler la méthode signature Sauvegarder(string nomFichier, TypeTrajet type)
. Cette méthode va d'abords filtrer la collection courante de trajets présente dans le catalogue. Pour cela, elle va appeler la méthode GetTrajetsParType de la classe CollectionTrajets. Cette méthode va donc lui retourner une collection de trajets contenant tous les trajets du type demandé par l'utilisateur. Une fois ceci fait, la méthode de Sauvegarde va appeler la méthode "générique" de sauvegarde avec la nouvelle collection obtenue.

### c. Sauvegarde par rapport à une ville de départ et/ou d'arrivée
Avant de sauvegarder les trajets, l'application va d'abords demander à l'utilisateur de saisir une ville de départ et/ou d'arrivée. Deux cas peuvent se produite : si la ville de départ et la ville d'arrivée ne sont pas valides (égales à "stop" car c'est cette chaîne là que l'utilisateur devra taper pour ne pas spécifier la ville courante), l'application appliquera la sauvegarde par défaut. Sinon, cela signifie qu'au moins une des deux villes est valide. L'application va appeler la méthode de signature Sauvegarder(string nomFichier, string depart, string arrivee). Cette méthode va d'abords filtrer la collection courante de trajets présente dans le catalogue. Pour cela, elle va appeler la méthode GetTrajetsParVilles de la classe CollectionTrajets. Cette méthode va donc lui retourner une collection de trajets contenant tous les trajets correspondant à la ville de départ et/ou d'arrivée. Une fois ceci, la méthode de Sauvegarde va appeler la méthode "générique" de sauvegarde avec la nouvelle collection obtenue.

### d. Sauvegarde par rapport à un intervalle
Si l'utilisateur a demandé à sauvegarder son catalogue courant de trajets dans un fichier par rapport à un interval, l'application va lui demander dans l'ordre :
* Le début de l'intervalle : Il s'agit du numéro du premier trajet que l'utilisateur veut sauvegarder. En cas de mauvaise saisie de la part de l'utilisateur (si l'utilisateur tape autre chose qu'un nombre ou qu'il donne un nombre supérieur au nombre de trajets effectivement présents dans le catalogue), le début de l'intervalle sera égal à une valeur par défaut (qui vaut 1). Note importante : la valeur de début de l'intervalle doit être supérieur ou égale à 1 et inférieure ou égale au nombre total de trajets présents dans le catalogue.
* Le fin de l'intervalle : Il s'agit du numéro du dernier trajet que l'utilisateur veut sauvegarder. Comme pour la valeur du début dl'intervalle, une valeur par défaut (qui est gal au nombre total de trajets) en cas de mauvaise saisie (si l'utilisateur tape autre chose qu'un nombre, que la valeur de fin est inférieure à celle du début ou que la valeur de fin est supérieure au nombre de trajets). Note importante : la valeur de fin de l'intervalle doit être supérieure ou égale au début de l'intervalle est inférieure ou égale au nombre total de trajets composant le catalogue.

Une fois que l'intervalle est correcte, l'application appelle une méthode de signature Sauvegarder(string nomFichier, int min, int max) qui va d'abords récupérer tous les trajets dans l'intervalle [min, max] à l'aide de la méthode GetTrajetsParIntervalle de la classe CollectionTrajets. Ensuite, elle appelle la méthode "générique" de sauvegarde avec la collection filtrée obtenue. 

# II. Restitution des trajets

## 1. Présentation 

La restitution des trajets est la deuxième et dernière fonctionnalité principale que nous avons développé lors de cette deuxième phase. Elle permet de reconstituer une collection de trajets à partir d'un fichier de sauvegarde. Cette fonctionnalité est assez symétrique par rapport à la sauvegarde. Comme pour cette-dernière, la classe Catalogue dispose d'une méthode avec la signature restituer(string nomFichier) qui est la seule méthode qui charge un fichier. Cette méthode "générique" sera appeler par les autres méthodes de restitution avec ou sans critères spécifiques. Son but est de lire tout le contenu d'un fichier et de restituer tous les trajets qui y sont présents. C'est donc aux autres méthodes de restitution qui s'occuperont de filtrer la collection de trajets obtenue via le fichier.

Lorsque l'utilisateur demande de restituer un fichier, nous lui demandons premièrement le nom de fichier possèdant le catalogue qui l'intéresse. Ensuite, on regarde si le fichier donné existe déjà. Si c'est la cas, on lui demande le type de restitution qu'il souhaite. Sinon, on lui demande un nouveau nom de fichier jusqu'à obtenir un fichier qui existe. Une fois ceci fait, l'application lui dmeande le type de restitution qu'il souhaite faire.

## 2. Types de restitution

### a. Restitution sans critères de sélection

Lors de la restitution sans critères de sélection, l'application va demander au catalogue de restituer le fichier passé à la ligne de commande via la méthode Restituer(string nomFichier). Cette méthode va récupérer via la méthode "générique" de restitution l'ensemble des trajets présents dans le fichier. Ensuite, elle va rajouter tous les trajets dans le catalogue courant.

### b. Restitution par type de trajets

Lors de la resitution par type de trajets, l'application va demander au catalogue de restituer le fichier passé à la ligne de commande via la méthode Restituer(string nomFichier, TypeTrajet
