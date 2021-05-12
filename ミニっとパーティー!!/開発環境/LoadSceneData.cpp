//-----------------------------------------------------------------
//
//	�e�L�X�g�ǂݍ��� (LoadText.cpp)
// Author:Itsuki Takaiwa
//
//-----------------------------------------------------------------
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

#include "LoadSceneData.h"
#include "texture_set.h"
#include "texture.h"
#include "model_set.h"
#include "shadow.h"
#include "player.h"
#include "camera.h"
#include "light.h"
#include "wall.h"
#include "meshfield.h"

//-----------------------------------------------------------------
// �\���̂̐錾
//-----------------------------------------------------------------
typedef struct
{
	int nCntTexture = 0;		// �e�N�X�`����
	int nCntModel = 0;			// ���f����
	int nCntCamera = 0;			// �J������
	int nCntLight = 0;			// ���C�g��
	int nCntPlayer = 0;			// �v���C���[��
}Counter;

typedef struct
{
	bool bCameraSet = false;
	bool bLightSet = false;
	bool bFieldSet = false;
	bool bWallSet = false;
	bool bModelSet = false;
	bool bPlayerSet = false;
}Set;

typedef struct
{
	D3DXVECTOR3 pos;	// �ʒu���
	D3DXVECTOR3 rot;	// �������
	int nFieldX;		// �ǂ̐�(��)
	int nFieldZ;		// �ǂ̐�(�s)
	float fWidth;		// ��
	float fDepth;		// ���s
	int nIdxtexture;	// ���Ԗڂ̃e�N�X�`����
}MeshFieldData;

typedef struct
{
	D3DXVECTOR3 pos;		// �ʒu���
	D3DXVECTOR3 rot;		// �������
	D3DXVECTOR3 moveRot;	// ��]�ʏ��
	int nWallX;				// �ǂ̐�(��)
	int nWallY;				// �ǂ̐�(�s)
	float fWidth;			// ��
	float fHieght;			// ���s
	int nIdxtexture;		// ���Ԗڂ̃e�N�X�`����
}WallData;

typedef struct
{
	D3DXVECTOR3 pos;	// �ʒu���
	D3DXVECTOR3 rot;	// �������
	int nIdxModel;		// ���Ԗڂ̃��f����
	int nCollition;	// �����蔻�肷�邩�ǂ���	 
}ModelSetData;

//-----------------------------------------------------------------
// �O���[�o���ϐ�
//-----------------------------------------------------------------
Counter g_Counter;				// �J�E���^�[�p
Set g_bSet;						// �Z�b�g�p
MeshFieldData g_MeshFieldInfo;
WallData g_WalInfo;
ModelSetData g_ModelSetInfo;
char aSceneFileName[MODE_MAX][128];		// �V�[���t�@�C���l�[��

//-----------------------------------------------------------------
// �V�[�����̓ǂݍ���
//-----------------------------------------------------------------
void LoadSceneInfoText(void)
{
	// FILE�^�̃|�C���^�֐�
	FILE *pFile;

	// �\���̂̃|�C���^�ϐ�
	Character *pCharacter = GetCharacter();

	// �t�@�C�����J��
	pFile = fopen("data/TEXT/scene.txt", "r");

	// �ϐ��錾
	bool bGetScript = false;

	char aLine[128];
	char aText[128];
	int nCntScene = 0;

	// SCRIPT��T��
	while (fgets(aLine, 128, pFile) != NULL)
	{
		fscanf(pFile, "%s", &aText[0]);

		// SCRIPT���������炻��ȍ~��ǂݍ���
		if (strcmp(&aText[0], "SCRIPT") == 0)
		{
			bGetScript = true;
		}

		if (bGetScript == true)
		{
			// SCENE_FILENAME����������e�L�X�g�t�@�C�������i�[
			if (strcmp(&aText[0], "SCENE_FILENAME") == 0)
			{
				fscanf(pFile, "%s %s", &aText[0], &aSceneFileName[nCntScene][0]);

				// �v���C���[�̑��������i�[����̂ŃJ�E���g�𑝂₷
				nCntScene++;
			}

			// END_SCRIPT����������ǂݍ��݂��I����
			if (strcmp(&aText[0], "END_SCRIPT") == 0)
			{
				break;
			}
		}
	}
	// �t�@�C�������
	fclose(pFile);
}		

