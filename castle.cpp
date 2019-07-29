//============================================
//  castle�֐�  (castle.cpp)
//
//  Author  Information
//  ���O  �Έ�  �Y��
//  �쐬��   2017�N04��21��
//  �C����   �N����
//  �C�����e:
//
//
//============================================

//============================================
//
//  �C���N���[�h�t�@�C��
//
//============================================
#include "castle.h"
#include "game.h"
#include "sound.h"

//============================================
//
//  �}�N����`
//
//============================================
#define CASTLE_TEX_NAME	"data/TEXTURE/GAME/CASTLE/castle01.png"	// �e�N�X�`����

#define CASTLE_HP 100	// �ϋv��

//============================================
//
//  �O���[�o���ϐ�
//
//============================================
//LP�̓|�C���^�[!!
LPDIRECT3DTEXTURE9 g_pTextureCastle = NULL;//Notes�̒���e�N�X�`���A�e�N�X�`���C���^�[�t�F�[�X

/*���_�o�b�t�@�Ǘ��p*/
LPDIRECT3DVERTEXBUFFER9 g_pVtxBufferCastle = NULL;//�|�C���^�[!!&������

/*��\����*/
CASTLE g_aCastle[CASTLE_NUM];

//============================================
//
//  �v���g�^�C�v�錾
//
//============================================
HRESULT MakeVertexCastle(LPDIRECT3DDEVICE9 pDevice);

//============================================
//
//  ���O  InitCastle�֐�
//  ����   int nStage
//  �߂�l void
//  ����   ��̏�����
//
//============================================
void InitCastle(int nStage)
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = getDevice();


	// ��\���̂̏�����

	for(int i = 0 ; i < CASTLE_NUM ; i++)
	{
		g_aCastle[i].bUse = true;
		g_aCastle[i].fPos = D3DXVECTOR3(CASTLE_POSX , CASTLE_POSY , 0.0f);
		g_aCastle[i].fSize = D3DXVECTOR2(CASTLE_WIDTH , CASTLE_HEIGHT);
		g_aCastle[i].fUV = D3DXVECTOR2(0.0f , 0.0f);
		g_aCastle[i].nHp = CASTLE_HP;
	} // EO for

	//���_�쐬
	if(FAILED(MakeVertexCastle(pDevice)))
	{
		return;
	} // EO if

	// �e�N�X�`���擾
	if(FAILED(D3DXCreateTextureFromFile( pDevice , CASTLE_TEX_NAME , &g_pTextureCastle )))
	{
		MessageBox(NULL , "��e�N�X�`�����擾�ł��܂���ł���" , "ERROR" , MB_OK);
	} // EO if

} // EO InitCastle

//============================================
//
//  ���O  UninitCastle�֐�
//  ����   void
//  �߂�l void
//  ����   ��̏I��
//
//============================================
void UninitCastle(void)
{
	// �C���^�[�t�F�[�X�̉��
	SAFE_RELEASE(g_pTextureCastle);
	SAFE_RELEASE(g_pVtxBufferCastle);

} // EO UninitCastle

//============================================
//
//  ���O  UpdateCastle�֐�
//  ����   void
//  �߂�l void
//  ����   ��̍X�V
//
//============================================
void UpdateCastle(void)
{
	//���_�o�b�t�@
	VERTEX2D* pVtx;
	//���_�o�b�t�@�����b�N���āA���z�A�h���X���擾����
	g_pVtxBufferCastle -> Lock(0,0,(void**)&pVtx,0);

	if(g_aCastle[0].nHp >= 50)
	{
		pVtx[0].tex = D3DXVECTOR2( 0.0f , 0.0f );
		pVtx[1].tex = D3DXVECTOR2( 0.25f , 0.0f );
		pVtx[2].tex = D3DXVECTOR2( 0.0f , 1.0f );
		pVtx[3].tex = D3DXVECTOR2( 0.25f , 1.0f );
	}
	else if(g_aCastle[0].nHp < 50 && g_aCastle[0].nHp >= 30)
	{
		pVtx[0].tex = D3DXVECTOR2( 0.25f , 0.0f );
		pVtx[1].tex = D3DXVECTOR2( 0.5f , 0.0f );
		pVtx[2].tex = D3DXVECTOR2( 0.25f , 1.0f );
		pVtx[3].tex = D3DXVECTOR2( 0.5f , 1.0f );
	}
	else if(g_aCastle[0].nHp < 30 && g_aCastle[0].nHp > 0)
	{
		pVtx[0].tex = D3DXVECTOR2( 0.5f , 0.0f );
		pVtx[1].tex = D3DXVECTOR2( 0.75f , 0.0f );
		pVtx[2].tex = D3DXVECTOR2( 0.5f , 1.0f );
		pVtx[3].tex = D3DXVECTOR2( 0.75f , 1.0f );
	}
	else
	{
		pVtx[0].tex = D3DXVECTOR2( 0.75f , 0.0f );
		pVtx[1].tex = D3DXVECTOR2( 1.00f , 0.0f );
		pVtx[2].tex = D3DXVECTOR2( 0.75f , 1.0f );
		pVtx[3].tex = D3DXVECTOR2( 1.00f , 1.0f );
	}

	g_pVtxBufferCastle -> Unlock();

} // EO UpdateCastle

