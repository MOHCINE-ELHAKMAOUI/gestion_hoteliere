#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include"Structures.h"


static unsigned int NB_Nourritures = 0 ; 
static unsigned int CNourritures = 0 ;
static Nourritures * TNourritures = NULL ;

#define FICHIER_NOURRITURE "nourritures.dat"

// sauvegarder dans un fichier
void sauvegarderNourritures() {
    FILE *f = fopen(FICHIER_NOURRITURE, "wb");
    if (!f) {
        printf("Erreur d'ouverture du fichier pour sauvegarde.\n");
        return;
    }
    fwrite(&NB_Nourritures, sizeof(unsigned int), 1, f);
    for (unsigned i = 0; i < NB_Nourritures; i++) {
        fwrite(&TNourritures[i].id_Nourriture, sizeof(unsigned), 1, f);
        fwrite(TNourritures[i].Nom_Nourriture, sizeof(char), 50, f);
        fwrite(TNourritures[i].Type_Nourriture, sizeof(char), 30, f);
        fwrite(TNourritures[i].Description_Nourriture, sizeof(char), 100, f);
        fwrite(&TNourritures[i].Prix_Total, sizeof(double), 1, f);
    }
    fclose(f);
}

// charger les nourritures depuis un fichier
void chargerNourritures() {
    FILE *f = fopen(FICHIER_NOURRITURE, "rb");
    if (!f) return;

    fread(&NB_Nourritures, sizeof(unsigned int), 1, f);
    TNourritures = malloc(NB_Nourritures * sizeof(Nourritures));
    
    for (unsigned i = 0; i < NB_Nourritures; i++) {
        fread(&TNourritures[i].id_Nourriture, sizeof(unsigned), 1, f);
        TNourritures[i].Nom_Nourriture = malloc(50);
        fread(TNourritures[i].Nom_Nourriture, sizeof(char), 50, f);
        TNourritures[i].Type_Nourriture = malloc(30);
        fread(TNourritures[i].Type_Nourriture, sizeof(char), 30, f);
        TNourritures[i].Description_Nourriture = malloc(100);
        fread(TNourritures[i].Description_Nourriture, sizeof(char), 100, f);
        fread(&TNourritures[i].Prix_Total, sizeof(double), 1, f);
    }
    fclose(f);
}

// saisir une nourriture
void saisirNourriture(Nourritures *n) {
    printf("\nID Nourriture : ");
    scanf("%u", &n->id_Nourriture);
    getchar();

    n->Nom_Nourriture = malloc(50);
    printf("Nom : ");
    fgets(n->Nom_Nourriture, 50, stdin);
    n->Nom_Nourriture[strcspn(n->Nom_Nourriture, "\n")] = 0;

    n->Type_Nourriture = malloc(30);
    printf("Type : ");
    fgets(n->Type_Nourriture, 30, stdin);
    n->Type_Nourriture[strcspn(n->Type_Nourriture, "\n")] = 0;

    n->Description_Nourriture = malloc(100);
    printf("Description : ");
    fgets(n->Description_Nourriture, 100, stdin);
    n->Description_Nourriture[strcspn(n->Description_Nourriture, "\n")] = 0;

    printf("Prix : ");
    scanf("%lf", &n->Prix_Total);
}

// ajouter une nourriture
void ajouterNourriture() {
    NB_Nourritures++;
    TNourritures = realloc(TNourritures, NB_Nourritures * sizeof(Nourritures));
    printf("\nAjout d'une nouvelle nourriture :\n");
    saisirNourriture(&TNourritures[NB_Nourritures - 1]);
    sauvegarderNourritures();
}

// supprimer une nourriture
void supprimerNourriture(unsigned id) {
    for (unsigned i = 0; i < NB_Nourritures; i++) {
        if (TNourritures[i].id_Nourriture == id) {
            free(TNourritures[i].Nom_Nourriture);
            free(TNourritures[i].Type_Nourriture);
            free(TNourritures[i].Description_Nourriture);

            for (unsigned j = i; j < NB_Nourritures - 1; j++) {
                TNourritures[j] = TNourritures[j + 1];
            }

            NB_Nourritures--;
            TNourritures = realloc(TNourritures, NB_Nourritures * sizeof(Nourritures));
            sauvegarderNourritures();
            printf("Nourriture supprimée.\n");
            return;
        }
    }
    printf("Nourriture non trouvée.\n");
}

// modifier une nourriture
void modifierNourriture(unsigned id) {
    for (unsigned i = 0; i < NB_Nourritures; i++) {
        if (TNourritures[i].id_Nourriture == id) {
            printf("Modification de la nourriture :\n");
            saisirNourriture(&TNourritures[i]);
            sauvegarderNourritures();
            return;
        }
    }
    printf("Nourriture non trouvée.\n");
}

// lister les nourritures
void listerNourritures() {
    printf("\nListe des nourritures :\n");
    for (unsigned i = 0; i < NB_Nourritures; i++) {
        printf("ID: %u, Nom: %s, Type: %s, Description: %s, Prix: %.2f\n",
               TNourritures[i].id_Nourriture, TNourritures[i].Nom_Nourriture,
               TNourritures[i].Type_Nourriture, TNourritures[i].Description_Nourriture,
               TNourritures[i].Prix_Total);
    }
}

// afficher le menu
void menuNourritures() {
    int choix;
    do {
        printf("\n===== MENU =====\n");
        printf("1. Ajouter une nourriture\n");
        printf("2. Supprimer une nourriture\n");
        printf("3. Modifier une nourriture\n");
        printf("4. Lister les nourritures\n");
        printf("0. Quitter\n");
        printf("Votre choix : ");
        scanf("%d", &choix);
        
        switch (choix) {
            case 1:
                ajouterNourriture();
                break;
            case 2: {
                unsigned id;
                printf("ID de la nourriture à supprimer : ");
                scanf("%u", &id);
                supprimerNourriture(id);
                break;
            }
            case 3: {
                unsigned id;
                printf("ID de la nourriture à modifier : ");
                scanf("%u", &id);
                modifierNourriture(id);
                break;
            }
            case 4:
                listerNourritures();
                break;
            case 0:
                printf("Fermeture du menu.\n");
                break;
            default:
                printf("Choix invalide.\n");
        }
    } while (choix != 0);
}