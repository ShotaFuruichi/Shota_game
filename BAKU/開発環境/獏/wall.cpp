////////////////////////////////////////////////////////////////////////////////
//
//Contents	: �ǂ̏��� [wall.cpp]
//Author	: ShotaFuruichi
//Since		: 2020/11/17
//
////////////////////////////////////////////////////////////////////////////////
#include "wall.h"

////////////////////////////////////////////////////////////////////////////////
//�}�N����`
////////////////////////////////////////////////////////////////////////////////
#define MAX_WALL (4)

////////////////////////////////////////////////////////////////////////////////
//�O���[�o���ϐ�
////////////////////////////////////////////////////////////////////////////////
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffWall= NULL;	//���_���
LPDIRECT3DTEXTURE9 g_pTextureWall = NULL;		//�e�N�X�`�����
WALL g_aWall[MAX_WALL];
VERTEX_3D *pVtx;

////////////////////////////////////////////////////////////////////////////////
//�ǂ̏���������
////////////////////////////////////////////////////////////////////////////////
HRESULT InitWall(void)
{
	//�ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\", &g_pTextureWall);

	g_aWall[0].pos = D3DXVECTOR3(0.0f, 100.0f, 500.0f);
	g_aWall[0].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aWall[1].pos = D3DXVECTOR3(0.0f, 100.0f, -500.0f);
	g_aWall[1].rot = D3DXVECTOR3(0.0f, D3DXToRadian(180), 0.0f);
	g_aWall[2].pos = D3DXVECTOR3(500.0f, 100.0f, 0.0f);
	g_aWall[2].rot = D3DXVECTOR3(0.0f, D3DXToRadian(90), 0.0f);
	g_aWall[3].pos = D3DXVECTOR3(-500.0f, 100.0f, 0.0f);
	g_aWall[3].rot = D3DXVECTOR3(0.0f, -D3DXToRadian(90), 0.0f);

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_WALL, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &g_pVtxBuffWall, NULL)))
	{
		return E_FAIL;
	}

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffWall->Lock(0, 0, (void**)&pVtx, 0);
	
	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-500, -100, 0);
		pVtx[1].pos = D3DXVECTOR3(-500, 100, 0);
		pVtx[2].pos = D3DXVECTOR3(500, -100, 0);
		pVtx[3].pos = D3DXVECTOR3(500, 100, 0);

		//�@���x�N�g���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//���_���̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);
		
		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffWall->Unlock();

	return S_OK;
}

////////////////////////////////////////////////////////////////////////////////
//�ǂ̏I������
////////////////////////////////////////////////////////////////////////////////
void UninitWall(void)
{
	//���_�o�b�t�@�̊J��
	if (g_pVtxBuffWall != NULL)
	{
		g_pVtxBuffWall->Release();	//�J��
		g_pVtxBuffWall = NULL;		//������
	}

	//�e�N�X�`���̊J��
	if (g_pTextureWall != NULL)
	{
		g_pTextureWall->Release();	//�J��
		g_pTextureWall = NULL;		//������
	}
}

////////////////////////////////////////////////////////////////////////////////
//�ǂ̍X�V����
////////////////////////////////////////////////////////////////////////////////
void UpdateWall(void)
{

}

////////////////////////////////////////////////////////////////////////////////
//�ǂ̕`�揈��
////////////////////////////////////////////////////////////////////////////////
void DrawWall(void)
{
	//�ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;
	D3DXMATRIX mtxRot, mtxTrans;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		//���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_aWall[nCntWall].mtxworld);

		//�����𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aWall[nCntWall].rot.y, g_aWall[nCntWall].rot.x, g_aWall[nCntWall].rot.z);
		D3DXMatrixMultiply(&g_aWall[nCntWall].mtxworld, &g_aWall[nCntWall].mtxworld, &mtxRot);

		//�ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, g_aWall[nCntWall].pos.x, g_aWall[nCntWall].pos.y, g_aWall[nCntWall].pos.z);
		D3DXMatrixMultiply(&g_aWall[nCntWall].mtxworld, &g_aWall[nCntWall].mtxworld, &mtxTrans);

		//���[���h�}�g���b�N�X
		pDevice->SetTransform(D3DTS_WORLD, &g_aWall[nCntWall].mtxworld);

		//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_pVtxBuffWall, 0, sizeof(VERTEX_3D));

		//���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_3D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, NULL);

		////�|���S���̕`��
		//pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntWall * 4, 2);
	}
}

WALL *GetWall(void)
{
	return &g_aWall[0];
}

VERTEX_3D *GetVtx(void)
{
	return pVtx;
}