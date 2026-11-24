#include "uin/etudiant.hpp"

#include <cassert>
#include <format>
#include <stdexcept>
#include <utility>

namespace uin {

Etudiant::Etudiant(std::string matricule, std::string nom, std::string prenom)
    : matricule_(std::move(matricule)), nom_(std::move(nom)), prenom_(std::move(prenom))
{
    if (matricule_.empty()) {
        throw std::invalid_argument("Etudiant : le matricule est obligatoire");
    }
    if (nom_.empty() || prenom_.empty()) {
        throw std::invalid_argument(
            std::format("Etudiant {} : le nom et le prénom sont obligatoires", matricule_));
    }
}

std::string Etudiant::nomComplet() const
{
    return std::format("{} {}", prenom_, nom_);
}

void Etudiant::enregistrerResultat(const UE& ue, Note note)
{
    for (ResultatUE& resultat : resultats_) {
        if (resultat.ue.code() == ue.code()) {
            resultat.note = note; // Remplace la note existante
            return;
        }
    }
    resultats_.push_back({ue, note});
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