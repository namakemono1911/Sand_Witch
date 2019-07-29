/*****************************************************************************
bulletUI.cpp
Aythor	: ���@��
Data	: 2017_05_21
=============================================================================
Updata

*****************************************************************************/
//////////////////////////////////////////////////////////////////////////////
//�w�b�_�[�t�@�C���C���N���[�h
//////////////////////////////////////////////////////////////////////////////
#include "main.h"
#include "polygon.h"
#include "bullet.h"
#include "bulletUI.h"

//////////////////////////////////////////////////////////////////////////////
//�\���̒�`
//////////////////////////////////////////////////////////////////////////////
#define MAX_BULLET_UI		(2)	//�eUI�̍ő吔
#define NUM_VTX_BULLET_UI	(12)	//���UI�Ɏg�����_��

//////////////////////////////////////////////////////////////////////////////
//�\���̒�`
//////////////////////////////////////////////////////////////////////////////
typedef struct
{
	POLYGON				conf;		//�|���S���̐ݒ�
	float				maxWidth;	//�ő�T�C�Y
	POLYGON				coolTime;	//�N�[���^�C���\��
	D3DXCOLOR			setColor;	//�ݒ肷�钸�_�F
	D3DXCOLOR			color;		//���_�F
	BULLET_UI_TYPE		type;		//UI�̎��
	UINT				cntTime;	//�N�[���^�C��
	bool				ct;			//�N�[���^�C���t���O
	bool				use;		//�g�p�t���O
}BULLET_UI;

//////////////////////////////////////////////////////////////////////////////
//�v���g�^�C�v�錾
//////////////////////////////////////////////////////////////////////////////
HRESULT	makeVertexBulletUI	( LPDIRECT3DDEVICE9 pDevice );
void	setBulletUIVtx	( const unsigned int num );

//////////////////////////////////////////////////////////////////////////////
//�O���[�o���ϐ�
//////////////////////////////////////////////////////////////////////////////
LPDIRECT3DVERTEXBUFFER9	g_pVtxBufferBulletUI = NULL;
LPDIRECT3DTEXTURE9		g_pTextureBulletUI[BULLET_UI_MAX] = {NULL};

BULLET_UI	bulletUI[MAX_BULLET_UI];		//�eUI�̏��i�[
const char	*g_texNameBulletUI[] =			//�e�N�X�`���̎��
{
	"data/TEXTURE/magicCursor.png",
	"data/TEXTURE/white.png",
};

