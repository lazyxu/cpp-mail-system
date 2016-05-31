/*  CMail.cpp
 *
 *  Created on: 2016年5月9日
 *      Author: Meteor
 */

#include "CMail.h"

CMail::CMail(string smtp, string pop3, string address, string password)
{
	strSmtp = smtp;
	strPop3 = pop3;
	strMailAddress = address;
	strMailPassword = password;
}
bool CMail::LoginMail(bool IsDebug)
{
	if ( IsDebug ) std::cout<< strSmtp.c_str();
	int smtpPort = 25;//smtp协议专用端口
	if(sockSendMail.Connect(strSmtp.c_str(), smtpPort) == false)
		return false;
	sockSendMail.recv_socket();
	if ( IsDebug ) if ( IsDebug ) std::cout<< "Client : connected! \nServer :"
	<< sockSendMail.get_recvbuf() <<std::endl;

	/*EHLO指令是必须首先发的，相当于和服务器说hello*/
	sockSendMail.send_socket("EHLO hello\r\n");//hello可以被替换为其它字符串
	sockSendMail.recv_socket();
	if ( IsDebug ) std::cout<< "Client : send helo \nServer :"
	<<sockSendMail.get_recvbuf() << std::endl;

	/*发送 auth login 指令，告诉服务器要登录邮箱*/
	sockSendMail.send_socket("auth login\r\n");
	sockSendMail.recv_socket();
	if ( IsDebug ) std::cout<< "Client : send auth login \nServer :"
	<<sockSendMail.get_recvbuf() << std::endl;

	/*告诉服务器要登录后，接着就是把用户名发过去了.
	 不过这个用户名是经过了base64编码的，smtp也支持
	 明文传送，至于具体有什么区别上网上找资料看看就知道了*/
	if ( IsDebug ) std::cout<< base64_encode(strMailAddress.c_str());
	sockSendMail.send_socket(base64_encode(strMailAddress.c_str()));//经过base64编码后的邮箱用户名
	sockSendMail.send_socket("\r\n");
	sockSendMail.recv_socket();
	if ( IsDebug ) std::cout<< "Client : send name \nServer :"
	<<sockSendMail.get_recvbuf() << std::endl;

	/*用户名发过去后接着就是用户密码了，当然也是经过base64编码后的*/
	if ( IsDebug ) std::cout<< base64_encode(strMailPassword.c_str());
	sockSendMail.send_socket(base64_encode(strMailPassword.c_str()));// 授权码 "cTEwNTE4MTQzNTM="
	sockSendMail.send_socket("\r\n");
	sockSendMail.recv_socket();
	if ( IsDebug ) std::cout<< "Client : send password \nServer :"
	<<sockSendMail.get_recvbuf() << std::endl;



	if ( IsDebug ) std::cout<< strPop3.c_str();
	int pop3Port = 110;//pop3协议专用端口
	if(sockReceiveMail.Connect(strPop3.c_str(), pop3Port) == false)
		return false;
	std::cout << "connected\n";
	sockReceiveMail.recv_socket();
	std::cout << "Client:connect successfully! \nServer:"
		<< sockReceiveMail.get_recvbuf() << std::endl;

	sockReceiveMail.send_socket("user q1051814353@163.com\r\n");//输入邮箱用户名
	sockReceiveMail.recv_socket();
	std::cout << "Client : send name \nServer:"
	   << sockReceiveMail.get_recvbuf() << std::endl;

	sockReceiveMail.send_socket("pass q1051814353\r\n");//邮箱密码
	sockReceiveMail.recv_socket();
	std::cout << "Client : send password \n Server ："
		<< sockReceiveMail.get_recvbuf() << std::endl;
	return true;
}

