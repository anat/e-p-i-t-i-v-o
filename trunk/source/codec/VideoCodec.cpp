#include "VideoCodec.hpp"
#include <iostream>

const uint32_t ImgCodec::quantization_matrix[8][8] =
  {
    {3,  6,  9,  12, 15,  18,  21,  24},
    {6,  12, 18, 24, 30,  36,  42,  48},
    {9,  18, 27, 36, 45,  54,  63,  72},
    {12, 24, 36, 48, 60,  72,  84,  96},
    {15, 30, 45, 60, 75,  90,  105, 120},
    {18, 36, 54, 72, 90,  108, 126, 144},
    {21, 42, 63, 84, 105, 126, 147, 168},
    {24, 48, 72, 96, 120, 144, 168, 192}
  };


ImgCodec::ImgCodec(int width, int heigth, enum colorType color)
{
  if (width % 8 || heigth % 8)
    throw "This is not going to work!";
  _width  = width;
  _heigth = heigth;
  _type   = color;
  _result = new uint8_t[width * heigth * 3 * 2]; // VIRER LE * 2 QUAND RLE + HUFFMAN
  _numb   = 0;
}

ImgCodec::~ImgCodec()
{
  if (_result)
    delete _result;
}

uint8_t *ImgCodec::getProcessedImg() const
{
  return _result;
}

void ImgCodec::decode(uint8_t *img)
{
  (void) img;
}

uint32_t ImgCodec::encode(uint8_t *img)
{
  uint32_t x, y;
  uint32_t luma[8][8], chromaU[8][8], chromaV[8][8];

  _buffsize = 0;
  if (1)//!(_numb % KEY_FREQ)) /* Make a keyframe */
    {
      for (y = 0; y < _heigth; y += 8)
	for (x = 0; x < _width; x += 8)
	  {
	    rgb_to_yuv(img, x, y, luma, chromaU, chromaV);
	    downsampling420(chromaU, chromaV);
	    dct(luma, chromaU, chromaV);
	    quantization(luma, chromaU, chromaV);
	    rle(luma, chromaU, chromaV);
	  }
    }
  else /* Make a frame diff */
    {
    }
  
  std::cout << "Buffer size (RLE) : " << _buffsize << std::endl;
  // huffman(_result, _buffsize);
  // std::cout << "Buffer size (Huff): " << _buffsize << std::endl;
  std::cout << "Ratio : " << ((float)_buffsize) / 921600.0 << std::endl;
  return _buffsize;
}

void ImgCodec::rgb_to_yuv(uint8_t *img, uint32_t x, uint32_t y,
			  uint32_t luma[8][8], uint32_t chromaU[8][8], uint32_t chromaV[8][8])
{
  int i, j;
  
  y *= _width * 3;
  x *= 3;
  for (i = 0; i < 8; i++)
    {
      for (j = 0; j < 8; j++)
	{
	  luma[i][j]    = 0.299f * img[y+x+2] + 0.587f * img[y+x+1] + 0.114 * img[y+x];
	  chromaU[i][j] = 0.492f * (img[y+x]   - luma[j][i]);
	  chromaV[i][j] = 0.877f * (img[y+x+2] - luma[j][i]);
	  x += 3;
	}
      x -= 24;
      y += _width * 3;
    }
}

void ImgCodec::downsampling420(uint32_t chromaU[8][8], uint32_t chromaV[8][8])
{
  int i, j;

  for (i = 0; i < 8; i += 2)
    {
      for (j = 0; j < 8; j += 2)
	{
	  chromaU[i][j] += chromaU[i][j+1] + chromaU[i+1][j] + chromaU[i+1][j+1];
	  chromaU[i][j] /= 4;
	  chromaV[i][j] += chromaV[i][j+1] + chromaV[i+1][j] + chromaV[i+1][j+1];
	  chromaV[i][j] /= 4;
	}
    }
}

void ImgCodec::dct(uint32_t luma[8][8], uint32_t chromaU[8][8], uint32_t chromaV[8][8])
{
  int i, j;
  uint32_t freq_matrix[8][8];

  /* DCT on luminance channel */
  for (i = 0; i < 8; i++)
    for (j = 0; j < 8; j++)
      freq_matrix[i][j] = dct(luma, j, i);
  for (i = 0; i < 8; i++)
    for (j = 0; j < 8; j++)
      luma[i][j] = freq_matrix[i][j];
  /* DCT on chrominance channel U */
  for (i = 0; i < 8; i++)
    for (j = 0; j < 8; j++)
      freq_matrix[i][j] = dct(chromaU, j, i);
  for (i = 0; i < 8; i++)
    for (j = 0; j < 8; j++)
      chromaU[i][j] = freq_matrix[i][j];
  /* DCT on chrominance channel V */
  for (i = 0; i < 8; i++)
    for (j = 0; j < 8; j++)
      freq_matrix[i][j] = dct(chromaV, j, i);
  for (i = 0; i < 8; i++)
    for (j = 0; j < 8; j++)
      chromaV[i][j] = freq_matrix[i][j];
}

