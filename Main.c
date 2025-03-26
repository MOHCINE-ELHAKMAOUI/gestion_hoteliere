#include <stdio.h>
#include<stdlib.h>
//#include"Reservation.h"
//#include "Clients.h"

#include"Structures.h"




void Menu_General()
{
	
	int choix = -1;
    int code;
    
    while (choix != 0)
    {
		printf("\n================== Le menu general ==================\n");
        printf("\n\t\t 0/  Quitter le programme");
        printf("\n\t\t 1/  Ajuster la table des clients");
        printf("\n\t\t 2/  Ajuster la table des chambres");
        printf("\n\t\t 3/  Ajuster la table des hotels");
        printf("\n\t\t 4/  Ajuster la table des factures");
        printf("\n\t\t 5/  Ajuster la table des reservations");
        printf("\n\t\t 6/  Ajuster la table des avis");
        printf("\n\t\t 7/  Ajuster la table des nourritures");
        printf("\n\t\t 8/  Ajuster la table des cccccccc");
        printf("\n\t\t 9/  Ajuster la table des cccccccc");
        
        printf("\n\t\t Saisir votre choix [0, 6] : ");
        scanf("%d", &choix);
        getchar();

        switch (choix)
        {
	        case 0:
	            printf("\n Sortie du programme");
				exit(0);
	        case 1:
	            Menu_Client();
	            break;
	        case 2:
	            Menu_Chambre();
	            break;
	        case 3:
	            Menu_Hotel();
	            break;
	        case 4:
				Menu_Facture();
	            break;
	        case 5:
				Menu_Reservation();
	            break;
	        case 6:
	            //Menu_Avis() ;
	            break;
	        case 7:
	        	//Menu_Nourritures();
	        	break;
	        default:
	            printf("\n Saisir une option entre 0 et 6\n");
	            break;
        }
}
}



int main()
{
	printf("\n================== Bienvenu dans le system de gestion hoteuliere ==================\n");
	Menu_General();
	
	return 0;
	
}
