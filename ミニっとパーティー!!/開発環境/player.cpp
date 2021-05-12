//-----------------------------------------------------------------
//
// プレイヤー (player.cpp)
// Author:Itsuki Takaiwa
//
//-----------------------------------------------------------------
#include "player.h"
#include "motion.h"
#include "meshfield.h"
#include "Bomb.h"
#include "camera.h"
#include "shadow.h"
#include "input.h"
#include "gamepad.h"
#include "motion.h"
#include "model_set.h"
#include "sound.h"
#include "chara_select_frame.h"
#include "chara.h"
#include "light.h"
#include "count_down.h"
#include "chara_select_frame.h"
#include "finish_game.h"
#include "BombCollision.h"

//-----------------------------------------------------------------
// マクロ定義
//-----------------------------------------------------------------
#define PLAYER_SIZEXZ (10)

#define MAX_BOMB (4)
#define DIS_BOMB (150)
#define EX_BOMB (50)

//-----------------------------------------------------------------
// グローバル変数
//-----------------------------------------------------------------
Player g_player[MAX_DISPLAY_CHARA];					// プレイヤー情報
int g_nNumOperationPlayer;							// 操作可能プレイヤー数
BOMB bomb[MAX_BOMB];
int g_nDisPlayer;

//-----------------------------------------------------------------
// プレイヤーの初期化処理
//-----------------------------------------------------------------
HRESULT InitPlayer(void)
{
	// 変数宣言
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// キャラ情報の取得
	Character *pCharacter = GetCharacter();

	// 操作可能なプレイヤー数の取得
	g_nNumOperationPlayer = GetnCntController();

	// キャラセレクトイメージ情報の取得
	CharaSelectFrame *pCharaSelectFrame = GetCharaSelectFrame();

	// モードの取得
	MODE mode = GetMode();

	// モードの取得
	int nNumPlayer = GetFrame();

	g_nDisPlayer = nNumPlayer;

	for (int nCntPlayer = 0; nCntPlayer < g_nDisPlayer; nCntPlayer++, pCharaSelectFrame++)
	{
		// プレイヤー情報の初期化
		for (int nCntMotion = 0; nCntMotion < MOTYONTYPE_MAX; nCntMotion++)
		{
			g_player[nCntPlayer].aMotionInfo[nCntMotion] = pCharacter->characterInfo[pCharaSelectFrame->nNumChara].aMotionInfo[nCntMotion];
		}
		g_player[nCntPlayer].nNumModel = pCharacter->characterInfo[pCharaSelectFrame->nNumChara].nNumModel;
		g_player[nCntPlayer].pos = D3DXVECTOR3(0.0f,0.0f, 0.0f);
		g_player[nCntPlayer].posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_player[nCntPlayer].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_player[nCntPlayer].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_player[nCntPlayer].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_player[nCntPlayer].bJump = false;
		g_player[nCntPlayer].state = PLAYERSTATE_NORMAL;
		g_player[nCntPlayer].MotionType = MOTIONTYPE_NEUTRAL;
		g_player[nCntPlayer].nStateCounter = 0;
		g_player[nCntPlayer].nCounterMotion = 1;
		g_player[nCntPlayer].nKey = 0;
		g_player[nCntPlayer].bLoopMotion = g_player[nCntPlayer].aMotionInfo[g_player[nCntPlayer].MotionType].bLoop;
		g_player[nCntPlayer].nNumKey = g_player[nCntPlayer].aMotionInfo[g_player[nCntPlayer].MotionType].nNumKey;
		g_player[nCntPlayer].MotionTypeBlend = MOTIONTYPE_NEUTRAL;
		g_player[nCntPlayer].bBlendMotion = false;
		g_player[nCntPlayer].nBombID = -1;

		if (mode == MODE_GAME)
		{
			g_player[nCntPlayer].bFall = false;
		}
		// プレイヤーのパーツ設定
		for (int nCntModel = 0; nCntModel < g_player[nCntPlayer].nNumModel; nCntModel++)
		{
			// モデル情報の取得
			g_player[nCntPlayer].aModel[nCntModel] = pCharacter->characterInfo[pCharaSelectFrame->nNumChara].aModel[nCntModel];

			// Xファイルの読み込み
			if (FAILED(D3DXLoadMeshFromX(g_player[nCntPlayer].aModel[nCntModel].aFileName,
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&g_player[nCntPlayer].aModel[nCntModel].pBuffMat,
				NULL,
				&g_player[nCntPlayer].aModel[nCntModel].nNumMat,
				&g_player[nCntPlayer].aModel[nCntModel].pMesh)))
			{
				return E_FAIL;
			}
		}

		// 変数宣言
		int nNumVtx;			// 頂点数
		DWORD sizeFVF;			// 頂点フォーマットのサイズ
		BYTE *pVtxBuff;			// 頂点バッファへのポインタ

		for (int nCntModel = 0; nCntModel < g_player[nCntPlayer].nNumModel; nCntModel++)
		{
			// 頂点数の取得
			nNumVtx = g_player[nCntPlayer].aModel[nCntModel].pMesh->GetNumVertices();

			// 頂点フォーマットのサイズを取得
			sizeFVF = D3DXGetFVFVertexSize(g_player[nCntPlayer].aModel[nCntModel].pMesh->GetFVF());

			// 頂点バッファのロック
			g_player[nCntPlayer].aModel[nCntModel].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

			for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
			{
				// 頂点座標の代入
				D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

				// 頂点を比較してモデルの最小値最大値を抜き出す
				if (g_player[nCntPlayer].minVecPlayer.x > vtx.x)
				{// X座標の最小値
					g_player[nCntPlayer].minVecPlayer.x = vtx.x;
				}
				else if (g_player[nCntPlayer].maxVecPlayer.x < vtx.x)
				{// X座標の最大値
					g_player[nCntPlayer].maxVecPlayer.x = vtx.x;
				}

				if (g_player[nCntPlayer].minVecPlayer.y > vtx.y)
				{// Y座標の最小値
					g_player[nCntPlayer].minVecPlayer.y = vtx.y;
				}
				else if (g_player[nCntPlayer].maxVecPlayer.y < vtx.y)
				{// Y座標の最大値
					g_player[nCntPlayer].maxVecPlayer.y = vtx.y;
				}

				if (g_player[nCntPlayer].minVecPlayer.z > vtx.z)
				{// Z座標の最小値
					g_player[nCntPlayer].minVecPlayer.z = vtx.z;
				}
				else if (g_player[nCntPlayer].maxVecPlayer.z < vtx.z)
				{// Z座標の最大値
					g_player[nCntPlayer].maxVecPlayer.z = vtx.z;
				}
				// 頂点フォーマットのサイズ文ポインタを進める
				pVtxBuff += sizeFVF;
			}
			// 頂点バッファのアンロック
			g_player[nCntPlayer].aModel[nCntModel].pMesh->UnlockVertexBuffer();
		}
	}
	return S_OK;
}

