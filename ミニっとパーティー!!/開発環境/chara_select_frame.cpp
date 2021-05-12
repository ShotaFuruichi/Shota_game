//-----------------------------------------------------------------
//
// �L�����Z���N�g�g (chara_select_frame.cpp)
// Author:Itsuki Takaiwa
//
//-----------------------------------------------------------------
#include "chara_select_frame.h"
#include "chara_select_image.h"
#include "dicision_chara.h"
#include "chara.h"
#include "gamepad.h"
#include "player.h"
#include "sound.h"

//-------------------------------------------------------------------
// �}�N����`
//-------------------------------------------------------------------
#define MAX_CHARAFRAME	(4)						// �e�N�X�`������
#define SCORE_X			(970.0f)				// ���S���W(X)
#define SCORE_Y			(50.0f)					// ���S���W(Y)

#define SCORE_WIDTH		(45.0f)					// �X�R�A�̕�
#define SCORE_HEIGHT	(80.0f)					// �X�R�A�̍���
#define WIDTH_X			(40.0f)					// �X�R�A��z�u����Ԋu

#define LANDAM_INTERBAL	(5)					// �����_���̂Ƃ��\������L�����̊Ԋu

//-----------------------------------------------------------------
// �O���[�o���ϐ�
//-----------------------------------------------------------------
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffCharaSelectFrame = NULL;	// �X�R�A�̃e�N�X�`���̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureCharaSelectFrame[MAX_CHARAFRAME] = {};		// �X�R�A�̒��_�o�b�t�@�̃|�C���^
CharaSelectFrame g_aCharaSelectFrame[MAX_CHARAFRAME];			// �g�̏��
int g_nNumFrame;

//-----------------------------------------------------------------
// �L�����Z���N�g�g�̏���������
//-----------------------------------------------------------------
HRESULT InitCharaSelectFrame(void)
{
	// �ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;

	// �ϐ��̎󂯓n��
	pDevice = GetDevice();

	// �L�����Z���N�g�C���[�W���̎擾
	CharaSelectImage *pCharaSelectImage = GetCharaSelectImage();

	g_nNumFrame = 2;

	// �e�N�X�`���̓ǂݍ���	
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/chara_select_frame1.png", &g_pTextureCharaSelectFrame[0]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/chara_select_frame2.png", &g_pTextureCharaSelectFrame[1]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/chara_select_frame3.png", &g_pTextureCharaSelectFrame[2]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/chara_select_frame4.png", &g_pTextureCharaSelectFrame[3]);

	// �ϐ��̏�����
	for (int nCntFrame = 0; nCntFrame < MAX_CHARAFRAME; nCntFrame++, pCharaSelectImage++)
	{
		g_aCharaSelectFrame[nCntFrame].pos = D3DXVECTOR3(pCharaSelectImage->pos.x, pCharaSelectImage->pos.y, 0.0f);
		g_aCharaSelectFrame[nCntFrame].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
		g_aCharaSelectFrame[nCntFrame].fWidth = 165.0f;
		g_aCharaSelectFrame[nCntFrame].fHeight = 165.0f;
		g_aCharaSelectFrame[nCntFrame].nNumChara = nCntFrame;
		g_aCharaSelectFrame[nCntFrame].nIdxChara = nCntFrame;
		g_aCharaSelectFrame[nCntFrame].bSelect = false;
	}

	// ���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * MAX_VERTEX * MAX_CHARAFRAME, // �m�ۂ���o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,					// ���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pVtxBuffCharaSelectFrame,
		NULL)))
	{
		return E_FAIL;
	}

	// �\���̂̃|�C���^�ϐ�
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffCharaSelectFrame->Lock(0, 0, (void**)&pVtx, 0);

	// ������
	for (int nCntFrame = 0; nCntFrame < MAX_CHARAFRAME; nCntFrame++)
	{
		// ���_���W�̐ݒ�
		SetVertexCharaSelectFrame(nCntFrame);

		// rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// ���_�J���[�̐ݒ�
		pVtx[0].col = g_aCharaSelectFrame[nCntFrame].col;
		pVtx[1].col = g_aCharaSelectFrame[nCntFrame].col;
		pVtx[2].col = g_aCharaSelectFrame[nCntFrame].col;
		pVtx[3].col = g_aCharaSelectFrame[nCntFrame].col;

		// �e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

		// �X�R�A�̏������ɂ���
		pVtx += 4;
	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffCharaSelectFrame->Unlock();

	return S_OK;
}

