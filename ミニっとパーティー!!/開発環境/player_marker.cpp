//-------------------------------------------------------------------
//
// �v���C���[�}�[�J�[ (player_marker.cpp)
// Author:Itsuki Takaiwa
//
//-------------------------------------------------------------------
#include "player_marker.h"
#include "player.h"
#include "gamepad.h"
#include "chara_select_frame.h"

//-------------------------------------------------------------------
// �}�N����`
//-------------------------------------------------------------------
#define MAX_PLAYER_MARKER		(4)						// �v���C���[�}�[�J�[�̍ő�l

#define PLAYER_MARKER_SIZE_X	(10.0f)					// �v���C���[�}�[�J�[�̃T�C�Y(��)
#define PLAYER_MARKER_SIZE_Y	(10.0f)					// �v���C���[�}�[�J�[�̃T�C�Y(����)

#define PLAYER_MARKER_HEIGHT	(100.0f)					// �v���C���[�}�[�J�[�̈ʒu����

//-----------------------------------------------------------------
// �O���[�o���ϐ�
//-----------------------------------------------------------------
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayerMarker = NULL;				// �v���C���[�}�[�J�[�̃e�N�X�`���̃|�C���^
LPDIRECT3DTEXTURE9 g_pTexturePlayerMarker[MAX_PLAYER_MARKER] = {};	// �v���C���[�}�[�J�[�̒��_�o�b�t�@�̃|�C���^
PLAYER_MARKER g_aPlayerMarker[MAX_PLAYER_MARKER];					// �v���C���[�}�[�J�[�̏��
int g_nCntPlayerMarker;												// �z�u����v���C���[�}�[�J�[�̐�

//-----------------------------------------------------------------
// �G�̏���������
//-----------------------------------------------------------------
HRESULT InitPlayerMarker(void)
{
	// �ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;
	Player *pPlayer;

	// �ϐ��̎󂯓n��
	pDevice = GetDevice();
	pPlayer = GetPlayer();

	// �Z���N�g���[�h���̎擾
	int nNumPlayer = GetFrame();

	g_nCntPlayerMarker = nNumPlayer;

	// �ϐ��̏�����
	for (int nCnt = 0; nCnt < g_nCntPlayerMarker; nCnt++,pPlayer++)
	{
		g_aPlayerMarker[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aPlayerMarker[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aPlayerMarker[nCnt].fWidth = PLAYER_MARKER_SIZE_X;
		g_aPlayerMarker[nCnt].fHeight = PLAYER_MARKER_SIZE_X;
	}

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/player_1.png", &g_pTexturePlayerMarker[0]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/player_2.png", &g_pTexturePlayerMarker[1]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/player_3.png", &g_pTexturePlayerMarker[2]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/player_4.png", &g_pTexturePlayerMarker[3]);


	// ���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * MAX_VERTEX * g_nCntPlayerMarker, // �m�ۂ���o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,								// ���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pVtxBuffPlayerMarker,
		NULL)))
	{
		return E_FAIL;
	}

	// �\���̂̃|�C���^�ϐ�
	VERTEX_3D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPlayerMarker->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntPlayerMarker = 0; nCntPlayerMarker < g_nCntPlayerMarker; nCntPlayerMarker++)
	{
		// ���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_aPlayerMarker[nCntPlayerMarker].pos.x - g_aPlayerMarker[nCntPlayerMarker].fWidth, g_aPlayerMarker[nCntPlayerMarker].pos.y + g_aPlayerMarker[nCntPlayerMarker].fHeight, g_aPlayerMarker[nCntPlayerMarker].pos.z);
		pVtx[1].pos = D3DXVECTOR3(g_aPlayerMarker[nCntPlayerMarker].pos.x + g_aPlayerMarker[nCntPlayerMarker].fWidth, g_aPlayerMarker[nCntPlayerMarker].pos.y + g_aPlayerMarker[nCntPlayerMarker].fHeight, g_aPlayerMarker[nCntPlayerMarker].pos.z);
		pVtx[2].pos = D3DXVECTOR3(g_aPlayerMarker[nCntPlayerMarker].pos.x - g_aPlayerMarker[nCntPlayerMarker].fWidth, g_aPlayerMarker[nCntPlayerMarker].pos.y - g_aPlayerMarker[nCntPlayerMarker].fHeight, g_aPlayerMarker[nCntPlayerMarker].pos.z);
		pVtx[3].pos = D3DXVECTOR3(g_aPlayerMarker[nCntPlayerMarker].pos.x + g_aPlayerMarker[nCntPlayerMarker].fWidth, g_aPlayerMarker[nCntPlayerMarker].pos.y - g_aPlayerMarker[nCntPlayerMarker].fHeight, g_aPlayerMarker[nCntPlayerMarker].pos.z);

		// �@���x�N�g���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		// ���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// �e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		// ���̏��ɍX�V
		pVtx += 4;
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPlayerMarker->Unlock();

	return S_OK;
}

