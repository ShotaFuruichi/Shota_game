////////////////////////////////////////////////////////////////////////////////
//
//Contents	: �V���[�e�B���O�Q�[�� [main.h]
//Author	: ShotaFuruichi
//Since		: 2020/07/17
//
////////////////////////////////////////////////////////////////////////////////
#ifndef _MAIN_H_
#define _MAIN_H_
#include <windows.h>
#include "d3dx9.h"		//�`�揈���ɕK�v
#include "player.h"
#include "bg.h"
#define DIRECTINPUT_VERSION (0x0800)
#include "dInput.h"		//���͏����ɕK�v
#include "xaudio2.h"	//�T�E���h�Đ��ɕK�v

//���C�u�����̃����N
#pragma comment(lib,"d3d9.lib")		//�`�揈���ɕK�v
#pragma comment(lib,"d3dx9.lib")	//�g�����C�u����
#pragma comment(lib,"dxguid.lib")	//�R���|�[�l���g�g�p�ɕK�v
#pragma comment(lib,"dInput8.lib")	//���͏����ɕK�v
#pragma comment(lib,"winmm.lib")	//

//�}�N����`
#define SCREEN_WIDTH (1920)												//�X�N���[���̕�
#define SCREEN_HEIGHT (1080)											//�X�N���[���̍���
#define FVF_VERTEX_2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)	//���_�t�H�[�}�b�g

//���_�t�H�[�}�b�g�ɍ��킹���\����
typedef struct
{
	D3DXVECTOR3 pos;	//�|���S�����W
	float rhw;
	D3DCOLOR col;		//�J���[���
	D3DXVECTOR2 tex;	//�e�N�X�`�����W
} VERTEX_2D;

//���[�h�̎��
typedef enum
{
	MODE_TITLE = 0,	//�^�C�g�����
	MODE_TUTORIAL,	//�`���[�g���A�����
	MODE_GAME,		//�Q�[�����
	MODE_RESULT,	//���U���g���
	MODE_MAX
} MODE;

//�v���g�^�C�v�錾
LPDIRECT3DDEVICE9 GetDevice(void);
void SetMode(MODE mode);
MODE GetMode(void);

#endif