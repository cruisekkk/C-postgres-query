#include "exerciser.h"

// my exerciser
// test the robustness of my program
void exercise(connection* C)
{
  //cout << "start exercise" << endl;
  add_player(C, 1, 1, "zhu", "Li", 1, 1, 1, 1, 1.0, 1.0);
  add_team(C, "A", 1, 1, 1, 1);
  add_state(C, "NC");
  add_color(C, "blue");
  //cout << "end exercise" << endl;
  //cout << "start q1" << endl;
  query1(C, 1, 50, 10, 0, 0, 75, 1, 1, 80, 0, 0, 55, 1, 1.0, 10.0, 0, 0.0, 6.0);
  //cout << "start q2" << endl;
  query2(C, "Orange");
  //cout << "start q3" << endl;
  query3(C, "Duke");
  //cout << "start q4" << endl;
  query4(C, "Shaun", "Belbey");
  //cout << "start q5" << endl;
  query5(C, 10);
}
