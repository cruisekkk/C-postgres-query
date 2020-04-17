#include <iostream>
#include <pqxx/pqxx>
#include <fstream>

using namespace std;
using namespace pqxx;

class fileReader{
public:
  string filename;
  string tableName;

  // constructor:
  // parameter: filename, passed by main.cpp 
  fileReader(string filename){
    this->filename = filename;
    int pos = filename.find(".");
    this->tableName = filename.substr(0, pos);
  }

  // write single file's data into database
  // parameter: connection C
  void writedb(connection* C){
    // transaction inside this funciton
    work* Trans = new work(*C);
    ifstream f;
    f.open(filename);
    if (!f.good()){ 
      throw "file is not good!";
    }

    string line;
    string command;
    while (getline (f,line) ){
      command = parse(line);
      //cout << command << endl;
      Trans->exec(command);
    }    
    f.close();

    Trans->commit();
  }

  // helper method: convert line info from .txt file into sql command
  // using insert command, the first column should be default
  // because the id is serialized
  string parse(string line){
    string s = "";
    s += "INSERT INTO "+ tableName + " VALUES( DEFAULT, ";
    line = line + " ";
    int pos = line.find(" ");
    line = line.substr(pos+1);
    while(!line.empty()){
      pos = line.find(" ");
      s += "'";
      string name = line.substr(0, pos);
      if (name.find("'") != string::npos){
        int escapePos = name.find("'");
        s = s.substr(0, s.length()-1);
        // escape sign handling
        name = "E'" + name.substr(0, escapePos) + "\\" + name.substr(escapePos);
      }
      s += name;
      line = line.substr(pos+1);
      s += "', ";
    }
    s = s.substr(0, s.length() -2) + ");";
    return s;
  }


};
