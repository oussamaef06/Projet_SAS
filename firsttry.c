#include <stdio.h>
#include <string.h>
#include <time.h>

int taille = 0;

typedef struct date
{
    int jour;
    int mois;
    int annee;
} date;

typedef struct Tache
{
    int id;
    char titre[100];
    char description[400];
    date deadline;
    char statut[30];
} Tache;

void ajouterTache(Tache liste[])
{
    Tache nouvelleTache;

    if (taille >= 250)
    {
        printf("La liste de tâches est pleine. Impossible d'ajouter une nouvelle tâche.\n");
        return;
    }
    nouvelleTache.id = taille + 1;
    printf("Entrez le titre de la tâche : ");
    scanf(" %[^\n]", nouvelleTache.titre);
    printf("Entrez la description de la tâche : ");
    scanf(" %[^\n]", nouvelleTache.description);
    printf("Entrez le deadline de la tâche (format JJ/MM/AAAA) : ");
    scanf("%d/%d/%d", &nouvelleTache.deadline.jour, &nouvelleTache.deadline.mois, &nouvelleTache.deadline.annee);
    int choix;
    printf("Entrez le statut de la tâche (à réaliser = 1, en cours de réalisation = 2, finalisée = 3) : ");
    scanf("%d", &choix);
    switch (choix)
    {
    case 1:
        strcpy(nouvelleTache.statut, "à réaliser");
        break;
    case 2:
        strcpy(nouvelleTache.statut, "en cours");
        break;
    case 3:
        strcpy(nouvelleTache.statut, "finalisée");
        break;
    default:
        break;
    }
    liste[taille] = nouvelleTache;
    (taille)++;
    printf("Tâche ajoutée avec succès !\n");
}

void ajouterPlusieursTaches(Tache liste[])
{
    int nombreTaches;
    int i;

    printf("Combien de tâches souhaitez-vous ajouter ? :");
    scanf("%d", &nombreTaches);
    for (i = 0; i < nombreTaches; i++)
    {
        if (taille >= 250)
        {
            printf("La liste de tâches est pleine. Impossible d'ajouter plus de tâches.\n");
            return;
        }
        ajouterTache(liste);
    }
}

void afficherToutesTaches(Tache liste[])
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

void swap(Tache liste[], int i, int j)
{
    Tache temp;

    temp = liste[i];
    liste[i] = liste[j];
    liste[j] = temp;
}

void trierParNom(Tache liste[])
{
    if (taille == 0)
    {
        printf("Aucune tâche à trier.\n");
        return;
    }
    for (int i = 0; i < taille; i++)
    {
        for (int j = i + 1; j < taille; j++)
        {
            if (strcmp(liste[i].titre, liste[j].titre) > 0)
            {
                swap(liste, i, j);
            }
        }
    }
    printf("Liste de toutes les tâches trier par ordre alphabétique :\n");
    printf("%-5s %-20s %-30s %-12s %-20s\n", "ID", "Titre", "Description", "Deadline", "Statut");
    for (int i = 0; i < taille; i++)
    {
        printf("%-5d %-20s %-30s %02d/%02d/%04d %-20s\n", liste[i].id, liste[i].titre, liste[i].description,
               liste[i].deadline.jour, liste[i].deadline.mois, liste[i].deadline.annee, liste[i].statut);
    }
}

void trierParDeadline(Tache liste[])
{
    if (taille == 0)
    {
        printf("Aucune tâche à trier.\n");
        return;
    }
    for (int i = 0; i < taille - 1; i++)
    {
        for (int j = 0; j < taille - i - 1; j++)
        {
            if (liste[j].deadline.annee > liste[j + 1].deadline.annee ||
                (liste[j].deadline.annee == liste[j + 1].deadline.annee &&
                 liste[j].deadline.mois > liste[j + 1].deadline.mois) ||
                (liste[j].deadline.annee == liste[j + 1].deadline.annee &&
                 liste[j].deadline.mois == liste[j + 1].deadline.mois &&
                 liste[j].deadline.jour > liste[j + 1].deadline.jour))
            {
                Tache temp = liste[j];
                liste[j] = liste[j + 1];
                liste[j + 1] = temp;
            }
        }
    }
    printf("Tâches triées par deadline :\n");
    printf("%-5s %-20s %-30s %-12s %-20s\n", "ID", "Titre", "Description", "Deadline", "Statut");
    for (int i = 0; i < taille; i++)
    {
        printf("%-5d %-20s %-30s %02d/%02d/%04d %-20s\n", liste[i].id, liste[i].titre, liste[i].description,
               liste[i].deadline.jour, liste[i].deadline.mois, liste[i].deadline.annee, liste[i].statut);
    }
}

