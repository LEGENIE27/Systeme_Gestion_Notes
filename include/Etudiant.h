#ifndef ETUDIANT_H
#define ETUDIANT_H

#include <string>
#include <vector>
#include "Note.h"

struct Etudiant {
    std::string nom;
    std::string identifiant;
    std::vector<Note> notes;
};

// Déclarations des fonctions associées à l'étudiant
void ajouterNote(Etudiant &etudiant, const std::string &matiere, double note);
double calculerMoyenne(const Etudiant &etudiant);
void afficherBulletin(const Etudiant &etudiant);
Etudiant* rechercherEtudiant(std::vector<Etudiant> &etudiants, const std::string &identifiant);
void sauvegarderEtudiants(const std::vector<Etudiant> &etudiants);
void chargerEtudiants(std::vector<Etudiant> &etudiants);

#endif
