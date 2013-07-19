qt-cgi
======

This is a C++ CGI Wrapper built in Qt

Installation
============
1.  Clone this repository into your site's CGI-BIN or a folder with ExecCGI privileges.
2.  Execute "cd qt-cgi/" where qt-cgi is the root of this repository.
3.  Execute "qmake QtCGI.pro", if you are running Qt5 and Qt4, execute "qmake-qt4 QtCGI.pro".
4.  Execute "make".
5.  Navigate to http://yourdomain.tld/cgi-bin/helloWorld.qgi

Updates
=======
2013-07-19 17:31 - Fixed support for reading and processing POST data
