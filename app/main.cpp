#include "uin/etudiant.hpp"
#include "uin/regles.hpp"

#include <exception>
#include <print>

int main()
{
    try {
        // 1. Création de l'étudiant
        uin::Etudiant etudiant{"UIN-2026-001", "Konaté", "Yassine"};
        
        // 2. Création des UE
        uin::UE ue1{"INF101", "Programmation C++", 6, 3.0};
        uin::UE ue2{"MAT101", "Mathématiques", 4, 2.0};
        
        // 3. Enregistrement des notes
        etudiant.enregistrerResultat(ue1, uin::Note{15.5});
        etudiant.enregistrerResultat(ue2, uin::Note{12.0});
        
        // 4. Affichage des résultats
        std::println("Étudiant : {}", etudiant.nomComplet());
        std::println("Moyenne  : {:.2f}", etudiant.moyenne());
        std::println("Crédits  : {}/{}", etudiant.creditsObtenus(), etudiant.creditsInscrits());
        std::println("Mention  : {}", uin::libelle(etudiant.mention()));
        
        std::println("\n--- Test des invariants ---");
        
        // 5. Test de sécurité : on essaie de créer une note de 25 (ce qui est interdit)
        // Le programme devrait attraper l'erreur et l'afficher proprement au lieu de planter.
        uin::Note noteInvalide{25.0};
        
    } catch (const std::exception& e) {
        std::println(stderr, "\nErreur interceptée : {}", e.what());
    }
    
    return 0;
}