#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct maillon{
    char nom[30];
    struct maillon *suiv;
} SYMPTOME;

void AfficherMaillon(SYMPTOME*);
SYMPTOME* LireFichier(FILE *fic);
void EcrireFichier(FILE*, SYMPTOME*);

void AfficherMaillon(SYMPTOME *pt_tete)
{
  if (!pt_tete)
  {
    printf("\nLa liste est vide!");
    while(pt_tete)
    {
        printf("\nNom : %s", pt_tete->nom);
        pt_tete = pt_tete->suiv;
    }
  }
}

SYMPTOME* LireFichier(FILE *fic){
  SYMPTOME tmp;
  SYMPTOME *pt_tete = NULL;
  SYMPTOME *pt_nouveau = NULL;

  fseek(fic, 0, SEEK_SET);
  memset(&tmp, '\0', sizeof(SYMPTOME));

  while(fread(&tmp, sizeof(SYMPTOME), 1, fic))
  {
      if(!(pt_nouveau = (SYMPTOME*)malloc(sizeof(SYMPTOME))))
      {
          printf("\nErreur a la creation du maillon.");
          break;
      }
      else
      {
          *pt_nouveau = tmp;
          pt_nouveau->suiv = NULL;
          //AfficherMaillon
          memset(&tmp, '\0', sizeof(SYMPTOME));
      }
  }
}

void EcrireFichier(FILE *fic, SYMPTOME *pt_tete)
{
  int i = 0;
  while(pt_tete)
  {
    i = fwrite(pt_tete, sizeof(SYMPTOME), 1, fic);
    if (i != 1)
    {
        print("\nErreur à l'écriture");
        break;
    }
      pt_tete = pt_tete->suiv;
  }
}

int main(void)
{
   int fin;



   fin = 0;
   while(!fin)
   {
      int c;

      /* affichage menu */
      printf("1.Effectuer un diagnostique 1\n"
             "2.Administrer la base de faits 2\n"
             "3.Administrer la base de regles 3\n"
             "4.Quitter\n");

      c = getchar();

      /* suppression des caracteres dans stdin */
      if(c != '\n' && c != EOF)
      {
         int d;
         while((d = getchar()) != '\n' && d != EOF);
      }

      switch(c)
      {
         case '1':
            printf("Choix 1\n");
            break;



         case '2':
            printf("Choix 2\n");
            break;



         case '3':
            printf("Choix 3\n");
            break;



         case '4':
            fin = 1;
            break;



         default:
            printf("Choix errone\n");
      }
   }

   return 0;
}
