#include "exerciser.h"

void exercise(connection* C)
{
  cout << "start exercise" << endl;
  add_player(C, 1, 1, "zhu", "Li", 1, 1, 1, 1, 1.0, 1.0);
  add_team(C, "A", 1, 1, 1, 1);
  add_state(C, "NC");
  add_color(C, "blue");
  cout << "end exercise" << endl;
  
  
}
