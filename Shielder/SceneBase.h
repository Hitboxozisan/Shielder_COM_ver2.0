#pragma once

class SceneManager;

class SceneBase
{
public:
	SceneBase(SceneManager* const sceneManager);
	virtual ~SceneBase();

	virtual void Initialize() = 0;	//初期化処理
	virtual void Finalize() = 0;	//終了処理
	virtual void Activate() = 0;	//活性化処理
	virtual void Deactivate() = 0;	//非活性化処理
	virtual void Update() = 0;		//更新処理
	virtual void Draw() = 0;		//描画処理

protected:
	SceneManager* const parent;

private:
	SceneBase();						//デフォルトコンストラクタ
	SceneBase(const SceneBase&);		//コピーコンストラクタ
	void operator=(const SceneBase&);	//コピー代入演算子
};

