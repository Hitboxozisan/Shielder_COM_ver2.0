#include "Pch.h"
#include "Player.h"

#include "Shield.h"


#include "ModelManager.h"
#include "KeyManager.h"
#include "DeltaTime.h"

using namespace My3dLib;

const float Player::HIT_POINT = 100.0f;
const float Player::DECREMENT_HIT_POINT = 5.0f;
const float Player::COLLIDE_RADIUS = 50.0f;
const float Player::NORMAL_SPEED = 5.0f;
const float Player::DEFENSE_SPEED = 1.0f;
const float Player::JUST_DEFENSE_TIME = 0.1f;
const float Player::NORMAL_DEFENSE_TIME = 0.16f;
const float Player::STOP_VELOCITY = 0.5f;
const float Player::HIT_OTHER_CHARACTER_DIRECTION_Y = 1.5f;
const float Player::GRAVITY = 1.0f;
const float Player::FRICTION_FORCE = 0.1f;
const float Player::TRUNK_POINT = 100.0f;
const float Player::INCREASE_TRUNK_POINT = 5.0f;
const float Player::RIGOR_TIME = 5.0f;
const float Player::INVINCIBLE_TIME = 5.0f;
const float Player::DEFENCE_INTERVAL = 0.5f;

/// <summary>
/// コンストラクタ
/// </summary>
Player::Player(BulletCreater* const inBulletCreater)
	:Character(inBulletCreater)
	,state()
	,defenceInterval(0.0f)
	,justDefenceTime()
	,normalDefenceTime()
	,isDefense()
	,pUpdate(nullptr)
{
}

/// <summary>
/// デストラクタ
/// </summary>
Player::~Player()
{
	if (modelHandle != NULL)
	{
		Finalize();
	}
	
}

/// <summary>
/// 初期化処理
/// </summary>
void Player::Initialize()
{
	//モデルの読み込み
	modelHandle = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::PLAYER));
	//読み込み失敗でエラー
	if (modelHandle < 0)
	{
		printfDx("モデルデータの読み込み_Player\n");
	}

	state = NORMAL;
	pUpdate = &Player::UpdateNormal;

	position = VGet(2000.0f, 0.0f, 100.0f);
	nextPosition = position;
	direction = ZERO_VECTOR;
	nextDirction = direction;
	
	isDefense = false;
	noDrawFrame = false;

	hitPoint = HIT_POINT;
	speed = NORMAL_SPEED;

	velocity = ZERO_VECTOR;
	inputDirection = ZERO_VECTOR;

	trunkPoint = 0.0f;

	invincibleTime = 5.0f;

	//位置を設定
	MV1SetPosition(modelHandle, position);
	MV1SetScale(modelHandle, VGet(0.5f, 0.5f, 0.5f));


	//当たり判定球を設定
	collisionSphere.localCenter = VGet(0.0f, 0.0f, 0.0f);
	collisionSphere.radius = COLLIDE_RADIUS;
	collisionSphere.worldCenter = position;

	shield = nullptr;
}

/// <summary>
/// 更新処理
/// </summary>
void Player::Update()
{
	invincibleTime += DeltaTime::GetInstace().GetDeltaTime();
	defenceInterval += DeltaTime::GetInstace().GetDeltaTime();
	if (pUpdate != nullptr)
	{
		(this->*pUpdate)();			//状態ごとの更新処理
	}

	//体力が尽きたら死亡する
	if (hitPoint <= 0.0f)
	{
		WaitTimer(1000);				//一秒止める
		state = DEAD;
	}
}

/// <summary>
/// 描画処理
/// </summary>
void Player::Draw()
{
	//描画しないフレームなら描画しない
	if (noDrawFrame)
	{
		return;
	}

	MV1DrawModel(modelHandle);			//3Dモデルの描画
	if (shield != nullptr)
	{
		shield->Draw();					//盾の描画
		DrawFormatString(50, 50, GetColor(255, 255, 255), "DefenseCount : %f", shield->GetDefenseCount(), TRUE);
	}

	//デバッグ用
	DrawFormatString(50, 210, GetColor(255, 255, 255), "Invincible : %f", this->GetInvincibleTime());

	//当たり判定デバック描画
	DrawSphere3D(collisionSphere.worldCenter, collisionSphere.radius,
		8, GetColor(0, 255, 0), 0, FALSE);


}

