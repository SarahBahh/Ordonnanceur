#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "ordonnanceur.h"

//Cette fonction sert à initialiser la file de processus
File *initialiser()
{
    //on alloue dynamiquement de la mémoire notre file
    File *file = malloc(sizeof(*file));
    //on donne la valeur NULL au premier element de la file
    file->premier = NULL;
    //on retourne la file 
    return file;
}

// Cette procedure sert à ajouter des processus dans la file
void ajout_activite(processus activite, File *maFile){
   
   elementdelafile *nouveau;
   //on alloue dynamiquement de la mémoire au nouvel element de notre file
   nouveau = malloc(sizeof(*nouveau));
   //si jamais cette allocation dynamique a échouer on sort
   if (maFile == NULL || nouveau==NULL){
      exit(EXIT_FAILURE);
   }
   //on implémente les objets de notre file avec le processus mis en argument de la procedure
   nouveau->process = activite;
   nouveau->suivant=NULL;
   //si la file n'est pas vide
   if (maFile->premier!=NULL){
      elementdelafile *curseur= maFile->premier;
      //on se met au bout de la file pour y ajouter le nouveau processus
      while(curseur->suivant!=NULL){
         curseur=curseur->suivant;
      }
      //on ajoute le nouveau processus en bout de file
      curseur->suivant = nouveau;
   }
   //si la file est vide on ajoute le nouveau processus en premier element
   else{
   maFile->premier=nouveau;
   }
}

// Cette procedure permet à l'utilisateur d'entrer les processus qu'il souhaite executé
void Remplirfile(File *maFile){
   int nbprocessus,i;
   processus votreprocessus;
   printf("Combien de processus voulez-vous ajouter à la file ?\n");
   scanf("%d",&nbprocessus);
   if(nbprocessus!=0){
      // on demande à l'utilisateur d'entrer le nom, la durée et la priorité qu'il souhaite dans son processus
      for(i=0;i<nbprocessus;i++){
         printf("Entrer le nom de votre processus\n");
         scanf("%s",votreprocessus.nom);
         printf("Entrer la durée de votre processus\n");
         scanf("%d",&votreprocessus.duree);
         printf("Entrer la priorité entre 0 et 5 de votre processus\n");
         scanf("%d",&votreprocessus.priorite);
         while(votreprocessus.priorite<0||votreprocessus.priorite>5){
            printf("La priorité entrée n'est pas comprise entre 0 et 5 réessayez\n");
            scanf("%d",&votreprocessus.priorite);
         }
         //on ajoute le nouveau processus crée à la file mise en argument de la procedure
         ajout_activite(votreprocessus, maFile);
     }
  }
}

/* Cette fonction permet de demander à l'utilisateur s'il souhaite ajouté des processus à la file, 
elle se déclenchera à chaque fois qu'un processus sera executé et s'arretera quand l'utilisateur l'aura notifié en tapant 0*/
int nonpreemptif(File *maFile){
   int a;;
   printf("Voulez-vous ajouter des processus à la file de l'ordonnanceur ?\n");
   printf("Tapez 0 pour arreter définitivement l'ajout de nouveaux processus\n");
   printf("Tapez 1 pour ajouter de nouveaux processus\n");
   printf("Tapez 2 pour avoir la possibilité de rajouter des processus à la file plus tard\n");
   scanf("%d",&a);
   switch (a)
   {
   //si l'utilisateur ne souhaite plus entrer de processus à executer il tape 0
   case 0 :
      printf("Nous allons poursuivre l'execution des processus deja présent dans la file s'il y en a et n'allons plus vous demander si vous voulez ajouter plus tard\n");
      return(0);
      break;
   //si l'utilisateur souhaite entrer de nouveau processus il tape 1
   case 1 :
      //on va integrer ce ou ces nouveau processus crée à notre file
      Remplirfile(maFile);
      //et on va retrier la file en fonction des priorité
      trierFile(maFile);
      return(1);
      break;
    case 2 :
    printf("Nous vous redemanderons si vous voulez ajouter des processus après l'execution du prochain\n");
      return(2);
      break;  
}
}

//Cette procédure permet d'executer un processus
void step(File *maFile){
   //si la file est vide on le dit
   if(maFile->premier==NULL){
      printf("la file est vide\n");
        }
   //on crée un processus et on l'initialise
   processus processusexecute={" ",0,0} ;
   if(maFile->premier!=NULL){
      //on cree un element de la file temporaire qui va nous permettre de changer le premier element de la file une fois qu'il sera execute
      elementdelafile *element=maFile->premier;
      //on prend un processus qui contiendra les information du processus pour l'execution
      processusexecute=element->process;
      /*on execute le processus en affichant son nom sa duree et en attendant la duree d'execution du processus*/
      printf("Le nom de ce processus est %s ",processusexecute.nom);
      printf("et sa durée est de %d secondes\n",processusexecute.duree);
      sleep(processusexecute.duree);
      //on change le premier element de la file par le suivant
      maFile->premier=element->suivant;
      //on vide le processus car il a ete execute
      free(element);
   }
}
//Cette fonction execute tout les processus de la file un à un
void run(File *maFile){
   //tant que la file n'est pas vide on execute le premier processus de la file
   while(maFile->premier!=NULL){
      step(maFile);
   }
}

//Cette procedure permet de trier la file de processus en fonction des priorité dans l'ordre croissant on utilise le tri par selection
 void trierFile(File *maFile){
//on cree deux element de la file qui vont nous permettre de faire les comparaison, temp1 pointe sur le premier element de la file
      elementdelafile *temp1 =  maFile->premier, *temp2 = NULL;
      //on alloue dynamiquement de la mémoire une variable processus temporaire
      processus *temp = (processus *)malloc(sizeof(processus));
      //si la file est vide on quitte la fonction
      if(maFile==NULL){
         return;
      }
      else {
      //tant que temp1 n'est pas nul
         while(temp1!= NULL) {
         //temp2 pointe sur l'element qui suit temp1  
         temp2 = temp1->suivant;
         //tant que temp2 n'est pas nul
            while(temp2!=NULL){
               //Si la priorite de temp 1 est plus grande que celle de temp2, on enchange les processus contenu dedans
               if(temp1->process.priorite>temp2->process.priorite)
               {
                  *temp=temp1->process;
                  temp1->process=temp2->process;
                  temp2->process=*temp;
               }
               //temp2 pointe sur l'element suivant et on continue les comparaicon avec notre nouveau minimum 
               temp2=temp2->suivant;
               }
               //temp1 pointe sur le processus suivant et on recommence les comparaison pour trouver le prochain element le plus petit de la file
               temp1=temp1->suivant;
               }
            }
      free(temp);
      }
