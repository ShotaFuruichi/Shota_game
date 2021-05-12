//-----------------------------------------------------------------
//
// �J���� (camera.cpp)
// Author:Itsuki Takaiwa
//
//-----------------------------------------------------------------
#include "camera.h"
#include "chara.h"
#include "input.h"
#include "gamepad.h"

//-----------------------------------------------------------------
// �}�N����`
//-----------------------------------------------------------------
#define MOVE_CAMERA			(3.0f)
#define LENGTH				(500.0f)
#define ROT					(0.03f)
#define PI_QUARTER			(D3DX_PI / 4.0f)

//-----------------------------------------------------------------
// �O���[�o���ϐ�
//-----------------------------------------------------------------
Camera g_camera;			// �J�������

//-----------------------------------------------------------------
// �J�����̏���������
//-----------------------------------------------------------------
void InitCamera(void)
{
	// �ϐ��̏�����
	// �Œ�J����
	for (int nCntCamera = 0; nCntCamera < MAX_CAMERA; nCntCamera++)
	{
		g_camera.CameraInfo[nCntCamera].posV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_camera.CameraInfo[nCntCamera].posVDest = g_camera.CameraInfo[nCntCamera].posV;
		g_camera.CameraInfo[nCntCamera].posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_camera.CameraInfo[nCntCamera].posRDest = g_camera.CameraInfo[nCntCamera].posR;
		g_camera.CameraInfo[nCntCamera].vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		g_camera.CameraInfo[nCntCamera].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_camera.CameraInfo[nCntCamera].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_camera.CameraInfo[nCntCamera].moveV = D3DXVECTOR3(0.0f, 500.0f, 0.0f);
		g_camera.CameraInfo[nCntCamera].moveR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_camera.CameraInfo[nCntCamera].viewport.X = 0;
		g_camera.CameraInfo[nCntCamera].viewport.Y = 0;
		g_camera.CameraInfo[nCntCamera].viewport.Width = SCREEN_WIDTH;
		g_camera.CameraInfo[nCntCamera].viewport.Height = SCREEN_HEIGHT;
		g_camera.CameraInfo[nCntCamera].viewport.MinZ = 0.0f;
		g_camera.CameraInfo[nCntCamera].viewport.MaxZ = 1.0f;
	}
}

//-----------------------------------------------------------------
// �J�����̏I������
//-----------------------------------------------------------------
void UninitCamera(void)
{
	// �ϐ��̏�����
	// �Œ�J����
	for (int nCntCamera = 0; nCntCamera < MAX_CAMERA; nCntCamera++)
	{
		g_camera.CameraInfo[nCntCamera].posV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_camera.CameraInfo[nCntCamera].posVDest = g_camera.CameraInfo[nCntCamera].posV;
		g_camera.CameraInfo[nCntCamera].posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_camera.CameraInfo[nCntCamera].posRDest = g_camera.CameraInfo[nCntCamera].posR;
		g_camera.CameraInfo[nCntCamera].vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		g_camera.CameraInfo[nCntCamera].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_camera.CameraInfo[nCntCamera].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_camera.CameraInfo[nCntCamera].moveV = D3DXVECTOR3(0.0f, 500.0f, 0.0f);
		g_camera.CameraInfo[nCntCamera].moveR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_camera.CameraInfo[nCntCamera].viewport.X = 0;
		g_camera.CameraInfo[nCntCamera].viewport.Y = 0;
		g_camera.CameraInfo[nCntCamera].viewport.Width = SCREEN_WIDTH;
		g_camera.CameraInfo[nCntCamera].viewport.Height = SCREEN_HEIGHT;
		g_camera.CameraInfo[nCntCamera].viewport.MinZ = 0.0f;
		g_camera.CameraInfo[nCntCamera].viewport.MaxZ = 1.0f;
	}
	g_camera.nNumCamera = 0;
}

//-----------------------------------------------------------------
// �J�����̍X�V����
//-----------------------------------------------------------------
void UpdateCamera(void)
{
	// �Ǐ]
	KeyboradFollow();
}

