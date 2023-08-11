# C-- Compiler README
Project github link: https://github.com/johnhaviland/finalCompiler/tree/main
## Setup Instructions
In order to run the C-- Compiler, you will need the following programs installed and enabled on your computer:
 - Windows Subsystem for Linux (WSL)
 - Flex
 - Bison

Following this is step by step instructions for installing and enabling all of these tools.
### Setting up and installing Windows Subsystem for Linux
 1. Ensure that your system meets the following requirements:
 - running Windows 10 or higher
 - running 64 bit version of Windows
 2. Open the Start menu and search for "Turn Windows features on or off".
 3. Scroll down and check the box next to "Windows Subsystem for Linux".
[![N|Solid](https://cdn.discordapp.com/attachments/929594997790101515/1139602840105521292/image.png)]()
 4. Click "OK" and wait for Windows to enable the feature.
 5. Open the Microsoft Store.
 6. Search for "ubuntu" and select the version that you desire.
 7. Click "Install" to download and install that Ubuntu version.
 8. Once installation is complete, click "Launch" from the Microsoft Store, or search the start menu for "Ubuntu" and launch it from there.
 9. The first time you launch, you'll need to set up a user account. You'll be asked to provide a username and password.
10.  After setting up the user account, the installation will be finalized, and you'll have a working Linux terminal.
11.  Once you are logged in, run the following commands in your terminal to update packages and to upgrade previously installed packages:
```sh
sudo apt update
sudo apt upgrade
```
Now you are ready to install Flex and Bison.
### Installing Flex
1.  First, to ensure all packages are up to date, run the following command on your Linux command line:
```sh
sudo apt update
```
2.  Next, to install Flex, execute the following:
```sh
sudo apt install flex
```
3.  Finally, to verify proper installation, run:
```sh
flex --version
```
This should output the version of flex that you just installed.
### Installing Bison
1.  First, to ensure all packages are up to date, run the following command on your Linux command line:
```sh
sudo apt update
```
2.  Next, to install Bison, execute the following:
```sh
sudo apt install bison
```
3.  Finally, to verify proper installation, run:
```sh
bison --version
```
Now you have all the tools to properly run the C-- Compiler.
### Setting up the compiler
The first step is to download all of the files that make up the compiler and place them into the same directory in your Linux environment.  All of the files necessary are:
| File Name | Github Link |
| ------ | ------ |
| AST.h | https://github.com/johnhaviland/finalCompiler/blob/main/AST.h |
| Assembly.h | https://github.com/johnhaviland/finalCompiler/blob/main/Assembly.h|
| IRcode.h | https://github.com/johnhaviland/finalCompiler/blob/main/IRcode.h |
| Makefile | https://github.com/johnhaviland/finalCompiler/blob/main/Makefile |
| lexer.l | https://github.com/johnhaviland/finalCompiler/blob/main/lexer.l |
| parser.y | https://github.com/johnhaviland/finalCompiler/blob/main/parser.y|
| registerManager.h | https://github.com/johnhaviland/finalCompiler/blob/main/registerManager.h |
| symbolTable.h | https://github.com/johnhaviland/finalCompiler/blob/main/symbolTable.h |
Once all of these files have been downloaded and placed in the same directory, create a .cmm file in that directory.  This can be accomplished in a few ways.  The first is with touch, which will simply create a file in your directory.
```sh
touch yourfile.cmm
```
The other option is to create a new file and then open it with a text editor.  There are a few options such as nano:
```sh
nano yourfile.cmm
```
vim:
```sh
vim yourfile.cmm
```
or emacs:
```sh
emacs yourfile.cmm
```
Once you have created your file and written your program, exit to the terminal and then open up the Makefile by running:
```sh
nano Makefile
```
Once you have opened it, modify line 11 of the file so that the program name matches your own.
```
11.  ./parser yourfile.cmm
```
The final step is to execute the compiler, which can be accomplished with the following two commands:
```sh
make clean
make parser
```
Those commands will run the compiler on your code.
