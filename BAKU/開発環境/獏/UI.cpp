////////////////////////////////////////////////////////////////////////////////
//
//Contents	: UI�̏��� [UI.cpp]
//Author	: ShotaFuruichi
//Since		: 2021/02/17
//
////////////////////////////////////////////////////////////////////////////////
#include "UI.h"
#include "game.h"
#include "player.h"
#include "enemy.h"
#include <string.h>
#include "xinput_pad.h"

////////////////////////////////////////////////////////////////////////////////
//�}�N����`
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//�O���[�o���ϐ�
////////////////////////////////////////////////////////////////////////////////
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffUI[UI_MAX] = {};			//���_���
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffCooldown[SKILL_MAX] = {};	//���_���
LPDIRECT3DTEXTURE9 g_pTextureUI[UI_MAX] = {};				//�e�N�X�`�����
LPD3DXFONT g_pUIFont = NULL;								//�t�H���g�ւ̃|�C���^

////////////////////////////////////////////////////////////////////////////////
//UI�̏���������
////////////////////////////////////////////////////////////////////////////////
HRESULT InitUI(void)
{
	//�ϐ��錾
	VERTEX_2D *pVtx;
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\HP.png", &g_pTextureUI[UI_HP]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\MP.png", &g_pTextureUI[UI_MP]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\EnemyHP.png", &g_pTextureUI[UI_ENEMYHP]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\gauge.png", &g_pTextureUI[UI_HPGAUGE]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\gauge.png", &g_pTextureUI[UI_MPGAUGE]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\gauge.png", &g_pTextureUI[UI_ENEMYHPGAUGE]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\fist.png", &g_pTextureUI[UI_SKILLACTION]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\fire.png", &g_pTextureUI[UI_SKILLBALL]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\cross.png", &g_pTextureUI[UI_SKILLHEAL]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\ChantGauge_MAGIC.png", &g_pTextureUI[UI_CHANTMAGIC]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\ChantGauge_HEAL.png", &g_pTextureUI[UI_CHANTHEAL]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\ChantGauge.png", &g_pTextureUI[UI_CHANTGAUGE]);


	for (int nCntUI = 0; nCntUI < UI_MAX; nCntUI++)
	{
		//���_�o�b�t�@�̐���
		if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffUI[nCntUI], NULL)))
		{
			return E_FAIL;
		}

		//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		g_pVtxBuffUI[nCntUI]->Lock(0, 0, (void**)&pVtx, 0);

		//���_���W�̐ݒ�
		switch (nCntUI)
		{
		case UI_HP:
			SetVertexHP();
			break;

		case UI_MP:
			SetVertexMP();
			break;

		case UI_ENEMYHP:
			SetVertexENEMYHP();
			break;

		case UI_HPGAUGE:
			SetVertexHPGauge();
			break;

		case UI_MPGAUGE:
			SetVertexMPGauge();
			break;

		case UI_ENEMYHPGAUGE:
			SetVertexEnemyHPGauge();
			break;

		case UI_SKILLACTION:
			SetVertexAction();
			break;

		case UI_SKILLBALL:
			SetVertexMagic();
			break;

		case UI_SKILLHEAL:
			SetVertexHeal();
			break;

		case UI_CHANTMAGIC:
			SetVertexChantMagic();
			break;

		case UI_CHANTHEAL:
			SetVertexChantHeal();
			break;

		case UI_CHANTGAUGE:
			SetVertexChant();
			break;

		default:
			break;
		}

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//���_���̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

		//���_�o�b�t�@���A�����b�N����
		g_pVtxBuffUI[nCntUI]->Unlock();
	}

	for (int nCntUI = 0; nCntUI < SKILL_MAX; nCntUI++)
	{
		//���_�o�b�t�@�̐���
		if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffCooldown[nCntUI], NULL)))
		{
			return E_FAIL;
		}

		//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		g_pVtxBuffCooldown[nCntUI]->Lock(0, 0, (void**)&pVtx, 0);

		//���_���W�̐ݒ�
		SetVertexCooldown(nCntUI);

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_���̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

		//���_�o�b�t�@���A�����b�N����
		g_pVtxBuffCooldown[nCntUI]->Unlock();
	}

	//�����\��
	D3DXCreateFont(pDevice, 30, 0, FW_NORMAL, 1, FALSE, SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "�l�r�o�S�V�b�N", &g_pUIFont);

	return S_OK;
}