//-----------------------------------------------------------------
// �J�����̐ݒu
//-----------------------------------------------------------------
void SetCamera(int nIdx)
{
	// �ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;	// �f�o�C�X�ւ̃|�C���^

	// �ϐ��̎󂯓n��
	pDevice = GetDevice();

	// �r���[�|�[�g�̐ݒ�
	pDevice->SetViewport(&g_camera.CameraInfo[nIdx].viewport);

	// �v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_camera.CameraInfo[nIdx].mtxProjection);

	// �v���W�F�N�V�����}�g���b�N�X���쐬
	D3DXMatrixPerspectiveFovLH(&g_camera.CameraInfo[nIdx].mtxProjection,
		D3DXToRadian(45.0f),
		(float)g_camera.CameraInfo[nIdx].viewport.Width / (float)g_camera.CameraInfo[nIdx].viewport.Height,
		10.0f,
		3000.0f);

	// �v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &g_camera.CameraInfo[nIdx].mtxProjection);

	// �r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_camera.CameraInfo[nIdx].mtxView);

	// �r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&g_camera.CameraInfo[nIdx].mtxView,
		&g_camera.CameraInfo[nIdx].posV,
		&g_camera.CameraInfo[nIdx].posR,
		&g_camera.CameraInfo[nIdx].vecU);

	// �r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &g_camera.CameraInfo[nIdx].mtxView);
}

