//
//  Transcoding.cpp
//  testcpp
//
//  Created by Meteor on 16/5/30.
//  Copyright © 2016年 meteor. All rights reserved.
//

#include "Transcoding.h"

/* 代码转换示例C++程序 */

#include <iostream>

#define OUTLEN 255

using namespace std;
char base64_index[65] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
char *pcfBase64Encode(const char *pcInput)
{
    size_t ulIndex1=0,ulIndex2,ulLength;
    char *pcOutput=new char[40];
    ulLength=0;
    pcOutput[0] = '\0';
    if (pcInput[0] == '\0')
        return pcOutput;
    while(pcInput[ulLength]!='\0')
        ulLength++;
    
    // 0x30 -> 00110000
    // 0x3C -> 00111100
    // 0x3F -> 00111111
    
    // 11111111 00000000 11111111
    // 111111 110000 000011 111111
    ulIndex1 = 0;
    ulIndex2 = 0;
    while (ulIndex1 <= ulLength-3) {
        pcOutput[ulIndex2++] = base64_index[( pcInput[ulIndex1] >> 2 ) & 0x3F];
        pcOutput[ulIndex2++] = base64_index[( (pcInput[ulIndex1] << 4) & 0x30 ) | ( pcInput[ulIndex1+1] >> 4 )];
        pcOutput[ulIndex2++] = base64_index[( (pcInput[ulIndex1+1] << 2) & 0x3C ) | ( pcInput[ulIndex1+2] >> 6 )];
        pcOutput[ulIndex2++] = base64_index[pcInput[ulIndex1+2] & 0x3F];
        ulIndex1 += 3;
    }
    
    if (ulLength - ulIndex1 > 0) {
        pcOutput[ulIndex2++] = base64_index[( pcInput[ulIndex1] >> 2 ) & 0x3F];
        if (ulLength - ulIndex1  == 2) {
            pcOutput[ulIndex2++] = base64_index[( (pcInput[ulIndex1] << 4) & 0x30 ) | ( pcInput[ulIndex1+1] >> 4 )];
            pcOutput[ulIndex2++] = base64_index[(pcInput[ulIndex1+1] << 2) & 0x3C];
            pcOutput[ulIndex2++] = '=';
        } else if (ulLength - ulIndex1  == 1) {
            pcOutput[ulIndex2++] = base64_index[(pcInput[ulIndex1] << 4) & 0x30];
            pcOutput[ulIndex2++] = '=';
            pcOutput[ulIndex2++] = '=';
        }
    }
    
    pcOutput[ulIndex2++] = '\0';
    return pcOutput;
}

char GetCharIndex(char cTemp) //内联函数可以省去函数调用过程，提速
{   if((cTemp >= 'A') && (cTemp <= 'Z'))
    return cTemp - 'A';
else if((cTemp >= 'a') && (cTemp <= 'z'))
    return cTemp - 'a' + 26;
else if((cTemp >= '0') && (cTemp <= '9'))
    return cTemp - '0' + 52;
else if(cTemp == '+')
    return 62;
else if(cTemp == '/')
    return 63;
else if(cTemp == '=')
    return 0;
    return 0;
}

unsigned char charToHex(char cTemp)
{
    if (cTemp>='0' && cTemp<='9') {
        return cTemp-'0';
    }
    else if (cTemp>='A' && cTemp<='Z') {
        return cTemp-'A'+10;
    }
    else if (cTemp>='a' && cTemp<='z') {
        return cTemp-'a'+10;
    }
    return -1;
}

