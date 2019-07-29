/*****************************************************************************
bulletEffect.cpp
Aythor	: ���@��
Data	: 2017_06_09
=============================================================================
Updata

*****************************************************************************/
//////////////////////////////////////////////////////////////////////////////
//�w�b�_�[�t�@�C���C���N���[�h
//////////////////////////////////////////////////////////////////////////////
#include "main.h"
#include "polygon.h"
#include "bulletEffect.h"

//////////////////////////////////////////////////////////////////////////////
//�萔��`
//////////////////////////////////////////////////////////////////////////////
#define MAX			(50)		//�G�t�F�N�g�ő吔
#define TEX_MOVE	(0.01f)		//�e�N�X�`���X�N���[���̑��x
#define TEX_HEIGHT	(1.f / 3.f)	//�e�N�X�`���̕�	
#define TEX_PER_SIZE	(1.f / 808.f)	//�e�N�X�`���T�C�Y�̊���

#define ANIME_FRAME	(15)		//�A�j���[�V��������t���[����

//////////////////////////////////////////////////////////////////////////////
//�\���̒�`
//////////////////////////////////////////////////////////////////////////////
typedef struct
{
	POLYGON			conf;		//�|���S���̐ݒ�
	TEXTURE			tex;		//�e�N�X�`���ݒ�
	BULLET_EFFECT_TYPE	type;	//�G�t�F�N�g�̎��
	int				anime;		//�A�j���[�V����
	bool			use;		//�g�p�t���O
}BULLET_EFFECT;

//////////////////////////////////////////////////////////////////////////////
//�v���g�^�C�v�錾
//////////////////////////////////////////////////////////////////////////////
HRESULT makeVertexBulletEffect(LPDIRECT3DDEVICE9 pDevice);

//////////////////////////////////////////////////////////////////////////////
//�O���[�o���ϐ�
//////////////////////////////////////////////////////////////////////////////
LPDIRECT3DTEXTURE9	g_pTextureBulletEffect[BULLET_EFFECT_MAX] = { NULL };	//�e�N�X�`���C���^�[�t�F�C�X
LPDIRECT3DVERTEXBUFFER9 g_pVtxBufferBulletEffect = NULL;	//���_�o�b�t�@�Ǘ��C���^�[�t�F�C�X

BULLET_EFFECT	g_bulletEffect[MAX];		//�w�i�\����
UINT			g_numBulletEffect = 0;		//�g���Ă���G�t�F�N�g��	
const char	*texNameBulletEffect[BULLET_EFFECT_MAX] =
{
	"data/TEXTURE/GAME/BULLET/mmm.png",
};

