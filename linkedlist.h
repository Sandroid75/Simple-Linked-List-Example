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
#ifndef _linkedlist_h
#define _linkedlist_h

typedef struct list list_t; //this is the new type definition

struct list { //data structure of simple linked list
    int data; //data
    struct list *next; //pointer to the next node/node
};

list_t *newnode(const int data);
list_t *listlast(list_t *list); //walk thru the list up to last node
list_t *listadd(list_t **list, const int val); //add a new node with val at the end of the list, return the pointer to new node
list_t *listpush(list_t **list, const int val); //push a new node with val at begin of the list, return the pointer to new node
void listfree(list_t **list); //frees memory occupied by the list
int listcount(list_t *list); //return the numbers of valid node of a list
int listsplit(list_t *list, const int upto, list_t **head, list_t **tail); //split the list in two counting the elments
void listcat(list_t **head, list_t *tail); //concatene two lists, but don't forget that it's not necessary free the second after concatenation
int countdigit(const int val); //recursive version return the numbers of digits of a number (base 10)
list_t *listdup(list_t *list); //duplicate a list building a new
list_t *prevnode(list_t *list, list_t *node);
list_t *swapnodes(list_t *list, list_t *node1, list_t *node2);
char *liststr(list_t *list); //build the string rappresentation of the list
void listprint(list_t *list);
_Bool upward(const int first, const int second); //comparation func ascending
_Bool downward(const int first, const int second); //comparation func descending
list_t *listpart(list_t *head, list_t *end, list_t **newHead, list_t **newEnd, _Bool compare(const int first, const int second));
list_t *listqsort(list_t *head, list_t *end, _Bool compare(const int first, const int second));
list_t *listpivot(list_t *list, list_t *node);
list_t *listbubble(list_t *list, _Bool compare(const int first, const int second));
void insertsort(list_t **head, list_t *newNode);
void listinsert(list_t **head);

#endif
