/*
 */


#ifndef			__RLE_H__
#define			__RLE_H__

#include <iostream>
#include <string>
#include <fstream>

class			Rle
{
 private:

 public:
  int			compressRle(char *, int *);
  void			decompressRle(int *, int *, int s);
};


#endif
