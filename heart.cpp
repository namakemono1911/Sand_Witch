//============================================
//  Heart�֐�  (Heart.cpp)
//
//  Author  Information
//  ���O  �Έ�  �Y��
//  �쐬��   2016�N07��24��
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
#include "main.h"
#include "notes.h"
#include "castle.h"
#include "gate.h"
#include "heart.h"

//============================================
//
//  �萔�錾
//
//============================================
#//�ǂݍ��ރe�N�X�`���t�@�C����
#define HEART_ONE_TEXTURENAME       "data/TEXTURE/GAME/ENEMY/haert.png"   // NHEART_ONE

//============================================
//
//  �O���[�o���ϐ�
//
//============================================
//LP�̓|�C���^�[!!
LPDIRECT3DTEXTURE9 g_pTextureHeart[MAX_HEART] = {};//Heart�̒���e�N�X�`���A�e�N�X�`���C���^�[�t�F�[�X

/*���_�o�b�t�@�Ǘ��p*/
LPDIRECT3DVERTEXBUFFER9 g_pVtxBufferHeart = NULL;//�|�C���^�[!!&������

/*�n�[�g�\����*/
HEART g_aHeart[MAX_HEART];

//============================================
//
//  �v���g�^�C�v�錾
//
//============================================
HRESULT MakeVertexHeart(LPDIRECT3DDEVICE9 pDevice);//���_�̍쐬

//============================================
//
//  ���O  InitHeart�֐�
//  ����	void
//  �߂�l  void
//  ����  Heart�֌W�̏�����
//
//============================================
HRESULT InitHeart(void)
{
	UINT nID;  //���b�Z�[�W�{�b�N�X�̕Ԃ�l������
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = getDevice();

	//���_�쐬
	if(FAILED(MakeVertexHeart(pDevice)))
	{
		return E_FAIL;
	}//EOif
	
	//�e�N�X�`���擾
	if(FAILED(
	D3DXCreateTextureFromFile( pDevice , HEART_ONE_TEXTURENAME , &g_pTextureHeart[0] )//�e�N�X�`���̓ǂݍ��݁A�f�B�X�N����ǂݍ��ނ�!!!!!!
		))
		{
			//�G���[���b�Z�[�W
			nID = MessageBox(NULL , "�e�N�X�`�����擾�ł��܂���ł����B","HEART_ONE",MB_OK | MB_DEFBUTTON1);
		}//EOif

	// �n�[�g�\���̂̏�����
	for(int nCntHeart = 0 ; nCntHeart < MAX_HEART ; nCntHeart++)
	{
		g_aHeart[nCntHeart].bUse = false;
		g_aHeart[nCntHeart].fHeight = 0.0f;
		g_aHeart[nCntHeart].fPos = D3DXVECTOR2(0.0f , 0.0f);
		g_aHeart[nCntHeart].fUV = D3DXVECTOR2(0.0f , 0.0f);
		g_aHeart[nCntHeart].fUVSize = D3DXVECTOR2(0.0f , 0.0f);
		g_aHeart[nCntHeart].fWidth = 0.0f;
	} // EO for

	return S_OK;
}//EOInitHeart

//============================================
//
//  ���O  UninitHeart�֐�
//  ����	void
//  �߂�l  void
//  ����  Heart�֌W�̏I������
//
//============================================
void UninitHeart(void)
{
	//�e�N�X�`���C���^�[�t�F�[�X�̌�Еt��
	SAFE_RELEASE( g_pTextureHeart[0] );

	//���_�o�b�t�@�̌�Еt��
	SAFE_RELEASE( g_pVtxBufferHeart );
}//EOUninitHeart

