//======== Copyright (c) 2021, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     Test Driven Development - priority queue code
//
// $NoKeywords: $ivs_project_1 $tdd_code.cpp
// $Author:     LENKA SOKOVA <xsokov01@stud.fit.vutbr.cz>
// $Date:       $2021-03-10
//============================================================================//
/**
 * @file tdd_code.cpp
 * @author LENKA SOKOVA
 * 
 * @brief Implementace metod tridy prioritni fronty.
 */

#include <stdlib.h>
#include <stdio.h>

#include "tdd_code.h"

//============================================================================//
// ** ZDE DOPLNTE IMPLEMENTACI **
//
// Zde doplnte implementaci verejneho rozhrani prioritni fronty (Priority Queue)
// 1. Verejne rozhrani fronty specifikovane v: tdd_code.h (sekce "public:")
//    - Konstruktor (PriorityQueue()), Destruktor (~PriorityQueue())
//    - Metody Insert/Remove/Find a GetHead
//    - Pripadne vase metody definovane v tdd_code.h (sekce "protected:")
//
// Cilem je dosahnout plne funkcni implementace prioritni fronty implementovane
// pomoci tzv. "double-linked list", ktera bude splnovat dodane testy 
// (tdd_tests.cpp).
//============================================================================//

PriorityQueue::PriorityQueue()
{
    m_pHead = NULL;
}

PriorityQueue::~PriorityQueue()
{
    for(int i = 0; i < Length(); i++){
        Remove(m_pHead->value);
    }

}

void PriorityQueue::Insert(int value)
{
    Element_t *actual_element_t = m_pHead;
    Element_t *new_element_t = (Element_t*)malloc(sizeof(Element_t));

    if (new_element_t == nullptr) return;

    new_element_t->value = value;
    new_element_t->pNext = nullptr;

    //list je prazdny
    if(m_pHead == nullptr){
        m_pHead = new_element_t;
        return;
    }

    //pridanie najmensieho prvku -> na zaciatok listu
    else if(value > actual_element_t->value){
        m_pHead = new_element_t;
        new_element_t->pNext = actual_element_t;
        return;
    }

    while(true){

        //pridanie noveho prvku na koniec listu
        if(actual_element_t->pNext == nullptr && value < actual_element_t->value){
            actual_element_t->pNext = new_element_t;
            break;
        }

        //pridanie noveho prvku do stredu listu
        else if(value > actual_element_t->pNext->value){
            new_element_t->pNext = actual_element_t->pNext;
            actual_element_t->pNext = new_element_t;

            break;
        }
        actual_element_t = actual_element_t->pNext;
    }
}

bool PriorityQueue::Remove(int value)
{
    Element_t *actual_element_t = m_pHead;
    Element_t *delete_element_t;

    // list je prazdny
    if(m_pHead == nullptr){
        return false;
    }

    // Odstranenie prveho prvku
    else if(value == actual_element_t->value){
        m_pHead = actual_element_t->pNext;
        free(actual_element_t);
        return true;
    }

    while(value != actual_element_t->pNext->value){
        if(actual_element_t->pNext->pNext == nullptr){
            return false;
        }

        actual_element_t = actual_element_t->pNext;
    }

    //Odstranenie prvku z pola
    delete_element_t = actual_element_t->pNext;
    actual_element_t->pNext = actual_element_t->pNext->pNext;
    free(delete_element_t);

    return true;
}

PriorityQueue::Element_t *PriorityQueue::Find(int value)
{
    Element_t *actual_element_t = m_pHead;

    if (m_pHead == nullptr){
        return NULL;
    }

    while(actual_element_t->value != value){

        // prvok sa nenachadza v liste
        if(actual_element_t->pNext == nullptr){
            return NULL;
        }

        actual_element_t = actual_element_t->pNext;
    }

    return actual_element_t;
}

size_t PriorityQueue::Length()
{
    Element_t *actual_element_t = m_pHead;

    if (m_pHead == nullptr){
        return 0;
    }

    int cnt_length = 1;

    while(actual_element_t->pNext != nullptr){
        cnt_length++;
        actual_element_t = actual_element_t->pNext;
    }

	return cnt_length;
}

PriorityQueue::Element_t *PriorityQueue::GetHead()
{
    return m_pHead;
}

/*** Konec souboru tdd_code.cpp ***/
