#include <iostream>
#include <chrono>
#include <list> // For comparison
#include "myList.hpp"

template<typename T>
bool arrCmp(T* arr1, T* arr2, int len){
    for(int i=0; i<len; i++){
        if(arr1[i] != arr2[i]){
            return false;
        }
    }
    return true;
}

#define VALIDATE_N 1000


int main(){
    gamingList::list<int> lst;
    std::list<int> s_lst;

    for(int i=0; i<VALIDATE_N; i++){
        lst.append(i);
        s_lst.push_back(i);
    }

    // Visit random elements of each list and place them into an array
    std::list<int>::iterator s_it = s_lst.begin();
    int* arr = new int[VALIDATE_N];
    int* arr2 = new int[VALIDATE_N];
    for(int i=0; i<VALIDATE_N; i++){
        int idx = rand()%lst.len();
        arr[i] = lst.get(idx);
        s_it = s_lst.begin();
        std::advance(s_it, idx);
        arr2[i] = *s_it;
    }
    bool valid = arrCmp(arr, arr2, VALIDATE_N);
    delete arr2;
    delete arr;
    if(!valid){
        std::cout << "ERROR: Random element validation failed!" << std::endl;
        return 1;
    }
    std::cout << "Random element validation successful!" << std::endl;

    // Visit sequential elements of each list and place them into an array
    s_it = s_lst.begin();
    arr = new int[VALIDATE_N];
    arr2 = new int[VALIDATE_N];
    for(int i=0; i<VALIDATE_N; i++){
        arr[i] = lst.get(i);
        arr2[i] = *s_it;
        s_it++;
    }
    valid = arrCmp(arr, arr2, VALIDATE_N);
    delete arr2;
    delete arr;
    if(!valid){
        std::cout << "ERROR: Sequential element validation failed!" << std::endl;
        return 1;
    }
    std::cout << "Sequential element validation successful!" << std::endl;

    // Remove half of the elements from each list randomly
    for(int i=0; i<VALIDATE_N/2; i++){
        int idx = rand()%lst.len();
        lst.remove(idx);
        s_it = s_lst.begin();
        std::advance(s_it, idx);
        s_lst.erase(s_it);
    }

    // And prepend some stuff too
    for(int i=0; i<VALIDATE_N/2; i++){
        lst.insert(0, i);
        s_lst.push_front(i);
    }

    // Now get random elements from each list and place them into an array again
    s_it = s_lst.begin();
    arr = new int[VALIDATE_N];
    arr2 = new int[VALIDATE_N];
    for(int i=0; i<VALIDATE_N; i++){
        int idx = rand()%lst.len();
        arr[i] = lst.get(idx);
        s_it = s_lst.begin();
        std::advance(s_it, idx);
        arr2[i] = *s_it;
    }
    valid = arrCmp(arr, arr2, VALIDATE_N);
    delete arr2;
    delete arr;
    if(!valid){
        std::cout << "ERROR: Random element validation failed after removal and prepending!" << std::endl;
        return 1;
    }
    std::cout << "Random element validation successful after removal and prepending!" << std::endl;

    return 0;
}