//-----------------------------------------------------------------
// �X�e�[�W���̓ǂݍ���
//-----------------------------------------------------------------
void LoadSceneData(void)
{
	// ���[�h�̎擾
	MODE mode = GetMode();

	// FILE�^�̃|�C���^�֐�
	FILE *pFile;

	// �t�@�C�����J��
	pFile = fopen(&aSceneFileName[mode][0], "r");

	// �ϐ��錾
	bool bGetScript = false;
	char aLine[128];
	char aText[128];

	// �ϐ��̏�����
	g_Counter.nCntTexture = 0;		
	g_Counter.nCntModel = 0;		
	g_Counter.nCntCamera = 0;		
	g_Counter.nCntLight = 0;		
	g_Counter.nCntPlayer = 0;		

	// SCRIPT��T��
	while (fgets(aLine, 128, pFile) != NULL)
	{
		fscanf(pFile, "%s", &aText[0]);

		// SCRIPT���������炻��ȍ~��ǂݍ���
		if (strcmp(&aText[0], "SCRIPT") == 0)
		{
			bGetScript = true;
		}

		if (bGetScript == true)
		{
			// UI�z�u���̓ǂݍ���
			LoadUIsetInfoText(pFile, &aText[0]);

			// �e�L�X�g���̓ǂݍ���
			LoadTextureInfo(pFile, &aText[0]);

			// ���f�����̓ǂݍ���
			LoadModelInfo(pFile, &aText[0]);

			// �J�������̓ǂݍ���
			LoadCameraInfo(pFile, &aText[0]);

			// ���C�g���̓ǂݍ���
			LoadLightInfo(pFile, &aText[0]);

			// �t�B�[���h���̓ǂݍ���
			LoadFieldInfo(pFile, &aText[0]);
			
			// �Ǐ��̓ǂݍ���
			LoadWallInfo(pFile, &aText[0]);

			// ���f���z�u���̓ǂݍ���
			LoadModelSetInfo(pFile, &aText[0]);

			// �v���C���[�z�u���̓ǂݍ���
			LoadPlayerSetInfo(pFile, &aText[0]);

			// END_SCRIPT����������ǂݍ��݂��I����
			if (strcmp(&aText[0], "END_SCRIPT") == 0)
			{
				// ���f�����̏�����
				InitModelSet();

				break;
			}
		}
	}
	// �t�@�C�������
	fclose(pFile);
}

//-----------------------------------------------------------------
// UI�Z�b�g���e�L�X�g�̓ǂݍ���
//-----------------------------------------------------------------
void LoadUIsetInfoText(FILE *pFile, char *aText)
{
	// �e�N�X�`�����̎擾
	TextureSet *pTextureSet = GetTextureSet();

	// UISET_FILENAME����������e�L�X�g�t�@�C�������i�[
	if (strcmp(&aText[0], "UISET_FILENAME") == 0)
	{
		fscanf(pFile, "%s %s", &aText[0], &pTextureSet->aTextName[0]);
	}
}

//-----------------------------------------------------------------
// �e�N�X�`�����̓ǂݍ���
//-----------------------------------------------------------------
void LoadTextureInfo(FILE *pFile,char *aText)
{
	// �e�N�X�`�����̎擾
	Texture *pTexture = GetTexture();

	// NUM_TEXTURE����������e�N�X�`���̑������i�[
	if (strcmp(&aText[0], "NUM_TEXTURE") == 0)
	{
		fscanf(pFile, "%s %d", &aText[0], &pTexture->nNumTexture);
	}
	// TEXTURE_FILENAME����������e�N�X�`���̃t�@�C�������i�[
	if (strcmp(&aText[0], "TEXTURE_FILENAME") == 0 && g_Counter.nCntTexture < pTexture->nNumTexture)
	{
		fscanf(pFile, "%s %s", &aText[0], &pTexture->TextureInfo[g_Counter.nCntTexture].aTexcharName[0]);

		// �e�N�X�`���̑��������i�[����̂ŃJ�E���g�𑝂₷
		g_Counter.nCntTexture++;
	}
}

