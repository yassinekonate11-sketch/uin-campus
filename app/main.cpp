#include "uin/etudiant.hpp"
#include "uin/regles.hpp"
#include "uin/saisie.hpp"
#include "uin/version.hpp"

#include <cstdlib>
#include <exception>
#include <format>
#include <print>
#include <string>
#include <utility>

namespace {

[[nodiscard]] uin::UE saisirUE(int numero)
{
    std::println("\nUE {}", numero);
    std::string code = uin::lireTexte(" Code : ");
    std::string intitule = uin::lireTexte(" Intitulé : ");
    const int credits = uin::lireEntier(" Credits (1 à 30) : ", 1, 30);
    const int coefficient = uin::lireEntier(" Coefficient (1 à 10, 0 = égal aux crédits) : ", 0, 10);

    if (coefficient == 0) {
        return uin::UE(std::move(code), std::move(intitule), credits); // Constructeur délégué
    }
    return uin::UE(std::move(code), std::move(intitule), credits, static_cast<double>(coefficient));
}

} // namespace

int main()
{
    try {
        std::println("UIN-Campus {} - Relevé d'un étudiant\n", uin::version());

        // On crée d'abord l'Identite (qui est une struct, donc les initialiseurs désignés marchent)
        // puis on la passe au constructeur de Etudiant.
        uin::Etudiant etudiant{
            uin::Identite{
                .matricule = uin::lireTexte("Matricule : "),
                .nom = uin::lireTexte("Nom : "),
                .prenom = uin::lireTexte("Prénom : ")
            }
        };

        const int nbUE = uin::lireEntier("Nombre d'UE (1 à 30) : ", 1, 30);
        for (int i{1}; i <= nbUE; ++i) {
            const uin::UE ue = saisirUE(i);
            etudiant.enregistrerResultat(ue, uin::Note{uin::lireNote(" Note : ")});
        }

        std::println("\n{:-<44}", "");
        std::println("Étudiant : {}", etudiant.nomComplet());
        std::println("Moyenne  : {:.2f}", etudiant.moyenne());
        std::println("Crédits  : {}/{}", etudiant.creditsObtenus(), etudiant.creditsInscrits());
        std::println("Mention  : {}", uin::libelle(etudiant.mention()));
        std::println("{:-<44}", "");

    } catch (const std::exception& e) {
        std::println(stderr, "Erreur : {}", e.what());
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}