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
-Download of files.
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

bool fileDownload (String localFile, String address, bool type);
This function downloads files from your Dropbox to your ESP8266, to use it simply provide it with the local address where the file will be saved (SPIFFS from your esp8266), the address of which place is saved the file you want to download from your dropbox and if you want to delete the file if there is already one with the same name in your esp8266, 1 to delete and 0 to not delete! If you enter 0 and the file exists, the new one will not be downloaded.
Ex: myDrop.fileDownload ("/test.txt", "/home/math/test.txt", 1);
This function returns TRUE if it succeeded and FALSE if there was a failure!


Remember to create an instance to access the library:
Ex: DropboxMan myDrop;

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


#include "ESP8266WiFi.h"
#include "WiFiClientSecure.h" 
#include "FS.h"
#include "DropboxManager.h"

#define ver "v1.1"
//#define debug_mode Serial


#define upload "/2/files/upload HTTP/1.1\r\n"
#define download "/2/files/download HTTP/1.1\r\n"
#define host_content "Host: content.dropboxapi.com\r\n"
#define content_type_octet "Content-Type: application/octet-stream\r\n"
#define _accept "Accept: */*\r\n"
#define Aut_Bearer "Authorization: Bearer "
#define timeout_client 5000
#define timeout_down 5000
#define content_API "162.125.5.8"
#define fingerprint_Content_API "9D 86 7B C9 7E 07 D7 5C 86 66 A3 E2 95 C3 B5 45 C5 1E 89 B3"
#define main_API "162.125.5.7"
#define fingerprint_Main_API "C8 50 54 26 17 A5 FB 9F 19 FC 59 ED 11 43 3C F9 37 F9 64 7F"
#define oauth2 "/oauth2/token HTTP/1.1\r\n"
#define host_API "Host: api.dropboxapi.com\r\n"
#define content_type_urlencoded "Content-Type: application/x-www-form-urlencoded\r\n"

DropboxMan::DropboxMan(){

}

void DropboxMan::begin(String token){
  
  if(token.length()<64){
    #ifdef debug_mode
      debug_mode.println("FAIL: Small token!");
    #endif
    return;
  }
  if(token.length()>64){
    #ifdef debug_mode
      debug_mode.println("FAIL: Big token!");
    #endif
    return;
  }
  _token=token;
}

String DropboxMan::getToken(String code){
  
  if(code.length()<43){
    #ifdef debug_mode
      debug_mode.println("FAIL: Small code!");
    #endif
    return "FAIL: Small code!";
  }
  if(code.length()>43){
    #ifdef debug_mode
      debug_mode.println("FAIL: Big code!");
    #endif
    return "FAIL: Big code!";
  }
  
  WiFiClientSecure client;
  //WiFiClientSecure *client= new WiFiClientSecure;
  #ifdef debug_mode
    debug_mode.println("Connecting to Dropbox...");
  #endif
  if (!client.connect(main_API,443)){
    #ifdef debug_mode
      debug_mode.println("Connection failed!");
    #endif
    //client.close();
    client.stop();
    return "FAIL";
  }

  if (client.verify(fingerprint_Main_API,"api.dropboxapi.com")) {
    #ifdef debug_mode
      debug_mode.println("Certificate matches!");
    #endif
  } else {
    #ifdef debug_mode
      debug_mode.println("Certificate doesn't match!");
    #endif
  }
  
  
  String pack ="code=" + code + "&grant_type=authorization_code&client_id=g0xkpmfu025pn8f&client_secret=knagh39wa75p8n9";
  client.print(String("POST ") + oauth2 +
               host_API +
               "User-Agent: ESP8266/Arduino_Dropbox_Manager_"+(String)ver+"\r\n" +
               _accept +
               content_type_urlencoded +
               "Content-Length: " + pack.length() + "\r\n\r\n" +
               pack
               );
               
  #ifdef debug_mode
    debug_mode.println("Request sent!");
  #endif
  uint32_t millisTimeoutClient;
  millisTimeoutClient = millis();
  String line;
  while (client.connected() && ((millis()-millisTimeoutClient)<timeout_client)) {
    line = client.readStringUntil('\n');
    if (line == "\r") {
      break;
    }
  }


  line = client.readStringUntil('\n');
  line = client.readStringUntil('\n');
  //client.close();
  client.stop();
  if (line.startsWith("{\"access_token\": \"")) {
    #ifdef debug_mode
      debug_mode.println("Successfull!!!");
      debug_mode.println("Token:");
      debug_mode.print(line.substring(line.indexOf("{\"access_token\": \"")+18, line.indexOf("\",")));
    #endif
    return line.substring(line.indexOf("{\"access_token\": \"")+18, line.indexOf("\","));
  } else {
    #ifdef debug_mode
      debug_mode.println(line);
    #endif
    return "FAIL";
  }

}

