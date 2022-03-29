#include <iostream>
#include <random>
//obsluga liczb pseudolosowych
std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<int> dist(1,100);
/* tworzymy strukturę stosu, w ramach tej struktury będziemy przechowywać trzy elementy - rozmiar, index elementu
 * bedącego aktualnie na szczycie stosu oraz wskaznik tablicy przechowującej stos. */
struct stack {
    int maxSize;
    int topIndex;
    int *items;
};
//funkcja zwracajaca nowa strukture o maksymalnym rozmiarze capacity
struct stack* newStack(int capacity){
    //tworzę nowy wskaźnik na strukturę o rozmiarze wyzej zdefiniowego stosu
    struct stack *stck = (struct stack*) malloc(sizeof(struct stack));
    //ustawiam parametry struktury - maksymalny rozmiar, index najwyzszego elementu i rezerwuje pamiec do rozszerzania
    stck -> maxSize = capacity;
    stck -> topIndex = -1;
    stck -> items = (int*) malloc(sizeof(int) * capacity);
    //zwracam nasza strukture
    return stck;
}
//zwracam rozmiar struktury stosu - biorę indeks najwyzszego elementu i dodaje 1 (bo liczymy od 0 domyslnie)
int size(struct stack *stck){
    return (stck-> topIndex + 1);
}
//sprawdzam czy stos jest pelny, tj. czy rozmiar stosu jest rowny parametrowi maxSize
bool isFull(struct stack *stck){
    return (size(stck) == stck -> maxSize) ? true:false;
}
/* sprawdzam czy stos jest pusty, czyli czy najwyzszy indeks ma wartosc -1 (tak jest domyślnie +
 * podczas pozniejszych operacji pop rowniez dla pustej tablicy bedzie ustawial parametr na -1) */
bool isEmpty(struct stack *stck){
    std::cout << "Czy stos jest pusty? " <<  ((stck -> topIndex == -1) ? "Tak":"Nie") << " (parametr top index = " <<stck->topIndex<<")\n";
    return (stck -> topIndex == -1) ? true:false;
}

//metoda dodajaca elementy do naszego stosu (jesli jest to mozliwe)
void push(struct stack *stck, int x) {
    /* jeśli stos jest pełny, to nie mamy już gdzie dodawać kolejnych elementów, zatem
     * funkcja nie wykona żadnej czynności oprócz wyświetlania komunikatu;
     * w przeciwnym wypadku zwiększamy parametr topIndex o jeden,
     * i umieszczamy w strukturze pod indexem topIndex element podany
     * jako argument funkcji push (int x). */
    if (!isFull(stck)){
        stck ->topIndex++;
        stck->items[stck->topIndex] = x;
        std::cout<<"Zwiekszam indeks wierzchni na " << stck -> topIndex << "\n";
        std::cout<<"stck->items[" <<stck->topIndex<<"] = "<<stck -> items[stck->topIndex]<<"\n";
    } else{
        std::cout<<"Stos jest pelny, zatem nie mozna dodac elementu \n";
    }
}
/* funkcja pop służy do usuwania elementu od góry stosu, czyli od indexu oznaczonego jako topIndex. Usuwamy tylko
 * jeden element za każdym wywołaniem funkcji, jednocześnie dekrementując topIndex; oczywiście funkcja nic nie zrobi
 * gdy stos będzie pusty - poza wyświetleniem komunikatu. */
