include<stdio.h>
include<string.h>

//Declaration de variables

//Fonction Addition ALIOU
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Structures
typedef struct Client {
    int codecli;
    char prenom[30];
    char nom[30];
    char tel[15];
    char ville[30];
    struct Client *next;
} Client;

typedef struct Compte {
    int numero;
    char dateouverture[11];
    char agence[30];
    float solde;
    int codecli;
    struct Compte *next;
} Compte;

typedef struct Operation {
    int code;
    int numero_compte;
    char type[10]; // "dépôt" ou "retrait"
    float montant;
    char dateop[11];
    struct Operation *next;
} Operation;

// Listes chaînées
Client *clients = NULL;
Compte *comptes = NULL;
Operation *operations = NULL;

// Fonctions utilitaires
void sauvegarder_clients();
void sauvegarder_comptes();
void sauvegarder_operations();
void charger_donnees();
char *date_actuelle();

// Fonctions principales
void menu_principal();
void gestion_clients();
void gestion_comptes();
void gestion_operations();
void ajouter_client();
void afficher_clients();
void ajouter_compte();
void afficher_comptes();
void effectuer_operation();
void afficher_historique();

int main() {
    charger_donnees();
    menu_principal();
    return 0;
}

// Menu principal
void menu_principal() {
    int choix;
    do {
        printf("\n========= SUIVI DES COMPTES CLIENTS =========\n");
        printf("1. Gestion des clients\n");
        printf("2. Gestion des comptes\n");
        printf("3. Gestion des opérations\n");
        printf("0. Quitter\n");
        printf("Choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                gestion_clients();
                break;
            case 2:
                gestion_comptes();
                break;
            case 3:
                gestion_operations();
                break;
            case 0:
                printf("Au revoir !\n");
                sauvegarder_clients();
                sauvegarder_comptes();
                sauvegarder_operations();
                break;
            default:
                printf("Choix invalide. Veuillez réessayer.\n");
        }
    } while (choix != 0);
}

// Gestion des clients
void gestion_clients() {
    int choix;
    do {
        printf("\n========= GESTION DES CLIENTS =========\n");
        printf("1. Ajouter un client\n");
        printf("2. Afficher les clients\n");
        printf("0. Retour au menu principal\n");
        printf("Choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                ajouter_client();
                break;
            case 2:
                afficher_clients();
                break;
            case 0:
                return;
            default:
                printf("Choix invalide. Veuillez réessayer.\n");
        }
    } while (choix != 0);
}

void ajouter_client() {
    Client *nouveau = (Client *)malloc(sizeof(Client));
    printf("Code client : ");
    scanf("%d", &nouveau->codecli);
    printf("Prénom : ");
    scanf("%s", nouveau->prenom);
    printf("Nom : ");
    scanf("%s", nouveau->nom);
    printf("Téléphone : ");
    scanf("%s", nouveau->tel);
    printf("Ville : ");
    scanf("%s", nouveau->ville);
    nouveau->next = clients;
    clients = nouveau;
    printf("Client ajouté avec succès !\n");
}

void afficher_clients() {
    Client *temp = clients;
    printf("\nListe des clients :\n");
    while (temp) {
        printf("Code : %d, Nom : %s %s, Téléphone : %s, Ville : %s\n",
               temp->codecli, temp->prenom, temp->nom, temp->tel, temp->ville);
        temp = temp->next;
    }
}

// Gestion des comptes
void gestion_comptes() {
    int choix;
    do {
        printf("\n========= GESTION DES COMPTES =========\n");
        printf("1. Ajouter un compte\n");
        printf("2. Afficher les comptes\n");
        printf("0. Retour au menu principal\n");
        printf("Choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                ajouter_compte();
                break;
            case 2:
                afficher_comptes();
                break;
            case 0:
                return;
            default:
                printf("Choix invalide. Veuillez réessayer.\n");
        }
    } while (choix != 0);
}

void ajouter_compte() {
    Compte *nouveau = (Compte *)malloc(sizeof(Compte));
    printf("Numéro de compte : ");
    scanf("%d", &nouveau->numero);
    printf("Agence : ");
    scanf("%s", nouveau->agence);
    printf("Code client : ");
    scanf("%d", &nouveau->codecli);
    nouveau->solde = 0.0;
    strcpy(nouveau->dateouverture, date_actuelle());
    nouveau->next = comptes;
    comptes = nouveau;
    printf("Compte ajouté avec succès !\n");
}