//-----------------------------------------------------------------
// プレイヤーの終了処理
//-----------------------------------------------------------------
void UninitPlayer(void)
{
	for (int nCntPlayer = 0; nCntPlayer < g_nDisPlayer; nCntPlayer++)
	{
		for (int nCnt = 0; nCnt < g_player[nCntPlayer].nNumModel; nCnt++)
		{
			// マテリアル情報の開放
			if (g_player[nCntPlayer].aModel[nCnt].pBuffMat != NULL)
			{
				g_player[nCntPlayer].aModel[nCnt].pBuffMat->Release();
				g_player[nCntPlayer].aModel[nCnt].pBuffMat = NULL;
			}

			// メッシュ情報の開放
			if (g_player[nCntPlayer].aModel[nCnt].pMesh != NULL)
			{
				g_player[nCntPlayer].aModel[nCnt].pMesh->Release();
				g_player[nCntPlayer].aModel[nCnt].pMesh = NULL;
			}
		}
	}
}

//-----------------------------------------------------------------
// プレイヤーの更新処理
//-----------------------------------------------------------------
void UpdatePlayer(void)
{
	// モードの取得
	MODE mode = GetMode();

	switch (mode)
	{
	case MODE_GAME:
		GamePlayer();
		break;

	case MODE_RESULT:
		ResultPlayer();
		break;
	}
}

//-----------------------------------------------------------------
// プレイヤーの描画処理
//-----------------------------------------------------------------
void DrawPlayer(void)
{
	// 変数宣言
	LPDIRECT3DDEVICE9 pDevice;		// デバイスへのポインタ
	D3DXMATRIX mtxRot, mtxTrans;	// 計算用マトリックス
	D3DMATERIAL9 matDef;			// 現在のマテリアル保存用
	D3DXMATERIAL *pMat;				// マテリアルデータへのポインタ

	// 変数の受け渡し
	pDevice = GetDevice();
	Light *pLight = GetLight();

	for (int nCntPlayer = 0; nCntPlayer < g_nDisPlayer; nCntPlayer++)
	{
		// ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_player[nCntPlayer].mtxWorld);

		// 向きを反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_player[nCntPlayer].rot.y, g_player[nCntPlayer].rot.x, g_player[nCntPlayer].rot.z);
		D3DXMatrixMultiply(&g_player[nCntPlayer].mtxWorld, &g_player[nCntPlayer].mtxWorld, &mtxRot);

		// 位置を反映
		D3DXMatrixTranslation(&mtxTrans, g_player[nCntPlayer].pos.x, g_player[nCntPlayer].pos.y, g_player[nCntPlayer].pos.z);
		D3DXMatrixMultiply(&g_player[nCntPlayer].mtxWorld, &g_player[nCntPlayer].mtxWorld, &mtxTrans);

		// ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_player[nCntPlayer].mtxWorld);

		// 現在のマテリアルを取得
		pDevice->GetMaterial(&matDef);

		for (int nCntModel = 0; nCntModel < g_player[nCntPlayer].nNumModel; nCntModel++)
		{
			// 変数宣言
			D3DXMATRIX mtxRotModel, mtxTransModel;		// 計算用マトリックス
			D3DXMATRIX mtxParent;						// 親のマトリックス

			// 各パーツのワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_player[nCntPlayer].aModel[nCntModel].mtxWorld);

			// 各パーツの向き
			D3DXMatrixRotationYawPitchRoll(&mtxRotModel, g_player[nCntPlayer].aModel[nCntModel].rot.y, g_player[nCntPlayer].aModel[nCntModel].rot.x, g_player[nCntPlayer].aModel[nCntModel].rot.z);
			D3DXMatrixMultiply(&g_player[nCntPlayer].aModel[nCntModel].mtxWorld, &g_player[nCntPlayer].aModel[nCntModel].mtxWorld, &mtxRotModel);

			// 各パーツの位置
			D3DXMatrixTranslation(&mtxTransModel, g_player[nCntPlayer].aModel[nCntModel].pos.x, g_player[nCntPlayer].aModel[nCntModel].pos.y, g_player[nCntPlayer].aModel[nCntModel].pos.z);
			D3DXMatrixMultiply(&g_player[nCntPlayer].aModel[nCntModel].mtxWorld, &g_player[nCntPlayer].aModel[nCntModel].mtxWorld, &mtxTransModel);

			// 各パーツの親のマトリックスを設定
			if (g_player[nCntPlayer].aModel[nCntModel].nIdxModelParent != -1)
			{
				mtxParent = g_player[nCntPlayer].aModel[g_player[nCntPlayer].aModel[nCntModel].nIdxModelParent].mtxWorld;
			}
			else
			{
				mtxParent = g_player[nCntPlayer].mtxWorld;
			}
			// 算出した各パーツのワールドマトリックスと親のマトリックスを掛け合わせる
			D3DXMatrixMultiply(&g_player[nCntPlayer].aModel[nCntModel].mtxWorld,
				&g_player[nCntPlayer].aModel[nCntModel].mtxWorld,
				&mtxParent);

			// 各パーツのマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_player[nCntPlayer].aModel[nCntModel].mtxWorld);

			// マテリアルデータへのポインタを取得
			pMat = (D3DXMATERIAL*)g_player[nCntPlayer].aModel[nCntModel].pBuffMat->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_player[nCntPlayer].aModel[nCntModel].nNumMat; nCntMat++)
			{
				// マテリアルの設定
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				// テクスチャの設定
				pDevice->SetTexture(0, g_player[nCntPlayer].aModel[nCntModel].pTexture[nCntMat]);

				// モデル(パーツ)の描画
				g_player[nCntPlayer].aModel[nCntModel].pMesh->DrawSubset(nCntMat);
			}
			// マトリックスを使用した影の描画
			MatrixShadow((int)g_player[nCntPlayer].aModel[nCntModel].nNumMat,
				g_player[nCntPlayer].aModel[nCntModel].mtxWorld, 
				g_player[nCntPlayer].PosShadow,
				g_player[nCntPlayer].aModel[nCntModel].pMesh);
		}
		// 保存していたマテリアルを戻す
		pDevice->SetMaterial(&matDef);
	}
}

