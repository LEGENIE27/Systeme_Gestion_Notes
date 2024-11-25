#include "../include/Etudiant.h"
#include <iostream>
#include <fstream>

// Ajout d'une note pour un étudiant
void ajouterNote(Etudiant &etudiant, const std::string &matiere, double note) {
    etudiant.notes.push_back({matiere, note});
}

// Calcule de la moyenne générale de l'étudiant
double calculerMoyenne(const Etudiant &etudiant) {
    double somme = 0;
    for (const Note &n : etudiant.notes) {
        somme += n.note;
    }
    return etudiant.notes.empty() ? 0 : somme / etudiant.notes.size();
}

// Affichage du bulletin de l'étudiant
void afficherBulletin(const Etudiant &etudiant) {
    std::cout << "Bulletin de l'etudiant : " << etudiant.nom << " (ID: " << etudiant.identifiant << ")\n";
    for (const Note &n : etudiant.notes) {
        std::cout << n.matiere << ": " << n.note << std::endl;
    }
    std::cout << "Moyenne generale: " << calculerMoyenne(etudiant) << std::endl;
}

// Rechercher un étudiant par son identifiant
Etudiant* rechercherEtudiant(std::vector<Etudiant> &etudiants, const std::string &identifiant) {
    for (Etudiant &etudiant : etudiants) {
        if (etudiant.identifiant == identifiant) {
            return &etudiant;
        }
    }
    return nullptr; // Retourne nullptr si l'étudiant n'est pas trouvé
}

// Sauvegarder les données des étudiants dans un fichier binaire
void sauvegarderEtudiants(const std::vector<Etudiant> &etudiants) {
    std::ofstream fichier("data/etudiants.dat", std::ios::binary);
    if (fichier) {
        size_t taille = etudiants.size();
        fichier.write(reinterpret_cast<const char*>(&taille), sizeof(taille));
        for (const Etudiant &etudiant : etudiants) {
            size_t nomTaille = etudiant.nom.size();
            fichier.write(reinterpret_cast<const char*>(&nomTaille), sizeof(nomTaille));
            fichier.write(etudiant.nom.c_str(), nomTaille);
            
            size_t idTaille = etudiant.identifiant.size();
            fichier.write(reinterpret_cast<const char*>(&idTaille), sizeof(idTaille));
            fichier.write(etudiant.identifiant.c_str(), idTaille);
            
            size_t notesTaille = etudiant.notes.size();
            fichier.write(reinterpret_cast<const char*>(&notesTaille), sizeof(notesTaille));
            for (const Note &note : etudiant.notes) {
                size_t matiereTaille = note.matiere.size();
                fichier.write(reinterpret_cast<const char*>(&matiereTaille), sizeof(matiereTaille));
                fichier.write(note.matiere.c_str(), matiereTaille);
                fichier.write(reinterpret_cast<const char*>(&note.note), sizeof(note.note));
            }
        }
    } else {
        std::cerr << "Erreur lors de la sauvegarde des donnees." << std::endl;
    }
}

// Charger les données des étudiants depuis un fichier binaire
void chargerEtudiants(std::vector<Etudiant> &etudiants) {
    std::ifstream fichier("data/etudiants.dat", std::ios::binary);
    if (fichier) {
        size_t taille;
        fichier.read(reinterpret_cast<char*>(&taille), sizeof(taille));
        etudiants.resize(taille);
        
        for (Etudiant &etudiant : etudiants) {
            size_t nomTaille;
            fichier.read(reinterpret_cast<char*>(&nomTaille), sizeof(nomTaille));
            etudiant.nom.resize(nomTaille);
            fichier.read(&etudiant.nom[0], nomTaille);
            
            size_t idTaille;
            fichier.read(reinterpret_cast<char*>(&idTaille), sizeof(idTaille));
            etudiant.identifiant.resize(idTaille);
            fichier.read(&etudiant.identifiant[0], idTaille);
            
            size_t notesTaille;
            fichier.read(reinterpret_cast<char*>(&notesTaille), sizeof(notesTaille));
            etudiant.notes.resize(notesTaille);
            for (Note &note : etudiant.notes) {
                size_t matiereTaille;
                fichier.read(reinterpret_cast<char*>(&matiereTaille), sizeof(matiereTaille));
                note.matiere.resize(matiereTaille);
                fichier.read(&note.matiere[0], matiereTaille);
                fichier.read(reinterpret_cast<char*>(&note.note), sizeof(note.note));
            }
        }
    } else {
        std::cerr << "Erreur lors du chargement des donnees." << std::endl;
    }
}
