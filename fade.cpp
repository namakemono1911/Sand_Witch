/*****************************************************************************
fade.cpp
Aythor	: ���@��
Data	: 2016_09_28
=============================================================================
Updata

*****************************************************************************/
//////////////////////////////////////////////////////////////////////////////
//�w�b�_�[�t�@�C���C���N���[�h
//////////////////////////////////////////////////////////////////////////////
#include "main.h"
#include "polygon.h"
#include "fade.h"

//////////////////////////////////////////////////////////////////////////////
//�萔��`
//////////////////////////////////////////////////////////////////////////////
#define FADE_POS_X		(SCREEN_WIDTH * 0.5f)	//�|���S���̕\���ʒuX
#define FADE_POS_Y		(SCREEN_HEIGHT * 0.5f)	//�|���S���̕\���ʒuY

#define FADE_WIDTH		(SCREEN_WIDTH)			//�|���S���̕�
#define FADE_HEIGHT		(SCREEN_HEIGHT)			//�|���S���̍���

#define SPEED_MAX		(30)					//�ō����x
#define ROT_MAX			(0.0005)				//�ō��p�x

#define NUM_HITBOX		(3)						//�q�b�g�{�b�N�X�̐�

#define TEXTURE_WIDTH	(1.0f)					//�e�N�X�`������̕�
#define TEXTURE_HEIGHT	(1.0f)					//�e�N�X�`������̍���

//////////////////////////////////////////////////////////////////////////////
//�\���̒�`
//////////////////////////////////////////////////////////////////////////////
typedef struct
{
	ROTPOLYGON	conf;		//�|���S���̊e��ݒ�
	TEXTURE		tex;		//�e�N�X�`���ݒ�
	D3DXCOLOR	color;		//�F
	float		time;		//�t�F�[�h�̎���
	bool		action;		//true�œ����Ă�
	MODE		nextMode;	//�t�F�[�h��̃��[�h
}FADE;

FADE fade;

//////////////////////////////////////////////////////////////////////////////
//�v���g�^�C�v�錾
//////////////////////////////////////////////////////////////////////////////
HRESULT makeVertexFade ( LPDIRECT3DDEVICE9 pDevice );
void	opeFade			( void );
void	updateFadeIn	( void );
void	updateFadeOut	( void );

//////////////////////////////////////////////////////////////////////////////
//�O���[�o���ϐ�
//////////////////////////////////////////////////////////////////////////////
LPDIRECT3DTEXTURE9		g_pTextureFade = NULL;			//�e�N�X�`���C���^�[�t�F�C�X
LPDIRECT3DVERTEXBUFFER9	g_pVtxBufferFade = NULL;		//���_�o�b�t�@�Ǘ��C���^�[�t�F�C�X

FADE_MODE		g_fadeMode = FADE_MODE_NONE;			//�t�F�[�h���[�h

//////////////////////////////////////////////////////////////////////////////
// �ϐ���	: initFade
// �Ԃ�l	:
// ����		: �f�o�C�X�̏�����
//////////////////////////////////////////////////////////////////////////////
void	initFade	( void )
{	
	//�ϐ��錾

	LPDIRECT3DDEVICE9 pDevice = getDevice();	//�f�o�C�X�|�C���^�擾

	//�\���̏�����
	initRotPolygon(&fade.conf,
		D3DXVECTOR3(FADE_POS_X, FADE_POS_Y, 0.f),
		D3DXVECTOR3(FADE_WIDTH, FADE_HEIGHT, 0.f));

	initTexture(&fade.tex,
		D3DXVECTOR2(0.f, 0.f),
		D3DXVECTOR2(TEXTURE_WIDTH, TEXTURE_HEIGHT));

	fade.action = false;

	//�f�o�C�X�擾
	makeVertexFade(pDevice);
}

