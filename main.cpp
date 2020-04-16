#include <iostream>
#include <pqxx/pqxx>

#include "exerciser.h"
#include "tableLoader.cpp"
using namespace std;
using namespace pqxx;

int main (int argc, char *argv[]) 
{

  //Allocate & initialize a Postgres connection object
  connection *C;

  try{
    //Establish a connection to the database
    //Parameters: database name, user name, user password
    C = new connection("dbname=ACC_BBALL user=postgres password=passw0rd");
    if (C->is_open()) {
      cout << "Opened database successfully: " << C->dbname() << endl;
    } else {
      cout << "Can't open database" << endl;
      return 1;
    }
  } catch (const std::exception &e){
    cerr << e.what() << std::endl;
    return 1;
  }


  //TODO: create PLAYER, TEAM, STATE, and COLOR tables in the ACC_BBALL database
  //      load each table with rows from the provided source txt files

  // a database transaction
  // 
  work* Trans = new work(*C);
  tableLoader* loader = new tableLoader();
  
  char* drop = (char *) "DROP TABLE IF EXISTS PLAYER, TEAM, STATE, COLOR;";
  Trans->exec(drop);
  Trans->exec(loader->getPlayerTable());
  Trans->exec(loader->getTeamTable());
  Trans->exec(loader->getStateTable());
  Trans->exec(loader->getColorTable());
  
  Trans->commit();

  
  exercise(C);


  //Close database connection
  C->disconnect();

  return 0;
}


