#include "struct.h"

#ifndef SCORE_H
#define SCORE_H

int getScore(Game* game);
int inPos(int x , int y, Position* positions,int nbPos);
int Add_Case_And_Check_Around(Game* game,char lettre,int x, int y,Position* positions,int* nbPos);

#endif
