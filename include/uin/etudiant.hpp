#pragma once

#include "uin/note.hpp"
#include "uin/regles.hpp"
#include "uin/ue.hpp"

#include <string>
#include <vector>

namespace uin {

/// Note obtenue par un étudiant dans une UE.
struct ResultatUE {
    UE ue;
    Note note;
};

/// Étudiant inscrit à l'UIN.
/// Invariants : matricule, nom et prénom non vides ; au plus un résultat par code d'UE.
class Etudiant {
public:
    /// @throws std::invalid_argument si le matricule, le nom ou le prénom est vide
    Etudiant(std::string matricule, std::string nom, std::string prenom);

    [[nodiscard]] const std::string& matricule() const { return matricule_; }
    [[nodiscard]] const std::string& nom() const { return nom_; }
    [[nodiscard]] const std::string& prenom() const { return prenom_; }
    [[nodiscard]] std::string nomComplet() const;

    /// Enregistre la note obtenue dans une UE.
    /// Si l'UE figure déjà dans les résultats, sa note est remplacée.
    void enregistrerResultat(const UE& ue, Note note);

    [[nodiscard]] const std::vector<ResultatUE>& resultats() const { return resultats_; }
    [[nodiscard]] bool aDesResultats() const { return !resultats_.empty(); }

    /// Moyenne pondérée par les coefficients des UE.
    /// @pre aDesResultats()
    [[nodiscard]] double moyenne() const;

    /// Somme des crédits des UE validées.
    [[nodiscard]] int creditsObtenus() const;

    /// Somme des crédits de toutes les UE présentes dans les résultats.
    [[nodiscard]] int creditsInscrits() const;

    /// @pre aDesResultats()
    [[nodiscard]] Mention mention() const;

private:
    std::string matricule_;
    std::string nom_;
    std::string prenom_;
    std::vector<ResultatUE> resultats_;
};

} // namespace uin