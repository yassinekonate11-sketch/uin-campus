#include "uin/ue.hpp"

#include <format>
#include <stdexcept>
#include <utility>

namespace uin {

UE::UE(std::string code, std::string intitule, int credits, double coefficient)
    : code_(std::move(code)),
      intitule_(std::move(intitule)),
      credits_(credits),
      coefficient_(coefficient)
{
    // On vérifie les ATTRIBUTS : les paramètres code et intitule ont été déplacés.
    if (code_.empty()) {
        throw std::invalid_argument("UE : le code est obligatoire");
    }
    if (intitule_.empty()) {
        throw std::invalid_argument(std::format("UE {} : l'intitulé est obligatoire", code_));
    }
    if (credits_ <= 0) {
        throw std::invalid_argument(
            std::format("UE {} : nombre de crédits invalide ({})", code_, credits_));
    }
    if (!(coefficient_ > 0.0)) {
        throw std::invalid_argument(
            std::format("UE {} : coefficient invalide ({})", code_, coefficient_));
    }
}

} // namespace uin