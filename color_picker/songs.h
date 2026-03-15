#pragma once
#include "RTTTLPlayer.h"

const Song ALL_SONGS[] = {
  "Tetris:d=4,o=5,b=144:e,8b4,8c,d,8c,8b4,a4,8a4,8c,e,8d,8c,b4.,8c,d,e,c,a4,a4,p,8p,d,8f,a,8g,8f,e.,8c,e,8d,8c,b4,8b4,8c,d,e,c,a4,a4,p,2e,2c,2d,2b4,2c,2a4,1b4,2e,2c,2d,2b4,c,e,2a,1g#,e,8b4,8c,d,8c,8b4,a4,8a4,8c,e,8d,8c,b4.,8c,d,e,c,a4,a4,p,8p,d,8f,a,8g,8f,8p,e,8c,e,8d,8c,8p,b4,8c,d,e,8p,c,8a4,a4..",
  "Super Mario:d=4,o=5,b=100:16e6,16e6,32p,8e6,16c6,8e6,8g6,8p,8g,8p,8c6,16p,8g,16p,8e,16p,8a,8b,16a#,8a,16g.,16e6,16g6,8a6,16f6,8g6,8e6,16c6,16d6,8b,16p,8c6,16p,8g,16p,8e,16p,8a,8b,16a#,8a,16g.,16e6,16g6,8a6,16f6,8g6,8e6,16c6,16d6,8b,8p,16g6,16f#6,16f6,16d#6,16p,16e6,16p,16g#,16a,16c6,16p,16a,16c6,16d6,8p,16g6,16f#6,16f6,16d#6,16p,16e6,16p,16c7,16p,16c7,16c7,p,16g6,16f#6,16f6,16d#6,16p,16e6,16p,16g#,16a,16c6,16p,16a,16c6,16d6,8p,16d#6,8p,16d6,8p,16c6",
  "Zelda:d=4,o=5,b=125:a#,f.,8a#,16a#,16c6,16d6,16d#6,2f6,8p,8f6,16f.6,16f#6,16g#.6,2a#.6,16a#.6,16g#6,16f#.6,8g#.6,16f#.6,2f6,f6,8d#6,16d#6,16f6,2f#6,8f6,8d#6,8c#6,16c#6,16d#6,2f6,8d#6,8c#6,8c6,16c6,16d6,2e6,g6,1f6",
  "StarWars:d=4,o=5,b=125:8a#4,8a#4,8a#4,2f,2c6,8a#,8a,8g,2f6,c6,8a#,8a,8g,2f6,c6,8a#,8a,8a#,2g,8c,8c,8c,2f,2c6,8a#,8a,8g,2f6,c6,8a#,8a,8g,2f6,c6,8a#,8a,8a#,2g,c.,16c,d.,8d,8a#,8a,8g,8f,8f,8g,8a,g,8d,e,c.,16c,d.,8d,8a#,8a,8g,8f,c6.,16g,2g,8p,8c,d.,8d,8a#,8a,8g,8f,8f,8g,8a,g,8d,e,c6.,16c6,f6,8d#6,c#6,8c6,a#,8g#,g,8f,1c6",
  "Indiana Jones:d=4,o=5,b=250:e,8p,8f,8g,8p,1c6,8p.,d,8p,8e,1f,p.,g,8p,8a,8b,8p,1f6,p,a,8p,8b,2c6,2d6,2e6,e,8p,8f,8g,8p,1c6,p,d6,8p,8e6,1f.6,g,8p,8g,e.6,8p,d6,8p,8g,e.6,8p,d6,8p,8g,f.6,8p,e6,8p,8d6,2c6",
  "Mission Impossible:d=16,o=6,b=95:32d,32d#,32d,32d#,32d,32d#,32d,32d#,32d,32d,32d#,32e,32f,32f#,32g,g,8p,g,8p,a#,p,c7,p,g,8p,g,8p,f,p,f#,p,g,8p,g,8p,a#,p,c7,p,g,8p,g,8p,f,p,f#,p,a#,g,2d,32p,a#,g,2c#,32p,a#,g,2c,a#5,8c,2p,32p,a#5,g5,2f#,32p,a#5,g5,2f,32p,a#5,g5,2e,d#,8d",
  "OdeToJoy:d=4,o=5,b=135:e,e,f,g,g,f,e,d,c,c,d,e,e.,8d,2d,e,e,f,g,g,f,e,d,c,c,d,e,d.,8c,2c,d,d,e,c,d,8e,8f,e,c,d,8e,8f,e,d,c,d,2g4,e,e,f,g,g,f,e,d,c,c,d,e,d.,8c,2c",
  "JingleBells:o=5,d=4,b=170:b,b,b,p,b,b,b,p,b,d6,g.,8a,2b.,8p,c6,c6,c6.,8c6,c6,b,b,8b,8b,b,a,a,b,2a,2d6,b,b,b,p,b,b,b,p,b,d6,g.,8a,2b.,8p,c6,c6,c6.,8c6,c6,b,b,8b,8b,d6,d6,c6,a,1g",
  "Birthday:d=4,o=4,b=140:c,8c,d.,c.,f.,2e.,c,8c,d.,c.,g.,2f.,c,8c,c5.,a.,f.,e..,2d.,a#,8a#,a.,f.,g.,2f."
};
const int NB_SONGS = sizeof(ALL_SONGS) / sizeof(Song);
