/*****************************************************************************
particle.cpp
Aythor	: ���@��
Data	: 2016_07_05
=============================================================================
Updata

*****************************************************************************/
//////////////////////////////////////////////////////////////////////////////
//�w�b�_�[�t�@�C���C���N���[�h
//////////////////////////////////////////////////////////////////////////////
#include "main.h"
#include "polygon.h"
#include "particle.h"
#include "input.h"
#include <math.h>

//////////////////////////////////////////////////////////////////////////////
//�萔��`
//////////////////////////////////////////////////////////////////////////////
#define TEXTURE_NAME	"data/TEXTURE/effect000.jpg"	//�e�N�X�`���t�@�C���l�[��

#define PARTICLE_POS_X	(SCREEN_WIDTH * 0.5f)		//�|���S���̕\���ʒuX
#define PARTICLE_POS_Y	(SCREEN_HEIGHT * 0.5f)		//�|���S���̕\���ʒuY

#define PARTICLE_WIDTH	(SCREEN_WIDTH)				//�|���S���̕�
#define PARTICLE_HEIGHT	(SCREEN_HEIGHT)				//�|���S���̍���
#define PARTICLE_RATE	(0.0001f)					//�t�F�[�h�W��

#define	MAX_PARTICLE	(1024)						//�p�[�e�B�N���̍ő��

//////////////////////////////////////////////////////////////////////////////
//�\���̒�`
//////////////////////////////////////////////////////////////////////////////
typedef struct
{
	ROTPOLYGON	conf;		//��]�|���S���̊e��ݒ�
	D3DXCOLOR	color;		//�|���S���̐F
	float		angle;		//���ˊp�x
	float		life;		//����
	float		move;		//�ړ���
	bool		use;		//true�Ŏg�p����Ă���
}PARTICLE;

//typedef enum
//{
//	MODE_ANGLE = 0,		//�p�x����
//	MODE_LIFE,			//��������
//	MODE_MOVE,			//�����x����
//	MODE_MAX,			//���[�h�̑���
//	MODE_NONE			//����NULL
//}OPERATION;				//�p�[�e�B�N���̑��샂�[�h

PARTICLE	particle[MAX_PARTICLE];
//////////////////////////////////////////////////////////////////////////////
//�v���g�^�C�v�錾
//////////////////////////////////////////////////////////////////////////////
HRESULT makeVertexParticle ( LPDIRECT3DDEVICE9 pDevice );
void	setConf	( int num );

//////////////////////////////////////////////////////////////////////////////
//�O���[�o���ϐ�
//////////////////////////////////////////////////////////////////////////////
LPDIRECT3DTEXTURE9		g_pTextureParticle = NULL;		//�e�N�X�`���C���^�[�t�F�C�X
LPDIRECT3DVERTEXBUFFER9 g_pVtxBufferParticle = NULL;	//���_�o�b�t�@�Ǘ��C���^�[�t�F�C�X

D3DXVECTOR3	g_pos;		//�����ʒu
D3DXCOLOR	g_color;	//�|���S���F
float		g_size;		//�T�C�Y
float		g_angle;	//���ˊp�x
float		g_move;		//�ړ���
float		g_life;		//����

