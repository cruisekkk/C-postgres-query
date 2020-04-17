
// This class help main function provide the initialization command in sql
// by using 'create'
class tableLoader{
private:
  // protect the command, just for external invoking
  char* player;
  char* team;
  char* state;
  char* color;
public:
  
  tableLoader(){
    player = (char *) "CREATE TABLE PLAYER(" 
      "PLAYER_ID 	SERIAL	PRIMARY KEY," // primary key is both of unique and not null
      "TEAM_ID	INT	NOT NULL,"
      "UNIFORM_NUM	INT NOT NULL," 
      "FIRST_NAME	TEXT	NOT NULL," 
      "LAST_NAME	TEXT	NOT NULL," 
      "MPG	INT	NOT NULL," 
      "PPG	INT	NOT NULL," 
      "RPG	INT	NOT NULL," 
      "APG	INT     NOT NULL," 
      "SPG	NUMERIC	NOT NULL," 
      "BPG	NUMERIC NOT NULL);";
    
    team = (char *) "CREATE TABLE TEAM(" 
      "TEAM_ID	SERIAL PRIMARY KEY," 
      "NAME     TEXT	NOT NULL," 
      "STATE_ID	INT	NOT NULL ," 
      "COLOR_ID	INT	NOT NULL ," 
      "WINS	INT	NOT NULL,"
      "LOSSES	INT	NOT NULL);";
    
    state = (char *) "CREATE TABLE STATE("
      "STATE_ID	SERIAL  PRIMARY KEY,"
      "NAME     TEXT	NOT NULL);";

    color = (char *) "CREATE TABLE COLOR("
      "COLOR_ID	SERIAL  PRIMARY KEY,"
      "NAME	TEXT    NOT NULL);";
  }
  
  char* getPlayerTable(){
    return player;
  }

  char* getTeamTable(){
    return team;
  }

  char* getStateTable(){
    return state;
  }
  
  char* getColorTable(){
    return color;
  }
};
