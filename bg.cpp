/*****************************************************************************
bg.cpp
Aythor	: ���@��
Data	: 2017_04_13
=============================================================================
Updata

*****************************************************************************/
//////////////////////////////////////////////////////////////////////////////
//�w�b�_�[�t�@�C���C���N���[�h
//////////////////////////////////////////////////////////////////////////////
#include "main.h"
#include "bg.h"
#include "polygon.h"
#include "input.h"
#include <math.h>

//////////////////////////////////////////////////////////////////////////////
//�萔��`
//////////////////////////////////////////////////////////////////////////////
#define BG_TEXTURENAME "data/TEXTURE/gameBG001.jpg"	//�ǂݍ��ރe�N�X�`���t�@�C��

//////////////////////////////////////////////////////////////////////////////
//�\���̒�`
//////////////////////////////////////////////////////////////////////////////
typedef struct
{
	ROTPOLYGON	conf;		//�|���S���̊e��ݒ�
	TEXTURE		tex;		//�e�N�X�`���ݒ�
	BG_TYPE		type;		//�w�i�摜�̎��
}BG;

//////////////////////////////////////////////////////////////////////////////
//�v���g�^�C�v�錾
//////////////////////////////////////////////////////////////////////////////
HRESULT makeVertexBg ( LPDIRECT3DDEVICE9 pDevice );

//////////////////////////////////////////////////////////////////////////////
//�O���[�o���ϐ�
//////////////////////////////////////////////////////////////////////////////
LPDIRECT3DTEXTURE9	g_pTextureBg[BG_TYPE_MAX] = {NULL};	//�e�N�X�`���C���^�[�t�F�C�X
LPDIRECT3DVERTEXBUFFER9 g_pVtxBufferBg = NULL;	//���_�o�b�t�@�Ǘ��C���^�[�t�F�C�X

BG		g_bg;		//�w�i�\����
const char	*texNameBg[BG_TYPE_MAX] =
{
	"data/TEXTURE/titleBG001.jpg",
	"data/TEXTURE/gameBG001.jpg",
};

//////////////////////////////////////////////////////////////////////////////
//�֐���	: initBg
//�Ԃ�l	: 
//����		: �|���S��������
//////////////////////////////////////////////////////////////////////////////
void initBg ( void )
{
	//�ϐ��錾
	LPDIRECT3DDEVICE9 pDevice = getDevice();	//�f�o�C�X�|�C���^�擾

	//�\���̏�����
	initRotPolygon(&g_bg.conf,
		D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.f),
		D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.f));

	initTexture(&g_bg.tex,
		D3DXVECTOR2(0.f, 0.f),
		D3DXVECTOR2(1.f, 1.f));
	
	//�e�N�X�`���̓ǂݍ���
	for(int i = 0; i < BG_TYPE_MAX; i++)
	{
		if(FAILED(D3DXCreateTextureFromFile(pDevice, texNameBg[i], &g_pTextureBg[i])))
		{
			//MessageBox(NULL, "bg", "�G���[", MB_OK);
		}
	}

	//�f�o�C�X�擾
	makeVertexBg(pDevice);
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: uninitBg
//�Ԃ�l	: 
//����		: �|���S���I��
//////////////////////////////////////////////////////////////////////////////
void uninitBg ( void )
{
	//�e�N�X�`���C���^�[�t�F�C�X�̉��
	for(int i = 0; i < BG_TYPE_MAX; i++)
	{
		if(g_pTextureBg[i] != NULL)
		{
			g_pTextureBg[i]->Release();
			g_pTextureBg[i] = NULL;
		}
	}

	//���_�o�b�t�@�Ǘ��̉��
	if(g_pVtxBufferBg != NULL)
	{
		g_pVtxBufferBg->Release();
		g_pVtxBufferBg = NULL;
	}
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: updateBg
//�Ԃ�l	: 
//����		: �|���S���X�V
//////////////////////////////////////////////////////////////////////////////
void updateBg ( void )
{
	
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: drawBg
//�Ԃ�l	: 
//����		: �|���S���`��
//////////////////////////////////////////////////////////////////////////////
void drawBg ( void )
{
	//�ϐ��錾
	LPDIRECT3DDEVICE9 pDevice = getDevice();
	
	//�X�g���[���쐬
	pDevice->SetStreamSource(0, g_pVtxBufferBg, 0, sizeof(VERTEX2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	pDevice->SetTexture(0,g_pTextureBg[g_bg.type]);

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
HRESULT makeVertexBg ( LPDIRECT3DDEVICE9 pDevice )
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
			&g_pVtxBufferBg,					//���_�o�b�t�@�Ǘ��C���^�[�t�F�C�X
			NULL
			)
		))
		
	{
		return E_FAIL;
	}

	//���_�o�b�t�@�����b�N���ĉ��z�A�h���X���擾
	g_pVtxBufferBg->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�(2D���W�E�E���)
	setRotBuffer(pVtx, g_bg.conf);

	//�e�N�X�`���ݒ�
	setTexture(pVtx, g_bg.tex);

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
	g_pVtxBufferBg->Unlock();

	return S_OK;
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: setBgType
//�Ԃ�l	: 
//����		: �w�i�摜�ݒ�
//////////////////////////////////////////////////////////////////////////////
void	setBgType	( BG_TYPE type )
{
	g_bg.type = type;
}