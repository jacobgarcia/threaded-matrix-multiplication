/*
 * Copyright (c) 2011-2014 Abelardo Lopez Lagunas
 *
 * File name: FileIO.c
 *
 * Author:  Abelardo Lopez Lagunas
 *
 * Purpose: Support routines that handle reading ASCII files
 *
 * References:
 *          Based on my own code, but won't be surprised if it is
 *          similar to other code out there
 *
 * Restrictions:
 *          All functions return (-1) in case something went wrong
 *
 * Revision history:
 *          Feb  4 15:15 2011 - File created
 *
 *          May 22 09:13 2012 - Added recognition of negative numbers.
 *
 *          Jan 30 15:44 2014 - Added recognition of strings. Note that
 *                              the Analyzer indicates potential memory
 *                              leaks in GetString because a malloc is done
 *                              inside the code and a pointer to it returned
 *
 *          Jan 31 17:02 2014 - Fixed potential memory leak by redefining
 *                              how GetString works.
 *
 * Error handling:
 *          None
 *
 * Notes:
 *          Support routine that reads an ASCII file and returns an
 *          integer value skiping over non-numeric data.
 *
 */


#include <stdlib.h>              /* Used for getc() and feof() functions */
#include <ctype.h>                    /* Used for the isdigit() function */
#include <stdio.h>                       /* Used to handle the FILE type */
#include <strings.h>                                /* Used for strdup() */
#include <assert.h>                       /* Used for the asser function */
#include "FileIO.h"                                   /* Function header */

/*
 *
 *  Function: GetInt
 *
 *  Purpose:  The function will read the input file and return an integer
 *            representing the ASCII characters that form a number. It
 *            skips over comments, which begin a line with a #, and other
 *            ASCII characters that do not represent numbers.
 *
 *  Parameters:
 *            input    Pointer to the text file to parse
 *
 *            output   Integer representing value. If the end of file is
 *                     reached a -1 is returned.
 *
 */
int GetInt (FILE *fp) {
    int	c,i;		  /* Character read and integer representation of it */
    int sign = 1;
    
    do {
        c = getc (fp); 	                           /* Get next character */
        if ( c == '#' )	                             /* Skip the comment */
            do {
                c = getc (fp);
            } while ( c != '\n');
        if ( c == '-')
            sign = -1;
    } while (!isdigit(c) && !feof(fp));
    
    if (feof(fp)){
        return (-1);
    } else {
        /* Found 1st digit, begin conversion until a non-digit is found */
        i = 0;
        while (isdigit (c) && !feof(fp)){
            i = (i*10) + (c - '0');
            c = getc (fp);
        }
        
        return (i*sign);
    }
}

/*
 *
 *  Function: GetString
 *
 *  Purpose:  The function will read the input file and return a string.
 *            It skips over comments, which begin a line with a #, and other
 *            ASCII characters that do not represent alphabetic characters.
 *            The maximum length of the string is 256 characters. Memory is
 *            allocated by this function and should be freed by the caller.
 *
 *  Parameters:
 *            input    Pointer to the text file to parse
 *
 *            output   String found in the file. If the end of file is
 *                     reached a NULL is returned.
 *
 */
char * GetString (FILE *fp){
    int	c,i;		   /* Character read and integer representation of it */
    char * buffer;                               /* String to be returned */
    
    buffer = (char *) malloc(sizeof(char)*256);              /* Ugly hack */
    assert (buffer != NULL);
    
    do {
        c = getc (fp); 	                           /* Get next character */
        if ( c == '#' )	                             /* Skip the comment */
            do {
                c = getc (fp);
            } while ( c != '\n');
    } while (!isalpha(c) && !feof(fp));
    
    if (feof(fp)){
        free(buffer);      /* End of file reached and no string was found */
        return (NULL);
    } else {
        /* Found 1st character, begin conversion until a digit is found */
        i = 0;
        while (isalpha (c) && !feof(fp) && (i < 255)){
            buffer[i] = c;
            i++;
            c = getc (fp);
        }
        buffer[i] = '\0';             /* Note how string may be truncated */
       
        return buffer;
    }
}