void ImgCodec::idct(uint32_t luma[8][8], uint32_t chromaU[8][8], uint32_t chromaV[8][8])
{
  int i, j;
  uint32_t pixel_matrix[8][8];

  /* IDCT on luminance channel */
  for (i = 0; i < 8; i++)
    for (j = 0; j < 8; j++)
      pixel_matrix[i][j] = idct(luma, j, i);
  for (i = 0; i < 8; i++)
    for (j = 0; j < 8; j++)
      luma[i][j] = pixel_matrix[i][j];
  /* IDCT on chrominance channel U */
  for (i = 0; i < 8; i++)
    for (j = 0; j < 8; j++)
      pixel_matrix[i][j] = idct(chromaU, j, i);
  for (i = 0; i < 8; i++)
    for (j = 0; j < 8; j++)
      chromaU[i][j] = pixel_matrix[i][j];
  /* IDCT on chrominance channel V */
  for (i = 0; i < 8; i++)
    for (j = 0; j < 8; j++)
      pixel_matrix[i][j] = idct(chromaV, j, i);
  for (i = 0; i < 8; i++)
    for (j = 0; j < 8; j++)
      chromaV[i][j] = pixel_matrix[i][j];
}

void ImgCodec::quantization(uint32_t luma[8][8], uint32_t chromaU[8][8], uint32_t chromaV[8][8])
{
  int i, j;

  for (i = 0; i < 8; i++)
    for (j = 0; j < 8; j++)
      luma[i][j] /= quantization_matrix[i][j]; 
  for (i = 0; i < 8; i++)
    for (j = 0; j < 8; j++)
      chromaU[i][j] /= quantization_matrix[i][j]; 
  for (i = 0; i < 8; i++)
    for (j = 0; j < 8; j++)
      chromaV[i][j] /= quantization_matrix[i][j]; 
}

void ImgCodec::iquantization(uint32_t luma[8][8], uint32_t chromaU[8][8], uint32_t chromaV[8][8])
{
  int i, j;

  for (i = 0; i < 8; i++)
    for (j = 0; j < 8; j++)
      luma[i][j] *= quantization_matrix[i][j]; 
  for (i = 0; i < 8; i++)
    for (j = 0; j < 8; j++)
      chromaU[i][j] *= quantization_matrix[i][j]; 
  for (i = 0; i < 8; i++)
    for (j = 0; j < 8; j++)
      chromaV[i][j] *= quantization_matrix[i][j]; 
}

int ImgCodec::dct(uint32_t m[8][8], uint8_t i, uint8_t j)
{
  double sum = 0.;

  for (uint8_t y = 0; y < 8; y++)
    for (uint8_t x = 0; x < 8; x++)
      sum += m[y][x] * COS1 * COS2;
  return (int) (0.25 * C(i) * C(j) * sum);
}

int ImgCodec::idct(uint32_t m[8][8], uint8_t x, uint8_t y)
{
  double sum = 0.;

  for (uint8_t j = 0; j < 8; j++)
    for (uint8_t i = 0; i < 8; i++)
      sum += C(i) * C(j) * m[j][i] * COS1 * COS2;
  return (int) (0.25 * sum);
}

/*********************
 Run Length Encoding
**********************/

void ImgCodec::rle(uint32_t luma[8][8], uint32_t chromaU[8][8], uint32_t chromaV[8][8])
{
  uint32_t tmp[64];

  zigzag(luma, tmp);
  _buffsize += compressRle(tmp, _result + _buffsize);
  zigzag(chromaU, tmp);
  _buffsize += compressRle(tmp, _result + _buffsize);
  zigzag(chromaV, tmp);
  _buffsize += compressRle(tmp, _result + _buffsize);
}

int			ImgCodec::compressRle(uint32_t tab[64], uint8_t *comp)
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

void			ImgCodec::decompressRle(int comp[128], int dec[64], int size)
{
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

void		ImgCodec::goRight(uint32_t *cha, uint32_t *x, uint32_t *i, uint32_t c)
{
  *cha = c;
  *x = *x + 1;
  *i = *i + 1;
}

void		ImgCodec::goDown(uint32_t *cha, uint32_t *y, uint32_t *i, uint32_t c)
{
  *cha = c;
  *y = *y + 1;
  *i = *i + 1;
}

void		ImgCodec::goDownLeft(uint32_t *cha, uint32_t tab[8][8], uint32_t *i, uint32_t *x, uint32_t *y)
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

void		ImgCodec::goUpRight(uint32_t *cha, uint32_t tab[8][8], uint32_t *i, uint32_t *x, uint32_t *y)
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

void		ImgCodec::zigzag(uint32_t tab[8][8], uint32_t cha[64])
{
  uint32_t     	x = 0;
  uint32_t     	y = 0;

  for (uint32_t i = 0; i < 64;)
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