bool DropboxMan::fileUpload(String localFile, String address, bool type){
  String _mode;
  if(type){
    _mode="overwrite";
  }else{
    _mode="add";
  }
  WiFiClientSecure client;
  //WiFiClientSecure *client= new WiFiClientSecure;
  #ifdef debug_mode
    debug_mode.println("Connecting to Dropbox...");
  #endif
  if (!client.connect(content_API,443)){
    #ifdef debug_mode
      debug_mode.println("Connection failed!");
    #endif
    //client.close();
    client.stop();
    return false;
  }

  if (client.verify(fingerprint_Content_API,"content.dropboxapi.com")) {
    #ifdef debug_mode
      debug_mode.println("Certificate matches!");
    #endif
  } else {
    #ifdef debug_mode
      debug_mode.println("Certificate doesn't match!");
    #endif
  }

  if(!SPIFFS.begin()){
      #ifdef debug_mode
        debug_mode.println("Failed to open file system...");
      #endif
      //client.close();
      client.stop();
      return false;
    } else {
      #ifdef debug_mode
        debug_mode.println("Open file system successfully!");
      #endif
    }
  
  File files = SPIFFS.open(localFile,"r+");
  uint32_t sizeFile=files.size();

  client.print(String("POST ") + upload +
               host_content +
               "User-Agent: ESP8266/Arduino_Dropbox_Manager_"+(String)ver+"\r\n" +
               (String)Aut_Bearer + (String)_token +"\r\n" +
               _accept +
               "Dropbox-API-Arg: {\"path\": \"" + address + "\",\"mode\": \"" + _mode + "\",\"autorename\": true,\"mute\": false}\r\n" +
               content_type_octet +
               "Content-Length: " + sizeFile + "\r\n\r\n"
               );
  uint32_t index=0;
  char _buffer[1001];
  while(index<sizeFile){ 
    yield();
    ESP.wdtFeed();
    index=index+1000;
    files.readBytes(_buffer,1000);
    _buffer[1000]='\0';
    client.print(_buffer);
  }
  client.flush();
  files.close();   
  SPIFFS.end();
  #ifdef debug_mode
    debug_mode.println("Request sent!");
  #endif
  uint32_t millisTimeoutClient;
  millisTimeoutClient = millis();
  String line;
  while (client.connected() && ((millis()-millisTimeoutClient)<timeout_client)) {
    line = client.readStringUntil('\n');
    if (line == "\r") {
      break;
    }
  }
  
  line = client.readStringUntil('\n');
  line = client.readStringUntil('\n');
  //client.close();
  client.stop();
  //delete client;
  if (line.startsWith("{\"name\": \"")) {
    #ifdef debug_mode
      debug_mode.println("Successfull!!!");
      debug_mode.println("File sent!");
    #endif
    return true;
  } else {
    #ifdef debug_mode
      debug_mode.println("ERROR!!!");
      debug_mode.println(line);
    #endif
    return false;
  }
}