//-----------------------------------------------------------------
// �L�����Z���N�g�g�̏I������
//-----------------------------------------------------------------
void UninitCharaSelectFrame(void)
{
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffCharaSelectFrame != NULL)
	{
		g_pVtxBuffCharaSelectFrame->Release();
		g_pVtxBuffCharaSelectFrame = NULL;
	}

	// �e�N�X�`���̊J��
	for (int nCntTexture = 0 ; nCntTexture < MAX_CHARAFRAME; nCntTexture++)
	{
		if (g_pTextureCharaSelectFrame[nCntTexture] != NULL)
		{
			g_pTextureCharaSelectFrame[nCntTexture] ->Release();
			g_pTextureCharaSelectFrame[nCntTexture]  = NULL;
		}
	}
}

//-----------------------------------------------------------------
// �L�����Z���N�g�g�̍X�V����
//-----------------------------------------------------------------
void UpdateCharaSelectFrame(void)
{
	// �q����Ă���R���g���[���[�̐����擾
	int nCntController = GetnCntController();

	// �q���ꂽ�R���g���[���[�̐�������
	for (int nCntPlayer = 0; nCntPlayer < nCntController ; nCntPlayer++)
	{// �I�����ꂽ�l��������
		if (nCntPlayer < g_nNumFrame)
		{
			// �Q�[���p�b�h���̎擾
			bool *pStickTrigger = GetStickTrigger(nCntPlayer);
			bool *pCrossKeyTrigger = GetCrossKeyTrigger(nCntPlayer);

			// �L�����Z���N�g�C���[�W���̎擾
			CharaSelectImage *pCharaSelectImage = GetCharaSelectImage();

			if (g_aCharaSelectFrame[nCntPlayer].bSelect == false)
			{
				// �v���C���[�̈ړ�
				if (pStickTrigger[STICKTRIGGER_RIGHT] == true || pCrossKeyTrigger[CROSSKEYTRIGGER_RIGHT] == true)
				{// �E�ړ�
					g_aCharaSelectFrame[nCntPlayer].nIdxChara++;

					if (g_aCharaSelectFrame[nCntPlayer].nIdxChara >= MAX_CHARAIMAGE)
					{
						g_aCharaSelectFrame[nCntPlayer].nIdxChara = 0;
					}
					// �ʒu�̊m��
					pCharaSelectImage += g_aCharaSelectFrame[nCntPlayer].nIdxChara;		// ���Ԗڂ̏����g����
					g_aCharaSelectFrame[nCntPlayer].pos.x = pCharaSelectImage->pos.x;
					PlaySound(SOUND_LABEL_SE_CURSOR);
				}
				else if (pStickTrigger[STICKTRIGGER_LEFT] == true || pCrossKeyTrigger[CROSSKEYTRIGGER_LEFT] == true)
				{// ���ړ�
					g_aCharaSelectFrame[nCntPlayer].nIdxChara--;

					if (g_aCharaSelectFrame[nCntPlayer].nIdxChara < 0)
					{
						g_aCharaSelectFrame[nCntPlayer].nIdxChara = MAX_CHARAIMAGE - 1;
					}
					// �ʒu�̊m��
					pCharaSelectImage += g_aCharaSelectFrame[nCntPlayer].nIdxChara;		// ���Ԗڂ̏����g����
					g_aCharaSelectFrame[nCntPlayer].pos.x = pCharaSelectImage->pos.x;
					PlaySound(SOUND_LABEL_SE_CURSOR);
				}
				// ���Ԗڂ̃L������I�����Ă��邩�t���[���̏ꏊ����Q��
				if (g_aCharaSelectFrame[nCntPlayer].nIdxChara == 4)
				{
					// �����_���I�����L���������Ԃɏo��
					if (0 == (g_aCharaSelectFrame[nCntPlayer].nCounterLandam % LANDAM_INTERBAL))
					{
						g_aCharaSelectFrame[nCntPlayer].nNumChara++;

						if (g_aCharaSelectFrame[nCntPlayer].nNumChara >= MAX_CHARAIMAGE - 1)
						{
							g_aCharaSelectFrame[nCntPlayer].nNumChara = 0;
						}
					}
					g_aCharaSelectFrame[nCntPlayer].nCounterLandam++;
				}
				else
				{
					// �����_���ȊO�̎�
					g_aCharaSelectFrame[nCntPlayer].nNumChara = g_aCharaSelectFrame[nCntPlayer].nIdxChara;
				}
				// A�{�^�����������猈���Ԃɂ���
				if (GetJoypadTrigger(nCntPlayer, JPINFO_OKorJUMP) == true)
				{
					g_aCharaSelectFrame[nCntPlayer].bSelect = true;
					SetDicisionChara(true, nCntPlayer);
					PlaySound(SOUND_LABEL_SE_DICIDE);
					// �B���L�����ɂ��邩�ǂ���
					if (SecretChara(nCntPlayer, g_aCharaSelectFrame[nCntPlayer].nIdxChara))
					{
						g_aCharaSelectFrame[nCntPlayer].nNumChara = 4;
					}
				}
			}
			else
			{
				// B�{�^������������L�����Z����Ԃɂ���
				if (GetJoypadTrigger(nCntPlayer, JPINFO_CANCEL) == true)
				{
					g_aCharaSelectFrame[nCntPlayer].bSelect = false;
					SetDicisionChara(false, nCntPlayer);
					PlaySound(SOUND_LABEL_SE_CANSEL);
				}
			}
			// ���_���W�̍X�V
			SetVertexCharaSelectFrame(nCntPlayer);
		}
	}
	if (GetJoypadTrigger(PLAYER_1, JPINFO_RIGHT_TURN) == true)
	{
		g_nNumFrame++;

		if (g_nNumFrame >= MAX_CHARAFRAME)
		{
			g_nNumFrame = MAX_CHARAFRAME;
		}
	}
	else if (GetJoypadTrigger(PLAYER_1, JPINFO_LEFT_TURN) == true)
	{
		g_nNumFrame--;

		if (g_nNumFrame < 2)
		{
			g_nNumFrame = 2;
		}
	}
}

