/*  pop3.cpp
 *
 *  Created on: 2016年5月9日
 *      Author: Meteor
 */

#include "pop3.h"

bool pop3::bfLoginPop3(bool bIsDebug)
{
    if ( bIsDebug ) std::cout<< strPop3.c_str();
    int16_t sPop3Port = 110;//pop3协议专用端口
    if(sockReceiveMail.Connect(strPop3.c_str(), sPop3Port) == false)
        return false;
    if (bIsDebug) std::cout << "connected\n";
    sockReceiveMail.recv_socket();
    if (bIsDebug) std::cout << "Client:connect successfully! \nServer:"
        << sockReceiveMail.get_recvbuf() << std::endl;
    
    sockReceiveMail.send_socket(("user " + this->strMailAddress + "\r\n").c_str());//输入邮箱用户名
    sockReceiveMail.recv_socket();
    if (bIsDebug) std::cout << "Client : send name \nServer:"
        << sockReceiveMail.get_recvbuf() << std::endl;
    
    sockReceiveMail.send_socket(("pass " + this->strMailPassword + "\r\n").c_str());//邮箱密码
    sockReceiveMail.recv_socket();
    if (bIsDebug) std::cout << "Client : send password \n Server ："
        << sockReceiveMail.get_recvbuf() << std::endl;
    return true;
}

size_t get_long(char *pcTemp, size_t &ulTempIndex)
{
    size_t ulIndex = 0;
    while (!(pcTemp[ulTempIndex]>='0'&&pcTemp[ulTempIndex]<='9')) {
        ulTempIndex++;
    }
    while (pcTemp[ulTempIndex]>='0'&&pcTemp[ulTempIndex]<='9') {
        ulIndex *= 10;
        ulIndex += pcTemp[ulTempIndex]-'0';
        ulTempIndex++;
    }
    return ulIndex;
}

size_t *list_to_array(char *pcTemp, size_t &ulTempIndex)
{
    size_t ulIndex1 = 0;
    size_t ulIndex2;
    size_t *pulMailSize, ulMailSize;
    ulTempIndex = get_long(pcTemp, ulIndex1);
    printf("n:%ld i:%lu ", ulTempIndex, ulIndex1);
    pulMailSize = (size_t *)malloc(sizeof(size_t)*(ulTempIndex+1));
    pulMailSize[0] = get_long(pcTemp, ulIndex1);
    for (ulIndex2=0; ulIndex2<ulTempIndex; ulIndex2++) {
        ulMailSize = get_long(pcTemp, ulIndex1);
        pulMailSize[ulMailSize] = get_long(pcTemp, ulIndex1);
        printf("n:%ld \n", pulMailSize[ulMailSize]);
    }
    return pulMailSize;
}

string strfSkipIllegal(string strTemp)
{
    size_t ulIndex, ulRet = 0;
    for (ulIndex=0; ulIndex<strTemp.length(); ulIndex++) {
        if (strTemp[ulIndex]==0x03 || strTemp[ulIndex]==0x0a) {
            strTemp.resize(strTemp.length()-1);
            continue;
        }
        strTemp[ulRet++] = strTemp[ulIndex];
    }
    strTemp[ulRet] = 0;
    return strTemp;
}

bool bfLineData(string &strTemp, string strMail, string strClass)
{
    size_t ulStart, ulEnd, ulTemp;
    string strFromCharset;
    char acTemp[100000];
    ulStart = strMail.find(strClass, 0);
    if (ulStart==(size_t)-1)
        return false;
    ulStart += strClass.length();
    strTemp = "";
    ulEnd = strMail.find("\r\n", ulStart);
    ulTemp = strMail.find("=?", ulStart);
    if ( ulTemp != (size_t)-1 && ulTemp < ulEnd) {
        ulStart = ulTemp + 2;
        ulTemp = strMail.find("?B?", ulStart);
        strFromCharset = strMail.substr(ulStart, ulTemp-ulStart);
        ulStart = ulTemp+3;
        ulTemp = strMail.find("?=", ulStart);
        strTemp = strMail.substr(ulStart, ulTemp-ulStart);
        pcfBase64Decode(acTemp, strTemp.c_str(), strTemp.length());
        strTemp = acTemp;
        strFromCharset = strfSkipIllegal(strFromCharset);
        if (strFromCharset.compare("UTF-8") != 0) {
            char *temp = (char *)malloc(sizeof(char)*strTemp.length());
            memset(temp, 0, strTemp.length());
            strcpy(temp, strTemp.c_str());
            char *temp1 = (char *)malloc(sizeof(char)*strTemp.length()*2);
            memset(temp1, 0, strTemp.length()*2);
            bfCodingConvert(temp, strlen(temp), temp1, strTemp.length()*2, strFromCharset.c_str(), "utf-8");
            strTemp = temp1;
            //            string strOut;
            //            strOut.resize(strTemp.length()*2+1, 0);
            //            bfCodingConvert((char *)strTemp.c_str(), strTemp.length(), (char *)strOut.c_str(), strOut.length(), strFromCharset.c_str(), "utf-8");
            //            strTemp = strOut;
        }
        ulStart = strMail.find("<", ulStart);
        if (ulStart > ulEnd) {
            return true;
        }
        strTemp += " ";
    }
    strTemp += strMail.substr(ulStart, ulEnd-ulStart);
    return true;
}

