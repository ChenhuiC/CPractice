/**
 * @file base64.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-07-12
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <stdio.h>
#include <string.h>


#define BASE64_DEBUG  0

const char * base64char = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

/**
 * @brief 
 * 
 * @param bindata 
 * @param base64 
 * @param binlength 
 * @return char* 
 */
char *base64_encode(const unsigned char * bindata, char * base64, int binlength)
{
  int i, j;
  unsigned char current;

  for(i = 0, j = 0 ; i < binlength ; i += 3)
  {
    current =(bindata[i] >> 2) ;
    current &=(unsigned char)0x3F;
    base64[j++] = base64char[(int)current];

    current =((unsigned char)(bindata[i] << 4)) &((unsigned char)0x30) ;
    if(i + 1 >= binlength)
    {
      base64[j++] = base64char[(int)current];
      base64[j++] = '=';
      base64[j++] = '=';
      break;
    }
    current |=((unsigned char)(bindata[i+1] >> 4)) &((unsigned char) 0x0F);
    base64[j++] = base64char[(int)current];

    current =((unsigned char)(bindata[i+1] << 2)) &((unsigned char)0x3C) ;
    if(i + 2 >= binlength)
    {
      base64[j++] = base64char[(int)current];
      base64[j++] = '=';
      break;
    }
    current |=((unsigned char)(bindata[i+2] >> 6)) &((unsigned char) 0x03);
    base64[j++] = base64char[(int)current];

    current =((unsigned char)bindata[i+2]) &((unsigned char)0x3F) ;
    base64[j++] = base64char[(int)current];
  }
  base64[j] = '\0';
  return base64;
}

/**
 * @brief 
 * 
 * @param base64 
 * @param bindata 
 * @return int 
 */
int base64_decode(const char * base64, unsigned char * bindata)
{
  int i, j;
  unsigned char k;
  unsigned char temp[4];
  for(i = 0, j = 0; base64[i] != '\0' ; i += 4)
  {
    memset(temp, 0xFF, sizeof(temp));
    for(k = 0 ; k < 64 ; k ++)
    {
      if(base64char[k] == base64[i])
        temp[0]= k;
    }
    for(k = 0 ; k < 64 ; k ++)
    {
      if(base64char[k] == base64[i+1])
        temp[1]= k;
    }
    for(k = 0 ; k < 64 ; k ++)
    {
      if(base64char[k] == base64[i+2])
        temp[2]= k;
    }
    for(k = 0 ; k < 64 ; k ++)
    {
      if(base64char[k] == base64[i+3])
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

    // printf("unsigned short int len:%d\r\n",sizeof(unsigned short int));
    // printf("unsigned int len:%d\r\n",sizeof(unsigned int));
    unsigned char bindata[] = "{\"sn\":\"8368230106R00001\",\"timestamp\":\"1689126119000\"}";
    char base64[1024];

    printf("%d\n", (int)sizeof(bindata));
    memset(base64, 0, 1024);
    base64_encode(bindata, base64, sizeof(bindata)-1);
    printf("%s\n", base64);

    /* 测试解密 */
    // const char *base64 = "eyJzbiI6IjgzNjgyMzAxMDZSMDAwMDEiLCJ0aW1lc3RhbXAiOiIxNjgwNTc0NTk2MDAwIn0";
    // unsigned char bindata[1024];
    // memset(bindata, 0, 1024);
    // printf("encryption data: %s\n",base64);
    // int len = 0;
    // len = base64_decode(base64,bindata);
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