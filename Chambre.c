//#include"Chambre.h"
//#include"Hotel.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include"Structures.h"


void ChargerChambresDepuisFichier(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Erreur d'ouverture du fichier.\n");
        return;
    }

    char line[512];
    while (fgets(line, sizeof(line), file))
    {
        NBChambre++;
        TChambre = realloc(TChambre, NBChambre * sizeof(Chambre));
        if (TChambre == NULL)
        {
            printf("Erreur d'allocation mémoire.\n");
            fclose(file);
            return;
        }

        char *token = strtok(line, "$");
        TChambre[NBChambre - 1].idChambre = atoi(token);

        token = strtok(NULL, "$");
        TChambre[NBChambre - 1].idHotel = atoi(token);

        token = strtok(NULL, "$");
        TChambre[NBChambre - 1].numeroChambre = atoi(token);

        token = strtok(NULL, "$");
        TChambre[NBChambre - 1].typeChambre = strdup(token);

        token = strtok(NULL, "$");
        TChambre[NBChambre - 1].capacite = atoi(token);

        token = strtok(NULL, "$");
        TChambre[NBChambre - 1].etage = atoi(token);

        token = strtok(NULL, "$");
        TChambre[NBChambre - 1].prixChambre = atof(token);
    }

    fclose(file);
    printf("Données des chambres chargées depuis le fichier %s.\n", filename);
}

void AjouterChambre()
{
    unsigned int idHotel;
    printf("ID de l'hôtel: ");
    scanf("%u", &idHotel);

    int hotelExiste = 0;
    int i;
    for( i = 0; i < NBHotel; i++)
    {
        if(idHotel == THotel[i].idHotel)
        {
            hotelExiste = 1;
            break;
        }
    }

    if (!hotelExiste)
    {
        printf("Erreur : l'hôtel avec l'ID %u n'existe pas.\n", idHotel);
        return;
    }

    NBChambre++;
    TChambre = realloc(TChambre, NBChambre * sizeof(Chambre));
    if (TChambre == NULL)
    {
        printf("Erreur d'allocation mémoire.\n");
        return;
    }

    TChambre[NBChambre - 1].idChambre = CChambre++;
    TChambre[NBChambre - 1].idHotel = idHotel;

    printf("Numero de chambre: ");
    scanf("%u", &TChambre[NBChambre - 1].numeroChambre);

    printf("Type de chambre: ");
    TChambre[NBChambre - 1].typeChambre = SaisirChaine();

    printf("Capacite: ");
    scanf("%u", &TChambre[NBChambre - 1].capacite);

    printf("etage: ");
    scanf("%u", &TChambre[NBChambre - 1].etage);

    printf("Prix de la chambre: ");
    scanf("%lf", &TChambre[NBChambre - 1].prixChambre);

    printf("Chambre ajoutée avec succees! ID: %u\n", TChambre[NBChambre - 1].idChambre);
}

void AfficherChambres()
{
    if (NBChambre == 0)
    {
        printf("Aucune chambre enregistrée.\n");
        return;
    }
	unsigned int i;
    for ( i = 0; i < NBChambre; i++)
    {
        printf("-----------------------------\n");
        printf("Chambre ID: %u\n", TChambre[i].idChambre);
        printf("Hotel ID: %u\n", TChambre[i].idHotel);
        printf("Numero: %u\n", TChambre[i].numeroChambre);
        printf("Type: %s\n", TChambre[i].typeChambre);
        printf("Capacite: %u\n", TChambre[i].capacite);
        printf("etage: %u\n", TChambre[i].etage);
        printf("Prix: %.2lf\n", TChambre[i].prixChambre);
        printf("-----------------------------\n");
    }
}

void SauvegarderChambresDansFichier(const char *filename)
{
    FILE *file = fopen(filename, "w");
    if (file == NULL)
    {
        printf("Erreur d'ouverture du fichier.\n");
        return;
    }
	unsigned int i;
    for (i = 0; i < NBChambre; i++)
    {
        fprintf(file, "%u$%u$%u$%s$%u$%u$%.2lf\n",
                TChambre[i].idChambre,
                TChambre[i].idHotel,
                TChambre[i].numeroChambre,
                TChambre[i].typeChambre,
                TChambre[i].capacite,
                TChambre[i].etage,
                TChambre[i].prixChambre);
    }

    fclose(file);
    printf("Donnees des chambres sauvegardees avec succes dans %s\n", filename);
}


