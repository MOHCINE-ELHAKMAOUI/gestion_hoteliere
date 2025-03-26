#include <stdio.h>
#include <stdlib.h>
//#include "Facture.h"
#include"Structures.h"

static unsigned int NB_Facture = 0;
static unsigned int CFacture = 0;
static Facture *TFacture = NULL;

// Ajouter une facture
void ajouterFacture(Facture nouvelleFacture) {
    if (NB_Facture == 0) {
        TFacture = (Facture *)malloc(sizeof(Facture));
    } else {
        TFacture = (Facture *)realloc(TFacture, (NB_Facture + 1) * sizeof(Facture));
    }
    TFacture[NB_Facture] = nouvelleFacture;
    NB_Facture++;
    CFacture++;
    printf("\nFacture ajoutee avec succes.\n");
}

// Afficher toutes les factures
void afficherFactures() {
	int i;
    for ( i = 0; i < NB_Facture; i++) {
        printf("ID Facture: %d | ID Client: %d | ID Reservation: %d | Montant Total: %.2f | Date Facture: %d/%d/%d\n",
               TFacture[i].id_Facture,
               TFacture[i].id_Client,
               TFacture[i].id_Reservation,
               TFacture[i].Montant_Total,
               TFacture[i].Date_Facture.j, TFacture[i].Date_Facture.m, TFacture[i].Date_Facture.a);
    }
}

// Rechercher une facture par ID
int rechercherFacture(int id) {
	int i;
    for ( i = 0; i < NB_Facture; i++) {
        if (TFacture[i].id_Facture == id) {
            return i; // Retourne l'index de la facture
        }
    }
    return -1; // Retourne -1 si non trouvé
}

// Modifier une facture
void modifierFacture(int id) {
    int index = rechercherFacture(id);
    if (index != -1) {
        printf("Nouveau montant total : ");
        scanf("%f", &TFacture[index].Montant_Total);
        printf("Nouvelle date (jj mm aaaa) : ");
        scanf("%d %d %d", &TFacture[index].Date_Facture.j, &TFacture[index].Date_Facture.m, &TFacture[index].Date_Facture.a);
        printf("Facture modifiee avec succes.\n");
    } else {
        printf("Facture introuvable.\n");
    }
}

// Générer une facture (affichage formaté)
void genererFacture(int id) {
    int index = rechercherFacture(id);
    if (index != -1) {
        printf("\n===== FACTURE =====\n");
        printf("ID Facture : %d\n", TFacture[index].id_Facture);
        printf("ID Client : %d\n", TFacture[index].id_Client);
        printf("ID Reservation : %d\n", TFacture[index].id_Reservation);
        printf("Montant Total : %.2f DH\n", TFacture[index].Montant_Total);
        printf("Date Facture : %d/%d/%d\n", TFacture[index].Date_Facture.j, TFacture[index].Date_Facture.m, TFacture[index].Date_Facture.a);
        printf("===================\n");
    } else {
        printf("Facture introuvable.\n");
    }
}

// Supprimer une facture
void supprimerFacture(int id) {
    int index = rechercherFacture(id);
    if (index != -1) {
    	int i;
        for (i = index; i < NB_Facture - 1; i++) {
            TFacture[i] = TFacture[i + 1];
        }
        NB_Facture--;
        TFacture = (Facture *)realloc(TFacture, NB_Facture * sizeof(Facture));
        printf("Facture supprimee avec succes.\n");
    } else {
        printf("Facture introuvable.\n");
    }
}

// Sauvegarder les factures dans un fichier texte
void sauvegarderFacturesDansFichier() {
    FILE *fichier = fopen("factures.txt", "w");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }
    int i;
    for (i = 0; i < NB_Facture; i++) {
        fprintf(fichier, "%d %d %d %.2f %d/%d/%d\n",
                TFacture[i].id_Facture,
                TFacture[i].id_Client,
                TFacture[i].id_Reservation,
                TFacture[i].Montant_Total,
                TFacture[i].Date_Facture.j,
                TFacture[i].Date_Facture.m,
                TFacture[i].Date_Facture.a);
    }
    fclose(fichier);
    printf("Factures sauvegardees avec succes dans 'factures.txt'.\n");
}

// Menu Facture
void Menu_Facture() 
{
    int choix=0, id;
    Facture nouvelleFacture;

    do 
	{
        printf("\n\t================== MENU FACTURE ==================\n");
        printf("\t\t\t1. Ajouter une facture\n");
        printf("\t\t\t2. Afficher les factures\n");
        printf("\t\t\t3. Sauvegarder les factures\n");
        printf("\t\t\t4. Quitter\n");
        printf("\t\t\tVotre choix : ");
        scanf("%d", &choix);
        getchar();

        switch (choix) {
            case 1:
                printf("ID Facture : "); scanf("%d", &nouvelleFacture.id_Facture);
                printf("ID Client : "); scanf("%d", &nouvelleFacture.id_Client);
                printf("ID Reservation : "); scanf("%d", &nouvelleFacture.id_Reservation);
                printf("Montant Total : "); scanf("%f", &nouvelleFacture.Montant_Total);
                printf("Date Facture (jj mm aaaa) : ");
                scanf("%d %d %d", &nouvelleFacture.Date_Facture.j, &nouvelleFacture.Date_Facture.m, &nouvelleFacture.Date_Facture.a);
                ajouterFacture(nouvelleFacture);
                break;
            case 2:
                afficherFactures();
                break;
            case 3:
                sauvegarderFacturesDansFichier();
                break;
            case 4:
                printf("Au revoir !\n");
                return;
            default:
                printf("Choix invalide, veuillez reessayer.\n");
        }
    } while (choix != 4);

    free(TFacture);
}
