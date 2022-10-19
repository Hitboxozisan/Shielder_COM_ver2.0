#pragma once
class KeyManager final
{
public:
    static KeyManager& GetInstance();// アドレスを返す

    void Update();

    bool CheckPressed(int keyCode) const;     // キーが押されているか
    bool CheckJustPressed(int keyCode) const; // キーが押された瞬間か
    bool CheckRelease(int keyCode) const;     // キーが離されたか

    int  GetKeyReleaseCount() const; // 連続キー入力がないカウントを返す
private:
    // 外部での実行を禁止する
    KeyManager();                        // コンストラクタ
    KeyManager(const KeyManager&);     // コピーコンストラクタ
    void operator=(const KeyManager&); // 代入演算子
    ~KeyManager();                       // デストラクタ

    char currentState[256];          // 現在のキー押下状態
    char prevState[256];             // 前フレームのキー押下状態
    int  allKeyReleaseCount;           // 連続キー入力がないカウント
};

