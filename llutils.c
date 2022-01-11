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

#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include "linkedlist.h"

int listcount(list_t *list) { //return the numbers of valid node of a list
    int count;
    
    for(count = 0; list; count++) { //walk thru valid node of the list
        list = list->next; //next step node
    }
    
    return count; //return the numbers of valid node
}

int listsplit(list_t *list, const int upto, list_t **head, list_t **tail) { //split the list in two counting the elments
    int rest;
    
    for(rest = 0; list && rest < upto; rest++) { //walk thru the valid node of the list up to specified index value
        listadd(head, list->data); //adding current node value to new list
        list = list->next; //next step node
    }
    
    for(rest = 0; list; rest++) { //while the current node of list is valid (not NULL) count the rest of node for splitted list
        listadd(tail, list->data); //create the next node of the list
        list = list->next; //next step node
    }
    
    return rest; //return the number of nodes stored in the second list
}

void listcat(list_t **head, list_t *tail) { //concatene two lists, but don't forget that it's not necessary free the second after concatenation
    list_t *ptr = listlast(*head); //get the last node pointer
    ptr->next = tail; //point to last node of the list to new node
    
    return; //void
}

int countdigit(const int val) { //recursive version return the numbers of digits of a number (base 10)
    if(val == 0)
        return 0;
        
    return (1 + countdigit(val / 10)); //recursive call with division by 10
}

list_t *listdup(list_t *list) { //duplicate a list building a new
    list_t *duplicate = NULL;

    while(list) { //while current list node is valid
        if(!listadd(&duplicate, list->data)) { //build new list
            fprintf(stderr, "%s: memory allocation error\n", __func__);
            
            return NULL;
        }
        list = list->next; //step to next node
    }

    return (list_t *) duplicate; //return the pointer to new list
}


list_t *prevnode(list_t *list, list_t *node) {
    for(list_t *ptr = list; ptr && ptr->next; ptr = ptr->next) {
        if(node == ptr->next) {
            return (list_t *) ptr;
        }
    }

    return (list_t *) node;
}

list_t *swapnodes(list_t *list, list_t *node1, list_t *node2) {
    list_t *node1prev, *node2prev, *tmp;

    node1prev = prevnode(list, node1);
    node2prev = prevnode(list, node2);
    
    tmp = node2->next;
   

    if(node1 != list) {
        node1prev->next = node2;
    } else {
        list = node2;
    }
    
    if(node1->next == node2) {
        node2->next = node1;
        node1->next = tmp;
    } else {
        node2->next = node1->next;
        node1->next = tmp;
        node2prev->next = node1;
    }
    
    return (list_t *) list;
}
char *liststr(list_t *list) { //build the string rappresentation of the list
    list_t *ptr = list;
    unsigned int count = 6;
    char *string;

    string = (char *) malloc(count); //reserve memory for new string
    strcpy(string, "*"); //the head of list rappresentation
    while(list) { //walk thru the list
        int mem = countdigit(list->data) +3;
        char tmp_str[mem];
        
        sprintf(tmp_str, "%d->", list->data); //convert a integer to string (instead of itoa())
        count += mem;
        string = realloc(string, count);
        strcat(string, tmp_str);
        list = list->next; //step to next node
    }
    strcat(string, "NULL"); //the end of the list
    
    return string; //return the pointer of the built list
}

void listprint(list_t *list) {
    list_t *ptr = list;
    
    printf("*");
    while(ptr) {
        printf("%02d->", ptr->data);
        ptr = ptr->next;
    }
    printf("NULL\n");
    
    return;
}
