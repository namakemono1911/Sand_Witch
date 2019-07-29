/*****************************************************************************
hp.cpp
Aythor	: ���@��
Data	: 2016_06_17
=============================================================================
Updata

*****************************************************************************/
//////////////////////////////////////////////////////////////////////////////
//�w�b�_�[�t�@�C���C���N���[�h
//////////////////////////////////////////////////////////////////////////////
#include "main.h"
#include "hp.h"
#include "polygon.h"
#include "input.h"
#include <math.h>

//////////////////////////////////////////////////////////////////////////////
//�萔��`
//////////////////////////////////////////////////////////////////////////////
#define HP_TEXTURENAME "data/TEXTURE/kobeni0.png"	//�ǂݍ��ރe�N�X�`���t�@�C��
#define MAX_NUM		(20)	//�\���ł���ő吔

#define MARGIN		(D3DXVECTOR2(44, 10))	//�]��
#define COUNT_TIME	(10)	//�o�[������n�߂鎞��

#define HP_POS_X	(0)		//�|���S���̕\���ʒuX
#define HP_POS_Y	(0)		//�|���S���̕\���ʒuY

#define HP_WIDTH	(500.0f)		//�|���S���̕�
#define HP_HEIGHT	(50.0f)		//�|���S���̍���

#define	LIFE		(500)		//����HP

//////////////////////////////////////////////////////////////////////////////
//�\���̒�`
//////////////////////////////////////////////////////////////////////////////
typedef struct
{
	POLYGON			conf;		//�|���S���ݒ�
	D3DXCOLOR		color;		//�o�[�̐F
	float			barPos[2];	//�o�[�̍��W
	int				time;		//�J�E���g�_�E��
	int				maxHp;		//�ő�HP
	int				hp;			//���݂�HP
	bool			use;		//�g�p�t���O
}HP_BAR;

//////////////////////////////////////////////////////////////////////////////
//�v���g�^�C�v�錾
//////////////////////////////////////////////////////////////////////////////
HRESULT makeVertexHp ( LPDIRECT3DDEVICE9 pDevice );

//////////////////////////////////////////////////////////////////////////////
//�O���[�o���ϐ�
//////////////////////////////////////////////////////////////////////////////
LPDIRECT3DTEXTURE9	g_pTextureHp = NULL;	//�e�N�X�`���C���^�[�t�F�C�X
LPDIRECT3DVERTEXBUFFER9 g_pVtxBufferHp = NULL;	//���_�o�b�t�@�Ǘ��C���^�[�t�F�C�X

D3DXVECTOR2 g_posHp;	//�|���S���̒��S���W
float g_rotHp;			//�|���S���̉�]��
float g_lengthHp;		//�|���S���̑Ίp���̒���
float g_angleHp;		//�|���S���̑Ίp���̊p�x

int		hp	=	LIFE;
int		time;
float	hpBarSize;
HP_BAR	hpBar[6];

int		g_numHpbar;		//���ݎg�p����Ă���HP�o�[�̐�

