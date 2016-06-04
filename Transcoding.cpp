//
//  Transcoding.cpp
//  testcpp
//
//  Created by Meteor on 16/5/30.
//  Copyright © 2016年 meteor. All rights reserved.
//

#include "Transcoding.hpp"

/* 代码转换示例C++程序 */

#include <iostream>

#define OUTLEN 255

using namespace std;
char base64_index[65] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
char *base64_encode(const char *input)
{
    int i=0,j,length;
    char *output=new char[40];
    length=0;
    output[0] = '\0';
    if (input[0] == '\0')
        return output;
    while(input[length]!='\0')
        length++;
    
    // 0x30 -> 00110000
    // 0x3C -> 00111100
    // 0x3F -> 00111111
    
    // 11111111 00000000 11111111
    // 111111 110000 000011 111111
    i = 0;
    j = 0;
    while (i <= length-3) {
        output[j++] = base64_index[( input[i] >> 2 ) & 0x3F];
        output[j++] = base64_index[( (input[i] << 4) & 0x30 ) | ( input[i+1] >> 4 )];
        output[j++] = base64_index[( (input[i+1] << 2) & 0x3C ) | ( input[i+2] >> 6 )];
        output[j++] = base64_index[input[i+2] & 0x3F];
        i += 3;
    }
    
    if (length - i > 0) {
        output[j++] = base64_index[( input[i] >> 2 ) & 0x3F];
        if (length - i  == 2) {
            output[j++] = base64_index[( (input[i] << 4) & 0x30 ) | ( input[i+1] >> 4 )];
            output[j++] = base64_index[(input[i+1] << 2) & 0x3C];
            output[j++] = '=';
        } else if (length - i  == 1) {
            output[j++] = base64_index[(input[i] << 4) & 0x30];
            output[j++] = '=';
            output[j++] = '=';
        }
    }
    
    output[j++] = '\0';
    return output;
}

char GetCharIndex(char c) //内联函数可以省去函数调用过程，提速
{   if((c >= 'A') && (c <= 'Z'))
    return c - 'A';
else if((c >= 'a') && (c <= 'z'))
    return c - 'a' + 26;
else if((c >= '0') && (c <= '9'))
    return c - '0' + 52;
else if(c == '+')
    return 62;
else if(c == '/')
    return 63;
else if(c == '=')
    return 0;
    return 0;
}

char charToHex(char c)
{
    if (c>='0' && c<='9') {
        return c-'0';
    }
    else if (c>='A' && c<='Z') {
        return c-'A'+10;
    }
    else if (c>='a' && c<='z') {
        return c-'a'+10;
    }
    return 0;
}

char *quoted_printable_decode(const char *lpSrc, unsigned long len)
{
    char *lpDes=new char[len];
    unsigned long sLen = 0;
    unsigned long dLen = 0;
    while(dLen <= len) {
        if (lpSrc[sLen] != '=') {
            lpDes[dLen++] = lpSrc[sLen++];
        }
        else if (lpSrc[sLen+1]=='\r' && lpSrc[sLen+2]=='\n') {
            sLen++;
            lpDes[dLen++] = lpSrc[sLen++];
            lpDes[dLen++] = lpSrc[sLen++];
        }
        else{
            lpDes[dLen++] = (charToHex(lpSrc[sLen+1])<<4) + charToHex(lpSrc[sLen+2]);
            sLen += 3;
        }
    }
    return lpDes;
}
char *base64_decode(const char *lpSrc, unsigned long sLen)   //解码函数
{   static char lpCode[4];
    char *lpString=new char[sLen/4*3+1];
    int vLen = 0;
    if(sLen % 4)        //Base64编码长度必定是4的倍数，包括'='
    {   lpString[0] = '\0';
        return lpString;
    }
    while(sLen > 2)      //不足三个字符，忽略
    {   lpCode[0] = GetCharIndex(lpSrc[0]);
        lpCode[1] = GetCharIndex(lpSrc[1]);
        lpCode[2] = GetCharIndex(lpSrc[2]);
        lpCode[3] = GetCharIndex(lpSrc[3]);
        
        lpString[vLen++] = (lpCode[0] << 2) | (lpCode[1] >> 4);
        lpString[vLen++] = (lpCode[1] << 4) | (lpCode[2] >> 2);
        lpString[vLen++] = (lpCode[2] << 6) | (lpCode[3]);
        
        lpSrc += 4;
        sLen -= 4;
    }
    return lpString;
}

void codingConvert(char *inbuf,size_t inlen,char *outbuf,size_t outlen, const char *from_charset, const char *to_charset) {
    char **pin = &inbuf;
    char **pout = &outbuf;
    size_t len;
    memset(outbuf,0,outlen);
    iconv_t cd = iconv_open(to_charset, from_charset);
    if (cd==0) return ;
    len = iconv(cd,pin,(size_t *)&inlen,pout,(size_t *)&outlen);
    iconv_close(cd);
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
