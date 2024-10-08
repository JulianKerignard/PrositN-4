#include <stdio.h>
#include <stdlib.h>

#define Nb_Capteurs 5          // Nombre total de capteurs
#define Indice_max_Tableau 10   // Nombre de mesures pour la moyenne instantanée

// Déclaration des tableaux
int Tab_Mesures[Nb_Capteurs];                 // Tableaux des mesures des capteurs
int Tab_Erreur[Nb_Capteurs];                  // Tableaux d'erreurs des capteurs
float Tab_Moy_Instant[Nb_Capteurs];           // Moyenne instantanée pour chaque capteur
int Tab_Capteur[Nb_Capteurs][Indice_max_Tableau];  // Mesures de chaque capteur

// Fonction de lecture des capteurs
void Lecture_Capteurs(int* mesures, int* erreurs) {
    for (int i = 0; i < Nb_Capteurs; i++) {
        erreurs[i] = 0;  // Pas d'erreurs au début
    }

    // Simulation de la lecture des capteurs
    for (int num_capteur = 0; num_capteur < Nb_Capteurs; num_capteur++) {
        int Mesure_capteur = rand() % 100;  // Simuler la mesure (exemple aléatoire)
        if (Mesure_capteur >= 0) {
            mesures[num_capteur] = Mesure_capteur;  // Enregistrer la mesure
        } else {
            erreurs[num_capteur] = 1;  // Marquer une erreur
        }
    }
}

// Fonction de mise à jour des mesures
void Maj_Mesures(int mesures[], int erreurs[], int capteurs[][Indice_max_Tableau]) {
    for (int num_capteur = 0; num_capteur < Nb_Capteurs; num_capteur++) {
        if (erreurs[num_capteur] != 1) {  // Si pas d'erreur
            Decalage(capteurs[num_capteur], &mesures[num_capteur]);
        }
    }
}

// Fonction pour décaler les mesures dans le tableau
void Decalage(int* tableau, int* valeur) {
    for (int i = 0; i < Indice_max_Tableau - 1; i++) {
        tableau[i] = tableau[i + 1];
    }
    tableau[Indice_max_Tableau - 1] = *valeur;  // Ajouter la nouvelle valeur à la fin
}

// Fonction pour calculer la moyenne instantanée
float Calcul_Moy_Instant(int* tableau) {
    float Moyenne = 0;
    for (int i = 0; i < Indice_max_Tableau; i++) {
        Moyenne += tableau[i];
    }
    Moyenne = Moyenne / Indice_max_Tableau;  // Moyenne arithmétique
    return Moyenne;
}

int main() {
    // Simulation de plusieurs cycles
    for (int cycle = 0; cycle < 10; cycle++) {
        printf("\nCycle %d\n", cycle);

        // 1. Lecture des capteurs
        Lecture_Capteurs(Tab_Mesures, Tab_Erreur);

        // 2. Mise à jour des mesures
        Maj_Mesures(Tab_Mesures, Tab_Erreur, Tab_Capteur);

        // 3. Calcul de la moyenne instantanée pour chaque capteur
        for (int num_capteur = 0; num_capteur < Nb_Capteurs; num_capteur++) {
            if (Tab_Erreur[num_capteur] == 0) {  // Si pas d'erreur
                Tab_Moy_Instant[num_capteur] = Calcul_Moy_Instant(Tab_Capteur[num_capteur]);
                printf("Capteur %d - Moyenne Instantanée: %.2f\n", num_capteur, Tab_Moy_Instant[num_capteur]);
            } else {
                printf("Capteur %d - Erreur de lecture\n", num_capteur);
            }
        }
    }

    return 0;
}
