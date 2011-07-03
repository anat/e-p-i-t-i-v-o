#include "VideoCodec.hpp"
#include <iostream>
#include <cstring>
#include <cstdlib>

const int32_t VideoCodec::quantization_matrix[8][8] =
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


VideoCodec::VideoCodec(int width, int heigth, enum colorType color)
{
  int i, j, x, y, z;

  if (width % 8 || heigth % 8)
    throw "This is not going to work!";
  _width  = width;
  _heigth = heigth;
  _type   = color;
  _result = new uint8_t[width * heigth * 3 * 4]; // VIRER LE * 2 QUAND RLE + HUFFMAN
  printf("_result is %p\n", _result);
  _resultDec = new uint8_t[width * heigth * 3 * 4]; // VIRER LE * 2 QUAND RLE + HUFFMAN
  _last   = new uint8_t[width * heigth * 3 * 4]; // VIRER LE * 2 QUAND RLE + HUFFMAN
  _last2  = new uint8_t[width * heigth * 3 * 4]; // VIRER LE * 2 QUAND RLE + HUFFMAN
  //_bdiff  = new uint8_t[width * heigth * 3 * 2]; // VIRER LE * 2 QUAND RLE + HUFFMAN
  _numb   = 0;
  _nextIsKeyframe = false;
  //_numb2   = 0;

  /*for (x = 0; x < 8; x++)
    for (i = 0; i < 8; i++)
    _pcos[x][i] = COS1;*/
  /*for (i = 0; i < 8; i++)
    for (j = 0; j < 8; j++)
      for (y= 0; y < 8; y++)
	for (x = 0; x < 8; x++)
	PPCOS = COS1 * COS2;*/

  for (z = 0; z < 255; z++)
    for (i = 0; i < 8; i++)
      for (j = 0; j < 8; j++)
	for (y= 0; y < 8; y++)
	  for (x = 0; x < 8; x++)
	    _pppcos[z][i][j][y][x] = z * COS1 * COS2;
}

VideoCodec::~VideoCodec()
{
  /*  if (_result)
    delete _result;
  if (_last)
    delete _last;
  if (_last2)
  delete _last2;*/
}

void VideoCodec::nextFrameIsKeyframe()
{
  _nextIsKeyframe = true;
}

uint8_t *VideoCodec::getProcessedImg() const
{
  return _result;
}

void VideoCodec::setResultBuff(uint8_t *res)
{
  _resultDec = res;
}