//////////////////////////////////////////////////////////////////////////////
//�֐���	: initBulletUI
//�Ԃ�l	: 
//����		: �eUI������
//////////////////////////////////////////////////////////////////////////////
HRESULT	initBulletUI	( void )
{
	//�ϐ��錾
	LPDIRECT3DDEVICE9 pDevice = getDevice();	//�f�o�C�X�|�C���^�擾

	//�\���̏�����
	for(int i = 0; i < MAX_BULLET_UI; i++)
	{
		bulletUI[i].cntTime = 0;
		bulletUI[i].use = false;
		bulletUI[i].ct = false;
	}
	
	for(int i = 0; i < 1; i++)
	{
		//�e�N�X�`���̓ǂݍ���
		if(FAILED(D3DXCreateTextureFromFile(pDevice, g_texNameBulletUI[i], &g_pTextureBulletUI[i])))
		{
			MessageBox(NULL, "bullet", "�G���[", MB_OK);
			return E_FAIL;
		}
	}

	//�f�o�C�X�擾
	makeVertexBulletUI(pDevice);

	return S_OK;
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: uninitBulletUI
//�Ԃ�l	: 
//����		: �eUI������
//////////////////////////////////////////////////////////////////////////////
void	uninitBulletUI	( void )
{
	//���_�����
	if(g_pVtxBufferBulletUI != NULL)
	{
		g_pVtxBufferBulletUI->Release();
		g_pVtxBufferBulletUI = NULL;
	}

	//�e�N�X�`�������
	for(int i = 0; i <BULLET_UI_MAX; i++)
	{
		if(g_pTextureBulletUI[i] != NULL)
		{
			g_pTextureBulletUI[i]->Release();
			g_pTextureBulletUI[i] = NULL;
		}
	}
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: updateBulletUI
//�Ԃ�l	: 
//����		: �eUI������
//////////////////////////////////////////////////////////////////////////////
void	updateBulletUI	( void )
{
	//�ϐ��錾
	VERTEX2D	*pVtx;

	g_pVtxBufferBulletUI->Lock(0, 0, (void**)&pVtx, 0);

	for(int i = 0; i < MAX_BULLET_UI; i++)
	{
		if(bulletUI[i].use == true)
		{
			//�N�[���^�C����Ԃ̏���
			if(bulletUI[i].ct == true)
			{
				bulletUI[i].coolTime.size.x += bulletUI[i].maxWidth * (1.f / (float)bulletUI[i].cntTime);
				bulletUI[i].coolTime.pos.x = (bulletUI[i].conf.pos.x - bulletUI[i].maxWidth * 0.5f) + bulletUI[i].coolTime.size.x * 0.5f;
				bulletUI[i].cntTime--;

				if(bulletUI[i].coolTime.size.x >= bulletUI[i].maxWidth || bulletUI[i].cntTime <= 0)
				{
					bulletUI[i].coolTime.size.x = bulletUI[i].maxWidth;
					bulletUI[i].coolTime.pos.x = bulletUI[i].conf.pos.x;
					bulletUI[i].cntTime = 0;
					bulletUI[i].ct = false;
				}
			}

			//�N�[���^�C����������
			pVtx[6 + i * NUM_VTX_BULLET_UI].color = 
			pVtx[7 + i * NUM_VTX_BULLET_UI].color = 
			pVtx[8 + i * NUM_VTX_BULLET_UI].color = 
			pVtx[9 + i * NUM_VTX_BULLET_UI].color =
			pVtx[10 + i * NUM_VTX_BULLET_UI].color =
			pVtx[11 + i * NUM_VTX_BULLET_UI].color =
			bulletUI[i].color;

			//�|���S��
			setListBuffer(&pVtx[6 + i * NUM_VTX_BULLET_UI], bulletUI[i].coolTime);
		}
	}

	g_pVtxBufferBulletUI->Unlock();
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: drawBulletUI
//�Ԃ�l	: 
//����		: �eUI������
//////////////////////////////////////////////////////////////////////////////
void	drawBulletUI	( void )
{
	//�ϐ��錾
	LPDIRECT3DDEVICE9 pDevice = getDevice();

	//�X�g���[���쐬
	pDevice->SetStreamSource(0, g_pVtxBufferBulletUI, 0, sizeof(VERTEX2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�|���S���̕`��
	for(int i = 0; i < MAX_BULLET_UI; i++)
	{
		if(bulletUI[i].use == true)
		{
			//����̓}�[�N�̕��I����̓N�[���^�C���̕����I
			for(int j = 0; j < 2; j++)
			{
				if(j % 2 == 0)
				{
					//�e�N�X�`���ǂݍ���
					pDevice->SetTexture(0, g_pTextureBulletUI[bulletUI[i].type]);
				}
				else
				{
					//�����̔���
					pDevice->SetTexture(0, NULL);
				}

				pDevice->DrawPrimitive
					(
					D3DPT_TRIANGLELIST,	//�|���S���̎��
					NUM_VTX_BULLET_UI * i + 6 * j,	//�I�t�Z�b�g(���_��)
					2						//�|���S���̐�
					);
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: makeVertexBulletUI
//�Ԃ�l	: 
//����		: �eUI������
//////////////////////////////////////////////////////////////////////////////
HRESULT	makeVertexBulletUI	( LPDIRECT3DDEVICE9 pDevice )
{
	//�ϐ��錾
	VERTEX2D *pVtx = NULL;;		//���z�A�h���X�p�|�C���^
	int		i;		//loop

	//���_�o�b�t�@�̐ݒ�
	if(FAILED(pDevice->CreateVertexBuffer
			(
			sizeof(VERTEX2D) * NUM_VTX_BULLET_UI * MAX_BULLET_UI,		//���_�o�b�t�@�T�C�Y
			D3DUSAGE_WRITEONLY,					//���_�o�b�t�@�̎g�p���@
			FVF_VERTEX_2D,						//
			D3DPOOL_MANAGED,					//�������Ǘ����@
			&g_pVtxBufferBulletUI,				//���_�o�b�t�@�Ǘ��C���^�[�t�F�C�X
			NULL
			)
		))
		
	{
		return E_FAIL;
	}

	g_pVtxBufferBulletUI->Lock(0, 0, (void**)&pVtx, 0);

	for(i = 0; i < NUM_VTX_BULLET_UI * MAX_BULLET_UI; i++)
	{
		//rhw�̐ݒ�(�K��1.0f)
		pVtx->rhw = 1.f;

		pVtx++;
	}

	g_pVtxBufferBulletUI->Unlock();

	return S_OK;
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: setBulletUI
//�Ԃ�l	: 
//����		: �eUI�ݒ�
//////////////////////////////////////////////////////////////////////////////
int	setBulletUI	( const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXCOLOR color )
{
	//���g�p�̍\���̒T��
	for(int i = 0; i < MAX_BULLET_UI; i++)
	{
		if(bulletUI[i].use == false)
		{
			//��]�|���S���ɕK�v�ȏ��ݒ�
			bulletUI[i].conf.pos = pos;
			bulletUI[i].conf.size = size;
			
			bulletUI[i].coolTime.pos = pos;
			bulletUI[i].coolTime.size = D3DXVECTOR3(0.f, size.y - 10.f, 0.f);

			bulletUI[i].maxWidth = size.x - 65.2f;

			bulletUI[i].color = D3DXCOLOR(0.f, 0.f, 0.f, 0.f);
			bulletUI[i].setColor = color;
			bulletUI[i].use = true;

			//���_���ݒ�
			setBulletUIVtx(i);

			return i;
		}
	}

	return -1;
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: setBulletUIVtx
//�Ԃ�l	: 
//����		: �eUI���_���ݒ�
//////////////////////////////////////////////////////////////////////////////
void	setBulletUIVtx	( const unsigned int num )
{
	//�ϐ��錾
	VERTEX2D	*pVtx;

	g_pVtxBufferBulletUI->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += NUM_VTX_BULLET_UI * num;

	//�A�C�R��
	pVtx[0].color = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].color = pVtx[2].color = pVtx[3].color = 
	pVtx[4].color = pVtx[5].color = D3DCOLOR_RGBA(255, 255, 255, 255);

	pVtx[0].tex = D3DXVECTOR2(0.f, 0.f);
	pVtx[1].tex = D3DXVECTOR2(1.f, 0.f);
	pVtx[2].tex = D3DXVECTOR2(0.f, 1.f);
	pVtx[3].tex = D3DXVECTOR2(1.f, 0.f);
	pVtx[4].tex = D3DXVECTOR2(1.f, 1.f);
	pVtx[5].tex = D3DXVECTOR2(0.f, 1.f);

	setListBuffer(pVtx, bulletUI[num].conf);

	pVtx += 6;
	/*
	//�k�ރ|���S��
	pVtx[0].pos = D3DXVECTOR3(
		bulletUI[num].conf.pos.x + (bulletUI[num].conf.size.x * 0.5f),
		bulletUI[num].conf.pos.y + (bulletUI[num].conf.size.y * 0.5f),
		0.f);
	
	pVtx[1].pos = D3DXVECTOR3(
		bulletUI[num].coolTime.pos.x - (bulletUI[num].conf.size.x * 0.5f),
		bulletUI[num].coolTime.pos.y - (bulletUI[num].conf.size.y * 0.5f),
		0.f);

	pVtx += 2;*/

	//�N�[���^�C����������
	pVtx[0].color = pVtx[1].color = pVtx[2].color = pVtx[3].color = 
	pVtx[4].color = pVtx[5].color = bulletUI[num].setColor;

	pVtx[0].tex = D3DXVECTOR2(0.f, 0.f);
	pVtx[1].tex = D3DXVECTOR2(0.f, 0.f);
	pVtx[2].tex = D3DXVECTOR2(0.f, 0.f);
	pVtx[3].tex = D3DXVECTOR2(0.f, 0.f);
	pVtx[4].tex = D3DXVECTOR2(0.f, 0.f);
	pVtx[5].tex = D3DXVECTOR2(0.f, 0.f);
	
	setListBuffer(pVtx, bulletUI[num].coolTime);

	g_pVtxBufferBulletUI->Unlock();
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: setBulletUICoolTime
//�Ԃ�l	: 
//����		: �eUI�N�[���^�C��
//////////////////////////////////////////////////////////////////////////////
void	setBulletUICoolTime	( const UINT num, const UINT coolTime )
{
	//�ϐ��錾
	VERTEX2D	*pVtx;

	bulletUI[num].coolTime.size.x = 0.f;
	bulletUI[num].color = bulletUI[num].setColor;
	bulletUI[num].coolTime.pos.x = bulletUI[num].conf.pos.x - bulletUI[num].maxWidth * 0.5f;
	bulletUI[num].cntTime = coolTime;

	g_pVtxBufferBulletUI->Lock(0, 0, (void**)&pVtx, 0);

	//�|�C���^�ړ�
	pVtx += NUM_VTX_BULLET_UI * num + 6;

	setBuffer(pVtx, bulletUI[num].coolTime);

	pVtx[0].color = pVtx[1].color = pVtx[2].color = pVtx[3].color = bulletUI[num].color;

	g_pVtxBufferBulletUI->Unlock();

	bulletUI[num].ct = true;
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: getBulletCoolTime
//�Ԃ�l	: 
//����		: �N�[���^�C���擾
//////////////////////////////////////////////////////////////////////////////
int	getBulletCoolTime	(const UINT num)
{
	return bulletUI[num].cntTime;
}