//-----------------------------------------------------------------
// �L�����Z���N�g�g�̕`�揈��
//-----------------------------------------------------------------
void DrawCharaSelectFrame(void)
{
	// �ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;

	// �ϐ��̎󂯓n��
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffCharaSelectFrame, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �I�����ꂽ���[�h�ɉ����ĕ`��
	for (int nCntFrame = 0; nCntFrame < g_nNumFrame; nCntFrame++)
	{
		pDevice->SetTexture(0, g_pTextureCharaSelectFrame[nCntFrame]);
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntFrame * 4, 2);
	}
}

//-----------------------------------------------------------------
// �L�����Z���N�g�t���[���̒��_���W�̐ݒ�
//-----------------------------------------------------------------
void SetVertexCharaSelectFrame(int nIdx)
{
	// �\���̂̃|�C���^�ϐ�
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffCharaSelectFrame->Lock(0, 0, (void**)&pVtx, 0);

	// ���Ԗڂ�
	pVtx += nIdx * 4;

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(g_aCharaSelectFrame[nIdx].pos.x - g_aCharaSelectFrame[nIdx].fWidth / 2.0f, g_aCharaSelectFrame[nIdx].pos.y + g_aCharaSelectFrame[nIdx].fHeight / 2.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_aCharaSelectFrame[nIdx].pos.x - g_aCharaSelectFrame[nIdx].fWidth / 2.0f, g_aCharaSelectFrame[nIdx].pos.y - g_aCharaSelectFrame[nIdx].fHeight / 2.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_aCharaSelectFrame[nIdx].pos.x + g_aCharaSelectFrame[nIdx].fWidth / 2.0f, g_aCharaSelectFrame[nIdx].pos.y + g_aCharaSelectFrame[nIdx].fHeight / 2.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_aCharaSelectFrame[nIdx].pos.x + g_aCharaSelectFrame[nIdx].fWidth / 2.0f, g_aCharaSelectFrame[nIdx].pos.y - g_aCharaSelectFrame[nIdx].fHeight / 2.0f, 0.0f);

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffCharaSelectFrame->Unlock();
}

//-----------------------------------------------------------------
// �L�����Z���N�g�t���[�����̎擾
//-----------------------------------------------------------------
CharaSelectFrame *GetCharaSelectFrame(void)
{
	return &g_aCharaSelectFrame[0];
}

//-----------------------------------------------------------------
// �B���L�������o��������
//-----------------------------------------------------------------
bool SecretChara(int nCntPlayer,int nNumChara)
{
	// �R�}���h���̎擾
	int *pSaveCommand = &g_aCharaSelectFrame[nCntPlayer].nSaveCommand[0];

	// �ϐ��錾
	int nAnswerCommand[MAX_COMMAND] = {4,3,2,1,0};	// �����̃R�}���h

	// �R�}���h�̍X�V
	for (int nCntCommandTop = MAX_COMMAND - 1; nCntCommandTop >= 0; nCntCommandTop--)
	{
		if (nCntCommandTop == 0)
		{
			// �R�}���h�Z�[�u�p�̕ϐ��ɕۑ�
			pSaveCommand[nCntCommandTop] = nNumChara;
		}
		else
		{
			pSaveCommand[nCntCommandTop] = pSaveCommand[nCntCommandTop - 1];
		}
	}

	// �R�}���h�̔�r
	for (int nCntCommand = 0; nCntCommand < MAX_COMMAND; nCntCommand++)
	{
		if (pSaveCommand[nCntCommand] != nAnswerCommand[nCntCommand])
		{
			return false;
		}
	}
	return true;
}

//-----------------------------------------------------------------
// �t���[�����̎擾
//-----------------------------------------------------------------
int GetFrame(void)
{
	return g_nNumFrame;
}