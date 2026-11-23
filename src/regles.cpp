#include "uin/regles.hpp"

namespace uin {

Mention mentionPour(double moyenne)
{
    if (moyenne < seuilValidation) { return Mention::Ajourne; }
    if (moyenne < 12.0)            { return Mention::Passable; }
    if (moyenne < 14.0)            { return Mention::AssezBien; }
    if (moyenne < 16.0)            { return Mention::Bien; }
    return Mention::TresBien;
}

std::string_view libelle(Mention m)
{
    using enum Mention;
    switch (m) {
        case Ajourne:   return "Ajourné";
        case Passable:  return "Passable";
        case AssezBien: return "Assez bien";
        case Bien:      return "Bien";
        case TresBien:  return "Très bien";
    }
    return "Inconnue";
}

} // namespace uin