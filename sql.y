%{
    #include <iostream>
    #include <cstring>
    #include <vector>
    #include "sql.cpp"

    using namespace std;
    
    extern int yylex();

    void yyerror(const char *s);

    char *tablename = (char *) malloc(100);
    vector <string> attributes;
    vector <string> dtypes;
    vector <string> values;
    char *condition = (char *) malloc(100);
    char *cval= (char *) malloc(100);
%}
%union{
    char *sval;
    int ival;
}

%token CREATE 
%token TABLE   
%token SELECT 
%token INSERT  
%token INTO   
%token FROM    
%token VALUES  
%token DROP    
%token <sval> STRING
%token CHAR
%token NUMBER
%token SCOLON
%token OBR
%token CBR
%token ALL
%token EOL
%token COMMA
%token COUNT
%token WHERE
%token EQUALS
%token <sval> INTEGER
%token QUOTE

%start stmt_list
%type <sval> table_name arg_name
%type <ival> stmt 

%%
stmt_list:
    | line stmt_list
    ;
line:EOL
    | stmt SCOLON EOL { execute(attributes, dtypes, values, tablename,condition,cval, $1); 
                        attributes.clear();
                        dtypes.clear();
                        values.clear();
                        strcpy(tablename, "");
                        strcpy(condition,"");
                        strcpy(cval,"");
                        cout<<"Mini-sql>";}
    ;

stmt: 
    create_stmt   { $$ = 1; }
    | insert_stmt   { $$ = 2; }
    | select_stmt1   { $$ = 3; }
    | select_stmt2   { $$ = 4; }
    | drop_stmt     { $$ = 5; }
    | count_stmt1   {$$ = 6; }
    | count_stmt2   { $$ = 7; }
    ;
drop_stmt: DROP TABLE table_name
         ;

select_stmt1: SELECT ALL FROM table_name 
           ;
select_stmt2: SELECT ALL FROM table_name WHERE argC EQUALS term
            ;
term:
        QUOTE STRING QUOTE  {strcpy(cval,$2);}
        | INTEGER           {strcpy(cval,$1);}
        ;
argC:
        STRING {strcpy(condition,$1);}
        ;

count_stmt1:  SELECT COUNT OBR ALL CBR FROM table_name
            ;

count_stmt2: SELECT COUNT OBR ALL CBR FROM table_name WHERE argC EQUALS term
            ;

create_stmt: CREATE TABLE table_name OBR create_args CBR
           ;

create_args: create_args COMMA arg
            | arg
           ;

insert_stmt: INSERT INTO table_name VALUES OBR insert_args CBR
            ;
insert_args: insert_args COMMA terminal
            | terminal
            ;

terminal:
        QUOTE STRING QUOTE  { values.push_back($2); }
        | INTEGER           { values.push_back($1); }
        ;            

arg: 
    arg_name CHAR  { attributes.push_back($1); dtypes.push_back("1");}
    | arg_name NUMBER   { attributes.push_back($1); dtypes.push_back("0");}
    ;

arg_name: STRING { $$ = $1;}
        ;

table_name: 
          STRING { strcpy(tablename, $1);}
          ;
%%
int main(){
    cout<<"Mini-sql>";
    yyparse();
}

void yyerror(const char *s){
    cout<<"Parse Err: "<<s<<endl;
    exit(-1);
}
