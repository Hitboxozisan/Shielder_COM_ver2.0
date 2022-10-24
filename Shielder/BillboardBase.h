#pragma once
class BillboardBase
{
public:
	BillboardBase();
	virtual ~BillboardBase();

    void Initialize(const int* inGraphicPointer);
    void Finalize();
    virtual void Activate(const VECTOR& creatorPosition, float creatorSize) = 0;
    void Deactivate();
    void Update();
    virtual void Draw(const VECTOR& inPosition);

    bool GetExist() const;    // 存在しているかどうかを返す

protected:
    static const float DEFAULT_GRAPHIC_CENTER; // デフォルトの画像の中心(0.0f～1.0f、通常は0.5f)

    VECTOR     position;       // 現在の座標
    const int* graphicPointer; // 画像のポインタ
    float      size;           // 現在の大きさ(画像)
    bool       exist;          // 存在しているか
    int        existFrame; // 存在できる残りフレーム

private:
    // 使用を禁止する
    BillboardBase(const BillboardBase&);  // コピーコンストラクタ
    void operator=(const BillboardBase&); // コピー代入演算子

    virtual void UpdateEach() = 0; // 子クラスそれぞれの更新処理

};

