//============================================
//  NucleusBoss�֐�  (NucleusBoss.cpp)
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
#include "sound.h"
#include "nucleusBoss.h"

//============================================
//
//  �萔�錾
//
//============================================
#define BOSSNUCLEUS_NUM_SIDE        (1.0f)							// �摜1���̉��̐�
#define BOSSNUCLEUS_NUM_VERTICAL	(1)								// �摜1���̏c�̐�
#define BOSSNUCLEUS_WIDTH           ( 1.0f / BOSSNUCLEUS_NUM_SIDE )	// 1U�̕�
#define BOSSNUCLEUS_HEIGHT          (1.0f)							// 1V�̍���
#define BOSSNUCLEUS_NUM_SPEED       (0.0f)							// �ړ����x
#define BOSSNUCLEUS_LIFE            (30)							// �ꂩ���̕\���t���[����
#define BOSSNUCLEUS_ANIME           (6)								// �ꂩ��

#//�ǂݍ��ރe�N�X�`���t�@�C����
#define BOSSNUCLEUS_TEXTURENAME_ONE      "data/TEXTURE/GAME/NUCLEUS/BossNuc01.png"
#define BOSSNUCLEUS_TEXTURENAME_TWO      "data/TEXTURE/GAME/NUCLEUS/BossNuc02.png"
#define BOSSNUCLEUS_TEXTURENAME_THREE    "data/TEXTURE/GAME/NUCLEUS/BossNuc03.png"

//============================================
//
//  �O���[�o���ϐ�
//
//============================================
//LP�̓|�C���^�[!!
LPDIRECT3DTEXTURE9 g_pTextureNucleusBoss[BOSSNUCLEUS_MAX] = {};//NucleusBoss�̒���e�N�X�`���A�e�N�X�`���C���^�[�t�F�[�X

/*���_�o�b�t�@�Ǘ��p*/
LPDIRECT3DVERTEXBUFFER9 g_pVtxBufferNucleusBoss[MAX_BOSSNUCLEUS] = {};//�|�C���^�[!!&������

/*�{�X�̒e�\����*/
BOSSNUCLEUS g_aNucleusBoss[MAX_BOSSNUCLEUS];

//============================================
//
//  �v���g�^�C�v�錾
//
//============================================
HRESULT MakeVertexNucleusBoss(LPDIRECT3DDEVICE9 pDevice);//���_�̍쐬

//============================================
//
//  ���O  InitNucleusBoss�֐�
//  ����	void
//  �߂�l  void
//  ����  NucleusBoss�֌W�̏�����
//
//============================================
HRESULT InitNucleusBoss(void)
{
	UINT nID;  //���b�Z�[�W�{�b�N�X�̕Ԃ�l������
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = getDevice();

	//���_�쐬
	if(FAILED(MakeVertexNucleusBoss(pDevice)))
	{
		return E_FAIL;
	}//EOif
	
	//�e�N�X�`���擾
	if(FAILED(
		D3DXCreateTextureFromFile( pDevice , BOSSNUCLEUS_TEXTURENAME_ONE , &g_pTextureNucleusBoss[0] )//�e�N�X�`���̓ǂݍ��݁A�f�B�X�N����ǂݍ��ނ�!!!!!!
		))
		{
			//�G���[���b�Z�[�W
			nID = MessageBox(NULL , "�e�N�X�`�����擾�ł��܂���ł����B","BOSSNUCLEUS",MB_OK | MB_DEFBUTTON1);
		}//EOif
	if(FAILED(
		D3DXCreateTextureFromFile( pDevice , BOSSNUCLEUS_TEXTURENAME_TWO , &g_pTextureNucleusBoss[1] )//�e�N�X�`���̓ǂݍ��݁A�f�B�X�N����ǂݍ��ނ�!!!!!!
		))
		{
			//�G���[���b�Z�[�W
			nID = MessageBox(NULL , "�e�N�X�`�����擾�ł��܂���ł����B","BOSSNUCLEUS",MB_OK | MB_DEFBUTTON1);
		}//EOif
	if(FAILED(
		D3DXCreateTextureFromFile( pDevice , BOSSNUCLEUS_TEXTURENAME_THREE , &g_pTextureNucleusBoss[2] )//�e�N�X�`���̓ǂݍ��݁A�f�B�X�N����ǂݍ��ނ�!!!!!!
		))
		{
			//�G���[���b�Z�[�W
			nID = MessageBox(NULL , "�e�N�X�`�����擾�ł��܂���ł����B","BOSSNUCLEUS",MB_OK | MB_DEFBUTTON1);
		}//EOif


	// �{�X�̒e�\���̂̏�����
	for(int nCntEx = 0 ; nCntEx < MAX_BOSSNUCLEUS ; nCntEx++)
	{
		g_aNucleusBoss[nCntEx].bUse = false;
		g_aNucleusBoss[nCntEx].bDraw = false;
		g_aNucleusBoss[nCntEx].fHeight = 0.0f;
		g_aNucleusBoss[nCntEx].fPos = D3DXVECTOR2(0.0f , 0.0f);
		g_aNucleusBoss[nCntEx].fUV = D3DXVECTOR2(0.0f , 0.0f);
		g_aNucleusBoss[nCntEx].fHeight = 0.0f;
		g_aNucleusBoss[nCntEx].fWidth = 0.0f;
		g_aNucleusBoss[nCntEx].nFlame = 0;
		g_aNucleusBoss[nCntEx].nLife = BOSSNUCLEUS_LIFE;
		g_aNucleusBoss[nCntEx].nType = BOSSNUCLEUS_NONE;
	} // EO for
	return S_OK;
}//EOInitPolygin

