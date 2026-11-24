#pragma once

#include "uin/note.hpp"
#include "uin/regles.hpp"
#include "uin/ue.hpp"

#include <initializer_list>
#include <string>
#include <vector>

namespace uin {

/// Identité civile d'un étudiant.
struct Identite {
    std::string matricule;
    std::string nom;
    std::string prenom;
};

/// Note obtenue par un étudiant dans une UE.
struct ResultatUE {
    UE ue;
    Note note;
};

/// Étudiant inscrit à l'UIN.
class Etudiant {
public:
    /// @throws std::invalid_argument si l'identité est invalide
    explicit Etudiant(Identite identite);

    /// Étudiant et ses premiers résultats.
    /// @throws std::invalid_argument si l'identité est invalide
    Etudiant(Identite identite, std::initializer_list<ResultatUE> resultats);

    [[nodiscard]] const std::string& matricule() const { return identite_.matricule; }
    [[nodiscard]] const std::string& nom() const { return identite_.nom; }
    [[nodiscard]] const std::string& prenom() const { return identite_.prenom; }
    [[nodiscard]] std::string nomComplet() const;

    void enregistrerResultat(const UE& ue, Note note);

    [[nodiscard]] const std::vector<ResultatUE>& resultats() const { return resultats_; }
    [[nodiscard]] bool aDesResultats() const { return !resultats_.empty(); }

    [[nodiscard]] double moyenne() const;
    [[nodiscard]] int creditsObtenus() const;
    [[nodiscard]] int creditsInscrits() const;
    [[nodiscard]] Mention mention() const;

private:
    Identite identite_;
    std::vector<ResultatUE> resultats_;
};

} // namespace uin