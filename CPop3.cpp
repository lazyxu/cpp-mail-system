//
//  CPop3
//  MailSystem
//
//  Created by Meteor on 16/5/9.
//  Copyright © 2016年 MeteorKL. All rights reserved.
//

#include "CPop3.h"

bool CPop3::bfLoginPop3()
{
    if (bIsDebug) cout<< strPop3.c_str();
    int16_t sPop3Port = 110;//pop3协议专用端口
    
    // 连接服务器
    if(sockReceiveMail.Connect(strPop3.c_str(), sPop3Port) == false)
        return false;
    sockReceiveMail.recv_socket();
    if (bIsDebug) cout << "Client : connected! \nServer:"
                        << sockReceiveMail.get_recvbuf() << endl;
    
    // 发送用户名
    sockReceiveMail.send_socket(("user " + this->strMailAddress + "\r\n").c_str());//输入邮箱用户名
    sockReceiveMail.recv_socket();
    if (bIsDebug) cout << "Client : send name \nServer:"
                        << sockReceiveMail.get_recvbuf() << endl;
    
    // 发送密码
    sockReceiveMail.send_socket(("pass " + this->strMailPassword + "\r\n").c_str());//邮箱密码
    sockReceiveMail.recv_socket();
    if (bIsDebug) cout << "Client : send password \n Server ："
                        << sockReceiveMail.get_recvbuf() << endl;
    
    return true;
}

// 获取字符串pcTemp第ulTempIndex个字符后面的第一个数字
// 返回数字
// pcTemp: 输入字符串
// ulTempIndex: 字符串下标
size_t ulfGetLong(char *pcTemp, size_t &ulTempIndex)
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

// 返回邮件数量
// pcTemp: 输入字符串
size_t ulfGetMailNum(char *pcTemp)
{
    size_t ulIndex = 0;
    size_t ulNum;
    ulNum = ulfGetLong(pcTemp, ulIndex);
    return ulNum;
}

// 从接收到的list中获取邮件大小数组
// pcTemp: 输入字符串
// pulMailSize: 邮件大小数组
// ulMailNum: 邮件数量
void ulfListToArray(char *pcTemp, size_t *pulMailSize, size_t ulMailNum)
{
    size_t ulStart = 0;
    size_t ulIndex;
    size_t ulMailIndex;
    ulStart = string(pcTemp).find("\r\n")+2;
    for (ulIndex=0; ulIndex<ulMailNum; ulIndex++) {
        ulMailIndex = ulfGetLong(pcTemp, ulStart) - 1;
        pulMailSize[ulMailIndex] = ulfGetLong(pcTemp, ulStart);
    }
}

// 过滤莫名其妙出现的字符，例如0x03，0x0a
// 返回过滤后的字符串
// strTemp: 输入字符串
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

// 分析简单的数据
// 返回分析是否成功
// strTemp: 解析后的字符串
// strMail: 接收到的内容
// strClass: 搜索xxx字符串
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
        bfBase64Decode(acTemp, strTemp.c_str(), strTemp.length());
        strTemp = acTemp;
        strFromCharset = strfSkipIllegal(strFromCharset);
        if (strFromCharset.compare("UTF-8") != 0) {
            char *temp1 = new char[strTemp.length()*2];
            memset(temp1, 0, strTemp.length()*2);
            bfCodingConvert((char *)strTemp.c_str(), strTemp.length(), temp1, strTemp.length()*2, strFromCharset.c_str(), "utf-8");
            strTemp = temp1;
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

// 获取邮件信息
// mailRev: 邮件类
// strMail: 收到的信息
// ulSize: 邮件大小
void vGetMailInfo(CMail &mailRev, string strMail, size_t ulSize)
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
                bfBase64Decode(acTemp, strContent.c_str(), strContent.length());
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
        if (strFromCharset.compare("utf-8")!=0) {
            char *temp1 = new char[strContent.length()*2];
            memset(temp1, 0, strContent.length()*2);
            bfCodingConvert((char *)strContent.c_str(), strContent.length(), temp1, strContent.length()*2, strFromCharset.c_str(), "utf-8");
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
    
    mailRev.vSetMail(strFrom, strTo, strTitle, strContent, strDate, type, ulSize);
}

CMail *CPop3::pmailfReceiveMail(size_t &ulRevMailNum)
{
    // 获取邮件列表
    sockReceiveMail.send_socket("list\r\n");
    sockReceiveMail.recv_socket();
    const char *pcRecv = sockReceiveMail.get_recvbuf();
    if (bIsDebug) cout << "Client : send list \nServer :"  << pcRecv << endl;
    
    // 获取邮件数量，每个邮件的大小，初始化邮件类指针
    ulRevMailNum = ulfGetMailNum((char *)pcRecv);
    size_t *ulRevMailSize = new size_t[ulRevMailNum]; // 每个邮件的大小
    ulfListToArray((char *)pcRecv, ulRevMailSize, ulRevMailNum);
    CMail *pmailRev = new CMail[ulRevMailNum]; // 邮件类指针
    
    size_t ulRev;  // 已接收到的字节数
    char acIndex[10]; // 邮件下标（转化为字符串）
    for (int32_t lIndex=0; lIndex<(int32_t)ulRevMailNum; lIndex++)
    {
        ulfItoa(lIndex+1, acIndex); // 数字转化为字符串
        
        // 读取第 lIndex 封邮件
        sockReceiveMail.send_socket(((string)"retr "+(string)acIndex+(string)"\r\n").c_str());
        sockReceiveMail.recvline_socket();
        if (bIsDebug) cout << "---------------------------------------------------------------------------"
            << ((string)"retr "+(string)acIndex+(string)"\r\n").c_str();
        if (bIsDebug) cout << "Client : " << ((string)"retr "+(string)acIndex+(string)"\r\n").c_str() <<
            "Server :" << sockReceiveMail.get_recvbuf()  << endl;
        
        // 读取第 lIndex 封邮件
        ulRev = 0;
        long lRetSize = ulRevMailSize[lIndex] + 3;
        string strRevMailContent = "";
        //cout << "[" << ulLen << "/" << ulRevMailSize[lIndex] + 3 << "]" ;
        while (lRetSize>0) {
            long lTemp = sockReceiveMail.recv_socket();
            if (lTemp > 0)
            {
                ulRev += lTemp;
                lRetSize -= lTemp;
            }
            else
                break;
            //cout << "->[" << ulLen << "/" << ulRevMailSize[lIndex] + 3 << "]" ;
            strRevMailContent += sockReceiveMail.get_recvbuf();
            //if (bIsDebug) cout << recv << endl;
        }
        
        // 分析邮件内容，提取出发件人，收件人，标题，正文等
        if (bIsDebug) cout << strRevMailContent << endl;
        vGetMailInfo(pmailRev[lIndex], strRevMailContent, ulRevMailSize[lIndex] + 3);
        if (bIsDebug) cout << "mail " << lIndex+1 << ":" << endl;
        if (bIsDebug) pmailRev[lIndex].vShowMail();
    }
    delete[] ulRevMailSize;
    
    // 断开和服务器的连接
    sockReceiveMail.send_socket("quit\r\n");
    sockReceiveMail.recv_socket();
    if (bIsDebug) cout << "Client : send quit \nServer :"
        << sockReceiveMail.get_recvbuf() << endl;
    
    return pmailRev;
}
