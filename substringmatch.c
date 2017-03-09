#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 256
 
int getNextState(char *pattern, int p_length, int state, int x)
{
  // If the character c is same as next character in pattern,
  // then simply increment state
  if (state < p_length && x == pattern[state])
  return state+1;
 
  int next_state, i; // ns stores the result which is next state
 
  // ns finally contains the longest prefix which is also suffix
  // in "pat[0..state-1]c"
 
  // Start from the largest possible value and stop when you find
  // a prefix which is also suffix
  for (next_state = state; next_state > 0; next_state--)
  {
  if(pattern[next_state-1] == x)
  {
  for(i = 0; i < next_state-1; i++)
  {
  if (pattern[i] != pattern[state-next_state+1+i])
  break;
  }
  if (i == next_state-1)
  return next_state;
  }
  }
 
  return 0;
}
 
/* This function builds the TF table which represents Finite Automata for a
  given pattern */
void compute_TransitionTable(char *pattern, int p_length, int Transition_Table[][ALPHABET_SIZE])
{
  int state, x;
  for (state = 0; state <= p_length;state++)
  	{
  		for (x = 0; x < ALPHABET_SIZE; x++)
  		Transition_Table[state][x] = getNextState(pattern, p_length, state, x);
	}
}
 
/* Prints all occurrences of pat in txt */
void search(char *pattern, char *text)
{
  int p_length = strlen(pattern);
  int t_length = strlen(text);
 
  int Transition_Table[p_length+1][ALPHABET_SIZE];
  compute_TransitionTable(pattern,p_length,Transition_Table);

  // Process txt over FA.
  int i, current_state=0,flag=0;
  
  for (i = 0; i < t_length; i++)
  {
  	current_state = Transition_Table[current_state][text[i]];
  if (current_state == p_length)
  {
  	printf ("Pattern found at index %d\n", i-p_length+1);
  	flag=1;
  }

  }
  if(flag==0)
  	printf("Pattern not found in the given text\n");
}
 
int main()
{
  char pattern[20],text[100];
  printf("Enter pattern\n");
  fgets(pattern,20,stdin);
  pattern[strlen(pattern)-1]='\0';
  printf("Enter text\n");
  fgets(text,100,stdin);
  text[strlen(text)-1]='\0';
  search(pattern,text);
  return 0;
}