/*
 */

#include <iostream>

void		goRight(int *cha, int *x, int *i, int c)
{
  *cha = c;
  *x = *x + 1;
  *i = *i + 1;
}

void		goDown(int *cha, int *y, int *i, int c)
{
  *cha = c;
  *y = *y + 1;
  *i = *i + 1;
}

void		goDownLeft(int *cha, int tab[8][8], int *i, int *x, int *y)
{
  cha[*i] = tab[*y][*x];
  *i = *i + 1;
  while (*x > 0 && *y < 7)
    {
      *x = *x - 1;
      *y = *y + 1;
      if (*x > 0 && *y < 7)
	{
	  cha[*i] = tab[*y][*x];
	  *i = *i + 1;
	}
    }
}

void		goUpRight(int *cha, int tab[8][8], int *i, int *x, int *y)
{
  cha[*i] = tab[*y][*x];
  *i = *i + 1;
  while (*x < 7 && *y > 0)
    {
      *x = *x + 1;
      *y = *y - 1;
      if (*x < 7 && *y > 0)
	{
	  cha[*i] = tab[*y][*x];
	  *i = *i + 1;
	}
    }
}

void		algo(int tab[8][8], int cha[64])
{
  int		x = 0;
  int		y = 0;

  for (int i = 0; i < 64;)
    {
      if (x < 7)
	{
	  goRight(&cha[i], &x, &i, tab[y][x]);
	  goDownLeft(cha, tab, &i, &x, &y);
	}
      if (x == 7 && y != 0)
	{
	  goDown(&cha[i], &y, &i, tab[y][x]);
	  goDownLeft(cha, tab, &i, &x, &y);
	}
      if (y < 7)
	{
	  goDown(&cha[i], &y, &i, tab[y][x]);
	  goUpRight(cha, tab, &i, &x, &y);
	}
      if (y == 7)
	{
	  goRight(&cha[i], &x, &i, tab[y][x]);
	  goUpRight(cha, tab, &i, &x, &y);
	}
    }
}

int		main(int ac, char **av)
{
  int		tab[8][8] = {{286, 7, -2, 1, -4, 0, 2, 4},{-10, 4, -1, 0, 0, 0, 0, 0},{-3, 0,-2, 0, 0, 0, 0, 0},{-11,1,1,-1,0,0,0,0},{3,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0}};
  int		cha[64];

  algo(tab, cha);

  for (int j = 0; j < 64; j++)
    {
      std::cout << cha[j] << " ";
    }
  std::cout << std::endl;
}
