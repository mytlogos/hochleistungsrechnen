/* 
** simple error demonstration to demonstrate power of valgrind
** Julian M. Kunkel - 17.04.2008
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int *
mistake1 ()
{
  int *buf = malloc (sizeof (int) * 6);
  int buf2[] = { 1, 1, 2, 3, 4, 5 };
  // Geht nicht:
  //buf = buf2;
  memcpy(buf, buf2, 6 * sizeof(int));
  return buf;
}

int *
mistake2 ()
{
  int *buf = malloc (sizeof (int) * 2);
  buf[1] = 2;
  return buf;
}

int *
mistake3 ()
{
  /* In dieser Funktion darf kein Speicher direkt allokiert werden. */
  int *buf = &mistake1()[3];
  return buf;
}

int *
mistake4 ()
{
  return &mistake1()[4];
}

int
main (void)
{
  /* Modifizieren Sie die folgende Zeile nicht */
  int *p[4] = { &mistake1 ()[1], &mistake2 ()[1], mistake3 (), mistake4 () };

  printf ("1 %d\n", *p[0]);
  printf ("2 %d\n", *p[1]);
  printf ("3 %d\n", *p[2]);
  printf ("4 %d\n", *p[3]);

  // TODO FREE?
  //free (p);			
  //free (p[1]);			
  //free (p[1]);			
  //free (p[1]);			

  return 0;
}
