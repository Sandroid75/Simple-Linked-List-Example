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

#include "linkedlist.h"
#include <stdlib.h>
#include <time.h>

#define ENABLE_ZENTIMER
#include "zentimer.h"

int main() {
    list_t *mainList, *firstList, *secondList, *ptr, *node, *bubble, *insert, *quick;
    int i, val, num_of_nodes, how_many;
    char *list_string;
    ztimer_t timer[7];
    
    mainList = firstList = secondList = NULL; //initializing the lists

    printf("Enter the total numbers of node to create: ");
    scanf("%d", &num_of_nodes);
    
    srand(time(NULL));
    ZenTimerStart(&timer[0]);
    for(i = 0; i < num_of_nodes; i++) { //build a list with something
        val = rand() % 100;
        listpush(&mainList, val);
    }
    ZenTimerStop(&timer[0]);
 
    list_string = liststr(mainList); //convert the list in a string
    printf("This is the main linked list:\n%s\n\n", list_string);
    free(list_string); //frees the memory of the string

    printf("Enter how many nodes to keep in first splitted list: ");
    scanf("%d", &how_many);
    if(how_many > num_of_nodes) {
        printf("\nERROR: the number of nodes to keep is more of the total numbers of nodes!\n\n");
        
        return 1;
    }
    
    ZenTimerStart(&timer[1]);
    i = listsplit(mainList, how_many, &firstList, &secondList); //split the list in two and get the number of second list
    ZenTimerStop(&timer[1]);
    
    list_string = liststr(firstList); //retrieve the representation of the list as a string
    printf("Nodes of first list:\n%s\n\n", list_string);
    free(list_string);  //frees the memory of the string

    list_string = liststr(secondList); //retrieve the representation of the list as a string
    printf("N. of nodes remain in the second list %d\n", i);
    printf("Nodes of second list:\n%s\n\n", list_string);
    free(list_string);  //frees the memory of the string

    ZenTimerStart(&timer[2]);
    listcat(&secondList, firstList); //concatene the second list with the first
    ZenTimerStop(&timer[2]);

    list_string = liststr(secondList); //retrieve the representation of the list as a string
    printf("After concatenation of second list with the first:\n%s\n\n", list_string);
    free(list_string);  //frees the memory of the string
    
    //listfree(&firstList); //NOT necessary because of secondList contain firstList
    listfree(&secondList); //frees the memory of the list
    
    bubble = listdup(mainList);
    insert = listdup(mainList);
    quick  = listdup(mainList);

    ZenTimerStart(&timer[3]);
    bubble = listbubble(bubble, downward);
    ZenTimerStop(&timer[3]);

    list_string = liststr(bubble); //retrieve the representation of the list as a string
    printf("Nodes Bubble Sorting of main list:\n%s\n\n", list_string);
    free(list_string);  //frees the memory of the string

    ZenTimerStart(&timer[4]);
    listinsert(&insert);
    ZenTimerStop(&timer[4]);

    list_string = liststr(insert); //retrieve the representation of the list as a string
    printf("Nodes insert Sorting of main list:\n%s\n\n", list_string);
    free(list_string);  //frees the memory of the string

    ZenTimerStart(&timer[5]);
    quick = listqsort(quick, listlast(quick), upward);
    ZenTimerStop(&timer[5]);
    
    ZenTimerStart(&timer[6]);
    list_string = liststr(quick); //retrieve the representation of the list as a string
    ZenTimerStop(&timer[6]);
    printf("Nodes Quick Sorting of main list:\n%s\n\n", list_string);
    free(list_string);  //frees the memory of the string

    // listprint(mainList);
    // listprint(bubble);
    // listprint(insert);
    // listprint(quick);

    listfree(&bubble); //frees the memory of the list
    listfree(&insert); //frees the memory of the list
    listfree(&quick); //frees the memory of the list
    listfree(&mainList); //frees the memory of the list
    
    printf("Total numbers of nodes: %d\nTotal number of nodes splitted in the first list: %d\n\n", num_of_nodes, how_many);
    
    ZenTimerReport(&timer[0], "List Building........");
	ZenTimerReport(&timer[1], "List Splitting.......");
	ZenTimerReport(&timer[2], "List Concatenation...");
	ZenTimerReport(&timer[3], "List Bubble Sorting..");
	ZenTimerReport(&timer[4], "List Insert Sorting..");
	ZenTimerReport(&timer[5], "List Quick Sorting...");
	ZenTimerReport(&timer[6], "List String..........");
   
    return 0;
}