bool CMail::SendMail(string strFromName, string strToMailAddress, string strTitle, string strContent, bool IsDebug)
{
	/*发送 mail from 指令，相当于填写发件人*/
    sockSendMail.send_socket(( string("MAIL FROM: <")+strMailAddress+string(">") ).c_str());
    sockSendMail.send_socket("\r\n");
    sockSendMail.recv_socket();
    if ( IsDebug ) std::cout<< "Client: send mail from \nServer :"
    <<sockSendMail.get_recvbuf() << std::endl;

    /*发送 rcpt to 指令，就是填写收件人了 */
    sockSendMail.send_socket(( string("RCPT TO: <")+strToMailAddress+string(">") ).c_str());
    sockSendMail.send_socket("\r\n");
    sockSendMail.recv_socket();
    if ( IsDebug ) std::cout<< "Client : send rcpt to \nServer"
    <<sockSendMail.get_recvbuf() << std::endl;

    /*发送data,标志着后面开始发送邮件的主题部分*/
    sockSendMail.send_socket("data\r\n");
    sockSendMail.recv_socket();
    if ( IsDebug ) std::cout<< "Client : send data \nServer :"
    <<sockSendMail.get_recvbuf() << std::endl;
    /*发送邮件主体部分，先是邮件主题（subject）,后面是邮件内容。
     下面就是发送主体的格式*/
    sockSendMail.send_socket(( string("From: ")+strFromName+string("\r\n") ).c_str());
    sockSendMail.send_socket(( string("To: ")+strToMailAddress+string("\r\n") ).c_str());
    sockSendMail.send_socket(( string("Subject: ")+strTitle+string("\r\n\r\n") ).c_str());
    sockSendMail.send_socket(( strContent+string("\r\n \r\n") ).c_str());
    sockSendMail.send_socket(".\r\n");
    sockSendMail.recv_socket();
    if ( IsDebug ) std::cout<< "Client : send content \nServer :"
    << sockSendMail.get_recvbuf() <<std::endl;

    sockSendMail.send_socket("quit\r\n");
    sockSendMail.recv_socket();
    if ( IsDebug ) std::cout<< "Client : send quit \nServer :"
    << sockSendMail.get_recvbuf() <<std::endl;
    return true;
}

char *reverse(char *s)
{
    char temp;
    char *p = s;    //p指向s的头部
    char *q = s;    //q指向s的尾部
    while(*q)
        ++q;
    q--;

    //交换移动指针，直到p和q交叉
    while(q > p)
    {
        temp = *p;
        *p++ = *q;
        *q-- = temp;
    }
    return s;
}

/*
 * 功能：整数转换为字符串
 * char s[] 的作用是存储整数的每一位
 */
char *itoa(int n)
{
    int i = 0,isNegative = 0;
    static char s[100];      //必须为static变量，或者是全局变量
    if((isNegative = n) < 0) //如果是负数，先转为正数
    {
        n = -n;
    }
    do      //从各位开始变为字符，直到最高位，最后应该反转
    {
        s[i++] = n%10 + '0';
        n = n/10;
    }while(n > 0);

    if(isNegative < 0)   //如果是负数，补上负号
    {
        s[i++] = '-';
    }
    s[i] = '\0';    //最后加上字符串结束符
    return reverse(s);
}

bool is_ok(const char *str)
{
    if (*str=='+' && *(str+1)=='O' && *(str+2)=='K' && *(str+3)==' ') {
        return 1;
    }
    return 0;
}

bool is_end(const char *str, long len)
{
    char tempstr[]="\r\n.\r\n";
    long i =len-1;
    long j=i>=4?4:i;
    if (BUFSIZ == len) {
        return 0;
    }
    while(str[i]==tempstr[j]){
        if (j==0) {
            return 1;
        }
        i--;
        j--;
    }
    return 0;
}

long get_long(char *str, int &i)
{
    long n = 0;
    while (!(str[i]>='0'&&str[i]<='9')) {
        i++;
    }
    while (str[i]>='0'&&str[i]<='9') {
        n *= 10;
        n += str[i]-'0';
        i++;
    }
    return n;
}

long *list_to_array(char *str, long &n)
{
    int i = 0, j;
    long *mail_size, index;
    n = get_long(str, i);
    printf("n:%ld i:%d ", n, i);
    mail_size = (long *)malloc(sizeof(long)*(n+1));
    mail_size[0] = get_long(str, i);
    for (j=0; j<n; j++) {
        index = get_long(str, i);
        mail_size[index] = get_long(str, i);
        printf("n:%ld \n", mail_size[index]);
    }
    return mail_size;
}