////////////////////////////////////////////////////////////////////////////////
//UI�̏I������
////////////////////////////////////////////////////////////////////////////////
void UninitUI(void)
{
	for (int nCntUI = 0; nCntUI < UI_MAX; nCntUI++)
	{
		//���_�o�b�t�@�̊J��
		if (g_pVtxBuffUI[nCntUI] != NULL)
		{
			g_pVtxBuffUI[nCntUI]->Release();	//�J��
			g_pVtxBuffUI[nCntUI] = NULL;		//������
		}
		if (g_pTextureUI[nCntUI] != NULL)
		{
			g_pTextureUI[nCntUI]->Release();	//�J��
			g_pTextureUI[nCntUI] = NULL;		//������
		}
	}

	for (int nCntUI = 0; nCntUI < SKILL_MAX; nCntUI++)
	{
		//���_�o�b�t�@�̊J��
		if (g_pVtxBuffCooldown[nCntUI] != NULL)
		{
			g_pVtxBuffCooldown[nCntUI]->Release();	//�J��
			g_pVtxBuffCooldown[nCntUI] = NULL;		//������
		}
	}

	//�t�H���g�̊J��
	if (g_pUIFont != NULL)
	{
		g_pUIFont->Release();			//�J��
		g_pUIFont = NULL;				//������
	}
}

////////////////////////////////////////////////////////////////////////////////
//UI�̍X�V����
////////////////////////////////////////////////////////////////////////////////
void UpdateUI(void)
{
	SetVertexHP();
	SetVertexMP();
	SetVertexENEMYHP();
	SetVertexHPGauge();
	SetVertexMPGauge();
	SetVertexEnemyHPGauge();
	SetVertexChant();
	for (int nCntUI = 0; nCntUI < SKILL_MAX; nCntUI++)
	{
		SetVertexCooldown(nCntUI);
	}

}

////////////////////////////////////////////////////////////////////////////////
//UI�̕`�揈��
////////////////////////////////////////////////////////////////////////////////
void DrawUI(void)
{
	//�ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;
	PLAYER *player = GetPlayer();
	ENEMY *enemy = GetEnemy();
	bool bUsePad = GetUseGamepad();

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	for (int nCntUI = 0; nCntUI < UI_MAX; nCntUI++)
	{
		//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_pVtxBuffUI[nCntUI], 0, sizeof(VERTEX_2D));

		//���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureUI[nCntUI]);

		//�|���S���̕`��
		if (nCntUI == UI_CHANTGAUGE || nCntUI == UI_CHANTMAGIC || nCntUI == UI_CHANTHEAL)
		{
			if (nCntUI != UI_CHANTHEAL)
			{
				if (player->skill == SKILL_MAGICBALL)
				{
					pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
				}
			}
			if (nCntUI != UI_CHANTMAGIC)
			{
				if (player->skill == SKILL_HEAL)
				{
					pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
				}
			}
		}
		else
		{
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
		}
	}


	for (int nCntUI = 0; nCntUI < SKILL_MAX; nCntUI++)
	{
		//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_pVtxBuffCooldown[nCntUI], 0, sizeof(VERTEX_2D));

		//���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, NULL);

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}

	RECT rect = {450, 840, 1920, 950};    // �\���������͈�

	char aStr[256];
	wsprintf(&aStr[0], "HP:%d                                               MP:%d", player->nLife, player->nMP);

	//�e�L�X�g�̕`��
	g_pUIFont->DrawTextA(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));

	rect = { 680, 25, 1920, 100 };    // �\���������͈�

	wsprintf(&aStr[0], "[BOSS] HP:%d\n", enemy->nLife);

	//�e�L�X�g�̕`��
	g_pUIFont->DrawTextA(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));

	rect = { 690, 980, 1920, 1080 };    // �\���������͈�

	if (bUsePad == true)
	{
		wsprintf(&aStr[0], "B                           Y                           X");
	}
	else
	{
		wsprintf(&aStr[0], "1                            2                           3");
	}

	//�e�L�X�g�̕`��
	g_pUIFont->DrawTextA(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
}

////////////////////////////////////////////////////////////////////////////////
//HP�Q�[�W�̘g�̒��_���W
////////////////////////////////////////////////////////////////////////////////
void SetVertexHPGauge(void)
{
	//�ϐ��錾
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffUI[UI_HPGAUGE]->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(430, 845, 0);
	pVtx[1].pos = D3DXVECTOR3(430, 800, 0);
	pVtx[2].pos = D3DXVECTOR3(950, 845, 0);
	pVtx[3].pos = D3DXVECTOR3(950, 800, 0);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffUI[UI_HPGAUGE]->Unlock();
}

////////////////////////////////////////////////////////////////////////////////
//MP�Q�[�W�̘g�̒��_���W
////////////////////////////////////////////////////////////////////////////////
void SetVertexMPGauge(void)
{
	//�ϐ��錾
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffUI[UI_MPGAUGE]->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(970, 845, 0);
	pVtx[1].pos = D3DXVECTOR3(970, 800, 0);
	pVtx[2].pos = D3DXVECTOR3(1490, 845, 0);
	pVtx[3].pos = D3DXVECTOR3(1490, 800, 0);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffUI[UI_MPGAUGE]->Unlock();
}