//-----------------------------------------------------------------
// プレイヤーのゲーム処理
//-----------------------------------------------------------------
void GamePlayer(void)
{
	// 変数宣言
	int nCntFallPlayer = 0;		// 落ちたプレイヤー数をカウント

	for (int nCntPlayer = 0; nCntPlayer < g_nDisPlayer; nCntPlayer++)
	{
		// プレイヤーモーション
		PlayerMotion(nCntPlayer);

		if (g_player[nCntPlayer].bFall == false)
		{
			// プレイヤーの状態を判別
			StateManagerPlayer(nCntPlayer);

			// 前の座標を保存
			g_player[nCntPlayer].posOld = g_player[nCntPlayer].pos;

			// 移動量の減衰(慣性)
			g_player[nCntPlayer].move.x += (0.0f - g_player[nCntPlayer].move.x) * 0.3f;
			g_player[nCntPlayer].move.z += (0.0f - g_player[nCntPlayer].move.z) * 0.3f;

			// 重力設定
			g_player[nCntPlayer].move.y -= GRAVITY;

			// 位置の更新
			g_player[nCntPlayer].pos.x += g_player[nCntPlayer].move.x;
			g_player[nCntPlayer].pos.y += g_player[nCntPlayer].move.y;
			g_player[nCntPlayer].pos.z += g_player[nCntPlayer].move.z;

			// メッシュフィールドとの当たり判定
			bool bLand = CollisionMeshField(&g_player[nCntPlayer].pos, &g_player[nCntPlayer].posOld, g_player[nCntPlayer].nIdx, &g_player[nCntPlayer].PosShadow);

			// モデルとの当たり判定
			bool bLandModel = CollisionModelSet(&g_player[nCntPlayer].pos, &g_player[nCntPlayer].posOld, &g_player[nCntPlayer].move, &g_player[nCntPlayer].minVecPlayer, &g_player[nCntPlayer].maxVecPlayer, g_player[nCntPlayer].nIdx, &g_player[nCntPlayer].PosShadow);
			CollisionPlayer(nCntPlayer);

			// player と　bomb
			if (g_player[nCntPlayer].nBombID == -1)
			{
				BombAndPlayer(nCntPlayer);
			}

			if (bLandModel == true)
			{
				if (g_player[nCntPlayer].state == PLAYERSTATE_FLOATING)
				{// ジャンプ中のときジャンプしていない状態にする
					g_player[nCntPlayer].state = PLAYERSTATE_NORMAL;
				}

				// 移動量を0.0fにする
				g_player[nCntPlayer].move.y = 0.0f;
			}
			else if (bLandModel == false && g_player[nCntPlayer].state != PLAYERSTATE_DAMAGE)
			{
				g_player[nCntPlayer].state = PLAYERSTATE_FLOATING;
			}
			if (bLand == true)
			{
				if (g_player[nCntPlayer].nBombID != -1)
				{
					SetBombBlow(g_player[nCntPlayer].nBombID);
					g_player[nCntPlayer].nBombID = -1;
				}
				g_player[nCntPlayer].bFall = true;
				SetMotion(nCntPlayer, MOTIONTYPE_SIRIMOTI, true, 10);
			}
			if (g_player[nCntPlayer].bFall == false)
			{
				nCntFallPlayer++;
			}
		}
	}
	if (nCntFallPlayer == 1)
	{
		SetFinishGame(true);
	}
}

//-----------------------------------------------------------------
// プレイヤーのリザルト処理
//-----------------------------------------------------------------
void ResultPlayer(void)
{
	for (int nCntPlayer = 0; nCntPlayer < g_nDisPlayer; nCntPlayer++)
	{
		// プレイヤーモーション
		PlayerMotion(nCntPlayer);

		// 前の座標を保存
		g_player[nCntPlayer].posOld = g_player[nCntPlayer].pos;

		// 移動量の減衰(慣性)
		g_player[nCntPlayer].move.x += (0.0f - g_player[nCntPlayer].move.x) * 0.3f;
		g_player[nCntPlayer].move.z += (0.0f - g_player[nCntPlayer].move.z) * 0.3f;

		// 重力設定
		g_player[nCntPlayer].move.y -= GRAVITY;

		// 位置の更新
		g_player[nCntPlayer].pos.x += g_player[nCntPlayer].move.x;
		g_player[nCntPlayer].pos.y += g_player[nCntPlayer].move.y;
		g_player[nCntPlayer].pos.z += g_player[nCntPlayer].move.z;

		// メッシュフィールドとの当たり判定
		bool bLand = CollisionMeshField(&g_player[nCntPlayer].pos, &g_player[nCntPlayer].posOld, g_player[nCntPlayer].nIdx, &g_player[nCntPlayer].PosShadow);

		// モデルとの当たり判定
		bool bLandModel = CollisionModelSet(&g_player[nCntPlayer].pos, &g_player[nCntPlayer].posOld, &g_player[nCntPlayer].move, &g_player[nCntPlayer].minVecPlayer, &g_player[nCntPlayer].maxVecPlayer, g_player[nCntPlayer].nIdx, &g_player[nCntPlayer].PosShadow);

		if (bLandModel == true)
		{
			// 移動量を0.0fにする
			g_player[nCntPlayer].move.y = 0.0f;
		}
		if (g_player[nCntPlayer].bFall == true)
		{
			SetMotion(nCntPlayer, MOTIONTYPE_LOSE, true, 10);
		}
		else if (g_player[nCntPlayer].bFall == false)
		{
			SetMotion(nCntPlayer, MOTIONTYPE_WIN, true, 10);
		}
	}
}

//-----------------------------------------------------------------
// プレイヤー状態の判別
//-----------------------------------------------------------------
void StateManagerPlayer(int nCntPlayer)
{
	// プレイヤーの状態を調べる
	switch (g_player[nCntPlayer].state)
	{// 状態が通常のとき
	case PLAYERSTATE_NORMAL:
		PlayerStateNormal(nCntPlayer);
		break;
		// 状態が浮遊のとき
	case PLAYERSTATE_FLOATING:
		PlayerStateFloating(nCntPlayer);
		break;
		// 状態がダメージのとき
	case PLAYERSTATE_DAMAGE:
		PlayerStateDamage(nCntPlayer);
		break;

		// 状態がダメージのとき
	case PLAYERSTATE_THROW:
		PlayerStateThrow(nCntPlayer);
		break;
	}
}

//-----------------------------------------------------------------
// プレイヤー状態が通常の時
//-----------------------------------------------------------------
void PlayerStateNormal(int nCntPlayer)
{
	// ゲームパッド情報の取得
	DIJOYSTATE2 Controller = GetControllerPless(nCntPlayer);

	if (nCntPlayer < g_nNumOperationPlayer)
	{
		// プレイヤーの移動処理
		MovePlayer(nCntPlayer);
	}
	if (g_player[nCntPlayer].bJump == false && g_player[nCntPlayer].MotionType == MOTIONTYPE_MOVE &&
		Controller.lX == 0 && Controller.lY == 0)
	{
		// 何もしないときニュートラルモーションに設定
		SetMotion(nCntPlayer, MOTIONTYPE_NEUTRAL, true, 10);
	}
}

//-----------------------------------------------------------------
// プレイヤー状態が浮遊の時
//-----------------------------------------------------------------
void PlayerStateFloating(int nCntPlayer)
{
	if (nCntPlayer < g_nNumOperationPlayer)
	{
		// プレイヤーの移動処理
		MovePlayer(nCntPlayer);
	}
}

