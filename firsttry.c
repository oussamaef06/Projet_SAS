#include <stdio.h>
#include <string.h>
#include <time.h>

typedef struct
{
    int jour;
    int mois;
    int annee;
} date;

typedef struct
{
    int id;
    char titre[100];
    char description[400];
    date deadline;
    char statut[30];
} Tache;

void ajouterTache(Tache liste[], int *taille)
{
    Tache nouvelleTache;

    if (*taille >= 500)
    {
        printf("La liste de tâches est pleine. Impossible d'ajouter une nouvelle tâche.\n");
        return;
    }
    nouvelleTache.id = *taille + 1;
    printf("Entrez le titre de la tâche : ");
    scanf("%s", nouvelleTache.titre);
    printf("Entrez la description de la tâche : ");
    scanf("%s", nouvelleTache.description);
    printf("Entrez le deadline de la tâche (format JJ/MM/AAAA) : ");
    scanf("%d/%d/%d", &nouvelleTache.deadline.jour, &nouvelleTache.deadline.mois, &nouvelleTache.deadline.annee);
    printf("Entrez le statut de la tâche (à réaliser, en cours de réalisation, finalisée) : ");
    scanf("%s", nouvelleTache.statut);
    liste[*taille] = nouvelleTache;
    (*taille)++;
    printf("Tâche ajoutée avec succès !\n");
}

void ajouterPlusieursTaches(Tache liste[], int *taille)
{
    int nombreTaches;
    int i;

    printf("Combien de tâches souhaitez-vous ajouter ? :");
    scanf("%d", &nombreTaches);
    for (i = 0; i < nombreTaches; i++)
    {
        if (*taille >= 500)
        {
            printf("La liste de tâches est pleine. Impossible d'ajouter plus de tâches.\n");
            return;
        }
        ajouterTache(liste, taille);
    }
}

void afficherToutesTaches(Tache liste[], int taille)
{
    int i;
    if (taille == 0)
    {
        printf("Aucune tâche à afficher.\n");
        return;
    }
    printf("Liste de toutes les tâches :\n");
    printf("%-5s %-20s %-30s %-12s %-20s\n", "ID", "Titre", "Description", "Deadline", "Statut");
    for (i = 0; i < taille; i++)
    {
        printf("%-5d %-20s %-30s %02d/%02d/%04d %-20s\n", liste[i].id, liste[i].titre, liste[i].description,
               liste[i].deadline.jour, liste[i].deadline.mois, liste[i].deadline.annee, liste[i].statut);
    }
}

void trierParNom(Tache liste[], int taille)
{
    int i, j;
    Tache temp;
    if (taille == 0)
    {
        printf("Aucune tâche à trier.\n");
        return;
    }
    for (i = 0; i < taille - 1; i++)
    {
        for (j = 0; j < taille - i - 1; j++)
        {
            // Compare the letters of titles one by one
            int k = 0;
            while (liste[j].titre[k] != '\0' && liste[j + 1].titre[k] != '\0' &&
                   liste[j].titre[k] == liste[j + 1].titre[k])
            {
                k++;
            }

            // If the letters are different or one title is shorter, swap if necessary
            if (liste[j].titre[k] > liste[j + 1].titre[k])
            {
                temp = liste[j];
                liste[j] = liste[j + 1];
                liste[j + 1] = temp;
            }
        }
    }
}



int main()
{
    Tache liste[500];
    int taille = 0;
    int choix;

    while (1)
    {
        printf("\n===== Menu de Gestion de Liste de Tâches à Faire =====\n");
        printf("1. Ajouter une nouvelle tâche\n");
        printf("2. Ajouter plusieurs nouvelles tâches\n");
        printf("3. Afficher la liste de toutes les tâches\n");
        printf("4. Trier les tâches par ordre alphabétique\n");
        printf("5. Trier les tâches par deadline\n");
        printf("6. Afficher les tâches avec un deadline proche\n");
        printf("7. Modifier une tâche\n");
        printf("8. Supprimer une tâche par identifiant\n");
        printf("9. Rechercher une tâche par identifiant\n");
        printf("10. Rechercher une tâche par titre\n");
        printf("11. Afficher les statistiques\n");
        printf("0. Quitter\n");
        printf("Choix : ");
        scanf("%d", &choix);

        switch (choix)
        {
        case 1:
            ajouterTache(liste, &taille);
            break;
        case 2:
            ajouterPlusieursTaches(liste, &taille);
            break;
        case 3:
            afficherToutesTaches(liste, taille);
            break;
        case 4:
            trierParNom(liste, taille);
            break;
        case 0:
            return 0; // Quitter le programme
        default:
            printf("Choix invalide. Veuillez réessayer.\n");
        }
    }

    return 0;
}
