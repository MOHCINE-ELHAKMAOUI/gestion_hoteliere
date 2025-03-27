#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Structures.h"

#define MAX_AVIS 1000
#define FICHIER_AVIS "avis_clients.txt"

static AvisClient *TAvis = NULL;
static unsigned int NBAvis = 0;
static unsigned int CptAvis = 0;

// Fonction pour initialiser le système d'avis
void InitialiserSystemeAvis() {
    TAvis = (AvisClient*)malloc(MAX_AVIS * sizeof(AvisClient));
    if (TAvis == NULL) {
        printf("Erreur d'allocation mémoire.\n");
        exit(EXIT_FAILURE);
    }
    NBAvis = 0;
    CptAvis = 0;
}

// Fonction pour libérer la mémoire
void LibererSystemeAvis() {
    if (TAvis != NULL) {
        int i ;
        for (i = 0; i < NBAvis; i++) {
            free(TAvis[i].Commentaire);
        }
        free(TAvis);
        TAvis = NULL;
    }
    NBAvis = 0;
    CptAvis = 0;
}

// Fonction pour sauvegarder les avis dans un fichier
void SauvegarderAvis() {
    FILE *fichier = fopen(FICHIER_AVIS, "wb");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier pour sauvegarde.\n");
        return;
    }

    // Écrire le nombre d'avis
    fwrite(&NBAvis, sizeof(unsigned int), 1, fichier);
    fwrite(&CptAvis, sizeof(unsigned int), 1, fichier);

    // Écrire chaque avis
    int i ;
    for (i = 0; i < NBAvis; i++) {
        fwrite(&TAvis[i].id_Avis, sizeof(unsigned int), 1, fichier);
        fwrite(&TAvis[i].id_Client, sizeof(unsigned int), 1, fichier);
        fwrite(&TAvis[i].id_Hotel, sizeof(unsigned int), 1, fichier);
        fwrite(&TAvis[i].Note, sizeof(unsigned int), 1, fichier);

        // Sauvegarder la longueur du commentaire puis le commentaire
        size_t longueur = strlen(TAvis[i].Commentaire) + 1;
        fwrite(&longueur, sizeof(size_t), 1, fichier);
        fwrite(TAvis[i].Commentaire, sizeof(char), longueur, fichier);
    }

    fclose(fichier);
    printf("Avis sauvegardés avec succès dans %s.\n", FICHIER_AVIS);
}

// Fonction pour charger les avis depuis un fichier
void ChargerAvis() {
    FILE *fichier = fopen(FICHIER_AVIS, "rb");
    if (fichier == NULL) {
        printf("Aucun fichier de sauvegarde trouvé. Création d'une nouvelle base.\n");
        return;
    }

    // Libérer la mémoire existante si nécessaire
    LibererSystemeAvis();
    InitialiserSystemeAvis();

    // Lire le nombre d'avis
    unsigned int nbAvisFichier, cptAvisFichier;
    fread(&nbAvisFichier, sizeof(unsigned int), 1, fichier);
    fread(&cptAvisFichier, sizeof(unsigned int), 1, fichier);

    // Lire chaque avis
    int i ;
    for (i = 0; i < nbAvisFichier; i++) {
        AvisClient avis;
        fread(&avis.id_Avis, sizeof(unsigned int), 1, fichier);
        fread(&avis.id_Client, sizeof(unsigned int), 1, fichier);
        fread(&avis.id_Hotel, sizeof(unsigned int), 1, fichier);
        fread(&avis.Note, sizeof(unsigned int), 1, fichier);

        // Lire la longueur du commentaire puis le commentaire
        size_t longueur;
        fread(&longueur, sizeof(size_t), 1, fichier);
        avis.Commentaire = (char*)malloc(longueur);
        fread(avis.Commentaire, sizeof(char), longueur, fichier);

        // Ajouter à notre tableau
        if (NBAvis < MAX_AVIS) {
            TAvis[NBAvis++] = avis;
        } else {
            free(avis.Commentaire);
            printf("Attention: Capacité maximale atteinte, certains avis n'ont pas été chargés.\n");
            break;
        }
    }

    CptAvis = cptAvisFichier;
    fclose(fichier);
    printf("%u avis chargés depuis %s.\n", nbAvisFichier, FICHIER_AVIS);
}

// Fonction pour ajouter un avis
void AjouterAvis() {
    if (NBAvis >= MAX_AVIS) {
        printf("Capacité maximale d'avis atteinte.\n");
        return;
    }

    AvisClient nouvelAvis;
    
    nouvelAvis.id_Avis = ++CptAvis;
    
    printf("\n=== Ajout d'un nouvel avis ===\n");
    
    printf("ID Client: ");
    scanf("%u", &nouvelAvis.id_Client);
    getchar();
    
    printf("ID Hotel: ");
    scanf("%u", &nouvelAvis.id_Hotel);
    getchar();
    
    do {
        printf("Note (1-5): ");
        scanf("%u", &nouvelAvis.Note);
        getchar();
        if (nouvelAvis.Note < 1 || nouvelAvis.Note > 5) {
            printf("La note doit être entre 1 et 5.\n");
        }
    } while (nouvelAvis.Note < 1 || nouvelAvis.Note > 5);
    
    printf("Commentaire: ");
    char buffer[500];
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    nouvelAvis.Commentaire = strdup(buffer);
    
    TAvis[NBAvis++] = nouvelAvis;
    
    printf("Avis ajouté avec succès (ID: %u)!\n", nouvelAvis.id_Avis);
    
    // Sauvegarder après ajout
    SauvegarderAvis();
}