//-----------------------------------------------------------------
// �G�̏I������
//-----------------------------------------------------------------
void UninitPlayerMarker(void)
{
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffPlayerMarker != NULL)
	{
		g_pVtxBuffPlayerMarker->Release();
		g_pVtxBuffPlayerMarker = NULL;
	}

	// �e�N�X�`���̊J��
	for (int nCnt = 0; nCnt < MAX_PLAYER_MARKER; nCnt++)
	{
		if (g_pTexturePlayerMarker[nCnt] != NULL)
		{
			g_pTexturePlayerMarker[nCnt]->Release();
			g_pTexturePlayerMarker[nCnt] = NULL;
		}
	}
}

//-----------------------------------------------------------------
// �G�̍X�V����
//-----------------------------------------------------------------
void UpdatePlayerMarker(void)
{
	// �\���̂̃|�C���^�ϐ�
	PLAYER_MARKER *pPlayerMarker = &g_aPlayerMarker[0];
	Player *pPlayer = GetPlayer();

	for (int nCntPlayerMarker = 0; nCntPlayerMarker < g_nCntPlayerMarker; nCntPlayerMarker++, pPlayerMarker++,pPlayer++)
	{
		// �ʒu�̍X�V
		pPlayerMarker->pos.x = pPlayer->pos.x;
		pPlayerMarker->pos.y = pPlayer->pos.y + PLAYER_MARKER_HEIGHT;
		pPlayerMarker->pos.z = pPlayer->pos.z;
	}
}

//-----------------------------------------------------------------
// �G�̕`�揈��
//-----------------------------------------------------------------
void DrawPlayerMarker(void)
{
	// �ϐ��錾
	PLAYER_MARKER *pPlayerMarker = &g_aPlayerMarker[0];
	LPDIRECT3DDEVICE9 pDevice;					// �f�o�C�X�ւ̃|�C���^
	D3DXMATRIX mtxView;							// �r���[�}�g���b�N�X�擾�p
	D3DXMATRIX mtxScaling, mtxTrans;			// �v�Z�p�}�g���b�N�X

	// �ϐ��̎󂯓n��
	pDevice = GetDevice();

	// ���C�g���I�t�ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// Z�o�b�t�@��K�p
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	for (int nCntPlayerMarker = 0; nCntPlayerMarker < g_nCntPlayerMarker; nCntPlayerMarker++, pPlayerMarker++)
	{
		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&pPlayerMarker->mtxWorld);

		// �r���[�}�g���b�N�X�̎擾
		pDevice->GetTransform(D3DTS_VIEW, &mtxView);
#if 0
		// �|���S�����J�����ɑ΂��Đ��ʂɌ�����
		D3DXMatrixInverse(&pBillboard->mtxWorld, NULL, &mtxView);
		pBillboard->mtxWorld._41 = 0.0f;
		pBillboard->mtxWorld._42 = 0.0f;
		pBillboard->mtxWorld._43 = 0.0f;
#else
		pPlayerMarker->mtxWorld._11 = mtxView._11;
		pPlayerMarker->mtxWorld._12 = mtxView._21;
		pPlayerMarker->mtxWorld._13 = mtxView._31;
		pPlayerMarker->mtxWorld._21 = mtxView._12;
		pPlayerMarker->mtxWorld._22 = mtxView._22;
		pPlayerMarker->mtxWorld._23 = mtxView._32;
		pPlayerMarker->mtxWorld._31 = mtxView._13;
		pPlayerMarker->mtxWorld._32 = mtxView._23;
		pPlayerMarker->mtxWorld._33 = mtxView._33;
#endif
		// �ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, pPlayerMarker->pos.x, pPlayerMarker->pos.y, pPlayerMarker->pos.z);
		D3DXMatrixMultiply(&pPlayerMarker->mtxWorld, &pPlayerMarker->mtxWorld, &mtxTrans);

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &pPlayerMarker->mtxWorld);

		// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_pVtxBuffPlayerMarker, 0, sizeof(VERTEX_3D));

		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_3D);

		// �|���S���̕`��
		pDevice->SetTexture(0, g_pTexturePlayerMarker[nCntPlayerMarker]);
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntPlayerMarker * 4, 2);
	}
	// �W���ɖ߂�
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	// ���C�g���I���ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}