////////////////////////////////////////////////////////////////////////////////
//�G��HP�Q�[�W�̘g�̒��_���W
////////////////////////////////////////////////////////////////////////////////
void SetVertexEnemyHPGauge(void)
{
	//�ϐ��錾
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffUI[UI_ENEMYHPGAUGE]->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(660, 95, 0);
	pVtx[1].pos = D3DXVECTOR3(660, 50, 0);
	pVtx[2].pos = D3DXVECTOR3(1280, 95, 0);
	pVtx[3].pos = D3DXVECTOR3(1280, 50, 0);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffUI[UI_ENEMYHPGAUGE]->Unlock();
}

////////////////////////////////////////////////////////////////////////////////
//HP�̒��_���W
////////////////////////////////////////////////////////////////////////////////
void SetVertexHP(void)
{
	//�ϐ��錾
	VERTEX_2D *pVtx;
	PLAYER *player = GetPlayer();
 	float fHP;

	fHP = (float)(player->nLife / (LIFE_PLAYER / 100));
	fHP = fHP * 5;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffUI[UI_HP]->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(440, 850, 0);
	pVtx[1].pos = D3DXVECTOR3(440, 800, 0);
	pVtx[2].pos = D3DXVECTOR3(440 + fHP, 850, 0);
	pVtx[3].pos = D3DXVECTOR3(440 + fHP, 800, 0);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffUI[UI_HP]->Unlock();
}

////////////////////////////////////////////////////////////////////////////////
//MP�̒��_���W
////////////////////////////////////////////////////////////////////////////////
void SetVertexMP(void)
{
	//�ϐ��錾
	VERTEX_2D *pVtx;
	PLAYER *player = GetPlayer();
	float fMP;

	fMP = (float)(player->nMP / (MP_PLAYER / 100));
	fMP = fMP * 5;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffUI[UI_MP]->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(980, 850, 0);
	pVtx[1].pos = D3DXVECTOR3(980, 800, 0);
	pVtx[2].pos = D3DXVECTOR3(980 + fMP, 850, 0);
	pVtx[3].pos = D3DXVECTOR3(980 + fMP, 800, 0);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffUI[UI_MP]->Unlock();
}

////////////////////////////////////////////////////////////////////////////////
//�G��HP�̒��_���W
////////////////////////////////////////////////////////////////////////////////
void SetVertexENEMYHP(void)
{
	//�ϐ��錾
	VERTEX_2D *pVtx;
	ENEMY *enemy = GetEnemy();
	float fEneHP;

	fEneHP = (float)(enemy->nLife / (LIFE_ENEMY / 100));
	fEneHP = fEneHP * 6;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffUI[UI_ENEMYHP]->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(670, 93, 0);
	pVtx[1].pos = D3DXVECTOR3(670, 50, 0);
	pVtx[2].pos = D3DXVECTOR3(670 + fEneHP, 93, 0);
	pVtx[3].pos = D3DXVECTOR3(670 + fEneHP, 50, 0);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffUI[UI_ENEMYHP]->Unlock();
}

////////////////////////////////////////////////////////////////////////////////
//�A�N�V�����X�L���̒��_���W
////////////////////////////////////////////////////////////////////////////////
void SetVertexAction(void)
{
	//�ϐ��錾
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffUI[UI_SKILLACTION]->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(650, 980, 0);
	pVtx[1].pos = D3DXVECTOR3(650, 880, 0);
	pVtx[2].pos = D3DXVECTOR3(750, 980, 0);
	pVtx[3].pos = D3DXVECTOR3(750, 880, 0);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffUI[UI_SKILLACTION]->Unlock();
}

////////////////////////////////////////////////////////////////////////////////
//�U�����@�X�L���̒��_���W
////////////////////////////////////////////////////////////////////////////////
void SetVertexMagic(void)
{
	//�ϐ��錾
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffUI[UI_SKILLBALL]->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(910, 980, 0);
	pVtx[1].pos = D3DXVECTOR3(910, 880, 0);
	pVtx[2].pos = D3DXVECTOR3(1010, 980, 0);
	pVtx[3].pos = D3DXVECTOR3(1010, 880, 0);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffUI[UI_SKILLBALL]->Unlock();
}

////////////////////////////////////////////////////////////////////////////////
//�񕜖��@�X�L���̒��_���W
////////////////////////////////////////////////////////////////////////////////
void SetVertexHeal(void)
{
	//�ϐ��錾
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffUI[UI_SKILLHEAL]->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(1170, 980, 0);
	pVtx[1].pos = D3DXVECTOR3(1170, 880, 0);
	pVtx[2].pos = D3DXVECTOR3(1270, 980, 0);
	pVtx[3].pos = D3DXVECTOR3(1270, 880, 0);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffUI[UI_SKILLHEAL]->Unlock();
}

