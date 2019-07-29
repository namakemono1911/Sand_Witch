/*****************************************************************************
bossHp.cpp
Aythor	: ���@��
Data	: 2016_06_17
=============================================================================
Updata

*****************************************************************************/
//////////////////////////////////////////////////////////////////////////////
//�w�b�_�[�t�@�C���C���N���[�h
//////////////////////////////////////////////////////////////////////////////
#include "main.h"
#include "bossHp.h"
#include "input.h"
#include <math.h>

//////////////////////////////////////////////////////////////////////////////
//�萔��`
//////////////////////////////////////////////////////////////////////////////
#define BOSS_HP_POS_X	(0)		//�|���S���̕\���ʒuX
#define BOSS_HP_POS_Y	(0)		//�|���S���̕\���ʒuY

#define BOSS_HP_WIDTH	(100.0f)		//�|���S���̕�
#define BOSS_HP_HEIGHT	(30.0f)			//�|���S���̍���

//////////////////////////////////////////////////////////////////////////////
//�\���̒�`
//////////////////////////////////////////////////////////////////////////////
typedef struct
{
	D3DXVECTOR3		pos;	//���W
	D3DXCOLOR		color;	//�o�[�̐F
	bool			use;	//�g�p�t���O
}BOSS_HP_BAR;

//////////////////////////////////////////////////////////////////////////////
//�v���g�^�C�v�錾
//////////////////////////////////////////////////////////////////////////////
HRESULT makeVertexBossHp ( LPDIRECT3DDEVICE9 pDevice );

//////////////////////////////////////////////////////////////////////////////
//�O���[�o���ϐ�
//////////////////////////////////////////////////////////////////////////////
LPDIRECT3DTEXTURE9	g_pTextureBossHp = NULL;	//�e�N�X�`���C���^�[�t�F�C�X
LPDIRECT3DVERTEXBUFFER9 g_pVtxBufferBossHp = NULL;	//���_�o�b�t�@�Ǘ��C���^�[�t�F�C�X

D3DXVECTOR2 g_posBossHp;	//�|���S���̒��S���W
float g_rotBossHp;			//�|���S���̉�]��
float g_lengthBossHp;		//�|���S���̑Ίp���̒���
float g_angleBossHp;		//�|���S���̑Ίp���̊p�x

int		maxBossHp = 0;		//�ő�̗�
int		bossHp = 0;			//���݂̗̑�
int		bossHptime;			//�Q�[�W������J�E���g�_�E��
float	bossHpBarSize;		//�T�C�Y
BOSS_HP_BAR	bossHpBar[6];	//hp�o�[�̐ݒ�
D3DXVECTOR3 centerBossHp;	//HP�o�[�̒��S���W

