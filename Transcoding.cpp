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