//-----------------------------------------------------------------
// ���f�����̓ǂݍ���
//-----------------------------------------------------------------
void LoadModelInfo(FILE *pFile, char *aText)
{
	// ���f�����̎擾
	ModelSet *pModelSet = GetModelSet();

	// NUM_MODEL���������烂�f���̑������i�[
	if (strcmp(&aText[0], "NUM_MODEL") == 0)
	{
		fscanf(pFile, "%s %d", &aText[0], &pModelSet->nNumModel);
	}
	// MODEL_FILENAME����������X�t�@�C�������i�[
	if (strcmp(&aText[0], "MODEL_FILENAME") == 0 && g_Counter.nCntModel < pModelSet->nNumModel)
	{
		fscanf(pFile, "%s %s", &aText[0], &pModelSet->modelInfo[g_Counter.nCntModel].aFileName[0]);

		// ���f���̑��������i�[����̂ŃJ�E���g�𑝂₷
		g_Counter.nCntModel++;
	}
}

//-----------------------------------------------------------------
// �J�������̓ǂݍ���
//-----------------------------------------------------------------
void LoadCameraInfo(FILE *pFile, char *aText)
{
	// �J�������̎擾
	Camera *pCamera = GetCamera();

	// CAMERASET����������J��������ǂݍ��ދ���^����
	if (strcmp(&aText[0], "CAMERASET") == 0)
	{
		g_bSet.bCameraSet = true;
	}
	if (g_bSet.bCameraSet == true)
	{
		// POS���������王�_�ʒu�����i�[
		if (strcmp(&aText[0], "POS") == 0)
		{
			fscanf(pFile, "%s %f %f %f", &aText[0],
				&pCamera->CameraInfo[g_Counter.nCntCamera].moveV.x,
				&pCamera->CameraInfo[g_Counter.nCntCamera].moveV.y,
				&pCamera->CameraInfo[g_Counter.nCntCamera].moveV.z);
		}
		// REF���������璍���_�ʒu�����i�[
		if (strcmp(&aText[0], "REF") == 0)
		{
			fscanf(pFile, "%s %f %f %f", &aText[0],
				&pCamera->CameraInfo[g_Counter.nCntCamera].moveR.x,
				&pCamera->CameraInfo[g_Counter.nCntCamera].moveR.y,
				&pCamera->CameraInfo[g_Counter.nCntCamera].moveR.z);
		}
		// LENGE����������ǂꂾ���������ʒu�ɒu�����i�[
		if (strcmp(&aText[0], "LENGE") == 0)
		{
			fscanf(pFile, "%s %f", &aText[0],&pCamera->CameraInfo[g_Counter.nCntCamera].fLenge);
		}
		// VIEWPORT��������������i�[
		if (strcmp(&aText[0], "VIEWPORT") == 0)
		{
			fscanf(pFile, "%s %d %d %d %d", &aText[0],
				&pCamera->CameraInfo[g_Counter.nCntCamera].viewport.X,
				&pCamera->CameraInfo[g_Counter.nCntCamera].viewport.Y,
				&pCamera->CameraInfo[g_Counter.nCntCamera].viewport.Width,
				&pCamera->CameraInfo[g_Counter.nCntCamera].viewport.Height);
		}
		// END_CAMERASET����������J�������̓ǂݍ��݂��I����
		if (strcmp(&aText[0], "END_CAMERASET") == 0)
		{
			// �ϐ������Z
			g_Counter.nCntCamera++;

			// �z�u����J�����������Z
			pCamera->nNumCamera++;

			g_bSet.bCameraSet = false;
		}
	}
}