//-----------------------------------------------------------------
// プレイヤーがダメージ状態のとき
//-----------------------------------------------------------------
void PlayerStateDamage(int nCntPlayer)
{
	// 状態カウンタを進める
	g_player[nCntPlayer].nStateCounter++;

	// 状態カウンターが20になったとき処理
	if (g_player[nCntPlayer].nStateCounter >= 40)
	{
		// 状態をノーマルに戻す
		SetMotion(nCntPlayer, MOTIONTYPE_NEUTRAL, true, 10); 

		// 状態カウンターを0に初期化
		g_player[nCntPlayer].nStateCounter = 0;
	}
}

// 投げ状態の時
void PlayerStateThrow(int nCntPlayer)
{
	
}

//-----------------------------------------------------------------
// プレイヤーの移動処理
//-----------------------------------------------------------------
void MovePlayer(int nCntPlayer)
{
	// カウントダウン情報の取得
	int nCountDown = GetCountDown();

	// 現在の回転角を制限
	if (g_player[nCntPlayer].rotDest.y - g_player[nCntPlayer].rot.y < -D3DX_PI)
	{// -3.14fより小さくなったとき値に3.14fにする
		g_player[nCntPlayer].rotDest.y += D3DX_PI * 2.0f;
	}
	else if (g_player[nCntPlayer].rotDest.y - g_player[nCntPlayer].rot.y > D3DX_PI)
	{// 3.14fより大きくなったとき値を-3.14fにする
		g_player[nCntPlayer].rotDest.y -= D3DX_PI * 2.0f;
	}
	// 向きの更新
	g_player[nCntPlayer].rot.y += (g_player[nCntPlayer].rotDest.y - g_player[nCntPlayer].rot.y) * 0.15f;

	// 現在の回転角を制限
	if (g_player[nCntPlayer].rot.y < -D3DX_PI)
	{// -3.14fより小さくなったとき値に3.14fにする
		g_player[nCntPlayer].rot.y += D3DX_PI * 2.0f;
	}
	else if (g_player[nCntPlayer].rot.y > D3DX_PI)
	{// 3.14fより大きくなったとき値を-3.14fにする
		g_player[nCntPlayer].rot.y -= D3DX_PI * 2.0f;
	}

	if (nCountDown == 0)
	{
		// キーボード
		MovePlayerKeyboard(nCntPlayer);

		// ゲームパッド
		MovePlayerGamepad(nCntPlayer);
	}
}

////////////////////////////////////////////////////////////////////////////////
//AI移動
////////////////////////////////////////////////////////////////////////////////
void MoveAi(int nCntPlayer)
{
/*
	D3DXVECTOR3 Distance[MAX_BOMB];
	float fDis[MAX_BOMB];
	float fSize = powf(EX_BOMB, 2.0f);

	D3DXVECTOR3 vector;
	float fAngle;

	for (int nCnt = 0; nCnt < MAX_BOMB; nCnt++)
	{
		if (bomb[nCnt].bUse == true && bomb[nCnt].bHave == false && bomb[nCnt].fExplosion <= 90)
		{	//使用していて誰も持っていないあと1.5秒で爆発する爆弾が存在する場合

			//プレイヤーと爆発範囲の距離を変数に代入
			Distance[nCnt].x = (g_player[nCntPlayer].pos.x - bomb[nCnt].pos.x);
			Distance[nCnt].z = (g_player[nCntPlayer].pos.z - bomb[nCnt].pos.z);

			//プレイヤーと爆発範囲の距離を2乗
			Distance[nCnt].x = powf(Distance[nCnt].x, 2.0f);
			Distance[nCnt].z = powf(Distance[nCnt].z, 2.0f);

			//プレイヤーの大きさの分をマイナス
			Distance[nCnt].x -= powf(PLAYER_SIZEXZ, 2.0f);
			Distance[nCnt].z -= powf(PLAYER_SIZEXZ, 2.0f);

			//x座標とz座標の距離を合わせる
			fDis[nCnt] = Distance[nCnt].x + Distance[nCnt].z;

			if (fDis[nCnt] <= fSize)
			{	//プレイヤーと爆発との距離が爆発範囲以下になっているとき

				//ベクトル・角度算出
				vector = bomb[nCnt].pos - g_player[nCnt].pos;
				fAngle = atan2f(-vector.x, -vector.z);

				//移動
				g_player[nCntPlayer].pos.x += sinf(fAngle) * MOVE_PLAYER;
				g_player[nCntPlayer].pos.z += cosf(fAngle) * MOVE_PLAYER;
				g_player[nCntPlayer].rotDest.y = (fAngle += D3DX_PI);
			}
		}
	}

	if (g_player[nCntPlayer].bHaveBomb == false)
	{	//プレイヤーが爆弾を持っていない場合

		D3DXVECTOR3 vector[MAX_BOMB];
		D3DXVECTOR3 vectorA;

		float fVector[MAX_BOMB];
		float fVectorA;
		float fAngle;
		float fSpeed;
		int nCountBomb = 0;

		for (int nCnt = 0; nCnt < MAX_BOMB; nCnt++)
		{
			if (bomb[nCnt].bUse == true && bomb[nCnt].bHave == false && bomb[nCnt].fExplosion > 90)
			{	//使用していて誰も持っていない爆発までの時間が1.5秒以上ある爆弾が存在する場合

				//ベクトルとベクトルの長さの算出
				vector[nCnt] = bomb[nCnt].pos - g_player[nCntPlayer].pos;
				fVector[nCnt] = D3DXVec3Length(&D3DXVECTOR3(vector[nCnt].x, 0, vector[nCnt].z));

				vectorA = vector[nCnt];
				fVectorA = fVector[nCnt];
			}
		}

		for (int nCnt = 0; nCnt < MAX_BOMB; nCnt++)
		{
			if (bomb[nCnt].bUse == true && bomb[nCnt].bHave == false && bomb[nCnt].fExplosion > 90)
			{	//使用していて誰も持っていない爆発までの時間が1.5秒以上ある爆弾が存在する場合

				if (fVectorA > fVector[nCnt])
				{	//一番近くの爆弾を判定
					vectorA = vector[nCnt];
					fVectorA = fVector[nCnt];
				}

				//角度
				fAngle = atan2f(vectorA.x, vectorA.z);
				fSpeed = MOVE_PLAYER;

				if (fSpeed > fVectorA)
				{	//爆弾までの距離よりも移動量の方が大きい場合

					//移動量を爆弾までの距離に変更
					fSpeed = fVectorA;
				}

				nCountBomb++;
			}
		}

		if (nCountBomb == 0)
		{	//条件に当てはまる爆弾が1つもない場合

			//移動無し・角度は引き継ぐ
			fSpeed = 0.0f;
			fAngle = g_player[nCntPlayer].rotDest.y - D3DX_PI;
		}

		//移動
		g_player[nCntPlayer].pos.x += sinf(fAngle) * fSpeed;
		g_player[nCntPlayer].pos.z += cosf(fAngle) * fSpeed;
		g_player[nCntPlayer].rotDest.y = (fAngle += D3DX_PI);

		for (int nCnt = 0; nCnt < MAX_BOMB; nCnt++)
		{
			if (bomb[nCnt].bUse == true && bomb[nCnt].bHave == false)
			{	//使用していて誰も持っていない爆弾が存在する場合
				if (g_player[nCntPlayer].pos.x == bomb[nCnt].pos.x && g_player[nCntPlayer].pos.z == bomb[nCnt].pos.z)
				{	//X座標、Y座標が重なっているとき

					//爆弾を拾う
					g_player[nCntPlayer].bHaveBomb = true;
					bomb[nCnt].bHave = true;
				}
			}
		}
	}
	else
	{
		D3DXVECTOR3 vector;
		float fVector;
		float fAngle;

		//ベクトル・ベクトルの長さを算出
		vector = g_player[g_player[nCntPlayer].nNearPlayer].pos - g_player[nCntPlayer].pos;
		fVector = D3DXVec3Length(&D3DXVECTOR3(vector.x, 0.0f, vector.z));

		if (fVector > DIS_BOMB)
		{	//一番近くの敵までの距離が爆弾の飛距離以上の場合

			//敵までの角度
			fAngle = atan2f(vector.x, vector.z);

			//移動
			g_player[nCntPlayer].pos.x += sinf(fAngle) * MOVE_PLAYER;
			g_player[nCntPlayer].pos.z += cosf(fAngle) * MOVE_PLAYER;
		}
	}*/
}

