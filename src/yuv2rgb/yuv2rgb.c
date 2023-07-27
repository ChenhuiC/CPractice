/**
* @file: yuv2rgb.c
* @brief: 
* @author: chenhui
* @created: 2023-07-27 22:17:57
* 
* @copyright (C), 2008-2023
* 
*/
/* includes ------------------------------------------------------------------*/
#include <stdio.h>


/* private marcos ------------------------------------------------------------*/
/* private types -------------------------------------------------------------*/
typedef struct RGB565
{
	unsigned short R:5;
	unsigned short G:6;
	unsigned short B:5;
}RGB565_T;


/* private variables ---------------------------------------------------------*/
/* private functions ---------------------------------------------------------*/








/* 普通算法，带浮点运算 */
/**
 * NV12属于YUV420SP格式         YYYYYYYY VUVU    =>YUV420SP
 * @param data
 * @param rgb
 * @param width
 * @param height
 */
static void NV12_TO_RGB24_FLOAT(unsigned char *data, unsigned char *rgb, int width, int height) 
{
    int index = 0;
    unsigned char *ybase = data;
    unsigned char *ubase = &data[width * height];
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            //YYYYYYYYUVUV
            unsigned char Y = ybase[x + y * width];
            unsigned char U = ubase[y / 2 * width + (x / 2) * 2];
            unsigned char V = ubase[y / 2 * width + (x / 2) * 2 + 1];

            rgb[index++] = Y + 1.402 * (V - 128); //R
            rgb[index++] = Y - 0.34413 * (U - 128) - 0.71414 * (V - 128); //G
            rgb[index++] = Y + 1.772 * (U - 128); //B
        }
    }
}


/*改进，使用整型代替浮点型运算， 要用移位的办法*/
static void NV12_TO_RGB24_INT(unsigned char *data, unsigned char *rgb888, int width, int height) 
{
    int index = 0;
    unsigned char *ybase = data;
    unsigned char *ubase = &data[width * height];
    unsigned char Y,U,V,u,v;
    unsigned char rdif,invgdif,bdif;
    
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            //YYYYYYYYUVUV
            Y = ybase[x + y * width];
            U = ubase[y / 2 * width + (x / 2) * 2];
            V = ubase[y / 2 * width + (x / 2) * 2 + 1];
            u = U - 128;
            v = V - 128;
            rdif = v + ((v * 103) >> 8);
            invgdif = ((u * 88) >> 8) +((v * 183) >> 8);
            bdif = u +((u*198) >> 8);
            
            rgb888[index++] = Y + rdif;
            rgb888[index++] = Y - invgdif;
            rgb888[index++] = Y + bdif;
        }
    }
}

/*
    要从RGB24转换成RGB565数据还要做移位和或运算：

       RGBdata[1] =( (r & 0xF8) | ( g >> 5) );
       RGBdata[0] =( ((g & 0x1C) << 3) | ( b >> 3) );
*/
void NV12_TO_RGB565_INT(unsigned char *data, unsigned char *rgb565, int width, int height) 
{
    int index = 0;
    unsigned char *ybase = data;
    unsigned char *ubase = &data[width * height];
    unsigned char Y,U,V,u,v;
    unsigned char rdif,invgdif,bdif;
   
   for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            //YYYYYYYYUVUV
            Y = ybase[x + y * width];
            U = ubase[y / 2 * width + (x / 2) * 2];
            V = ubase[y / 2 * width + (x / 2) * 2 + 1];
            u = U - 128;
            v = V - 128;
            rdif = v + ((v * 103) >> 8);
            invgdif = ((u * 88) >> 8) +((v * 183) >> 8);
            bdif = u +((u*198) >> 8);
            
            // rgb888[index++] = Y + rdif;
            // rgb888[index++] = Y - invgdif;
            // rgb888[index++] = Y + bdif;

            rgb565[index++] = ((Y + rdif) &  0xF8) | ((Y - invgdif) >> 5);
            rgb565[index++] = (((Y - invgdif) & 0x1C) << 3) | ((Y + bdif) >> 3);
        }
    }
    
}

/* 进一步改进， 查表（部分查表法）： 用查表替代上述整型算法中的乘法运算*/




/* 完全查表法 */


static void RGB888_TO_RGB565(unsigned char *buffer, unsigned char *rgb565, int width, int height)
{
    RGB565_T *buffer1 = (RGB565_T*)rgb565;
    for(int i=0;i<width*height;i++)
    {
        buffer1[i].R = buffer[i*3]>>3;
        buffer1[i].G = buffer[i*3+1]>>2;
        buffer1[i].B = buffer[i*3+2]>>3;
    }
}
