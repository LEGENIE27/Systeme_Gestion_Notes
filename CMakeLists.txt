# Version minimale de CMake requise
cmake_minimum_required(VERSION 3.10)

# Nom du projet
project(Systeme_Gestion_Notes)

# Définir le standard de C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Ajouter les fichiers sources
set(SOURCES
    src/Etudiant.cpp
    src/Note.cpp
    src/main.cpp
)

# Inclure les fichiers d'en-têtes
include_directories(include)

# Ajouter l'exécutable
add_executable(Systeme_Gestion_Notes ${SOURCES})