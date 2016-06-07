//
//  Transcoding.h
//  MailSystem
//
//  Created by Meteor on 16/5/30.
//  Copyright © 2016年 MeteorKL. All rights reserved.
//

#ifndef Transcoding_h
#define Transcoding_h

#include <iconv.h>
#include <stdio.h>
#include <iostream>

    // Base64加密
    // 返回密文
    // pcInput: 原文
    char *pcfBase64Encode(const char *pcInput);

    // Base64解密
    // 返回解密是否成功
    // pcDes: 原文
    // pcSrc: 密文
    // ulLen: 密文长度
    bool bfBase64Decode(char *pcDes, const char *pcSrc, size_t ulLen);

    // Quoted Printable解密
    // 返回原文
    // pcSrc: 密文
    // ulLen: 密文长度
    unsigned char *pcfQuotedPrintableDecode(const char *pcSrc, size_t ulLen);

    // 中文字符编码转换
    // 返回编码转换是否成功
    // pcInBuf: 转换前的字符串
    // ulInLen: 转换前的字符串长度
    // pcOutBuf: 转换后的字符串
    // ulOutLen: 转换后的字符串长度
    // pcFromCharset: 转换前的编码
    // pcToCharset: 转换后的编码
    bool bfCodingConvert(char *pcInBuf,size_t ulInLen,char *pcOutBuf,size_t ulOutLen, const char *pcFromCharset, const char *pcToCharset);

    // 整数转化为字符串
    // 返回整数位数
    // lVal: 整数
    // pcBuf: 字符串
    size_t ulfItoa(long lVal, char* pcBuf);

#endif /* Transcoding_h */