void VideoCodec::decode(uint8_t *img)
{
  uint32_t x, y;
  uint32_t luma[8][8], chromaU[8][8], chromaV[8][8];
  uint8_t *tmp;
  char c;
  unsigned int size;
  
    /*{
      std::cout << "decode(): error (Wrong magic number)." << std::endl;
      ::exit(1);
      }*/
  /*std::cout << std::endl;
  std::cout << "AVANT DECOMP[0]=" <<((unsigned int*)_resultDec)[0] << std::endl;
  std::cout << "AVANT DECOMP[1]=" <<((unsigned int*)_resultDec)[1] << std::endl;
  std::cout << "AVANT DECOMP[2]=" <<((unsigned int*)_resultDec)[2] << std::endl;
  std::cout << "AVANT DECOMP[3]=" <<((unsigned int*)_resultDec)[3] << std::endl;
  std::cout << std::endl;
  huffman.uncompress(_resultDec);
  size = huffman.getSize();
  std::cout << "UNCOMPRESS OK (datasize="<< size << ")"<< std::endl;
  tmp = huffman.getBuffer();
  std::cout << "APRES DECOMP [0]=" <<((unsigned int*)tmp)[0] << std::endl;
  std::cout << "APRES DECOMP [1]=" <<((unsigned int*)tmp)[1] << std::endl;
  std::cout << "APRES DECOMP [2]=" <<((unsigned int*)tmp)[2] << std::endl;
  std::cout << "APRES DECOMP [3]=" <<((unsigned int*)tmp)[3] << std::endl;
  ::memcpy(_resultDec, tmp, size);
  std::cout << "APRES DECOMP2 [0]=" <<((unsigned int*)_resultDec)[0] << std::endl;
  std::cout << "APRES DECOMP2 [1]=" <<((unsigned int*)_resultDec)[1] << std::endl;
  std::cout << "APRES DECOMP2 [2]=" <<((unsigned int*)_resultDec)[2] << std::endl;
  std::cout << "APRES DECOMP2 [3]=" <<((unsigned int*)_resultDec)[3] << std::endl;*/

  _buffsize = 4;
  if (*((unsigned int *)_resultDec) == 0x42424242)
  //if (!(_numb2++ % KEY_FREQ)) /* Extract a keyframe */
    {
      for (y = 0; y < _heigth; y += 8)
	{
	  for (x = 0; x < _width; x += 8)
	    {
	      irle(luma, chromaU, chromaV);
	      if (0)//!y && !x)
	      {
		std::cout << "==========YY BEFORE IQUANTI============" << std::endl;
		for (int i = 0; i < 8; i++)
		  {
		    for (int j = 0; j < 8; j++)
		      std::cout << "  " << (int)luma[i][j];
		    std::cout << std::endl;
		  }
	      }
	      iquantization((int32_t (*)[8])luma, chromaU, chromaV);
	      if (0)//!y && !x)
	      {
		std::cout << "==========Y============" << std::endl;
		for (int i = 0; i < 8; i++)
		  {
		    for (int j = 0; j < 8; j++)
		      std::cout << "  " << (int)luma[i][j];
		    std::cout << std::endl;
		  }
		std::cout << std::endl;		    std::cout << std::endl;
		std::cout << "==========U============" << std::endl;
		for (int i = 0; i < 8; i++)
		  {
		    for (int j = 0; j < 8; j++)
		      std::cout << "  " << (int)chromaU[i][j];
		    std::cout << std::endl;
		  }
		std::cout << std::endl;		    std::cout << std::endl;
		std::cout << "==========V============" << std::endl;
		for (int i = 0; i < 8; i++)
		  {
		    for (int j = 0; j < 8; j++)
		      std::cout << "  " << (int)chromaV[i][j];
		    std::cout << std::endl;
		  }
		std::cout << std::endl;		    std::cout << std::endl;
	      }
	      idct((int32_t (*)[8])luma, chromaU, chromaV);
	      yuv_to_rgb(img, x, y, (int32_t (*)[8])luma, (int32_t (*)[8])chromaU, (int32_t (*)[8])chromaV);

	      if (0)//!y && !x)
	      {
		std::cout << "===========R===========" << std::endl;
		for (int py = 0; py < 8; py++)
		  {
		    for (int px = 0; px < 8; px++)
		      std::cout << "  " << (int)img[py*640*3 + px*3+2];
		    std::cout << std::endl;
		  }
		std::cout << std::endl;		    std::cout << std::endl;
		std::cout << "===========V===========" << std::endl;
		for (int py = 0; py < 8; py++)
		  {
		    for (int px = 0; px < 8; px++)
		      std::cout << "  " << (int)img[py*640*3 + px*3+1];
		    std::cout << std::endl;
		  }
		std::cout << std::endl;		    std::cout << std::endl;
		std::cout << "===========B===========" << std::endl;
		for (int py = 0; py < 8; py++)
		  {
		    for (int px = 0; px < 8; px++)
		      std::cout << "  " << (int)img[py*640*3 + px*3+0];
		    std::cout << std::endl;
		  }
		std::cout << std::endl;		    std::cout << std::endl;
	      }
	      //std::cout << "DE Buffer size: " << _buffsize << std::endl;
	    }
	}
      //std::cout << "Decode keyframe" << std::endl;
    }
  else if (*((unsigned int *)_resultDec) == 0x43434343)
    {
      ::memcpy(img, _last2, _width*_heigth*3);

      int i = 0, nb = (((unsigned int *)_resultDec)[1] - 4) / 7;
      unsigned int pos;

      //std::cout << "Decode diff: " << nb << std::endl;
      _buffsize += 4;

      while (i++ < nb)
	{
	  pos = ((unsigned int *)(_resultDec + _buffsize))[0];
	  _buffsize += 4;
	  //std::cout << "undiff (" << pos+2 << ")" << std::endl;
	  img[pos+2] = *(_resultDec + _buffsize++);
	  img[pos+1] = *(_resultDec + _buffsize++);
	  img[pos+0] = *(_resultDec + _buffsize++);
	  //std::cout << "undiff ok" << std::endl;

	  //_buffsize += 3;
	  //img[pos+2] = 0;
	  //img[pos+1] = 0;
	  //img[pos]   = 0;
	}
    }
  else
    {
      std::cout << "decode(): error (Wrong magic number)." << std::endl;
      ::exit(1);
    }

  /*for (y = 0; y < _width*_heigth*3; y += 3)
    {
      c = img[y+2];
      img[y+2] = img[y];
      img[y] = c;
    }*/
  ::memcpy(_last2, img, _width*_heigth*3);
}

