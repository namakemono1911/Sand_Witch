/*****************************************************************************
gameBG.cpp
Aythor	: ���@��
Data	: 2017_06_04
=============================================================================
Updata

*****************************************************************************/
//////////////////////////////////////////////////////////////////////////////
//�w�b�_�[�t�@�C���C���N���[�h
//////////////////////////////////////////////////////////////////////////////
#include "main.h"
#include "polygon.h"
#include "gameBG.h"
#include "stage.h"

//////////////////////////////////////////////////////////////////////////////
//�萔��`
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//�\���̒�`
//////////////////////////////////////////////////////////////////////////////
typedef struct
{
	ROTPOLYGON		conf;		//�|���S���̊e��ݒ�
	TEXTURE			tex;		//�e�N�X�`���ݒ�
	GAME_BG_TYPE	type;		//�w�i�摜�̎��
}GAME_BG;

//////////////////////////////////////////////////////////////////////////////
//�v���g�^�C�v�錾
//////////////////////////////////////////////////////////////////////////////
HRESULT makeVertexGameBG ( LPDIRECT3DDEVICE9 pDevice );

//////////////////////////////////////////////////////////////////////////////
//�O���[�o���ϐ�
//////////////////////////////////////////////////////////////////////////////
LPDIRECT3DTEXTURE9	g_pTextureGameBG = NULL;		//�e�N�X�`���C���^�[�t�F�C�X
LPDIRECT3DVERTEXBUFFER9 g_pVtxBufferGameBG = NULL;	//���_�o�b�t�@�Ǘ��C���^�[�t�F�C�X

GAME_BG		g_gameBG;		//�w�i�\����
const char	*texNameGameBG[GAMEBG_MAX] =
{
	"data/TEXTURE/GAME/BG/stageBG01.jpg",
	"data/TEXTURE/GAME/BG/stageBG02.jpg",
	"data/TEXTURE/GAME/BG/stageBG03.jpg",
};

//////////////////////////////////////////////////////////////////////////////
//�֐���	: initGameBG
//�Ԃ�l	: 
//����		: �|���S��������
//////////////////////////////////////////////////////////////////////////////
void initGameBG( void )
{
	//�ϐ��錾
	LPDIRECT3DDEVICE9 pDevice = getDevice();	//�f�o�C�X�|�C���^�擾

	//�\���̏�����
	initRotPolygon(&g_gameBG.conf,
		D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.f),
		D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.f));

	initTexture(&g_gameBG.tex,
		D3DXVECTOR2(0.f, 0.f),
		D3DXVECTOR2(1.f, 1.f));
	
	//�e�N�X�`���̓ǂݍ���
	int num;
	switch(getStgNum())
	{
	case 0:
	case 1:
	case 2:
	case 3:
		num = 0;
		break;

	case 4:
	case 5:
	case 6:
		num = 1;
		break;

	case 7:
	case 8:
	case 9:
		num = 2;
		break;
	}

	if(FAILED(D3DXCreateTextureFromFile(pDevice, texNameGameBG[num], &g_pTextureGameBG)))
	{
		MessageBox(NULL, "bg", "�G���[", MB_OK);
	}

	//�f�o�C�X�擾
	makeVertexGameBG(pDevice);
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: uninitGameBG
//�Ԃ�l	: 
//����		: �|���S���I��
//////////////////////////////////////////////////////////////////////////////
void uninitGameBG( void )
{
	//�e�N�X�`���C���^�[�t�F�C�X�̉��
	if(g_pTextureGameBG != NULL)
	{
		g_pTextureGameBG->Release();
		g_pTextureGameBG = NULL;
	}

	//���_�o�b�t�@�Ǘ��̉��
	if(g_pVtxBufferGameBG != NULL)
	{
		g_pVtxBufferGameBG->Release();
		g_pVtxBufferGameBG = NULL;
	}
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: updateGameBG
//�Ԃ�l	: 
//����		: �|���S���X�V
//////////////////////////////////////////////////////////////////////////////
void updateGameBG ( void )
{
	
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: drawBg
//�Ԃ�l	: 
//����		: �|���S���`��
//////////////////////////////////////////////////////////////////////////////
void drawGameBG ( void )
{
	//�ϐ��錾
	LPDIRECT3DDEVICE9 pDevice = getDevice();
	
	//�X�g���[���쐬
	pDevice->SetStreamSource(0, g_pVtxBufferGameBG, 0, sizeof(VERTEX2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	pDevice->SetTexture(0,g_pTextureGameBG);

	//�|���S���̕`��
	pDevice->DrawPrimitive
		(
		D3DPT_TRIANGLESTRIP,	//�|���S���̎��
		0,						//�I�t�Z�b�g(���_��)
		NUM_POLYGON				//�|���S���̐�
		);
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: makeVertexBg
//�Ԃ�l	: 
//����		: ���_�쐬
//////////////////////////////////////////////////////////////////////////////
HRESULT makeVertexGameBG ( LPDIRECT3DDEVICE9 pDevice )
{
	//�ϐ��錾
	VERTEX2D *pVtx = NULL;;		//���z�A�h���X�p�|�C���^

	//���_�o�b�t�@�̐ݒ�
	if(FAILED(pDevice->CreateVertexBuffer
			(
			sizeof(VERTEX2D) * NUM_VERTEX,		//���_�o�b�t�@�T�C�Y
			D3DUSAGE_WRITEONLY,					//���_�o�b�t�@�̎g�p���@
			FVF_VERTEX_2D,						//
			D3DPOOL_MANAGED,					//�������Ǘ����@
			&g_pVtxBufferGameBG,					//���_�o�b�t�@�Ǘ��C���^�[�t�F�C�X
			NULL
			)
		))
		
	{
		return E_FAIL;
	}

	//���_�o�b�t�@�����b�N���ĉ��z�A�h���X���擾
	g_pVtxBufferGameBG->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�(2D���W�E�E���)
	setRotBuffer(pVtx, g_gameBG.conf);

	//�e�N�X�`���ݒ�
	setTexture(pVtx, g_gameBG.tex);

	//rhw�̐ݒ�(�K��1.0f)
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�(0~155�̐����l)
	pVtx[0].color = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].color = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].color = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].color = D3DCOLOR_RGBA(255, 255, 255, 255);

	//���̂�����A�[�����b�N��
	g_pVtxBufferGameBG->Unlock();

	return S_OK;
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: setBgType
//�Ԃ�l	: 
//����		: �w�i�摜�ݒ�
//////////////////////////////////////////////////////////////////////////////
void	setGameBGType	( GAME_BG_TYPE type )
{
	g_gameBG.type = type;
}