//============================================
//
//  ���O  UpdateHeart�֐�
//  ����	void
//  �߂�l  void
//  ����  Heart�֌W�̍X�V����
//
//============================================
void UpdateHeart(void)
{
	//���_�o�b�t�@
	VERTEX2D* pVtx;//���z�A�h���X���擾���邽�߂̃|�C���^�[�A������hiaruyo

		//���_�o�b�t�@�����b�N���āA���z�A�h���X���擾����
	g_pVtxBufferHeart -> Lock(0,	//�ǂ����烍�b�N���邩
								0,				//�ǂ��܂Ń��b�N���邩(0~0�őS�����b�N)
								(void**)&pVtx,	//�|�C���^�̃|�C���^(�A�h���X�������ꂽ�������̃A�h���X)
								0);				//�l�ڒ��ׂ�Ɩʔ��������B

	// UV�A�j���[�V�����Ńn�[�g
	for(int nCntHeart = 0 ; nCntHeart < MAX_HEART ; nCntHeart++)
	{
		// �g�p�`�F�b�N
		if(g_aHeart[nCntHeart].bUse == true)
		{
			//���_���W�̐ݒ�(2D���W , �E��� )
			pVtx [ 0 + 4*nCntHeart] . pos = D3DXVECTOR3 (g_aHeart[nCntHeart].fPos.x , g_aHeart[nCntHeart].fPos.y , 0.0f);
			pVtx [ 1 + 4*nCntHeart] . pos = D3DXVECTOR3 (g_aHeart[nCntHeart].fPos.x + g_aHeart[nCntHeart].fWidth ,g_aHeart[nCntHeart].fPos.y , 0.0f);
			pVtx [ 2 + 4*nCntHeart] . pos = D3DXVECTOR3 (g_aHeart[nCntHeart].fPos.x , g_aHeart[nCntHeart].fPos.y + g_aHeart[nCntHeart].fHeight , 0.0f);
			pVtx [ 3 + 4*nCntHeart] . pos = D3DXVECTOR3 (g_aHeart[nCntHeart].fPos.x + g_aHeart[nCntHeart].fWidth , g_aHeart[nCntHeart].fPos.y + g_aHeart[nCntHeart].fHeight , 0.0f);

		    //�e���_�̃e�N�X�`�����W�̐ݒ�
			pVtx [ 0 + 4*nCntHeart] . tex = D3DXVECTOR2 (g_aHeart[nCntHeart].fUV.x , g_aHeart[nCntHeart].fUV.y);
			pVtx [ 1 + 4*nCntHeart] . tex = D3DXVECTOR2 (g_aHeart[nCntHeart].fUV.x + g_aHeart[nCntHeart].fUVSize.x , g_aHeart[nCntHeart].fUV.y);
			pVtx [ 2 + 4*nCntHeart] . tex = D3DXVECTOR2 (g_aHeart[nCntHeart].fUV.x , g_aHeart[nCntHeart].fUV.y + g_aHeart[nCntHeart].fUVSize.y);
			pVtx [ 3 + 4*nCntHeart] . tex = D3DXVECTOR2 (g_aHeart[nCntHeart].fUV.x + g_aHeart[nCntHeart].fUVSize.x , g_aHeart[nCntHeart].fUV.y+ g_aHeart[nCntHeart].fUVSize.y);


		} // EO if
	} // EO for

	g_pVtxBufferHeart->Unlock ();												//���b�N����

}//EOUpdateHeart

//============================================
//
//  ���O  DrawHeart�֐�
//  ����	void
//  �߂�l  void
//  ����  Heart�֌W�̕`�揈��
//
//============================================
void DrawHeart(void)
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = getDevice();

	//�p�C�v���C���̐ݒ�
	pDevice -> SetStreamSource(0,//�X�g���[���ԍ�(���{������)
						g_pVtxBufferHeart ,//�f�[�^�̂���ꏊ(�擪�A�h���X)
						0,//�I�t�Z�b�g(�P�ʃo�C�g)�A�f�[�^�̂ǂ̕ӂ��玝���Ă��邩,0�͐擪
						sizeof(VERTEX2D) );//�X�g���C�h��(��̒P�ʂ̑傫��)

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice -> SetFVF( FVF_VERTEX_2D | D3DFVF_TEX1 );

	// �ő吔�`�F�b�N
	for(int nCntHeart = 0 ; nCntHeart < MAX_HEART ; nCntHeart++)
	{
		if(g_aHeart[nCntHeart].bUse == true)
		{
			//Heart�̕`������鐡�O
			pDevice -> SetTexture( 0 , g_pTextureHeart[0] );

			//�v���~�e�B�u�̕`��
			pDevice -> DrawPrimitive(D3DPT_TRIANGLESTRIP,//�v���~�e�B�u�̎��
				nCntHeart * 4 ,//�I�t�Z�b�g(���_��)�����_�ڂ���Ƃ邩
				NUM_POLYGON );//�������_�����Ă���΂����̂��A�v���~�e�B�u�̖������������Q���B�p�C�v���C���͐��ꗬ���ɂȂ��Ă��邩��B
		} // EO if
	} // EO for
}//EODarwHeart

