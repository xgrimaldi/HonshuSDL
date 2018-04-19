# PROJET INFO ENSIIE 1A - SOLVEUR HONSHU
##### Xavier GRIMALDI, Houda HASSINI, Johan CHAGNON, Quentin DELAVELLE

# I ) Pré-requis

### Installer SDL 2.0

* Ouvrir un terminal
* Cette commande permet de visualiser toutes les librairies disponibles:

```
apt-cache search ^libsdl2
```

* Pour Honshu, nous aurons besoin des librairies suivantes:
    1. libsdl2-2.0-0 - bibliothèque Simple DirectMedia Layer
    2. libsdl2-dev - Fichiers de développement Simple DirectMedia Layer
    3. libsdl2-image-2.0-0 - Image loading library for Simple DirectMedia Layer 2, libraries
    4. libsdl2-image-dev - Image loading library for Simple DirectMedia Layer 2, development files
    5. libsdl2-mixer-2.0-0 - Mixer library for Simple DirectMedia Layer 2, libraries
    6. libsdl2-mixer-dev - Mixer library for Simple DirectMedia Layer 2, development files
    7. libsdl2-ttf-2.0-0 - TrueType Font library for Simple DirectMedia Layer 2, libraries
    8. libsdl2-ttf-dev - TrueType Font library for Simple DirectMedia Layer 2, development files

* Installer les libraires via cette commande

```
 sudo apt-get install libsdl2-2.0-0 libsdl2-dev libsdl2-image-2.0-0 libsdl2-image-dev libsdl2-mixer-2.0-0 libsdl2-mixer-dev libsdl2-ttf-2.0-0 libsdl2-tff-dev
```


### Installer doxygen

* Ouvrir un terminal
* Télécharger doxygen:

```
sudo apt-get install doxygen
```

* Pour mettre à jour le doxygen, faire un cd dans le dossier doxygen du projet
* Puis executer la commande

```
doxygen Doxyfile
```

* Le Doxyfile comprend tous les paramètres du doxygen dont: l'input et l'output directory


### Installer la libraire CUnit pour effectuer les tests

* Ouvrir un terminal BASH
* Télécharger les librairies:

```
sudo apt-get install libcunit1 libcunit1-doc libcunit1-dev
```
* Le fichier make comprend la création d'un fichier de test exécutable dans le dossier "bin"

### Construction des dossiers

* Les fichiers exécutable sont présents dans le dossier "bin"
* Les fichiers .c .h sont présents dans le fichier "src"
* Les fichiers .o sont présents dans le fichier "obj"

# II) Démarrer le programme HONSHU
### Compiler les fichiers à l'aide du makefile

* Le makefile devra être alimenter en fonction des avancement du projet
* Ouvrir un terminal
* Faites un cd dans le dossier contenant le makefile:

```
cd ~/Documents/ENSIIE/Les_Tuileurs_Honshu
```

* Executer le makefile en tapant:

```
make
```

* Cette opération permettra de créer le fichier exécutable dans le bin

### Lancer le programme HONSHU

* Ouvrir le bash et faites un cd dans le dossier "bin"
* Exécuté le fichier "honshu"

```
./honshu
```

### Choix possibles dans le programme
* Dans le menu principale, il est possible de sélectionner 2 modes
* 1 - Création d'une partie personnalisée
* 2 - Création d'une partie à partir d'un fichier
* 3 - Lancement d'une partie graphique (SDL)


# III) HOW-TO USE GIT
### Ajouter le projet sur votre ordinateur (LINUX !!)

* Ouvrir un terminal BASH
* Faites un cd dans le dossier de votre choix, dans le terminal:

```
cd ~/Documents/ENSIIE/PROJET_INFO
```
        
* Importation du projet dans le répertoire:
* Copier le lien du projet puis dans le terminal ==> git clone leliencopié

```
Ex: 
git clone https://gitlab.com/Sphinx06/Les_Tuileurs_Honshu.git
```

* Il vous sera demandé de rentrer votre identifiant GIT et votre mot de passe après.
```
ex: Sphinx06 (pour moi)
ex: puis mon mdp
```

### Obtenir les dernières mise à jour

* Se rendre à la base du dossier projet sur votre ordinateur
* Exécuter la commande suivante dans le bash:

```
git pull
```

### Ajouter du contenu au projet
* Se rendre à la base du dossier projet sur votre ordinateur
* Exécuter la commande suivante dans le bash:
* NOTE: Le fichier .gitignore permet de ne pas synchroniser les dossiers/fichiers souhaités

```
git add .
git commit -m "Message de votre choix ex: Mise à jour honshu V3"
git push
```
