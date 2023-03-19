#include "AdptArray.h"
#include "book.h"
#include "Person.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

struct AdptArray_{
    PElement* arr;
    COPY_FUNC copy_func;
    DEL_FUNC del_func;
    PRINT_FUNC print_func;
    int size;  // array size
};


// Initialize an empty array
PAdptArray CreateAdptArray(COPY_FUNC copy_func, DEL_FUNC del_func,PRINT_FUNC print_func){
    PAdptArray ptr = (PAdptArray) malloc(sizeof(struct AdptArray_));
     if (ptr == NULL) {
        printf("Memory not allocated.\n");
        return NULL;
    }

    ptr->arr = NULL;
    ptr->copy_func = copy_func;
    ptr->del_func = del_func;
    ptr->print_func = print_func;
    ptr->size = 0;

    return ptr;
}

// Frees the memory of the object including its elements
void DeleteAdptArray(PAdptArray ptr){
    for (int i = 0; i < ptr->size; i++) {
        if(ptr->arr[i] != NULL){
            // free element i
            ptr->del_func(ptr->arr[i]);
        }
    }
    free(ptr->arr);
    free(ptr);
}

// Saves a copy of the element in the requested location
// Frees the old element if it exists
Result SetAdptArrayAt(PAdptArray ptr_adp, int index, PElement ptr_element){
    if(index >= ptr_adp->size){
    // the array is not big enough

    // realloc
    ptr_adp->arr = (PElement*) realloc(ptr_adp->arr, (index+1)*sizeof(PElement));
     if (ptr_adp->arr == NULL) {
        printf("Memory not allocated.\n");
        return FAIL;
    }

    // fill the other new cells with NULL
    for (int i = ptr_adp->size; i < index+1 ; i++) {
        ptr_adp->arr[i] = NULL;
    }

    // resize
    ptr_adp->size = index+1;
    }


    if(ptr_adp->arr[index] != NULL){
        // there is an element in this index
        // free the element
        ptr_adp->del_func(ptr_adp->arr[index]);
    }


    // finaly, copy the element
    ptr_adp->arr[index] = ptr_adp->copy_func(ptr_element);
    return SUCCESS;
}


// Gets an index and returns a copy of the element at this location
PElement GetAdptArrayAt(PAdptArray ptr, int index){
    if(index >= ptr->size){
    // the array is not big enough
        return NULL;
    }

    if(ptr->arr[index] != NULL){
    // there is an element that saved in this index
        return ptr->copy_func(ptr->arr[index]);
    }

    return NULL;
}

// Returns the size of the array (-1 when the array was not initialized successfully)
int GetAdptArraySize(PAdptArray ptr){
    if(ptr != NULL)
        return ptr->size;
    return -1;
}

// Prints the elements in the array
void PrintDB(PAdptArray ptr){
     for (int i = 0; i < ptr->size; i++) {
        if(ptr->arr[i] != NULL){
            ptr->print_func(ptr->arr[i]);
        }
    }
}