//============================================
//
//  ���O  UninitNucleusBoss�֐�
//  ����	void
//  �߂�l  void
//  ����  NucleusBoss�֌W�̏I������
//
//============================================
void UninitNucleusBoss(void)
{
	//�e�N�X�`���C���^�[�t�F�[�X�̌�Еt��
	for(int i = 0 ; i < 2 ; i++)
	{
		SAFE_RELEASE( g_pTextureNucleusBoss[i] );
	} // EO for

	for(int nCntExp = 0 ; nCntExp < MAX_BOSSNUCLEUS ; nCntExp++)
	{
		//���_�o�b�t�@�̌�Еt��
		SAFE_RELEASE( g_pVtxBufferNucleusBoss[nCntExp] );
	} // EO for
}//EOUninitNucleusBoss

//============================================
//
//  ���O  UpdateNucleusBoss�֐�
//  ����	void
//  �߂�l  void
//  ����  NucleusBoss�֌W�̍X�V����
//
//============================================
void UpdateNucleusBoss(void)
{
	//���_�o�b�t�@
	VERTEX2D* pVtx;//���z�A�h���X���擾���邽�߂̃|�C���^�[�A������hiaruyo

	// UV�A�j���[�V�����Ń{�X�̒e
	for(int nCntEx = 0 ; nCntEx < MAX_BOSSNUCLEUS ; nCntEx++)
	{
		// �g�p�`�F�b�N
		if(g_aNucleusBoss[nCntEx].bUse == true)
		{
			if(g_aNucleusBoss[nCntEx].nDrawTime > 0)
			{
				g_aNucleusBoss[nCntEx].nDrawTime--;
				if(g_aNucleusBoss[nCntEx].nDrawTime <= 0)
				{
					OffDrawNucleusBoss(nCntEx);
				} // EO if
			} // EO if

			// ���W�̕ۑ�
			g_pVtxBufferNucleusBoss[ nCntEx ]->Lock ( 0 , 0 , (void**)&pVtx , 0);				//���b�N

			//���_���W�̐ݒ�(2D���W , �E��� )
			pVtx [ 0 ] . pos = D3DXVECTOR3 (g_aNucleusBoss[nCntEx].fPos.x - g_aNucleusBoss[nCntEx].fWidth / 2 ,
				g_aNucleusBoss[nCntEx].fPos.y - g_aNucleusBoss[nCntEx].fHeight / 2 , 0.0f);
			pVtx [ 1 ] . pos = D3DXVECTOR3 (g_aNucleusBoss[nCntEx].fPos.x + g_aNucleusBoss[nCntEx].fWidth / 2 ,
				g_aNucleusBoss[nCntEx].fPos.y - g_aNucleusBoss[nCntEx].fHeight / 2, 0.0f);
			pVtx [ 2 ] . pos = D3DXVECTOR3 (g_aNucleusBoss[nCntEx].fPos.x - g_aNucleusBoss[nCntEx].fWidth / 2 ,
				g_aNucleusBoss[nCntEx].fPos.y + g_aNucleusBoss[nCntEx].fHeight / 2, 0.0f);
			pVtx [ 3 ] . pos = D3DXVECTOR3 (g_aNucleusBoss[nCntEx].fPos.x + g_aNucleusBoss[nCntEx].fWidth / 2 ,
				g_aNucleusBoss[nCntEx].fPos.y + g_aNucleusBoss[nCntEx].fHeight / 2, 0.0f);

			//�e���_�̃e�N�X�`�����W�̐ݒ�
			pVtx [ 0 ] . tex = D3DXVECTOR2 (g_aNucleusBoss[nCntEx].fUV.x , g_aNucleusBoss[nCntEx].fUV.y);
			pVtx [ 1 ] . tex = D3DXVECTOR2 (g_aNucleusBoss[nCntEx].fUV.x  +BOSSNUCLEUS_WIDTH, g_aNucleusBoss[nCntEx].fUV.y);
			pVtx [ 2 ] . tex = D3DXVECTOR2 (g_aNucleusBoss[nCntEx].fUV.x , g_aNucleusBoss[nCntEx].fUV.y + BOSSNUCLEUS_HEIGHT);
			pVtx [ 3 ] . tex = D3DXVECTOR2 (g_aNucleusBoss[nCntEx].fUV.x + BOSSNUCLEUS_WIDTH, g_aNucleusBoss[nCntEx].fUV.y+ BOSSNUCLEUS_HEIGHT);

			g_pVtxBufferNucleusBoss[ nCntEx ]->Unlock ();												//���b�N����

		} // EO if
	} // EO for
}//EOUpdateNucleusBoss