void Player::ReleaseInvincible()
{
	if (invincibleTime > INVINCIBLE_TIME)
	{
		noDrawFrame = false;
	}
}

/// <summary>
/// //盾の耐久値が限界に達した
/// </summary>
void Player::BreakShield()
{
	float emplaceTime{0.0f};
	emplaceTime += DeltaTime::GetInstace().GetDeltaTime();

	//エフェクト再生

	//一定時間経過すると解除する
	if(emplaceTime >= RIGOR_TIME)
	{ 
		state = NORMAL;
	}
}

/// <summary>
/// 他のキャラクターと接触した
/// </summary>
/// <param name="forceDirection">吹き飛ばす量</param>
void Player::OnHitOtherCharacter(const VECTOR& forceDirection)
{
	//前回のvelocityをリセットする
	velocity = ZERO_VECTOR;
	invincibleTime = 0.0f;					//無敵時間を初期化

	VECTOR force = forceDirection;
	force.y = HIT_OTHER_CHARACTER_DIRECTION_Y;

	force = VScale(force, 8.0f);
	force.z = 0.0f;

	velocity = VAdd(velocity, force);
	hitPoint -= DECREMENT_HIT_POINT;		//体力を減少させる
	state = DAMAGE;
	pUpdate = &Player::UpdateDamage;
}

/// <summary>
/// 盾が他のキャラクターと接触した
/// </summary>
/// <param name="adjust">吹き飛ばす量</param>
void Player::OnHitShield(const VECTOR& adjust)
{
	//前回のvelocityをリセットする
	velocity = ZERO_VECTOR;
	invincibleTime = 0.0f;			//無敵時間を発生させる

	VECTOR force = adjust;
	force.y = 0.0f;			//変な方向に動かないようにする
	

	//ガードしたタイミングによって後退させる量を変化させる
	if (shield->GetDefenseCount() <= JUST_DEFENSE_TIME)
	{
		//ジャストガードなら小さく後退させる
		force = VScale(force, 3.0f);
		//体幹ゲージを減らす
		trunkPoint += INCREASE_TRUNK_POINT * 0.5;
	}
	else
	{
		//ジャストガードじゃないなら大きく後退させる
		force = VScale(force, 8.0f);
		//体幹ゲージを減らす
		trunkPoint += INCREASE_TRUNK_POINT * 1.0f;
	}

	force.z = 0.0f;			//変な方向に動かないようにする

	velocity = VAdd(velocity, force);
	//耐久値が限界なら硬直状態に遷移させる
	if (trunkPoint >= TRUNK_POINT)
	{
		state = RIGOR;
		pUpdate = &Player::UpdateRigor;
	}
	else
	{
		state = SLIDE;
		pUpdate = &Player::UpdateSlide;
	}
	
}

/// <summary>
/// 盾とエネミーの弾が当たった
/// </summary>
/// <param name="adjust"></param>
void Player::OnHitShieldWithBullet(const VECTOR& adjust)
{
}

/// <summary>
/// 生きているか
/// </summary>
/// <returns></returns>
const bool Player::IsAlive() const
{
	//存在しないなら死んでいる状態にする
	if (state == NONE ||
		state == DEAD)
	{
		return false;
	}

	return true;
}


/// <summary>
/// 接触できる状態か
/// </summary>
/// <returns></returns>
//const bool Player::IsCollidableState() const
//{
//	//接触できる状態なら
//	if (state == NORMAL ||
//		state == DEFENSE)
//	{
//		return true;
//	}
//
//	return false;
//}

