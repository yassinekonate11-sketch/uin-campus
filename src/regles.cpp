#include "uin/regles.hpp"

namespace uin {

Mention mentionPour(double moyenne)
{
    int rang{0};
    for (double seuil : seuilsMentions) {
        if (moyenne >= seuil) {
            ++rang;
        }
    }
    return static_cast<Mention>(rang);
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