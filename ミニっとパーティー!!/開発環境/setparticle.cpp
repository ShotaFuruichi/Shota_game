//-------------------------------------------------------------------
//
// �Z�b�g�p�[�e�B�N�� (setparticle.cpp)
// Author:Itsuki Takaiwa
//
//-------------------------------------------------------------------
#include "setparticle.h"
#include "effect.h"

//-------------------------------------------------------------------
// �}�N����`
//-------------------------------------------------------------------
#define Appear		(2)				// �o����
#define MOVE		(2)				// �ړ���
#define HEIGHT		(2)				// ����
#define RCOL		(1.0f)			// R����
#define GCOL		(1.0f)			// G����
#define BCOL		(1.0f)			// B����
#define RANDIUS		(5)				// ���a
#define ALPHA		(0.01f)			// ���l�̌�����
#define GRAVITY		(0.0f)			// �d��

//-------------------------------------------------------------------
// �O���[�o���ϐ�
//-------------------------------------------------------------------
int g_nCnt = 0;

//-------------------------------------------------------------------
// �e�X�g
//-------------------------------------------------------------------
void SetParticle(void)
{
	g_nCnt++;

	if (g_nCnt % 10 == 0)
	{
		for (int nCnt = 0; nCnt < Appear; nCnt++)
		{// �p�x�̐ݒ�
			float fAngle = ((float)(rand() % 628 - 314)) / 100.0f;
			float fmove = (float)(rand() % MOVE + 1);

			// �G�t�F�N�g�̐ݒ�
			SetEffect(D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				D3DXVECTOR3(sinf(fAngle) * fmove, HEIGHT, cosf(fAngle) * fmove),
				D3DXCOLOR(RCOL, GCOL, BCOL, 1.0f),
				1.0f,
				(float)(rand() % 10 + RANDIUS),
				ALPHA,
				GRAVITY);
		}
	}
}

//-------------------------------------------------------------------
// �e�̋O��
//-------------------------------------------------------------------
void SetOrbitBullet(D3DXVECTOR3 pos)
{
	for (int nCnt = 0; nCnt < 1; nCnt++)
	{
		// �G�t�F�N�g�̐ݒ�
		SetEffect(pos,
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			D3DXCOLOR(0.9f, 0.7f, 0.2f, 1.0f),
			1.0f,
			10.0f,
			0.07f,
			0.0f);
	}
}