void trierParDeadlineProche(Tache liste[])
{
    time_t currentTime; 
    time(&currentTime); 

    printf("Tâches dont la deadline est proche :\n");
    printf("%-5s %-20s %-30s %-12s %-20s\n", "ID", "Titre", "Description", "Deadline", "Statut");

    for (int i = 0; i < taille; i++) 
    {
        struct tm task_tm = {0};                          
        task_tm.tm_mday = liste[i].deadline.jour;         
        task_tm.tm_mon = liste[i].deadline.mois - 1;      
        task_tm.tm_year = liste[i].deadline.annee - 1900; 

        time_t taskTime = mktime(&task_tm);            
        double diff = difftime(taskTime, currentTime); 
        int daysDiff = diff / (60 * 60 * 24);          

        if (daysDiff <= 3 && daysDiff >= 0)
        { 
            printf("%-5d %-20s %-30s %02d/%02d/%04d %-20s\n", liste[i].id, liste[i].titre, liste[i].description,
                   liste[i].deadline.jour, liste[i].deadline.mois, liste[i].deadline.annee, liste[i].statut);
        }
    }
}

void modifierTache(Tache liste[])
{
    int idTache;
    printf("Entrez l'ID de la tâche que vous souhaitez modifier : ");
    scanf("%d", &idTache);

    int index = -1;
    for (int i = 0; i < taille; i++)
    {
        if (liste[i].id == idTache)
        {
            index = i;
            break;
        }
    }
    if (index != -1)
    {
        int choix;
        printf("Que souhaitez-vous modifier pour cette tâche ?\n");
        printf("1. Modifier la description\n");
        printf("2. Modifier le statut\n");
        printf("3. Modifier le deadline\n");
        printf("Choix : ");
        scanf("%d", &choix);

        switch (choix)
        {
        case 1:
            printf("Entrez la nouvelle description pour la tâche : ");
            scanf(" %[^\n]", liste[index].description);
            printf("Description modifiée avec succès !\n");
            break;
        case 2:
            printf("Entrez le nouveau statut pour la tâche (à réaliser = 1, en cours de réalisation = 2, finalisée = 3) : ");
            scanf(" %d", &choix);
            switch (choix)
            {
            case 1:
                strcpy(liste[index].statut, "à réaliser");
                break;
            case 2:
                strcpy(liste[index].statut, "en cours");
                break;
            case 3:
                strcpy(liste[index].statut, "finalisée");
                break;
            default:
                break;
            }
            printf("Statut modifié avec succès !\n");
            break;
        case 3:
            printf("Entrez la nouvelle deadline de la tâche (format JJ/MM/AAAA) : ");
            scanf("%d/%d/%d", &liste[index].deadline.jour, &liste[index].deadline.mois, &liste[index].deadline.annee);
            printf("Deadline modifiée avec succès !\n");
            break;
        default:
            printf("Choix invalide.\n");
        }
    }
    else
    {
        printf("Tâche avec ID %d non trouvée.\n", idTache);
    }
}

int supprimerTache(Tache liste[], int idToDelete)
{
    for (int i = 0; i < taille; i++)
    {
        if (liste[i].id == idToDelete)
        {
            for (int j = i; j < taille - 1; j++)
            {
                liste[j] = liste[j + 1];
            }
            taille--;
            printf("Tâche avec l'ID %d supprimée avec succès !\n", idToDelete);
            return taille;
        }
    }
    printf("Tâche avec l'ID %d non trouvée.\n", idToDelete);
    return taille;
}

void rechercheIdentifiant(Tache liste[], int idToFind)
{
    for (int i = 0; i < taille; i++)
    {
        if (liste[i].id == idToFind)
        {
            printf("Tâche trouvée :\n");
            printf("ID: %d\n", liste[i].id);
            printf("Titre: %s\n", liste[i].titre);
            printf("Description: %s\n", liste[i].description);
            printf("Deadline: %02d/%02d/%04d\n", liste[i].deadline.jour, liste[i].deadline.mois, liste[i].deadline.annee);
            printf("Statut: %s\n", liste[i].statut);
            return;
        }
    }

    printf("Tâche avec l'ID %d non trouvée.\n", idToFind);
}