//-----------------------------------------------------------------
// �J�����̃L�[�{�[�h����(�Ǐ])
//-----------------------------------------------------------------
void KeyboradFollow(void)
{
	// �v���C���[���̎擾
	Character *pCharacter = GetCharacter();
#if _DEBUG

	if (GetKeyboardPress(KEYINFO_UP) == true)
	{
		// ���f����ړ�
		g_camera.CameraInfo[0].moveR.x -= 10.0f * sinf(-g_camera.CameraInfo[0].rot.y);
		g_camera.CameraInfo[0].moveR.z += 10.0f * cosf(-g_camera.CameraInfo[0].rot.y);
		g_camera.CameraInfo[0].moveV.x -= 10.0f * sinf(-g_camera.CameraInfo[0].rot.y);
		g_camera.CameraInfo[0].moveV.z += 10.0f * cosf(-g_camera.CameraInfo[0].rot.y);
		
	}
	if (GetKeyboardPress(KEYINFO_DOWN) == true)
	{
		// ���f�����ړ�
		g_camera.CameraInfo[0].moveR.x += 10.0f * sinf(-g_camera.CameraInfo[0].rot.y);
		g_camera.CameraInfo[0].moveR.z -= 10.0f * cosf(-g_camera.CameraInfo[0].rot.y);
		g_camera.CameraInfo[0].moveV.x += 10.0f * sinf(-g_camera.CameraInfo[0].rot.y);
		g_camera.CameraInfo[0].moveV.z -= 10.0f * cosf(-g_camera.CameraInfo[0].rot.y);
	}
	if (GetKeyboardPress(KEYINFO_RIGHT) == true)
	{// ���f���E�ړ�
		g_camera.CameraInfo[0].moveR.x += 10.0f * cosf(-g_camera.CameraInfo[0].rot.y);
		g_camera.CameraInfo[0].moveR.z += 10.0f * sinf(-g_camera.CameraInfo[0].rot.y);
		g_camera.CameraInfo[0].moveV.x += 10.0f * cosf(-g_camera.CameraInfo[0].rot.y);
		g_camera.CameraInfo[0].moveV.z += 10.0f * sinf(-g_camera.CameraInfo[0].rot.y);

	}
	if (GetKeyboardPress(KEYINFO_LEFT) == true)
	{// ���f�����ړ�
		g_camera.CameraInfo[0].moveR.x -= 10.0f * cosf(-g_camera.CameraInfo[0].rot.y);
		g_camera.CameraInfo[0].moveR.z -= 10.0f * sinf(-g_camera.CameraInfo[0].rot.y);
		g_camera.CameraInfo[0].moveV.x -= 10.0f * cosf(-g_camera.CameraInfo[0].rot.y);
		g_camera.CameraInfo[0].moveV.z -= 10.0f * sinf(-g_camera.CameraInfo[0].rot.y);
	}
	if (GetKeyboardPress(KEYINFO_ROT_LEFT) == true)
	{// ���_�̍���]
		g_camera.CameraInfo[CAMERATYPE_FIXED].rot.y -= ROT;						// ��]��

		if (g_camera.CameraInfo[CAMERATYPE_FIXED].rot.y < -D3DX_PI)
		{// 3.14f���傫���Ȃ����Ƃ��l��-3.14f�ɂ���
			g_camera.CameraInfo[CAMERATYPE_FIXED].rot.y += D3DX_PI * 2.0f;
		}
	}
	else if (GetKeyboardPress(KEYINFO_ROT_RIGHT) == true)
	{// ���_�̉E��]
		g_camera.CameraInfo[CAMERATYPE_FIXED].rot.y += ROT;						// ��]��

		if (g_camera.CameraInfo[CAMERATYPE_FIXED].rot.y > D3DX_PI)
		{// -3.14f��菬�����Ȃ����Ƃ��l��3.14f�ɂ���
			g_camera.CameraInfo[CAMERATYPE_FIXED].rot.y -= D3DX_PI * 2.0f;
		}
	}
	if (GetKeyboardPress(KEYINFO_ROT_UP) == true)
	{// ���_�̍���]
		g_camera.CameraInfo[0].moveV.y += 2.0f;						// ��]��
	}
	if (GetKeyboardPress(KEYINFO_ROT_DOWN) == true)
	{// ���_�̉E��]
		g_camera.CameraInfo[0].moveV.y -= 2.0f;						// ��]��
	}
	if (GetKeyboardPress(KEYINFO_ROT_CAMERA_UP) == true)
	{// ���_�̍���]
		g_camera.CameraInfo[0].moveR.y += 2.0f;						// ��]��
	}
	if (GetKeyboardPress(KEYINFO_ROT_CAMERA_DOWN) == true)
	{// ���_�̉E��]
		g_camera.CameraInfo[0].moveR.y -= 2.0f;						// ��]��
	}

#endif
	for (int nCntCamera = 0; nCntCamera < g_camera.nNumCamera; nCntCamera++)
	{
		// �ړI�̒����_
		g_camera.CameraInfo[nCntCamera].posRDest.x = g_camera.CameraInfo[nCntCamera].moveR.x;		// �ړI�̒����_��X�����W�̌���
		g_camera.CameraInfo[nCntCamera].posRDest.z = g_camera.CameraInfo[nCntCamera].moveR.z;		// �ړI�̒����_��Z�����W�̌���
		g_camera.CameraInfo[nCntCamera].posRDest.y = g_camera.CameraInfo[nCntCamera].moveR.y;

		// �ړI�̎��_
		g_camera.CameraInfo[nCntCamera].posVDest.x =  sinf(g_camera.CameraInfo[nCntCamera].rot.y) * -g_camera.CameraInfo[nCntCamera].fLenge + g_camera.CameraInfo[nCntCamera].moveV.x;	// �ړI�̎��_��X�����W�̌���
		g_camera.CameraInfo[nCntCamera].posVDest.z =  cosf(g_camera.CameraInfo[nCntCamera].rot.y) * -g_camera.CameraInfo[nCntCamera].fLenge + g_camera.CameraInfo[nCntCamera].moveV.z;	// �ړI�̎��_��Z�����W�̌���
		g_camera.CameraInfo[nCntCamera].posVDest.y =  g_camera.CameraInfo[nCntCamera].moveV.y;

		// �����_�̍X�V
		g_camera.CameraInfo[nCntCamera].posR.x += (g_camera.CameraInfo[nCntCamera].posRDest.x - g_camera.CameraInfo[nCntCamera].posR.x) * 1.0f;	// �����_��X�����W�̌���
		g_camera.CameraInfo[nCntCamera].posR.z += (g_camera.CameraInfo[nCntCamera].posRDest.z - g_camera.CameraInfo[nCntCamera].posR.z) * 1.0f;	// �����_��Z�����W�̌���
		g_camera.CameraInfo[nCntCamera].posR.y += (g_camera.CameraInfo[nCntCamera].posRDest.y - g_camera.CameraInfo[nCntCamera].posR.y) * 1.0f;	// �����_��Y�����W�̌���

		// ���_�̍X�V
		g_camera.CameraInfo[nCntCamera].posV.x += (g_camera.CameraInfo[nCntCamera].posVDest.x - g_camera.CameraInfo[nCntCamera].posV.x) * 1.0f;	// ���_��X�����W�̌���
		g_camera.CameraInfo[nCntCamera].posV.z += (g_camera.CameraInfo[nCntCamera].posVDest.z - g_camera.CameraInfo[nCntCamera].posV.z) * 1.0f;	// ���_��Z�����W�̌���
		g_camera.CameraInfo[nCntCamera].posV.y += (g_camera.CameraInfo[nCntCamera].posVDest.y - g_camera.CameraInfo[nCntCamera].posV.y) * 1.0f;
	}
}

//-----------------------------------------------------------------
// �Q�[����ʂ̃J����������
//-----------------------------------------------------------------
void InitGameCamera(void)
{

}


//-----------------------------------------------------------------
// �J�������̎擾
//-----------------------------------------------------------------
Camera *GetCamera(void)
{
	return &g_camera;
}