uint32_t VideoCodec::encode(uint8_t *img)
{
  uint32_t x, y, c;
  uint32_t luma[8][8], chromaU[8][8], chromaV[8][8];
  bool diffFlag = false;

  _buffsize = 4; /* MAGIC NUMBER */
  for (y = 0; y < _width*_heigth*3; y += 3)
    {
      c = img[y+2];
      img[y+2] = img[y];
      img[y] = c;
    }

  if ((_numb++ % KEY_FREQ) && _nextIsKeyframe == false) /* Make a frame diff */
    {
      *((unsigned int *)_result) = 0x43434343;
      if (diff(img) == 1)
	{
	  diffFlag = true;
	  //std::cout << std::endl;
	  //std::cout << "Buffer size (diff) : " << _buffsize << std::endl;
	}
    }
  if (diffFlag == false)//!(_numb++ % KEY_FREQ)) /* Make a keyframe */
    {
      _nextIsKeyframe = false;
      *((unsigned int *)_result) = 0x42424242;
      for (y = 0; y < _heigth; y += 8)
	{
	for (x = 0; x < _width; x += 8)
	  {
	    if (0)//!y && !x)
	      {
		std::cout << "===========R===========" << std::endl;
		for (int py = 0; py < 8; py++)
		  {
		    for (int px = 0; px < 8; px++)
		      std::cout << "  " << (int)img[py*640*3 + px*3+2];
		    std::cout << std::endl;
		  }
		std::cout << std::endl;		    std::cout << std::endl;
		std::cout << "===========V===========" << std::endl;
		for (int py = 0; py < 8; py++)
		  {
		    for (int px = 0; px < 8; px++)
		      std::cout << "  " << (int)img[py*640*3 + px*3+1];
		    std::cout << std::endl;
		  }
		std::cout << std::endl;		    std::cout << std::endl;
		std::cout << "===========B===========" << std::endl;
		for (int py = 0; py < 8; py++)
		  {
		    for (int px = 0; px < 8; px++)
		      std::cout << "  " << (int)img[py*640*3 + px*3+0];
		    std::cout << std::endl;
		  }
		std::cout << std::endl;		    std::cout << std::endl;
	      }
	    rgb_to_yuv(img, x, y, (int32_t (*)[8])luma, (int32_t (*)[8])chromaU, (int32_t (*)[8])chromaV);

	    downsampling420(chromaU, chromaV);
	    dct(luma, chromaU, chromaV);
	    if (0)//!y && !x)
	      {
		std::cout << "==========Y============" << std::endl;
		for (int i = 0; i < 8; i++)
		  {
		    for (int j = 0; j < 8; j++)
		      std::cout << "  " << (int)luma[i][j];
		    std::cout << std::endl;
		  }
		std::cout << std::endl;		    std::cout << std::endl;
		std::cout << "==========U============" << std::endl;
		for (int i = 0; i < 8; i++)
		  {
		    for (int j = 0; j < 8; j++)
		      std::cout << "  " << (int)chromaU[i][j];
		    std::cout << std::endl;
		  }
		std::cout << std::endl;		    std::cout << std::endl;
		std::cout << "==========V============" << std::endl;
		for (int i = 0; i < 8; i++)
		  {
		    for (int j = 0; j < 8; j++)
		      std::cout << "  " << (int)chromaV[i][j];
		    std::cout << std::endl;
		  }
		std::cout << std::endl;		    std::cout << std::endl;
	      }
	    quantization((int32_t (*)[8])luma, chromaU, chromaV);
	    rle(luma, chromaU, chromaV);
	    /*if (!y && !x)
	      {
		for (int i = 0; i < 8; i++)
		  {
		    for (int j = 0; j < 8; j++)
		      std::cout << "  " << (int)luma[i][j];
		    std::cout << std::endl;
		  }
		std::cout << "---------------------" << std::endl;    
		}*/
	    //std::cout << "EN Buffer size: " << _buffsize << std::endl;
	  }
	//std::cout << "y = " << y << std::endl;
	}
      //std::cout << std::endl;
      //std::cout << "Buffer size (RLE) : " << _buffsize << std::endl;
      //std::cout << "Ratio : " << ((float)_buffsize) / 921600.0 << std::endl;
    }

  ::memcpy(_last, img, _width*_heigth*3);

  /*std::cout << "==============================" << std::endl;
  std::cout << "AVANT COMP [0]=" <<((unsigned int*)_result)[0] << std::endl;
  std::cout << "AVANT COMP [1]=" <<((unsigned int*)_result)[1] << std::endl;
  std::cout << "AVANT COMP [2]=" <<((unsigned int*)_result)[2] << std::endl;
  std::cout << "AVANT COMP [3]=" <<((unsigned int*)_result)[3] << std::endl;
  std::cout << std::endl;
  huffman.compress(_result, _buffsize);
  ::memcpy(_result, huffman.getBuffer(), (_buffsize = huffman.getSize()));  

  std::cout << "APRES COMP [0]=" <<((unsigned int*)_result)[0] << std::endl;
  std::cout << "APRES COMP [1]=" <<((unsigned int*)_result)[1] << std::endl;
  std::cout << "APRES COMP [2]=" <<((unsigned int*)_result)[2] << std::endl;
  std::cout << "APRES COMP [3]=" <<((unsigned int*)_result)[3] << std::endl;
  std::cout << "Buffer size (Huff): " << _buffsize << std::endl;
  std::cout << std::endl;*/

  /*uint8_t *tmp;
  huffman.uncompress(_result);
  std::cout << "UNCOMPRESS OK (datasize="<< huffman.getSize() << ")"<< std::endl;
  tmp = huffman.getBuffer();
  std::cout << "APRES DECOMP [0]=" <<((unsigned int*)tmp)[0] << std::endl;
  std::cout << "APRES DECOMP [1]=" <<((unsigned int*)tmp)[1] << std::endl;
  std::cout << "APRES DECOMP [2]=" <<((unsigned int*)tmp)[2] << std::endl;
  std::cout << "APRES DECOMP [3]=" <<((unsigned int*)tmp)[3] << std::endl;
  ::memcpy(_result, tmp, (_buffsize = huffman.getSize()));*/

  //std::cout << "Ratio : " << ((float)_buffsize) / 921600.0 << std::endl;
  return _buffsize;
}

