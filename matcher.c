/*
File name: matcher.c
An implementation of rgrep, aka restricted grep. rgrep reads lines from its standard input 
and puts them out on its standard output if and only if the pattern "matches" the line.  
*/  

#include "matcher.h"

/**
 * Returns true if partial_line matches pattern, starting from
 * the first char of partial_line.
 */  
int matches_leading(char *partial_line, char *pattern) 
{
  // checking if the partial_line and pattern matches each other or if the partial_line is the null terminator  
  if (*partial_line == '\0' || *partial_line == *pattern)
  {
    return 1;
  }
  return 0;
}

/* For commenting, the following variables will be called:
    *line - character
    *pattern - element
*/  
int rgrep_matches(char *line, char *pattern) 
{
  //returning true if it is the end of the pattern, gets here recursively!  
  if (*pattern == '\0')
  {
    return 1;
  }

  //did not reach the end :(  
  if (*line == 0)
  {
    return 0;
  }
  
  // \(backlash) operator: nullifies next element  
  else if (*pattern == '\\')
  {
    //if the character matches the next element  
    pattern += 1;
    if (matches_leading(line, pattern))
    {
      return rgrep_matches(line + 1, pattern + 1);
    }
    else
    {
      return 0;
    }
  }

  // + operator: character appears 1 or more times  
  else if (*pattern == '+')
  {
    // increment line until the character doesn't repeat anymore  
    while (*line == *(pattern - 1))
    {
      line += 1;
    }
    // 
    return rgrep_matches(line, pattern + 1);
  }

  // ? operator: character may appear between 0 and 1 times  
  else if (*(pattern + 1) == '?')
  {
    // if character and next next element match AND next character and next next element do not match
    if (matches_leading(line, pattern + 2) && !matches_leading(line + 1, pattern + 2))
    {
      return rgrep_matches(line, pattern + 2);
    }
    // if character and element match :)  
    else if (*line == *pattern)
    {
      return rgrep_matches(line + 1, pattern + 2);
    }
    // character and element don't match :(  
    else
    {
      // increment element to the next non-'?'  
      return rgrep_matches(line, pattern + 2);
    }
  }

  // . operator: matches any character  
  else if ((*line == *pattern) || (*pattern == '.' && *line != '\0'))
  {
    //carry on as usual since the '.' operator is any character  
    return rgrep_matches(line + 1, pattern + 1);
  }

  //line and pattern do not match!  
  else
  {
    return 0;
  }

  return 0;
}
