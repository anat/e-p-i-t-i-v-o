/*

 */

#include "Rle.h"
#include <stdlib.h>

int			Rle::compressRle(char tab[64], int comp[128])
{
  int			j = 1;
  int			nb = 1;
  int			i = 0;

  while (j != 64)
    {
      if (tab[j] == tab[j - 1])
	nb++;
      else
	{
	  comp[i] = nb;
	  i++;
	  comp[i] = tab[j-1];
	  nb = 1;
	  i++;
	}
      j++;
    }
  comp[i] = nb;
  i++;
  comp[i] = tab[j-1];
  return i;
}

void			Rle::decompressRle(int comp[128], int dec[64], int size)
{
  int			b = 1;
  int			nb;
  int			j=0;

  for (int i = 0; i < 128 && i < size; i++)
    {
      nb = comp[i];
      i++;
      while (nb > 0)
	{
	  dec[j] = comp[i];
	  nb--;
	  j++;
	}
    }
}
