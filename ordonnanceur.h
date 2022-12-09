#ifndef H_ORDONNANCEUR
#define H_ORDONNANCEUR
//on definit notre structure de processus
typedef struct processus{
   char nom[20];
   int duree;
   int priorite;
}processus;
//on definit notre structure pour les elements de la file
typedef struct elementdelafile{
   struct processus process;
   struct  elementdelafile *suivant;
}elementdelafile;
//on definit notre structure qui nous permettera de garder le premier element de la file
typedef struct Premier{
   struct elementdelafile *premier;
}File;

File *initialiser();
void ajout_activite(processus activite, File *premier);
void Remplirfile(File *premier);
void step(File *premier);
void run(File *premier);
void trierFile(File *file);
int nonpreemptif(File *premier);
#endif 
