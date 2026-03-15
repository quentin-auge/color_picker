#pragma once
#include "RTTTLPlayer.h"

const Song ALL_SONGS[] = {
  "Tetris:d=4,o=5,b=144:e,8b4,8c,d,8c,8b4,a4,8a4,8c,e,8d,8c,b4.,8c,d,e,c,a4,a4,p,8p,d,8f,a,8g,8f,e.,8c,e,8d,8c,b4,8b4,8c,d,e,c,a4,a4,p,2e,2c,2d,2b4,2c,2a4,1b4,2e,2c,2d,2b4,c,e,2a,1g#,e,8b4,8c,d,8c,8b4,a4,8a4,8c,e,8d,8c,b4.,8c,d,e,c,a4,a4,p,8p,d,8f,a,8g,8f,8p,e,8c,e,8d,8c,8p,b4,8c,d,e,8p,c,8a4,a4,p",
  "Mario:d=4,o=5,b=200:p,8g,8f#,8f,d#,8e,8p,8g#4,8a4,8c4,8p,8a4,8c,8d,p,d#,8p,d.,2c,2p,8c,c,8c,8p,8c,d,8e,c,8a4,2g4,8c,c,8c,8p,8c,8d,8e,1p,8c,c,8c,8p,8c,d,8e,c,8a4,2g4,8e,8e,8p,8e,8p,8c,e,g,p,g4,p,c.,8g4,p,e4.,a4,b4,8a#4,a4,g4.,e.,g.,a,8f,8g,8p,e,8c,8d,b4.,c.,8g4,p,e4.,a4,b4,8a#4,a4,g4.,e.,g.,a,8f,8g,8p,e,8c,8d,b4.,8e,c,8g4,p,g#4,8a4,f,8f,2a4,d.,a.,a.,a.,g.,f.,8e,c,8a4,2g4,8e,c,8g4,p,g#4,8a4,f,8f,2a4,8b4,f,8f,f.,e.,d.,8c,e4,8e4,2c4",
  "Zelda:d=4,o=5,b=88:a#4,f4.,8a#4,16a#4,16c,16d,16d#,2f,8f,8f,8f,16f#,16g#,a#..,8a#,8a#,8g#,16f#,g#.,16f#,2f,f,d#.,16f,2f#,8f,8d#,c#.,16d#,2f,8d#,8c#,c.,16d,2e,8g,16f,16f4,16f4,16f4,16f4,16f4,16f4,16f4,8f4,16f4,8f4,a#4,f4.,8a#4,16a#4,16c,16d,16d#,2f,8f,8f,8f,16f#,16g#,a#..,c6,c6,2a,f,f#..,a#,a,2f,f,f#..,a#,a,2f,d,d#..,f#,f,2c#,a#,c.,16d,2e,8g,16f,16f4,16f4,16f4,16f4,16f4,16f4,16f4,8f4,16f4,8f4",
  "StarWars:d=4,o=5,b=108:8a#4,8a#4,8a#4,2f,2c6,8a#,8a,8g,2f6,c6,8a#,8a,8g,2f6,c6,8a#,8a,8a#,2g,8c,8c,8c,2f,2c6,8a#,8a,8g,2f6,c6,8a#,8a,8g,2f6,c6,8a#,8a,8a#,2g,c.,16c,d.,8d,8a#,8a,8g,8f,8f,8g,8a,g,8d,e,c.,16c,d.,8d,8a#,8a,8g,8f,c6.,16g,2g,8p,8c,d.,8d,8a#,8a,8g,8f,8f,8g,8a,g,8d,e,c6.,16c6,f6,8d#6,c#6,8c6,a#,8g#,g,8f,1c6",
  "Indiana Jones:d=4,o=5,b=250:e,8p,8f,8g,8p,1c6,8p.,d,8p,8e,1f,p.,g,8p,8a,8b,8p,1f6,p,a,8p,8b,2c6,2d6,2e6,e,8p,8f,8g,8p,1c6,p,d6,8p,8e6,1f.6,g,8p,8g,e.6,8p,d6,8p,8g,e.6,8p,d6,8p,8g,f.6,8p,e6,8p,8d6,2c6",
  "Birthday:d=4,o=4,b=140:c,8c,d.,c.,f.,e..,c,8c,d.,c.,g.,f..,c,8c,c5.,a.,f.,e.,d.,a#,8a#,a.,f.,g.,f..",
  "Christmas:d=4,o=5,b=140:c,f,8f,8g,8f,8e,d,d,d,g,8g,8a,8g,8f,e,c,c,a,8a,8a#,8a,8g,f,d,8c,8c,d,g,e,2f,c,f,8f,8g,8f,8e,d,d,d,g,8g,8a,8g,8f,e,c,c,a,8a,8a#,8a,8g,f,d,8c,8c,d,g,e,2f,c,f,f,f,2e,e,f,e,d,2c,a,a#,a,g,c6,c,8c,8c,d,g,e,2f,c,f,8f,8g,8f,8e,d,d,d,g,8g,8a,8g,8f,e,c,c,a,8a,8a#,8a,8g,f,d,8c,8c,d,g,e,2f,c,f,f,f,2e,e,f,e,d,2c,a,a#,a,g,c6,c,8c,8c,d,g,e,2f,p"
};
const int NB_SONGS = sizeof(ALL_SONGS) / sizeof(Song);
