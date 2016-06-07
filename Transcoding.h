//
//  Transcoding.hpp
//  testcpp
//
//  Created by Meteor on 16/5/30.
//  Copyright © 2016年 meteor. All rights reserved.
//

#ifndef Transcoding_hpp
#define Transcoding_hpp
#include <iconv.h>
#include <stdio.h>
#include <iostream>

char *pcfBase64Encode(const char *input);
bool pcfBase64Decode(char *pcDes, const char *pcSrc, size_t ulLen);
unsigned char *pcfQuotedPrintableDecode(const char *lpSrc, unsigned long len);
bool bfCodingConvert(char *inbuf,size_t inlen,char *outbuf,size_t outlen, const char *from_charset, const char *to_charset);
size_t ulItoa(int val, char* buf);

#endif /* Transcoding_hpp */