bool DropboxMan::stringUpload(String data, String address, bool type){
  String _mode;
  if(type){
    _mode="overwrite";
  }else{
    _mode="add";
  }
  WiFiClientSecure client;
  #ifdef debug_mode
    debug_mode.println("Connecting to Dropbox...");
  #endif
  if (!client.connect(content_API,443)){
    #ifdef debug_mode
      debug_mode.println("Connection failed!");
    #endif
    return false;
  }

  if (client.verify(fingerprint_Content_API,"content.dropboxapi.com")) {
    #ifdef debug_mode
      debug_mode.println("Certificate matches!");
    #endif
  } else {
    #ifdef debug_mode
      debug_mode.println("Certificate doesn't match!");
    #endif
  }        
         
  client.print(String("POST ") + upload +
               host_content +
               "User-Agent: ESP8266/Arduino_Dropbox_Manager_"+(String)ver+"\r\n" +
               (String)Aut_Bearer + (String)_token +"\r\n" +
               _accept +
               "Dropbox-API-Arg: {\"path\": \"" + address + "\",\"mode\": \"" + _mode + "\",\"autorename\": true,\"mute\": false}\r\n" +
               content_type_octet +
               "Content-Length: " + data.length() + "\r\n\r\n" +
               data
               );
  client.flush();
  #ifdef debug_mode
    debug_mode.println("Request sent!");
  #endif
  uint32_t millisTimeoutClient;
  millisTimeoutClient = millis();
  String line;
  while (client.connected() && ((millis()-millisTimeoutClient)<timeout_client)) {
    line = client.readStringUntil('\n');
    if (line == "\r") {
      break;
    }
  }  
  line = client.readStringUntil('\n');
  line = client.readStringUntil('\n');
  //client.close();
  client.stop();
  if (line.startsWith("{\"name\": \"")) {
    #ifdef debug_mode
      debug_mode.println("Successfull!!!");
      debug_mode.println("File sent!");
    #endif
    return true;
  } else {
    #ifdef debug_mode
      debug_mode.println("ERROR!!!");
      debug_mode.println(line);
    #endif
    return false;
  }
  
}

bool DropboxMan::fileDownload(String localFile, String address, bool type){
  

  WiFiClientSecure client;
  //WiFiClientSecure *client= new WiFiClientSecure;
  #ifdef debug_mode
    debug_mode.println("Connecting to Dropbox...");
  #endif
  if (!client.connect(content_API,443)){
    #ifdef debug_mode
      debug_mode.println("Connection failed!");
    #endif
    //client.close();
    client.stop();
    return false;
  }

  if (client.verify(fingerprint_Content_API,"content.dropboxapi.com")) {
    #ifdef debug_mode
      debug_mode.println("Certificate matches!");
    #endif
  } else {
    #ifdef debug_mode
      debug_mode.println("Certificate doesn't match!");
    #endif
  }

  if(!SPIFFS.begin()){
      #ifdef debug_mode
        debug_mode.println("Failed to open file system...");
      #endif
      //client.close();
      client.stop();
      return false;
  } else {
      #ifdef debug_mode
        debug_mode.println("Open file system successfully!");
      #endif
  }

  client.print(String("POST ") + download +
               host_content +
               "User-Agent: ESP8266/Arduino_Dropbox_Manager_"+(String)ver+"\r\n" +
               (String)Aut_Bearer + (String)_token +"\r\n" +
               _accept +
               "Dropbox-API-Arg: {\"path\": \"" + address + "\"}\r\n\r\n"// +
               //"Content-Length: 0\r\n\r\n"
               );
  

  #ifdef debug_mode
    debug_mode.println("Request sent!");
  #endif
  uint32_t millisTimeoutClient;
  millisTimeoutClient = millis();
  String line;
  bool ok;
  ok=0;
  while (client.connected() && ((millis()-millisTimeoutClient)<timeout_client)) {
    line = client.readStringUntil('\n');
    if (line == "\r") {
      break;
    }
    if(line.indexOf("\", \"path_display\": \""+address+"\", \"")!=-1){
      ok=1;
    }
  }

  if(ok){
    if(type){
      SPIFFS.remove(localFile);
      #ifdef debug_mode
          debug_mode.println("Old file removed!");
      #endif 
    }else{
      if(SPIFFS.exists(localFile)){
        #ifdef debug_mode
          debug_mode.println("Aborted, file exist!");
        #endif   
        SPIFFS.end();
        client.stop();
        return false;
      }
    }
    char _buffer[1001];
    millisTimeoutClient = millis();
    File files = SPIFFS.open(localFile,"a");
    while (client.connected() && ((millis()-millisTimeoutClient)<timeout_down)) {
      if (client.available()) {
        millisTimeoutClient = millis();
        yield();
        ESP.wdtFeed();

        client.readBytes(_buffer,1000);
        _buffer[1000]='\0';
        files.print(_buffer);
      }
    }
      
    files.close();   
    SPIFFS.end();
  }
  //client.close();
  client.stop();
  //delete client;
  if (ok) {
    #ifdef debug_mode
      debug_mode.println("Successfull!!!");
      debug_mode.println("File downloaded!!!");
    #endif
    return true;
  } else {
    #ifdef debug_mode
      debug_mode.println("ERROR!!!");
      debug_mode.println(client.readString());
    #endif
    return false;
  }
}






