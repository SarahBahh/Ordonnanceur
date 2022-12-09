#include <stdio.h>
#include <stdlib.h>
#include "ordonnanceur.h"


int main(){
   int a;
   //on initialise la file
   File *maFile = initialiser();
   //on demande a l'utilisateur d'entrer les processus qu'il veut executer et on les entre dans la file
   Remplirfile(maFile);
   //on trie la file de processus
   trierFile(maFile);
   //on execute le premier processus de la file d'il existe un sinon on prévient que la file est vide
   step(maFile);
   /*on demande à l'utilisateur s'il souhaite ajouter des processus
   s'il ne souhaite plus jamais en ajouter il suffit de taper 0
   s'il souhaite en ajouter il suffit de 1 
   s'il souhaite en ajouter plus tard il suffit de taper 2
   et on le stock dans la variable a*/
   a=nonpreemptif(maFile);
   //on demande à chaque fin d'execution d'un processus si l'utilisateur souhaite ajouter des processus et on execute le prochain processus
   while(a==1||a==2){
      step(maFile);
      a=nonpreemptif(maFile);
   }
   //une fois que l'utilisateur à taper 0 on execute tout les processus restant dans la file
   run(maFile);
   free(maFile);
   return(0);
}