<img src="https://github.com/lucasromeiro/ArduinoESP8266DropboxManager/DropboxManager/readme.png”/>

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
https://github.com/lucasromeiro/ArduinoESP8266DropboxManager


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

#############################################################################################

EM PORTUGUES:

DropboxManager ESP8266

Direitos autorais (c) 2018 Lucas Romeiro

Autor: Lucas Romeiro
Contato: lucas_romeiro@hotmail.com

Esta biblioteca foi construída obedecendo os critérios das documentações oficiais do Dropbox e a empresa não é responsável pela criação, manutenção ou funcionamento desta biblioteca.
O nome "Dropbox" é propriedade da dropbox.com.
A empresa dropbox.com detém todos os direitos autorais sobre o nome e a marca.

Nosso objetivo é facilitar a integração dos dispositivos embarcados / IOT com sistema de armazenamento de dados na nuvem! 
Para manipular seus arquivos de forma simples, fácil e prática.
Integre seu esp8266 com seu site ou com seu computador! 
Expanda a capacidade de espaço e recursos!

Esta biblioteca tem algumas limitações:
-Não é possível fazer upload de arquivos maiores que 150MB.
-Não é possível fazer upload de vários arquivos ao mesmo tempo. Se desejar fazer upload de vários arquivos, faça um de cada vez.

Recursos disponíveis:
-Aquisição de token.
-Upload de arquivos.
-Upload de strings.
(MAIS EM BREVE!)

Esta biblioteca não conta com todos os recursos disponíveis no dropbox, ela está em constante desenvolvimento e melhoria!

APOIE NOSSO TRABALHO, PARA QUE POSSAMOS CONTINUAR A MELHORAR E DESENVOLVER NOVOS RECURSOS!

POR FAVOR, FAÇA UMA DOAÇÃO PARA NOS INCENTIVAR!!!
https://www.paypal.com/cgi-bin/webscr?cmd=_donations&business=lucas_romeiro%40hotmail%2ecom


Nos apoie e nos ajude também no repositório original do Github:
https://github.com/lucasromeiro/ArduinoESP8266DropboxManager


Licença:

É concedida permissão, gratuitamente, a qualquer pessoa que obtenha uma cópia deste software e dos arquivos de documentação associados (o "Software"), os direitos de uso pessoal, acadêmico e publicação.

Se deseja fazer uso comercial deste software, também concedemos a permissão, porém fazemos um pedido especial e não obrigatório: Nos ajude com alguma doação, precisamos de contribuições e incentivos.

Para permitir que pessoas a quem o Software esteja fornecido ou em projetos utilizados, sujeito às seguintes condições:

O aviso de copyright acima e este aviso de permissão devem ser incluídos em todas as cópias ou partes substanciais do Software.

Lembre que o nome "Dropbox" é propriedade da dropbox.com.
A empresa dropbox.com detém todos os direitos autorais sobre o nome e a marca.

O SOFTWARE É FORNECIDO "COMO ESTÁ", SEM GARANTIA DE QUALQUER TIPO, EXPRESSA OU IMPLÍCITA, INCLUINDO, MAS NÃO SE LIMITANDO ÀS GARANTIAS DE COMERCIALIZAÇÃO, APTIDÃO PARA UMA FINALIDADE ESPECÍFICA E NÃO VIOLAÇÃO. EM NENHUMA CIRCUNSTÂNCIA AUTORES OU DETENTORES DOS DIREITOS AUTORAIS SERÃO RESPONSABILIZADOS POR QUALQUER RECLAMAÇÃO, DANOS, USO OU OUTRAS RESPONSABILIDADES, SEJA EM AÇÃO DE CONTRATO, DELITO OU OUTRO, DECORRENTE DE, FORA OU EM CONEXÃO COM O SOFTWARE OU O USO OU OUTRAS CONCESSÕES DO SOFTWARE.


############################################################
############################################################


Funções disponíveis:


void begin(String token);
Se voce já tem um token ou após adquirir ele através da função getToken();, deverá chamar a função begin("<seu token aqui>"); botando seu token como parâmetro para que sejam inicializadas as demais funções!


String getToken(String code);
Essa função recebe seu código de usuário e através dele retorna o token para conseguir acessar os serviços das demais funções ou o código do erro encontrado!
Ex: myDrop.getToken("<seu código aqui>");
Para conseguir o seu código de usuário, acesse este endereço em seu browser, o código será informado após logar e aceitar o acesso do aplicativo na sua conta do dropbox. O código tem comprimento de 43 caracteres, forneça todos.
Endereço: https://www.dropbox.com/oauth2/authorize?response_type=code&client_id=g0xkpmfu025pn8f

O retorno da função getToken(); é o seu token, ele é secreto e pessoal, não compartilhe com ninguém! Nós não temos acesso ao token dos usuários, fique tranquilo.
O token tem 64 caracteres, guarde com segurança seu token, porque somente com ele será possível acessar as funções disponíveis nesta biblioteca, seu token é a chave de acesso ao seu dropbox e deverá ser inserido na função begin(); conforme explicado acima!

bool fileUpload(String localFile, String address, bool type);
Essa função faz o upload de arquivos para seu dropbox, para usar basta fornecer a ela o endereço local do arquivo a ser upado que está armazenado no SPIFFS do seu esp8266, o endereço de qual lugar deverá ser salvo o arquivo em seu dropbox e o tipo de envio!
Existem 2 tipos de envio: Adicionar e Substituir.
O tipo Adicionar insere um novo arquivo sem substituir nem apagar nenhum arquivo.
O tipo Substituir insere um novo arquivo e se existir um arquivo com o mesmo nome na pasta, ele será substituído pelo atual.
1 para Substituir.
0 para Adicionar.
Ex: myDrop.fileUpload("/test.txt","/home/math/test.txt",1);
Essa função retorna TRUE se teve sucesso e FALSE se houve alguma falha!

bool stringUpload(String data, String address, bool type);
Essa função faz o upload de strings para seu dropbox, para usar basta fornecer a ela uma string, o endereço de qual lugar deverá ser salvo o arquivo em seu dropbox e o tipo de envio!
Existem 2 tipos de envio: Adicionar e Substituir.
O tipo Adicionar insere um novo arquivo sem substituir nem apagar nenhum arquivo.
O tipo Substituir insere um novo arquivo e se existir um arquivo com o mesmo nome na pasta, ele será substituído pelo atual.
1 para Substituir.
0 para Adicionar.
Ex: myDrop.stringUpload("<minha string aqui>","/home/math/test.txt",1);
Essa função retorna TRUE se teve sucesso e FALSE se houve alguma falha!
Lembre de criar uma instancia para acessar a biblioteca:
Ex: DropboxManager myDrop;

Veja o exemplo Basic_upload para entender melhor.

Ative o modo debug, retirando o comentário do define debug_mode no arquivo DropboxManager.cpp


#############################################################################################
#############################################################################################

NÓS PRECISAMOS DE SUA AJUDA!
POR FAVOR, FAÇA UMA DOAÇÃO E NOS INCENTIVE A CONTINUAR!
https://www.paypal.com/cgi-bin/webscr?cmd=_donations&business=lucas_romeiro%40hotmail%2ecom

#############################################################################################
#############################################################################################


Entre em contato caso tenha dúvidas, sugestões ou queira nos ajudar.
lucas_romeiro@hotmail.com