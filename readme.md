```
基本完成了普通文本中英文的收发邮件，但是网页模式的还没搞定，好像挺麻烦的orz
编码方式不统一真是神烦

linux,mac os下用liconv转换编码
需要加上 other link flags: -liconv

create_qt_xcode_project.sh需要修改下qmake路径
新建工程qt_xcode工程：  ./create_qt_xcode_project.sh 工程名

http://stackoverflow.com/questions/30127910/os-x-compile-error-ld-symbols-not-found-for-architecture-x86-64

windows下用api转换编码
```
From: =?UTF-8?B?572R5piT5omL5py65Y+356CB6YKu566x?= <phone@service.netease.com>
Sender: phone@service.netease.com
To: 17816862370@163.com
Subject: =?GBK?B?xPq1xM340tfK1rv6usXC69PKz+S8pLvus8m5pg==?=
Date: Mon, 11 Apr 2016 09:12:58 +0800 (CST)

Date: Mon, 11 Apr 2016 10:07:59 +0800 (CST)
From: meteor <qqq1051814353@163.com>
To: q1051814353@163.com
Subject: hello
------=_Part_86044_371223391.1460340479574
Content-Type: text/plain; charset=GBK
Content-Transfer-Encoding: base64

bWV0ZW9yOgogICAgaG93YXJlIHlvdS4=
------=_Part_86044_371223391.1460340479574
Content-Type: text/html; charset=GBK
Content-Transfer-Encoding: base64

PGRpdiBzdHlsZT0ibGluZS1oZWlnaHQ6MS43O2NvbG9yOiMwMDAwMDA7Zm9udC1zaXplOjE0cHg7
Zm9udC1mYW1pbHk6QXJpYWwiPjxkaXY+PHNwYW4gc3R5bGU9ImZvbnQtdmFyaWFudC1saWdhdHVy
ZXM6IG5vLWNvbW1vbi1saWdhdHVyZXMiPm1ldGVvcjo8L3NwYW4+PC9kaXY+PGRpdj48c3BhbiBz
dHlsZT0iZm9udC12YXJpYW50LWxpZ2F0dXJlczogbm8tY29tbW9uLWxpZ2F0dXJlcyI+Jm5ic3A7
ICZuYnNwOyBob3dhcmUgeW91Ljwvc3Bhbj48L2Rpdj48L2Rpdj48YnI+PGJyPjxzcGFuIHRpdGxl
PSJuZXRlYXNlZm9vdGVyIj48cD4mbmJzcDs8L3A+PC9zcGFuPg==
------=_Part_86044_371223391.1460340479574--


subject:hello
meteor:
howare you.
Date: Mon, 11 Apr 2016 10:08:40 +0800 (CST)
From: q1051814353@163.com


subject:hello
meteor:
howare you.
Date: Mon, 11 Apr 2016 10:09:41 +0800 (CST)
From: q1051814353@163.com


From: "=?gb18030?B?TWV0ZW9y?=" <1051814353@qq.com>
To: "=?gb18030?B?cTEwNTE4MTQzNTM=?=" <q1051814353@163.com>
Subject: =?gb18030?B?xOPKx3Niw7Q=?=
Date: Mon, 30 May 2016 00:23:55 +0800
<<<<<<< HEAD
```
=======
```
>>>>>>> origin/master
