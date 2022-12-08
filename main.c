/*

  Word Count using dedicated lists,
  modified for Kinneret College on the Sea of Galile

*/

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

*/

#include <assert.h>
#include <getopt.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>

#include "word_count.h"

/* Global data structure tracking the words encountered */
WordCount *word_counts = NULL;

/* The maximum length of each word in a file */
#define MAX_WORD_LEN 64

/*
 * Total Word Count
 *
 * Returns the total amount of words found in infile.
 * Useful functions: fgetc(), isalpha().
 */
int num_words(FILE* infile) {

  
 char ch;
	int num_words = 0;                  // counter for the words
	int other_space = 0;             // variable to check one more space
    int ascii;

	
	if(infile == NULL)
	{
	  printf("no file like this\n");
	  return -1;
	}
	while(1)
	{
       if(feof(infile)){break;}
      ch=fgetc(infile);
      ascii=ch;
	   if(isalpha(ch)!=0||(ascii<=57&&ascii>=48)||(ispunct(ch)!=0))//if the ch is alphabet or nummbers by 0->9
	   {
	      other_space = 0;
	   }
	   else 
	   {
          if(!other_space)
	      {
		 other_space = 1;
		 num_words++;
	      }
	     
	   }
	}
    
	

  return num_words;
}

/*
 * Word Frequency Count
 *
 * Given infile, extracts and adds each word in the FILE to `wclist`.
 * Useful functions: fgetc(), isalpha(), tolower(), add_word().
 */
void count_words(WordCount **wclist, FILE *infile) {

     int other_space = 0;
     char ch;
     int ascii;
     char wordt[MAX_WORD_LEN]="";
     int i = 0; 
   
    if(infile == NULL)
    {
       printf("file not exists\n");
       
    }
    while(1)
    {
        if(feof(infile))
        {
           break;
        }
        ch = tolower(fgetc(infile));//c get a small character 
        ascii = ch;
        if((isalpha(ch) != 0) ||(ascii<=57&&ascii>=48))//if the c have a->z or numbers by 0->9
        {
          wordt[i] = ch;
          i++;
          other_space = 1; 
         
        }
        else
        {
           if(other_space == 1)
           {
              add_word(&word_counts,wordt);
              other_space = 0;
              i = 0;
           }
        }
        wordt[i] = '\0';
    }


}

/*
 * Comparator to sort list by frequency.
 * Useful function: strcmp().
 */
static bool wordcount_less(const WordCount *wc1, const WordCount *wc2) {
  if(wc1->count > wc2->count) return 0 ;
  else if(wc1->count < wc2->count) return 1;
  else
  {
    if(strcmp(wc1->word,wc2->word)>0)
    {
     return 0;
    }
    else return 1;
  }
}

/*
 * Comparator to reverse sort list by frequency.
 * Useful function: strcmp().
 */
static bool wordcount_more(const WordCount *wc1, const WordCount *wc2) {
  if(wc1->count > wc2->count) return 1;
  else if(wc1->count < wc2->count) return 0;
  else
  {
    if(strcmp(wc1->word,wc2->word)>0)
    {
     return 1;
    }
    else return 0;
  }
  
}


// In trying times, displays a helpful message.
static int display_help(void) {
	printf("Flags:\n"
	    "-c: Count the total amount of words in the file, or STDIN if a file is not specified.\n"
	    "-f: Count the frequency of each word in the file, or STDIN if a file is not specified.  Display words sorted by count (ascending), then alphabetically (A->Z)\n"
		"-r: Count the frequency of each word in the file, or STDIN if a file is not specified.  Display words sorted by count (descending), then reverse alphabetically (Z->A)\n"
	    "-h: Displays this help message.\n");
	return 0;
}

/*
 * Handle command line flags and arguments.
 */
int main (int argc, char *argv[]) {
 
  // Count Mode (default): outputs the total amount of words counted
  bool count_mode = true;
  int total_words = 0;

  // Freq Mode: outputs the frequency of each word
  bool freq_mode = false;
  bool reverse_mode = false;


  FILE *infile = NULL;

  // Variables for command line argument parsing
  int i;
  static struct option long_options[] =
  {
      {"count", no_argument, 0, 'c'},
      {"frequency", no_argument, 0, 'f'},
	  {"reverse", no_argument, 0, 'r'},
      {"help", no_argument, 0, 'h'},
      {0, 0, 0, 0}
  };

  // Sets flags
  while ((i = getopt_long(argc, argv, "cfrh", long_options, NULL)) != -1) {
      switch (i) {
          case 'c':
              count_mode = true;
              freq_mode = false;
     		  reverse_mode = false;
              break;
          case 'f':
              	count_mode = false;
              	freq_mode = true;
		reverse_mode = false;
              	break;
	  case 'r':
		count_mode = false;
		freq_mode = false;
		reverse_mode = true;
		break;
          case 'h':
              	return display_help();
		break;
      }
  }

  if (!count_mode && !freq_mode && !reverse_mode) {
    printf("Please specify a mode.\n");
    return display_help();
  }

  /* Create the empty data structure */
  init_words(&word_counts);

  if ((argc - optind) < 1) {
 
    
  
    if(count_mode==true)//if we write ./words -c  and any think
    {
    infile = stdin;
    total_words=num_words(infile);
    }
    else//if we write -f/-r and any think
    {
    infile=stdin; 
    count_words(&word_counts,infile);
    }
    
    
    
  } else {
  

    
    if(argv[optind]==argv[argc-1])// if we write -c/-f <filename.txt>
    {
    infile = fopen(argv[optind],"r");
    total_words = num_words(infile);
    fclose(infile);
    infile = fopen(argv[optind],"r");
    count_words(&word_counts,infile);
    fclose(infile);
    

    }
    else// if we write -c/-f <filename1.txt> <filename2.txt>
    {
    
    infile = fopen(argv[optind],"r");
    total_words = num_words(infile);
    fclose(infile);
    infile = fopen(argv[argc-1],"r");
    total_words += num_words(infile);
    fclose(infile);
    infile = fopen(argv[optind],"r");
    count_words(&word_counts,infile);
    fclose(infile);
    infile = fopen(argv[argc-1],"r");
    count_words(&word_counts,infile);
    fclose(infile);

    }
    
    
  }

  if (count_mode) {
    	printf("The total number of words is: %i\n", total_words);
  }  else if (freq_mode) {
    	wordcount_sort(&word_counts, wordcount_less);
    	printf("The frequencies of each word are: \n");
    	fprint_words(word_counts, stdout);
   } else if (reverse_mode) {
	 wordcount_sort(&word_counts, wordcount_more);
	 printf("The reverse frequencies of each word are: \n");
	 fprint_words(word_counts, stdout);
	}
  return 0;
}
