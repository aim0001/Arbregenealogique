#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// 1°) ===============================================================================================
typedef struct Person Person;
struct Person{
    char prenom[20];
    int age;
    Person *frere_soeur;
    Person *fils;
};
typedef struct Arbre Arbre;
struct Arbre{
    Person *racine;
};
void init_arbre (Arbre *A){
    A->racine=NULL;
}
// 2°) ===============================================================================================
Person *rechercher(Arbre *A,char prenom[20]){
    if(strcmp(A->racine->prenom,prenom)==0){
        return A->racine;
    }
    Person *brother_sister = A->racine->frere_soeur;
    Person *kid = A->racine->fils;
    Person *resultat = NULL;
    while(brother_sister != NULL && resultat == NULL){
        resultat = rechercher(brother_sister,prenom);
        brother_sister = brother_sister->frere_soeur;
    }
    while(kid != NULL && resultat == NULL){
        resultat = rechercher(kid,prenom);
        kid = kid ->fils;
    }
    return resultat;
}
void ajout_membre(Arbre *A,char nomP[20],int age,char prenom[20],char typedAffiliation[20]){
    Person *parentRechercher = NULL;
    Person *nouveau = malloc(sizeof(Person));
    strcpy(nouveau->prenom , prenom);
    nouveau->age = age;
    nouveau->frere_soeur = NULL;
    nouveau->fils = NULL;
    if(A->racine == NULL){
        A->racine = nouveau;
        typedAffiliation = NULL;
        nomP = NULL;
    }
    else{
        parentRechercher = rechercher(A->racine,nomP);
        if(strcmp(typedAffiliation,"frere_soeur") == 0){
            if(parentRechercher != NULL){
                Person *frere_soeur = parentRechercher->frere_soeur;
                if(frere_soeur == NULL){
                    parentRechercher->frere_soeur = nouveau;
                } else {
                    while(frere_soeur->frere_soeur != NULL){
                        frere_soeur = frere_soeur->frere_soeur;
                    }
                    frere_soeur->frere_soeur = nouveau;
                    }
                }else printf("Ce parent n existe pas sur l arbre.\n");
        }
                if(strcmp(typedAffiliation,"enfant") == 0){
                    nomP = NULL;
                    if(parentRechercher != NULL){
                        Person *fils = parentRechercher->fils;
                        if(fils == NULL){
                            parentRechercher->fils = nouveau;
                        } else{
                            while(fils->frere_soeur != NULL){
                                fils = fils->frere_soeur;
                            }
                            fils->frere_soeur = nouveau;
                        }
                    } else printf("Ce parent n existe pas sur l arbre.\n");
                }

        }
}

