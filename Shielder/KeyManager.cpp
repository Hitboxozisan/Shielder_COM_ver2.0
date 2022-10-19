#include "KeyManager.h"
#include "Pch.h"

#include <chrono>

//=========================
// コンストラクタ
//=========================
KeyManager::KeyManager()
    : currentState()
    , prevState()
    , allKeyReleaseCount()
{
    // 処理なし
}
//=========================
// コピーコンストラクタ
//=========================
KeyManager::KeyManager(const KeyManager&)
{
    // 使用しない
}
//=========================
// 代入演算子
//=========================
void KeyManager::operator=(const KeyManager&)
{
    // 使用しない
}

//=========================
// デストラクタ
//=========================
KeyManager::~KeyManager()
{
    // 処理なし
}

//=========================
// アドレス生成と参照返し
//=========================
KeyManager& KeyManager::GetInstance()
{
    static KeyManager keyManager;
    return keyManager;
}

//=========================
// 更新処理
//=========================
void KeyManager::Update()
{
    for (int i = 0; i < 256; ++i)
    {
        prevState[i] = currentState[i]; // prevを更新
    }

    GetHitKeyStateAll(currentState);  // currentを更新

    // 何かキーが押されていたらカウントリセット
    for (int i = 0; i < 256; ++i)
    {
        if (currentState[i])
        {
            allKeyReleaseCount = 0;
            return;
        }
    }

    ++allKeyReleaseCount;
}

//=========================
// キーが押されているか
//=========================
bool KeyManager::CheckPressed(int keyCode) const
{
    if (currentState[keyCode] == 0)
    {
        return false;   // 現フレームで押されていない
    }
    return true;    // 現フレームで押されている
}

//=========================
// キーが初めて押された瞬間か
//=========================
bool KeyManager::CheckJustPressed(int keyCode) const
{
    if (prevState[keyCode] == 1)
    {
        return false;   // 前フレームで押されている
    }
    if (currentState[keyCode] == 0)
    {
        return false;   // 現フレームで押されていない
    }

    return true;    // 現フレームで初めて押された
}

//=========================
// キーが離されたか
//=========================
bool KeyManager::CheckRelease(int keyCode) const
{
    if (prevState[keyCode] == 0)
    {
        return false;   // 前フレームで押されていない
    }
    if (currentState[keyCode] == 1)
    {
        return false;   // 現フレームで押されている
    }

    return true;    // 現フレームでキーは離された
}

//=========================
// 前回のキー入力からのカウント
//=========================
int KeyManager::GetKeyReleaseCount() const
{
    return allKeyReleaseCount;
}