int VideoCodec::diff(uint8_t *img)
{
  unsigned int i;
  const int threshold = 5;
  bool tooMuch = false;
  uint32_t backBuffSize = _buffsize;
  
  //printf("1 = %d %d %d %d\n", _last[0], _last[1], _last[2], _last[3]);
  //printf("2 = %d %d %d %d\n", img[0], img[1], img[2], img[3]);

  _buffsize += 4;
  for (i = 0; i < _width*_heigth*3; i += 3)
    {
      if (_last[i]   > img[i]+threshold   || _last[i]   < img[i]-threshold   ||
          _last[i+1] > img[i+1]+threshold || _last[i+1] < img[i+1]-threshold ||
	  _last[i+2] > img[i+2]+threshold || _last[i+2] < img[i+2]-threshold)
	{
	  if (_buffsize > 900000)
	    {
	      tooMuch = true;
	      break;
	    }
	  ((unsigned int *)(_result + _buffsize))[0] = i;
	  _buffsize += 4;
	  *(_result + _buffsize++) = img[i+2];
	  *(_result + _buffsize++) = img[i+1];
	  *(_result + _buffsize++) = img[i];
	}
    }
  if (tooMuch)
    {
      _buffsize = backBuffSize;
      return (-1);
    }
  //_buffsize = (_buffsize - 4) / 7;
  ((unsigned int *)(_result))[1] = _buffsize;
  //std::cout << (_buffsize-4)/7 << " differents entries" << std::endl;
  return (1);
}


void VideoCodec::rgb_to_yuv(uint8_t *img, uint32_t x, uint32_t y,
			  int32_t luma[8][8], int32_t chromaU[8][8], int32_t chromaV[8][8])
{
  int i, j;
  
  y *= _width * 3;
  x *= 3;
  for (i = 0; i < 8; i++)
    {
      for (j = 0; j < 8; j++)
	{
	  luma[i][j]    = 0.299f * (float)img[y+x+2] + 0.587f *
	  (float)img[y+x+1] + 0.114 * (float)img[y+x];
	  chromaU[i][j] = 0.492f * (float)(img[y+x]   - luma[i][j]) + 128;
	  chromaV[i][j] = 0.877f * (float)(img[y+x+2] - luma[i][j]) + 128;
	  //luma[i][j]    = img[y+x+2];//0.299f * (float)img[y+x+2] + 0.587f *
	  //(float)img[y+x+1] + 0.114 * (float)img[y+x];
	  //chromaU[i][j] = img[y+x+1];//0.492f * (float)(img[y+x]   - luma[i][j]);
	  //chromaV[i][j] = img[y+x+0];//0.877f * (float)(img[y+x+2] - luma[i][j]);
	  x += 3;
	}
      x -= 24;
      y += _width * 3;
    }
}

void VideoCodec::yuv_to_rgb(uint8_t *img, uint32_t x, uint32_t y,
			    int32_t luma[8][8], int32_t chromaU[8][8], int32_t chromaV[8][8])
{
  int i, j, tmp;
  int truc = 0;
  y *= _width * 3;
  x *= 3;
  if (!x && !y) truc = 1;
  for (i = 0; i < 8; i++)
    {
      for (j = 0; j < 8; j++)
	{
	  if (0)//truc)
	    {
	      //std::cout << "("<<i<<","<<j<<") tmp = ";
	      //std::cout << luma[i][j] << " + ";
	      //std::cout << 1.13983f * (float)chromaV[i][j];
	      //std::cout << "    1.13983f * " << (float)chromaV[i][j] << std::endl;
	    }
	  tmp = (int) ((float)luma[i][j] + 1.13983f * (float)(chromaV[i][j]-128));
	  tmp = (tmp > 255) ? 255 : ((tmp < 0) ? 0 : tmp);
	  img[y+x+2] = tmp;
	  tmp = (int) ((float)luma[i][j] - 0.39465f * (float)(chromaU[i][j]-128)
	  	       - 0.58060f * (float)(chromaV[i][j]-128));
	  tmp = (tmp > 255) ? 255 : ((tmp < 0) ? 0 : tmp);
	  img[y+x+1] = tmp;
	  tmp = (int) ((float)luma[i][j] + 2.03211f * (float)(chromaU[i][j]-128));
	  tmp = (tmp > 255) ? 255 : ((tmp < 0) ? 0 : tmp);
	  img[y+x]   = tmp;

	  //img[y+x+2] = luma[i][j];//tmp;
	  //img[y+x+1] = chromaU[i][j];//tmp;
	  //img[y+x]   = chromaV[i][j];//tmp;
	  x += 3;
	}
      x -= 24;
      y += _width * 3;
    }
}

void VideoCodec::downsampling420(uint32_t chromaU[8][8], uint32_t chromaV[8][8])
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