void pop(struct stack *stck) {
    if (isEmpty(stck)){
        std::cout<<"Stos jest pusty, nie moge usunac nastepnego elementu \n";
    } else{
        std::cout<<"Zatem usuwam element o indeksie "<<stck->topIndex<<" (wartosc elementu: "<<stck -> items[stck->topIndex]<<") i ustawiam parametr top index na: ";
        stck ->topIndex--;
        std::cout<<stck ->topIndex << "\n";
    }
}
//prosta funkcja umieszczajaca losowy element w stosie
int getRandomNumber(){
    return dist(gen);
}
//funkcja zwracajaca element znajdujacy się pod indeksem topIndex (czyli na samej górze, tzw. wierzchni)
int top(struct stack *stck){
    if(!isEmpty(stck)) {
        return stck->items[stck->topIndex];
    }
    /* dodalem obsluge wyjatkow, zeby mozna bylo dynamicznie wyswietlać błędy gdy stos jest pusty
     * w innych funkcjach tego nie dodaje, bo sa typu void i nie zwracają nic - tutaj muszę, żeby
     * uniknąć błędów exitowych dla pustego stosu (swoją drogą, bez tego też się kompiluje, ale dla
     * pustego stosu zwraca losowe numery */
    else throw std::invalid_argument("Stos jest pusty! \n");
}
int main() {
    //tworze wskaznik nowego stosu o maksymalnym rozmiarze 20 elementow
    struct stack *stck = newStack(20);
    //zapelniam go 10 losowymi liczbami
    std::cout<<"-----------------------------\n";
    std::cout<<"| Wstepne napelnienie stosu |\n";
    std::cout<<"-----------------------------\n";
    for (int i = 0; i<10; i++){
        push(stck,getRandomNumber());
    }
    //zmienna do obslugi petli w menu
    bool timeToEnd = false;
    //menu, prosta petla while + switch
    do{
        std::cout<<"---\n";
        std::cout<<"1. Push an item \n";
        std::cout<<"2. Pop an item \n";
        std::cout<<"3. Get top item \n";
        std::cout<<"4. Exit\n";
        std::cout<<"(1/2/3/4): ";
        int choice;
        std::cin >> choice;
        switch(choice){
            case 1:
                //wywołanie metody do pushowania, oraz sprawdzanie czy stos jest pełny.
               std::cout << "Czy stos jest pełny? " <<  (isFull(stck) ? "Tak" :" Nie") << "\n";
               push(stck,getRandomNumber());
               break;
            case 2:
               //wywoluje metode do usuwania pierwszego elementu stosu (jesli istnieje)
               pop(stck);
               break;
            case 3:
               /* wywoluje metode pokazujaca pierwszy element stosu (jesli istnieje) przy okazji
                * korzystając z obsługi błędów, ponieważ zwracam inta a nie jak przy poprzednikach
                * void. */
               try{
                   int a = top(stck);
                   std::cout<<"Pierwszy element stosu jest rowny: " <<a<< "\n";
               }
               catch(std::invalid_argument& e){
                   std::cout<<e.what();
               }
               break;
               //obsługa końca i elementów spoza zakresu
            case 4:
               timeToEnd = true;
               break;
            default:
               std::cout<<"Wrong input, try again \n";
               break;
            }
        }while(!timeToEnd);
    return 0;
}
/*
 * Dominik Borawski A1 215IC
 * Stos - implementacja z komentarzami */

