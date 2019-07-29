/*****************************************************************************
main.h
Aythor	: ���@��
Data	: 2016_07_05
=============================================================================
Updata

*****************************************************************************/
#ifndef MAIN_H
#define MAIN_H

//////////////////////////////////////////////////////////////////////////////
//�萔��`
//////////////////////////////////////////////////////////////////////////////
#define SCREEN_WIDTH	(1280)		//�E�B���h�E�̕�
#define SCREEN_HEIGHT	(720)		//�E�B���h�E�̍���

#define FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)	//2D�|���S���ݒ�
#define NUM_VERTEX		(4)			//���_��
#define NUM_VERTEXLIST	(6)			//TRIANGLELIST�p
#define NUM_POLYGON		(2)			//�|���S����

#define SAFE_RELEASE(x) { if(x){(x)->Release(); (x) = NULL;} }

#define PI				(3.141592f)	//�~����

//////////////////////////////////////////////////////////////////////////////
//�w�b�_�[�t�@�C���C���N���[�h
//////////////////////////////////////////////////////////////////////////////
#include <Windows.h>
#include <tchar.h>
#include <stdio.h>
#include <d3dx9.h>
#define	DisableLoad	(0x0800)
#include <dinput.h>
#include <XAudio2.h>

//////////////////////////////////////////////////////////////////////////////
//�\���̒�`
//////////////////////////////////////////////////////////////////////////////
typedef struct
{
	D3DXVECTOR3 pos;
	float rhw;
	D3DCOLOR color;
	D3DXVECTOR2 tex;
}VERTEX2D;		//�|���S���`�ʗp�\����

typedef enum
{
	TITLE_MODE = 0,			//�^�C�g�����[�h
	STAGE_SELECT,
	GAME_MODE,				//�Q�[�����[�h
	RESULT_MODE,			//���U���g���[�h
	MODE_MAX,				//���[�h�ő吔
	MODE_NULL				//null
}MODE;

//////////////////////////////////////////////////////////////////////////////
// �v���g�^�C�v�錾
//////////////////////////////////////////////////////////////////////////////
LPDIRECT3DDEVICE9 getDevice ( void );
void	setMode	(MODE mode);
MODE	getMode	(void);

//////////////////////////////////////////////////////////////////////////////
//���C�u�����̃����N
//////////////////////////////////////////////////////////////////////////////
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")
#pragma comment (lib, "dxguid.lib")
#pragma comment (lib, "winmm.lib")		//�V�X�e�������擾�ɕK�v
#pragma comment (lib, "dinput8.lib")	//���͑��u���C�u����

#endif