void getMailInfo(mail &revMail, string revMailContent, long size)
{
    size_t start, end;
    string from, to, title, content, Date;
    char from_charset[10]="utf-8";
    start = revMailContent.find("From: ", 0);
    if (start!=-1) {
        start += 6;
        from = "";
        if ((end=revMailContent.find("=\?UTF-8\?B\?", start))!=-1) {
            start = end + 10;
            end = revMailContent.find("\?=", start);
            from = revMailContent.substr(start, end-start);
            from = base64_decode(from.c_str(), from.length());
            start = revMailContent.find("<", start);
            from += " ";
        }
        else if ((end=revMailContent.find("=\?gb18030\?B\?", start))!=-1) {
            start = end + 13;
            end = revMailContent.find("\?=", start);
            from = revMailContent.substr(start, end-start);
            from = base64_decode(from.c_str(), from.length());
            start = revMailContent.find("<", start);
            from += " ";
        }
        end = revMailContent.find("\r\n", start);
        from += revMailContent.substr(start, end-start);
    }
    
    start = revMailContent.find("To: ", 0);
    if (start!=-1) {
        start += 4;
        to = "";
        if ((end=revMailContent.find("=\?UTF-8\?B\?", start))!=-1) {
            start = end + 10;
            end = revMailContent.find("\?=", start);
            to = revMailContent.substr(start, end-start);
            to = base64_decode(to.c_str(), to.length());
            start = revMailContent.find("<", start);
            to += " ";
        }
        else if ((end=revMailContent.find("=\?gb18030\?B\?", start))!=-1) {
            start = end + 12;            //=?gb18030?B?
            end = revMailContent.find("\?=", start);
            to = revMailContent.substr(start, end-start);
            to = base64_decode(to.c_str(), to.length());
            start = revMailContent.find("<", start);
            to += " ";
        }
        end = revMailContent.find("\r\n", start);
        to += revMailContent.substr(start, end-start);
    }
    
    start = revMailContent.find("Date: ", 0);
    if (start!=-1) {
        end = revMailContent.find("\r\n", start);
        Date = revMailContent.substr(start+6, end-start-6);
    }
    
    bool flag = false;
    if ((end=revMailContent.find("Content-Type: text/plain;", 0))!=-1) {
        start = end + 25;
        flag = true;
    }
    else if ((end=revMailContent.find("Content-Type: text/html;", 0))!=-1) {
        start = end + 24;
        flag = true;
    }
    if (flag == true) {
        if ((end=revMailContent.find("charset=GBK", start))!=-1) {
            start = end + 11;
            from_charset[0]=0;
            strcpy(from_charset,"gbk");
        }
        else if ((end=revMailContent.find("charset=\"gb18030\"", start))!=-1) {
            start = end + 17;
            from_charset[0]=0;
            strcpy(from_charset,"gb18030");
        }
        if ((end=revMailContent.find("Content-Transfer-Encoding: base64", start))!=-1) {
            start = end + 33;
            start = revMailContent.find("\r\n\r\n", start);
            start += 4;
            end = revMailContent.find("\r\n", start);
            content = revMailContent.substr(start, end-start);
            content = base64_decode(content.c_str(), content.length());
        }
        else if ((end=revMailContent.find("Content-Transfer-Encoding: base64", start))!=-1) {
            start = end + 33;
            start = revMailContent.find("\r\n\r\n", start);
            start += 4;
            end = revMailContent.find("\r\n", start);
            content = revMailContent.substr(start, end-start);
            content = base64_decode(content.c_str(), content.length());
        }
        else if ((end=revMailContent.find("Content-Transfer-Encoding: quoted-printable", start))!=-1) {
            start = end + 33;
            start = revMailContent.find("\r\n\r\n", start);
            start += 4;
            end = revMailContent.find("\r\n.\r\n", start);
            content = revMailContent.substr(start, end-start);
            content = string(quoted_printable_decode(content.c_str(), content.length()));
        }
        
        if (strcmp(from_charset, "utf-8")!=0) {
            char *temp = (char *)malloc(sizeof(char)*content.length());
            strcpy(temp, content.c_str());
            char *temp1 = (char *)malloc(sizeof(char)*content.length()*2);
            codingConvert(temp, strlen(temp), temp1, content.length()*2, from_charset, "utf-8");
            content = temp1;
            content += "转码似乎有点问题，暂时解决不了orz";
        }
    }
    else {
        
    }
    
    start = revMailContent.find("Subject: ", 0);
    if (start!=-1) {
        start += 9;
        if ((end=revMailContent.find("=\?GBK\?B\?", start))!=-1) {
            start = end + 8;
            end = revMailContent.find("\?=", start);
            title = revMailContent.substr(start, end-start);
            title = base64_decode(title.c_str(), title.length());
            char *temp = (char *)malloc(sizeof(char)*title.length());
            strcpy(temp, title.c_str());
            char *temp1 = (char *)malloc(sizeof(char)*title.length()/2*3);
            codingConvert(temp, strlen(temp), temp1, title.length()/2*3, "gb18030", "utf-8");
            title = temp1;
            
        }
        else if ((end=revMailContent.find("=\?gb18030\?B\?", start))!=-1) {
            start = end + 12;
            end = revMailContent.find("\?=", start);
            title = revMailContent.substr(start, end-start);
            title = base64_decode(title.c_str(), title.length());
            char *temp = (char *)malloc(sizeof(char)*title.length());
            strcpy(temp, title.c_str());
            char *temp1 = (char *)malloc(sizeof(char)*title.length()/2*3);
            codingConvert(temp, strlen(temp), temp1, title.length()/2*3, "gb18030", "utf-8");
            title = temp1;
        }
        else {
            end = revMailContent.find("\r\n", start);
            title = revMailContent.substr(start, end-start);
        }
    }
    
    revMail.setMail(from, to, title, content, Date, size);
}

