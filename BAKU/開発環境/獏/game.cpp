////////////////////////////////////////////////////////////////////////////////
//
//Contents	: ゲーム画面の処理 [game.cpp]
//Author	: ShotaFuruichi
//Since		: 2020/10/30
//
////////////////////////////////////////////////////////////////////////////////
#include "game.h"
#include "Billboard.h"
#include "bullet.h"
#include "camera.h"
#include "light.h"
#include "input.h"
#include "meshfield.h"
#include "player.h"
#include "fade.h"
#include "object.h"
#include "polygon.h"
#include "shadow.h"
#include "wall.h"
#include "xinput_pad.h"
#include "enemy.h"
#include "EnemyAttack.h"
#include "UI.h"
#include "effect.h"
#include "circle.h"

////////////////////////////////////////////////////////////////////////////////
//グローバル変数
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//ゲーム画面の初期化処理
////////////////////////////////////////////////////////////////////////////////
HRESULT InitGame(void)
{
	//カメラの初期化
	InitCamera();

	//ライトの初期化
	InitLight();

	//ポリゴンの初期化
	InitMeshfield();

	//壁の初期化
	InitWall();

	//ビルボードの初期化
	InitBillboard();

	//影の初期化
	InitShadow();

	//弾の初期化
	InitBullet();

	//オブジェクトの初期化
	InitObject();

	//プレイヤーの初期化
	InitPlayer();

	//敵の初期化
	InitEnemy();

	//敵の攻撃の初期化
	InitEnemyAttack();

	//魔法陣の初期化
	InitCircle();

	//エフェクトの初期化
	InitEffect();

	//UIの初期化
	InitUI();

	return S_OK;
}

////////////////////////////////////////////////////////////////////////////////
//終了処理
////////////////////////////////////////////////////////////////////////////////
void UninitGame(void)
{
	//UIの終了
	UninitUI();

	//エフェクトの終了
	UninitEffect();

	//魔法陣の終了
	UninitCircle();

	//敵の攻撃の終了
	UninitEnemyAttack();

	//敵の終了
	UninitEnemy();

	//プレイヤーの終了
	UninitPlayer();

	//オブジェクトの終了
	UninitObject();

	//弾の終了
	UninitBullet();

	//影の終了
	UninitShadow();

	//ビルボードの終了
	UninitBillboard();

	//壁の終了
	UninitWall();

	//ポリゴンの終了
	UninitMeshfield();

	//ライトの終了
	UninitPolygon();

	//カメラの終了
	UninitCamera();
}

////////////////////////////////////////////////////////////////////////////////
//更新処理
////////////////////////////////////////////////////////////////////////////////
void UpdateGame(void)
{
	//カメラの更新
	UpdateCamera();

	//ライトの更新
	UpdateLight();

	//ポリゴンの更新
	UpdateMeshfield();

	//壁の更新
	UpdateWall();

	//ビルボードの更新
	UpdateBillboard();

	//影の更新
	UpdateShadow();

	//弾の更新
	UpdateBullet();

	//オブジェクトの更新
	UpdateObject();

	//プレイヤーの更新
	UpdatePlayer();

	//敵の更新
	UpdateEnemy();

	//敵の攻撃の更新
	UpdateEnemyAttack();

	//魔法陣の更新
	UpdateCircle();

	//エフェクトの更新
	UpdateEffect();

	//UIの更新
	UpdateUI();

	XinputGamepad *pXinput = GetXinputGamepad();
}

////////////////////////////////////////////////////////////////////////////////
//描画処理
////////////////////////////////////////////////////////////////////////////////
void DrawGame(void)
{
	//カメラの設定
	SetCamera();

	//ポリゴンの描画
	DrawMeshfield();

	//壁の描画
	DrawWall();

	//ビルボードの更新
	DrawBillboard();

	//影の描画
	DrawShadow();

	//弾の描画
	DrawBullet();

	//オブジェクトの描画
	DrawObject();

	//プレイヤーの描画
	DrawPlayer();

	//敵の描画
	DrawEnemy();

	//敵の攻撃の描画
	DrawEnemyAttack();

	//魔法陣の更新
	DrawCircle();

	//エフェクトの描画
	DrawEffect();

	//UIの描画
	DrawUI();
}