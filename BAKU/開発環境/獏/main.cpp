////////////////////////////////////////////////////////////////////////////////
//
//Contents	: �A�N�V�����Q�[�� [main.cpp]
//Author	: ShotaFuruichi
//Since		: 2020/10/13
//
////////////////////////////////////////////////////////////////////////////////
#define _CRT_SECURE_NO_WARNINGS
#include "main.h"
#include "polygon.h"
#include "camera.h"
#include "light.h"
#include "model.h"
#include "input.h"
#include "shadow.h"
#include "wall.h"
#include "Billboard.h"
#include "meshfield.h"
#include "bullet.h"
#include <string.h>
#include <stdio.h>
#include "object.h"
#include "player.h"
#include "title.h"
#include "tutorial.h"
#include "game.h"
#include "result.h"
#include "ranking.h"
#include "fade.h"
#include "xinput_pad.h"
#include "enemy.h"

////////////////////////////////////////////////////////////////////////////////
//�}�N����`
////////////////////////////////////////////////////////////////////////////////
#define CLASS_NAME "windowclass"		//�N���X�̖��O
#define WINDOW_NAME "�E�B���h�E�\��"	//�E�B���h�E�̖��O
#define WINDOW_POS_X (0)				//�E�B���h�E�̍���X���W
#define WINDOW_POS_Y (0)				//�E�B���h�E�̍���Y���W
#define ID_TIMER (121)					//�^�C�}�[��ID
#define TIMER_INTERVAL (1000/60)		//�^�C�}�[�̔������o

////////////////////////////////////////////////////////////////////////////////
//�v���g�^�C�v�錾
////////////////////////////////////////////////////////////////////////////////
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);
void DrawFPS(void);

////////////////////////////////////////////////////////////////////////////////
//�O���[�o���ϐ�
////////////////////////////////////////////////////////////////////////////////
LPDIRECT3D9 g_pD3D = NULL;					//Direct3D�I�u�W�F�N�g�ւ̃|�C���^
LPDIRECT3DDEVICE9 g_pD3DDevice = NULL;		//Direct3D�f�o�C�X�ւ̃|�C���^
LPD3DXFONT g_pFont = NULL;					//�t�H���g�ւ̃|�C���^
int g_nCountFPS;							//FPS�J�E���^
MODE g_mode = MODE_TITLE;					//���[�h�̎��
HWND hWnd;									//�E�B���h�E�n���h��

////////////////////////////////////////////////////////////////////////////////
//���C���֐�
////////////////////////////////////////////////////////////////////////////////
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//�ϐ��錾
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WindowProc,
		0,
		0,
		hInstance,
		LoadIcon(NULL,IDI_APPLICATION),
		LoadCursor(NULL,IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		"CLASS_NAME",	//�E�B���h�E�N���X�̖��O
		LoadIcon(NULL,IDI_APPLICATION),
	};
	MSG msg;				//���b�Z�[�W���i�[����
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	DWORD dwExecLastTime;	//�����I���ŏI����
	DWORD dwFPSLastTime;	//FPS�v���ŏI����
	DWORD dwCurrentTime;	//���ݎ���
	DWORD dwFrameCount;		//�t���[���J�E���g

							//���݂̎��Ԃ��擾
	dwExecLastTime =
		dwFPSLastTime =
		dwCurrentTime = timeGetTime();
	dwFrameCount = 0;

	//�E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

	//�E�B���h�E�̍쐬
	hWnd = CreateWindowEx
	(
		0,
		"CLASS_NAME",			//�E�B���h�E�N���X�̖��O
		"3D",		//�E�B���h�E�̖��O
		WS_OVERLAPPEDWINDOW,	//�E�B���h�E����ԑO�ɏo��
		CW_USEDEFAULT,			//X���W
		CW_USEDEFAULT,			//Y���W
		rect.right,				//��
		rect.bottom,			//����
		NULL,					//�e�̃n���h��
		NULL,
		hInstance,
		NULL
	);

	//����������
	if (FAILED(Init(hInstance, hWnd, TRUE)))
	{
		return-1;
	}

	//�E�B���h�E�̕\��
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	//���b�Z�[�W���[�v
	while (1)
	{
		//���b�Z�[�W���擾�������̔���
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{	//Windows�̏���
			if (msg.message == WM_QUIT)
			{	//�擾�������b�Z�[�W��WM_QUIT�������ꍇ
				break;
			}
			else
			{	//�擾�������b�Z�[�W��WM_QUIT�ȊO�������ꍇ

				//���b�Z�[�W�̖|��Ƒ��o
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{	//DirectX�̏���

			dwCurrentTime = timeGetTime();
			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{	//0.5�b�o��
				g_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);
				dwFPSLastTime = dwCurrentTime;
				dwFrameCount = 0;
			}

			if ((dwCurrentTime - dwExecLastTime) > (1000 / 60))
			{
				dwExecLastTime = dwCurrentTime;

				//�X�V����
				Update();

				//�`�揈��
				Draw();

				dwFrameCount++;
			}
		}
	}

	//�I������
	Uninit();

	//�E�B���h�E�N���X�̓o�^����
	UnregisterClass("CLASS_NAME", wcex.hInstance);

	return(int)msg.wParam;
	return 0;
}