/*
 * przykładowy output:
-----------------------------
| Wstepne napelnienie stosu |
-----------------------------
Zwiekszam indeks wierzchni na 0
stck->items[0] = 44
Zwiekszam indeks wierzchni na 1
stck->items[1] = 66
Zwiekszam indeks wierzchni na 2
stck->items[2] = 80
Zwiekszam indeks wierzchni na 3
stck->items[3] = 69
Zwiekszam indeks wierzchni na 4
stck->items[4] = 9
Zwiekszam indeks wierzchni na 5
stck->items[5] = 60
Zwiekszam indeks wierzchni na 6
stck->items[6] = 65
Zwiekszam indeks wierzchni na 7
stck->items[7] = 34
Zwiekszam indeks wierzchni na 8
stck->items[8] = 27
Zwiekszam indeks wierzchni na 9
stck->items[9] = 98
---
1. Push an item
2. Pop an item
3. Get top item
4. Exit
(1/2/3/4): 1
Czy stos jest pełny?  Nie
Zwiekszam indeks wierzchni na 10
stck->items[10] = 83
---
1. Push an item
2. Pop an item
3. Get top item
4. Exit
(1/2/3/4): 1
Czy stos jest pełny?  Nie
Zwiekszam indeks wierzchni na 11
stck->items[11] = 99
---
1. Push an item
2. Pop an item
3. Get top item
4. Exit
(1/2/3/4): 1
Czy stos jest pełny?  Nie
Zwiekszam indeks wierzchni na 12
stck->items[12] = 42
---
1. Push an item
2. Pop an item
3. Get top item
4. Exit
(1/2/3/4): 1
Czy stos jest pełny?  Nie
Zwiekszam indeks wierzchni na 13
stck->items[13] = 81
---
1. Push an item
2. Pop an item
3. Get top item
4. Exit
(1/2/3/4): 1
Czy stos jest pełny?  Nie
Zwiekszam indeks wierzchni na 14
stck->items[14] = 20
---
1. Push an item
2. Pop an item
3. Get top item
4. Exit
(1/2/3/4): 1
Czy stos jest pełny?  Nie
Zwiekszam indeks wierzchni na 15
stck->items[15] = 19
---
1. Push an item
2. Pop an item
3. Get top item
4. Exit
(1/2/3/4): 1
Czy stos jest pełny?  Nie
Zwiekszam indeks wierzchni na 16
stck->items[16] = 98
---
1. Push an item
2. Pop an item
3. Get top item
4. Exit
(1/2/3/4): 1
Czy stos jest pełny?  Nie
Zwiekszam indeks wierzchni na 17
stck->items[17] = 36
---
1. Push an item
2. Pop an item
3. Get top item
4. Exit
(1/2/3/4): 1
Czy stos jest pełny?  Nie
Zwiekszam indeks wierzchni na 18
stck->items[18] = 27
---
1. Push an item
2. Pop an item
3. Get top item
4. Exit
(1/2/3/4): 1
Czy stos jest pełny?  Nie
Zwiekszam indeks wierzchni na 19
stck->items[19] = 41
---
1. Push an item
2. Pop an item
3. Get top item
4. Exit
(1/2/3/4): 1
Czy stos jest pełny? Tak
Stos jest pelny, zatem nie mozna dodac elementu
---
1. Push an item
2. Pop an item
3. Get top item
4. Exit
(1/2/3/4): 2
Czy stos jest pusty? Nie (parametr top index = 19)
Zatem usuwam element o indeksie 19 (wartosc elementu: 41) i ustawiam parametr top index na: 18
---
1. Push an item
2. Pop an item
3. Get top item
4. Exit
(1/2/3/4): 3
Czy stos jest pusty? Nie (parametr top index = 18)
Pierwszy element stosu jest rowny: 27
---
1. Push an item
2. Pop an item
3. Get top item
4. Exit
(1/2/3/4): 2
Czy stos jest pusty? Nie (parametr top index = 18)
Zatem usuwam element o indeksie 18 (wartosc elementu: 27) i ustawiam parametr top index na: 17
---
1. Push an item
2. Pop an item
3. Get top item
4. Exit
(1/2/3/4): 3
Czy stos jest pusty? Nie (parametr top index = 17)
Pierwszy element stosu jest rowny: 36
---
1. Push an item
2. Pop an item
3. Get top item
4. Exit
(1/2/3/4): 2
Czy stos jest pusty? Nie (parametr top index = 17)
Zatem usuwam element o indeksie 17 (wartosc elementu: 36) i ustawiam parametr top index na: 16
---
1. Push an item
2. Pop an item
3. Get top item
4. Exit
(1/2/3/4): 3
Czy stos jest pusty? Nie (parametr top index = 16)
Pierwszy element stosu jest rowny: 98
---
1. Push an item
2. Pop an item
3. Get top item
4. Exit
(1/2/3/4): 2
Czy stos jest pusty? Nie (parametr top index = 16)
Zatem usuwam element o indeksie 16 (wartosc elementu: 98) i ustawiam parametr top index na: 15
---
1. Push an item
2. Pop an item
3. Get top item
4. Exit
(1/2/3/4): 3
Czy stos jest pusty? Nie (parametr top index = 15)
Pierwszy element stosu jest rowny: 19
---
1. Push an item
2. Pop an item
3. Get top item
4. Exit
(1/2/3/4): 2
Czy stos jest pusty? Nie (parametr top index = 15)
Zatem usuwam element o indeksie 15 (wartosc elementu: 19) i ustawiam parametr top index na: 14
---
1. Push an item
2. Pop an item
3. Get top item
4. Exit
(1/2/3/4): 3
Czy stos jest pusty? Nie (parametr top index = 14)
Pierwszy element stosu jest rowny: 20
---
1. Push an item
2. Pop an item
3. Get top item
4. Exit
(1/2/3/4): 2
Czy stos jest pusty? Nie (parametr top index = 14)
Zatem usuwam element o indeksie 14 (wartosc elementu: 20) i ustawiam parametr top index na: 13
---
1. Push an item
2. Pop an item
3. Get top item
4. Exit
(1/2/3/4): 3
Czy stos jest pusty? Nie (parametr top index = 13)
Pierwszy element stosu jest rowny: 81
---
1. Push an item
2. Pop an item
3. Get top item
4. Exit
(1/2/3/4): 2
Czy stos jest pusty? Nie (parametr top index = 13)
Zatem usuwam element o indeksie 13 (wartosc elementu: 81) i ustawiam parametr top index na: 12
---
1. Push an item
2. Pop an item
3. Get top item
4. Exit
(1/2/3/4): 3
Czy stos jest pusty? Nie (parametr top index = 12)
Pierwszy element stosu jest rowny: 42
---
1. Push an item
2. Pop an item
3. Get top item
4. Exit
(1/2/3/4): 2
Czy stos jest pusty? Nie (parametr top index = 12)
Zatem usuwam element o indeksie 12 (wartosc elementu: 42) i ustawiam parametr top index na: 11
---
1. Push an item
2. Pop an item
3. Get top item
4. Exit
(1/2/3/4): 3
Czy stos jest pusty? Nie (parametr top index = 11)
Pierwszy element stosu jest rowny: 99
---
1. Push an item
2. Pop an item
3. Get top item
4. Exit
(1/2/3/4): 4

Process finished with exit code 0
 */