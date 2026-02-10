#include "zlasdtest/test.hpp"

#include "zmytest/test.cpp" 

#include <iostream>

/* ************************************************************************** */

int main() {
    std::cout << "LASD Libraries 2025" << std::endl;

    int scelta = -1;

    while (scelta != 0) {
        std::cout << "\n-----------------------------------------" << std::endl;
        std::cout << "           MENU PRINCIPALE              " << std::endl;
        std::cout << "-----------------------------------------" << std::endl;
        std::cout << "  1. Esegui test zlasdtest" << std::endl;
        std::cout << "  2. Esegui i miei test mytest" << std::endl;
        std::cout << "  0. Esci" << std::endl;
        std::cout << "-----------------------------------------" << std::endl;
        std::cout << "Inserisci la tua scelta: ";
        
        std::cin >> scelta;

        // Gestione input non valido
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            std::cout << "\n[ERRORE] Input non valido. Riprova." << std::endl;

            scelta = -1;
            continue;
        }

        std::cout << std::endl;

        switch (scelta) {
            case 1:
                std::cout << "Avvio test zlasdtest.." << std::endl;
                lasdtest(); 
                break;
            
            case 2:
                std::cout << "Avvio i test personalizzati..." << std::endl;
                mytest();  
                break;

            case 0:
                std::cout << "Uscita dal programma. Arrivederci!" << std::endl;
                break;

            default:
                std::cout << "[ERRORE] Scelta non valida. Riprova." << std::endl;
                break;
        }
    }

    return 0;
}