//////////////////////////////////////////////////////////////////////////////
//�֐���	: initHp
//�Ԃ�l	: 
//����		: �|���S��������
//////////////////////////////////////////////////////////////////////////////
void initHp ( void )
{
	//�ϐ��錾
	LPDIRECT3DDEVICE9 pDevice = getDevice();	//�f�o�C�X�|�C���^�擾
	int		i;	//loop

	//�\���̏�����
	for (int i = 0; i < MAX_NUM; i++)
	{
		hpBar[i].use = false;
	}

	//�e�N�X�`���̓ǂݍ���
	/*
	if(FAILED(D3DXCreateTextureFromFile(pDevice, HP_TEXTURENAME, &g_pTextureHp)))
	{
		MessageBox(NULL, "�G���[", "�G���[", MB_OK);
	}*/

	//�f�o�C�X�擾
	makeVertexHp(pDevice);
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: uninitHp
//�Ԃ�l	: 
//����		: �|���S���I��
//////////////////////////////////////////////////////////////////////////////
void uninitHp ( void )
{
	//�e�N�X�`���C���^�[�t�F�C�X�̉��
	if(g_pTextureHp != NULL)
	{
		g_pTextureHp->Release();
		g_pTextureHp = NULL;
	}

	//���_�o�b�t�@�Ǘ��̉��
	if(g_pVtxBufferHp != NULL)
	{
		g_pVtxBufferHp->Release();
		g_pVtxBufferHp = NULL;
	}
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: updateHp
//�Ԃ�l	: 
//����		: �|���S���X�V
//////////////////////////////////////////////////////////////////////////////
void updateHp ( void )
{
	//�ϐ��錾
	float	len;		//�o�[�̒���

	//HP�o�[�X�V
	if(GetKeyboardPress(DIK_A))
	{
		hpBar[0].hp--;
		hpBar[0].time =	0;
		if(hpBar[0].hp < 0)
		{
			hpBar[0].hp =	0;
		}
	}
	
	if(GetKeyboardPress(DIK_D))
	{
		hpBar[0].hp--;
		hpBar[0].time =	0;

		if(hpBar[0].hp > LIFE)
		{
			hpBar[0].hp =	LIFE;
		}
	}

	//�g���Ă���HP�o�[�X�V
	for (int i = 0, j = 0; j < MAX_NUM; i++)
	{
		if (hpBar[i].use == true)
		{
			//�p�[�Z���g�̌v�Z
			float	percent;
			len = hpBar[i].conf.size.x - MARGIN.x * 2;

			percent = ((float)hpBar[i].maxHp - (float)hpBar[i].hp) / (float)hpBar[i].maxHp;
			hpBar[i].barPos[0] = (hpBar[i].conf.pos.x - hpBar[i].conf.size.x * 0.5f) - len * (1 - percent);

			//���Ԍv�Z
			if(time <= COUNT_TIME)
			{
				time++;
			}

			if(time >= COUNT_TIME)
			{
				if(hpBar[i].barPos[1] > hpBar[i].barPos[0])
				{
					hpBar[i].barPos[1] -= 2.f;
				}
			}

			j++;
		}
	}

	//���_�o�b�t�@�����b�N���ĉ��z�A�h���X���擾
	VERTEX2D *pVtx = NULL;
	g_pVtxBufferHp->Lock(0, 0, (void**)&pVtx, 0);
	
	for (int i = 0, j = 0; j < g_numHpbar; i++)
	{
		if (hpBar[i].use == true)
		{
			//�|���S���̒��_���W�ݒ�
			setBuffer(pVtx, hpBar[i].conf);

			//�e�N�X�`�����_���W�̐ݒ�(0~1)
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	
			pVtx	+=	4;

			//�c��̗̑�
			pVtx[0].pos = D3DXVECTOR3(
				hpBar[i].conf.pos.x - len * 0.5f,
				hpBar[i].conf.pos.y + hpBar[i].conf.size.y * 0.5f - MARGIN.y, 
				0.f);

			pVtx[1].pos = D3DXVECTOR3(
				hpBar[i].conf.pos.x - len * 0.5f,
				hpBar[i].conf.pos.y - hpBar[i].conf.size.y * 0.5f + MARGIN.y,
				0.f);

			pVtx[2].pos = D3DXVECTOR3(
				hpBar[i].barPos[0],
				hpBar[i].conf.pos.y + hpBar[i].conf.size.y * 0.5f - MARGIN.y,
				0.f);

			pVtx[3].pos = D3DXVECTOR3(
				hpBar[i].barPos[0],
				hpBar[i].conf.pos.y - hpBar[i].conf.size.y * 0.5f + MARGIN.y,
				0.f);

			pVtx[0].color = pVtx[1].color =
			pVtx[2].color = pVtx[3].color = hpBar[i].color;

			//�k�ރ|���S��
			pVtx[4].pos = D3DXVECTOR3(
				hpBar[i].barPos[0],
				hpBar[i].conf.pos.y - hpBar[i].conf.size.y * 0.5f + MARGIN.y,
				0.f);

			pVtx[5].pos = D3DXVECTOR3(
				hpBar[i].barPos[0],
				hpBar[i].conf.pos.y + hpBar[i].conf.size.y * 0.5f - MARGIN.y,
				0.f);

			//�����Ă�����
			pVtx[6].pos = D3DXVECTOR3(
				hpBar[i].barPos[0],
				hpBar[i].conf.pos.y + hpBar[i].conf.size.y * 0.5f - MARGIN.y,
				0.f);

			pVtx[7].pos = D3DXVECTOR3(
				hpBar[i].barPos[0],
				hpBar[i].conf.pos.y - hpBar[i].conf.size.y * 0.5f + MARGIN.y,
				0.f);

			pVtx[8].pos = D3DXVECTOR3(
				hpBar[i].barPos[1],
				hpBar[i].conf.pos.y + hpBar[i].conf.size.y * 0.5f - MARGIN.y,
				0.f);

			pVtx[9].pos = D3DXVECTOR3(
				hpBar[i].barPos[1],
				hpBar[i].conf.pos.y - hpBar[i].conf.size.y * 0.5f + MARGIN.y,
				0.f);

			pVtx[6].color = pVtx[7].color =
			pVtx[8].color = pVtx[9].color = D3DCOLOR_RGBA(192, 255, 255, 255);

			//�k�ރ|���S��


			j++;
		}
	}
	//�o�b�t�@�A�����b�N
	g_pVtxBufferHp->Unlock();
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: drawHp
//�Ԃ�l	: 
//����		: �|���S���`��
//////////////////////////////////////////////////////////////////////////////
void drawHp ( void )
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
	pDevice->SetStreamSource(0, g_pVtxBufferHp, 0, sizeof(VERTEX2D));

	//�e�N�X�`���ǂݍ���
	//pDevice->SetTexture(0,g_pTextureHp);

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
//�֐���	: setHpbar
//�Ԃ�l	: 
//����		: HP�o�[�ݒ�
//////////////////////////////////////////////////////////////////////////////
int setHpbar(int maxHp, D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR color)
{
	for (int i = 0; i < MAX_NUM; i++)
	{
		if (hpBar[i].use == false)
		{
			hpBar[i].maxHp = maxHp;			//�ő�̗�
			hpBar[i].hp = maxHp;			//���݂̗̑�
			hpBar[i].conf.pos = pos;		//���S���W
			hpBar[i].conf.size = size;		//�T�C�Y
			hpBar[i].color = color;			//�o�[�̐F
			hpBar[i].time = 0;

			g_numHpbar++;
			return i;
		}
	}

	return -1;
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: makeVertexHp
//�Ԃ�l	: 
//����		: ���_�쐬
//////////////////////////////////////////////////////////////////////////////
void releaseHpbar(int num)
{
	if (hpBar[num].use == true)
	{
		hpBar[num].use = false;
		g_numHpbar--;
	}
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: makeVertexHp
//�Ԃ�l	: 
//����		: ���_�쐬
//////////////////////////////////////////////////////////////////////////////
HRESULT makeVertexHp ( LPDIRECT3DDEVICE9 pDevice )
{
	//�ϐ��錾
	VERTEX2D *pVtx = NULL;;		//���z�A�h���X�p�|�C���^
	int		i;	//loop	

	//���_�o�b�t�@�̐ݒ�
	if(FAILED(pDevice->CreateVertexBuffer
			(
			sizeof(VERTEX2D) * (NUM_VERTEX + 6 * 2) * MAX_NUM,		//���_�o�b�t�@�T�C�Y
			D3DUSAGE_WRITEONLY,					//���_�o�b�t�@�̎g�p���@
			FVF_VERTEX_2D,						//
			D3DPOOL_MANAGED,					//�������Ǘ����@
			&g_pVtxBufferHp,					//���_�o�b�t�@�Ǘ��C���^�[�t�F�C�X
			NULL
			)
		))
		
	{
		return E_FAIL;
	}

	//���_�o�b�t�@�����b�N���ĉ��z�A�h���X���擾
	g_pVtxBufferHp->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < (NUM_VERTEX + 6 * 2) * MAX_NUM; i++)
	{
		//rhw�̐ݒ�(�K��1.0f)
		pVtx[0].rhw = 1.0f;

		//���_�J���[�̐ݒ�(0~155�̐����l)
		pVtx[0].color = D3DCOLOR_RGBA(255, 255, 255, 255);

		pVtx++;
	}

	//���̂�����A�[�����b�N��
	g_pVtxBufferHp->Unlock();

	return S_OK;
}