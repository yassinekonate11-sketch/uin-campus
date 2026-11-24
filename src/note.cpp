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

} // namespace uin