void VideoCodec::dct(uint32_t luma[8][8], uint32_t chromaU[8][8], uint32_t chromaV[8][8])
{
  int i, j;
  uint32_t freq_matrix[8][8];
  static int test = 0;

  if (0)//test == 0)
    {
      std::cout << "==========AV DCT============" << std::endl;
      for (i = 0; i < 8; i++)
	{
	  for (j = 0; j < 8; j++)
	    std::cout << "  " << (int)luma[i][j];
	  std::cout << std::endl;
	}
      std::cout << std::endl;		    std::cout << std::endl;
    }
  /* DCT on luminance channel */
  for (i = 0; i < 8; i++)
    for (j = 0; j < 8; j++)
      freq_matrix[i][j] = dct(luma, j, i);
  for (i = 0; i < 8; i++)
    for (j = 0; j < 8; j++)
      luma[i][j] = freq_matrix[i][j];

  if (0)//test == 0)
    {
      std::cout << "==========AP DCT============" << std::endl;
      for (i = 0; i < 8; i++)
	{
	  for (j = 0; j < 8; j++)
	    std::cout << "  " << (int)luma[i][j];
	  std::cout << std::endl;
	}
      std::cout << std::endl;		    std::cout << std::endl;
      test++;
    }
  /* DCT on chrominance channel U *
  for (i = 0; i < 8; i++)
    for (j = 0; j < 8; j++)
      freq_matrix[i][j] = dct(chromaU, j, i);
  for (i = 0; i < 8; i++)
    for (j = 0; j < 8; j++)
      chromaU[i][j] = freq_matrix[i][j];
  /* DCT on chrominance channel V *
  for (i = 0; i < 8; i++)
    for (j = 0; j < 8; j++)
      freq_matrix[i][j] = dct(chromaV, j, i);
  for (i = 0; i < 8; i++)
    for (j = 0; j < 8; j++)
    chromaV[i][j] = freq_matrix[i][j];**/
}

void VideoCodec::idct(int32_t luma[8][8], uint32_t chromaU[8][8], uint32_t chromaV[8][8])
{
  int i, j;
  uint32_t pixel_matrix[8][8];
  static int test = 0;

  if (0)//test == 0)
    {
      std::cout << "==========AV IDCT============" << std::endl;
      for (i = 0; i < 8; i++)
	{
	  for (j = 0; j < 8; j++)
	    std::cout << "  " << (int)luma[i][j];
	  std::cout << std::endl;
	}
      std::cout << std::endl;		    std::cout << std::endl;
    }

  /* IDCT on luminance channel */
  for (i = 0; i < 8; i++)
    for (j = 0; j < 8; j++)
      pixel_matrix[i][j] = idct(luma, j, i);
  for (i = 0; i < 8; i++)
    for (j = 0; j < 8; j++)
      luma[i][j] = pixel_matrix[i][j];

  if (0)//test == 0)
    {
      std::cout << "==========AP IDCT============" << std::endl;
      for (i = 0; i < 8; i++)
	{
	  for (j = 0; j < 8; j++)
	    std::cout << "  " << (int)luma[i][j];
	  std::cout << std::endl;
	}
      std::cout << std::endl;		    std::cout << std::endl;
      test++;
    }

  /* IDCT on chrominance channel U *
  for (i = 0; i < 8; i++)
    for (j = 0; j < 8; j++)
      pixel_matrix[i][j] = idct(chromaU, j, i);
  for (i = 0; i < 8; i++)
    for (j = 0; j < 8; j++)
      chromaU[i][j] = pixel_matrix[i][j];
  /* IDCT on chrominance channel V *
  for (i = 0; i < 8; i++)
    for (j = 0; j < 8; j++)
      pixel_matrix[i][j] = idct(chromaV, j, i);
  for (i = 0; i < 8; i++)
    for (j = 0; j < 8; j++)
    chromaV[i][j] = pixel_matrix[i][j];*/
}

void VideoCodec::quantization(int32_t luma[8][8], uint32_t chromaU[8][8], uint32_t chromaV[8][8])
{
  int i, j;
  static int test = 0;
  for (i = 0; i < 8; i++)
    for (j = 0; j < 8; j++)
      {
	luma[i][j] /= quantization_matrix[i][j]; 
	if (0)//i==1 && j==0 || i==0&&j==1)
	  {
	    std::cout << "ij" << i << "  " << j << std::endl;
	    std::cout << "qt> " << quantization_matrix[i][j] << std::endl;
	    std::cout << "val> " << ((int)luma[i][j] / quantization_matrix[i][j]) << std::endl;
	    std::cout << "va2> " << (int)((int)luma[i][j] / quantization_matrix[i][j]) << std::endl;
	  }
	//luma[i][j] = (int)((int)luma[i][j] / quantization_matrix[i][j]); 
      }
  if (0)//test == 0)
    {
      std::cout << "==========AP QTZ============" << std::endl;
      for (i = 0; i < 8; i++)
	{
	  for (j = 0; j < 8; j++)
	    std::cout << "  " << (int)luma[i][j];
	  std::cout << std::endl;
	}
      std::cout << std::endl;		    std::cout << std::endl;
      test++;
    }
  /*for (i = 0; i < 8; i++)
    for (j = 0; j < 8; j++)
      chromaU[i][j] /= quantization_matrix[i][j]; 
  for (i = 0; i < 8; i++)
    for (j = 0; j < 8; j++)
    chromaV[i][j] /= quantization_matrix[i][j];*/
}

