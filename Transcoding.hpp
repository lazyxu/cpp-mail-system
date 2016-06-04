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

char *base64_encode(const char *input);
char *base64_decode(const char *lpSrc, unsigned long sLen);
char *quoted_printable_decode(const char *lpSrc, unsigned long sLen);
void codingConvert(char *inbuf,size_t inlen,char *outbuf,size_t outlen, const char *from_charset, const char *to_charset);

#endif /* Transcoding_hpp */