// Fonction pour afficher un avis
void AfficherAvis(const AvisClient *avis) {
    printf("\nID Avis: %u\n", avis->id_Avis);
    printf("ID Client: %u\n", avis->id_Client);
    printf("ID Hotel: %u\n", avis->id_Hotel);
    printf("Note: %u/5\n", avis->Note);
    printf("Commentaire: %s\n", avis->Commentaire);
}

// Fonction pour afficher tous les avis
void AfficherTousLesAvis() {
    printf("\n=== Liste de tous les avis ===\n");
    if (NBAvis == 0) {
        printf("Aucun avis enregistré.\n");
        return;
    }
    
    int i ;
    for (i = 0; i < NBAvis; i++) {
        AfficherAvis(&TAvis[i]);
    }
}

// Fonction pour rechercher un avis par ID
AvisClient* RechercherAvisParId(unsigned int id) {
    int i;
    for (i = 0; i < NBAvis; i++) {
        if (TAvis[i].id_Avis == id) {
            return &TAvis[i];
        }
    }
    return NULL;
}

// Fonction pour afficher les avis d'un hotel
void AfficherAvisParHotel(unsigned int idHotel) {
    printf("\n=== Avis pour l'hotel ID %u ===\n", idHotel);
    int trouve = 0;
    
    int i ;
    for (i = 0; i < NBAvis; i++) {
        if (TAvis[i].id_Hotel == idHotel) {
            AfficherAvis(&TAvis[i]);
            trouve = 1;
        }
    }
    
    if (!trouve) {
        printf("Aucun avis trouvé pour cet hotel.\n");
    }
}

// Fonction pour calculer la moyenne des notes d'un hotel
float CalculerMoyenneHotel(unsigned int idHotel) {
    unsigned int somme = 0;
    unsigned int compte = 0;
    
    int i ;
    for (i = 0; i < NBAvis; i++) {
        if (TAvis[i].id_Hotel == idHotel) {
            somme += TAvis[i].Note;
            compte++;
        }
    }
    
    if (compte == 0) return 0.0f;
    return (float)somme / compte;
}

// Fonction pour supprimer un avis
void SupprimerAvis(unsigned int id) {
    int index = -1;
    
    int i ;
    for (i = 0; i < NBAvis; i++) {
        if (TAvis[i].id_Avis == id) {
            index = i;
            break;
        }
    }
    
    if (index == -1) {
        printf("Avis avec ID %u non trouvé.\n", id);
        return;
    }
    
    free(TAvis[index].Commentaire);
    
    int i ;
    for (i = index; i < NBAvis - 1; i++) {
        TAvis[i] = TAvis[i + 1];
    }
    
    NBAvis--;
    printf("Avis ID %u supprimé avec succès.\n", id);
    
    // Sauvegarder après suppression
    SauvegarderAvis();
}

// Menu de gestion des avis
void MenuAvisClient() {
    int choix;
    unsigned int id;
    
    InitialiserSystemeAvis();
    ChargerAvis(); // Charger les données au démarrage
    
    do {
        printf("\n=== MENU GESTION AVIS CLIENTS ===\n");
        printf("1. Ajouter un avis\n");
        printf("2. Afficher tous les avis\n");
        printf("3. Rechercher un avis par ID\n");
        printf("4. Afficher les avis d'un hotel\n");
        printf("5. Calculer la moyenne d'un hotel\n");
        printf("6. Supprimer un avis\n");
        printf("7. Sauvegarder les avis\n");
        printf("0. Quitter\n");
        printf("Votre choix: ");
        scanf("%d", &choix);
        getchar();
        
        switch (choix) {
            case 1:
                AjouterAvis();
                break;
            case 2:
                AfficherTousLesAvis();
                break;
            case 3:
                printf("ID de l'avis à rechercher: ");
                scanf("%u", &id);
                getchar();
                AvisClient *avis = RechercherAvisParId(id);
                if (avis != NULL) {
                    AfficherAvis(avis);
                } else {
                    printf("Avis non trouvé.\n");
                }
                break;
            case 4:
                printf("ID de l'hotel: ");
                scanf("%u", &id);
                getchar();
                AfficherAvisParHotel(id);
                break;
            case 5:
                printf("ID de l'hotel: ");
                scanf("%u", &id);
                getchar();
                float moyenne = CalculerMoyenneHotel(id);
                printf("Moyenne des notes pour l'hotel %u: %.2f/5\n", id, moyenne);
                break;
            case 6:
                printf("ID de l'avis à supprimer: ");
                scanf("%u", &id);
                getchar();
                SupprimerAvis(id);
                break;
            case 7:
                SauvegarderAvis();
                break;
            case 0:
                printf("Sauvegarde avant de quitter...\n");
                SauvegarderAvis();
                printf("Retour au menu principal.\n");
                break;
            default:
                printf("Choix invalide.\n");
        }
    } while (choix != 0);
    
    LibererSystemeAvis();
}

