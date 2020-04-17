#include "query_funcs.h"


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


void add_state(connection *C, string name)
{
  string s = "";
  work* Trans = new work(*C);
  s += "INSERT INTO state VALUES( DEFAULT, '";
  s += to_string(name) + "');";

  Trans->exec(s);
  Trans->commit();
}


void add_color(connection *C, string name)
{
  string s = "";
  work* Trans = new work(*C);
  s += "INSERT INTO state VALUES( DEFAULT, '";
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
}


void query2(connection *C, string team_color)
{
}


void query3(connection *C, string team_name)
{
}


void query4(connection *C, string team_state, string team_color)
{
}


void query5(connection *C, int num_wins)
{
}
