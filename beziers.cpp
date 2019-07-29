/*****************************************************************************
beziers.cpp
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
#include "beziers.h"
#include "input.h"

//////////////////////////////////////////////////////////////////////////////
//�萔��`
//////////////////////////////////////////////////////////////////////////////
#define TEXTURE_NAME	"data/TEXTURE/white.png"	//�e�N�X�`���t�@�C���l�[��

#define BEZIERS_POS_X	(SCREEN_WIDTH * 0.5f)		//�|���S���̕\���ʒuX
#define BEZIERS_POS_Y	(SCREEN_HEIGHT * 0.5f)		//�|���S���̕\���ʒuY

#define BEZIERS_WIDTH	(SCREEN_WIDTH)				//�|���S���̕�
#define BEZIERS_HEIGHT	(SCREEN_HEIGHT)				//�|���S���̍���
#define BEZIERS_RATE	(0.0001f)					//�t�F�[�h�W��

#define	MAX_BEZIERS	(100.f)							//�Ȑ��̒��_��

//////////////////////////////////////////////////////////////////////////////
//�\���̒�`
//////////////////////////////////////////////////////////////////////////////
typedef struct
{
	POLYGON		conf;		//�|���S���̃R���t�B�O
	float		width;		//����
	D3DXVECTOR3	impact[4];	//�e���_
}BEZIERS;

BEZIERS	beziers;
//////////////////////////////////////////////////////////////////////////////
//�v���g�^�C�v�錾
//////////////////////////////////////////////////////////////////////////////
HRESULT makeVertexBeziers ( LPDIRECT3DDEVICE9 pDevice );
D3DXVECTOR3	bezieFormula	( float	t );

//////////////////////////////////////////////////////////////////////////////
//�O���[�o���ϐ�
//////////////////////////////////////////////////////////////////////////////
LPDIRECT3DTEXTURE9		g_pTextureBeziers = NULL;		//�e�N�X�`���C���^�[�t�F�C�X
LPDIRECT3DVERTEXBUFFER9 g_pVtxBufferBeziers = NULL;	//���_�o�b�t�@�Ǘ��C���^�[�t�F�C�X

//////////////////////////////////////////////////////////////////////////////
//�֐���	: initBeziers
//�Ԃ�l	: 
//����		: �|���S��������
//////////////////////////////////////////////////////////////////////////////
void initBeziers ( void )
{
	//�ϐ��錾
	LPDIRECT3DDEVICE9 pDevice = getDevice();	//�f�o�C�X�|�C���^�擾

	//�\���̏�����
	beziers.impact[0] = D3DXVECTOR3(50, BEZIERS_POS_Y, 0.f);
	beziers.impact[1] = D3DXVECTOR3(SCREEN_WIDTH * 0.3f, SCREEN_HEIGHT, 0.f);
	beziers.impact[2] = D3DXVECTOR3(SCREEN_WIDTH * 0.6f, 0.f, 0.f);
	beziers.impact[3] = D3DXVECTOR3(SCREEN_WIDTH * 0.8f, BEZIERS_POS_Y, 0.f);
	beziers.width = 3;

	//�e�N�X�`���̓ǂݍ���
	/*if(FAILED(D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME, &g_pTextureBeziers)))
	{
		MessageBox(NULL, "beziers", "�G���[", MB_OK);
	}*/

	//�f�o�C�X�擾
	makeVertexBeziers(pDevice);
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: uninitBeziers
//�Ԃ�l	: 
//����		: �|���S���I��
//////////////////////////////////////////////////////////////////////////////
void uninitBeziers ( void )
{
	//�e�N�X�`���C���^�[�t�F�C�X�̉��
	if(g_pTextureBeziers != NULL)
	{
		g_pTextureBeziers->Release();
		g_pTextureBeziers = NULL;
	}

	//���_�o�b�t�@�Ǘ��̉��
	if(g_pVtxBufferBeziers != NULL)
	{
		g_pVtxBufferBeziers->Release();
		g_pVtxBufferBeziers = NULL;
	}
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: updateBeziers
//�Ԃ�l	: 
//����		: �|���S���X�V
//////////////////////////////////////////////////////////////////////////////
void updateBeziers ( void )
{
	
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: drawBeziers
//�Ԃ�l	: 
//����		: �|���S���`��
//////////////////////////////////////////////////////////////////////////////
void drawBeziers ( void )
{
	//�ϐ��錾
	int		i;			//loop
	LPDIRECT3DDEVICE9 pDevice = getDevice();

	//�`��ݒ�����Z�����ɕύX
	addDevice();

	//�X�g���[���쐬
	pDevice->SetStreamSource(0, g_pVtxBufferBeziers, 0, sizeof(VERTEX2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	pDevice->SetTexture(0,g_pTextureBeziers);

	//�`��
	for(i = 0; i < MAX_BEZIERS; i++)
	{
		pDevice->DrawPrimitive
			(
			D3DPT_TRIANGLESTRIP,			//�|���S���̎��
			NUM_VERTEX * i,				//�I�t�Z�b�g(���_��)
			NUM_POLYGON						//�|���S���̐�
			);
	}

	//�`��ݒ����Z�����ɕύX
	initDevice();
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: makeVertexBeziers
//�Ԃ�l	: 
//����		: ���_�쐬
//////////////////////////////////////////////////////////////////////////////
HRESULT makeVertexBeziers ( LPDIRECT3DDEVICE9 pDevice )
{
	//�ϐ��錾
	float		i;		//loop
	VERTEX2D *pVtx = NULL;;		//���z�A�h���X�p�|�C���^

	//���_�o�b�t�@�̐ݒ�
	if(FAILED(pDevice->CreateVertexBuffer
			(
			(UINT)(sizeof(VERTEX2D) * NUM_VERTEXLIST * MAX_BEZIERS),		//���_�o�b�t�@�T�C�Y
			D3DUSAGE_WRITEONLY,					//���_�o�b�t�@�̎g�p���@
			FVF_VERTEX_2D,						//
			D3DPOOL_MANAGED,					//�������Ǘ����@
			&g_pVtxBufferBeziers,				//���_�o�b�t�@�Ǘ��C���^�[�t�F�C�X
			NULL
			)
		))
		
	{
		return E_FAIL;
	}

	//���_�o�b�t�@�����b�N���ĉ��z�A�h���X���擾
	g_pVtxBufferBeziers->Lock(0, 0, (void**)&pVtx, 0);

	for(i = 0; i <= 0.9f; i += 1 / MAX_BEZIERS)
	{
		//���_���W�̐ݒ�(2D���W�E�E���)
		pVtx[0].pos = bezieFormula(i);
		pVtx[1].pos = bezieFormula(i + 1 / MAX_BEZIERS);
		pVtx[2].pos = D3DXVECTOR3(bezieFormula(i).x, bezieFormula(i).y + beziers.width, 0.f);
		pVtx[3].pos = D3DXVECTOR3(bezieFormula(i + 1 / MAX_BEZIERS).x, bezieFormula(i + 1 / MAX_BEZIERS).y + beziers.width, 0.f);

		//rhw�̐ݒ�(�K��1.0f)
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�(0~155�̐����l)
		pVtx[0].color = D3DCOLOR_RGBA(100, 100, 192, 255);
		pVtx[1].color = D3DCOLOR_RGBA(100, 100, 192, 255);
		pVtx[2].color = D3DCOLOR_RGBA(100, 100, 192, 255);
		pVtx[3].color = D3DCOLOR_RGBA(100, 100, 192, 255);
	
		//�e�N�X�`�����_���W�̐ݒ�(0~1)
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		//�|�C���^�ړ�
		pVtx += NUM_VERTEX;
	}

	//���̂�����A�[�����b�N��
	g_pVtxBufferBeziers->Unlock();

	return S_OK;
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: bezieFormula
//�Ԃ�l	: 
//����		: ���_�̕�����
//////////////////////////////////////////////////////////////////////////////
D3DXVECTOR3	bezieFormula	( float	t )
{
	return D3DXVECTOR3(
		beziers.impact[0].x * ((1 - t) * (1 - t) * (1 - t)) + beziers.impact[1].x * 3 * t *(( 1 - t ) * ( 1 - t )) + beziers.impact[2].x * 3 * (t * t) * ( 1 - t ) + beziers.impact[3].x * (t * t * t),
		beziers.impact[0].y * ((1 - t) * (1 - t) * (1 - t)) + beziers.impact[1].y * 3 * t *(( 1 - t ) * ( 1 - t )) + beziers.impact[2].y * 3 * (t * t) * ( 1 - t ) + beziers.impact[3].y * (t * t * t),
		0.f);
}