void ModifyChambre(unsigned int id)
{
    int index = -1;
    unsigned int i;
    for (i = 0; i < NBChambre; i++)
    {
        if (TChambre[i].idChambre == id)
        {
            index = i;
            break;
        }
    }

    if (index == -1)
    {
        printf("Erreur : Aucun chambre trouvée avec l'ID %u.\n", id);
        return;
    }

    printf("Modification de la chambre ID %u :\n", id);

    printf("Numéro de chambre (%u): ", TChambre[index].numeroChambre);
    scanf("%u", &TChambre[index].numeroChambre);

    printf("Type de chambre (%s): ", TChambre[index].typeChambre);
    free(TChambre[index].typeChambre);
    TChambre[index].typeChambre = SaisirChaine();

    printf("Capacité (%u): ", TChambre[index].capacite);
    scanf("%u", &TChambre[index].capacite);

    printf("Étage (%u): ", TChambre[index].etage);
    scanf("%u", &TChambre[index].etage);

    printf("Prix de la chambre (%.2lf): ", TChambre[index].prixChambre);
    scanf("%lf", &TChambre[index].prixChambre);

    printf("Chambre ID %u modifiée avec succès.\n", id);
}



void SupprimerChambre()
{
    unsigned int id;
    printf("ID de la chambre à supprimer: ");
    scanf("%u", &id);

    int index = -1;
    unsigned int i;
    for ( i = 0; i < NBChambre; i++)
    {
        if (TChambre[i].idChambre == id)
        {
            index = i;
            break;
        }
    }

    if (index == -1)
    {
        printf("Erreur : Aucun chambre trouvée avec l'ID %u.\n", id);
        return;
    }

    free(TChambre[index].typeChambre); 

    for ( i = index; i < NBChambre - 1; i++)
    {
        TChambre[i] = TChambre[i + 1];
    }

    NBChambre--;
    TChambre = realloc(TChambre, NBChambre * sizeof(Chambre));

    printf("Chambre ID %u supprimée avec succès.\n", id);
}


void RechercherChambreParTypeChambre(char *typeChambre)
{
    int found = 0;
    unsigned int i;
    for ( i = 0; i < NBChambre; i++)
    {
        if (strcmp(TChambre[i].typeChambre, typeChambre) == 0)
        {
            printf("Chambre ID: %u, Hôtel ID: %u, Numéro: %u, Capacité: %u, Étage: %u, Prix: %.2lf\n",
                   TChambre[i].idChambre, TChambre[i].idHotel, TChambre[i].numeroChambre,
                   TChambre[i].capacite, TChambre[i].etage, TChambre[i].prixChambre);
            found = 1;
        }
    }
    if (!found)
    {
        printf("Aucune chambre trouvée pour le type %s.\n", typeChambre);
    }
}


void RechercherChambreParEtage(unsigned int etage)
{
    int found = 0;
    unsigned int i;
    for (i = 0; i < NBChambre; i++)
    {
        if (TChambre[i].etage == etage)
        {
            printf("Chambre ID: %u, Hôtel ID: %u, Numéro: %u, Type: %s, Capacité: %u, Prix: %.2lf\n",
                   TChambre[i].idChambre, TChambre[i].idHotel, TChambre[i].numeroChambre,
                   TChambre[i].typeChambre, TChambre[i].capacite, TChambre[i].prixChambre);
            found = 1;
        }
    }
    if (!found)
    {
        printf("Aucune chambre trouvée à l'étage %u.\n", etage);
    }
}


void RechercherChambreParPrixChambre(double prixChambre)
{
    int found = 0;
    unsigned int i;
    for ( i = 0; i < NBChambre; i++)
    {
        if (TChambre[i].prixChambre <= prixChambre)
        {
            printf("Chambre ID: %u, Hôtel ID: %u, Numéro: %u, Type: %s, Capacité: %u, Étage: %u, Prix: %.2lf\n",
                   TChambre[i].idChambre, TChambre[i].idHotel, TChambre[i].numeroChambre,
                   TChambre[i].typeChambre, TChambre[i].capacite, TChambre[i].etage, TChambre[i].prixChambre);
            found = 1;
        }
    }
    if (!found)
    {
        printf("Aucune chambre trouvée avec un prix inférieur ou égal à %.2lf.\n", prixChambre);
    }
}

int ComparerParID(const void *a, const void *b)
{
    return ((Chambre *)a)->idChambre - ((Chambre *)b)->idChambre;
}