// 3°) ===============================================================================================
int est_membre(Arbre *A,char prenom[20]){
    if(A->racine=NULL){
        return 0;
    }
    if(strcmp(A->racine->prenom,prenom)==0){
        return 1;
    }
    else {
        return est_membre(A->racine->frere_soeur,prenom) || est_membre(A->racine->fils,prenom);
    }
}
//4°) ===============================================================================================
void frere (Arbre *A,char prenom[20]){
    if(A->racine == NULL) printf("L arbre est vide \n");
    else{
         if(est_membre(A->racine,prenom) == 1){
            Person *sauvFrere = A->racine->frere_soeur;
            do{
                printf("%s\t %d ans\n\n",sauvFrere->prenom,sauvFrere->age);
                sauvFrere = sauvFrere->frere_soeur;
            }
            while(sauvFrere!=NULL);
        }
        if(est_membre(A->racine->fils,prenom) == 1){
            Person *sauvFrerefils = A->racine->fils->frere_soeur;
            do{
                printf("%s\t %d ans\n\n",sauvFrerefils->prenom,sauvFrerefils->age);
                sauvFrerefils = sauvFrerefils->frere_soeur;
            }
            while(sauvFrerefils!=NULL);
        }
    }

}
// 5°) ====================================================================================================
void enfants (Arbre *A,char prenom[20]){
    if(A->racine == NULL) printf("L arbre est vide \n");
    else{
         if(est_membre(A->racine,prenom) == 1){
            Person *sauvFils = A->racine->fils;
            do{
                printf("%s\t %d ans\n\n",sauvFils->prenom,sauvFils->age);
                sauvFils = sauvFils->fils;
            }
            while(sauvFils!=NULL);
        }
        if(est_membre(A->racine->frere_soeur,prenom) == 1){
            Person *sauvfils = A->racine->frere_soeur->fils;
            do{
                printf("%s\t %d ans\n\n",sauvfils->prenom,sauvfils->age);
                sauvfils = sauvfils->fils;
            }
            while(sauvfils!=NULL);
        }
    }
}
// 6°) ======================================================================================================
void parent(Arbre *A,char prenom[20]){
    if(A->racine == NULL) printf("L arbre est vide \n");
    else{
        if(strcmp(A->racine->prenom,prenom)==0) printf("Cette personne n a pas de parent \n");
        Person *p = A->racine;
        while(p != NULL){
            if(p->fils != NULL){
                if(strcmp(p->fils->prenom,prenom) == 0){
                    printf("%s\t %d ans\n\n",p->prenom,p->age);
                }
            }
            p = p->fils;
        }
        printf("le parent n existe pas dans l arbre\n");
    }
}
// 7°) ==============================================================================================
void affiche_arbre(Arbre *A){
    if(A->racine == NULL) printf("L arbre est vide\n");
    else{
        printf("%s, %d\n",A->racine->prenom,A->racine->age);
        if(A->racine->frere_soeur != NULL)
        {affiche_arbre(A->racine->frere_soeur);
        }
        if(A->racine->fils != NULL){
            printf("............");
            affiche_arbre(A->racine->fils);
        }
    }
}
// 8°) ==============================================================================================
int main()
{
Arbre *A;
init_arbre(&A);
int choix;
char prenom[50];
char nom_membre[20];
char affiliation[20];
char nom_parent[20];
int age_membre;
int age;
    printf("Menu :\n");
    printf("1- Ajouter un membre\n");
    printf("2- Verifier si le membre existe dans l'arbre\n");
    printf("3- Afficher les freres et soeurs d'un membre\n");
    printf("4- Afficher les enfants d'un membre\n");
    printf("5- Afficher le parent direct d'un membre\n");
    printf("6- Afficher l'arbre genealogique\n");
    printf("7- Quitter\n");
    while (choix != 7){
    printf("\n\nVeillez choisir une option : ");
    scanf("%d", &choix);
    switch (choix) {
      case 1 :
        if(A == NULL){
        printf("Entrez le nom du membre: ");
        scanf("%s",nom_membre);
        printf("Entrez l'age du membre: ");
        scanf("%d",&age_membre);
        ajout_membre(&A, nom_parent , age_membre, nom_membre, affiliation);
        printf("\nMembre ajouter avec succes\n");
        }
        else{
        if(A != NULL){
            printf("Entrez le nom du membre: ");
            scanf("%s",nom_membre);
            printf("Entrez l'age du membre: ");
            scanf("%d",&age_membre);
            printf("Entrez le type d affiliation(frere_soeur ou enfant): ");
            scanf("%s",affiliation);
            if(strcmp(affiliation,"enfant") == 0){
                printf("Entrez le nom du parent: ");
                scanf("%s",nom_parent);
            }
            ajout_membre(&A, nom_parent , age_membre, nom_membre, affiliation);
            printf("\nMembre ajouter avec succes\n");
        }
        }
        break;
      case 2:
        printf("Entrez le prenom a rechercher :\n");
        scanf("%s",prenom);
        est_membre(&A, prenom);
        break;
      case 3:
        // Afficher les fr�res et s�urs d'une personne//
        printf("Entrer le nom de la personne dont vous voulez voire les frere et soeur: ");
        scanf("%s", prenom);
  frere(&A, prenom );

        break;
      case 4:
      // Afficher les enfants d'une personne//
  printf("Entrer le nom de la personne dont vous voulez voire ses enfants: ");
  scanf("%s", prenom);
  printf("Ses enfants sont :\n");
  enfants(&A, prenom);
        break;
      case 5:
      // Afficher le parent direct d'une personne//
        printf("Entrer le nom de la personne dont vous voulez voire son parent: ");
        scanf("%s", prenom);
        parent(&A, prenom);
        break;
      case 6:
        // Afficher l'arbre g�n�alogique
        printf("Arbre genealogique :\n");
        affiche_arbre(&A);
        break;
      case 7:
        printf("Au revoir !\n");
        break;
      default:
        printf("Choix invalide. Veuillez reessayer.\n");
    return 0;
    }
  }
}
