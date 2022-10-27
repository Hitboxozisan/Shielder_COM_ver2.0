#include "Pch.h"

#ifdef DEBUG
const bool IS_WINDOW_MODE = true;
#else
const bool IS_WINDOW_MODE = false;
#endif

const int  SCREEN_WIDTH = 1920;						//ウィンドウの幅
const int  SCREEN_HEIGHT = 1080;					//ウィンドウの高さ

const int SCREEN_LEFTMOST = 1100;					//画面左端座標
const int SCREEN_RIGHTMOST = 2900;					//画面右端座標

const int SCREEN_CENTER = (SCREEN_RIGHTMOST - SCREEN_LEFTMOST) / 2;	//画面中心座標

const VECTOR ZERO_VECTOR = { 0.0f, 0.0f, 0.0f };	//ゼロベクトル

const VECTOR RIGHT = { 1.0f, 0.0f, 0.0f };			//右
const VECTOR LEFT = { -1.0f, 0.0f, 0.0f };			//左