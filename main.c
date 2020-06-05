#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct maillon{
    char nom[30];
    struct maillon *suiv;
} SYMPTOME;

SYMPTOME* CreerMaillon();
SYMPTOME* InsererMaillonEnTete(SYMPTOME*, SYMPTOME*);
void AfficherMaillon(SYMPTOME*);
void LireFichier(FILE *fic);
void EcrireFichier(FILE*, SYMPTOME*);
bool Rechercher(FILE*, char[30]);

SYMPTOME* CreerMaillon(){
  SYMPTOME *pt_maillon = NULL;

  pt_maillon = (SYMPTOME*)malloc(sizeof(SYMPTOME));

  printf("Veuillez entrer un nouveau symptome à la base : ");
  scanf("%s", pt_maillon->nom);

  pt_maillon->suiv = NULL;

  return pt_maillon;
}

SYMPTOME* InsererMaillonEnTete(SYMPTOME *pt_tete, SYMPTOME *nouveau)
{
    nouveau->suiv = pt_tete;
    return nouveau;
}


void AfficherMaillon(SYMPTOME *pt_tete)
{
  if (!pt_tete)
    printf("\nLa liste est vide!");
  while(pt_tete)
  {
      printf("\nNom : %s", pt_tete->nom);
      pt_tete = pt_tete->suiv;
  }
}

void LireFichier(FILE *fic){
  SYMPTOME tmp;

  fseek(fic, 0, SEEK_SET);
  memset(&tmp, '\0', sizeof(SYMPTOME));

  while(fread(&tmp, sizeof(SYMPTOME), 1, fic))
  {
      printf("%s\n", &(tmp.nom));
  }
}

bool Rechercher(FILE *fic, char to_find[30]){
  SYMPTOME tmp;

  fseek(fic, 0, SEEK_SET);
  memset(&tmp, '\0', sizeof(SYMPTOME));

  while(fread(&tmp, sizeof(SYMPTOME), 1, fic))
  {
      if(strcmp(&(tmp.nom), to_find) == 0)
      {
        return true;
      }
  }
    return false;
}


void EcrireFichier(FILE *fic, SYMPTOME *pt_tete)
{
  int i = 0;
  while(pt_tete)
  {
    i = fwrite(pt_tete, sizeof(SYMPTOME), 1, fic);
    if (i != 1)
    {
        printf("\nErreur à l'écriture");
        break;
    }
      pt_tete = pt_tete->suiv;
  }
}

int main()
{

   SYMPTOME *pt_tete_symptomes, *nouvel_element = NULL;
   int fin;

   fin = 0;

   printf("Hope");

   while(fin != 1)
   {
      int c;

      /* affichage menu */
      printf("1.Effectuer un diagnostique 1\n"
             "2.Administrer la base de faits 2\n"
             "3.Administrer la base de regles 3\n"
             "5.Inserer nouveau symptome dans la bd_symptomes\n"
             "6.Afficher la bd_symptomes\n"
             "7.Chercher symptome dans la bd de symptomes\n"
             "0.Quitter\n");

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
            //fin = 1;
            break;

        case '5':
          {
            SYMPTOME *pt_tete, *nouvel_element = NULL;

            bool insert = true;

            pt_tete = CreerMaillon();
            char choix;

            FILE *f = fopen("bd_symptomes.txt", "a+");
            if (f == NULL)
            {
                printf("Error opening file!\n");
                exit(1);
            }

            while (insert){
              printf("Voulez-vous ajouter un nouvel symptome? (o/n)");
              scanf(" %c", &choix);
              if (choix == 'o')
              {
                nouvel_element = CreerMaillon();
                pt_tete = InsererMaillonEnTete(pt_tete, nouvel_element);
              } else {
                insert = false;
              }
            }

            AfficherMaillon(pt_tete);
            EcrireFichier(f, pt_tete);
            fclose(f);
            break;

          }

          case '6':
          {
            FILE *f = NULL;
            f = fopen("bd_symptomes.txt", "r");
            LireFichier(f);
            fclose(f);
          }

          case '7':
          {
            FILE *f = NULL;
            f = fopen("bd_symptomes.txt", "r");
            char symptome_a_chercher[30];
            printf("Veuillez entrer le symptome à chercher : ");
            scanf("%s", symptome_a_chercher);
            bool resultat = Rechercher(f, symptome_a_chercher);
            if(resultat)
              printf("Trouvé!");
            else
              printf("Non trouvé!");
            fclose(f);
          }

         case '0':
            fin = 1;
            break;

         default:
            printf("Choix errone\n");
      }
   }

   return 0;
}
