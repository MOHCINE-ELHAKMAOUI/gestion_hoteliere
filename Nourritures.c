#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Structures.h"

#define MAX_NOURRITURES 1000
#define FICHIER_NOURRITURES "nourritures.dat"


static Nourritures *TNourritures = NULL;
static unsigned int NBNourritures = 0;
static unsigned int CptNourritures = 0;



// Fonctions de sauvegarde/chargement des chaînes
void SauvegarderChaine(FILE *f, const char *chaine) {
    size_t len = strlen(chaine) + 1;
    fwrite(&len, sizeof(size_t), 1, f);
    fwrite(chaine, sizeof(char), len, f);
}

char* ChargerChaine(FILE *f) {
    size_t len;
    fread(&len, sizeof(size_t), 1, f);
    char *chaine = malloc(len);
    fread(chaine, sizeof(char), len, f);
    return chaine;
}

// Initialisation et libération mémoire
void InitialiserNourritures() {
    TNourritures = (Nourritures*)malloc(MAX_NOURRITURES * sizeof(Nourritures));
    if (TNourritures == NULL) {
        printf("Erreur d'allocation mémoire.\n");
        exit(EXIT_FAILURE);
    }
    NBNourritures = 0;
    CptNourritures = 0;
}

void LibererNourritures() {
    if (TNourritures != NULL) {
        for (unsigned int i = 0; i < NBNourritures; i++) {
            free(TNourritures[i].Nom_Nourriture);
            free(TNourritures[i].Type_Nourriture);
            free(TNourritures[i].Description_Nourriture);
        }
        free(TNourritures);
        TNourritures = NULL;
    }
    NBNourritures = 0;
    CptNourritures = 0;
}

// Sauvegarde et chargement des données
void SauvegarderNourritures() {
    FILE *f = fopen(FICHIER_NOURRITURES, "wb");
    if (!f) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }
    
    fwrite(&NBNourritures, sizeof(unsigned int), 1, f);
    fwrite(&CptNourritures, sizeof(unsigned int), 1, f);
    
    for (unsigned int i = 0; i < NBNourritures; i++) {
        fwrite(&TNourritures[i].id_Nourriture, sizeof(unsigned int), 1, f);
        fwrite(&TNourritures[i].id_Hotel, sizeof(unsigned int), 1, f);
        
        SauvegarderChaine(f, TNourritures[i].Nom_Nourriture);
        SauvegarderChaine(f, TNourritures[i].Type_Nourriture);
        SauvegarderChaine(f, TNourritures[i].Description_Nourriture);
        
        fwrite(&TNourritures[i].Prix_Total, sizeof(double), 1, f);
    }
    
    fclose(f);
    printf("Données sauvegardées avec succès.\n");
}

void ChargerNourritures() {
    FILE *f = fopen(FICHIER_NOURRITURES, "rb");
    if (!f) {
        printf("Aucun fichier de données trouvé. Création d'une nouvelle base.\n");
        return;
    }
    
    LibererNourritures();
    InitialiserNourritures();
    
    fread(&NBNourritures, sizeof(unsigned int), 1, f);
    fread(&CptNourritures, sizeof(unsigned int), 1, f);
    
    for (unsigned int i = 0; i < NBNourritures; i++) {
        fread(&TNourritures[i].id_Nourriture, sizeof(unsigned int), 1, f);
        fread(&TNourritures[i].id_Hotel, sizeof(unsigned int), 1, f);
        
        TNourritures[i].Nom_Nourriture = ChargerChaine(f);
        TNourritures[i].Type_Nourriture = ChargerChaine(f);
        TNourritures[i].Description_Nourriture = ChargerChaine(f);
        
        fread(&TNourritures[i].Prix_Total, sizeof(double), 1, f);
    }
    
    fclose(f);
    printf("%u nourritures chargées.\n", NBNourritures);
}

// Fonctions CRUD
void AjouterNourriture() {
    if (NBNourritures >= MAX_NOURRITURES) {
        printf("Capacité maximale atteinte.\n");
        return;
    }
    
    Nourritures nouvelle;
    nouvelle.id_Nourriture = ++CptNourritures;
    
    printf("\n=== Ajout d'une nouvelle nourriture ===\n");
    
    printf("ID Hotel: ");
    scanf("%u", &nouvelle.id_Hotel);
    getchar();
    
    printf("Nom: ");
    nouvelle.Nom_Nourriture = SaisirChaine();
    
    printf("Type: ");
    nouvelle.Type_Nourriture = SaisirChaine();
    
    printf("Description: ");
    nouvelle.Description_Nourriture = SaisirChaine();
    
    printf("Prix: ");
    scanf("%lf", &nouvelle.Prix_Total);
    getchar();
    
    TNourritures[NBNourritures++] = nouvelle;
    printf("Nourriture ajoutée avec succès (ID: %u)!\n", nouvelle.id_Nourriture);
}

void AfficherNourriture(const Nourritures *n) {
    printf("\nID: %u\n", n->id_Nourriture);
    printf("Hotel: %u\n", n->id_Hotel);
    printf("Nom: %s\n", n->Nom_Nourriture);
    printf("Type: %s\n", n->Type_Nourriture);
    printf("Description: %s\n", n->Description_Nourriture);
    printf("Prix: %.2f\n", n->Prix_Total);
}

