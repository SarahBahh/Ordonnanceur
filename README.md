# Ordonnanceur
# Information générale

Ce devoir a pour but de représenter un ordonnanceur à l'aide d'une file, il a été conçu par Sarah BAHHAR et Abdellah HASSANI.
 
Date: 08/12/22

Langage: C
# Installation

https://github.com/SarahBahh/Ordonnanceur.git

# Ordonnanceur

On veut ici représenté l'ordonnancement de processus. Dans notre cas c'est un ordonnancement avec priorité non préemptif. 
C'est à dire que les processus sont trié dans la file en fonction de leur priorité et que si un processus arrive à un temps 
t il n'interrompera pas l'execution du processus en cours.

# Contenu

## source

ordonnanceur.h
ordonnanceur.c

main.c

## bin

ordonnanceur.o

main.o

# Execution

make exe

# Make

make : pour compiler

make exe :  pour compiler et executer

make zip : pour compiler et compresser

make clean : pour compiler et enlever le fichier bin
