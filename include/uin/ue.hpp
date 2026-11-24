#pragma once

#include <string>

namespace uin {

/// Unité d'enseignement.
/// Invariants : code et intitulé non vides ; credits() > 0 ; coefficient() > 0.
class UE {
public:
    /// @throws std::invalid_argument si un invariant n'est pas respecté.
    UE(std::string code, std::string intitule, int credits, double coefficient);

    /// UE dont le coefficient est égal au nombre de crédits.
    /// @throws std::invalid_argument si un invariant n'est pas respecté.
    UE(std::string code, std::string intitule, int credits);

    [[nodiscard]] const std::string& code() const { return code_; }
    [[nodiscard]] const std::string& intitule() const { return intitule_; }
    [[nodiscard]] int credits() const { return credits_; }
    [[nodiscard]] double coefficient() const { return coefficient_; }

private:
    std::string code_;
    std::string intitule_;
    int credits_;
    double coefficient_;
};

} // namespace uin