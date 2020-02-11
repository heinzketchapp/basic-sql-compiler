#include <iostream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <cstring>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

char *find_filename(string tablename){
    tablename += ".csv";
    char *filename = new char[tablename.length()+1];
    strcpy(filename, tablename.c_str());
    return filename;
}

bool file_exists(const char *filename){
    ifstream fp;
    fp.open(filename);
    if (fp){
        fp.close();
        return true;
    }
    return false;
}

string create_table(string table_name, vector<string> attributes, vector<string>dtypes){
    char *filename = find_filename(table_name);
    if(file_exists(filename)){
        return "Error : Table already exists!";
    }
    fstream fp;
    fp.open(filename, ios::out);
    string head = "";
    for (int i=0; i<attributes.size(); i++){
        if (i!=0){
            head += "," + attributes[i]+dtypes[i];
        }
        else
            head += attributes[i]+dtypes[i];
    }
    fp<<head<<endl;
    fp.close();
    return "Table created successfully.";
}

vector <string> tokenize(string line){
    vector <string> tokens;
    stringstream stream(line);
    string temp;
    while (getline(stream, temp, ',')){
        tokens.push_back(temp);
    }
    return tokens;
}

bool is_digit(string line){
    for (int i=0; i<line.length(); i++){
        int c = (int) line[i];
        if (!(c>=48 && c<58))
            return false;
    }  
    return true;
}

string insert_into(string tablename, vector<string> values){
    char *filename = find_filename(tablename);
    if (!file_exists(filename)){
        return "Error : Table not found!";
    }
    fstream fp;
    fp.open(filename, ios::in);
    string line;
    getline(fp, line);
    fp.close();
    vector <string> params = tokenize(line);
    if (values.size() != params.size())
        return "Error : Number of attributes mismatch!";
    line = "";
    for (int i=0; i<values.size(); i++){
        string attr = params[i];
        if (attr[attr.length()-1] == '0' && (!is_digit(values[i])))
            return "Error : "+values[i]+" is not of type integer!";
        if (i==0)
            line += values[i];
        else
            line += "," + values[i];
    }
    fp.open(filename, ios::app);
    fp<<line<<endl;
    fp.close();
    return "Inserted 1 row in table " + tablename + " successfully!";
}

vector <vector <string> > get_all(string tablename){
    const char* filename = find_filename(tablename);
    vector <vector <string> > data;
    fstream fp;
    fp.open(filename, ios::in);
    string line;
    while(getline(fp, line)){
        data.push_back(tokenize(line));
    }
    for (int i=0; i<data[0].size();i++){
        data[0][i].pop_back();
    }
    fp.close();
    return data;
}

vector <vector <string> > get_where(string tablename, string condition, string cval){
       const char* filename = find_filename(tablename);
       vector <vector <string> > data;
       fstream fp;
       fp.open(filename, ios::in);
       string line;
       getline(fp,line);
       int ind=-1;
       vector <string> token=tokenize(line);
       for (int i=0;i<token.size();i++){
        //token[i][ token[i].length() - 1] = '\0';
        token[i].pop_back();
       }
       std::transform(condition.begin(), condition.end(), condition.begin(), ::tolower);
       std::transform(cval.begin(), cval.end(), cval.begin(), ::tolower);
       
       condition[condition.length()]='\0';
       for (int i=0; i<token.size();i++){
           if(string(token[i]).compare(condition)==0){
               ind=i;
           }
       }
       if( ind==-1){
           cout<<"Error : Attribute "+condition+" does not exist"<<endl;
       }
       else {
            data.push_back(token);
            
            while (getline(fp, line)){
                  token=tokenize(line);
                  if( string(token[ind]).compare(cval)==0){
                      data.push_back(token);
                  }
            }
       }
       fp.close();
       return data;
}

void print_data(vector<vector<string> > data){
    for (int i=0;i<data.size(); i++){
        for (int j=0; j<data[i].size();j++)
            cout<<data[i][j]<<"\t";
        cout<<endl;
    }
}

string drop_table(string tablename){
    const char *filename = find_filename(tablename);
    int status = remove(filename);
    if (status == 0){
        return "Table " + tablename + " dropped successfully.";
    }
    return "Error : Table "+tablename + " does not exist!";
}

void execute(vector<string> attributes, vector<string> dtypes, vector<string> values, char *tablename, char *condition, char *cval, int cmd){
    string table_name = string(tablename);
    string condition1=string(condition);
    string cval1=string(cval);
    vector< vector<string> > data;
    switch (cmd){
        case 1:            
            cout<<create_table(table_name, attributes, dtypes)<<endl;
            break;
        case 2:             
            cout<<insert_into(table_name, values)<<endl;
            break;
        case 3:            
            data = get_all(table_name);
            print_data(data);
            break;
        case 4:
             data=get_where(table_name,condition1,cval1);
             print_data(data);
             break;
        case 5:             
            cout<<drop_table(table_name)<<endl;
            break;
        case 6:
             data=get_all(table_name);
             cout<<"Count(*)"<<endl;
             cout<<data.size()-1<<endl;
             break;
        case 7:
             data=get_where(table_name,condition,cval);
             cout<<"Count(*)"<<endl;
             cout<<data.size()-1<<endl;
             break;
    }
}