//============================================
//
//  ���O  DrawNucleusBoss�֐�
//  ����	void
//  �߂�l  void
//  ����  NucleusBoss�֌W�̕`�揈��
//
//============================================
void DrawNucleusBoss(void)
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = getDevice();

	// �ő吔�`�F�b�N
	for(int nCntEx = 0 ; nCntEx < MAX_BOSSNUCLEUS ; nCntEx++)
	{
		if(g_aNucleusBoss[nCntEx].bUse == true && g_aNucleusBoss[nCntEx].bDraw == true )
		{
			//�p�C�v���C���̐ݒ�
			pDevice -> SetStreamSource(0,//�X�g���[���ԍ�(���{������)
								g_pVtxBufferNucleusBoss[nCntEx] ,//�f�[�^�̂���ꏊ(�擪�A�h���X)
								0,//�I�t�Z�b�g(�P�ʃo�C�g)�A�f�[�^�̂ǂ̕ӂ��玝���Ă��邩,0�͐擪
								sizeof(VERTEX2D));//�X�g���C�h��(��̒P�ʂ̑傫��)


			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice -> SetFVF( FVF_VERTEX_2D | D3DFVF_TEX1 );

			switch(g_aNucleusBoss[nCntEx].nType)
			{
			case BOSSNUCLEUS_ONE:
				pDevice -> SetTexture( 0 , g_pTextureNucleusBoss[0] );
				break;
			case BOSSNUCLEUS_TWO:
				pDevice -> SetTexture( 0 , g_pTextureNucleusBoss[1] );
				break;
			case BOSSNUCLEUS_THREE:
				pDevice -> SetTexture( 0 , g_pTextureNucleusBoss[2] );
				break;
			} // EO switch
			//�v���~�e�B�u�̕`��
			pDevice -> DrawPrimitive(D3DPT_TRIANGLESTRIP,//�v���~�e�B�u�̎��
				0,//�I�t�Z�b�g(���_��)�����_�ڂ���Ƃ邩
				NUM_POLYGON);//�������_�����Ă���΂����̂��A�v���~�e�B�u�̖������������Q���B�p�C�v���C���͐��ꗬ���ɂȂ��Ă��邩��B

		} // EO if
	} // EO for
}//EODarwNucleusBoss