////////////////////////////////////////////////////////////////////////////////
//AI投げ
////////////////////////////////////////////////////////////////////////////////
void ThrowAi(int nCntPlayer)
{
	D3DXVECTOR3 vector[MAX_DISPLAY_CHARA];
	D3DXVECTOR3 vectorA;

	float fVector[MAX_DISPLAY_CHARA];
	float fVectorA = 30000000000000.0f;

	float fAngle = 0.0f;

	if (g_player[nCntPlayer].bHaveBomb == true)
	{	//爆弾を所持している場合

		//他プレイヤーへのベクトルを取得
		for (int nCnt = 0; nCnt < MAX_DISPLAY_CHARA; nCnt++)
		{
			if (nCnt != nCntPlayer)
			{	//自分以外

				//他プレイヤーへのベクトル・ベクトルの長さを算出
				vector[nCnt] = g_player[nCnt].pos - g_player[nCntPlayer].pos;
				fVector[nCnt] = D3DXVec3Length(&D3DXVECTOR3(vector[nCnt].x, 0, vector[nCnt].z));

				if (fVectorA > fVector[nCnt])
				{	//一番近いプレイヤー
					fVectorA = fVector[nCnt];
					vectorA = vector[nCnt];
					g_player[nCntPlayer].nNearPlayer = nCnt;
				}
			}
		}

		//そのプレイヤーが飛距離内にいるかどうか
		if (fVectorA <= DIS_BOMB)
		{//飛距離内にいる場合

		 //多分投げる処理はプレイヤーの向きで投げる方向を決めるのでそのプレイヤーの方向に向ける
			fAngle = atan2f(vectorA.x, vectorA.z);
			g_player[nCntPlayer].rotDest.y = (fAngle += D3DX_PI);

			//投げる
			if (g_player[nCntPlayer].rot == g_player[nCntPlayer].rotDest)
			{

			}
		}
	}
}

////////////////////////////////////////////////////////////////////////////////
//プレイヤー同士の当たり判定
////////////////////////////////////////////////////////////////////////////////
bool CollisionPlayer(int nCntPlayer)
{
	D3DXVECTOR3 vector[MAX_DISPLAY_CHARA];
	float fVector[MAX_DISPLAY_CHARA];
	float fPlayerSize;

	for (int nCnt = 0; nCnt < g_nDisPlayer; nCnt++)
	{
		if (nCnt != nCntPlayer)
		{
			vector[nCnt] = g_player[nCnt].pos - g_player[nCntPlayer].pos;
			fVector[nCnt] = D3DXVec3Length(&D3DXVECTOR3(vector[nCnt].x, 0.0f, vector[nCnt].z));

			fPlayerSize = ((g_player[nCntPlayer].pos.x + g_player[nCntPlayer].maxVecPlayer.x) - g_player[nCntPlayer].pos.x) * 3;

			if (fVector[nCnt] < fPlayerSize)
			{
				float fAngle = atan2f(vector[nCnt].x, vector[nCnt].z);
				g_player[nCntPlayer].bPush = true;

				g_player[nCnt].pos.x += sinf(fAngle) * fPlayerSize /10;
				g_player[nCnt].pos.z += cosf(fAngle) * fPlayerSize /10;
				return true;
			}
		}
	}

	return false;
}