//============================================
//
//  ���O  DrawCastle�֐�
//  ����   void
//  �߂�l void
//  ����   ��̕`��
//
//============================================
void DrawCastle(void)
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = getDevice();

	//�p�C�v���C���̐ݒ�
	pDevice -> SetStreamSource(0,//�X�g���[���ԍ�(���{������)
						g_pVtxBufferCastle ,//�f�[�^�̂���ꏊ(�擪�A�h���X)
						0,//�I�t�Z�b�g(�P�ʃo�C�g)�A�f�[�^�̂ǂ̕ӂ��玝���Ă��邩,0�͐擪
						sizeof(VERTEX2D) );//�X�g���C�h��(��̒P�ʂ̑傫��)

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice -> SetFVF( FVF_VERTEX_2D | D3DFVF_TEX1 );

	for(int nCntNotes = 0 ; nCntNotes < CASTLE_NUM ; nCntNotes++ )
	{
		if(g_aCastle[nCntNotes].bUse == false)
		{
			int i = 0;
		}
		if(g_aCastle[nCntNotes].bUse == true)
		{
			pDevice->SetTexture(0  ,g_pTextureCastle);
			//�v���~�e�B�u�̕`��
			pDevice -> DrawPrimitive(D3DPT_TRIANGLESTRIP,//�v���~�e�B�u�̎��
				nCntNotes * 4 ,//�I�t�Z�b�g(���_��)�����_�ڂ���Ƃ邩
				NUM_POLYGON );//�������_�����Ă���΂����̂��A�v���~�e�B�u�̖������������Q���B�p�C�v���C���͐��ꗬ���ɂȂ��Ă��邩��B
		} // EO if
	} // EO fro

} // EO DrawCastle

//============================================
//
//  ���O  MakeVertexCastle�֐�
//  ����	LPDIRECT3DDEVICE9 pDevice
//  �߂�l  void
//  ����  ���_�̍쐬
//
//============================================
HRESULT MakeVertexCastle(LPDIRECT3DDEVICE9 pDevice)
{
	//���_�o�b�t�@�쐬
	if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX2D) * NUM_VERTEX,D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,D3DPOOL_MANAGED,&g_pVtxBufferCastle,NULL)))
	{
		MessageBox(NULL , "���_�o�b�t�@�̍쐬�Ɏ��s���܂���" , "ERROR" , MB_OK);
		return E_FAIL;
	} // EO if


	//���_�o�b�t�@
	VERTEX2D* pVtx;
	//���_�o�b�t�@�����b�N���āA���z�A�h���X���擾����
	g_pVtxBufferCastle -> Lock(0,0,(void**)&pVtx,0);

	for(int nCntNotes = 0 ; nCntNotes < CASTLE_NUM ; nCntNotes++)
	{
		pVtx[0 + 4 * nCntNotes].pos = D3DXVECTOR3(g_aCastle[nCntNotes].fPos.x , g_aCastle[nCntNotes].fPos.y , 0.0f);
		pVtx[1 + 4 * nCntNotes].pos = D3DXVECTOR3(g_aCastle[nCntNotes].fPos.x + CASTLE_WIDTH , g_aCastle[nCntNotes].fPos.y , 0.0f);
		pVtx[2 + 4 * nCntNotes].pos = D3DXVECTOR3(g_aCastle[nCntNotes].fPos.x , g_aCastle[nCntNotes].fPos.y + g_aCastle[nCntNotes].fSize.y, 0.0f);
		pVtx[3 + 4 * nCntNotes].pos = D3DXVECTOR3(g_aCastle[nCntNotes].fPos.x  + CASTLE_WIDTH , g_aCastle[nCntNotes].fPos.y + g_aCastle[nCntNotes].fSize.y, 0.0f);

		pVtx[0 + 4 * nCntNotes].tex = D3DXVECTOR2( 0.0f , 0.0f );
		pVtx[1 + 4 * nCntNotes].tex = D3DXVECTOR2( 0.25f , 0.0f );
		pVtx[2 + 4 * nCntNotes].tex = D3DXVECTOR2( 0.0f , 1.0f );
		pVtx[3 + 4 * nCntNotes].tex = D3DXVECTOR2( 0.25f , 1.0f );

		//rhw�̐ݒ�(�K��1.0f������!!!!!!!!)
		pVtx[0 + 4 * nCntNotes].rhw = 1.0f;
		pVtx[1 + 4 * nCntNotes].rhw = 1.0f;
		pVtx[2 + 4 * nCntNotes].rhw = 1.0f;
		pVtx[3 + 4 * nCntNotes].rhw = 1.0f;

		//���_�J���[(0�`255�̐����l)
		pVtx[0 + 4 * nCntNotes].color = D3DCOLOR_RGBA(255 , 255 , 255 , 255);
		pVtx[1 + 4 * nCntNotes].color = D3DCOLOR_RGBA(255 , 255 , 255 , 255);
		pVtx[2 + 4 * nCntNotes].color = D3DCOLOR_RGBA(255 , 255 , 255 , 255);
		pVtx[3 + 4 * nCntNotes].color = D3DCOLOR_RGBA(255 , 255 , 255 , 255);

	} // EO for

	//�����A�����b�N
	g_pVtxBufferCastle -> Unlock();

	return S_OK;
}//EOMakeVertexNotes

void AddDamegeCastle(int nDamege)
{
	g_aCastle[0].nHp -= nDamege;
	if(g_aCastle[0].nHp <= 0)
	{
		g_aCastle[0].nHp = 0;
		PlaySound(SE_GAME_GATE_BREAK_ALL);
		setGameState(LOSE);
	}
	else
	{
		PlaySound(SE_GAME_GATE_BREAK);
	}
}

int GetCastleHp(void)
{
	return g_aCastle[0].nHp;
}