////////////////////////////////////////////////////////////////////////////////
//�N�[���_�E���̒��_���W
////////////////////////////////////////////////////////////////////////////////
void SetVertexCooldown(int nIdx)
{
	//�ϐ��錾
	VERTEX_2D *pVtx;
	PLAYER *player = GetPlayer();

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffCooldown[nIdx]->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	switch (nIdx)
	{
	case 0:
		pVtx[0].pos = D3DXVECTOR3(660, 972, 0);
		pVtx[1].pos = D3DXVECTOR3(660, 890, 0);
		pVtx[2].pos = D3DXVECTOR3(742, 972, 0);
		pVtx[3].pos = D3DXVECTOR3(742, 890, 0);
		break;

	case 1:
		pVtx[0].pos = D3DXVECTOR3(920, 972, 0);
		pVtx[1].pos = D3DXVECTOR3(920, 890, 0);
		pVtx[2].pos = D3DXVECTOR3(1002, 972, 0);
		pVtx[3].pos = D3DXVECTOR3(1002, 890, 0);
		break;

	case 2:
		pVtx[0].pos = D3DXVECTOR3(1180, 972, 0);
		pVtx[1].pos = D3DXVECTOR3(1180, 890, 0);
		pVtx[2].pos = D3DXVECTOR3(1262, 972, 0);
		pVtx[3].pos = D3DXVECTOR3(1262, 890, 0);
		break;

	default:
		pVtx[0].pos = D3DXVECTOR3(10000, 980, 0);
		pVtx[1].pos = D3DXVECTOR3(10000, 880, 0);
		pVtx[2].pos = D3DXVECTOR3(10000, 980, 0);
		pVtx[3].pos = D3DXVECTOR3(10000, 880, 0);
		break;
	}

	float fCooldown = ((float)player->nCooldown / (float)MAX_COOLDOWN);

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, fCooldown);
	pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, fCooldown);
	pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, fCooldown);
	pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, fCooldown);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffCooldown[nIdx]->Unlock();
}

////////////////////////////////////////////////////////////////////////////////
//�U�����@�r�����̃Q�[�W�̘g�̒��_���W
////////////////////////////////////////////////////////////////////////////////
void SetVertexChantMagic(void)
{
	//�ϐ��錾
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffUI[UI_CHANTMAGIC]->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(425, 800, 0);
	pVtx[1].pos = D3DXVECTOR3(425, 700, 0);
	pVtx[2].pos = D3DXVECTOR3(835, 800, 0);
	pVtx[3].pos = D3DXVECTOR3(835, 700, 0);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffUI[UI_CHANTMAGIC]->Unlock();
}

///////////////////////////////////////////////////////////////////////////////
//�񕜖��@�r�����̃Q�[�W�̘g�̒��_���W
////////////////////////////////////////////////////////////////////////////////
void SetVertexChantHeal(void)
{
	//�ϐ��錾
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffUI[UI_CHANTHEAL]->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(425, 800, 0);
	pVtx[1].pos = D3DXVECTOR3(425, 700, 0);
	pVtx[2].pos = D3DXVECTOR3(835, 800, 0);
	pVtx[3].pos = D3DXVECTOR3(835, 700, 0);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffUI[UI_CHANTHEAL]->Unlock();
}

///////////////////////////////////////////////////////////////////////////////
//���@�r�����̃Q�[�W�̒��_���W
////////////////////////////////////////////////////////////////////////////////
void SetVertexChant(void)
{
	//�ϐ��錾
	VERTEX_2D *pVtx;
	PLAYER *player = GetPlayer();
	float fMagic = (((float)player->nChantCounter / (float)CHANT_TIMEMAGIC) * 400.0f);
	float fHeal = (((float)player->nChantCounter / (float)CHANT_TIMEHEAL) * 400.0f);

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffUI[UI_CHANTGAUGE]->Lock(0, 0, (void**)&pVtx, 0);

	if (player->skill == SKILL_MAGICBALL)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(430, 790, 0);
		pVtx[1].pos = D3DXVECTOR3(430, 770, 0);
		pVtx[2].pos = D3DXVECTOR3(830 - fMagic, 790, 0);
		pVtx[3].pos = D3DXVECTOR3(830 - fMagic, 770, 0);
	}
	else if (player->skill == SKILL_HEAL)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(430, 790, 0);
		pVtx[1].pos = D3DXVECTOR3(430, 770, 0);
		pVtx[2].pos = D3DXVECTOR3(830 - fHeal, 790, 0);
		pVtx[3].pos = D3DXVECTOR3(830 - fHeal, 770, 0);
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffUI[UI_CHANTGAUGE]->Unlock();
}