#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>  

//NONGUIERMA WENDKUNI FABRICE EZECKIEL && AWOURASSIBE FIDELE TINDANAHIRE

// Structure note d'étudiant
struct Note {
    std::string matiere;
    double note;
};

// Structure étudiant
struct Etudiant {
    std::string nom;
    std::string identifiant;
    std::vector<Note> notes;

    void ajouterNote(const std::string& matiere, double note) {
        notes.push_back({matiere, note});
    }

    double calculerMoyenne() const {
        if (notes.empty()) return 0.0;
        double somme = 0;
        for (const auto& n : notes) {
            somme += n.note;
        }
        return somme / notes.size();
    }

    void afficherBulletin() const {
        std::cout << "Bulletin de l'etudiant: " << nom << " (ID: " << identifiant << ")\n";
        for (const auto& n : notes) {
            std::cout << n.matiere << ": " << n.note << std::endl;
        }
        std::cout << "Moyenne generale: " << calculerMoyenne() << "\n";
    }
};

// Fonction pour rechercher un étudiant par identifiant
Etudiant* rechercherEtudiant(std::vector<Etudiant>& etudiants, const std::string& identifiant) {
    for (auto& etudiant : etudiants) {
        if (etudiant.identifiant == identifiant) {
            return &etudiant;
        }
    }
    return nullptr;
}

// Fonction pour sauvegarder les données dans un fichier
void sauvegarderDonnees(const std::vector<Etudiant>& etudiants, const std::string& filename) {
    std::ofstream fichier(filename, std::ios::binary);
    for (const auto& etudiant : etudiants) {
        fichier << etudiant.nom << "\n" << etudiant.identifiant << "\n";
        fichier << etudiant.notes.size() << "\n"; // nombre de notes
        for (const auto& note : etudiant.notes) {
            fichier << note.matiere << "\n" << note.note << "\n";
        }
    }
}

// Fonction pour charger les données depuis un fichier
void chargerDonnees(std::vector<Etudiant>& etudiants, const std::string& filename) {
    std::ifstream fichier(filename, std::ios::binary);
    std::string nom, identifiant, matiere;
    double note;
    size_t nbNotes;

    while (getline(fichier, nom)) {
        getline(fichier, identifiant);
        Etudiant etudiant;
        etudiant.nom = nom;
        etudiant.identifiant = identifiant;
        fichier >> nbNotes;
        fichier.ignore();  // Pour ignorer le saut de ligne après le nombre de notes

        for (size_t i = 0; i < nbNotes; ++i) {
            getline(fichier, matiere);
            fichier >> note;
            fichier.ignore();  // Pour ignorer le saut de ligne après la note
            etudiant.ajouterNote(matiere, note);
        }
        etudiants.push_back(etudiant);
    }
}

void afficherMenu() {
    std::cout << "\nSysteme de gestion de notes :\n";
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
                etudiant->ajouterNote(matiere, note);
            } else {
                std::cout << "Etudiant non trouve.\n";
            }
        }
        else if (choix == 3) {
            // Modifier une note pour un étudiant
            std::string identifiant, matiere;
            double nouvelleNote;
            std::cout << "Identifiant de l'etudiant : ";
            std::getline(std::cin, identifiant);
            Etudiant* etudiant = rechercherEtudiant(etudiants, identifiant);
            if (etudiant) {
                std::cout << "Matiere : ";
                std::getline(std::cin, matiere);
                bool noteModifiee = false;
                for (auto& note : etudiant->notes) {
                    if (note.matiere == matiere) {
                        std::cout << "Nouvelle note : ";
                        std::cin >> nouvelleNote;
                        note.note = nouvelleNote;
                        noteModifiee = true;
                        break;
                    }
                }
                if (!noteModifiee) {
                    std::cout << "Note non trouvée pour cette matiere.\n";
                }
            } else {
                std::cout << "Etudiant non trouve.\n";
            }
        }
        else if (choix == 4) {
            // Supprimer une note pour un étudiant
            std::string identifiant, matiere;
            std::cout << "Identifiant de l'etudiant : ";
            std::getline(std::cin, identifiant);
            Etudiant* etudiant = rechercherEtudiant(etudiants, identifiant);
            if (etudiant) {
                std::cout << "Matiere : ";
                std::getline(std::cin, matiere);
                auto it = std::remove_if(etudiant->notes.begin(), etudiant->notes.end(),
                                         [&matiere](const Note& note) { return note.matiere == matiere; });
                if (it != etudiant->notes.end()) {
                    etudiant->notes.erase(it, etudiant->notes.end());
                    std::cout << "Note supprimee.\n";
                } else {
                    std::cout << "Note non trouvee.\n";
                }
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
                std::cout << "Moyenne generale: " << etudiant->calculerMoyenne() << "\n";
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
                etudiant->afficherBulletin();
            } else {
                std::cout << "Etudiant non trouve.\n";
            }
        }
        else if (choix == 7) {
            // Rechercher un étudiant
            std::string identifiant;
            std::cout << "Identifiant de l'étudiant : ";
            std::getline(std::cin, identifiant);
            Etudiant* etudiant = rechercherEtudiant(etudiants, identifiant);
            if (etudiant) {
                std::cout << "Etudiant trouve : " << etudiant->nom << " (ID: " << etudiant->identifiant << ")\n";
            } else {
                std::cout << "Etudiant non trouve.\n";
            }
        }
        else if (choix == 8) {
            // Sauvegarder les données
            sauvegarderDonnees(etudiants, "etudiants.dat");
            std::cout << "Donnees sauvegardees.\n";
        }
        else if (choix == 9) {
            // Charger les données
            chargerDonnees(etudiants, "etudiants.dat");
            std::cout << "Donnees chargees.\n";
        }

    } while (choix != 0);

    return 0;
}