//-----------------------------------------------------------------
// プレイヤーの移動処理(キーボード)
//-----------------------------------------------------------------
void MovePlayerKeyboard(int nCntPlayer)
{
	// 情報の取得
	Camera *pCamera = GetCamera();				// カメラ情報
#if 0
	if (GetKeyboardPress(KEYINFO_UP) == true)
	{
		if (GetKeyboardPress(KEYINFO_RIGHT) == true)
		{// モデル斜め右上移動
			g_player[nCntPlayer].move.z -= MOVE_MODEL * sinf(pCamera->CameraInfo[0].rot.y - PI_QUARTER);
			g_player[nCntPlayer].move.x += MOVE_MODEL * cosf(pCamera->CameraInfo[0].rot.y - PI_QUARTER);
			g_player[nCntPlayer].rotDest.y = pCamera->CameraInfo[0].rot.y - PI_QUARTER * 3.0f;
		}
		else if (GetKeyboardPress(KEYINFO_LEFT) == true)
		{// モデル斜め右上移動
			g_player[nCntPlayer].move.z += MOVE_MODEL * sinf(pCamera->CameraInfo[0].rot.y + PI_QUARTER);
			g_player[nCntPlayer].move.x -= MOVE_MODEL * cosf(pCamera->CameraInfo[0].rot.y + PI_QUARTER);
			g_player[nCntPlayer].rotDest.y = pCamera->CameraInfo[0].rot.y + PI_QUARTER * 3.0f;
		}
		else
		{// モデル上移動
			g_player[nCntPlayer].move.z += MOVE_MODEL * cosf(pCamera->CameraInfo[0].rot.y);
			g_player[nCntPlayer].move.x += MOVE_MODEL * sinf(pCamera->CameraInfo[0].rot.y);
			g_player[nCntPlayer].rotDest.y = pCamera->CameraInfo[0].rot.y - D3DX_PI;
		}
		// 移動しているとき移動モーションに設定
		SetMotion(nCntPlayer, MOTIONTYPE_MOVE, false, 0);
	}
	else if (GetKeyboardPress(KEYINFO_DOWN) == true)
	{
		if (GetKeyboardPress(KEYINFO_RIGHT) == true)
		{// モデル斜め右上移動
			g_player[nCntPlayer].move.z -= MOVE_MODEL * sinf(pCamera->CameraInfo[0].rot.y + PI_QUARTER);
			g_player[nCntPlayer].move.x += MOVE_MODEL * cosf(pCamera->CameraInfo[0].rot.y + PI_QUARTER);
			g_player[nCntPlayer].rotDest.y = pCamera->CameraInfo[0].rot.y - PI_QUARTER;
		}
		else if (GetKeyboardPress(KEYINFO_LEFT) == true)
		{// モデル斜め右上移動
			g_player[nCntPlayer].move.z += MOVE_MODEL * sinf(pCamera->CameraInfo[0].rot.y - PI_QUARTER);
			g_player[nCntPlayer].move.x -= MOVE_MODEL * cosf(pCamera->CameraInfo[0].rot.y - PI_QUARTER);
			g_player[nCntPlayer].rotDest.y = pCamera->CameraInfo[0].rot.y + PI_QUARTER;
		}
		else
		{// モデル下移動
			g_player[nCntPlayer].move.z -= MOVE_MODEL * cosf(pCamera->CameraInfo[0].rot.y);
			g_player[nCntPlayer].move.x -= MOVE_MODEL * sinf(pCamera->CameraInfo[0].rot.y);
			g_player[nCntPlayer].rotDest.y = pCamera->CameraInfo[0].rot.y;
		}
		// 移動しているとき移動モーションに設定
		SetMotion(nCntPlayer, MOTIONTYPE_MOVE, false, 0);
	}
	else if (GetKeyboardPress(KEYINFO_RIGHT) == true)
	{// モデル右移動
		g_player[nCntPlayer].move.z -= MOVE_MODEL * sinf(pCamera->CameraInfo[0].rot.y);
		g_player[nCntPlayer].move.x += MOVE_MODEL * cosf(pCamera->CameraInfo[0].rot.y);
		g_player[nCntPlayer].rotDest.y = pCamera->CameraInfo[0].rot.y - D3DX_PI / 2.0f;

		// 移動しているとき移動モーションに設定
		SetMotion(nCntPlayer, MOTIONTYPE_MOVE, false, 0);
	}
	else if (GetKeyboardPress(KEYINFO_LEFT) == true)
	{// モデル左移動
		g_player[nCntPlayer].move.z += MOVE_MODEL * sinf(pCamera->CameraInfo[0].rot.y);
		g_player[nCntPlayer].move.x -= MOVE_MODEL * cosf(pCamera->CameraInfo[0].rot.y);
		g_player[nCntPlayer].rotDest.y = pCamera->CameraInfo[0].rot.y + D3DX_PI / 2.0f;

		// 移動しているとき移動モーションに設定
		SetMotion(nCntPlayer, MOTIONTYPE_MOVE, false, 0);
	}
	if (GetKeyboardTrigger(KEYINFO_SHOOT) == true &&
		g_player[nCntPlayer].state != PLAYERSTATE_FLOATING)
	{
		g_player[nCntPlayer].move.y += JUMP_PLAYER;
		g_player[nCntPlayer].state = PLAYERSTATE_FLOATING;

		// 音を出す
		//PlaySound(SOUND_LABEL_SE_JUMP);
	}
#endif
}

//-----------------------------------------------------------------
// プレイヤーの移動処理(ゲームパッド)
//-----------------------------------------------------------------
void MovePlayerGamepad(int nCntPlayer)
{
	// 情報の取得
	Camera *pCamera = GetCamera();				// カメラ情報

	// ゲームパッド情報の取得
	DIJOYSTATE2 Controller = GetControllerPless(nCntPlayer);

	// JOYPADのスティック入力
	// 移動処理
	if (Controller.lX != 0 || Controller.lY != 0)
	{// スティックの入力角度
		float fAngle = atan2f((float)Controller.lX, (float)Controller.lY);

		g_player[nCntPlayer].rotDest.y = pCamera->CameraInfo[0].rot.y - fAngle;								// 向きの設定
		g_player[nCntPlayer].move.x -= MOVE_PLAYER * sinf(g_player[nCntPlayer].rotDest.y);			// X軸移動量の決定
		g_player[nCntPlayer].move.z -= MOVE_PLAYER * cosf(g_player[nCntPlayer].rotDest.y);			// Z軸移動量の決定

		// 現在の回転角を制限
		if (g_player[nCntPlayer].rotDest.y > D3DX_PI)
		{// 3.14fより大きくなったとき値を-3.14fにする
			g_player[nCntPlayer].rotDest.y -= D3DX_PI * 2.0f;
		}
		else if (g_player[nCntPlayer].rotDest.y < -D3DX_PI)
		{// -3.14fより小さくなったとき値に3.14fにする
			g_player[nCntPlayer].rotDest.y += D3DX_PI * 2.0f;
		}
		// モーションを移動モーションにする
		SetMotion(nCntPlayer,MOTIONTYPE_MOVE,true,10);
	}
	// 投げモーション
	if (GetJoypadTrigger(nCntPlayer, JPINFO_OKorJUMP) == true &&
		g_player[nCntPlayer].state != PLAYERSTATE_FLOATING)
	{
		// モーションを投げモーションにする
		SetMotion(nCntPlayer, MOTIONTYPE_THROW, true, 10);
		g_player[nCntPlayer].state = PLAYERSTATE_THROW;
	}
	// ジャンプ処理
	if (GetJoypadTrigger(nCntPlayer, JPINFO_CANCEL) == true &&
		g_player[nCntPlayer].state != PLAYERSTATE_FLOATING)
	{
		g_player[nCntPlayer].move.y += JUMP_PLAYER;
		g_player[nCntPlayer].state = PLAYERSTATE_FLOATING;
		// モーションを投げモーションにする
		SetMotion(nCntPlayer, MOTIONTYPE_JUMP, true, 10);
	}
}

//-----------------------------------------------------------------
// プレイヤー情報の取得
//-----------------------------------------------------------------
Player *GetPlayer(void)
{
	return &g_player[0];
}