//////////////////////////////////////////////////////////////////////////////
//�֐���	: initBulletEffect
//�Ԃ�l	: 
//����		: �|���S��������
//////////////////////////////////////////////////////////////////////////////
void initBulletEffect(void)
{
	//�ϐ��錾
	LPDIRECT3DDEVICE9 pDevice = getDevice();	//�f�o�C�X�|�C���^�擾

	//�\���̏�����
	for(int i = 0; i < MAX; i++)
	{
		g_bulletEffect[i].tex.size.y = TEX_HEIGHT;
		g_bulletEffect[i].use = false;
	}
	g_numBulletEffect = 0;

	//�e�N�X�`���̓ǂݍ���
	for (int i = 0; i < BULLET_EFFECT_MAX; i++)
	{
		if (FAILED(D3DXCreateTextureFromFile(pDevice, texNameBulletEffect[i], &g_pTextureBulletEffect[i])))
		{
			MessageBox(NULL, "bg", "�G���[", MB_OK);
		}
	}

	//�f�o�C�X�擾
	makeVertexBulletEffect(pDevice);
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: uninitBulletEffect
//�Ԃ�l	: 
//����		: �|���S���I��
//////////////////////////////////////////////////////////////////////////////
void uninitBulletEffect(void)
{
	//�e�N�X�`���C���^�[�t�F�C�X�̉��
	for (int i = 0; i < BULLET_EFFECT_MAX; i++)
	{
		if (g_pTextureBulletEffect[i] != NULL)
		{
			g_pTextureBulletEffect[i]->Release();
			g_pTextureBulletEffect[i] = NULL;
		}
	}

	//���_�o�b�t�@�Ǘ��̉��
	if (g_pVtxBufferBulletEffect != NULL)
	{
		g_pVtxBufferBulletEffect->Release();
		g_pVtxBufferBulletEffect = NULL;
	}
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: updateBulletEffect
//�Ԃ�l	: 
//����		: �|���S���X�V
//////////////////////////////////////////////////////////////////////////////
void updateBulletEffect(void)
{
	//�ϐ��錾
	VERTEX2D	*pVtx;

	g_pVtxBufferBulletEffect->Lock(0, 0, (void**)&pVtx, 0);

	for(UINT i = 0, j = 0; j < g_numBulletEffect; i++)
	{
		if (g_bulletEffect[i].use == true)
		{
			//���W
			setBuffer(pVtx, g_bulletEffect[i].conf);

			//�e�N�X�`��
			g_bulletEffect[i].anime = (g_bulletEffect[i].anime + 1) % 60;
			g_bulletEffect[i].tex.pos.x += TEX_MOVE;
			g_bulletEffect[i].tex.size.x += TEX_MOVE;
			if (g_bulletEffect[i].anime % (60 / ANIME_FRAME) == 0)
			{
				g_bulletEffect[i].tex.pos.y += g_bulletEffect[i].tex.size.y;
				//g_bulletEffect[i].tex.size.y = fmod(g_bulletEffect[i].tex.size.y + TEX_HEIGHT, 1.f);
			}
			setTexture(pVtx, g_bulletEffect[i].tex);

			j++;
		}

		pVtx += NUM_VERTEX;
	}

	g_pVtxBufferBulletEffect->Unlock();
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: drawBulletEffect
//�Ԃ�l	: 
//����		: �|���S���`��
//////////////////////////////////////////////////////////////////////////////
void drawBulletEffect(void)
{
	//�ϐ��錾
	LPDIRECT3DDEVICE9 pDevice = getDevice();

	//�X�g���[���쐬
	pDevice->SetStreamSource(0, g_pVtxBufferBulletEffect, 0, sizeof(VERTEX2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for(UINT i = 0, j = 0; j < g_numBulletEffect; i++)
	{
		if (g_bulletEffect[i].use == true)
		{
			pDevice->SetTexture(0, g_pTextureBulletEffect[g_bulletEffect[i].type]);

			//�|���S���̕`��
			pDevice->DrawPrimitive
			(
				D3DPT_TRIANGLESTRIP,	//�|���S���̎��
				NUM_VERTEX * i,			//�I�t�Z�b�g(���_��)
				NUM_POLYGON				//�|���S���̐�
			);

			j++;
		}
	}
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: makeVertexBulletEffect
//�Ԃ�l	: 
//����		: ���_�쐬
//////////////////////////////////////////////////////////////////////////////
HRESULT makeVertexBulletEffect(LPDIRECT3DDEVICE9 pDevice)
{
	//�ϐ��錾
	VERTEX2D *pVtx = NULL;;		//���z�A�h���X�p�|�C���^

								//���_�o�b�t�@�̐ݒ�
	if (FAILED(pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX2D) * NUM_VERTEX * MAX,	//���_�o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,					//���_�o�b�t�@�̎g�p���@
		FVF_VERTEX_2D,						//
		D3DPOOL_MANAGED,					//�������Ǘ����@
		&g_pVtxBufferBulletEffect,				//���_�o�b�t�@�Ǘ��C���^�[�t�F�C�X
		NULL
	)
	))

	{
		return E_FAIL;
	}

	//���_�o�b�t�@�����b�N���ĉ��z�A�h���X���擾
	g_pVtxBufferBulletEffect->Lock(0, 0, (void**)&pVtx, 0);

	for(int i = 0; i < MAX; i++)
	{
		//rhw�̐ݒ�(�K��1.0f)
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�(0~155�̐����l)
		pVtx[0].color = D3DCOLOR_RGBA(255, 255, 255, 192);
		pVtx[1].color = D3DCOLOR_RGBA(255, 255, 255, 192);
		pVtx[2].color = D3DCOLOR_RGBA(255, 255, 255, 192);
		pVtx[3].color = D3DCOLOR_RGBA(255, 255, 255, 192);

		pVtx += NUM_VERTEX;
	}

	//���̂�����A�[�����b�N��
	g_pVtxBufferBulletEffect->Unlock();

	return S_OK;
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: setBulletEffect
//�Ԃ�l	: 
//����		: �G�t�F�N�g����
//////////////////////////////////////////////////////////////////////////////
int	setBulletEffect(D3DXVECTOR3 pos, D3DXVECTOR3 size, BULLET_EFFECT_TYPE type)
{
	for (int i = 0; i < MAX; i ++)
	{
		if (g_bulletEffect[i].use == false)
		{
			g_bulletEffect[i].conf.pos = pos;
			g_bulletEffect[i].conf.size = size;
			g_bulletEffect[i].tex.pos = D3DXVECTOR2(0.f, 0.f);
			g_bulletEffect[i].tex.size.x = TEX_PER_SIZE * size.x;
			g_bulletEffect[i].type = type;
			g_bulletEffect[i].anime = 0;
			g_bulletEffect[i].use = true;

			g_numBulletEffect++;
			return i;
		}
	}

	return -1;
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: ReleaseBulletEffect
//�Ԃ�l	: 
//����		: �t���O�����[�X
//////////////////////////////////////////////////////////////////////////////
void releaseBulletEffect(int id)
{
	if(id >= 0)
	{
		g_bulletEffect[id].use = false;
		g_numBulletEffect--;
	}
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: setBulletEffectPos
//�Ԃ�l	: 
//����		: �G�t�F�N�g�̍��W�ݒ�
//////////////////////////////////////////////////////////////////////////////
void setBulletEffectPos(int id, D3DXVECTOR3 pos)
{
	if (id >= 0)
	{
		g_bulletEffect[id].conf.pos = pos;
	}
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: setBulletEffectSize
//�Ԃ�l	: 
//����		: �G�t�F�N�g�̍��W�ݒ�
//////////////////////////////////////////////////////////////////////////////
void setBulletEffectSize(int id, D3DXVECTOR3 size)
{
	if (id >= 0)
	{
		g_bulletEffect[id].conf.size = size;
		g_bulletEffect[id].tex.size.x = TEX_PER_SIZE * size.x;
	}
}