#include "uin/note.hpp"

#include <format>
#include <stdexcept>

namespace uin {

Note::Note(double valeur) : valeur_(valeur)
{
    if (!estNoteValide(valeur_)) {
        throw std::invalid_argument(std::format(
            "Note invalide : {} (attendu entre {} et {})", valeur_, noteMin, noteMax));
    }
}

Note Note::depuisBarème(double valeur, double barème)
{
    if (!(barème > 0.0)) {
        throw std::invalid_argument(std::format("Barème invalide : {}", barème));
    }
    // Le constructeur vérifie le résultat
    return Note(valeur * noteMax / barème);
}

} // namespace uin