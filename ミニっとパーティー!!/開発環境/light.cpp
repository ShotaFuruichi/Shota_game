//-----------------------------------------------------------------
//
// ���C�g (light.cpp)
// Author:Itsuki Takaiwa
//
//-----------------------------------------------------------------
#include "light.h"
#include "input.h"

//-----------------------------------------------------------------
// �O���[�o���ϐ�
//-----------------------------------------------------------------
Light g_Light;			// ���C�g���

//-----------------------------------------------------------------
// ���C�g�̏���������
//-----------------------------------------------------------------
void InitLight(void)
{
	// �ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;			// �f�o�C�X�ւ̃|�C���^

	// �ϐ��̎󂯓n��
	pDevice = GetDevice();

	// ���C�g���N���A����
	for (int nCntLight = 0; nCntLight < g_Light.nNumLight; nCntLight++)
	{
		ZeroMemory(&g_Light.aLightInfo[nCntLight], sizeof(D3DLIGHT9));

		// ���C�g�̎�ނ�ݒ�
		g_Light.aLightInfo[nCntLight].Type = D3DLIGHT_DIRECTIONAL;

		// ���C�g�̐F���w��
		g_Light.aLightInfo[nCntLight].Diffuse = g_Light.colDef[nCntLight];

		// ���C�g�̕�����ݒ�
		D3DXVec3Normalize(&g_Light.vecDir[nCntLight], &g_Light.vecDir[nCntLight]);		// ���K������
		g_Light.aLightInfo[nCntLight].Direction = g_Light.vecDir[nCntLight];

		// ���C�g��ݒ�
		pDevice->SetLight(nCntLight, &g_Light.aLightInfo[nCntLight]);

		// ���C�g��L���ɂ���
		pDevice->LightEnable(nCntLight, TRUE);
	}
}

//-----------------------------------------------------------------
// ���C�g�̏I������
//-----------------------------------------------------------------
void UninitLight(void)
{
	for (int nCntLight = 0; nCntLight < g_Light.nNumLight; nCntLight++)
	{
		g_Light.colDef[nCntLight].a = 0.0f;
		g_Light.colDef[nCntLight].r = 0.0f;
		g_Light.colDef[nCntLight].g = 0.0f;
		g_Light.colDef[nCntLight].b = 0.0f;
		g_Light.vecDir[nCntLight] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
	g_Light.nNumLight = 0;											
}

//-----------------------------------------------------------------
// ���C�g�̍X�V����
//-----------------------------------------------------------------
void UpdateLight(void)
{
	// �ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;			// �f�o�C�X�ւ̃|�C���^

	// �ϐ��̎󂯓n��
	pDevice = GetDevice();

	// ���C�g���N���A����
	for (int nCntLight = 0; nCntLight < g_Light.nNumLight; nCntLight++)
	{
		ZeroMemory(&g_Light.aLightInfo[nCntLight], sizeof(D3DLIGHT9));

		// ���C�g�̎�ނ�ݒ�
		g_Light.aLightInfo[nCntLight].Type = D3DLIGHT_DIRECTIONAL;

		// ���C�g�̐F���w��
		g_Light.aLightInfo[nCntLight].Diffuse = g_Light.colDef[nCntLight];

		// ���C�g�̕�����ݒ�
		D3DXVec3Normalize(&g_Light.vecDir[nCntLight], &g_Light.vecDir[nCntLight]);		// ���K������
		g_Light.aLightInfo[nCntLight].Direction = g_Light.vecDir[nCntLight];

		// ���C�g��ݒ�
		pDevice->SetLight(nCntLight, &g_Light.aLightInfo[nCntLight]);

		// ���C�g��L���ɂ���
		pDevice->LightEnable(nCntLight, TRUE);
	}
#if _DEBUG
	if (GetKeyboardTrigger(KEYINFO_MODEL_UP) == true)
	{
		g_Light.nCntLight++;

		if (g_Light.nCntLight >= g_Light.nNumLight)
		{
			g_Light.nCntLight = 0;
		}
	}
	else if (GetKeyboardTrigger(KEYINFO_MODEL_DOWN) == true)
	{
		g_Light.nCntLight--;

		if (g_Light.nCntLight < 0)
		{
			g_Light.nCntLight = g_Light.nNumLight - 1;
		}
	}
	if (GetKeyboardPress(KEYINFO_DIK_1) == true)
	{
		g_Light.colDef[g_Light.nCntLight].r += 0.01f;

		if (g_Light.colDef[g_Light.nCntLight].r > 1.0f)
		{
			g_Light.colDef[g_Light.nCntLight].r = 1.0f;
		}
	}
	if (GetKeyboardPress(KEYINFO_DIK_2) == true)
	{
		g_Light.colDef[g_Light.nCntLight].r -= 0.01f;

		if (g_Light.colDef[g_Light.nCntLight].r < 0.0f)
		{
			g_Light.colDef[g_Light.nCntLight].r = 0.0f;
		}
	}
	if (GetKeyboardPress(KEYINFO_DIK_3) == true)
	{
		g_Light.colDef[g_Light.nCntLight].g += 0.01f;

		if (g_Light.colDef[g_Light.nCntLight].g > 1.0f)
		{
			g_Light.colDef[g_Light.nCntLight].g = 1.0f;
		}
	}
	if (GetKeyboardPress(KEYINFO_DIK_4) == true)
	{
		g_Light.colDef[g_Light.nCntLight].g -= 0.01f;

		if (g_Light.colDef[g_Light.nCntLight].g < 0.0f)
		{
			g_Light.colDef[g_Light.nCntLight].g = 0.0f;
		}
	}
	if (GetKeyboardPress(KEYINFO_DIK_5) == true)
	{
		g_Light.colDef[g_Light.nCntLight].b += 0.01f;

		if (g_Light.colDef[g_Light.nCntLight].b > 1.0f)
		{
			g_Light.colDef[g_Light.nCntLight].b = 1.0f;
		}
	}
	if (GetKeyboardPress(KEYINFO_DIK_6) == true)
	{
		g_Light.colDef[g_Light.nCntLight].b -= 0.01f;

		if (g_Light.colDef[g_Light.nCntLight].b < 0.0f)
		{
			g_Light.colDef[g_Light.nCntLight].b = 0.0f;
		}
	}
#endif
}

//-----------------------------------------------------------------
// ���C�g���̎擾
//-----------------------------------------------------------------
Light *GetLight(void)
{
	return &g_Light;
}