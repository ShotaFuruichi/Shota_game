////////////////////////////////////////////////////////////////////////////////
//
//Contents	: �A�N�V�����Q�[�� [main.h]
//Author	: ShotaFuruichi
//Since		: 2020/10/13
//
////////////////////////////////////////////////////////////////////////////////
#ifndef _MAIN_H_
#define _MAIN_H_
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include "d3dx9.h"		//�`�揈���ɕK�v
#define DIRECTINPUT_VERSION (0x0800)
#include "dInput.h"		//���͏����ɕK�v
#include "xaudio2.h"	//�T�E���h�Đ��ɕK�v
#include "XInput.h"		//xinput�ɕK�v
#define FVF_VERTEX_3D (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)


//���C�u�����̃����N
#pragma comment(lib,"d3d9.lib")		//�`�揈���ɕK�v
#pragma comment(lib,"d3dx9.lib")	//�g�����C�u����
#pragma comment(lib,"dxguid.lib")	//�R���|�[�l���g�g�p�ɕK�v
#pragma comment(lib,"dInput8.lib")	//���͏����ɕK�v
#pragma comment(lib,"winmm.lib")	//
#pragma comment(lib,"xinput.lib")	//xinout�ɕK�v

//�}�N����`
#define SCREEN_WIDTH (1920)												//�X�N���[���̕�
#define SCREEN_HEIGHT (1080)											//�X�N���[���̍���
#define FVF_VERTEX_2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)	//���_�t�H�[�}�b�g

//���_�t�H�[�}�b�g�ɍ��킹���\����
typedef struct
{
	D3DXVECTOR3 pos;	//�|���S�����W
	D3DXVECTOR3 nor;	//�@���x�N�g��
	D3DCOLOR col;		//�J���[���
	D3DXVECTOR2 tex;	//�e�N�X�`�����W
} VERTEX_3D;

typedef struct
{
	D3DXVECTOR3 pos;
	float rhw;
	D3DCOLOR col;
	D3DXVECTOR2 tex;
}VERTEX_2D;

//���[�h�񋓌^
typedef enum
{
	MODE_TITLE = 0,
	MODE_TUTORIAL,
	MODE_GAME,
	MODE_RESULT,
	MODE_RANKING,
	MODE_MAX
} MODE;

//�v���g�^�C�v�錾
LPDIRECT3DDEVICE9 GetDevice(void);
void DrawFPS(void);
void DrawText(void);
void SetMode(MODE mode);
HWND GethWnd(void);
#endif