//-----------------------------------------------------------------
// ���C�g���̓ǂݍ���
//-----------------------------------------------------------------
void LoadLightInfo(FILE *pFile, char *aText)
{
	// ���C�g���̓ǂݍ���
	Light *pLight = GetLight();

	// LIGHTSET���������烉�C�g����ǂݍ��ދ���^����
	if (strcmp(&aText[0], "LIGHTSET") == 0)
	{
		g_bSet.bLightSet = true;
	}
	if (g_bSet.bLightSet == true)
	{
		// DIRECTION������������������i�[
		if (strcmp(&aText[0], "DIRECTION") == 0)
		{
			fscanf(pFile, "%s %f %f %f", &aText[0],
				&pLight->vecDir[g_Counter.nCntLight].x,
				&pLight->vecDir[g_Counter.nCntLight].y,
				&pLight->vecDir[g_Counter.nCntLight].z);
		}
		// DIFFUSE���������疾�邳�����i�[
		if (strcmp(&aText[0], "DIFFUSE") == 0)
		{
			fscanf(pFile, "%s %f %f %f", &aText[0],
				&pLight->colDef[g_Counter.nCntLight].r,
				&pLight->colDef[g_Counter.nCntLight].g,
				&pLight->colDef[g_Counter.nCntLight].b);
		}
		// END_LIGHTSET���������烉�C�g���̓ǂݍ��݂��I����
		if (strcmp(&aText[0], "END_LIGHTSET") == 0)
		{
			// �ϐ������Z
			g_Counter.nCntLight++;

			// �z�u����J�����������Z
			pLight->nNumLight++;

			// ���C�g���̓ǂݍ��݂��I����
			g_bSet.bLightSet = false;
		}
	}
}

//-----------------------------------------------------------------
// �t�B�[���h���̓ǂݍ���
//-----------------------------------------------------------------
void LoadFieldInfo(FILE *pFile, char *aText)
{
	// �t�B�[���h���̎擾
	MeshFieldData *pMeshFieldInfo = &g_MeshFieldInfo;

	// FIELDSET���������t�B�[���h����ǂݍ��ދ���^����
	if (strcmp(&aText[0], "FIELDSET") == 0)
	{
		g_bSet.bFieldSet = true;
	}
	if (g_bSet.bFieldSet == true)
	{
		// TEXTYPE����������e�N�X�`���ԍ����i�[
		if (strcmp(&aText[0], "TEXTYPE") == 0)
		{
			fscanf(pFile, "%s %d", &aText[0], &pMeshFieldInfo->nIdxtexture);
		}
		// POS����������ʒu�����i�[
		if (strcmp(&aText[0], "POS") == 0)
		{
			fscanf(pFile, "%s %f %f %f", &aText[0],
				&pMeshFieldInfo->pos.x,
				&pMeshFieldInfo->pos.y,
				&pMeshFieldInfo->pos.z);
		}
		// ROT������������������i�[
		if (strcmp(&aText[0], "ROT") == 0)
		{
			fscanf(pFile, "%s %f %f %f", &aText[0],
				&pMeshFieldInfo->rot.x,
				&pMeshFieldInfo->rot.y,
				&pMeshFieldInfo->rot.z);
		}
		// BLOCK����������}�X�����i�[
		if (strcmp(&aText[0], "BLOCK") == 0)
		{
			fscanf(pFile, "%s %d %d", &aText[0],
				&pMeshFieldInfo->nFieldX,
				&pMeshFieldInfo->nFieldZ);
		}
		// SIZE����������T�C�Y�����i�[
		if (strcmp(&aText[0], "SIZE") == 0)
		{
			fscanf(pFile, "%s %f %f", &aText[0],
				&pMeshFieldInfo->fWidth,
				&pMeshFieldInfo->fDepth);
		}
		// END_FIELDSET����������t�B�[���h���̓ǂݍ��݂��I����
		if (strcmp(&aText[0], "END_FIELDSET") == 0)
		{
			// ���b�V���t�B�[���h�̐ݒu
			SetMeshField(pMeshFieldInfo->nIdxtexture,
				pMeshFieldInfo->pos,
				pMeshFieldInfo->rot,
				pMeshFieldInfo->nFieldX,
				pMeshFieldInfo->nFieldZ,
				pMeshFieldInfo->fWidth,
				pMeshFieldInfo->fDepth);

			// �t�B�[���h���̓ǂݍ��݂��I����
			g_bSet.bFieldSet = false;
		}
	}
}

