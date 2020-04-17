#include "query_funcs.h"

// add a single player relationship(tuple) into database
void add_player(connection *C, int team_id, int jersey_num, string first_name, string last_name,
                int mpg, int ppg, int rpg, int apg, double spg, double bpg)
{
  string s = "";
  work* Trans = new work(*C);
  s += "INSERT INTO player VALUES( DEFAULT, '";
  s += to_string(team_id) + "', '";
  s += to_string(jersey_num) + "', '";
  s += to_string(first_name) + "', '";
  s += to_string(last_name) + "', '";
  s += to_string(mpg) + "', '";
  s += to_string(ppg) + "', '";
  s += to_string(rpg) + "', '";
  s += to_string(apg) + "', '";
  s += to_string(spg) + "', '";
  s += to_string(bpg) + "');";

  Trans->exec(s);
  Trans->commit();
}

// add a single team relationship(tuple) into database
void add_team(connection *C, string name, int state_id, int color_id, int wins, int losses)
{
  string s = "";
  work* Trans = new work(*C);
  s += "INSERT INTO team VALUES( DEFAULT, '";
  s += to_string(name) + "', '";
  s += to_string(state_id) + "', '";
  s += to_string(color_id) + "', '";
  s += to_string(wins) + "', '";
  s += to_string(losses) + "');";

  Trans->exec(s);
  Trans->commit();
}

// add a single state relationship(tuple) into database
void add_state(connection *C, string name)
{
  string s = "";
  work* Trans = new work(*C);
  s += "INSERT INTO state VALUES( DEFAULT, '";
  s += to_string(name) + "');";

  Trans->exec(s);
  Trans->commit();
}

// add a single color relationship(tuple) into database
void add_color(connection *C, string name)
{
  string s = "";
  work* Trans = new work(*C);
  s += "INSERT INTO color VALUES( DEFAULT, '";
  s += to_string(name) + "');";

  Trans->exec(s);
  Trans->commit();
}


void query1(connection *C,
	    int use_mpg, int min_mpg, int max_mpg,
            int use_ppg, int min_ppg, int max_ppg,
            int use_rpg, int min_rpg, int max_rpg,
            int use_apg, int min_apg, int max_apg,
            int use_spg, double min_spg, double max_spg,
            int use_bpg, double min_bpg, double max_bpg
            )
{
  // this nontransaction class is for read activity in the database
  // may not necessary folow the integrity
  nontransaction* NonTrans;
  NonTrans = new nontransaction(*C);
  
  vector<string> indicators{"mpg", "ppg", "rpg", "apg", "spg", "bpg"};
  vector<int> mask{use_mpg, use_ppg, use_rpg, use_apg, use_spg, use_bpg};
  vector<double> min{(double)min_mpg, (double)min_ppg, (double)min_rpg, (double)min_apg, min_spg, min_bpg};
  vector<double> max{(double)max_mpg, (double)max_ppg, (double)max_rpg, (double)max_apg, max_spg, max_bpg};

  string s = "";
  s += "SELECT * FROM PLAYER ";
  int sign = 0;
  for (size_t i = 0; i < indicators.size(); ++i){
    if (mask[i] == 0){
      continue;
    }
    if (sign == 1){
      s += " AND ";
    }
    if (mask[i] == 1 && sign == 0){
      sign = 1;
      s += "WHERE";
    }
    s += "( " + indicators[i] + " >= " + to_string(min[i]) + " AND " + indicators[i] + " <= " + to_string(max[i]) + " )";

    if(i < 5 && mask[i+1] != 0){
      s += " AND";
    }
  }
  s += ";";
  
  result* output = new result(NonTrans->exec(s));
  // display the result
  // part 1: column names
  cout << "PLAYER_ID TEAM_ID UNIFORM_NUM FIRST_NAME LAST_NAME MPG PPG RPG APG SPG BPG" << endl;	
  // part 2: tuples that satisfied the condition
  for (result::const_iterator it = output->begin(); it != output->end(); ++it) {
    cout<<it[0]<<" "<<it[1]<<" "<<it[2]<<" "<<it[3]<<" "<<it[4]<<" ";
    cout<<it[5]<<" "<<it[6]<<" "<<it[7]<<" "<<it[8]<<" "<<it[9]<<" "<<it[10]<< endl;
  }
  NonTrans->commit();
    
}


void query2(connection *C, string team_color)
{
  nontransaction* NonTrans;
  NonTrans = new nontransaction(*C);
  string s = "";
  
  s += "SELECT TEAM.NAME FROM TEAM, COLOR WHERE COLOR.NAME = '" + team_color + "' AND COLOR.COLOR_ID = TEAM.COLOR_ID;";

  result* output = new result( NonTrans->exec(s));
  cout << "Name" << endl;
  for (result::const_iterator it = output->begin(); it != output->end(); ++it) {
    cout << it[0] << endl;
  }
  NonTrans->commit();
}


void query3(connection *C, string team_name)
{
  nontransaction* NonTrans;
  NonTrans = new nontransaction(*C);
  string s = "";
  
  s += "SELECT PLAYER.FIRST_NAME, PLAYER.LAST_NAME ";
  s += "FROM PLAYER, TEAM ";
  s += "WHERE TEAM.NAME = '" + team_name + "' AND TEAM.TEAM_ID = PLAYER.TEAM_ID ";
  s += "ORDER BY PPG DESC;";
  result* output = new result(NonTrans->exec(s));
  
  cout << "FIRST_NAME LAST_NAME" << endl;
  for (result::const_iterator it = output->begin(); it != output->end(); ++it) {
    cout << it[0] << " " << it[1] << endl;
  }
  
  NonTrans->commit();
}


void query4(connection *C, string team_state, string team_color)
{
  nontransaction* NonTrans;
  NonTrans = new nontransaction(*C);
  
  string s = "";
  
  s += "SELECT PLAYER.FIRST_NAME, PLAYER.LAST_NAME, PLAYER.UNIFORM_NUM ";
  s += "FROM PLAYER, TEAM, STATE, COLOR ";
  s += "WHERE STATE.NAME = '" + team_state + "' AND COLOR.NAME = '" + team_color + "' ";
  s += "AND PLAYER.TEAM_ID = TEAM.TEAM_ID AND TEAM.STATE_ID = STATE.STATE_ID AND TEAM.COLOR_ID = COLOR.COLOR_ID;";
  result* output = new result(NonTrans->exec(s));
  
  cout << "FIRST_NAME LAST_NAME UNIFORM_NUM" << endl;
  for (result::const_iterator it = output->begin(); it != output->end(); ++it) {
    cout << it[0] << " " << it[1] << " " << it[2] << endl;
  }
  
  NonTrans->commit();
}


void query5(connection *C, int num_wins)
{
  nontransaction* NonTrans;
  NonTrans = new nontransaction(*C);
  string s;
  
  s += "SELECT PLAYER.FIRST_NAME, PLAYER.LAST_NAME, TEAM.NAME, TEAM.WINS FROM PLAYER, TEAM ";
  s += "WHERE TEAM.WINS > " + to_string(num_wins) + " AND PLAYER.TEAM_ID = TEAM.TEAM_ID;";
  result* output = new result(NonTrans->exec(s));

  cout << "FIRST_NAME LAST_NAME TEAM_NAME WINS" << endl;
  for (result::const_iterator it = output->begin(); it != output->end(); ++it) {
    cout << it[0] << " " << it[1] << " " << it[2] << " " << it[3] << endl;
  }
  
  NonTrans->commit();
}