void getMailInfo(mail &mailRev, string strMail, size_t ulSize)
{
    size_t ulStart = 0, ulEnd;
    string strFrom, strTo, strTitle, strContent, strDate, strFromCharset = "utf-8", strContentTransferEncoding;
    char acTemp[100000];
    bfLineData(strFrom, strMail, "From: ");
    bfLineData(strTo, strMail, "To: ");
    bfLineData(strDate, strMail, "Date: ");
    bfLineData(strTitle, strMail, "Subject: ");
    
    bool flag = false;
    string type;
    if ((ulEnd=strMail.find("Content-Type: text/plain;", 0))!=(size_t)-1) {
        ulStart = ulEnd + 25;
        flag = true;
        type = "text/plain";
    }
    else if ((ulEnd=strMail.find("Content-Type: text/html;", 0))!=(size_t)-1) {
        ulStart = ulEnd + 24;
        flag = true;
        type = "text/html";
    }
    if ((ulEnd=strMail.find("Content-Transfer-Encoding: 8bit", 0))!=(size_t)-1) {
        if ((ulEnd=strMail.find("\r\n\r\n", ulEnd))!=(size_t)-1) {
            ulStart = ulEnd + 4;
            ulEnd = strMail.find("\r\n.\r\n", ulStart);
            strContent = strMail.substr(ulStart, ulEnd-ulStart);
            strContent = strfSkipIllegal(strContent);
        }
    }
    else if (flag == true) {
        if ((ulEnd=strMail.find("charset=\"", ulStart))!=(size_t)-1) {
            ulStart = ulEnd + 9;
            ulEnd = strMail.find("\"\r\n", ulStart);
            strFromCharset = strMail.substr(ulStart, ulEnd-ulStart);
            strFromCharset = strfSkipIllegal(strFromCharset);
        }
        else if ((ulEnd=strMail.find("charset=", ulStart))!=(size_t)-1) {
            ulStart = ulEnd + 8;
            ulEnd = strMail.find("\r\n", ulStart);
            strFromCharset = strMail.substr(ulStart, ulEnd-ulStart);
            strFromCharset = strfSkipIllegal(strFromCharset);
        }
        if ((ulEnd=strMail.find("Content-Transfer-Encoding: ", ulStart))!=(size_t)-1) {
            ulStart = ulEnd + 27;
            ulEnd = strMail.find("\r\n", ulStart);
            strContentTransferEncoding = strMail.substr(ulStart, ulEnd-ulStart);
            strContentTransferEncoding = strfSkipIllegal(strContentTransferEncoding);
            
            if (strcmp(strContentTransferEncoding.c_str(), "base64")==0) {//base64
                ulStart = strMail.find("\r\n\r\n", ulStart);
                ulStart += 4;
                ulEnd = strMail.find("\r\n", ulStart);
                strContent = strMail.substr(ulStart, ulEnd-ulStart);
                strContent = strfSkipIllegal(strContent);
                pcfBase64Decode(acTemp, strContent.c_str(), strContent.length());
                strContent = acTemp;
            }
            else if (strContentTransferEncoding.compare("quoted-printable")==0) {
                ulStart = strMail.find("\r\n\r\n", ulStart);
                ulStart += 4;
                ulEnd = strMail.find("\r\n.\r\n", ulStart);
                strContent = strMail.substr(ulStart, ulEnd-ulStart);
                strContent = string((char *)pcfQuotedPrintableDecode(strContent.c_str(), strContent.length()));
            }
        }
        //        if ((ulEnd=strMail.find("Content-Transfer-Encoding: base64", ulStart))!=(size_t)-1) {
        //            ulStart = ulEnd + 33;
        //            ulStart = strMail.find("\r\n\r\n", ulStart);
        //            ulStart += 4;
        //            ulEnd = strMail.find("\r\n", ulStart);
        //            strContent = strMail.substr(ulStart, ulEnd-ulStart);
        //            pcfBase64Decode(acTemp, strContent.c_str(), strContent.length());
        //            strContent = acTemp;
        //        }
        //        else if ((ulEnd=strMail.find("Content-Transfer-Encoding: base64", ulStart))!=(size_t)-1) {
        //            ulStart = ulEnd + 33;
        //            ulStart = strMail.find("\r\n\r\n", ulStart);
        //            ulStart += 4;
        //            ulEnd = strMail.find("\r\n", ulStart);
        //            strContent = strMail.substr(ulStart, ulEnd-ulStart);
        //            pcfBase64Decode(acTemp, strContent.c_str(), strContent.length());
        //            strContent = acTemp;
        //        }
        //        else if ((ulEnd=strMail.find("Content-Transfer-Encoding: quoted-printable", ulStart))!=(size_t)-1) {
        //            ulStart = ulEnd + 33;
        //            ulStart = strMail.find("\r\n\r\n", ulStart);
        //            ulStart += 4;
        //            ulEnd = strMail.find("\r\n.\r\n", ulStart);
        //            strContent = strMail.substr(ulStart, ulEnd-ulStart);
        //            strContent = string((char *)pcfQuotedPrintableDecode(strContent.c_str(), strContent.length()));
        //        }
        
        if (strFromCharset.compare("utf-8")!=0) {
            char *temp = (char *)malloc(sizeof(char)*strContent.length());
            memset(temp, 0, strContent.length());
            strcpy(temp, strContent.c_str());
            char *temp1 = (char *)malloc(sizeof(char)*strContent.length()*2);
            memset(temp1, 0, strContent.length()*2);
            bfCodingConvert(temp, strlen(temp), temp1, strContent.length()*2, strFromCharset.c_str(), "utf-8");
            strContent = temp1;
        }
    }
    else {
        if ((ulEnd=strMail.find("\r\n\r\n", 0))!=(size_t)-1) {
            ulStart = ulEnd + 4;
            ulEnd = strMail.find("\r\n.\r\n", ulStart);
            strContent = strMail.substr(ulStart, ulEnd-ulStart);
            strContent = strfSkipIllegal(strContent);
        }
    }
    
    
    mailRev.setMail(strFrom, strTo, strTitle, strContent, strDate, type, ulSize);
}