//////////////////////////////////////////////////////////////////////////////
//�֐���	: initBossHp
//�Ԃ�l	: 
//����		: �|���S��������
//////////////////////////////////////////////////////////////////////////////
void initBossHp( void )
{
	//�ϐ��錾
	LPDIRECT3DDEVICE9 pDevice = getDevice();	//�f�o�C�X�|�C���^�擾
	int		i;	//loop


	//�e�N�X�`���̓ǂݍ���
	/*
	if(FAILED(D3DXCreateTextureFromFile(pDevice, BOSS_HP_TEXTURENAME, &g_pTextureBossHp)))
	{
		MessageBox(NULL, "�G���[", "�G���[", MB_OK);
	}*/

	//�|���S���̍��W
	g_posBossHp = D3DXVECTOR2(BOSS_HP_WIDTH * 0.5f, BOSS_HP_HEIGHT * 0.5f);

	//�|���S���̊p�x
	g_rotBossHp = 0.0f;

	//�Ίp���̒���
	g_lengthBossHp = sqrt(BOSS_HP_WIDTH * BOSS_HP_WIDTH + BOSS_HP_HEIGHT * BOSS_HP_HEIGHT) * 0.5f;

	//�|���S���̑Ίp���̊p�x
	g_angleBossHp = atan2(BOSS_HP_HEIGHT, BOSS_HP_WIDTH);

	//�\���̏�����
	for(i = 0; i < 6; i++)
	{
		bossHpBar[i].pos.y	=	sin(g_rotBossHp + g_angleBossHp) * g_lengthBossHp + g_posBossHp.y - 3;
	}

	//���[
	bossHpBar[0].pos.x	=	-cos(g_rotBossHp + g_angleBossHp) * g_lengthBossHp + g_posBossHp.x + 3;

	//�E�[
	bossHpBar[5].pos.x	=	cos(g_rotBossHp + g_angleBossHp) * g_lengthBossHp + g_posBossHp.x - 3;

	bossHpBar[1].pos	=	bossHpBar[5].pos;
	bossHpBar[2].pos	=	bossHpBar[5].pos;
	bossHpBar[3].pos	=	bossHpBar[5].pos;
	bossHpBar[4].pos	=	bossHpBar[5].pos;

	bossHpBar[0].color	=	D3DXCOLOR(0.5f, 1.f, 0.5f, 1.f);
	bossHpBar[1].color	=	bossHpBar[0].color;

	bossHpBar[2].color	=	D3DXCOLOR(0.9f, 0.8f, 0.3f, 1.f);
	bossHpBar[3].color	=	bossHpBar[2].color;

	bossHpBar[4].color	=	D3DXCOLOR(1.f, 0.f, 0.f, 1.f);
	bossHpBar[5].color	=	bossHpBar[4].color;

	//�f�o�C�X�擾
	makeVertexBossHp(pDevice);
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: uninitBossHp
//�Ԃ�l	: 
//����		: �|���S���I��
//////////////////////////////////////////////////////////////////////////////
void uninitBossHp ( void )
{
	//�e�N�X�`���C���^�[�t�F�C�X�̉��
	if(g_pTextureBossHp != NULL)
	{
		g_pTextureBossHp->Release();
		g_pTextureBossHp = NULL;
	}

	//���_�o�b�t�@�Ǘ��̉��
	if(g_pVtxBufferBossHp != NULL)
	{
		g_pVtxBufferBossHp->Release();
		g_pVtxBufferBossHp = NULL;
	}
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: updateBossHp
//�Ԃ�l	: 
//����		: �|���S���X�V
//////////////////////////////////////////////////////////////////////////////
void updateBossHp ( void )
{
	//�ϐ��錾
	VERTEX2D *pVtx = NULL;
	float topLeftX;		//�|���S���̍�����WX
	float topLeftY;		//�|���S���̍�����WY
	float topRightX;	//�|���S���̉E��X
	float topRightY;	//�|���S���̉E��Y
	float bottomLeftX;	//�|���S���̍������WX
	float bottomLeftY;	//�|���S���̍������WY
	float bottomRightX;	//�|���S���̉E��X
	float bottomRightY;	//�|���S���̉E��Y
	float percent;
	int	 i;

	//�|���S���̍���̍��W
	topLeftX = -cos(g_rotBossHp + g_angleBossHp) * g_lengthBossHp + g_posBossHp.x;
	topLeftY = -sin(g_rotBossHp + g_angleBossHp) * g_lengthBossHp + g_posBossHp.y;

	//�|���S���̉E��
	topRightX = cos(g_rotBossHp - g_angleBossHp) * g_lengthBossHp + g_posBossHp.x;
	topRightY = sin(g_rotBossHp - g_angleBossHp) * g_lengthBossHp + g_posBossHp.y;

	//�|���S���̍���
	bottomLeftX = -cos(g_rotBossHp - g_angleBossHp) * g_lengthBossHp + g_posBossHp.x;
	bottomLeftY = -sin(g_rotBossHp - g_angleBossHp) * g_lengthBossHp + g_posBossHp.y;

	//�|���S���̉E���̍��W
	bottomRightX = cos(g_rotBossHp + g_angleBossHp) * g_lengthBossHp + g_posBossHp.x;
	bottomRightY = sin(g_rotBossHp + g_angleBossHp) * g_lengthBossHp + g_posBossHp.y;

	//�p�[�Z���g�̌v�Z
	percent = ((float)maxBossHp - (float)bossHp) / (float)maxBossHp;
	bossHpBar[1].pos.x	=	(bossHpBar[5].pos.x) * (1 - percent);
	bossHpBar[2].pos	=	bossHpBar[1].pos;

	//���Ԍv�Z
	if(bossHptime <= 24)
	{
		bossHptime++;
	}

	if(bossHptime >= 24)
	{
		if(bossHpBar[3].pos.x > (bossHpBar[5].pos.x) * (1 - percent))
		{
			bossHpBar[3].pos.x -= 2.f;
			bossHpBar[4].pos.x = bossHpBar[3].pos.x;
		}
	}

	//���_�o�b�t�@�����b�N���ĉ��z�A�h���X���擾
	g_pVtxBufferBossHp->Lock(0, 0, (void**)&pVtx, 0);
	
	//�|���S���̒��_���W�ݒ�
	pVtx[0].pos = D3DXVECTOR3(topLeftX + centerBossHp.x, topLeftY + centerBossHp.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(topRightX + centerBossHp.x, topRightY + centerBossHp.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(bottomLeftX + centerBossHp.x, bottomLeftY + centerBossHp.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(bottomRightX + centerBossHp.x, bottomRightY + centerBossHp.y, 0.0f);

	//�e�N�X�`�����_���W�̐ݒ�(0~1)
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	
	pVtx	+=	4;

	for(i = 0; i < 3; i ++)
	{
		pVtx[0].pos	=	D3DXVECTOR3(
			bossHpBar[2 * i].pos.x + centerBossHp.x,
			bossHpBar[2 * i].pos.y + centerBossHp.y,
			0.f);

		pVtx[1].pos	=	D3DXVECTOR3(
			bossHpBar[2 * i].pos.x + centerBossHp.x,
			bossHpBar[2 * i].pos.y - 44 + centerBossHp.y,
			0.f);
		
		pVtx[2].pos	=	D3DXVECTOR3(
			bossHpBar[2 * i + 1].pos.x + centerBossHp.x,
			bossHpBar[2 * i + 1].pos.y + centerBossHp.y,
			0.f);

		pVtx[3].pos	=	D3DXVECTOR3(
			bossHpBar[2 * i + 1].pos.x + centerBossHp.x,
			bossHpBar[2 * i + 1].pos.y - 44 + centerBossHp.y,
			0.f);
		
		pVtx[0].color = bossHpBar[2 * i].color;
		pVtx[1].color = bossHpBar[2 * i].color;
		pVtx[2].color = bossHpBar[2 * i + 1].color;
		pVtx[3].color = bossHpBar[2 * i + 1].color;

		pVtx	+=	4;
	}

	//�o�b�t�@�A�����b�N
	g_pVtxBufferBossHp->Unlock();
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: drawBossHp
//�Ԃ�l	: 
//����		: �|���S���`��
//////////////////////////////////////////////////////////////////////////////
void drawBossHp ( void )
{
	//�ϐ��錾
	LPDIRECT3DDEVICE9 pDevice = getDevice();

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	pDevice->SetRenderState(D3DRS_DITHERENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//�T���v���[�X�e�[�g�̐ݒ�
	pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	pDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);

	//�X�g���[���쐬
	pDevice->SetStreamSource(0, g_pVtxBufferBossHp, 0, sizeof(VERTEX2D));

	//�e�N�X�`���ǂݍ���
	pDevice->SetTexture(0, NULL);

	//�|���S���̕`��
	pDevice->DrawPrimitive
		(
		D3DPT_TRIANGLESTRIP,	//�|���S���̎��
		0,						//�I�t�Z�b�g(���_��)
		NUM_POLYGON				//�|���S���̐�
		);
	
	pDevice->DrawPrimitive
		(
		D3DPT_TRIANGLESTRIP,	//�|���S���̎��
		4,						//�I�t�Z�b�g(���_��)
		NUM_POLYGON * 8				//�|���S���̐�
		);
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: setBossHp
//�Ԃ�l	: 
//����		: �{�X�̗̑͐ݒ�
//////////////////////////////////////////////////////////////////////////////
void setBossHp(int hp)
{
	bossHp = hp;
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: setBossHpPos
//�Ԃ�l	: 
//����		: �{�X��HP�o�[�̍��W�ݒ�
//////////////////////////////////////////////////////////////////////////////
void setBossHpPos(D3DXVECTOR3 pos)
{
	centerBossHp = pos;
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: setMaxBossHp
//�Ԃ�l	: 
//����		: �{�X��HP�o�[�̍ő�l�ݒ�
//////////////////////////////////////////////////////////////////////////////
void setMaxBossHp(int hp)
{
	maxBossHp = hp;
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: makeVertexBossHp
//�Ԃ�l	: 
//����		: ���_�쐬
//////////////////////////////////////////////////////////////////////////////
HRESULT makeVertexBossHp ( LPDIRECT3DDEVICE9 pDevice )
{
	//�ϐ��錾
	VERTEX2D *pVtx = NULL;;		//���z�A�h���X�p�|�C���^
	int		i;	//loop	

	//���_�o�b�t�@�̐ݒ�
	if(FAILED(pDevice->CreateVertexBuffer
			(
			sizeof(VERTEX2D) * (NUM_VERTEX + 6 * 2),		//���_�o�b�t�@�T�C�Y
			D3DUSAGE_WRITEONLY,					//���_�o�b�t�@�̎g�p���@
			FVF_VERTEX_2D,						//
			D3DPOOL_MANAGED,					//�������Ǘ����@
			&g_pVtxBufferBossHp,				//���_�o�b�t�@�Ǘ��C���^�[�t�F�C�X
			NULL
			)
		))
		
	{
		return E_FAIL;
	}

	//���_�o�b�t�@�����b�N���ĉ��z�A�h���X���擾
	g_pVtxBufferBossHp->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�(2D���W�E�E���)
	pVtx[0].pos = D3DXVECTOR3(BOSS_HP_POS_X, BOSS_HP_POS_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(BOSS_HP_WIDTH, BOSS_HP_POS_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(BOSS_HP_POS_X, BOSS_HP_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(BOSS_HP_WIDTH, BOSS_HP_HEIGHT, 0.0f);

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

	pVtx	+=	4;

	for(i = 0; i < 3; i ++)
	{
		pVtx[0].pos	=	D3DXVECTOR3(
			bossHpBar[i].pos.x,
			bossHpBar[i].pos.y,
			0.f);

		pVtx[1].pos	=	D3DXVECTOR3(
			bossHpBar[i].pos.x,
			bossHpBar[i].pos.y - 44,
			0.f);

		pVtx[2].pos	-	D3DXVECTOR3(
			bossHpBar[i + 1].pos.x,
			bossHpBar[i + 1].pos.y,
			0.f);

		pVtx[3].pos	-	D3DXVECTOR3(
			bossHpBar[i + 1].pos.x,
			bossHpBar[i + 1].pos.y - 44,
			0.f);
		
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		
		pVtx[0].color = bossHpBar[i].color;
		pVtx[1].color = bossHpBar[i].color;
		pVtx[2].color = bossHpBar[i + 1].color;
		pVtx[3].color = bossHpBar[i + 1].color;

		pVtx	+=	4;
	}

	//���̂�����A�[�����b�N��
	g_pVtxBufferBossHp->Unlock();

	return S_OK;
}