void afficher_comptes() {
    Compte *temp = comptes;
    printf("\nListe des comptes :\n");
    while (temp) {
        printf("Numéro : %d, Agence : %s, Solde : %.2f, Date d'ouverture : %s, Code client : %d\n",
               temp->numero, temp->agence, temp->solde, temp->dateouverture, temp->codecli);
        temp = temp->next;
    }
}

// Gestion des opérations
void gestion_operations() {
    int choix;
    do {
        printf("\n========= GESTION DES OPÉRATIONS =========\n");
        printf("1. Effectuer une opération\n");
        printf("2. Afficher l'historique des opérations\n");
        printf("0. Retour au menu principal\n");
        printf("Choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                effectuer_operation();
                break;
            case 2:
                afficher_historique();
                break;
            case 0:
                return;
            default:
                printf("Choix invalide. Veuillez réessayer.\n");
        }
    } while (choix != 0);
}

void effectuer_operation() {
    Operation *nouvelle = (Operation *)malloc(sizeof(Operation));
    Compte *compte = comptes;
    int numero_compte;
    printf("Numéro de compte : ");
    scanf("%d", &numero_compte);

    while (compte && compte->numero != numero_compte)
        compte = compte->next;

    if (!compte) {
        printf("Compte introuvable.\n");
        free(nouvelle);
        return;
    }

    printf("Type d'opération (dépôt/retrait) : ");
    scanf("%s", nouvelle->type);
    printf("Montant : ");
    scanf("%f", &nouvelle->montant);

    if (strcmp(nouvelle->type, "retrait") == 0 && nouvelle->montant > compte->solde) {
        printf("Solde insuffisant.\n");
        free(nouvelle);
        return;
    }

    nouvelle->code = (operations ? operations->code + 1 : 1);
    nouvelle->numero_compte = numero_compte;
    strcpy(nouvelle->dateop, date_actuelle());
    nouvelle->next = operations;
    operations = nouvelle;

    if (strcmp(nouvelle->type, "dépôt") == 0)
        compte->solde += nouvelle->montant;
    else
        compte->solde -= nouvelle->montant;

    printf("Opération effectuée avec succès !\n");
}

void afficher_historique() {
    Operation *temp = operations;
    printf("\nHistorique des opérations :\n");
    while (temp) {
        printf("Code : %d, Compte : %d, Type : %s, Montant : %.2f, Date : %s\n",
               temp->code, temp->numero_compte, temp->type, temp->montant, temp->dateop);
        temp = temp->next;
    }
}

// Gestion des fichiers
void sauvegarder_clients() {
    FILE *file = fopen("clients.dat", "wb");
    Client *temp = clients;
    while (temp) {
        fwrite(temp, sizeof(Client), 1, file);
        temp = temp->next;
    }
    fclose(file);
}

void sauvegarder_comptes() {
    FILE *file = fopen("comptes.dat", "wb");
    Compte *temp = comptes;
    while (temp) {
        fwrite(temp, sizeof(Compte), 1, file);
        temp = temp->next;
    }
    fclose(file);
}

void sauvegarder_operations() {
    FILE *file = fopen("operations.dat", "wb");
    Operation *temp = operations;
    while (temp) {
        fwrite(temp, sizeof(Operation), 1, file);
        temp = temp->next;
    }
    fclose(file);
}

void charger_donnees() {
    FILE *file;
    Client temp_client;
    Compte temp_compte;
    Operation temp_operation;

    file = fopen("clients.dat", "rb");
    if (file) {
        while (fread(&temp_client, sizeof(Client), 1, file)) {
            Client *nouveau = (Client *)malloc(sizeof(Client));
            *nouveau = temp_client;
            nouveau->next = clients;
            clients = nouveau;
        }
        fclose(file);
    }

    file = fopen("comptes.dat", "rb");
    if (file) {
        while (fread(&temp_compte, sizeof(Compte), 1, file)) {
            Compte *nouveau = (Compte *)malloc(sizeof(Compte));
            *nouveau = temp_compte;
            nouveau->next = comptes;
            comptes = nouveau;
        }
        fclose(file);
    }

    file = fopen("operations.dat", "rb");
    if (file) {
        while (fread(&temp_operation, sizeof(Operation), 1, file)) {
            Operation *nouvelle = (Operation *)malloc(sizeof(Operation));
            *nouvelle = temp_operation;
            nouvelle->next = operations;
            operations = nouvelle;
        }
        fclose(file);
    }
}

// Fonction pour obtenir la date actuelle
char *date_actuelle() {
    static char date[11];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(date, "%02d/%02d/%04d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
    return date;
}
int somme(float a, int b) 
//Fonction Multiplication RYAD

//Fonction Division NDIAYA