//============================================
//
//  ���O  MakeVertexNucleusBoss�֐�
//  ����	LPDIRECT3DDEVICE9 pDevice
//  �߂�l  void
//  ����  ���_�̍쐬
//
//============================================
HRESULT MakeVertexNucleusBoss(LPDIRECT3DDEVICE9 pDevice)
{
	// �ő吔��
	for(int nCntEx = 0 ; nCntEx < MAX_BOSSNUCLEUS ; nCntEx++)
	{
		//���_�o�b�t�@�쐬
		if(FAILED(
		pDevice -> CreateVertexBuffer(sizeof(VERTEX2D) * NUM_VERTEX,//�쐬���������_�o�b�t�@�̃T�C�Y = 1�̒��_�̃T�C�Y * ���_��
																	 //�ǂꂭ�炢�������ق������A�������߂�����ӂ₷��Ł[�[�[
				D3DUSAGE_WRITEONLY,									//���_�o�b�t�@�̎g�p���@�A�������ݐ�p�Ȃ̂ŁA���炭�ő�
				FVF_VERTEX_2D,										//NULL��0�ł����v�A�}�i�[�I�ɂ͏�������B���̃o�b�t�@�̒��_�t�H�[�}�b�g��₤
				D3DPOOL_MANAGED,									//�������Ǘ��ǂ�����ݒ�A���̏�Ԃ̓f�o�C�X�ɂ��C��
				&g_pVtxBufferNucleusBoss[nCntEx],						//�o���オ�������_�o�b�t�@���Ǘ�����A�h���X
				NULL)												//�䂾�����NULL
		))
		{
			return E_FAIL;
		}

		//���_�o�b�t�@
		VERTEX2D* pVtx;//���z�A�h���X���擾���邽�߂̃|�C���^�[�A������hiaruyo
		//���_�o�b�t�@�����b�N���āA���z�A�h���X���擾����
		g_pVtxBufferNucleusBoss[nCntEx] -> Lock(0,	//�ǂ����烍�b�N���邩
									0,				//�ǂ��܂Ń��b�N���邩(0~0�őS�����b�N)
									(void**)&pVtx,	//�|�C���^�̃|�C���^(�A�h���X�������ꂽ�������̃A�h���X)
									0);				//�l�ڒ��ׂ�Ɩʔ��������B
		//���_�o�b�t�@�g�p
		
		//rhw�̐ݒ�(�K��1.0f������!!!!!!!!)
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[(0�`255�̐����l)
		pVtx[0].color = D3DCOLOR_RGBA(255 , 255 , 255 , 255);
		pVtx[1].color = D3DCOLOR_RGBA(255 , 255 , 255 , 255);
		pVtx[2].color = D3DCOLOR_RGBA(255 , 255 , 255 , 255);
		pVtx[3].color = D3DCOLOR_RGBA(255 , 255 , 255 , 255);

		//�����A�����b�N
		g_pVtxBufferNucleusBoss[nCntEx] -> Unlock();
	} // EO for
	return S_OK;

}//EOMakeVertexNucleusBoss

//============================================
//
//  ���O  SetNucleusBoss�֐�
//  ����	void
//  �߂�l  float fPosX ,float fPosY,float fWidth,float fHeught,EXPLOSION_MODE nMode
//  ����  �{�X�̒e���Z�b�g
//
//============================================
int    SetNucleusBoss    (float fPosX , // ���S���WX
	float fPosY,					   // ���S���WY
	float fWidth,					   // ��
	float fHeught,				   // ����
	BOSSNUCLEUS_TYPE nType
	)
{
	for(int nCntEx = 0 ; nCntEx < MAX_BOSSNUCLEUS ; nCntEx++)
	{
		if(g_aNucleusBoss[nCntEx].bUse == false)
		{
			g_aNucleusBoss[nCntEx].fPos = D3DXVECTOR2(fPosX , fPosY);
			g_aNucleusBoss[nCntEx].fUV = D3DXVECTOR2(0.0f , 0.0f);
			g_aNucleusBoss[nCntEx].fWidth = fWidth;
			g_aNucleusBoss[nCntEx].fHeight = fHeught;
			g_aNucleusBoss[nCntEx].nFlame = 0;
			g_aNucleusBoss[nCntEx].bUse = true;
			g_aNucleusBoss[nCntEx].nLife = BOSSNUCLEUS_LIFE;
			g_aNucleusBoss[nCntEx].nType = nType;
			return nCntEx;
		} // EO if
	} // EO for

	return -1;
} // EO SetNucleusBoss

//============================================
//
//  ���O  MakeVertexNucleusBoss�֐�
//  ����	LPDIRECT3DDEVICE9 pDevice
//  �߂�l  void
//  ����  ���_�̍쐬
//
//============================================
BOSSNUCLEUS* GetNucleusBoss(void)
{
	return &g_aNucleusBoss[0];
} // EO GetNucleusBoss

void AddDmgNucBoss(int damage, int num)
{
	g_aNucleusBoss[num].nLife -= damage;
}

void SetPosNucleusBoss(int nIndex , D3DXVECTOR2 fPos)
{
	if(g_aNucleusBoss[nIndex].bUse == false)
	{
		return;
	} // EO if
	
	g_aNucleusBoss[nIndex].fPos = fPos;
} // EO SetPosNucleusBoss

void OffDrawNucleusBoss(int nIndex)
{
	if(g_aNucleusBoss[nIndex].bUse == false)
	{
		return;
	} // EO if

	g_aNucleusBoss[nIndex].bDraw = false;
} // EO OffDrawNucleusBoss


void OnDrawNucleusBoss(int nIndex , int nTime)
{
	if(g_aNucleusBoss[nIndex].bUse == false)
	{
		return;
	} // EO if
		g_aNucleusBoss[nIndex].bDraw = true;
		g_aNucleusBoss[nIndex].nDrawTime = nTime;
} // EO 

void ReleaseNucleusBoss(int nIdx)
{
	g_aNucleusBoss[nIdx].bUse = false;
}

void OffNucleusBoss(int nIndex)
{
	g_aNucleusBoss[nIndex].bUse = false;
} // EO OffDrawNucleusBoss