unsigned char *pcfQuotedPrintableDecode(const char *pcSrc, size_t ulLen)
{
    unsigned char *pcDes=new unsigned char[ulLen];
    size_t ulSrcLen = 0;
    size_t ulDesLen = 0;
    while(ulDesLen <= ulLen) {
        if (pcSrc[ulSrcLen] != '=') {
            pcDes[ulDesLen++] = pcSrc[ulSrcLen++];
        }
        else if (strncmp(pcSrc+ulSrcLen, "=\r\n", 3) == 0) {//lpSrc[sLen+1]=='\r' && lpSrc[sLen+2]=='\n'
            ulSrcLen += 3;
        }
        else{
            if (charToHex(pcSrc[ulSrcLen+2])==(unsigned char)-1) {
                pcDes[ulDesLen++] = (charToHex(pcSrc[ulSrcLen+1])<<4) + charToHex(pcSrc[ulSrcLen+3]);
                ulSrcLen += 4;
            }
            else {
                pcDes[ulDesLen++] = (charToHex(pcSrc[ulSrcLen+1])<<4) + charToHex(pcSrc[ulSrcLen+2]);
                ulSrcLen += 3;
            }
        }
    }
    return pcDes;
}

bool pcfBase64Decode(char *pcDes, const char *pcSrc, size_t ulLen)   //解码函数
{   static char acCode[4];
    size_t ulDesLen = 0;
    memset(pcDes, 0, ulLen/4*3+1);
    if(ulLen % 4)        //Base64编码长度必定是4的倍数，包括'='
        return false;
    while(ulLen > 2)      //不足三个字符，忽略
    {   acCode[0] = GetCharIndex(pcSrc[0]);
        acCode[1] = GetCharIndex(pcSrc[1]);
        acCode[2] = GetCharIndex(pcSrc[2]);
        acCode[3] = GetCharIndex(pcSrc[3]);
        
        pcDes[ulDesLen++] = (acCode[0] << 2) | (acCode[1] >> 4);
        pcDes[ulDesLen++] = (acCode[1] << 4) | (acCode[2] >> 2);
        pcDes[ulDesLen++] = (acCode[2] << 6) | (acCode[3]);
        
        pcSrc += 4;
        ulLen -= 4;
    }
    return true;
}

size_t ulItoa(int val, char* buf)
{
    const unsigned int radix = 10;
    char* p;
    size_t a; //every digit
    size_t len;
    char* b; //start of the digit char
    char temp;
    unsigned int u;
    p = buf;
    if (val < 0)
    {
        *p++ = '-';
        val = 0 - val;
    }
    u = (unsigned int)val;
    b = p;
    do
    {
        a = u % radix;
        u /= radix;
        *p++ = a + '0';
    } while (u > 0);
    len = (int)(p - buf);
    *p-- = 0;
    //swap
    do
    {
        temp = *p;
        *p = *b;
        *b = temp;
        --p;
        ++b;
    } while (b < p);
    return len;
}

bool bfCodingConvert(char *pcInBuf,size_t ulInLen,char *pcOutbuf,size_t ulOutLen, const char *pcFromCharset, const char *pcToCharset) {
    char **ppcIn = &pcInBuf;
    char **ppcOut = &pcOutbuf;
    size_t ulLen;
    memset(pcOutbuf,0,ulOutLen);
    iconv_t cd = iconv_open(pcToCharset, pcFromCharset);
    if (cd == (iconv_t)-1) return false;
    ulLen = iconv(cd,ppcIn,(size_t *)&ulInLen,ppcOut,(size_t *)&ulOutLen);
    if (ulLen == (size_t)-1) return false;
    iconv_close(cd);
    return true;
}

//windows
//std::string GBKToUTF8(const char* strGBK)
//{
//    int len = MultiByteToWideChar(CP_ACP, 0, strGBK, -1, NULL, 0);
//    wchar_t* wstr = new wchar_t[len+1];
//    memset(wstr, 0, len+1);
//    MultiByteToWideChar(CP_ACP, 0, strGBK, -1, wstr, len);
//    len = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, NULL, 0, NULL, NULL);
//    char* str = new char[len+1];
//    memset(str, 0, len+1);
//    WideCharToMultiByte(CP_UTF8, 0, wstr, -1, str, len, NULL, NULL);
//    std::string strTemp = str;
//    if(wstr) delete wstr;
//    if(str) delete str;
//    return strTemp;
//}
