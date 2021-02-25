////////////////////////////////////////////////////////////////////////////////
//
//Contents	: プレイヤーの処理 [player.cpp]
//Author	: ShotaFuruichi
//Since		: 2020/12/17
//
////////////////////////////////////////////////////////////////////////////////
#include "player.h"
#include "camera.h"
#include "input.h"
#include "bullet.h"
#include "xinput_pad.h"
#include "object.h"
#include "fade.h"
#include "enemy.h"
#include "result.h"
#include "circle.h"
#include "effect.h"

////////////////////////////////////////////////////////////////////////////////
//マクロ定義
////////////////////////////////////////////////////////////////////////////////
#define PMOVE_SPEED (5.0f)				//プレイヤーの移動速度
#define MAX_INVI (4)					//透明な壁の枚数
#define EX_INVI (2000)					//透明な壁の大きさ
#define PLAYER_APPEARX (0)				//プレイヤーの出現位置X座標
#define PLAYER_APPEARZ (-EX_INVI + 30)	//プレイヤーの出現位置Z座標
#define MP_COUNT (SEC_ONE * 15)			//mp回復の間隔
#define MP_RECOVERY (1000)				//mpの回復量
#define ATTACK_REACH (500.0f)			//物理攻撃が届く距離

#define ATTACK_DAMAGE (500)				//物理攻撃の威力
#define HEAL_POWER (800)				//回復魔法の効力

#define MAGIC_MP (600)					//攻撃魔法の消費MP
#define HEAL_MP (800)					//回復魔法の消費MP

#define NEUT_KEY (2)					//ニュートラルモーションのキー数
#define MOVE_KEY (4)					//移動モーションのキー数
#define JUMP_KEY (5)					//ジャンプモーションのキー数
#define ACTION_KEY (3)					//アクションモーションのキー数

////////////////////////////////////////////////////////////////////////////////
//グローバル変数
////////////////////////////////////////////////////////////////////////////////
PLAYER g_Player;				//プレイヤー
D3DXVECTOR3 aPos[MAX_INVI];		//外積
float fGaiseki[MAX_INVI * 2];	//外積