//////////////////////////////////////////////////////////////////////////////
// �ϐ���	: uninitFade
// �Ԃ�l	:
// ����		: �f�o�C�X�̏I��
//////////////////////////////////////////////////////////////////////////////
void uninitFade ( void )
{
	//�e�N�X�`���C���^�[�t�F�C�X�̉��
	if(g_pTextureFade != NULL)
	{
		g_pTextureFade->Release();
		g_pTextureFade = NULL;
	}

	//���_�o�b�t�@�Ǘ��̉��
	if(g_pVtxBufferFade != NULL)
	{
		g_pVtxBufferFade->Release();
		g_pVtxBufferFade = NULL;
	}
}

//////////////////////////////////////////////////////////////////////////////
// �ϐ���	: updateFade
// �Ԃ�l	:
// ����		: �X�V
//////////////////////////////////////////////////////////////////////////////
void	updateFade	( void )
{
	//�ϐ��錾
	VERTEX2D	*pVtx;		

	//���[�h���Ə���
	switch(g_fadeMode)
	{
	case FADE_IN:
		{
			updateFadeIn();
			break;
		}

	case FADE_OUT:
		{
			updateFadeOut();
			break;
		}

	case FADE_MODE_NONE:
		{
			return;
		}
	}

	//���_�o�b�t�@�����b�N���ĉ��z�A�h���X���擾
	g_pVtxBufferFade->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�(2D���W�E�E���)
	setRotBuffer(pVtx, fade.conf);

	//���_�J���[�̐ݒ�(0~155�̐����l)
	pVtx[0].color = fade.color;
	pVtx[1].color = fade.color;
	pVtx[2].color = fade.color;
	pVtx[3].color = fade.color;
	
	//�e�N�X�`�����_���W�̐ݒ�(0~1)
	setTexture(pVtx, fade.tex);

	//���̂�����A�[�����b�N��
	g_pVtxBufferFade->Unlock();
}

//////////////////////////////////////////////////////////////////////////////
// �ϐ���	: updateFadeIn
// �Ԃ�l	:
// ����		: �X�V
//////////////////////////////////////////////////////////////////////////////
void	updateFadeIn	( void )
{
	//���ߓx���Z
	fade.color.a -= fade.time;

	if(fade.color.a <= 0.f)
	{
		fade.color.a = 0.f;
		g_fadeMode = FADE_MODE_NONE;
		fade.action = false;
	}
}

//////////////////////////////////////////////////////////////////////////////
// �ϐ���	: updateFadeOut
// �Ԃ�l	:
// ����		: �X�V
//////////////////////////////////////////////////////////////////////////////
void	updateFadeOut	( void )
{
	//���ߓx���Z
	fade.color.a += fade.time;
	
	if(fade.color.a >= 1.f)
	{
		fade.color.a = 1.f;
		g_fadeMode = FADE_MODE_NONE;
		fade.action = false;
		setMode(fade.nextMode);
	}
}

//////////////////////////////////////////////////////////////////////////////
// �ϐ���	: setFade
// �Ԃ�l	:
// ����		: �t�F�[�h�̐ݒ�
//////////////////////////////////////////////////////////////////////////////
void	setFade	( char *texAdd, D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR2 texPos, D3DXVECTOR2 texSize )
{
	//�ϐ��錾
	LPDIRECT3DDEVICE9 pDevice = getDevice();	//�f�o�C�X�|�C���^�擾

	//�e�N�X�`���̓ǂݍ���
	if(texAdd != NULL)
	{
		if(FAILED(D3DXCreateTextureFromFile(pDevice, texAdd, &g_pTextureFade)))
		{
			MessageBox(NULL, "Test", "�G���[", MB_OK);
		}
	}

	//�ϐ����
	initRotPolygon(&fade.conf, pos, size);
	initTexture(&fade.tex, texPos, texSize);
}

//////////////////////////////////////////////////////////////////////////////
// �ϐ���	: startFadeIn
// �Ԃ�l	:
// ����		: �t�F�[�h�̐ݒ�
//////////////////////////////////////////////////////////////////////////////
void	startFadeIn	( int time, D3DXCOLOR color )
{
	if(fade.action == false)
	{
		fade.time = 1.f / (float)time;
		fade.color = color;

		g_fadeMode = FADE_IN;

		fade.action = true;
	}
}