void TrierChambresParID()
{
    qsort(TChambre, NBChambre, sizeof(Chambre), ComparerParID);
    printf("Chambres triées par ID.\n");
}

int ComparerParNumero(const void *a, const void *b)
{
    return ((Chambre *)a)->numeroChambre - ((Chambre *)b)->numeroChambre;
}

void TrierChambresParNumero()
{
    qsort(TChambre, NBChambre, sizeof(Chambre), ComparerParNumero);
    printf("Chambres triées par numéro.\n");
}

int ComparerParPrixCroissant(const void *a, const void *b)
{
    return (((Chambre *)a)->prixChambre > ((Chambre *)b)->prixChambre) ? 1 : -1;
}

int ComparerParPrixDecroissant(const void *a, const void *b)
{
    return (((Chambre *)a)->prixChambre < ((Chambre *)b)->prixChambre) ? 1 : -1;
}

void TrierChambresParPrix(int ordre)
{
    if (ordre == 1)
        qsort(TChambre, NBChambre, sizeof(Chambre), ComparerParPrixCroissant);
    else
        qsort(TChambre, NBChambre, sizeof(Chambre), ComparerParPrixDecroissant);

    printf("Chambres triées par prix (%s).\n", ordre ? "croissant" : "décroissant");
}

int ComparerParCapacite(const void *a, const void *b)
{
    return ((Chambre *)a)->capacite - ((Chambre *)b)->capacite;
}

void TrierChambresParCapacite()
{
    qsort(TChambre, NBChambre, sizeof(Chambre), ComparerParCapacite);
    printf("Chambres triées par capacité.\n");
}

void Menu_Tri()
{
    int choix;
    do
    {
        printf("\n\t\t===== MENU TRI CHAMBRES =====\n");
        printf("\t\t\t\t1. Trier par ID\n");
        printf("\t\t\t\t2. Trier par numéro de chambre\n");
        printf("\t\t\t\t3. Trier par prix croissant\n");
        printf("\t\t\t\t4. Trier par prix décroissant\n");
        printf("\t\t\t\t5. Trier par capacité\n");
        printf("\t\t\t\t6. Retour\n");
        printf("Votre choix: ");
        scanf("%d", &choix);

        switch (choix)
        {
        case 1:
            TrierChambresParID();
            break;
        case 2:
            TrierChambresParNumero();
            break;
        case 3:
            TrierChambresParPrix(1);
            break;
        case 4:
            TrierChambresParPrix(0);
            break;
        case 5:
            TrierChambresParCapacite();
            break;
        case 6:
            return;
        default:
            printf("Choix invalide, réessayez.\n");
        }
    } while (1);
}







void Menu_Chambre()
{
    int choix;
    do
    {
        printf("\n\t================== MENU CHAMBRES ==================\n");
        printf("\t\t\t1. Ajouter une chambre\n");
        printf("\t\t\t2. Modifier une chambre\n");
        printf("\t\t\t3. Supprimer une chambre\n");
        printf("\t\t\t4. Afficher toutes les chambres\n");
        printf("\t\t\t5. Rechercher une chambre par type\n");
        printf("\t\t\t6. Rechercher une chambre par étage\n");
        printf("\t\t\t7. Rechercher une chambre par prix\n");
        printf("\t\t\t8. Trier les chambres\n");
        printf("\t\t\t9. Quitter\n");
        printf("\t\t\tVotre choix: ");
        scanf("%d", &choix);
        getchar();

        switch (choix)
        {
        case 1:
            AjouterChambre();
            break;
        case 2:
        {
            unsigned int id;
            printf("ID de la chambre à modifier: ");
            scanf("%u", &id);
            ModifyChambre(id);
            break;
        }
        case 3:
            SupprimerChambre();
            break;
        case 4:
            AfficherChambres();
            break;
        case 5:
        {
            char type[50];
            printf("Type de chambre à rechercher: ");
            scanf("%s", type);
            RechercherChambreParTypeChambre(type);
            break;
        }
        case 6:
        {
            unsigned int etage;
            printf("Numéro de l'étage: ");
            scanf("%u", &etage);
            RechercherChambreParEtage(etage);
            break;
        }
        case 7:
        {
            double prix;
            printf("Prix maximum: ");
            scanf("%lf", &prix);
            RechercherChambreParPrixChambre(prix);
            break;
        }
        case 8:
            Menu_Tri();
            break;
        case 9:
            return;
        default:
            printf("Choix invalide, réessayez.\n");
        }
    } while (1);
}


