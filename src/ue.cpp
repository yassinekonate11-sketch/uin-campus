#include "uin/ue.hpp"

#include <format>
#include <stdexcept>
#include <utility>

namespace uin {

// Constructeur principal
UE::UE(std::string code, std::string intitule, int credits, double coefficient)
    : code_(std::move(code)),
      intitule_(std::move(intitule)),
      credits_(credits),
      coefficient_(coefficient)
{
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

// Constructeur délégué
UE::UE(std::string code, std::string intitule, int credits)
    : UE(std::move(code), std::move(intitule), credits, static_cast<double>(credits))
{
    // Toutes les vérifications sont faites par le constructeur principal !
}

} // namespace uin