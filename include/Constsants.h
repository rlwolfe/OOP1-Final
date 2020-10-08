#pragma once

const char WALL = '#';
const char STONE = '@';
const char BONUS = '+';
const char DIGGER = '/';
const char DIAMOND = 'D'; 
const char MONSTER = '!';

const int BEGIN_NUMBER_OF_LIVES = 3;
const int FIRST_LEVEL = 1;

const int SCREEN_WIDTH = 1600;
const int SCREEN_HEIGHT = 800;
const int MOV_CNTR_SQ_DIST = 10;

const int NO_MORE_LIVES = 0;
const int EMPTY_SPACE_SIZE = 80;
const int CHARACTER_SIZE = 70;

const int NUM_DIFF_BONUSES = 3;
const int BONUS_MSG_CHAR_SIZE = 20;

const int UNLIMTED = -1;
const int SECONDS_FOR_MSG = 3;

const int PTS_UPPER_BOUND = 40;
const int PTS_LOWER_BOUND = 10;

const int STNS_UPPER_BOUND = 4;
const int STNS_LOWER_BOUND = 1;

const int TIME_UPPER_BOUND = 20;
const int TIME_LOWER_BOUND = 5;

const int DIAMOND_PTS = 15;

const int DIGR_SPEED_IN_PXLS = 80; 
const int MONST_SPEED_IN_PXLS = 35;

const double SPACE_BW_MSG = 1.5;
const double RATIO_BW_MOVABLE = 0.8333;

enum characterDirection { left, right, up, down };