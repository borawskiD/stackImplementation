#include <iostream>
#include <random>
/* tworzymy strukturę stosu, w ramach tej struktury będziemy przechowywać trzy elementy - rozmiar, index elementu
 * bedącego aktualnie na szczycie stosu oraz wskaznik tablicy przechowującej stos.
 */
std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<int> dist(1,100);
struct stack {
    int maxSize;
    int topIndex;
    int *items;
};

struct stack* newStack(int capacity){
    struct stack *stck = (struct stack*) malloc(sizeof(struct stack));
    stck -> maxSize = capacity;
    stck -> topIndex = -1;
    stck -> items = (int*) malloc(sizeof(int) * capacity);
    return stck;
}
int size(struct stack *stck){
    return (stck-> topIndex + 1);
}

bool isFull(struct stack *stck){
    return (size(stck) == stck -> maxSize) ? true:false;
}

bool isEmpty(struct stack *stck){
    return (stck -> topIndex == -1) ? true:false;
}

void push(struct stack *stck, int x) {
    if (isFull(stck)){
        std::cout<<"Stack is full! \n";
    } else{
        stck ->topIndex++;
        stck->items[stck->topIndex] = x;
    }
}

void pop(struct stack *stck) {
    if (isEmpty(stck)){
        std::cout<<"Stack is empty! \n";
    } else{
        stck ->topIndex--;
    }
}
void insertRandom(struct stack *stck,int n){
    for (int i = 0; i<n; i++){
        push(stck, dist(gen));
    }
}
int top(struct stack *stck){
    if(!isEmpty(stck)) return stck->items[stck->topIndex];
    else std::cout <<"Stack is empty \n";
}
int main() {
    struct stack *stck = newStack(100);
    bool timeToEnd = false;
    do{
       std::cout<<"1. Push an item \n";
       std::cout<<"2. Pop an item \n";
       std::cout<<"3. Get top item \n";
       std::cout<<"4. Exit\n";
       int choice;
       std::cin >> choice;
       switch(choice){
           case 1:
               insertRandom(stck, 1);
               break;
           case 2:
               pop(stck);
               break;
           case 3:
               std::cout<<top(stck) << "\n";
               break;
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
