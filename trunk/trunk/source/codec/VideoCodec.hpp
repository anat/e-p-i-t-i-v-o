#ifndef VIDEOCODEC_HPP
# define VIDEOCODEC_HPP

# include <stdint.h>
# include <math.h>

enum colorType
  {
    COLOR_RGB,
    COLOR_BGR
  };

# define KEY_FREQ 12 /* 1 key frame every KEY_FREQ frames */

# define C(x) (!(x) ? 0.707106781 : 1)
# define COS1 (cos((2 * x + 1) * i * M_PI / 16))
# define COS2 (cos((2 * y + 1) * j * M_PI / 16))

/*
# define YUV_TO_RGB(y, x, n)						\
  bloc[((y)*24)+((x)*3)]   = roundf(Y[n] + 1.13983f * V[n]);		\
  bloc[((y)*24)+((x)*3)+1] = roundf(Y[n] - (0.39465f * U[n])		\
				    - (0.58060f * V[n]));		\
  bloc[((y)*24)+((x)*3)+2] = roundf(Y[n] + 2.03211f * U[n]);
*/

class VideoCodec
{
private:
  uint16_t       _width;
  uint16_t       _heigth;
  enum colorType _type;     /* RGB || BGR              */
  uint8_t       *_result;   /* Compressed image buffer */
  uint32_t       _buffsize; /* Compressed data size    */
  uint32_t       _numb;     /* Current frame number    */
  static const uint32_t quantization_matrix[8][8];

public:
  VideoCodec(int width, int heigth, enum colorType color = COLOR_RGB);
  ~VideoCodec();
  uint32_t encode(uint8_t *img);
  void     decode(uint8_t *img);
  uint8_t *getProcessedImg()     const;

private:
  /* Image compression */
  void rgb_to_yuv(uint8_t *img, uint32_t x, uint32_t y,
		  uint32_t luma[8][8], uint32_t chromaU[8][8], uint32_t chromaV[8][8]);

  void downsampling420(uint32_t chromaU[8][8], uint32_t chromaV[8][8]);

  void dct(uint32_t luma[8][8], uint32_t chromaU[8][8], uint32_t chromaV[8][8]);
  void idct(uint32_t luma[8][8], uint32_t chromaU[8][8], uint32_t chromaV[8][8]);
  void quantization(uint32_t luma[8][8], uint32_t chromaU[8][8], uint32_t chromaV[8][8]);
  void iquantization(uint32_t luma[8][8], uint32_t chromaU[8][8], uint32_t chromaV[8][8]);
  int  dct(uint32_t m[8][8], uint8_t u, uint8_t v);
  int  idct(uint32_t m[8][8], uint8_t x, uint8_t y);


  /* Run Length Encoding */
  void rle(uint32_t luma[8][8], uint32_t chromaU[8][8], uint32_t chromaV[8][8]);
  int  compressRle(uint32_t tab[64], uint8_t *comp);
  void decompressRle(int comp[128], int dec[64], int size);
  void goRight(uint32_t *cha, uint32_t *x, uint32_t *i, uint32_t c);
  void goDown(uint32_t *cha, uint32_t *y, uint32_t *i, uint32_t c);
  void goDownLeft(uint32_t *cha, uint32_t tab[8][8], uint32_t *i, uint32_t *x, uint32_t *y);
  void goUpRight(uint32_t *cha, uint32_t tab[8][8], uint32_t *i, uint32_t *x, uint32_t *y);
  void zigzag(uint32_t tab[8][8], uint32_t cha[64]);

  /* Huffman */
};
#endif