void VideoCodec::iquantization(int32_t luma[8][8], uint32_t chromaU[8][8], uint32_t chromaV[8][8])
{
  int i, j;
  static int test = 0;
  if (0)//test == 0)
    {
      std::cout << "==========AV DQTZ============" << std::endl;
      for (i = 0; i < 8; i++)
	{
	  for (j = 0; j < 8; j++)
	    {
	      std::cout << "  " << (int)luma[i][j];
	      if ((int)luma[i][j] > 128)
		{
		  std::cout << "|" << (int)(unsigned char)luma[i][j];
		  std::cout << "|" << (int)((signed char)((unsigned char)luma[i][j]));
		}
	    }
	  std::cout << std::endl;
	}
      std::cout << std::endl;		    std::cout << std::endl;
      test++;
    }
  for (i = 0; i < 8; i++)
    for (j = 0; j < 8; j++)
      {
	if (!i && !j)
	  {
	    luma[i][j] *= quantization_matrix[i][j]; 
	  }
	else
	  {
	    luma[i][j] = (int)((signed char)((unsigned char)luma[i][j]));
	    luma[i][j] *= quantization_matrix[i][j]; 
	  }
      }
  /*for (i = 0; i < 8; i++)
    for (j = 0; j < 8; j++)
      chromaU[i][j] *= quantization_matrix[i][j]; 
  for (i = 0; i < 8; i++)
    for (j = 0; j < 8; j++)
    chromaV[i][j] *= quantization_matrix[i][j]; */
}

inline int VideoCodec::dct(uint32_t m[8][8], uint8_t i, uint8_t j)
{
  double sum = 0.;

  for (uint8_t y = 0; y < 8; y++)
    for (uint8_t x = 0; x < 8; x++)
      sum += m[y][x] * COS1 * COS2;
      //sum += PPPCOS;// m[y][x] * PPCOS;//PCOS1 * PCOS2;

  /*  sum += m[0][0] * _pcos[0][i] * _pcos[0][j];
  sum += m[0][1] * _pcos[1][i] * _pcos[0][j];
  sum += m[0][2] * _pcos[2][i] * _pcos[0][j];
  sum += m[0][3] * _pcos[3][i] * _pcos[0][j];
  sum += m[0][4] * _pcos[4][i] * _pcos[0][j];
  sum += m[0][5] * _pcos[5][i] * _pcos[0][j];
  sum += m[0][6] * _pcos[6][i] * _pcos[0][j];
  sum += m[0][7] * _pcos[7][i] * _pcos[0][j];

  sum += m[1][0] * _pcos[0][i] * _pcos[1][j];
  sum += m[1][1] * _pcos[1][i] * _pcos[1][j];
  sum += m[1][2] * _pcos[2][i] * _pcos[1][j];
  sum += m[1][3] * _pcos[3][i] * _pcos[1][j];
  sum += m[1][4] * _pcos[4][i] * _pcos[1][j];
  sum += m[1][5] * _pcos[5][i] * _pcos[1][j];
  sum += m[1][6] * _pcos[6][i] * _pcos[1][j];
  sum += m[1][7] * _pcos[7][i] * _pcos[1][j];

  sum += m[2][0] * _pcos[0][i] * _pcos[2][j];
  sum += m[2][1] * _pcos[1][i] * _pcos[2][j];
  sum += m[2][2] * _pcos[2][i] * _pcos[2][j];
  sum += m[2][3] * _pcos[3][i] * _pcos[2][j];
  sum += m[2][4] * _pcos[4][i] * _pcos[2][j];
  sum += m[2][5] * _pcos[5][i] * _pcos[2][j];
  sum += m[2][6] * _pcos[6][i] * _pcos[2][j];
  sum += m[2][7] * _pcos[7][i] * _pcos[2][j];

  sum += m[3][0] * _pcos[0][i] * _pcos[3][j];
  sum += m[3][1] * _pcos[1][i] * _pcos[3][j];
  sum += m[3][2] * _pcos[2][i] * _pcos[3][j];
  sum += m[3][3] * _pcos[3][i] * _pcos[3][j];
  sum += m[3][4] * _pcos[4][i] * _pcos[3][j];
  sum += m[3][5] * _pcos[5][i] * _pcos[3][j];
  sum += m[3][6] * _pcos[6][i] * _pcos[3][j];
  sum += m[3][7] * _pcos[7][i] * _pcos[3][j];

  sum += m[4][0] * _pcos[0][i] * _pcos[4][j];
  sum += m[4][1] * _pcos[1][i] * _pcos[4][j];
  sum += m[4][2] * _pcos[2][i] * _pcos[4][j];
  sum += m[4][3] * _pcos[3][i] * _pcos[4][j];
  sum += m[4][4] * _pcos[4][i] * _pcos[4][j];
  sum += m[4][5] * _pcos[5][i] * _pcos[4][j];
  sum += m[4][6] * _pcos[6][i] * _pcos[4][j];
  sum += m[4][7] * _pcos[7][i] * _pcos[4][j];

  sum += m[5][0] * _pcos[0][i] * _pcos[5][j];
  sum += m[5][1] * _pcos[1][i] * _pcos[5][j];
  sum += m[5][2] * _pcos[2][i] * _pcos[5][j];
  sum += m[5][3] * _pcos[3][i] * _pcos[5][j];
  sum += m[5][4] * _pcos[4][i] * _pcos[5][j];
  sum += m[5][5] * _pcos[5][i] * _pcos[5][j];
  sum += m[5][6] * _pcos[6][i] * _pcos[5][j];
  sum += m[5][7] * _pcos[7][i] * _pcos[5][j];

  sum += m[6][0] * _pcos[0][i] * _pcos[6][j];
  sum += m[6][1] * _pcos[1][i] * _pcos[6][j];
  sum += m[6][2] * _pcos[2][i] * _pcos[6][j];
  sum += m[6][3] * _pcos[3][i] * _pcos[6][j];
  sum += m[6][4] * _pcos[4][i] * _pcos[6][j];
  sum += m[6][5] * _pcos[5][i] * _pcos[6][j];
  sum += m[6][6] * _pcos[6][i] * _pcos[6][j];
  sum += m[6][7] * _pcos[7][i] * _pcos[6][j];

  sum += m[7][0] * _pcos[0][i] * _pcos[7][j];
  sum += m[7][1] * _pcos[1][i] * _pcos[7][j];
  sum += m[7][2] * _pcos[2][i] * _pcos[7][j];
  sum += m[7][3] * _pcos[3][i] * _pcos[7][j];
  sum += m[7][4] * _pcos[4][i] * _pcos[7][j];
  sum += m[7][5] * _pcos[5][i] * _pcos[7][j];
  sum += m[7][6] * _pcos[6][i] * _pcos[7][j];
  sum += m[7][7] * _pcos[7][i] * _pcos[7][j];*/
  return (int) (0.25 * C(i) * C(j) * sum);
}

