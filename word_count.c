/*

Copyright © 2019 University of California, Berkeley

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

word_count provides lists of words and associated count

Functional methods take the head of a list as first arg.
Mutators take a reference to a list as first arg.
*/

#include "word_count.h"


/* Basic utililties */

char *new_string(char *str) {
  return strcpy((char *)malloc(strlen(str)+1), str);
}

void init_words(WordCount **wclist) {
  /* Initialize word count.  */


*wclist=NULL;



  
}

size_t len_words(WordCount *wchead) {
    size_t len = 0;
    return len;
}

WordCount *find_word(WordCount *wchead, char *word) {
  /* Return count for word, if it exists */

    WordCount *wc = NULL;
    while(wchead!=NULL)
    {
    if(strcmp(wchead->word,word)==0)//if the word is exists in the list .
    {
    wc=wchead;
    ++wc->count;
    return wc;
    }
    wchead=wchead->next;
    }

  
  return wc;
}

void add_word(WordCount **wclist, char *word) {
  /* If word is present in word_counts list, increment the count, otw insert with count 1. */


WordCount *head=NULL;

if(*wclist==NULL)//if the list is empty
{

head=(WordCount*)malloc(sizeof(WordCount));//assigns denamic memory to the list
head->word=new_string(word);//assigns denamic memory to the string word
strcpy(head->word,word);//add a new word to the list 
head->count=1;// because this is the first struct it get count 1 
head->next=NULL;// the first is last 
*wclist=head;
}
else 
{

  head=*wclist;//head have the wclist list
  if(find_word(head,word)==NULL)// if the words is not exists in the list , make new struct and add it to the list 
 {
   while(head!=NULL)
  {
    if(head->next==NULL)
    {
    WordCount *last=NULL;
    last=(WordCount*)malloc(sizeof(WordCount));
    last->word=new_string(word);
    strcpy(last->word,word);
    last->count=1;
    last->next=NULL;
    head->next=last;
    return;
    }
  head=head->next;
  }
  

 }
 

  
}

}

void fprint_words(WordCount *wchead, FILE *ofile) {
  /* print word counts to a file */

  WordCount *wc;
  for (wc = wchead; wc; wc = wc->next) {
    fprintf(ofile, "%i\t%s\n", wc->count, wc->word);
  }
}
