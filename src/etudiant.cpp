#include "uin/etudiant.hpp"

#include <cassert>
#include <format>
#include <stdexcept>
#include <utility>

namespace uin {

Etudiant::Etudiant(Identite identite) : identite_(std::move(identite))
{
    if (identite_.matricule.empty()) {
        throw std::invalid_argument("Etudiant : le matricule est obligatoire");
    }
    if (identite_.nom.empty() || identite_.prenom.empty()) {
        throw std::invalid_argument(std::format(
            "Etudiant {} : le nom et le prénom sont obligatoires", identite_.matricule));
    }
}

// Constructeur à liste
Etudiant::Etudiant(Identite identite, std::initializer_list<ResultatUE> resultats)
    : Etudiant(std::move(identite)) // Délégation pour vérifier l'identité
{
    for (const auto& [ue, note] : resultats) {
        enregistrerResultat(ue, note); // Préserve l'invariant
    }
}

std::string Etudiant::nomComplet() const
{
    return std::format("{} {}", identite_.prenom, identite_.nom);
}

void Etudiant::enregistrerResultat(const UE& ue, Note note)
{
    for (ResultatUE& resultat : resultats_) {
        if (resultat.ue.code() == ue.code()) {
            resultat.note = note;
            return;
        }
    }
    resultats_.push_back(ResultatUE{.ue = ue, .note = note});
}

double Etudiant::moyenne() const
{
    assert(aDesResultats() && "moyenne() : aucun résultat");
    double sommeNotes = 0.0;
    double sommeCoefficients = 0.0;
    for (const auto& res : resultats_) {
        sommeNotes += res.note.valeur() * res.ue.coefficient();
        sommeCoefficients += res.ue.coefficient();
    }
    return sommeNotes / sommeCoefficients;
}

int Etudiant::creditsObtenus() const
{
    int credits = 0;
    for (const auto& res : resultats_) {
        if (res.note.estValidee()) {
            credits += res.ue.credits();
        }
    }
    return credits;
}

int Etudiant::creditsInscrits() const
{
    int credits = 0;
    for (const auto& res : resultats_) {
        credits += res.ue.credits();
    }
    return credits;
}

Mention Etudiant::mention() const
{
    assert(aDesResultats() && "mention() : aucun résultat");
    return mentionPour(moyenne());
}

} // namespace uin