mail *pop3::pmailReceiveMail(bool bIsDebug, size_t &ulIndex)
{
    sockReceiveMail.send_socket("stat\r\n");
    sockReceiveMail.recv_socket();
    if (bIsDebug) std::cout << "Client : send stat \nServer : "
        << sockReceiveMail.get_recvbuf() << std::endl;
    
    sockReceiveMail.send_socket("list\r\n");
    sockReceiveMail.recv_socket();
    const char *pcRecv = sockReceiveMail.get_recvbuf();
    if (bIsDebug) std::cout << "Client : send list \nServer :"  << pcRecv << std::endl;
    size_t *ulRevMailSize;
    ulRevMailSize = list_to_array((char *)pcRecv, ulIndex);
    //下面的while循环有些问题，目前还没有想到解决方法。以后改正！
    int32_t lIndex=1;
    //while (1)
    size_t ulLen;
    char acIndex[10];
    mail *pmailRev = new mail[ulIndex];
    for (lIndex=1; lIndex<=(int32_t)ulIndex; lIndex++)
    {
        ulItoa(lIndex, acIndex);
        //cIndex=itoa(lIndex);
        if (bIsDebug) std::cout << "---------------------------------------------------------------------------";
        if (bIsDebug) std::cout << ((string)"retr "+(string)acIndex+(string)"\r\n").c_str();
        sockReceiveMail.send_socket(((string)"retr "+(string)acIndex+(string)"\r\n").c_str());
        sockReceiveMail.recvline_socket();
        const char *recv = sockReceiveMail.get_recvbuf();
        if (bIsDebug) std::cout << "Client : " << ((string)"retr "+(string)acIndex+(string)"\r\n").c_str() <<
            "Server :" << recv  << endl;
        //        len = 0;
        //        while (len < mail_rev[i]) {
        //            //do{
        //            cout << "[" << len << "/" << mail_rev[i] << "]" ;
        //            len = len + sockReceiveMail.recv_socket();
        //            cout << "->[" << len << "/" << mail_rev[i] << "]" ;
        //            recv = sockReceiveMail.get_recvbuf();
        //            if (IsDebug) std::cout << recv << endl;
        //            //}while (!is_end(recv, len));
        //        }
        //        cout << "[" << len << "/" << mail_rev[i] << "]" ;
        
        ulLen = 0;
        size_t ulRevSize = ulRevMailSize[lIndex] + 3;
        string strRevMailContent = "";
        //cout << "[" << ulLen << "/" << ulRevMailSize[lIndex] + 3 << "]" ;
        while (ulRevSize>0) {
            size_t ulRet = sockReceiveMail.recv_socket();
            if (ulRet > 0)
            {
                ulLen += ulRet;
                ulRevSize -= ulRet;
            }
            else
                break;
            //cout << "->[" << ulLen << "/" << ulRevMailSize[lIndex] + 3 << "]" ;
            recv = sockReceiveMail.get_recvbuf();
            strRevMailContent += recv;
            //if (IsDebug) std::cout << recv << endl;
        }
        //if (IsDebug) std::cout << revMailContent << endl << "[" << len << "/" << mail_rev[i] + 3 << "]" << endl;
        getMailInfo(pmailRev[lIndex-1], strRevMailContent, ulRevMailSize[lIndex] + 3);
        cout << "mail " << lIndex << ":" << endl;
        pmailRev[lIndex-1].showMail();
    }
    
    sockReceiveMail.send_socket("quit\r\n");
    sockReceiveMail.recv_socket();
    if (bIsDebug) std::cout << "Client : send quit \nServer :"
        << sockReceiveMail.get_recvbuf() << std::endl;
    return pmailRev;
}
