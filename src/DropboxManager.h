/*
DropboxManager ESP8266

Copyright (c) 2018 Lucas Romeiro

Author: Lucas Romeiro
Contact: lucas_romeiro@hotmail.com

This library was built in compliance with the criteria of official Dropbox documentation and the company is not responsible for the creation, 
maintenance or operation of this library.
The name "Dropbox" is owned by dropbox.com.
The dropbox.com company owns all copyrights on the name and brand.

Our goal is to facilitate the integration of embedded / IOT devices with cloud data storage system!
To manipulate your files in a simple, easy and practical way.
Integrate your esp8266 with your website or with your computer!
Expand the capacity of space and resources!

This library has some limitations:
-You can not upload files larger than 150MB.
-You can not upload multiple files at the same time. If you want to upload multiple files, do one at a time.

Available resources:
-Acquisition of token.
-Upload files.
-Upload of strings.
(COMING SOON!)

This library does not have all the features available in the dropbox, it is constantly developing and improving!

WE NEED YOUR HELP!!!

SUPPORT OUR WORK, SO THAT WE CAN CONTINUE TO IMPROVE AND DEVELOP NEW RESOURCES!

PLEASE, MAKE A DONATION TO ENCOURAGE US !!!
https://www.paypal.com/cgi-bin/webscr?cmd=_donations&business=lucas_romeiro%40hotmail%2ecom


Support us and help us also in the original repository of Github:
https://github.com/lucasromeiro/DropboxManager


License:

Permission is granted, free of charge, to anyone who obtains a copy of this software and associated documentation files (the "Software"), 
the rights of personal, academic and publication use.

If you wish to make commercial use of this software, we also grant the permission, but we make a special and non-obligatory request: 
Help us with some donation, we need contributions and incentives.

To allow persons to whom the Software is provided or in projects used, subject to the following conditions:

The above copyright notice and this permission notice must be included in all copies or substantial portions of the Software.

Note that the name "Dropbox" is owned by dropbox.com.
The dropbox.com company owns all copyrights on the name and brand.

THE SOFTWARE IS PROVIDED "AS IS," WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGE, 
USE OR OTHER LIABILITY WHETHER IN CONTRACT, TORT OR OTHERWISE, ARISING OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER CONCESSIONS OF THE SOFTWARE .
############################################################
############################################################

FUNCTIONS AVAILABLE:


void begin (String token);
If you already have a token or after acquiring it through the getToken(); function, 
you should call the begin("<your token here>”); function putting your token as a parameter so that the other functions can be initialized!

String getToken (String code);
This function receives its user code and through it returns the token to be able to access the services of the other functions or the error code found!
Ex: myDrop.getToken("<your code here>");
To get your user code, access this address in your browser, the code will be informed after logging in and accept the application access in your dropbox account. 
The code is 43 characters in length, please provide all.
Address: https://www.dropbox.com/oauth2/authorize?response_type=code&client_id=g0xkpmfu025pn8f

The return of the getToken(); function it's your token, it's secret and personal, do not share it with anyone! We do not have access to the users' token, so stay calm.
The token has 64 characters, securely store your token, because only it will be able to access the functions available in this library, 
your token is the access key to your dropbox and should be inserted in the begin(); function as explained above!

bool fileUpload (String localFile, String address, bool type);
This function uploads files to your dropbox, to use it simply provide it with the local address of the file to be uploaded that is stored in the SPIFFS of your esp8266, 
the address of which place the file in your dropbox should be saved and the type shipping
There are 2 types of submission: Add and Replace.
The Add type inserts a new file without replacing or deleting any files.
The Replace type inserts a new file and if there is a file with the same name in the folder, it will be replaced by the current one.
1 to Replace.
0 to Add.
Ex: myDrop.fileUpload("/test.txt", "/home/math/test.txt", 1);
This function returns TRUE if it succeeded and FALSE if there was a failure!

bool stringUpload (String data, String address, bool type);
This function uploads strings to your dropbox, to use it simply provide it with a string, the address of where to save the file in your dropbox and the type of submission!
There are 2 types of submission: Add and Replace.
The Add type inserts a new file without replacing or deleting any files.
The Replace type inserts a new file and if there is a file with the same name in the folder, it will be replaced by the current one.
1 to Replace.
0 to Add.
Ex: myDrop.stringUpload("<my string here>", "/home/math/test.txt", 1);
This function returns TRUE if it succeeded and FALSE if there was a failure!
Remember to create an instance to access the library:
Ex: DropboxManager myDrop;

See the Basic_upload example to understand better.

Enable debug mode by removing the comment from the define debug_mode in the DropboxManager.cpp file,


#############################################################################################
#############################################################################################

WE NEED YOUR HELP!!!
PLEASE, MAKE A DONATION AND LET US CONTINUE TO CONTINUE!
https://www.paypal.com/cgi-bin/webscr?cmd=_donations&business=lucas_romeiro%40hotmail%2ecom

#############################################################################################
#############################################################################################


Contact us if you have any questions, suggestions or want to help us.
lucas_romeiro@hotmail.com


PARA EXPLICAÇÕES EM PORTUGUES, CONSULTAR O ARQUIVO “README.md” QUE SE ENCONTRA NA PASTA DA BIBLIOTECA OU EM NOSSO REPOSITÓRIO DO GITHUB:
https://github.com/lucasromeiro/DropboxManager

*/

#ifndef DropboxManager_h
#define DropboxManager_h

#include "ESP8266WiFi.h"
#include "WiFiClientSecure.h" 
#include "FS.h"

class DropboxMan{
  public:
    DropboxMan();
    void begin(String token);
    String getToken(String code);
    bool fileUpload(String localFile, String address, bool type);
    bool stringUpload(String data, String address, bool type);
    
  private:
    String _token;
    
};

#endif
