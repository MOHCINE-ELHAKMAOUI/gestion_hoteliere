

struct date
{
	unsigned int j ;
	unsigned int m ;
	unsigned int a ;
};
typedef struct date Date ;

int IsDate(unsigned int, unsigned int, unsigned int) ;
int IsStrDate(char * , const char );
int ComparerDatesCroissantes(Date, Date) ;
int ComparerDatesDecroissantes(Date, Date) ;
Date Str_Date(char *);
//

struct client {
    int id_Client;
    char *Nom;
    char *Prenom;
    char *Email;
    char *Adresse;
    char *Nationalite;
    int Code_Postale;
    char *Ville_Client;
    Date Date_Naissance;
    struct client *suivant;
};
typedef struct client Client;

void Menu_Client();
//

struct reservation {
    int id_Reservation;
    int id_Chambre;
    int id_Nourriture;
    int id_Client;
    int Nombre_Personnes;
    Date Date_Arrive;
    Date Date_Depart;
    float Prix_Total;
};
typedef struct reservation Reservation;

void Menu_Reservation();
//

struct facture {
    int id_Facture;
    int id_Client;
    int id_Reservation;
    float Montant_Total;
    Date Date_Facture;
};
typedef struct facture Facture;

void Menu_Facture();
//

typedef struct chambre
{
    unsigned int idChambre;
    unsigned int idHotel;
    unsigned int numeroChambre;
    char* typeChambre;
    unsigned int capacite;
    unsigned int etage;
    double prixChambre;
}Chambre;


static unsigned int NBChambre = 0 ; 
static unsigned int CChambre= 0 ; 
static Chambre * TChambre = NULL ;

void Menu_Chambre();
//

typedef struct AvisClient{
    unsigned int id_Avis;
    unsigned int id_Client;
    unsigned int id_Hotel;
    unsigned int Note;
    char *Commentaire;
}AvisClient;
//

char *SaisirChaine();
int IsPhoneNumber(const char *);
int IsEmail(const char *);
int IsWebsite(const char *);
//

typedef struct hotel{
    unsigned int idHotel;
    char* nomHotel;
    char* adresseHotel;
    char* villeHotel;
    char* paysHotel;
    char*telHotel;
    char*emailHotel;
    char*siteWebHotel;
    unsigned int nbrEtoil;
}Hotel;


static unsigned int NBHotel = 0;
static unsigned int IdsHotel = 0;
static Hotel *THotel = NULL;

void Menu_Hotel();
//

typedef struct Nourritures{
    unsigned int id_Nourriture;
    unsigned int id_Hotel;
    char *Nom_Nourriture;
    char *Type_Nourriture;
    char *Description_Nourriture;
    double Prix_Total;
}Nourritures;
//



