#include "test.hpp"

#include <iostream>
#include <random> // Per generare numeri casuali
#include <vector>

// Inclusione delle librerie
#include "../vector/vector.hpp" 
#include "../list/list.hpp"     
#include "../heap/vec/heapvec.hpp"
#include "../pq/heap/pqheap.hpp"

using namespace std;
using namespace lasd;

// Funzione ausiliaria per stampare errori se la condizione è falsa
void my_assert(bool condition, const string& message) {
    if (!condition) {
        cout << "[FAIL] " << message << endl;
    } else {
        cout << "[OK] " << message << endl;
    }
}

template <typename Data>
void print_vec(Vector<Data>& vec) {
    cout << "( ";
    for (ulong i = 0; i < vec.Size(); ++i) {
        cout << vec[i] << " ";
    }
    cout << ")" << endl;
}

void test_vector() {
    cout << "\n--- Inizio Test Vector (Custom) ---" << endl;

    // Test Costruttore e Resize
    Vector<int> vec(5);
    for(ulong i=0; i<vec.Size(); ++i) vec[i] = i;
    
    my_assert(vec.Size() == 5, "Dimensione iniziale 5");
    my_assert(vec.Front() == 0, "Front() corretto");
    my_assert(vec.Back() == 4, "Back() corretto");

    // Test Resize (espansione)
    vec.Resize(10);
    my_assert(vec.Size() == 10, "Resize a 10");
    vec[9] = 99;
    my_assert(vec[9] == 99, "Accesso a nuovo indice dopo resize");

    // Test Resize (contrazione)
    vec.Resize(2);
    my_assert(vec.Size() == 2, "Resize a 2 (taglio)");
    my_assert(vec.Back() == 1, "Nuovo Back() dopo taglio");

    // Test Clear
    vec.Clear();
    my_assert(vec.Size() == 0, "Vettore svuotato con Clear()");
    my_assert(vec.Empty(), "Controllo Empty()");
}

void test_list() {
    cout << "\n--- Inizio Test List (Custom) ---" << endl;

    List<string> lista;
    my_assert(lista.Empty(), "Lista creata vuota");

    // Test Inserimenti (Front/Back) 
    lista.InsertAtFront("Mondo");
    lista.InsertAtFront("Ciao");
    lista.InsertAtBack("!");
    
    // Lista attesa: Ciao -> Mondo -> !
    my_assert(lista.Front() == "Ciao", "InsertAtFront funziona");
    my_assert(lista.Back() == "!", "InsertAtBack funziona");
    my_assert(lista.Size() == 3, "Size corretta (3)");

    // Test Rimozioni
    lista.RemoveFromFront(); // Via "Ciao"
    my_assert(lista.Front() == "Mondo", "RemoveFromFront funziona");
    
    // Test FrontNRemove (leggi e rimuovi)
    string val = lista.FrontNRemove(); // Legge "Mondo" e lo toglie
    my_assert(val == "Mondo", "FrontNRemove restituisce valore corretto");
    my_assert(lista.Front() == "!", "Rimasto solo l'ultimo elemento");

    lista.Clear();
    my_assert(lista.Size() == 0, "Lista pulita con Clear()");
}

void test_heapsort() {
    cout << "\n--- Inizio Test HeapSort (HeapVec) ---" << endl;

    // Creazione di un vettore disordinato
    Vector<int> vec(10);
    for(ulong i=0; i<10; ++i) vec[i] = (i * 7) % 13; // Numeri pseudo-casuali
    
    cout << "Vettore originale: ";
    print_vec(vec);

    // Creazione dello HeapVec a partire dal vettore (dovrebbe fare Heapify nel costruttore)
    HeapVec<int> myHeap(vec);
    
    my_assert(myHeap.IsHeap(), "Costruzione HeapVec (IsHeap check)");
    
    cout << "Struttura Heap: ";
    print_vec(myHeap);

    // Testo il Sort
    myHeap.Sort();
    
    cout << "Dopo Sort(): ";
    print_vec(myHeap);

    // Verifica ordinamento
    bool sorted = true;
    for(ulong i=0; i < myHeap.Size()-1; ++i) {
        if(myHeap[i] > myHeap[i+1]) {
            sorted = false;
            break;
        }
    }
    my_assert(sorted, "Il vettore e' ordinato in modo crescente?");
}

void test_priority_queue() {
    cout << "\n--- Inizio Test PriorityQueue (PQHeap) ---" << endl;

    PQHeap<string> pq;
    
    // Inserimento
    pq.Insert("Anna");
    pq.Insert("Zoro"); // Dovrebbe andare in testa (Max-Heap lessicografico)
    pq.Insert("Luca");
    pq.Insert("Mario");

    cout << "Tip (dovrebbe essere Zoro): " << pq.Tip() << endl;
    my_assert(pq.Tip() == "Zoro", "Controllo Tip()");

    // Cambio priorità: "Mario" (che è da qualche parte) diventa "Aaaa" (minima)
   // in un MaxHeap su array, Zoro è a indice 0. 
    // Provo a cambiare la radice (Zoro) facendola diventare piccolissima per vederla scendere.
    
    cout << "Cambio priorita' radice (Zoro -> Alberto)..." << endl;
    pq.Change(0, "Alberto"); 
    // Ora la radice non è più Zoro, dovrà scendere.
    
    cout << "Nuova Tip: " << pq.Tip() << endl;
    // Mario o Luca dovrebbero essere saliti. "Mario" > "Luca" > "Anna" > "Alberto"
    my_assert(pq.Tip() == "Mario", "Dopo Change(0, Alberto), Mario e' il nuovo massimo?");

    // Estrazione completa
    cout << "Estrazione ordine decrescente: ";
    while(!pq.Empty()) {
        cout << pq.TipNRemove() << " ";
    }
    cout << endl;
}

void mytest() {
    cout << endl << "~*~*~ I MIEI TEST PERSONALIZZATI (zmytest) ~*~*~" << endl;
    
    try {
        // test parte 1
        test_vector();
        test_list(); 
        
        // Test parte 2
        test_heapsort();
        test_priority_queue();
    } catch (exception& e) {
        cout << "ECCEZIONE INATTESA: " << e.what() << endl;
    }
    
    cout << "~*~*~ FINE MIEI TEST ~*~*~" << endl << endl;
}