//-----------------------------------------------------------------
// �Ǐ��̓ǂݍ���
//-----------------------------------------------------------------
void LoadWallInfo(FILE *pFile, char *aText)
{
	// �Ǐ��̎擾
	WallData *pWallInfo = &g_WalInfo;

	// WALLSET����������Ǐ���ǂݍ��ދ���^����
	if (strcmp(&aText[0], "WALLSET") == 0)
	{
		// ������
		pWallInfo->nIdxtexture = -1;
		pWallInfo->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pWallInfo->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pWallInfo->moveRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pWallInfo->nWallX = 0;
		pWallInfo->nWallY = 0;
		pWallInfo->fWidth = 0.0f;
		pWallInfo->fHieght = 0.0f;

		g_bSet.bWallSet = true;
	}
	if (g_bSet.bWallSet == true)
	{
		// TEXTYPE����������e�N�X�`���ԍ����i�[
		if (strcmp(&aText[0], "TEXTYPE") == 0)
		{
			fscanf(pFile, "%s %d", &aText[0], &pWallInfo->nIdxtexture);
		}
		// POS����������ʒu�����i�[
		if (strcmp(&aText[0], "POS") == 0)
		{
			fscanf(pFile, "%s %f %f %f", &aText[0],
				&pWallInfo->pos.x,
				&pWallInfo->pos.y,
				&pWallInfo->pos.z);
		}
		// ROT������������������i�[
		if (strcmp(&aText[0], "ROT") == 0)
		{
			fscanf(pFile, "%s %f %f %f", &aText[0],
				&pWallInfo->rot.x,
				&pWallInfo->rot.y,
				&pWallInfo->rot.z);
		}
		// MOVEROT�����������]�ʏ����i�[
		if (strcmp(&aText[0], "MOVEROT") == 0)
		{
			fscanf(pFile, "%s %f %f %f", &aText[0],
				&pWallInfo->moveRot.x,
				&pWallInfo->moveRot.y,
				&pWallInfo->moveRot.z);
		}
		// BLOCK����������}�X�����i�[
		if (strcmp(&aText[0], "BLOCK") == 0)
		{
			fscanf(pFile, "%s %d %d", &aText[0],
				&pWallInfo->nWallX,
				&pWallInfo->nWallY);
		}
		// SIZE����������T�C�Y�����i�[
		if (strcmp(&aText[0], "SIZE") == 0)
		{
			fscanf(pFile, "%s %f %f", &aText[0],
				&pWallInfo->fWidth,
				&pWallInfo->fHieght);
		}
		// END_WALLSET����������Ǐ��̓ǂݍ��݂��I����
		if (strcmp(&aText[0], "END_WALLSET") == 0)
		{
			// �ǂ̐ݒu
			SetWall(pWallInfo->nIdxtexture,
				pWallInfo->pos,
				pWallInfo->rot,
				pWallInfo->moveRot,
				pWallInfo->nWallX,
				pWallInfo->nWallY,
				pWallInfo->fWidth,
				pWallInfo->fHieght);

			// �Ǐ��̓ǂݍ��݂��I����
			g_bSet.bWallSet = false;
		}
	}
}