////////////////////////////////////////////////////////////////////////////////
//�E�B���h�E�v���V�[�W��
////////////////////////////////////////////////////////////////////////////////
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:	//�E�B���h�E��j������
		PostQuitMessage(0);	//WM_QUIT ���b�Z�[�W��Ԃ�
		break;

	case WM_CLOSE:	//�~���������Ƃ�
		DestroyWindow(hWnd);	//WM_DESTROY ���b�Z�[�W��Ԃ�
		break;

	case WM_KEYDOWN:	//�L�[���͂������Ƃ�
		switch (wParam)
		{
		case VK_ESCAPE:		//�G�X�P�[�v�L�[
			DestroyWindow(hWnd);	//WM_DESTROY ���b�Z�[�W��Ԃ�
			break;

		default:
			break;
		}

	default:
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

////////////////////////////////////////////////////////////////////////////////
//����������
////////////////////////////////////////////////////////////////////////////////
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	//�ϐ��錾
	D3DDISPLAYMODE d3ddm;
	D3DPRESENT_PARAMETERS d3dpp;

	//Direct3D�I�u�W�F�N�g�̐���
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}

	//�f�B�X�v���C���[�h���擾
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	//�f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.BackBufferWidth = SCREEN_WIDTH;
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;
	d3dpp.BackBufferFormat = d3ddm.Format;
	d3dpp.BackBufferCount = 1;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	d3dpp.Windowed = bWindow;
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;

	//Direct3D�f�o�C�X�̐���
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &g_pD3DDevice)))
	{	//�`�揈���F�n�[�h�E�F�A�@���_�����F�n�[�h�E�F�A�@�Ŏ��s�ł��Ȃ������ꍇ
		if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &g_pD3DDevice)))
		{	//�`�揈���F�n�[�h�E�F�A�@���_�����F�\�t�g�E�F�A�@�Ŏ��s�ł��Ȃ������ꍇ
			if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &g_pD3DDevice)))
			{	//�`�揈���F�\�t�g�E�F�A�@���_�����F�\�t�g�E�F�A�@�Ŏ��s�ł��Ȃ������ꍇ
				return E_FAIL;
			}
		}
	}

	//�����_�[�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);				//�J�����O�̐ݒ�
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);				//���u�����h(���l�̍���)�̐ݒ�
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		//�\�[�X(�`�挳�F�G�A�摜)�̍������@�̐ݒ�
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	//�f�X�e�B�l�[�V����(�`���F���n)�̍������@�̐ݒ�

	//�T���v���[�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	//�k�������
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	//�g�厞���
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	//U�l�J��Ԃ�
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);	//V�l�J��Ԃ�

	// �e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE); // ���l�̍���
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	//�����\��
	D3DXCreateFont(g_pD3DDevice, 30, 0, 0, 0, FALSE, SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &g_pFont);

	//���͂̏�����
	InitKeyboard(hInstance, hWnd);

	//�^�C�g���̏�����
	InitTitle();

	//�`���[�g���A���̏�����
	InitTutorial();

	//�t�F�[�h�̏�����
	InitFade(MODE_GAME);

	return S_OK;
}

////////////////////////////////////////////////////////////////////////////////
//�I������
////////////////////////////////////////////////////////////////////////////////
void Uninit(void)
{	
	//���͂̏I��
	UninitKeyboard();

	//�t�F�[�h�̏I��
	UninitFade();

	//�t�H���g�̊J��
	if (g_pFont != NULL)
	{
		g_pFont->Release();			//�J��
		g_pFont = NULL;				//������
	}

	//Direct3D�f�o�C�X�̊J��
	if (g_pD3DDevice != NULL)
	{
		g_pD3DDevice->Release();	//�J��
		g_pD3DDevice = NULL;		//������
	}

	//Direct3D�I�u�W�F�N�g�̊J��
	if (g_pD3D != NULL)
	{
		g_pD3D->Release();			//�J��
		g_pD3D = NULL;				//������
	}
}

////////////////////////////////////////////////////////////////////////////////
//�X�V����
////////////////////////////////////////////////////////////////////////////////
void Update(void)
{
	//���͂̍X�V
	UpdateKeyboard();

	//�R���g���[���[�̍X�V
	LoadGamepad();

	//�t�F�[�h�̍X�V
	UpdateFade();

	//�e��X�V
	switch (g_mode)
	{
	case MODE_TITLE:
		//�^�C�g���̍X�V����
		UpdateTitle();
		break;

	case MODE_TUTORIAL:
		//�`���[�g���A���̍X�V����
		UpdateTutorial();
		break;

	case MODE_GAME:
		//�Q�[����ʂ̍X�V����
		UpdateGame();
		break;

	case MODE_RESULT:
		//���U���g��ʂ̍X�V����
		UpdateResult();
		break;
	case MODE_RANKING:
		//�����L���O�X�V����
		UpdateRanking();
		break;
	}

}

