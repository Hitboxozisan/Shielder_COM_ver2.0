#pragma once

extern const bool IS_WINDOW_MODE;		//ウィンドウモードか

extern const int  SCREEN_WIDTH;			//ウィンドウの幅
extern const int  SCREEN_HEIGHT;		//ウィンドウの高さ

extern const int SCREEN_LEFTMOST;		//画面左端座標
extern const int SCREEN_RIGHTMOST;		//画面右端座標

extern const int SCREEN_CENTER;			//画面中心座標

extern const VECTOR ZERO_VECTOR;		//ゼロベクトル

extern const VECTOR RIGHT;
extern const VECTOR LEFT;


template <typename T>
inline void SafeDelete(T*& p)   // ポインタの参照渡し
{
    // NULLチェックは不要
    delete (p);
    (p) = nullptr;

}