//////////////////////////////////////////////////////////////////////////////
// �ϐ���	: startFadeOut
// �Ԃ�l	:
// ����		: �t�F�[�h�̐ݒ�
//////////////////////////////////////////////////////////////////////////////
void	startFadeOut	( int time, D3DXCOLOR color, MODE nextMode )
{
	if(fade.action == false)
	{
		fade.time = 1.f / (float)time;
		fade.color = color;

		g_fadeMode = FADE_OUT;

		fade.action = true;

		fade.nextMode = nextMode;
	}
}

//////////////////////////////////////////////////////////////////////////////
// �ϐ���	: setFadeMode
// �Ԃ�l	:
// ����		: �t�F�[�h���[�h�r���؂�ւ�
//////////////////////////////////////////////////////////////////////////////
void	setFadeMode	( FADE_MODE mode )
{
	g_fadeMode = mode;
}

//////////////////////////////////////////////////////////////////////////////
// �ϐ���	: drawFade
// �Ԃ�l	:
// ����		: �f�o�C�X�̏�����
//////////////////////////////////////////////////////////////////////////////
void	drawFade	( void )
{
	//�ϐ��錾
	LPDIRECT3DDEVICE9 pDevice = getDevice();

	//�X�g���[���쐬
	pDevice->SetStreamSource(0, g_pVtxBufferFade, 0, sizeof(VERTEX2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0,g_pTextureFade);

	//�|���S���̕`��
	pDevice->DrawPrimitive
		(
		D3DPT_TRIANGLESTRIP,	//�|���S���̎��
		0,						//�I�t�Z�b�g(���_��)
		NUM_POLYGON				//�|���S���̐�
		);
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: makeVertexFade
//�Ԃ�l	: 
//����		: ���_�쐬
//////////////////////////////////////////////////////////////////////////////
HRESULT makeVertexFade ( LPDIRECT3DDEVICE9 pDevice )
{
	//�ϐ��錾
	VERTEX2D	*pVtx = NULL;;		//���z�A�h���X�p�|�C���^

	//���_�o�b�t�@�̐ݒ�
	if(FAILED(pDevice->CreateVertexBuffer
			(
			sizeof(VERTEX2D) * NUM_VERTEX,	//���_�o�b�t�@�T�C�Y
			D3DUSAGE_WRITEONLY,				//���_�o�b�t�@�̎g�p���@
			FVF_VERTEX_2D,					//
			D3DPOOL_MANAGED,				//�������Ǘ����@
			&g_pVtxBufferFade,				//���_�o�b�t�@�Ǘ��C���^�[�t�F�C�X
			NULL
			)
		))
	{
		return E_FAIL;
	}

	//���_�o�b�t�@�����b�N���ĉ��z�A�h���X���擾
	g_pVtxBufferFade->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�(2D���W�E�E���)
	setRotBuffer(pVtx, fade.conf);

	//rhw�̐ݒ�(�K��1.0f)
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�(0~155�̐����l)
	pVtx[0].color = D3DCOLOR_RGBA(255, 255, 255, 0);
	pVtx[1].color = D3DCOLOR_RGBA(255, 255, 255, 0);
	pVtx[2].color = D3DCOLOR_RGBA(255, 255, 255, 0);
	pVtx[3].color = D3DCOLOR_RGBA(255, 255, 255, 0);
	
	//�e�N�X�`�����_���W�̐ݒ�(0~1)
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���̂�����A�[�����b�N��
	g_pVtxBufferFade->Unlock();

	return S_OK;
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: getFadeAction
//�Ԃ�l	: 
//����		: �t�F�[�h�������擾
//////////////////////////////////////////////////////////////////////////////
bool	getFadeAction	( void )
{
	return fade.action;
}