////////////////////////////////////////////////////////////////////////////////
//�`�揈��
////////////////////////////////////////////////////////////////////////////////
void Draw(void)
{
	//�o�b�N�o�b�t�@&Z�o�b�t�@�̃N���A(��ʂ̃N���A)
	g_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	//�`��̊J�n
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{
		//�e��X�V
		switch (g_mode)
		{
		case MODE_TITLE:
			//�^�C�g���̕`�揈��
			DrawTitle();
			break;

		case MODE_TUTORIAL:
			//�`���[�g���A���̕`�揈��
			DrawTutorial();
			break;

		case MODE_GAME:
			//�Q�[����ʂ̕`�揈��
			DrawGame();
			break;

		case MODE_RESULT:
			//���U���g��ʂ̕`�揈��
			DrawResult();
			break;
		case MODE_RANKING:
			//�����L���O�`�揈��
			DrawRanking();
			break;
		}

		//FPS�̕`�揈��
#ifdef _DEBUG
		DrawFPS();
		DrawText();
#endif

		DrawFade();

		//�`��̏I��
		g_pD3DDevice->EndScene();
	}
	//�o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

////////////////////////////////////////////////////////////////////////////////
//FPS�\��
////////////////////////////////////////////////////////////////////////////////
void DrawFPS(void)
{
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];
	wsprintf(&aStr[0], "FPS:%d\n", g_nCountFPS);

	//�e�L�X�g�̕`��
	g_pFont->DrawTextA(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
}

////////////////////////////////////////////////////////////////////////////////
//�e�L�X�g�\��
////////////////////////////////////////////////////////////////////////////////
void DrawText(void)
{
	RECT rect = { 0,50,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[512];
	CAMERA *camera = GetCamera();
	PLAYER *player = GetPlayer();
	ENEMY *enemy = GetEnemy();
	float Gaiseki = *GetGaiseki();
	int nNum = sprintf(&aStr[0], "�J�������_���W:%f|%f|%f\n", camera->posV.x, camera->posV.y, camera->posV.z);
	nNum += sprintf(&aStr[nNum], "�J���������_���W:%f|%f|%f\n", camera->posR.x, camera->posR.y, camera->posR.z);
	nNum += sprintf(&aStr[nNum], "�J������]���:%f|%f|%f\n", camera->rot.x, camera->rot.y, camera->rot.z);
	nNum += sprintf(&aStr[nNum], "�v���C���[���W:%f|%f|%f\n", player->pos.x, player->pos.y, player->pos.z);
	nNum += sprintf(&aStr[nNum], "�v���C���[��]:%f|%f|%f\n", player->rot.x, player->rot.y, player->rot.z);
	nNum += sprintf(&aStr[nNum], "�v���C���[�̗̑�:%d\n", player->nLife);
	nNum += sprintf(&aStr[nNum], "�v���C���[��MP:%d\n", player->nMP);
	nNum += sprintf(&aStr[nNum], "�v���C���[�N�[���_�E��:%f\n", player->nCooldown / 60.0f);
	nNum += sprintf(&aStr[nNum], "�v���C���[�r��:%f\n", player->nChantCounter / 60.0f);
	nNum += sprintf(&aStr[nNum], "�v���C���[�X�L�����g���邩:%d\n", player->bUseSkill);
	nNum += sprintf(&aStr[nNum], "gaiseki:%f\n", Gaiseki);
	nNum += sprintf(&aStr[nNum], "�G�̗̑�:%d\n", enemy->nLife);

	//�e�L�X�g�̕`��
	g_pFont->DrawTextA(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
}

////////////////////////////////////////////////////////////////////////////////
//���[�h�̐ݒ�
////////////////////////////////////////////////////////////////////////////////
void SetMode(MODE mode)
{
	//���݂̉�ʂ̏I������
	switch (g_mode)
	{
	case MODE_TITLE:
		//�^�C�g���̏I������
		UninitTitle();
		break;

	case MODE_TUTORIAL:
		//�`���[�g���A���̏I������
		UninitTutorial();
		break;

	case MODE_GAME:
		//�Q�[����ʂ̏I������
		UninitGame();
		break;

	case MODE_RESULT:
		//���U���g��ʂ̏I������
		UninitResult();
		break;
	case MODE_RANKING:
		//�����L���O�I������
		UninitRanking();
		break;
	}

	//��ʑJ�ڌ�̉�ʂ̏���������
	switch (mode)
	{
	case MODE_TITLE:
		//�^�C�g���̏���������
		InitTitle();
		break;

	case MODE_TUTORIAL:
		//�`���[�g���A���̏���������
		InitTutorial();
		break;

	case MODE_GAME:
		//�Q�[����ʂ̏���������
		InitGame();
		break;

	case MODE_RESULT:
		//���U���g��ʂ̏���������
		InitResult();
		break;

	case MODE_RANKING:
		//�����L���O������
		InitRanking();
	}

	g_mode = mode;
}

////////////////////////////////////////////////////////////////////////////////
//�f�o�C�X�̎擾
////////////////////////////////////////////////////////////////////////////////
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}

HWND GethWnd(void)
{
	return hWnd;
}
