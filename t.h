#pragma once
#include "C:\raylib\raylib\src\raylib.h"
#include <iostream>
#include <cmath>
#include <list>
#include <string.h>

using std::cout;
using std::list;

#define RANCHO 1080
#define RALTO 720

#define CASILLA 40
#define BORDE_LEFT CASILLA*3
#define BORDE_UP CASILLA
#define BORDE_RIGHT RANCHO - CASILLA*3
#define BORDE_DOWN RALTO - CASILLA*2

#define LEFT 2 
#define UP 1
#define RIGHT 0
#define DOWN 3

#define TANKV 3
#define TANKH 60
#define TANKW 80
#define TANKDIAG sqrt((TANKH/2.f)*(TANKH/2.f) + (TANKW/2.f)*(TANKW/2.f))