//-----------------------------------------------------------------
// プレイヤ-モーションの設定
//-----------------------------------------------------------------
void PlayerMotion(int nCntPlayer)
{
	// 変数宣言
	Player *pPlayer = GetPlayer();
	pPlayer += nCntPlayer;	// 何番目のプレイヤーか
	KEY *pKey;				// キー情報
	KEY *pKeyNext;			// 次のキー情報
	KEY *pKeyBlend;			// ブレンドキー情報
	KEY *pKeyNextBlend;		// 次のブレンドキー情報
	float fPosX;
	float fPosY;
	float fPosZ;
	float fRotX;
	float fRotY;
	float fRotZ;

	for (int nCntModel = 0; nCntModel < g_player[nCntPlayer].nNumModel; nCntModel++)
	{
		// キーの確定
		pKey = &pPlayer->aMotionInfo[pPlayer->MotionType].aKeyInfo[pPlayer->nKey].aKey[nCntModel];
		pKeyNext = &pPlayer->aMotionInfo[pPlayer->MotionType].aKeyInfo[(pPlayer->nKey + 1) % pPlayer->nNumKey].aKey[nCntModel];

		// 差分の確定
		float fDiffMoitonPosX = pKeyNext->fPosX - pKey->fPosX;
		float fDiffMoitonPosY = pKeyNext->fPosY - pKey->fPosY;
		float fDiffMoitonPosZ = pKeyNext->fPosZ - pKey->fPosZ;
		float fDiffMoitonRotX = pKeyNext->fRotX - pKey->fRotX;
		float fDiffMoitonRotY = pKeyNext->fRotY - pKey->fRotY;
		float fDiffMoitonRotZ = pKeyNext->fRotZ - pKey->fRotZ;

		// 相対値の確定
		float fRateMotion = (float)pPlayer->nCounterMotion / (float)pPlayer->aMotionInfo[pPlayer->MotionType].aKeyInfo[pPlayer->nKey].nFrame;

		if (g_player[nCntPlayer].bBlendMotion == true)
		{
			// キーの確定
			pKeyBlend = &pPlayer->aMotionInfo[pPlayer->MotionTypeBlend].aKeyInfo[pPlayer->nKeyBlend].aKey[nCntModel];
			pKeyNextBlend = &pPlayer->aMotionInfo[pPlayer->MotionTypeBlend].aKeyInfo[(pPlayer->nKeyBlend + 1) % pPlayer->nNumKeyBlend].aKey[nCntModel];

			// 差分の確定
			float fDiffMoitonBlendPosX = pKeyNextBlend->fPosX - pKeyBlend->fPosX;
			float fDiffMoitonBlendPosY = pKeyNextBlend->fPosY - pKeyBlend->fPosY;
			float fDiffMoitonBlendPosZ = pKeyNextBlend->fPosZ - pKeyBlend->fPosZ;
			float fDiffMoitonBlendRotX = pKeyNextBlend->fRotX - pKeyBlend->fRotX;
			float fDiffMoitonBlendRotY = pKeyNextBlend->fRotY - pKeyBlend->fRotY;
			float fDiffMoitonBlendRotZ = pKeyNextBlend->fRotZ - pKeyBlend->fRotZ;

			// 相対値の確定
			float fRateMotionBlend = (float)pPlayer->nCounterMotionBlend / (float)pPlayer->aMotionInfo[pPlayer->MotionTypeBlend].aKeyInfo[pPlayer->nKeyBlend].nFrame;

			float fRateBlend = (float)pPlayer->nCounterBlend / (float)pPlayer->nFrameBlend;

			// 現在のモーションの位置と向きの確定
			float fPosXCurrent = pKey->fPosX + (fDiffMoitonPosX * fRateMotion);
			float fPosYCurrent = pKey->fPosY + (fDiffMoitonPosY * fRateMotion);
			float fPosZCurrent = pKey->fPosZ + (fDiffMoitonPosZ * fRateMotion);
			float fRotXCurrent = pKey->fRotX + (fDiffMoitonRotX * fRateMotion);
			float fRotYCurrent = pKey->fRotY + (fDiffMoitonRotY * fRateMotion);
			float fRotZCurrent = pKey->fRotZ + (fDiffMoitonRotZ * fRateMotion);

			// 角度の制限
			D3DXVECTOR3(fRotXCurrent, fRotYCurrent, fRotZCurrent) = AngleCorrection(fRotXCurrent, fRotYCurrent, fRotZCurrent);

			// ブレンドモーションの位置と向きの確定
			float fPosXBlend = pKeyBlend->fPosX + (fDiffMoitonBlendPosX * fRateMotionBlend);
			float fPosYBlend = pKeyBlend->fPosY + (fDiffMoitonBlendPosY * fRateMotionBlend);
			float fPosZBlend = pKeyBlend->fPosZ + (fDiffMoitonBlendPosZ * fRateMotionBlend);
			float fRotXBlend = pKeyBlend->fRotX + (fDiffMoitonBlendRotX * fRateMotionBlend);
			float fRotYBlend = pKeyBlend->fRotY + (fDiffMoitonBlendRotY * fRateMotionBlend);
			float fRotZBlend = pKeyBlend->fRotZ + (fDiffMoitonBlendRotZ * fRateMotionBlend);

			// 角度の制限
			D3DXVECTOR3(fRotXBlend, fRotYBlend, fRotZBlend) = AngleCorrection(fRotXBlend, fRotYBlend, fRotZBlend);

			// 現在のモーションとブレンドモーションの差分
			float fDiffBlendPosX = fPosXBlend - fPosXCurrent;
			float fDiffBlendPosY = fPosYBlend - fPosYCurrent;
			float fDiffBlendPosZ = fPosZBlend - fPosZCurrent;
			float fDiffBlendRotX = fRotXBlend - fRotXCurrent;
			float fDiffBlendRotY = fRotYBlend - fRotYCurrent;
			float fDiffBlendRotZ = fRotZBlend - fRotZCurrent;

			// 角度の制限
			D3DXVECTOR3(fDiffBlendRotX, fDiffBlendRotY, fDiffBlendRotZ) = AngleCorrection(fDiffBlendRotX, fDiffBlendRotY, fDiffBlendRotZ);

			// ブレンドモーションの位置と向きの確定
			fPosX = fPosXCurrent + (fDiffBlendPosX * fRateBlend);
			fPosY = fPosYCurrent + (fDiffBlendPosY * fRateBlend);
			fPosZ = fPosZCurrent + (fDiffBlendPosZ * fRateBlend);
			fRotX = fRotXCurrent + (fDiffBlendRotX * fRateBlend);
			fRotY = fRotYCurrent + (fDiffBlendRotY * fRateBlend);
			fRotZ = fRotZCurrent + (fDiffBlendRotZ * fRateBlend);
		}
		else
		{
			// モーションの位置と向きの確定
			fPosX = pKey->fPosX + (fDiffMoitonPosX * fRateMotion);
			fPosY = pKey->fPosY + (fDiffMoitonPosY * fRateMotion);
			fPosZ = pKey->fPosZ + (fDiffMoitonPosZ * fRateMotion);
			fRotX = pKey->fRotX + (fDiffMoitonRotX * fRateMotion);
			fRotY = pKey->fRotY + (fDiffMoitonRotY * fRateMotion);
			fRotZ = pKey->fRotZ + (fDiffMoitonRotZ * fRateMotion);
		}
		// 角度の制限
		D3DXVECTOR3(fRotX, fRotY, fRotZ) = AngleCorrection(fRotX, fRotY, fRotZ);

		// 位置と向きの設定
		pPlayer->aModel[nCntModel].pos.x = fPosX;
		pPlayer->aModel[nCntModel].pos.y = fPosY;
		pPlayer->aModel[nCntModel].pos.z = fPosZ;
		pPlayer->aModel[nCntModel].rot.x = fRotX;
		pPlayer->aModel[nCntModel].rot.y = fRotY;
		pPlayer->aModel[nCntModel].rot.z = fRotZ;
	}

	if (g_player[nCntPlayer].bBlendMotion == true)
	{
		if (pPlayer->nCounterMotionBlend > pPlayer->aMotionInfo[pPlayer->MotionTypeBlend].aKeyInfo[pPlayer->nKeyBlend].nFrame)
		{
			// ブレンドモーションカウンタの初期化
			pPlayer->nCounterMotionBlend = 0;

			// キーの更新
			pPlayer->nKeyBlend++;

			// キーの確定
			pPlayer->nKeyBlend = pPlayer->nKeyBlend % pPlayer->nNumKeyBlend;
		}
		else
		{
			// ブレンドモーションカウンタの更新
			pPlayer->nCounterMotionBlend++;

			// ブレンドカウンタの更新
			pPlayer->nCounterBlend++;

			if (pPlayer->nCounterBlend >= pPlayer->nFrameBlend)
			{
				// モーションの確定
				pPlayer->MotionType = pPlayer->MotionTypeBlend;

				// モーションカウンタを初期化
				pPlayer->nCounterMotion = pPlayer->nCounterMotionBlend;

				// 現在のキーを初期化
				pPlayer->nKey = pPlayer->nKeyBlend;

				// ループするかどうか
				pPlayer->bLoopMotion = pPlayer->bLoopMotionBlend;

				// キー数の確定
				pPlayer->nNumKey = pPlayer->nNumKeyBlend;

				// モーションブレンドを終える
				pPlayer->bBlendMotion = false;

				pPlayer->bFinishMotion = false;
			}
		}
	}
	else
	{
		if (pPlayer->nCounterMotion > pPlayer->aMotionInfo[pPlayer->MotionType].aKeyInfo[pPlayer->nKey].nFrame)
		{
			// モーションカウンタの初期化
			pPlayer->nCounterMotion = 0;

			// キーの更新
			pPlayer->nKey++;

			// キーの確定
			pPlayer->nKey = pPlayer->nKey % pPlayer->nNumKey;

			if (pPlayer->nKey == (pPlayer->nNumKey - 1))
			{
				if (pPlayer->aMotionInfo[pPlayer->MotionType].bLoop == false)
				{
					if ((pPlayer->MotionType == MOTIONTYPE_THROW) || (pPlayer->MotionType == MOTIONTYPE_JUMP))
					{
						SetMotion(nCntPlayer, MOTIONTYPE_NEUTRAL, true, 10);
					}
				}
			}
		}
		else if (pPlayer->MotionType == MOTIONTYPE_THROW &&
			pPlayer->nKey == 1 &&
			pPlayer->nCounterMotion == 5)
		{
			BombThrow(pPlayer->nBombID, pPlayer->pos, pPlayer->rot);
			pPlayer->nBombID = -1;
		}
		// モーションカウンタの更新
		pPlayer->nCounterMotion++;
	}
}