int VideoCodec::idct(int32_t m[8][8], uint8_t x, uint8_t y)
{
  double sum = 0.;

  for (uint8_t j = 0; j < 8; j++)
    for (uint8_t i = 0; i < 8; i++)
      sum += C(i) * C(j) * m[j][i] * COS1 * COS2;
  //sum += C(i) * C(j) * PPPCOS;//m[j][i] * PPCOS;//PCOS1 * PCOS2;
  return (int) (0.25 * sum);
}

/*********************
 Run Length Encoding
**********************/

/*
** 2Byte  1Bytes         sizeBytes
**  DC     size      Rle Compressed Data
*/

void VideoCodec::rle(uint32_t luma[8][8], uint32_t chromaU[8][8], uint32_t chromaV[8][8])
{
  uint32_t tmp[64];
  unsigned char size;
  //static int test = 0;
  zigzag(luma, tmp);
  size = compressRle(&tmp[1], _result + _buffsize + 3);

  /*std::cout << "-------------" << std::endl;
 std::cout << "sz "   << (int) size << std::endl;
 std::cout << "nb : " << (int)(_result + _buffsize + 3)[0] << std::endl;
 std::cout << "val: " << (int)(_result + _buffsize + 3)[1] << std::endl;
 std::cout << "nb : " << (int)(_result + _buffsize + 3)[2] << std::endl;
 std::cout << "val: " << (int)(_result + _buffsize + 3)[3] << std::endl;
 std::cout << "nb : " << (int)(_result + _buffsize + 3)[4] << std::endl;
 std::cout << "val: " << (int)(_result + _buffsize + 3)[5] << std::endl;
 std::cout << "nb : " << (int)(_result + _buffsize + 3)[6] << std::endl;
 std::cout << "val: " << (int)(_result + _buffsize + 3)[7] << std::endl;
 std::cout << "============" << std::endl;*/

  //std::cout << "size is " << (int) size << std::endl;
  *(short *)(_result + _buffsize) = tmp[0] & 0xffff;
  *(_result + _buffsize + 2) = size;
  _buffsize += size + 3;

  /*for (int i = 0; i < 8; i++)
    for (int j = 0; j < 8; j++)
      *(_result + _buffsize + i*8 + j) = luma[i][j];
  _buffsize += 64;

  for (int i = 0; i < 8; i++)
    for (int j = 0; j < 8; j++)
      *(_result + _buffsize + i*8 + j) = chromaU[i][j];

  for (int i = 0; i < 8; i++)
    for (int j = 0; j < 8; j++)
      *(_result + _buffsize + 64 + i*8 + j) = chromaV[i][j];

      _buffsize += 128;*/

  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++)
      *(_result + _buffsize + i*4 + j) = chromaU[i<<1][j<<1];

  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++)
      *(_result + _buffsize + 16 + i*4 + j) = chromaV[i<<1][j<<1];

      _buffsize += 32;

  /*zigzag(chromaU, tmp);
  _buffsize += compressRle(tmp, _result + _buffsize);
  zigzag(chromaV, tmp);
  _buffsize += compressRle(tmp, _result + _buffsize);*/
}