/// <summary>
/// Normal状態の更新処理
/// </summary>
void Player::UpdateNormal()
{
	InputAction();
	Move();
}

/// <summary>
/// Defence状態の更新処理
/// </summary>
void Player::UpdateDefence()
{
	InputAction();
	Move();

	Defense();
}

void Player::UpdateSlide()
{
	Defense();
	Slide();
}

void Player::UpdateDamage()
{
	Damage();
}

void Player::UpdateRigor()
{
	BreakShield();
}

void Player::Move()
{
	if (!VSquareSize(inputDirection) == 0.0f)
	{
		nextDirction = VNorm(inputDirection);
	}
	else
	{
		nextDirction = inputDirection;
	}

	nextPosition = VAdd(position, VScale(nextDirction, speed));
}

void Player::MoveFinish()
{
	//前フレームの位置を更新
	prevPosition = position;
	//前フレームの向きを更新
	prevDirection = direction;
	position = nextPosition;
	direction = nextDirction;

	//位置を設定
	MV1SetPosition(modelHandle, position);
	
	//移動キーを押していない場合は向きを固定する
	if (!VSquareSize(inputDirection) == 0.0f)
	{
		MV1SetRotationYUseDir(modelHandle, direction, 0.0f);
	}
}

void Player::Jump()
{
	
}

void Player::Defense()
{
	if (shield != nullptr)
	{
		//盾を生成
		shield->Activate(position, direction, prevDirection);
		shield->Update();
		shield->OnHitOtherCharacter();
	}
}

/// <summary>
/// ガード成功時
/// </summary>
void Player::Slide()
{
	//エフェクト生成

	
	//滑らせる
	if (velocity.x <= 0.0f)
	{
		velocity.x += FRICTION_FORCE;
	}
	else
	{
		velocity.x -= FRICTION_FORCE;
	}
	

	//止まったら通常状態に戻る
	if (VSquareSize(velocity) <= STOP_VELOCITY)
	{
		velocity = ZERO_VECTOR;
		state = NORMAL;
		pUpdate = &Player::UpdateNormal;
	}

	nextPosition = VAdd(nextPosition, velocity);
}

/// <summary>
/// ダメージ処理
/// </summary>
void Player::Damage()
{
	noDrawFrame = !noDrawFrame;		//2回に1回描画しない

	//エフェクト生成


	nextPosition = VAdd(nextPosition, velocity);

	velocity.y -= GRAVITY;

	if (nextPosition.y <= 0.0f)
	{
		nextPosition.y = 0.0f;
		velocity = ZERO_VECTOR;
		state = NORMAL;
		noDrawFrame = false;
		pUpdate = &Player::UpdateNormal;
	}
}

void Player::InputAction()
{
	inputDirection = ZERO_VECTOR;
	//左右移動
	if (KeyManager::GetInstance().CheckPressed(KEY_INPUT_A) && nextPosition.x >= SCREEN_LEFTMOST)
	{
		inputDirection += LEFT * speed;
	}
	if (KeyManager::GetInstance().CheckPressed(KEY_INPUT_D) && nextPosition.x <= SCREEN_RIGHTMOST)
	{
		inputDirection += RIGHT * speed;
	}

	if (KeyManager::GetInstance().CheckPressed(KEY_INPUT_SPACE))
	{
		//ジャンプ

	}

	//防御
	if (KeyManager::GetInstance().CheckPressed(KEY_INPUT_LSHIFT))
	{
		speed = DEFENSE_SPEED;
		isDefense = true;		//防御
		CreateShield();

		pUpdate = &Player::UpdateDefence;
	}
	else
	{
		speed = NORMAL_SPEED;
		isDefense = false;

		pUpdate = &Player::UpdateNormal;
		shield = nullptr;			//盾を消滅させる
	}

	
}

void Player::CreateShield()
{
	if (shield == nullptr)
	{
		shield = new Shield;
		shield->Initialize(prevDirection);
		state = DEFENSE;
	}
}
