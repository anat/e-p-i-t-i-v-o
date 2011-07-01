#ifndef VIDEOCODEC_HPP
# define VIDEOCODEC_HPP

# include <stdint.h>
# include <math.h>
# include "Huffman.h"

enum colorType
  {
    COLOR_RGB,
    COLOR_BGR
  };

# define KEY_FREQ 48 /* 1 key frame every KEY_FREQ frames */

# define C(x) (!(x) ? 0.707106781 : 1)
# define COS1 (cos((2 * x + 1) * i * M_PI / 16))
# define COS2 (cos((2 * y + 1) * j * M_PI / 16))
# define PCOS1 _pcos[x][i] /* Precalculated cosinus */
# define PCOS2 _pcos[y][j] /* Precalculated cosinus */
# define PPCOS _ppcos[i][j][y][x]
# define PPPCOS _pppcos[m[y][x]][i][j][y][x]

class VideoCodec
{
private:
  uint16_t       _width;
  uint16_t       _heigth;
  enum colorType _type;       /* RGB || BGR              */
  uint8_t       *_result;     /* Compressed image buffer */
  uint8_t       *_last;
  uint8_t       *_last2;
  //uint8_t       *_truc;
  uint32_t       _buffsize;   /* Compressed data size    */
  uint32_t       _numb;       /* Current frame number    */
  uint32_t       _numb2;      /* Current frame number (Decode)   */
  //double         _pcos[8][8]; /* Precalculated cosinus   */
  //double         _ppcos[8][8][8][8]; /* Precalculated cosinus   */
  double         _pppcos[256][8][8][8][8]; /* Precalculated cosinus   */
  Huffman        huffman;
  static const int32_t quantization_matrix[8][8];

public:
  VideoCodec(int width, int heigth, enum colorType color = COLOR_RGB);
  ~VideoCodec();
  uint32_t encode(uint8_t *img);
  void     decode(uint8_t *img);
  uint8_t *getProcessedImg()     const;
  void setResultBuff(uint8_t *res);

private:
  /* Image compression */
  void rgb_to_yuv(uint8_t *img, uint32_t x, uint32_t y,
		  int32_t luma[8][8], int32_t chromaU[8][8], int32_t chromaV[8][8]);
  void yuv_to_rgb(uint8_t *img, uint32_t x, uint32_t y,
		  int32_t luma[8][8], int32_t chromaU[8][8], int32_t chromaV[8][8]);
  void downsampling420(uint32_t chromaU[8][8], uint32_t chromaV[8][8]);

  void dct(uint32_t luma[8][8], uint32_t chromaU[8][8], uint32_t chromaV[8][8]);
  void idct(int32_t luma[8][8], uint32_t chromaU[8][8], uint32_t chromaV[8][8]);
  void quantization(int32_t luma[8][8], uint32_t chromaU[8][8], uint32_t chromaV[8][8]);
  void iquantization(int32_t luma[8][8], uint32_t chromaU[8][8], uint32_t chromaV[8][8]);
  int  dct(uint32_t m[8][8], uint8_t u, uint8_t v);
  int  idct(int32_t m[8][8], uint8_t x, uint8_t y);
  void diff(uint8_t *img);


  /* Run Length Encoding */
  void rle(uint32_t luma[8][8], uint32_t chromaU[8][8], uint32_t chromaV[8][8]);
  void irle(uint32_t luma[8][8], uint32_t chromaU[8][8], uint32_t chromaV[8][8]);
  int  compressRle(uint32_t *tab, uint8_t *comp);
  void decompressRle(unsigned char *comp, uint32_t *dec, int size);
  void goRight(uint32_t *cha, uint32_t *x, uint32_t *i, uint32_t c);
  void goDown(uint32_t *cha, uint32_t *y, uint32_t *i, uint32_t c);
  void goDownLeft(uint32_t *cha, uint32_t tab[8][8], uint32_t *i, uint32_t *x, uint32_t *y);
  void goUpRight(uint32_t *cha, uint32_t tab[8][8], uint32_t *i, uint32_t *x, uint32_t *y);
  void zigzag(uint32_t tab[8][8], uint32_t cha[64]);
  void goRight2(uint32_t *cha, uint32_t *x, uint32_t *i, uint32_t c);
  void goDown2(uint32_t *cha, uint32_t *y, uint32_t *i, uint32_t c);
  void goDownLeft2(uint32_t *cha, uint32_t tab[8][8], uint32_t *i, uint32_t *x, uint32_t *y);
  void goUpRight2(uint32_t *cha, uint32_t tab[8][8], uint32_t *i, uint32_t *x, uint32_t *y);
  void zigzag2(uint32_t tab[8][8], uint32_t cha[64]);

  /* Huffman */
};
#endif