bool CMail::ReceiveMail(bool IsDebug)
{
	sockReceiveMail.send_socket("stat\r\n");
    sockReceiveMail.recv_socket();
    std::cout << "Client : send stat \nServer : "
        << sockReceiveMail.get_recvbuf() << std::endl;

    sockReceiveMail.send_socket("list\r\n");
    sockReceiveMail.recv_socket();
    const char *recv = sockReceiveMail.get_recvbuf();
    std::cout << "Client : send list \nServer :"  << recv << std::endl;
    long n = 0;
    long *mail_rev;
    mail_rev = list_to_array((char *)recv, n);
          //下面的while循环有些问题，目前还没有想到解决方法。以后改正！
    int i=1;
    //while (1)
    long len;
    char *stri=new char[4];
    mail *revMail = new mail[n];
    for (i=1; i<=n; i++)
    {
    	stri=itoa(i);
    	std::cout << "---------------------------------------------------------------------------";
    	std::cout << ((string)"retr "+(string)stri+(string)"\r\n").c_str();
    	sockReceiveMail.send_socket(((string)"retr "+(string)stri+(string)"\r\n").c_str());
        sockReceiveMail.recv_socket();
        const char *recv = sockReceiveMail.get_recvbuf();
    	std::cout << "Client : " << ((string)"retr "+(string)stri+(string)"\r\n").c_str() <<
                "Server :" << recv  << endl;
//        len = 0;
//        while (len < mail_rev[i]) {
//            //do{
//            cout << "[" << len << "/" << mail_rev[i] << "]" ;
//            len = len + sockReceiveMail.recv_socket();
//            cout << "->[" << len << "/" << mail_rev[i] << "]" ;
//            recv = sockReceiveMail.get_recvbuf();
//            std::cout << recv << endl;
//            //}while (!is_end(recv, len));
//        }
//        cout << "[" << len << "/" << mail_rev[i] << "]" ;
        
        len = 0;
        long iRecvSize = mail_rev[i] + 3;
        string revMailContent = "";
        cout << "[" << len << "/" << mail_rev[i] + 3 << "]" ;
        while (iRecvSize>0) {
            long iRet = sockReceiveMail.recv_socket();
            if (iRet > 0)
            {
                len += iRet;
                iRecvSize -= iRet;
            }
            else
                break;
            cout << "->[" << len << "/" << mail_rev[i] + 3 << "]" ;
            recv = sockReceiveMail.get_recvbuf();
            revMailContent += recv;
            //std::cout << recv << endl;
        }
        //std::cout << revMailContent << endl << "[" << len << "/" << mail_rev[i] + 3 << "]" << endl;
        getMailInfo(revMail[i-1], revMailContent, mail_rev[i] + 3);
        cout << endl << "mail " << i << ":" << endl;
        revMail[i-1].showMail();
	}
    
    sockReceiveMail.send_socket("quit\r\n");
    sockReceiveMail.recv_socket();
    std::cout << "Client : send quit \nServer :"
           << sockReceiveMail.get_recvbuf() << std::endl;
    return true;
}
