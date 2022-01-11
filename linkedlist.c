/*********************************************************************************
**                                                                              **
**      Copyleft 1991-2021 by Sandroid75 with GNU General Public License.       **
**                                                                              **
**                                                                              **
**  Redistribution and use in source and binary forms, with or without          **
**  modification, are permitted provided that the following conditions are met: **
**                                                                              **
**   * Redistributions of source code must retain the above copyleft notice,    **
**     this list of conditions and the following disclaimer.                    **
**   * Redistributions in binary form must reproduce the above copyleft         **
**     notice, this list of conditions and the following disclaimer in the      **
**     documentation and/or other materials provided with the distribution.     **
**   * Neither the name of Sandroid75 nor the names of its contributors may     **
**     be used to endorse or promote products derived from this software        **
**     without specific prior written permission.                               **
**                                                                              **
**  THIS SOFTWARE IS PROVIDED BY THE COPYLEFT HOLDERS AND CONTRIBUTORS "AS IS"  **
**  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE   **
**  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE  **
**  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYLEFT OWNER OR CONTRIBUTORS BE     **
**  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR         **
**  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF        **
**  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS    **
**  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN     **
**  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)     **
**  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE  **
**  POSSIBILITY OF SUCH DAMAGE.                                                 **
**                                                                              **
**  This code was made by Sandroid75 to illustrate various C language powers.   **
**                                                                              **
**  My recommendations for developing robust C code are:                        **
**  - first of all read The C Programming Language: ANSI C Version by K&R (C)   **
**  - after read K&R keep always in mind rules and methods                      **
**  - one of the most characteristics and powers of the C is the pointers       **
**  - pointers are very helpfull and flexibile to write efficient code          **
**  - pointers can be dangerous for stable code if you forget the rules         **
**  - if you use pointers for list of datas don't forget to reserve memory      **
**  - if you use pointers for list of datas don't forget to release memory      **
**  - write well-formatted code                                                 **
**  - only good formatted code makes the code readable                          **
**  - good formatting code reduces the risk of errors                           **
**  - good formatting code facilitates the debugging                            **
**  - good formatting code facilitates the maintenences                         **
**  - good formatting code facilitates future implementantions                  **
**  - commenting the code is another good and necessary practice                **
**  - commenting the code means understanding what you are doing                **
**  - commenting the code means understanding what you have done                **
**  - commenting the code is not a waste of time                                **
**  - at the last but not least, remember rules and methods                     **
**                                                                              **
**                  Have fun with C programming by Sandroid75                   **
**                                                                              **
**********************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <errno.h>
#include "linkedlist.h"

list_t *newnode(const int data) {
    list_t *node = (list_t *) malloc(sizeof(list_t)); //reserve memory for the new node
    
    if(!node) { //if malloc() fail...
        fprintf(stderr, "malloc fail: %s\n", strerror(errno)); //print the error
    } else { //else malloc works
        node->data = data; //set the data of list from the argument val
        node->next = NULL; //the new node will be the last of list
    }
    
    return (list_t *) node; //return NULL if malloc() fail, otherwise return the pointer to new node
}

list_t *listlast(list_t *list) { //walk thru the list up to last node
    while(list && list->next) { //while list and next node are true
        list = list->next; //step to next node
    }
        
    return (list_t *) list; //resturn last node or NULL if the list is empty
}

list_t *listadd(list_t **list, const int val) { //add a new node with val at the end of the list, return the pointer to new node
    list_t *node = newnode(val); //allocate memory for new node
    
    if(!node) { //if newnode() fail...
        fprintf(stderr, "%s: memory allocation error\n", __func__);
    }
    
    if(!(*list)) { //if the list is empty
        (*list) = node; //this is the first node of list
        
        return node; //return the new node
    }
    
    list_t *ptr = listlast(*list); //get the last node pointer
    ptr->next = node; //assign the new node to next pointer of tail

    return (list_t *) node; //return the pointer of the new node
}

list_t *listpush(list_t **list, const int val) { //push a new node with val at begin of the list, return the pointer to new node
    list_t *node = newnode(val); //allocate memory for new node
    
    if(!node) { //if newnode() fail...
        fprintf(stderr, "%s: memory allocation error\n", __func__);
    } else { //else newnode() it work well 
        node->next = (*list); //push the new node at begin of the list if the list is empty the next node will be NULL
        (*list) = node; //set the new starting point of the list
    }

    return (list_t *) node; //return the pointer of the new node
}

void listfree(list_t **list) { //frees memory occupied by the list
    list_t *ptrNext;
    
    if(!list || !(*list)) { //if list is empty
        return; //void
    }
    
    while((*list)) { //walk thru the enteire list
        ptrNext = (*list)->next; //point to the next node of the list before destroy the current
        free(*list); //destroy the current node of the list
        (*list) = ptrNext; //go to next node of the list
    }

    list = NULL;
    
    return; //void
}
