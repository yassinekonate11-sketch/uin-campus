#include "uin/saisie.hpp"
#include "uin/regles.hpp"
#include <iostream>
#include <sstream>
#include <format>

namespace uin {

double lireNote(std::string_view invite)
{
    while (true) {
        std::cout << invite;
        std::string ligne;
        if (!std::getline(std::cin, ligne)) { return noteMin; }
        
        for (char& c : ligne) {
            if (c == ',') { c = '.'; } // accepter la virgule décimale
        }
        
        std::istringstream flux(ligne);
        double note{};
        char reste{};
        if ((flux >> note) && !(flux >> reste)) {
            if (!estNoteValide(note)) {
                std::cout << "La note doit être comprise entre 0 et 20.\n";
            } else {
                return note;
            }
        } else {
            std::cout << "Saisie invalide.\n";
        }
    }
}

int lireEntier(std::string_view invite, int min, int max)
{
    while (true) {
        std::cout << invite;
        std::string ligne;
        if (!std::getline(std::cin, ligne)) { return min; }
        
        std::istringstream flux(ligne);
        int valeur{};
        char reste{};
        if ((flux >> valeur) && !(flux >> reste)) {
            if (valeur < min || valeur > max) {
                std::cout << std::format("La valeur doit être comprise entre {} et {}.\n", min, max);
            } else {
                return valeur;
            }
        } else {
            std::cout << "Saisie invalide.\n";
        }
    }
}

} // namespace uin