//-----------------------------------------------------------------
// ���f���z�u���̓ǂݍ���
//-----------------------------------------------------------------
void LoadModelSetInfo(FILE *pFile, char *aText)
{
	// ���f���z�u���̎擾
	ModelSetData *pModelSetInfo = &g_ModelSetInfo;

	// �e�p�[�c�ɏ���ǂݍ��ދ�������Ƃ�����
	if (strcmp(&aText[0], "MODELSET") == 0)
	{
		g_bSet.bModelSet = true;
	}
	if (g_bSet.bModelSet == true)
	{
		// TYPE����������ԍ����i�[
		if (strcmp(&aText[0], "TYPE") == 0)
		{
			fscanf(pFile, "%s %d", &aText[0], &pModelSetInfo->nIdxModel);
		}
		// POS������������W�����i�[
		if (strcmp(&aText[0], "POS") == 0)
		{
			fscanf(pFile, "%s %f %f %f", &aText[0],
				&pModelSetInfo->pos.x,
				&pModelSetInfo->pos.y,
				&pModelSetInfo->pos.z);
		}
		// ROT����������p�x�����i�[
		if (strcmp(&aText[0], "ROT") == 0)
		{
			// �ϐ��錾
			D3DXVECTOR3 rot;			// �p�x�ۑ��p

			fscanf(pFile, "%s %f %f %f", &aText[0],
				&rot.x,
				&rot.y,
				&rot.z);

			pModelSetInfo->rot.x = (rot.x / 180.0f) * D3DX_PI;
			pModelSetInfo->rot.y = (rot.y / 180.0f) * D3DX_PI;
			pModelSetInfo->rot.z = (rot.z / 180.0f) * D3DX_PI;
		}
		// COLLISION���������瓖���蔻�肷�邩�ǂ����i�[
		if (strcmp(&aText[0], "COLLISION") == 0)
		{
			int nNumCollition = 1;
			fscanf(pFile, "%s %d", &aText[0], &nNumCollition);

			pModelSetInfo->nCollition = nNumCollition;
		}
		// END_MODELSETKEY���������烂�f���z�u������
		if (strcmp(&aText[0], "END_MODELSET") == 0)
		{
			// ���f���Z�b�g
			SetModel(pModelSetInfo->nIdxModel,
				pModelSetInfo->pos,
				pModelSetInfo->rot,
				pModelSetInfo->nCollition);

			// ������
			pModelSetInfo->nCollition = 1;

			// ���f���z�u���̎擾���I����
			g_bSet.bModelSet = false;
		}
	}
}

//-----------------------------------------------------------------
// �v���C���[�z�u���̓ǂݍ���
//-----------------------------------------------------------------
void LoadPlayerSetInfo(FILE *pFile, char *aText)
{
	// �v���C���[���̎擾
	Player *pPlayer = GetPlayer();
	
	// ���Ԗڂ̏��
	pPlayer += g_Counter.nCntPlayer;

	// �ϐ��錾
	D3DXVECTOR3 rot;			// �����ۑ��p

	// PLAYERSET����������v���C���[�z�u�����i�[���鋖��^����
	if (strcmp(&aText[0], "PLAYERSET") == 0)
	{
		g_bSet.bPlayerSet = true;
	}
	if (g_bSet.bPlayerSet == true)
	{
		// POS������������W�����i�[
		if (strcmp(&aText[0], "POS") == 0)
		{
			fscanf(pFile, "%s %f %f %f", &aText[0],
				&pPlayer->pos.x,
				&pPlayer->pos.y,
				&pPlayer->pos.z);
		}
		// ROT����������p�x�����i�[
		if (strcmp(&aText[0], "ROT") == 0)
		{
			fscanf(pFile, "%s %f %f %f", &aText[0],
				&rot.x,
				&rot.y,
				&rot.z);

			pPlayer->rot.x = (rot.x / 180.0f) * D3DX_PI;
			pPlayer->rot.y = (rot.y / 180.0f) * D3DX_PI;
			pPlayer->rot.z = (rot.z / 180.0f) * D3DX_PI;
		}
		// END_PLAYERSET���������狖��������
		if (strcmp(&aText[0], "END_PLAYERSET") == 0)
		{
			// �v���C���[�z�u���̎擾���I����
			g_bSet.bPlayerSet = false;

			// ���̍X�V
			g_Counter.nCntPlayer++;
		}
	}
}