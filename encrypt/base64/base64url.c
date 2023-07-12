/**
 * @file base64URL.c
 * @author Chanhuni
 * @brief Base64编码是使用64个可打印ASCII字符（A-Z、a-z、0-9、+、/）将任意字节序列数据编码成ASCII字符串
 *        原理：将原来3个字节变成4个字节，将3个字节(共24位)变成4个字节后，每个字节只有6bit有效，6bit所能表示的字符正好是64个
 *              将3个字节拆分为4个字节，那么就肯定需要编码前总的字节数是3的倍数，这样编码后的内容才会是4的倍数，不是3的倍数时（编码前可以不是3的倍数，但编码后需要是4的倍数。解决办法：给编码后的内容补充’==’），在末尾有且可能最多存在两个'='
 *        注意： URL安全的Base64编码特点：
 *              1. 不能被3整除时，不补=符号。
 *              2. 生成Base64编码中，"+"和"/"被替换成其他非URL保留字符，使其可以直接放入URL中传输。比如"+"和"/"被替换成"-"和"_"。
 *              安全的Base64编码也有好多种，有些编码不会去掉等号，有些编码替换的符号不同
 * @version 0.1
 * @date 2023-07-12
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BASE64_DEBUG  1

const char * base64urlchar = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_";

/**
 * @brief base64url加密
 * 
 * @param bindata 原始数据
 * @param base64 加密后数据
 * @param binlength 原始数据长度
 * @return char* 
 */
char *base64url_encode(const unsigned char * bindata, char * base64, int binlength)
{
  int i, j;
  unsigned char current;

  for(i = 0, j = 0 ; i < binlength ; i += 3)            /* 将3字节拆为4字节 */
  {
    current =(bindata[i] >> 2) ;
    current &=(unsigned char)0x3F;
    base64[j++] = base64urlchar[(int)current];

    current =((unsigned char)(bindata[i] << 4)) &((unsigned char)0x30) ;    /* 获取剩余2bit */
    if(i + 1 >= binlength)              /* 移向下一字节时需要判断是否到结尾 */
    {
      base64[j++] = base64urlchar[(int)current];
    //   base64[j++] = '=';                 /* =用在URL、Cookie里面会造成歧义，所以，Base64URL编码后会把=去掉 */
    //   base64[j++] = '=';
      break;
    }
    current |=((unsigned char)(bindata[i+1] >> 4)) &((unsigned char) 0x0F);
    base64[j++] = base64urlchar[(int)current];

    current =((unsigned char)(bindata[i+1] << 2)) &((unsigned char)0x3C) ;
    if(i + 2 >= binlength)
    {
      base64[j++] = base64urlchar[(int)current];
    //   base64[j++] = '=';
      break;
    }
    current |=((unsigned char)(bindata[i+2] >> 6)) &((unsigned char) 0x03);
    base64[j++] = base64urlchar[(int)current];

    current =((unsigned char)bindata[i+2]) &((unsigned char)0x3F) ;
    base64[j++] = base64urlchar[(int)current];
  }
  base64[j] = '\0';
  return base64;
}

/**
 * @brief base64url解密
 * 
 * @param base64url 
 * @param bindata 解密后的数据
 * @return int 
 */
int base64url_decode(const char * base64url, unsigned char * bindata)
{
  int i, j;
  unsigned char k;
  unsigned char temp[4];
  unsigned int urllen = strlen(base64url),base64len;
  unsigned char mod = urllen%4;
  unsigned char addValue = (mod)?(4 - mod):(0);
  base64len = urllen+addValue+1;      /* 加'\0'字符 */
  char *base64 = malloc(base64len);
  memcpy(base64,base64url,urllen);
  if(addValue == 1){
    base64[base64len-2] = '=';
    base64[base64len-1] = '\0';
  }else if (addValue == 2)
  {
    base64[base64len-3] = '=';
    base64[base64len-2] = '=';
    base64[base64len-1] = '\0';
  }
  // printf("base64: %s\r\n",base64);
  for(i = 0, j = 0; base64[i] != '\0' ; i += 4)
  {
    memset(temp, 0xFF, sizeof(temp));
    for(k = 0 ; k < 64 ; k ++)
    {
      if(base64urlchar[k] == base64[i])
        temp[0]= k;
    }
    for(k = 0 ; k < 64 ; k ++)
    {
      if(base64urlchar[k] == base64[i+1])
        temp[1]= k;
    }
    for(k = 0 ; k < 64 ; k ++)
    {
      if(base64urlchar[k] == base64[i+2])
        temp[2]= k;
    }
    for(k = 0 ; k < 64 ; k ++)
    {
      if(base64urlchar[k] == base64[i+3])
        temp[3]= k;
    }

    bindata[j++] =((unsigned char)(((unsigned char)(temp[0] << 2))&0xFC)) |
       ((unsigned char)((unsigned char)(temp[1]>>4)&0x03));
    if(base64[i+2] == '=')
      break;

    bindata[j++] =((unsigned char)(((unsigned char)(temp[1] << 4))&0xF0)) |
       ((unsigned char)((unsigned char)(temp[2]>>2)&0x0F));
    if(base64[i+3] == '=')
      break;

    bindata[j++] =((unsigned char)(((unsigned char)(temp[2] << 6))&0xF0)) |
       ((unsigned char)(temp[3]&0x3F));
  }
  return j;
}


#if (BASE64_DEBUG == 1)
int main()
{
    // unsigned char bindata[] = "{\"alg\":\"HS256\",\"typ\":\"JWT\"}";

    unsigned char bindata[] = "{\"sn\":\"8368230106R00001\",\"timestamp\":\"1689126119000\"}";

    char base64[1024];
    printf("%d\n", sizeof(bindata)-1);
    memset(base64, 0, 1024);
    base64url_encode(bindata, base64, sizeof(bindata)-1);
    printf("%s\n", base64);

    /* 测试解密 */
    // const char *base64 = "eyJzbiI6IjgzNjgyMzAxMDZSMDAwMDEiLCJ0aW1lc3RhbXAiOiIxNjg5MTI2MTE5MDAwIn0";
    // unsigned char bindata[1024];
    // memset(bindata, 0, 1024);
    // printf("encryption data: %s\n",base64);
    // int len = 0;
    // len = base64url_decode(base64,bindata);
    // printf("%s\r\n",bindata);
    // if(len != 0)
    // {
    //     printf("decode data len: %d ,data is: ",len);
    //     for(int i=0; i<len; i++)
    //     {
    //         printf(" %02X",bindata[i]);
    //     }
    //     printf("\n");
    // }

  return 0;
}
#endif