void rechercheTitre(Tache liste[], const char titreToFind[])
{
    for (int i = 0; i < taille; i++)
    {
        if (strcmp(liste[i].titre, titreToFind) == 0)
        {
            printf("Tâche trouvée :\n");
            printf("ID: %d\n", liste[i].id);
            printf("Titre: %s\n", liste[i].titre);
            printf("Description: %s\n", liste[i].description);
            printf("Deadline: %02d/%02d/%04d\n", liste[i].deadline.jour, liste[i].deadline.mois, liste[i].deadline.annee);
            printf("Statut: %s\n", liste[i].statut);
        }
    }
    printf("Aucune tâche avec le titre \"%s\" n'a été trouvée.\n", titreToFind);
}

void statistiques(Tache liste[])
{
    printf("Statistiques :\n");

    int tachesCompletes = 0;
    int tachesIncompletes = 0;

    printf("Nombre total de tâches : %d\n", taille);

    for (int i = 0; i < taille; i++)
    {
        if (strcmp(liste[i].statut, "finalisée") == 0)
        {
            tachesCompletes++;
        }
        else
        {
            tachesIncompletes++;
        }
    }
    
    printf("Nombre de tâches complètes : %d\n", tachesCompletes);
    printf("Nombre de tâches incomplètes : %d\n", tachesIncompletes);

    printf("Nombre de jours restants jusqu'au délai de chaque tâche :\n");
    printf("%-5s %-20s %-12s %-20s\n", "ID", "Titre", "Délai (j)", "Statut");

    for (int i = 0; i < taille; i++)
    {
        struct tm task_tm = {0};
        task_tm.tm_mday = liste[i].deadline.jour;
        task_tm.tm_mon = liste[i].deadline.mois - 1;
        task_tm.tm_year = liste[i].deadline.annee - 1900;

        time_t currentTime;
        time(&currentTime);

        time_t taskTime = mktime(&task_tm);
        double diff = difftime(taskTime, currentTime);
        int joursRestants = diff / (60 * 60 * 24);

        printf("%-5d %-20s %-12d %-20s\n", liste[i].id, liste[i].titre, joursRestants, liste[i].statut);
    }
}

int main()
{
    Tache liste[250];

    int choix;

    while (1)
    {
        printf("\n===== Menu de Gestion de Liste de Tâches à Faire =====\n");
        printf("1. Ajouter une nouvelle tâche\n");
        printf("2. Ajouter plusieurs nouvelles tâches\n");
        printf("3. Afficher la liste de toutes les tâches\n");
        printf("4. Trier et afficher les tâches par ordre alphabétique\n");
        printf("5. Trier et afficher les tâches par deadline\n");
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
            ajouterTache(liste);
            break;
        case 2:
            ajouterPlusieursTaches(liste);
            break;
        case 3:
            afficherToutesTaches(liste);
            break;
        case 4:
            trierParNom(liste);
            break;
        case 5:
            trierParDeadline(liste);
            break;
        case 6:
            trierParDeadlineProche(liste);
            break;
        case 7:
            modifierTache(liste);
            break;
        case 8:
            int idToDelete;
            printf("Entrez l'ID de la tâche que vous souhaitez supprimer : ");
            scanf("%d", &idToDelete);
            taille = supprimerTache(liste, idToDelete);
            break;
        case 9:
            int idToFind;
            printf("Entrez l'ID de la tâche que vous souhaitez rechercher : ");
            scanf("%d", &idToFind);
            rechercheIdentifiant(liste, idToFind);
            break;
        case 10:
            char titreToFind[100];
            printf("Entrez le titre de la tâche que vous souhaitez rechercher : ");
            scanf(" %[^\n]", titreToFind);
            rechercheTitre(liste, titreToFind);
            break;
        case 11:
            statistiques(liste);
            break;
        case 0:
            return 0;
        default:
            printf("Choix invalide. Veuillez réessayer.\n");
        }
    }

    return 0;
}