//////////////////////////////////////////////////////////////////////////////
//�֐���	: initParticle
//�Ԃ�l	: 
//����		: �|���S��������
//////////////////////////////////////////////////////////////////////////////
void initParticle ( void )
{
	//�ϐ��錾
	int		i;		//loop
	LPDIRECT3DDEVICE9 pDevice = getDevice();	//�f�o�C�X�|�C���^�擾
	
	//�O���[�o���ϐ�������
	g_pos = D3DXVECTOR3(PARTICLE_POS_X, PARTICLE_POS_Y, 0.f);
	//g_color = 0xf9861e;
	g_color = D3DXCOLOR(0.9f, 0.5f, 0.03f, 0.5f);
	g_size = 30.f;
	g_angle = 6.28f;
	g_move = 2;
	g_life = 0.001f;

	//�\���̏�����
	for(i = 0; i < MAX_PARTICLE; i++)
	{
		//�g�p����
		particle[i].use = false;
	}

	//�e�N�X�`���̓ǂݍ���
	if(FAILED(D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME, &g_pTextureParticle)))
	{
		MessageBox(NULL, "particle", "�G���[", MB_OK);
	}

	//�f�o�C�X�擾
	makeVertexParticle(pDevice);
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: uninitParticle
//�Ԃ�l	: 
//����		: �|���S���I��
//////////////////////////////////////////////////////////////////////////////
void uninitParticle ( void )
{
	//�e�N�X�`���C���^�[�t�F�C�X�̉��
	if(g_pTextureParticle != NULL)
	{
		g_pTextureParticle->Release();
		g_pTextureParticle = NULL;
	}

	//���_�o�b�t�@�Ǘ��̉��
	if(g_pVtxBufferParticle != NULL)
	{
		g_pVtxBufferParticle->Release();
		g_pVtxBufferParticle = NULL;
	}
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: updateParticle
//�Ԃ�l	: 
//����		: �|���S���X�V
//////////////////////////////////////////////////////////////////////////////
void updateParticle ( void )
{
	//�ϐ��錾
	int		i;		//loop
	VERTEX2D	*pVtx;

	//�V�������q�𔭐�������
	for(i = 0; i < MAX_PARTICLE; i++)
	{
		if(particle[i].use == false)
		{
			particle[i].use = true;
			setConf(i);
			break;
		}
	}

	//���ɏo�Ă��闱�q�X�V
	for(i = 0; i < MAX_PARTICLE; i++)
	{
		if(particle[i].use == true)
		{
			//���W�X�V
			particle[i].conf.conf.pos = D3DXVECTOR3(
				particle[i].move * cos(particle[i].angle) + particle[i].conf.conf.pos.x,
				particle[i].move * sin(particle[i].angle) + particle[i].conf.conf.pos.y,
				0.f);

			//�F�X�V
			particle[i].color.a -= particle[i].life;

			if(particle[i].color.a < 0.f)
			{
				particle[i].color.a = 0.f;
				particle[i].use = false;
			}
		}
	}

	//=============================
	// �L�[����
	//=============================


	//--------------------------------------------------------------------------
	// �`��ʒu�m��
	//--------------------------------------------------------------------------
	//���_�o�b�t�@�����b�N���ĉ��z�A�h���X���擾
	g_pVtxBufferParticle->Lock(0, 0, (void**)&pVtx, 0);

	//���W�ݒ�
	for(i = 0; i < MAX_PARTICLE; i++)
	{
		//�g���Ă��闱�q�����o�^
		if(particle[i].use == true)
		{
			//�o�b�t�@�ɍ��W�o�^
			setRotBuffer(pVtx, particle[i].conf);

			//�k�ރ|���S���ݒ�
			if(i < MAX_PARTICLE - 1)
			{
				pVtx[4].pos = D3DXVECTOR3(
					cos(particle[i].conf.rot + particle[i].angle) * particle[i].conf.length + particle[i].conf.conf.pos.x,
					sin(particle[i].conf.rot + particle[i].angle) * particle[i].conf.length + particle[i].conf.conf.pos.y,
					0.0f);

				pVtx[5].pos = D3DXVECTOR3(
					-cos(particle[i + 1].conf.rot + particle[i + 1].angle) * particle[i + 1].conf.length + particle[i + 1].conf.conf.pos.x,
					-sin(particle[i + 1].conf.rot + particle[i + 1].angle) * particle[i + 1].conf.length + particle[i + 1].conf.conf.pos.y,
					0.0f);
			}

			pVtx[0].color = particle[i].color;
			pVtx[1].color = particle[i].color;
			pVtx[2].color = particle[i].color;
			pVtx[3].color = particle[i].color;

			//�|�C���^�ړ�
			pVtx += NUM_VERTEXLIST;
		}

	}

	//�o�b�t�@�A�����b�N
	g_pVtxBufferParticle->Unlock();
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: drawParticle
//�Ԃ�l	: 
//����		: �|���S���`��
//////////////////////////////////////////////////////////////////////////////
void drawParticle ( void )
{
	//�ϐ��錾
	int		i;			//loop
	int		numVertex;	//���_��
	LPDIRECT3DDEVICE9 pDevice = getDevice();

	//�`��ݒ�����Z�����ɕύX
	addDevice();

	//�X�g���[���쐬
	pDevice->SetStreamSource(0, g_pVtxBufferParticle, 0, sizeof(VERTEX2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	pDevice->SetTexture(0,g_pTextureParticle);

	//�|���S���̕`��
	for(i = 0, numVertex = 0; i < MAX_PARTICLE; i++)
	{
		//�g���Ă��闱�q�����`��
		if(particle[i].use == true)
		{
			pDevice->DrawPrimitive
				(
				D3DPT_TRIANGLESTRIP,			//�|���S���̎��
				numVertex * NUM_VERTEXLIST,		//�I�t�Z�b�g(���_��)
				NUM_POLYGON						//�|���S���̐�
				);

			//���_�����Z
			numVertex++;
		}
	}

	//�`��ݒ����Z�����ɕύX
	initDevice();
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: makeVertexParticle
//�Ԃ�l	: 
//����		: ���_�쐬
//////////////////////////////////////////////////////////////////////////////
HRESULT makeVertexParticle ( LPDIRECT3DDEVICE9 pDevice )
{
	//�ϐ��錾
	int		i;		//loop
	VERTEX2D *pVtx = NULL;;		//���z�A�h���X�p�|�C���^

	//���_�o�b�t�@�̐ݒ�
	if(FAILED(pDevice->CreateVertexBuffer
			(
			sizeof(VERTEX2D) * NUM_VERTEXLIST * MAX_PARTICLE,		//���_�o�b�t�@�T�C�Y
			D3DUSAGE_WRITEONLY,					//���_�o�b�t�@�̎g�p���@
			FVF_VERTEX_2D,						//
			D3DPOOL_MANAGED,					//�������Ǘ����@
			&g_pVtxBufferParticle,				//���_�o�b�t�@�Ǘ��C���^�[�t�F�C�X
			NULL
			)
		))
		
	{
		return E_FAIL;
	}

	//���_�o�b�t�@�����b�N���ĉ��z�A�h���X���擾
	g_pVtxBufferParticle->Lock(0, 0, (void**)&pVtx, 0);

	for(i = 0; i < MAX_PARTICLE; i++)
	{
		//���_���W�̐ݒ�(2D���W�E�E���)
		pVtx[0].pos = D3DXVECTOR3(PARTICLE_POS_X, PARTICLE_POS_Y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(PARTICLE_WIDTH, PARTICLE_POS_Y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(PARTICLE_POS_X, PARTICLE_HEIGHT, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(PARTICLE_WIDTH, PARTICLE_HEIGHT, 0.0f);

		//rhw�̐ݒ�(�K��1.0f)
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�(0~155�̐����l)
		pVtx[0].color = g_color;
		pVtx[1].color = g_color;
		pVtx[2].color = g_color;
		pVtx[3].color = g_color;
	
		//�e�N�X�`�����_���W�̐ݒ�(0~1)
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		//�|�C���^�ړ�
		pVtx += NUM_VERTEX;
	}

	//���̂�����A�[�����b�N��
	g_pVtxBufferParticle->Unlock();

	return S_OK;
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: setConf
//�Ԃ�l	: 
//����		: ���_�쐬
//////////////////////////////////////////////////////////////////////////////
void	setConf	( int num )
{
	//�ϐ��錾
	float	size;	//�T�C�Y�̃��[�N
	float	color;	//�J���[�̃��[�N

	//�������T�C�Y�ɐݒ�
	size = (float)(rand() % 20);
	size -= g_size;

	//�e�평����
	initRotPolygon(&particle[num].conf, 
		g_pos,
		D3DXVECTOR3(size, size, 0.f));

	//�F�ݒ�
	particle[num].color = g_color;
	color = (float)(rand() % 50);
	color /= 100;
	particle[num].color.a += color; 

	//�p�x�ݒ�
	particle[num].angle = (float)(rand() % (int)(g_angle * 100) - 314);
	particle[num].angle /= 100;

	//�����ݒ�
	particle[num].life = (float)(rand() % 10 + 1);
	particle[num].life /= 10000.f;
	particle[num].life += g_life;

	//�ړ���
	particle[num].move = (float)(rand() % 5);
	particle[num].move -= g_move;
}