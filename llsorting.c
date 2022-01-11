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
#include <stdbool.h>
#include "linkedlist.h"

/*
#define die(F, arg...) ({ fprintf(stderr, "die: " F "\n", ##arg); exit(1); 1})
#define NEW(T) (T*) ( {malloc(sizeof(T)) || die("malloc %s", strerror(errno)); })

#define die(F, arg...) do { fprintf(stderr, "die: " F "\n", ##arg); exit(1); } while(0)
#define NEW(T) (T*) ( {T* r=malloc(sizeof(T)); if (!r) die("malloc %s",strerror(errno)); r;})
*/

_Bool upward(const int first, const int second) { //comparation func ascending
    return first < second ? true : false;
}

_Bool downward(const int first, const int second) { //comparation func descending
    return first > second ? true : false;
}

list_t *listpart(list_t *head, list_t *end, list_t **newHead, list_t **newEnd, _Bool compare(const int first, const int second)) {
    list_t *pivot, *prev, *cur, *tail;
 
    tail = pivot = end;
    prev = NULL;
    cur = head;
    
    // During partition, both the head and end of the list
    // might change which is updated in the newHead and
    // newEnd variables
    while(cur != pivot) {
        if(compare(cur->data, pivot->data)) { //if first compared with pivot is true
            if(!(*newHead)) {
                (*newHead) = cur;
            }
            prev = cur;  //than becomes the new head
            cur = cur->next;
        } else { //otherwise if compared is false
            if(prev) {
                prev->next = cur->next;
            }
            list_t *ptr = cur->next; //move cur node to tail
            cur->next = NULL;
            tail->next = cur;
            tail = cur;
            cur = ptr; //change the tail
        }
    }
 
    if(!(*newHead)) { 
        (*newHead) = pivot;
    }
 
    (*newEnd) = tail;
 
    return pivot;
}

list_t *listqsort(list_t *head, list_t *end, _Bool compare(const int first, const int second)) {
    if(!head || head == end)
        return head;
 
    list_t *newHead, *newEnd, *pivot;

    newHead = newEnd = NULL;
    pivot = listpart(head, end, &newHead, &newEnd, compare);
 
    if(newHead != pivot) {
        list_t *ptr = newHead;
        while(ptr->next != pivot) {
            ptr = ptr->next;
        }
        ptr->next = NULL;
        newHead = listqsort(newHead, ptr, compare);
        ptr = listlast(newHead);
        ptr->next = pivot;
    }
    pivot->next = listqsort(pivot->next, newEnd, compare);
 
    return (list_t *) newHead;
}

/*
list_t *listpivot(list_t *list, list_t *node) {
    list_t *ptr, *prev;
    int i;;
    
    for(i = 1, ptr = list; ptr && ptr != node; i++, ptr = ptr->next);
    
    i = (int) ((float) i /2+0.5);
    
    for(ptr = list; ptr && i; i--) {
        ptr = ptr->next;
    }
    prev = prevnode(list, node);
    if(ptr != prev) {
        list = swapnodes(list, ptr, prev->next);
        
        return (list_t *) ptr;
    }
    
    return (list_t *) ptr->next;
}

list_t *listqsort(list_t *list, _Bool compare(const int first, const int second), int flag) {
    list_t *pivot, *left, *right, *ptr, *lesslast, *lessfirst;
    int start, end;
    _Bool quit = false;
    
    if(list && flag == -1) {
        ptr = prevnode(list, listlast(list));
    } else if(list && flag == 1) {
        ptr = list->next;
    }
    
    
    left = list;
    pivot = listpivot(list);
    right = prevnode(left, pivot);
    start = 1;
    end = listcount(list);
    
    
    while(!quit) {
        while(compare(left->data, pivot->data)) {
            start++;
            left = left->next;
        }
        
        while(!compare(left->data, pivot->data)) {
            end--;
            right = prevnode(list, right);
        }
        
        
        if(start < end) {
            list = swapnodes(list, left, right);
            ptr = left;
            left = right;
            right = ptr;
        } else {
            quit = true;
        }
    }
    
    list = swapnodes(list, left, pivot);
    list = listqsort(list, compare, -1);
    list = listqsort(list, compare, 1);
    
    return (list_t *) list;
}

void listbubble(list_t **list, _Bool compare(const int first, const int second)) {  
    list_t *current = *list, *index = NULL;
      
    if(!current) {  
        return; //void  
    }
    
    while(current) {  
        index = current->next;  
          
        while(index) {  
            if(compare(current->data, index->data)) {
                (index) = swapnodes((index), current, index);
            }  
            index = index->next;  
        }  
        current = current->next;  
    }      

}  

list_t *listbubble(list_t **list, _Bool compare(const int first, const int second)) {
    int swapped, i; 
    list_t *start, *ptr1, *lptr = NULL; 
    
    start = (*list);
  
    if (start == NULL) 
        return (list_t *) start; 
  
    do { 
        swapped = 0; 
        ptr1 = start; 
  
        while (ptr1->next && ptr1->next != lptr) { 
            if (compare(ptr1->data, ptr1->next->data)) {  
                start = swapnodes(start, ptr1, ptr1->next); 
                swapped = 1; 
            } 
            ptr1 = ptr1->next; 
        } 
        lptr = ptr1; 
    } while (swapped); 
    
    return (list_t *) start;
} 
*/

list_t *listbubble(list_t *list, _Bool compare(const int first, const int second)) {
    list_t *ptr;
    _Bool swapped;

    if(!list) {
        return (list_t *) list;
    }
    
    do {
        swapped = false;
        for(ptr = list; ptr && ptr->next; ptr = ptr->next) {
            if(compare(ptr->data, ptr->next->data)) {
                list = swapnodes(list, ptr, ptr->next);
                swapped = true;
            }
        }
    } while(swapped);
    
    return (list_t *) list;
}

void insertsort(list_t **head, list_t *newNode) {
    list_t dummy;
    list_t *current = &dummy;
    
    dummy.next = (*head);
 
    while (current->next && current->next->data < newNode->data) {
        current = current->next;
    }
 
    newNode->next = current->next;
    current->next = newNode;
    (*head) = dummy.next;
}
 
// Given a list, change it to be in sorted order (using `sortedInsert()`).
void listinsert(list_t **head) {
    list_t *result = NULL;     // build the answer here
    list_t *current = *head;   // iterate over the original list
    list_t *next;
 
    while (current != NULL) {
        // tricky: note the next pointer before we change it
        next = current->next;
 
        insertsort(&result, current);
        current = next;
    }
 
    *head = result;
}
