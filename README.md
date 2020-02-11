# basic-sql-compiler
This is a basic SQL compiler that can parse and show output for the following statements:
1. Create table table-name();
2. Insert into table-name values();
3. Select * from table-name where condition;
4. Select count( * ) from table-name where condition;
5. Drop table table-name;

# DEPENDENCIES
1. Flex
2. Bison
#. g++

# Installation

For Windows:
You'll need the latest versions of:
[Flex](http://gnuwin32.sourceforge.net/packages/flex.htm) 
[Bison](http://gnuwin32.sourceforge.net/packages/bison.htm)
Do a full install in a directory of your preference without spaces in the name because bison has problems with spaces in directory names.
Suggested directory: 
C:\GnuWin32
Set PATH variable to include the bin directories of flex/bison: C:\GnuWin32\bin

[g++](http://www.mingw.org/)
Set PATH variable to include C:\MinGW\bin

For Linux:
$ yum install flex
$ yum install bison
If gcc and/or g++ and its related Development Tools are not installed in your system by default, you can install the latest available from the repositories as follows:
$ yum groupinstall 'Development tools'

# Commands to setup and execute
`$ flex sql.l`

`$ bison -dy sql.y`

`$ g++ lex.yy.c y.tab.c -o sql.exe`

To execute, run sql.exe

# Acknowledgement
[Muttashim Sarkar](https://github.com/Muttashim)
