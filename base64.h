/*
 * base64.h
 *
 *  Created on: 2016年5月9日
 *      Author: Meteor
 */

#ifndef BASE64_H_
#define BASE64_H_

char *base64_encode(const char *input);
char *base64_decode(const char *lpSrc, unsigned long sLen);
char *quoted_printable_decode(const char *lpSrc, unsigned long sLen);

#endif /* BASE64_H_ */
