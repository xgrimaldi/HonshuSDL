# PROJET INFO 1A - HONSHU

## Lancement du programme honshu V2

* Ouvrir le bash et faites un cd dans le dossier "bin"
* Exécuté le fichier "honshu" (1er paramètre pour donner le fichier Tuiles)

```
./honshu Tuiles

ou

./honshu
```

* Choix des programmes à éxécuter

## Ajouter le projet sur votre ordinateur (LINUX !!)

* Ouvrir un terminal BASH
* Faites un cd dans le dossier de votre choix, dans le terminal:

```
cd ~/Documents/ENSIIE/PROJET_INFO
```
        
* Importation du projet dans le répertoire:
* Copier le lien du projet puis dans le terminal ==> git clone leliencopié

```
Ex: 
git clone http://pedago-etu.ensiie.fr/xavier.grimaldi/Les_Tuileurs_Projet.git
```

* Il vous sera demandé de rentrer votre identifiant GIT et votre mot de passe après.
```
ex: xavier.grimaldi (pour moi)
ex: puis mon mdp
```

## Obtenir les dernières mise à jour

* Se rendre à la base du dossier projet sur votre ordinateur
* Exécuter la commande suivante dans le bash:

```
git pull
```

## Ajouter du contenu au projet
* Se rendre à la base du dossier projet sur votre ordinateur
* Exécuter la commande suivante dans le bash:

```
git add .
git commit -m "Message de votre choix ex: Mise à jour honshu V3"
git push
```

## Compiler les fichiers à l'aide du makefile

* Makefile à alimenter en fonction des avancement du projet
* Ouvrir un bash 
* Faites un cd dans le dossier contenant le makefile:

```
cd ~/Documents/ENSIIE/PROJET_INFO
```

* Executer le makefile en tapant:

```
make
```

## Construction des dossiers

* Les fichiers exécutable sont présents dans le dossier "bin"
* Les fichiers .c .h sont présents dans le fichier "src"
* Les fichiers .o sont présents dans le fichier "obj"

## Installer la libraire CUnit pour effectuer les tests

* Ouvrir un terminal BASH
* Télécharger les librairies:

```
sudo apt-get install libcunit1 libcunit1-doc libcunit1-dev
```
* Le fichier make comprend la création d'un fichier de test exécutable dans le dossier "bin"
