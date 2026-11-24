#pragma once

#include "uin/regles.hpp"

namespace uin {

/// Note sur 20.
/// Invariant : noteMin <= valeur() <= noteMax. Objet valeur immuable.
class Note {
public:
    /// @throws std::invalid_argument si la valeur est hors de [noteMin ; noteMax]
    explicit Note(double valeur);

    /// Construit une note sur 20 à partir d'une note sur un autre barème (ex. 45 sur 60 -> 15).
    /// @throws std::invalid_argument si le barème n'est pas strictement positif
    ///         ou si la note obtenue est hors de [noteMin ; noteMax]
    [[nodiscard]] static Note depuisBarème(double valeur, double barème);

    [[nodiscard]] double valeur() const { return valeur_; }
    [[nodiscard]] bool estValidee() const { return valeur_ >= seuilValidation; }
    [[nodiscard]] Mention mention() const { return mentionPour(valeur_); }

private:
    double valeur_;
};

} // namespace uin