void VideoCodec::irle(uint32_t luma[8][8], uint32_t chromaU[8][8], uint32_t chromaV[8][8])
{
  uint32_t tmp[64], tmp2;
  unsigned char size;

  tmp[0] = *(short *)(_resultDec + _buffsize);
  size = *(_resultDec + _buffsize + 2);
  //std::cout << "size is " << (int)size << std::endl;
  decompressRle(_resultDec + _buffsize + 3, &tmp[1], size);
  /*std::cout << "-------------" << std::endl;
  std::cout << "dc : " << tmp[0] << std::endl;
  std::cout << "sz : " << (int)size << std::endl;
  std::cout << "nb : " << tmp[1] << std::endl;
  std::cout << "val: " << tmp[2] << std::endl;
  std::cout << "nb : " << tmp[3] << std::endl;
  std::cout << "val: " << tmp[4] << std::endl;
  std::cout << "nb : " << tmp[5] << std::endl;
  std::cout << "val: " << tmp[6] << std::endl;
  std::cout << "nb : " << tmp[7] << std::endl;
  std::cout << "val: " << tmp[8] << std::endl;
  std::cout << "============" << std::endl;*/
  zigzag2(luma, tmp);
  _buffsize += size + 3;
  
  /*for (int i = 0; i < 8; i++)
    for (int j = 0; j < 8; j++)
      luma[i][j] = *(_resultDec + _buffsize + i*8 + j);
  _buffsize += 64;

  for (int i = 0; i < 8; i++)
    for (int j = 0; j < 8; j++)
      chromaU[i][j] = *(_resultDec + _buffsize + i*8 + j);
  _buffsize += 64;

  for (int i = 0; i < 8; i++)
    for (int j = 0; j < 8; j++)
      chromaV[i][j] = *(_resultDec + _buffsize + i*8 + j);
      _buffsize += 64;*/

  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++)
      {
	tmp2 = *(_resultDec + _buffsize + i*4 + j);
	chromaU[(i<<1)][(j<<1)]     = tmp2;
	chromaU[(i<<1)+1][(j<<1)]   = tmp2;
	chromaU[(i<<1)][(j<<1)+1]   = tmp2;
	chromaU[(i<<1)+1][(j<<1)+1] = tmp2;
      }

  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++)
      {
	tmp2 = *(_resultDec + _buffsize + 16 + i*4 + j);
	chromaV[(i<<1)][(j<<1)]     = tmp2;
	chromaV[(i<<1)+1][(j<<1)]   = tmp2;
	chromaV[(i<<1)][(j<<1)+1]   = tmp2;
	chromaV[(i<<1)+1][(j<<1)+1] = tmp2;
      }

  _buffsize += 32;
}

int			VideoCodec::compressRle(uint32_t *tab, uint8_t *comp)
{
  int			j = 1;
  int			nb = 1;
  int			i = 0;

  while (j != 63)//64)
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
  //std::cout << "i ============ " << i << std::endl;
  return i + 1;
}

void			VideoCodec::decompressRle(unsigned char *comp, uint32_t *dec, int size)
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

/**************
Zigzag2
 *************/

void		VideoCodec::goRight(uint32_t *cha, uint32_t *x, uint32_t *i, uint32_t c)
{
  *cha = c;
  *x = *x + 1;
  *i = *i + 1;
}

void		VideoCodec::goDown(uint32_t *cha, uint32_t *y, uint32_t *i, uint32_t c)
{
  *cha = c;
  *y = *y + 1;
  *i = *i + 1;
}

void		VideoCodec::goDownLeft(uint32_t *cha, uint32_t tab[8][8], uint32_t *i, uint32_t *x, uint32_t *y)
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

void		VideoCodec::goUpRight(uint32_t *cha, uint32_t tab[8][8], uint32_t *i, uint32_t *x, uint32_t *y)
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

void		VideoCodec::zigzag(uint32_t tab[8][8], uint32_t cha[64])
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

/***************
Zigzag2
 **************/

void		VideoCodec::goRight2(uint32_t *cha, uint32_t *x, uint32_t *i, uint32_t c)
{
  *cha = c;
  *x = *x + 1;
  *i = *i + 1;
}

void		VideoCodec::goDown2(uint32_t *cha, uint32_t *y, uint32_t *i, uint32_t c)
{
  *cha = c;
  *y = *y + 1;
  *i = *i + 1;
}

void		VideoCodec::goDownLeft2(uint32_t *cha, uint32_t tab[8][8], uint32_t *i, uint32_t *x, uint32_t *y)
{
  tab[*y][*x] = cha[*i];
  *i = *i + 1;
  while (*x > 0 && *y < 7)
    {
      *x = *x - 1;
      *y = *y + 1;
      if (*x > 0 && *y < 7)
	{
	  tab[*y][*x] = cha[*i];
	  *i = *i + 1;
	}
    }
}

void		VideoCodec::goUpRight2(uint32_t *cha, uint32_t tab[8][8], uint32_t *i, uint32_t *x, uint32_t *y)
{
  tab[*y][*x] = cha[*i];
  *i = *i + 1;
  while (*x < 7 && *y > 0)
    {
      *x = *x + 1;
      *y = *y - 1;
      if (*x < 7 && *y > 0)
	{
	  tab[*y][*x] = cha[*i];
	  *i = *i + 1;
	}
    }
}

void		VideoCodec::zigzag2(uint32_t tab[8][8], uint32_t cha[64])
{
  uint32_t     	x = 0;
  uint32_t     	y = 0;

  for (uint32_t i = 0; i < 64;)
    {
      if (x < 7)
	{
	  goRight2(&tab[y][x], &x, &i, cha[i]);
	  goDownLeft2(cha, tab, &i, &x, &y);
	}
      if (x == 7 && y != 0)
	{
	  goDown2(&tab[y][x], &y, &i, cha[i]);
	  goDownLeft2(cha, tab, &i, &x, &y);
	}
      if (y < 7)
	{
	  goDown2(&tab[y][x], &y, &i, cha[i]);
	  goUpRight2(cha, tab, &i, &x, &y);
	}
      if (y == 7)
	{
	  goRight2(&tab[y][x], &x, &i, cha[i]);
	  goUpRight2(cha, tab, &i, &x, &y);
	}
    }
}