void AfficherToutesNourritures() {
    printf("\n=== Liste des nourritures (%u) ===\n", NBNourritures);
    if (NBNourritures == 0) {
        printf("Aucune nourriture enregistrée.\n");
        return;
    }
    
    for (unsigned int i = 0; i < NBNourritures; i++) {
        AfficherNourriture(&TNourritures[i]);
    }
}

Nourritures* RechercherNourritureParId(unsigned int id) {
    for (unsigned int i = 0; i < NBNourritures; i++) {
        if (TNourritures[i].id_Nourriture == id) {
            return &TNourritures[i];
        }
    }
    return NULL;
}

void AfficherNourrituresParHotel(unsigned int idHotel) {
    printf("\n=== Nourritures pour l'hotel %u ===\n", idHotel);
    int trouve = 0;
    for (unsigned int i = 0; i < NBNourritures; i++) {
        if (TNourritures[i].id_Hotel == idHotel) {
            AfficherNourriture(&TNourritures[i]);
            trouve = 1;
        }
    }
    if (!trouve) printf("Aucune nourriture trouvée pour cet hotel.\n");
}

void ModifierNourriture(unsigned int id) {
    Nourritures *n = RechercherNourritureParId(id);
    if (!n) {
        printf("Nourriture non trouvée!\n");
        return;
    }
    
    printf("\n=== Modification nourriture ID %u ===\n", id);
    printf("Nouvel ID Hotel (%u): ", n->id_Hotel);
    unsigned int temp_id;
    if (scanf("%u", &temp_id) == 1) {
        n->id_Hotel = temp_id;
    }
    getchar();
    
    printf("Nouveau nom (%s): ", n->Nom_Nourriture);
    char *temp = SaisirChaine();
    if (strlen(temp) > 0) {
        free(n->Nom_Nourriture);
        n->Nom_Nourriture = temp;
    } else {
        free(temp);
    }
    
    printf("Nouveau type (%s): ", n->Type_Nourriture);
    temp = SaisirChaine();
    if (strlen(temp) > 0) {
        free(n->Type_Nourriture);
        n->Type_Nourriture = temp;
    } else {
        free(temp);
    }
    
    printf("Nouvelle description (%s): ", n->Description_Nourriture);
    temp = SaisirChaine();
    if (strlen(temp) > 0) {
        free(n->Description_Nourriture);
        n->Description_Nourriture = temp;
    } else {
        free(temp);
    }
    
    printf("Nouveau prix (%.2f): ", n->Prix_Total);
    double temp_prix;
    if (scanf("%lf", &temp_prix) == 1) {
        n->Prix_Total = temp_prix;
    }
    getchar();
    
    printf("Nourriture modifiée avec succès.\n");
}

void SupprimerNourriture(unsigned int id) {
    int index = -1;
    for (unsigned int i = 0; i < NBNourritures; i++) {
        if (TNourritures[i].id_Nourriture == id) {
            index = i;
            break;
        }
    }
    
    if (index == -1) {
        printf("Nourriture non trouvée.\n");
        return;
    }
    
    free(TNourritures[index].Nom_Nourriture);
    free(TNourritures[index].Type_Nourriture);
    free(TNourritures[index].Description_Nourriture);
    
    for (unsigned int i = index; i < NBNourritures-1; i++) {
        TNourritures[i] = TNourritures[i+1];
    }
    
    NBNourritures--;
    printf("Nourriture supprimée avec succès.\n");
}

// Menu principal
void MenuNourritures() {
    InitialiserNourritures();
    ChargerNourritures();
    
    int choix;
    unsigned int id;
    
    do {
        printf("\n=== MENU GESTION NOURRITURES ===\n");
        printf("1. Ajouter une nourriture\n");
        printf("2. Afficher toutes les nourritures\n");
        printf("3. Rechercher par ID\n");
        printf("4. Modifier une nourriture\n");
        printf("5. Supprimer une nourriture\n");
        printf("6. Afficher par hotel\n");
        printf("7. Sauvegarder les données\n");
        printf("0. Quitter\n");
        printf("Votre choix: ");
        scanf("%d", &choix);
        getchar();
        
        switch(choix) {
            case 1:
                AjouterNourriture();
                break;
            case 2:
                AfficherToutesNourritures();
                break;
            case 3:
                printf("ID de la nourriture: ");
                scanf("%u", &id);
                getchar();
                Nourritures *n = RechercherNourritureParId(id);
                if (n) AfficherNourriture(n);
                else printf("Nourriture non trouvée.\n");
                break;
            case 4:
                printf("ID de la nourriture à modifier: ");
                scanf("%u", &id);
                getchar();
                ModifierNourriture(id);
                break;
            case 5:
                printf("ID de la nourriture à supprimer: ");
                scanf("%u", &id);
                getchar();
                SupprimerNourriture(id);
                break;
            case 6:
                printf("ID de l'hotel: ");
                scanf("%u", &id);
                getchar();
                AfficherNourrituresParHotel(id);
                break;
            case 7:
                SauvegarderNourritures();
                break;
            case 0:
                printf("Sauvegarde avant de quitter...\n");
                SauvegarderNourritures();
                break;
            default:
                printf("Choix invalide.\n");
        }
    } while(choix != 0);
    
    LibererNourritures();
}