//============================================
//
//  ���O  MakeVertexHeart�֐�
//  ����	LPDIRECT3DDEVICE9 pDevice
//  �߂�l  void
//  ����  ���_�̍쐬
//
//============================================
HRESULT MakeVertexHeart(LPDIRECT3DDEVICE9 pDevice)
{

	//���_�o�b�t�@�쐬
	if(FAILED(
		pDevice -> CreateVertexBuffer(sizeof(VERTEX2D) * NUM_VERTEX * MAX_HEART,//�쐬���������_�o�b�t�@�̃T�C�Y = 1�̒��_�̃T�C�Y * ���_��
																	//�ǂꂭ�炢�������ق������A�������߂�����ӂ₷��Ł[�[�[
			D3DUSAGE_WRITEONLY,									//���_�o�b�t�@�̎g�p���@�A�������ݐ�p�Ȃ̂ŁA���炭�ő�
			FVF_VERTEX_2D,										//NULL��0�ł����v�A�}�i�[�I�ɂ͏�������B���̃o�b�t�@�̒��_�t�H�[�}�b�g��₤
			D3DPOOL_MANAGED,									//�������Ǘ��ǂ�����ݒ�A���̏�Ԃ̓f�o�C�X�ɂ��C��
			&g_pVtxBufferHeart,						//�o���オ�������_�o�b�t�@���Ǘ�����A�h���X
			NULL)												//�䂾�����NULL
	))
	{
		return E_FAIL;
	}


	//���_�o�b�t�@
	VERTEX2D* pVtx;//���z�A�h���X���擾���邽�߂̃|�C���^�[�A������hiaruyo
	//���_�o�b�t�@�����b�N���āA���z�A�h���X���擾����
	g_pVtxBufferHeart -> Lock(0,	//�ǂ����烍�b�N���邩
								0,				//�ǂ��܂Ń��b�N���邩(0~0�őS�����b�N)
								(void**)&pVtx,	//�|�C���^�̃|�C���^(�A�h���X�������ꂽ�������̃A�h���X)
								0);				//�l�ڒ��ׂ�Ɩʔ��������B

		// �ő吔��
	for(int nCntHeart = 0 ; nCntHeart < MAX_HEART ; nCntHeart++)
	{
		//rhw�̐ݒ�(�K��1.0f������!!!!!!!!)
		pVtx[0 + 4 * nCntHeart].rhw = 1.0f;
		pVtx[1 + 4 * nCntHeart].rhw = 1.0f;
		pVtx[2 + 4 * nCntHeart].rhw = 1.0f;
		pVtx[3 + 4 * nCntHeart].rhw = 1.0f;

		//���_�J���[(0�`255�̐����l)
		pVtx[0 + 4 * nCntHeart].color = D3DCOLOR_RGBA(255 , 255 , 255 , 255);
		pVtx[1 + 4 * nCntHeart].color = D3DCOLOR_RGBA(255 , 255 , 255 , 255);
		pVtx[2 + 4 * nCntHeart].color = D3DCOLOR_RGBA(255 , 255 , 255 , 255);
		pVtx[3 + 4 * nCntHeart].color = D3DCOLOR_RGBA(255 , 255 , 255 , 255);

	} // EO for

	//�����A�����b�N
	g_pVtxBufferHeart -> Unlock();

	return S_OK;

}//EOMakeVertexHeart

//============================================
//
//  ���O  SetHeart�֐�
//  ����	void
//  �߂�l  float fPosX ,float fPosY,float fWidth,float fHeught,Heart_MODE nMode
//  ����  �n�[�g���Z�b�g
//
//============================================
int    SetHeart    (float fPosX , // ���S���WX
	float fPosY,					   // ���S���WY
	float fWidth,					   // ��
	float fHeught,					   // ����
	int nHp
	)
{
	for(int nCntHeart = 0 ; nCntHeart < MAX_HEART ; nCntHeart++)
	{
		if(g_aHeart[nCntHeart].bUse == false)
		{
			g_aHeart[nCntHeart].bUse = true;
			g_aHeart[nCntHeart].fPos = D3DXVECTOR2(fPosX , fPosY);
			g_aHeart[nCntHeart].fUV = D3DXVECTOR2(0.0f , 0.0f);
			g_aHeart[nCntHeart].fWidth = fWidth;
			g_aHeart[nCntHeart].fHeight = fHeught;

			// hp����T�C�Y�v�Z
			float x= 1.0f / 10.0f * nHp;
			g_aHeart[nCntHeart].fUVSize = D3DXVECTOR2(x , 1.0f);

			return nCntHeart;
		} // EO if
	} // EO for

	return -1;
} // EO SetHeart

//============================================
//
//  ���O  GetHeart�֐�
//  ����	void
//  �߂�l  HEART *g_aHeart[0]
//  ����  g_aHeart�̐擪�A�h���X��n��
//
//============================================
HEART* GetHeart()
{
	return &g_aHeart[0];
} // EO GetHeart

void SetPosHeart (int nIdx , D3DXVECTOR2 fPos)	// ���W
{
	if(g_aHeart[nIdx].bUse == false)
	{
		return;
	}

	g_aHeart[nIdx].fPos = fPos;

}

void SetUVSizeHeart(int nIdx , int nLife)	// ���C�t����uv�v�Z
{
	if(g_aHeart[nIdx].bUse == false)
	{
		return;
	}

	float x = 1.0f / 10.0f * nLife;
	g_aHeart[nIdx].fUVSize.x = x;
	g_aHeart[nIdx].fWidth = nLife * HEART_WIDTH;
}

void OffHeart(int nIdx)
{
	if(g_aHeart[nIdx].bUse == false)
	{
		return;
	}
	g_aHeart[nIdx].bUse = false;
}

