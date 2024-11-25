#include <iostream>
#include <vector>
#include <string>
#include "../include/Etudiant.h"
#include "../include/Note.h"

void afficherMenu() {
    std::cout << "\nMenu :\n";
    std::cout << "1. Ajouter un etudiant\n";
    std::cout << "2. Ajouter une note pour un etudiant\n";
    std::cout << "3. Modifier une note\n";
    std::cout << "4. Supprimer une note\n";
    std::cout << "5. Calculer la moyenne d'un etudiant\n";
    std::cout << "6. Afficher le bulletin de l'etudiant\n";
    std::cout << "7. Rechercher un etudiant\n";
    std::cout << "8. Sauvegarder les donnees\n";
    std::cout << "9. Charger les donnees\n";
    std::cout << "0. Quitter\n";
}

int main() {
    std::vector<Etudiant> etudiants;
    chargerEtudiants(etudiants); // Charger les étudiants au démarrage

    int choix;
    do {
        afficherMenu();
        std::cout << "Votre choix : ";
        std::cin >> choix;
        std::cin.ignore(); // Pour ignorer le saut de ligne après le choix

        if (choix == 1) {
            // Ajouter un étudiant
            Etudiant etudiant;
            std::cout << "Nom de l'etudiant : ";
            std::getline(std::cin, etudiant.nom);
            std::cout << "Identifiant de l'etudiant : ";
            std::getline(std::cin, etudiant.identifiant);
            etudiants.push_back(etudiant);
        }
        else if (choix == 2) {
            // Ajouter une note pour un étudiant
            std::string identifiant;
            std::cout << "Identifiant de l'etudiant : ";
            std::getline(std::cin, identifiant);
            Etudiant* etudiant = rechercherEtudiant(etudiants, identifiant);
            if (etudiant) {
                std::string matiere;
                double note;
                std::cout << "Matiere : ";
                std::getline(std::cin, matiere);
                std::cout << "Note : ";
                std::cin >> note;
                std::cin.ignore(); // Pour ignorer le saut de ligne
                ajouterNote(*etudiant, matiere, note);
            } else {
                std::cout << "Etudiant non trouve.\n";
            }
        }
        else if (choix == 5) {
            // Calculer la moyenne d'un étudiant
            std::string identifiant;
            std::cout << "Identifiant de l'etudiant : ";
            std::getline(std::cin, identifiant);
            Etudiant* etudiant = rechercherEtudiant(etudiants, identifiant);
            if (etudiant) {
                double moyenne = calculerMoyenne(*etudiant);
                std::cout << "Moyenne generale : " << moyenne << std::endl;
            } else {
                std::cout << "Etudiant non trouve.\n";
            }
        }
        else if (choix == 6) {
            // Afficher le bulletin de l'étudiant
            std::string identifiant;
            std::cout << "Identifiant de l'etudiant : ";
            std::getline(std::cin, identifiant);
            Etudiant* etudiant = rechercherEtudiant(etudiants, identifiant);
            if (etudiant) {
                afficherBulletin(*etudiant);
            } else {
                std::cout << "Etudiant non trouve.\n";
            }
        }
        else if (choix == 8) {
            // Sauvegarder les données
            sauvegarderEtudiants(etudiants);
        }
        else if (choix == 9) {
            // Charger les données
            chargerEtudiants(etudiants);
        }
    } while (choix != 0);

    return 0;
}