////////////////////////////////////////////////////////////////////////////////
//初期化処理
////////////////////////////////////////////////////////////////////////////////
void InitPlayer(void)
{
	//変数宣言
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//Xファイルの読み込み
	D3DXLoadMeshFromX("data/model/body.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Player.aModel[0].pBufferMat, NULL, &g_Player.aModel[0].nNumMat, &g_Player.aModel[0].pMesh);
	D3DXLoadMeshFromX("data/model/head.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Player.aModel[1].pBufferMat, NULL, &g_Player.aModel[1].nNumMat, &g_Player.aModel[1].pMesh);
	D3DXLoadMeshFromX("data/model/armR.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Player.aModel[2].pBufferMat, NULL, &g_Player.aModel[2].nNumMat, &g_Player.aModel[2].pMesh);
	D3DXLoadMeshFromX("data/model/armL.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Player.aModel[3].pBufferMat, NULL, &g_Player.aModel[3].nNumMat, &g_Player.aModel[3].pMesh);
	D3DXLoadMeshFromX("data/model/legR.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Player.aModel[4].pBufferMat, NULL, &g_Player.aModel[4].nNumMat, &g_Player.aModel[4].pMesh);
	D3DXLoadMeshFromX("data/model/legL.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Player.aModel[5].pBufferMat, NULL, &g_Player.aModel[5].nNumMat, &g_Player.aModel[5].pMesh);

	g_Player.nNumModel = MAX_MODEL_PLAYER;
	aPos[0] = D3DXVECTOR3(EX_INVI, 0.0f, EX_INVI);
	aPos[1] = D3DXVECTOR3(-EX_INVI, 0.0f, EX_INVI);
	aPos[2] = D3DXVECTOR3(-EX_INVI, 0.0f, -EX_INVI);
	aPos[3] = D3DXVECTOR3(EX_INVI, 0.0f, -EX_INVI);

	//各パーツの階層構造設定
	g_Player.aModel[0].nIdxModelParent = -1;							//親モデルのインデックスを設定
	g_Player.aModel[0].pos = D3DXVECTOR3(0.0f, 45.0f, 0.0f);			//位置(オフセット)の初期設定
	g_Player.aModel[0].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//向きの初期設定
	g_Player.aModel[1].nIdxModelParent = 0;								//親モデルのインデックスを設定
	g_Player.aModel[1].pos = D3DXVECTOR3(0.0f, 60.0f, 0.0f);			//位置(オフセット)の初期設定
	g_Player.aModel[1].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//向きの初期設定
	g_Player.aModel[2].nIdxModelParent = 0;								//親モデルのインデックスを設定
	g_Player.aModel[2].pos = D3DXVECTOR3(-13.0f, 57.5f, 2.5f);			//位置(オフセット)の初期設定
	g_Player.aModel[2].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//向きの初期設定
	g_Player.aModel[3].nIdxModelParent = 0;								//親モデルのインデックスを設定
	g_Player.aModel[3].pos = D3DXVECTOR3(13.0f, 57.5f, 2.6f);			//位置(オフセット)の初期設定
	g_Player.aModel[3].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//向きの初期設定
	g_Player.aModel[4].nIdxModelParent = 0;								//親モデルのインデックスを設定
	g_Player.aModel[4].pos = D3DXVECTOR3(-10.0f, 7.5f, 2.5f);			//位置(オフセット)の初期設定
	g_Player.aModel[4].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//向きの初期設定
	g_Player.aModel[5].nIdxModelParent = 0;								//親モデルのインデックスを設定
	g_Player.aModel[5].pos = D3DXVECTOR3(10.0f, 7.5f, 2.5f);			//位置(オフセット)の初期設定
	g_Player.aModel[5].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//向きの初期設定

	g_Player.pos = D3DXVECTOR3(PLAYER_APPEARX, 0.0f, PLAYER_APPEARZ);	//プレイヤーの位置の初期設定
	g_Player.posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					//プレイヤーの前回更新時の位置の初期設定
	g_Player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);						//プレイヤーの向きの初期設定
	g_Player.rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					//プレイヤーの目標の向きの初期設定
	g_Player.nowMotion = MOTION_NEUTRAL;								//プレイヤーの現在のモーションの初期設定
	g_Player.fGravity = 0.0f;											//重力の初期設定
	g_Player.bJump = true;												//ジャンプの可不可の初期設定
	g_Player.nLife = LIFE_PLAYER;										//プレイヤーの体力の初期設定
	g_Player.nMP = MP_PLAYER;											//プレイヤーのmpの初期設定
	g_Player.nMpRec = 0;												//mp回復のためのカウンタ
	g_Player.bMove = false;												//プレイヤーが移動中か
	g_Player.bChant = false;											//プレイヤーが詠唱中か
	g_Player.nCooldown = 0;												//スキルのクールダウン
	g_Player.bUseSkill = true;											//スキルを使えるか
	g_Player.nChantCounter = 0;											//詠唱時間
	g_Player.skill = SKILL_NONE;										//使用するスキル
}

////////////////////////////////////////////////////////////////////////////////
//終了処理
////////////////////////////////////////////////////////////////////////////////
void UninitPlayer(void)
{
	for (int nCntModel = 0; nCntModel < MAX_MODEL_PLAYER; nCntModel++)
	{
		if (g_Player.aModel[nCntModel].pMesh != NULL)
		{
			g_Player.aModel[nCntModel].pMesh->Release();	//破棄
			g_Player.aModel[nCntModel].pMesh = NULL;		//初期化
		}

		if (g_Player.aModel[nCntModel].pBufferMat != NULL)
		{
			g_Player.aModel[nCntModel].pBufferMat->Release();	//破棄
			g_Player.aModel[nCntModel].pBufferMat = NULL;		//初期化
		}
	}
}

////////////////////////////////////////////////////////////////////////////////
//更新処理
////////////////////////////////////////////////////////////////////////////////
void UpdatePlayer(void)
{	
	//モーションの優先度管理
	if (g_Player.nowMotion != MOTION_JUMP && g_Player.nowMotion != MOTION_ACTION)
	{	
		g_Player.nowMotion = MOTION_NEUTRAL;
	}

	g_Player.bMove = false;

	//MP回復
	if (g_Player.nMP != MP_PLAYER)
	{
		g_Player.nMpRec++;
	}

	if (g_Player.nMpRec % MP_COUNT == 0)
	{
		int nRec = MP_RECOVERY;
		if (g_Player.nMP + MP_RECOVERY > MP_PLAYER)
		{
			nRec = MP_PLAYER - g_Player.nMP;
		}
		g_Player.nMP += nRec;
	}

	MovePlayer();
	SkillPlayer();
	MotionPlayer();

	if (g_Player.nLife <= 0)
	{	//プレイヤーの体力が0以下になった場合リザルトへ
		SetFade(FADE_OUT, MODE_RESULT);
	}
}

////////////////////////////////////////////////////////////////////////////////
//描画処理
////////////////////////////////////////////////////////////////////////////////
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans;				//計算用マトリックス
	D3DMATERIAL9 matDef;						//現在のマテリアル保存用
	D3DXMATERIAL *pMat;							//マテリアルデータへのポインタ

	//プレイヤーのワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_Player.mtxWorld);

	//プレイヤーの向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Player.rot.y, g_Player.rot.x, g_Player.rot.z);
	D3DXMatrixMultiply(&g_Player.mtxWorld, &g_Player.mtxWorld, &mtxRot);

	//プレイヤーの位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_Player.pos.x, g_Player.pos.y, g_Player.pos.z);
	D3DXMatrixMultiply(&g_Player.mtxWorld, &g_Player.mtxWorld, &mtxTrans);

	//プレイヤーのワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_Player.mtxWorld);

	//現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);

	for (int nCntModel = 0; nCntModel < g_Player.nNumModel; nCntModel++)
	{
		D3DXMATRIX mtxRotModel, mtxTransModel;	//計算用マトリックス
		D3DXMATRIX mtxParent;					//親のマトリックス

		//各パーツのワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_Player.aModel[nCntModel].mtxWorld);

		//各パーツの向きを反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Player.aModel[nCntModel].rot.y, g_Player.aModel[nCntModel].rot.x, g_Player.aModel[nCntModel].rot.z);
		D3DXMatrixMultiply(&g_Player.aModel[nCntModel].mtxWorld, &g_Player.aModel[nCntModel].mtxWorld, &mtxRot);

		//各パーツの位置を反映
		D3DXMatrixTranslation(&mtxTrans, g_Player.aModel[nCntModel].pos.x, g_Player.aModel[nCntModel].pos.y, g_Player.aModel[nCntModel].pos.z);
		D3DXMatrixMultiply(&g_Player.aModel[nCntModel].mtxWorld, &g_Player.aModel[nCntModel].mtxWorld, &mtxTrans);

		//各パーツの親のマトリックスを設定
		if (g_Player.aModel[nCntModel].nIdxModelParent != -1)
		{
			mtxParent = g_Player.aModel[g_Player.aModel[nCntModel].nIdxModelParent].mtxWorld;
		}
		else
		{
			mtxParent = g_Player.mtxWorld;	//プレイヤーのマトリックスを設定
		}

		//算出した各パーツのワールドマトリックスと親のマトリックスを掛け合わせる
		D3DXMatrixMultiply(&g_Player.aModel[nCntModel].mtxWorld, &g_Player.aModel[nCntModel].mtxWorld, &mtxParent);

		//各パーツのワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_Player.aModel[nCntModel].mtxWorld);

		//マテリアルデータへのポインタを取得
		pMat = (D3DXMATERIAL *)g_Player.aModel[nCntModel].pBufferMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_Player.aModel[nCntModel].nNumMat; nCntMat++)
		{
			//マテリアルの設定
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			//テクスチャの設定
			pDevice->SetTexture(0, NULL);

			//モデル(パーツ)の描画
			g_Player.aModel[nCntModel].pMesh->DrawSubset(nCntMat);
		}
		//保存していたマテリアルを戻す
		pDevice->SetMaterial(&matDef);
	}
}

////////////////////////////////////////////////////////////////////////////////
//プレイヤーのスキル処理
////////////////////////////////////////////////////////////////////////////////
void SkillPlayer(void)
{
	//変数定義
	XinputGamepad *pXinput = GetXinputGamepad();
	ENEMY *enemy = GetEnemy();
	static int nCntEff = 0;

	if (g_Player.nCooldown > 0)
	{	//クールダウン
		g_Player.nCooldown--;
	}

	if (g_Player.bChant == false)
	{
		if (g_Player.nCooldown == 0)
		{
			g_Player.bUseSkill = true;
		}
	}

	//スキル使用
	if (g_Player.bUseSkill == true)
	{
		if (GetKeyboardTrigger(DIK_1) == TRUE || pXinput->bPressB == true)
		{
			float fDis;
			float fReach = powf(ATTACK_REACH, 2.0f);
			float fDisX = g_Player.pos.x - enemy->pos.x;
			float fDisZ = g_Player.pos.z - enemy->pos.z;
			fDisX = powf(fDisX, 2.0f);
			fDisZ = powf(fDisZ, 2.0f);
			fDis = fDisX + fDisZ;
			
			if (fDis < fReach)
			{
				g_Player.skill = SKILL_ATTACK;
				g_Player.bUseSkill = false;
			}
		}

		if (g_Player.nMP >= MAGIC_MP)
		{
			if (GetKeyboardTrigger(DIK_2) == TRUE || pXinput->bPressY == true)
			{
				g_Player.skill = SKILL_MAGICBALL;
				g_Player.nCooldown = MAX_COOLDOWN;
				g_Player.bUseSkill = false;
				SetCircle(SKILL_MAGICBALL);
			}
		}

		if (g_Player.nMP >= HEAL_MP)
		{
			if (GetKeyboardTrigger(DIK_3) == TRUE || pXinput->bPressX == true)
			{
				g_Player.skill = SKILL_HEAL;
				g_Player.nCooldown = MAX_COOLDOWN;
				g_Player.bUseSkill = false;
				SetCircle(SKILL_HEAL);
			}
		}
	}
		
	//物理攻撃
	if (g_Player.skill == SKILL_ATTACK)
	{
		//ダメージ量
		int nAttack = GetRandom(ATTACK_DAMAGE, ATTACK_DAMAGE + 200);

		g_Player.bChant = true;

		if (enemy->nLife - nAttack < 0)
		{	//攻撃が敵の残りHPを超えたとき0までのダメージに変換
			nAttack = enemy->nLife;
		}

		g_Player.nowMotion = MOTION_ACTION;
		enemy->nLife -= nAttack;
		g_Player.nCooldown = MAX_COOLDOWN;
		g_Player.skill = SKILL_NONE;
		g_Player.bChant = false;
	}

	//攻撃魔法
	if (g_Player.skill == SKILL_MAGICBALL)
	{
		if (g_Player.bChant == false)
		{
			g_Player.nChantCounter = (int)CHANT_TIMEMAGIC;
		}
		g_Player.nChantCounter--;
		g_Player.bChant = true;

		if (g_Player.nChantCounter == 0)
		{	//詠唱終了時に回復、クールダウンを設定
			SetBullet(D3DXVECTOR3(g_Player.pos.x + sinf(g_Player.rot.y) * -100, g_Player.pos.y + 70, g_Player.pos.z + cosf(g_Player.rot.y) * -100));
			g_Player.skill = SKILL_NONE;
			g_Player.bChant = false;
			g_Player.nMP -= MAGIC_MP;
		}
	}

	//回復魔法
	if (g_Player.skill == SKILL_HEAL)
	{
		//HP回復量
		int nHeal = HEAL_POWER;

		if (g_Player.bChant == false)
		{
			g_Player.nChantCounter = CHANT_TIMEHEAL;
		}
		g_Player.nChantCounter--;
		g_Player.bChant = true;

		if (g_Player.nLife + nHeal > LIFE_PLAYER)
		{	//HP上限を超えた回復を上限までの回復に変換
			nHeal = LIFE_PLAYER - g_Player.nLife;
		}

		if (g_Player.nChantCounter == 0)
		{	//詠唱終了時に回復、クールダウンを設定
			g_Player.nLife += nHeal;
			g_Player.skill = SKILL_NONE;
			g_Player.bChant = false;
			g_Player.nMP -= HEAL_MP;
			nCntEff = 30;
		}
	}

	if (nCntEff > 0)
	{
		SetEffect(D3DXVECTOR3(g_Player.pos.x, g_Player.pos.y + 50, g_Player.pos.z), D3DXCOLOR(0.0f, 1.f, 0.6f, 0.2f));
		nCntEff--;
	}
		
	if (g_Player.bChant == true)
	{	//詠唱中に動いたら詠唱中断
		if (g_Player.bMove == true)
		{
			g_Player.skill = SKILL_NONE;
			g_Player.nCooldown = 0;
			g_Player.bChant = false;

		}
	}
}

////////////////////////////////////////////////////////////////////////////////
//プレイヤーの移動処理
////////////////////////////////////////////////////////////////////////////////
void MovePlayer(void)
{
	CAMERA *camera = GetCamera();
	XinputGamepad *pXinput = GetXinputGamepad();
	ENEMY *enemy = GetEnemy();

	//位置を保存
	g_Player.posOld = g_Player.pos;

	if (g_Player.rotDest.y - g_Player.rot.y < -D3DX_PI)
	{// -3.14fより小さくなったとき値を3.14fにする
		g_Player.rotDest.y += D3DX_PI * 2.0f;
	}
	else if (g_Player.rotDest.y - g_Player.rot.y > D3DX_PI)
	{// 3.14fより大きくなったとき値を-3.14fにする
		g_Player.rotDest.y -= D3DX_PI * 2.0f;
	}
	// 向きの更新
	g_Player.rot.y += (g_Player.rotDest.y - g_Player.rot.y) * 0.08f;

	if (g_Player.rot.y < -D3DX_PI)
	{// -3.14fより小さくなったとき値に3.14fにする
		g_Player.rot.y += D3DX_PI * 2.0f;
	}
	else if (g_Player.rot.y > D3DX_PI)
	{// 3.14fより大きくなったとき値を-3.14fにする
		g_Player.rot.y -= D3DX_PI * 2.0f;
	}

	D3DXVECTOR3 vector = enemy->pos - g_Player.pos;
	float fAngle = atan2f(vector.x, vector.z);

	if(g_Player.skill == SKILL_MAGICBALL)
	{
		g_Player.rotDest.y = D3DX_PI + fAngle;
	}

	//移動
	if (pXinput->bPressLStick == true)
	{	//左スティックを傾けた方向に移動
		g_Player.pos.x -= sinf(camera->rot.y - pXinput->fAngleL) * PMOVE_SPEED;
		g_Player.pos.z -= cosf(camera->rot.y - pXinput->fAngleL) * PMOVE_SPEED;
		g_Player.rotDest.y = camera->rot.y - pXinput->fAngleL;
		g_Player.bMove = true;

		if (g_Player.nowMotion != MOTION_JUMP && g_Player.nowMotion != MOTION_ACTION)
		{	//ジャンプ以外
			g_Player.nowMotion = MOTION_MOVE;
		}
	}

	if (GetKeyboardPress(DIK_W) == TRUE)
	{
		if (GetKeyboardPress(DIK_A) == TRUE)
		{	//左前
			g_Player.pos.x += sinf(camera->rot.y + D3DXToRadian(-45)) * PMOVE_SPEED;
			g_Player.pos.z += cosf(camera->rot.y + D3DXToRadian(-45)) * PMOVE_SPEED;
			g_Player.rotDest.y = (D3DXToRadian(135) + camera->rot.y);
			g_Player.bMove = true;

			if (g_Player.nowMotion != MOTION_JUMP && g_Player.nowMotion != MOTION_ACTION)
			{
				g_Player.nowMotion = MOTION_MOVE;
			}
		}
		else if (GetKeyboardPress(DIK_D) == TRUE)
		{	//右前
			g_Player.pos.x += sinf(camera->rot.y + D3DXToRadian(45)) * PMOVE_SPEED;
			g_Player.pos.z += cosf(camera->rot.y + D3DXToRadian(45)) * PMOVE_SPEED;
			g_Player.rotDest.y = (D3DXToRadian(-135) + camera->rot.y);
			g_Player.bMove = true;

			if (g_Player.nowMotion != MOTION_JUMP && g_Player.nowMotion != MOTION_ACTION)
			{
				g_Player.nowMotion = MOTION_MOVE;
			}
		}
		else
		{	//前
			g_Player.pos.x += sinf(camera->rot.y) * PMOVE_SPEED;
			g_Player.pos.z += cosf(camera->rot.y) * PMOVE_SPEED;
			g_Player.rotDest.y = (D3DX_PI + camera->rot.y);
			g_Player.bMove = true;

			if (g_Player.nowMotion != MOTION_JUMP && g_Player.nowMotion != MOTION_ACTION)
			{
				g_Player.nowMotion = MOTION_MOVE;
			}
		}
	}
	else if (GetKeyboardPress(DIK_S) == TRUE)
	{
		if (GetKeyboardPress(DIK_A) == TRUE)
		{	//左後ろ
			g_Player.pos.x -= sinf(camera->rot.y + D3DXToRadian(45)) * PMOVE_SPEED;
			g_Player.pos.z -= cosf(camera->rot.y + D3DXToRadian(45)) * PMOVE_SPEED;
			g_Player.rotDest.y = (D3DXToRadian(45) + camera->rot.y);
			g_Player.bMove = true;

			if (g_Player.nowMotion != MOTION_JUMP && g_Player.nowMotion != MOTION_ACTION)
			{
				g_Player.nowMotion = MOTION_MOVE;
			}
		}
		else if (GetKeyboardPress(DIK_D) == TRUE)
		{	//右後ろ
			g_Player.pos.x -= sinf(camera->rot.y + D3DXToRadian(-45)) * PMOVE_SPEED;
			g_Player.pos.z -= cosf(camera->rot.y + D3DXToRadian(-45)) * PMOVE_SPEED;
			g_Player.rotDest.y = (D3DXToRadian(-45) + camera->rot.y);
			g_Player.bMove = true;

			if (g_Player.nowMotion != MOTION_JUMP && g_Player.nowMotion != MOTION_ACTION)
			{
				g_Player.nowMotion = MOTION_MOVE;
			}
		}
		else
		{	//後ろ
			g_Player.pos.x -= sinf(camera->rot.y) * PMOVE_SPEED;
			g_Player.pos.z -= cosf(camera->rot.y) * PMOVE_SPEED;
			g_Player.rotDest.y = (0.0f + camera->rot.y);
			g_Player.bMove = true;

			if (g_Player.nowMotion != MOTION_JUMP && g_Player.nowMotion != MOTION_ACTION)
			{
				g_Player.nowMotion = MOTION_MOVE;
			}
		}
	}
	else if (GetKeyboardPress(DIK_A) == TRUE)
	{	//左
		g_Player.pos.x -= sinf(camera->rot.y + D3DXToRadian(90)) * PMOVE_SPEED;
		g_Player.pos.z += cosf(camera->rot.y - D3DXToRadian(90)) * PMOVE_SPEED;
		g_Player.rotDest.y = (camera->rot.y + (D3DX_PI / 2));
		g_Player.bMove = true;

		if (g_Player.nowMotion != MOTION_JUMP && g_Player.nowMotion != MOTION_ACTION)
		{
			g_Player.nowMotion = MOTION_MOVE;
		}

	}
	else if (GetKeyboardPress(DIK_D) == TRUE)
	{	//右
		g_Player.pos.x += sinf(camera->rot.y + D3DXToRadian(90)) * PMOVE_SPEED;
		g_Player.pos.z -= cosf(camera->rot.y - D3DXToRadian(90)) * PMOVE_SPEED;
		g_Player.rotDest.y = (camera->rot.y + (-D3DX_PI / 2));
		g_Player.bMove = true;

		if (g_Player.nowMotion != MOTION_JUMP && g_Player.nowMotion != MOTION_ACTION
			)
		{
			g_Player.nowMotion = MOTION_MOVE;
		}
	}

	//移動範囲の制限
	for (int nCnt = 0; nCnt < MAX_INVI; nCnt++)
	{
		if (nCnt != MAX_INVI - 1)
		{
			fGaiseki[nCnt * 2] = ((aPos[nCnt + 1].z - aPos[nCnt].z) * (g_Player.pos.x - aPos[nCnt].x)) - ((aPos[nCnt + 1].x - aPos[nCnt].x) * (g_Player.pos.z - aPos[nCnt].z));
			fGaiseki[nCnt * 2 + 1] = ((aPos[nCnt + 1].z - aPos[nCnt].z) * (g_Player.posOld.x - aPos[nCnt].x)) - ((aPos[nCnt + 1].x - aPos[nCnt].x) * (g_Player.posOld.z - aPos[nCnt].z));

			if (fGaiseki[nCnt * 2] >= 0)
			{
				if (fGaiseki[nCnt * 2 + 1] <= 0)
				{
					g_Player.pos = g_Player.posOld;
				}
			}
		}
		else
		{
			fGaiseki[nCnt * 2] = ((aPos[0].z - aPos[nCnt].z) * (g_Player.pos.x - aPos[nCnt].x)) - ((aPos[0].x - aPos[nCnt].x) * (g_Player.pos.z - aPos[nCnt].z));
			fGaiseki[nCnt * 2 + 1] = ((aPos[0].z - aPos[nCnt].z) * (g_Player.posOld.x - aPos[nCnt].x)) - ((aPos[0].x - aPos[nCnt].x) * (g_Player.posOld.z - aPos[nCnt].z));

			if (fGaiseki[nCnt * 2] >= 0)
			{
				if (fGaiseki[nCnt * 2 + 1] <= 0)
				{
					g_Player.pos = g_Player.posOld;
				}
			}
		}
	}

	//ジャンプ
	if (g_Player.bJump == true)
	{
		if (pXinput->bPressA == true || GetKeyboardTrigger(DIK_SPACE) == true)
		{
			g_Player.fGravity += 20.0f;
			g_Player.bJump = false;
			g_Player.bMove = true;
			if (g_Player.nowMotion != MOTION_ACTION)
			{
				g_Player.nowMotion = MOTION_JUMP;
			}
		}
	}

	//重力加算
	g_Player.fGravity -= 1.0f;
	g_Player.pos.y += g_Player.fGravity;

	//押し戻す
	if (g_Player.pos.y < 0)
	{
		g_Player.fGravity = 0.0f;
		g_Player.bJump = true;
		g_Player.pos.y = g_Player.posOld.y;
	}
	if (CollisionObject(g_Player.pos, g_Player.posOld) == true)
	{
		g_Player.fGravity = 0.0f;
		g_Player.bJump = true;
		g_Player.pos.y = g_Player.posOld.y;
	}
}

////////////////////////////////////////////////////////////////////////////////
//モーションの切り替え
////////////////////////////////////////////////////////////////////////////////
void MotionPlayer(void)
{
	switch(g_Player.nowMotion)
	{
	case MOTION_NEUTRAL:	//ニュートラル
		MotionPlayerNeutral();
		break;
	case MOTION_MOVE:		//移動
		MotionPlayerMove();
		break;
	case MOTION_JUMP:		//ジャンプ
		MotionPlayerJump();
		break;
	case MOTION_ACTION:		//アクション
		MotionPlayerAction();
		break;
	}
}

////////////////////////////////////////////////////////////////////////////////
//ニュートラルモーション
////////////////////////////////////////////////////////////////////////////////
void MotionPlayerNeutral(void)
{
	static int nNextKey = 0;
	D3DXVECTOR3 diff[MAX_MODEL_PLAYER];
	D3DXVECTOR3 next[NEUT_KEY][MAX_MODEL_PLAYER];
	static int nFrame = 40;
	
	if (g_Player.bChant == false)
	{
		//キー1
		next[0][0] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		next[0][1] = D3DXVECTOR3(0.03f, 0.0f, 0.0f);
		next[0][2] = D3DXVECTOR3(0.03f, 0.0f, 0.5f);
		next[0][3] = D3DXVECTOR3(0.03f, 0.0f, -0.5f);
		next[0][4] = D3DXVECTOR3(0.03f, 0.0f, 0.0f);
		next[0][5] = D3DXVECTOR3(0.03f, 0.0f, 0.0f);

		//キー2
		next[1][0] = D3DXVECTOR3(-0.03f, 0.0f, 0.0f);
		next[1][1] = D3DXVECTOR3(-0.06f, 0.0f, 0.0f);
		next[1][2] = D3DXVECTOR3(0.03f, 0.0f, 0.79f);
		next[1][3] = D3DXVECTOR3(0.03f, 0.0f, -0.79f);
		next[1][4] = D3DXVECTOR3(0.03f, 0.0f, 0.0f);
		next[1][5] = D3DXVECTOR3(0.03f, 0.0f, 0.0f);
	}
	else if (g_Player.bChant == true)
	{
		//キー1
		next[0][0] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		next[0][1] = D3DXVECTOR3(0.03f, 0.0f, 0.0f);
		next[0][2] = D3DXVECTOR3(0.03f, -1.5f, 0.5f);
		next[0][3] = D3DXVECTOR3(0.03f, 0.0f, -0.5f);
		next[0][4] = D3DXVECTOR3(0.03f, 0.0f, 0.0f);
		next[0][5] = D3DXVECTOR3(0.03f, 0.0f, 0.0f);

		//キー2
		next[1][0] = D3DXVECTOR3(-0.03f, 0.0f, 0.0f);
		next[1][1] = D3DXVECTOR3(-0.06f, 0.0f, 0.0f);
		next[1][2] = D3DXVECTOR3(0.03f, -1.5f, 0.5f);
		next[1][3] = D3DXVECTOR3(0.03f, 0.0f, -0.79f);
		next[1][4] = D3DXVECTOR3(0.03f, 0.0f, 0.0f);
		next[1][5] = D3DXVECTOR3(0.03f, 0.0f, 0.0f);
	}
	
	for (int nCntNeut = 0; nCntNeut < MAX_MODEL_PLAYER; nCntNeut++)
	{
		diff[nCntNeut] = next[nNextKey][nCntNeut] - g_Player.aModel[nCntNeut].rot;
		g_Player.aModel[nCntNeut].rot += (diff[nCntNeut] / (float)nFrame);
	}
	nFrame--;

	if(nFrame == 0)
	{
		if (nNextKey == NEUT_KEY - 1)
		{
			nNextKey = 0;
		}
		else
		{
			nNextKey++;
		}
		nFrame = 40;
	}
}

////////////////////////////////////////////////////////////////////////////////
//移動モーション
////////////////////////////////////////////////////////////////////////////////
void MotionPlayerMove(void)
{
	static int nNextKey = 0;
	D3DXVECTOR3 diff[MAX_MODEL_PLAYER];
	D3DXVECTOR3 next[MOVE_KEY][MAX_MODEL_PLAYER];
	static int nFrame = 15;

	//キー1
	next[0][0] = D3DXVECTOR3(-0.3f, -0.16f, 0.0f);
	next[0][1] = D3DXVECTOR3(0.22f, 0.09f, 0.0f);
	next[0][2] = D3DXVECTOR3(2.1f, 0.0f, 1.31f);
	next[0][3] = D3DXVECTOR3(-1.07f, 0.0f, -1.32f);
	next[0][4] = D3DXVECTOR3(-2.02f, 0.0f, 0.1f);
	next[0][5] = D3DXVECTOR3(1.5f, 0.0f, -0.1f);

	//キー2
	next[1][0] = D3DXVECTOR3(-0.4f, 0.0f, 0.0f);
	next[1][1] = D3DXVECTOR3(0.31f, 0.0f, 0.0f);
	next[1][2] = D3DXVECTOR3(2.01f, 0.0f, 1.32f);
	next[1][3] = D3DXVECTOR3(-0.75f, 0.0f, -1.32f);
	next[1][4] = D3DXVECTOR3(-1.33f, 0.0f, 0.1f);
	next[1][5] = D3DXVECTOR3(0.83f, 0.0f, -0.1f);

	//キー3
	next[2][0] = D3DXVECTOR3(-0.3f, 0.15f, 0.0f);
	next[2][1] = D3DXVECTOR3(0.22f, -0.1f, 0.0f);
	next[2][2] = D3DXVECTOR3(-1.07f, 0.0f, 1.32f);
	next[2][3] = D3DXVECTOR3(2.1f, 0.0f, -1.32f);
	next[2][4] = D3DXVECTOR3(2.23f, 0.0f, 0.1f);
	next[2][5] = D3DXVECTOR3(-1.5f, 0.0f, -0.1f);

	//キー4
	next[3][0] = D3DXVECTOR3(-0.4f, 0.0f, 0.0f);
	next[3][1] = D3DXVECTOR3(0.31f, 0.0f, 0.0f);
	next[3][2] = D3DXVECTOR3(-0.75f, 0.0f, 1.32f);
	next[3][3] = D3DXVECTOR3(2.01f, 0.0f, -1.32f);
	next[3][4] = D3DXVECTOR3(1.33f, 0.0f, 0.1f);
	next[3][5] = D3DXVECTOR3(-0.83f, 0.0f, -0.1f);

	for (int nCntNeut = 0; nCntNeut < MAX_MODEL_PLAYER; nCntNeut++)
	{
		diff[nCntNeut] = next[nNextKey][nCntNeut] - g_Player.aModel[nCntNeut].rot;
		g_Player.aModel[nCntNeut].rot += (diff[nCntNeut] / (float)nFrame);
	}
	nFrame--;

	if (nFrame == 0)
	{
		if (nNextKey == MOVE_KEY - 1)
		{
			nNextKey = 0;
		}
		else
		{
			nNextKey++;
		}
		nFrame = 8;
	}
}

////////////////////////////////////////////////////////////////////////////////
//ジャンプモーション
////////////////////////////////////////////////////////////////////////////////
void MotionPlayerJump(void)
{
	static int nNextKey = 0;
	D3DXVECTOR3 diff[MAX_MODEL_PLAYER];
	D3DXVECTOR3 next[JUMP_KEY][MAX_MODEL_PLAYER];
	static int nFrame = 5;

	//キー1
	next[0][0] = D3DXVECTOR3(-0.03f, 0.0f, 0.0f);
	next[0][1] = D3DXVECTOR3(0.03f, 0.0f, 0.0f);
	next[0][2] = D3DXVECTOR3(0.0f, -0.25f, 0.82f);
	next[0][3] = D3DXVECTOR3(0.0f, 0.25f, -0.82f);
	next[0][4] = D3DXVECTOR3(0.13f, 0.0f, 0.0f);
	next[0][5] = D3DXVECTOR3(0.13f, 0.0f, 0.0f);

	//キー2
	next[1][0] = D3DXVECTOR3(0.06f, -0.06f, 0.0f);
	next[1][1] = D3DXVECTOR3(-0.06f, 0.06f, 0.0f);
	next[1][2] = D3DXVECTOR3(0.0f, -1.41f, -0.44f);
	next[1][3] = D3DXVECTOR3(-1.16f, 0.0f, -1.41f);
	next[1][4] = D3DXVECTOR3(-1.19f, 0.0f, 0.0f);
	next[1][5] = D3DXVECTOR3(1.1f, 0.0f, 0.0f);

	//キー3
	next[2][0] = D3DXVECTOR3(0.06f, -0.06f, 0.0f);
	next[2][1] = D3DXVECTOR3(-0.06f, 0.06f, 0.0f);
	next[2][2] = D3DXVECTOR3(0.0f, -1.41f, -0.64f);
	next[2][3] = D3DXVECTOR3(-1.36f, 0.0f, -1.41f);
	next[2][4] = D3DXVECTOR3(-1.19f, 0.0f, 0.0f);
	next[2][5] = D3DXVECTOR3(1.1f, 0.0f, 0.0f);

	//キー4
	next[3][0] = D3DXVECTOR3(0.06f, -0.06f, 0.0f);
	next[3][1] = D3DXVECTOR3(-0.06f, 0.06f, 0.0f);
	next[3][2] = D3DXVECTOR3(0.0f, -1.41f, -0.64f);
	next[3][3] = D3DXVECTOR3(-1.36f, 0.0f, -1.41f);
	next[3][4] = D3DXVECTOR3(-1.19f, 0.0f, 0.0f);
	next[3][5] = D3DXVECTOR3(1.1f, 0.0f, 0.0f);

	//キー5
	next[4][0] = D3DXVECTOR3(0.06f, -0.06f, 0.0f);
	next[4][1] = D3DXVECTOR3(-0.06f, 0.06f, 0.0f);
	next[4][2] = D3DXVECTOR3(0.0f, -1.41f, -0.64f);
	next[4][3] = D3DXVECTOR3(-1.36f, 0.0f, -1.41f);
	next[4][4] = D3DXVECTOR3(-1.19f, 0.0f, 0.0f);
	next[4][5] = D3DXVECTOR3(1.1f, 0.0f, 0.0f);

	for (int nCntNeut = 0; nCntNeut < MAX_MODEL_PLAYER; nCntNeut++)
	{
		diff[nCntNeut] = next[nNextKey][nCntNeut] - g_Player.aModel[nCntNeut].rot;
		g_Player.aModel[nCntNeut].rot += (diff[nCntNeut] / (float)nFrame);
	}
	nFrame--;

	if (nFrame == 0)
	{
		if (nNextKey == JUMP_KEY - 1)
		{
			g_Player.nowMotion = MOTION_NEUTRAL;
			nNextKey = 0;
		}
		else
		{
			nNextKey++;
		}
		nFrame = 5;
	}
}

////////////////////////////////////////////////////////////////////////////////
//アクションモーション
////////////////////////////////////////////////////////////////////////////////
void MotionPlayerAction(void)
{
	static int nowKey;
	static int nNextKey = 0;
	D3DXVECTOR3 diff[MAX_MODEL_PLAYER];
	D3DXVECTOR3 next[ACTION_KEY][MAX_MODEL_PLAYER];
	static int nFrame = 12;

	//キー1
	next[0][0] = D3DXVECTOR3(0.0f, 0.31f, 0.0f);
	next[0][1] = D3DXVECTOR3(0.0f, -0.31f, 0.0f);
	next[0][2] = D3DXVECTOR3(0.0f, 0.0f, 1.04f);
	next[0][3] = D3DXVECTOR3(0.0f, 0.0f, -0.66f);
	next[0][4] = D3DXVECTOR3(-0.38f, -0.16f, 0.0f);
	next[0][5] = D3DXVECTOR3(-0.16f, 0.0f, 0.0f);

	//キー2
	next[1][0] = D3DXVECTOR3(0.0f, -0.41f, 0.0f);
	next[1][1] = D3DXVECTOR3(0.0f, 0.22f, 0.0f);
	next[1][2] = D3DXVECTOR3(0.0f, -1.36f, 0.0f);
	next[1][3] = D3DXVECTOR3(0.0f, 0.0f, -1.1f);
	next[1][4] = D3DXVECTOR3(-0.75f, 0.22f, 0.0f);
	next[1][5] = D3DXVECTOR3(0.75f, 0.22f, 0.0f);
	
	//キー3
	next[2][0] = D3DXVECTOR3(0.0f, -0.41f, 0.0f);
	next[2][1] = D3DXVECTOR3(0.0f, 0.22f, 0.0f);
	next[2][2] = D3DXVECTOR3(0.0f, -1.36f, 0.0f);
	next[2][3] = D3DXVECTOR3(0.0f, 0.0f, -1.1f);
	next[2][4] = D3DXVECTOR3(-0.75f, 0.22f, 0.0f);
	next[2][5] = D3DXVECTOR3(0.75f, 0.22f, 0.0f);
	
	for (int nCntNeut = 0; nCntNeut < MAX_MODEL_PLAYER; nCntNeut++)
	{
		diff[nCntNeut] = next[nNextKey][nCntNeut] - g_Player.aModel[nCntNeut].rot;
		g_Player.aModel[nCntNeut].rot += (diff[nCntNeut] / (float)nFrame);
	}
	nFrame--;

	if (nFrame == 0)
	{
		if (nNextKey == ACTION_KEY - 1)
		{
			g_Player.nowMotion = MOTION_NEUTRAL;
			nNextKey = 0;
		}
		else
		{
			nNextKey++;
		}
		nFrame = 12;
	}
}

////////////////////////////////////////////////////////////////////////////////
//プレイヤーの位置を取得
////////////////////////////////////////////////////////////////////////////////
D3DXVECTOR3 *GetPosPlayer(void)
{
	return &g_Player.pos;
}

////////////////////////////////////////////////////////////////////////////////
//プレイヤーの過去の位置を取得
////////////////////////////////////////////////////////////////////////////////
D3DXVECTOR3 *GetPosOld(void)
{
	return &g_Player.posOld;
}

////////////////////////////////////////////////////////////////////////////////
//プレイヤーの向きを取得
////////////////////////////////////////////////////////////////////////////////
D3DXVECTOR3 *GetRotPlayer(void)
{
	return &g_Player.rot;
}

////////////////////////////////////////////////////////////////////////////////
//プレイヤーを取得
////////////////////////////////////////////////////////////////////////////////
PLAYER *GetPlayer(void)
{
	return &g_Player;
}

////////////////////////////////////////////////////////////////////////////////
//外積
////////////////////////////////////////////////////////////////////////////////
float *GetGaiseki(void)
{
	return &fGaiseki[0];
}

////////////////////////////////////////////////////////////////////////////////
//ランダムな数値を取得
////////////////////////////////////////////////////////////////////////////////
int GetRandom(int min, int max)
{
	static int nNum;

	if (nNum == 0)
	{
		srand((unsigned int)time(NULL));
		nNum = 1;
	}

	return min + (rand() * (max - min + 1) / (1 + RAND_MAX));
}