//-----------------------------------------------------------------
// モーションの設定
//-----------------------------------------------------------------
void SetMotion(int nCntPlayer,MOTIONTYPE motiontype, bool bBlend, int nFrameBlend)
{
	// 変数宣言
	Player *pPlayer = GetPlayer();
	pPlayer += nCntPlayer;

	switch (motiontype)
	{
	case MOTIONTYPE_NEUTRAL:
		pPlayer->state = PLAYERSTATE_NORMAL;
		break;

	case MOTIONTYPE_MOVE:
		break;

	case MOTIONTYPE_THROW:
		pPlayer->state = PLAYERSTATE_THROW;
		break;

	case MOTIONTYPE_LAND:
		break;

	case MOTIONTYPE_DAMAGE:
		pPlayer->state = PLAYERSTATE_DAMAGE;
		break;

	default:
		break;
	}
	//if (pPlayer->bFinishMotion == true)
	{
		if (bBlend == true && pPlayer->MotionTypeBlend != motiontype)
		{
			// モーションの確定
			pPlayer->MotionTypeBlend = motiontype;

			// モーションカウンタを初期化
			pPlayer->nCounterMotionBlend = 0;

			// 現在のキーを初期化
			pPlayer->nKeyBlend = 0;

			// ループするかどうか
			pPlayer->bLoopMotionBlend = pPlayer->aMotionInfo[pPlayer->MotionTypeBlend].bLoop;

			// キー数の確定
			pPlayer->nNumKeyBlend = pPlayer->aMotionInfo[pPlayer->MotionTypeBlend].nNumKey;

			// ブレンドフレームの設定
			pPlayer->nFrameBlend = nFrameBlend;

			// ブレンドするかどうか
			pPlayer->bBlendMotion = bBlend;

			// ブレンドカウンタの初期化
			pPlayer->nCounterBlend = 0;
		}
		else if (bBlend == false && pPlayer->MotionType != motiontype && pPlayer->bFinishMotion == true)
		{
			// モーションの確定
			pPlayer->MotionType = motiontype;

			// モーションカウンタを初期化
			pPlayer->nCounterMotion = 0;

			// 現在のキーを初期化
			pPlayer->nKey = 0;

			// ループするかどうか
			pPlayer->bLoopMotion = pPlayer->aMotionInfo[pPlayer->MotionType].bLoop;

			// キー数の確定
			pPlayer->nNumKey = pPlayer->aMotionInfo[pPlayer->MotionType].nNumKey;

			pPlayer->bFinishMotion = false;
		}
	}
}

//-----------------------------------------------------------------
// 角度の制限
//-----------------------------------------------------------------
D3DXVECTOR3 AngleCorrection(float rotX, float rotY, float rotZ)
{
	// 現在の回転角を制限
	if (rotX > D3DX_PI)
	{// 3.14fより大きくなったとき値を-3.14fにする
		rotX -= D3DX_PI * 2.0f;
	}
	else if (rotX < -D3DX_PI)
	{// -3.14fより小さくなったとき値に3.14fにする
		rotX += D3DX_PI * 2.0f;
	}
	// 現在の回転角を制限
	if (rotY  > D3DX_PI)
	{// 3.14fより大きくなったとき値を-3.14fにする
		rotY -= D3DX_PI * 2.0f;
	}
	else if (rotY < -D3DX_PI)
	{// -3.14fより小さくなったとき値に3.14fにする
		rotY += D3DX_PI * 2.0f;
	}
	// 現在の回転角を制限
	if (rotZ > D3DX_PI)
	{// 3.14fより大きくなったとき値を-3.14fにする
		rotZ -= D3DX_PI * 2.0f;
	}
	else if (rotZ < -D3DX_PI)
	{// -3.14fより小さくなったとき値に3.14fにする
		rotZ += D3DX_PI * 2.0f;
	}

	return D3DXVECTOR3(rotX, rotY, rotZ);
}