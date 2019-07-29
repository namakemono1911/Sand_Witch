//============================================
//  BulletBoss�֐�  (BulletBoss.cpp)
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
#include "bulletBoss.h"
#include "gate.h"

//============================================
//
//  �萔�錾
//
//============================================
#define BOSSBULLET_NUM_SIDE                  (10.0f)                  // �摜1���̉��̐�
#define BOSSBULLET_NUM_VERTICAL              (1)                   // �摜1���̏c�̐�
#define BOSSBULLET_WIDTH           ( 1.0f / BOSSBULLET_NUM_SIDE )        // 1U�̕�
#define BOSSBULLET_HEIGHT          (1.0f)    // 1V�̍���
#define BOSSBULLET_NUM_SPEED                 (5.5f)                  // �ړ����x
#define BOSSBULLET_LIFE                      (1) // �ꂩ���̕\���t���[����
#define BOSSBULLET_ANIME                     (6) // �ꂩ��

#define BOSSBULLET_ATTACK                    (10) // �U����
#//�ǂݍ��ރe�N�X�`���t�@�C����
#define BOSSBULLET_TEXTURENAME_ONE      "data/TEXTURE/GAME/BULLET/BossBullet01.png"
#define BOSSBULLET_TEXTURENAME_TWO      "data/TEXTURE/GAME/BULLET/BossBullet02.png"
#define BOSSBULLET_TEXTURENAME_THREE    "data/TEXTURE/GAME/BULLET/BossBullet03.png"

//============================================
//
//  �O���[�o���ϐ�
//
//============================================
//LP�̓|�C���^�[!!
LPDIRECT3DTEXTURE9 g_pTextureBulletBoss[BOSSBULLET_MAX] = {};//BulletBoss�̒���e�N�X�`���A�e�N�X�`���C���^�[�t�F�[�X

/*���_�o�b�t�@�Ǘ��p*/
LPDIRECT3DVERTEXBUFFER9 g_pVtxBufferBulletBoss[MAX_BOSSBULLET] = {};//�|�C���^�[!!&������

/*�{�X�̒e�\����*/
BOSSBULLET g_aBulletBoss[MAX_BOSSBULLET];

//============================================
//
//  �v���g�^�C�v�錾
//
//============================================
HRESULT MakeVertexBulletBoss(LPDIRECT3DDEVICE9 pDevice);//���_�̍쐬

//============================================
//
//  ���O  InitBulletBoss�֐�
//  ����	void
//  �߂�l  void
//  ����  BulletBoss�֌W�̏�����
//
//============================================
HRESULT InitBulletBoss(void)
{
	UINT nID;  //���b�Z�[�W�{�b�N�X�̕Ԃ�l������
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = getDevice();

	//���_�쐬
	if(FAILED(MakeVertexBulletBoss(pDevice)))
	{
		return E_FAIL;
	}//EOif
	
	//�e�N�X�`���擾
	if(FAILED(
		D3DXCreateTextureFromFile( pDevice , BOSSBULLET_TEXTURENAME_ONE , &g_pTextureBulletBoss[0] )//�e�N�X�`���̓ǂݍ��݁A�f�B�X�N����ǂݍ��ނ�!!!!!!
		))
		{
			//�G���[���b�Z�[�W
			nID = MessageBox(NULL , "�e�N�X�`�����擾�ł��܂���ł����B","BOSSBULLET",MB_OK | MB_DEFBUTTON1);
		}//EOif
	if(FAILED(
		D3DXCreateTextureFromFile( pDevice , BOSSBULLET_TEXTURENAME_TWO , &g_pTextureBulletBoss[1] )//�e�N�X�`���̓ǂݍ��݁A�f�B�X�N����ǂݍ��ނ�!!!!!!
		))
		{
			//�G���[���b�Z�[�W
			nID = MessageBox(NULL , "�e�N�X�`�����擾�ł��܂���ł����B","BOSSBULLET",MB_OK | MB_DEFBUTTON1);
		}//EOif
	if(FAILED(
		D3DXCreateTextureFromFile( pDevice , BOSSBULLET_TEXTURENAME_THREE , &g_pTextureBulletBoss[2] )//�e�N�X�`���̓ǂݍ��݁A�f�B�X�N����ǂݍ��ނ�!!!!!!
		))
		{
			//�G���[���b�Z�[�W
			nID = MessageBox(NULL , "�e�N�X�`�����擾�ł��܂���ł����B","BOSSBULLET",MB_OK | MB_DEFBUTTON1);
		}//EOif


	// �{�X�̒e�\���̂̏�����
	for(int nCntEx = 0 ; nCntEx < MAX_BOSSBULLET ; nCntEx++)
	{
		g_aBulletBoss[nCntEx].bUse = false;
		g_aBulletBoss[nCntEx].fHeight = 0.0f;
		g_aBulletBoss[nCntEx].fPos = D3DXVECTOR2(0.0f , 0.0f);
		g_aBulletBoss[nCntEx].fUV = D3DXVECTOR2(0.0f , 0.0f);
		g_aBulletBoss[nCntEx].fHeight = 0.0f;
		g_aBulletBoss[nCntEx].fWidth = 0.0f;
		g_aBulletBoss[nCntEx].nFlame = 0;
		g_aBulletBoss[nCntEx].nLife = BOSSBULLET_LIFE;
		g_aBulletBoss[nCntEx].nType = BOSSBULLET_NONE;
	} // EO for
	return S_OK;
}//EOInitPolygin

//============================================
//
//  ���O  UninitBulletBoss�֐�
//  ����	void
//  �߂�l  void
//  ����  BulletBoss�֌W�̏I������
//
//============================================
void UninitBulletBoss(void)
{
	//�e�N�X�`���C���^�[�t�F�[�X�̌�Еt��
	for(int i = 0 ; i < 2 ; i++)
	{
		SAFE_RELEASE( g_pTextureBulletBoss[i] );
	} // EO for

	for(int nCntExp = 0 ; nCntExp < MAX_BOSSBULLET ; nCntExp++)
	{
		//���_�o�b�t�@�̌�Еt��
		SAFE_RELEASE( g_pVtxBufferBulletBoss[nCntExp] );
	} // EO for
}//EOUninitBulletBoss

//============================================
//
//  ���O  UpdateBulletBoss�֐�
//  ����	void
//  �߂�l  void
//  ����  BulletBoss�֌W�̍X�V����
//
//============================================
void UpdateBulletBoss(void)
{
	//���_�o�b�t�@
	VERTEX2D* pVtx;//���z�A�h���X���擾���邽�߂̃|�C���^�[�A������hiaruyo
	GATE* pGate = GetGate();

	// UV�A�j���[�V�����Ń{�X�̒e
	for(int nCntEx = 0 ; nCntEx < MAX_BOSSBULLET ; nCntEx++)
	{
		// �g�p�`�F�b�N
		if(g_aBulletBoss[nCntEx].bUse == true)
		{
			// �ړ�
			g_aBulletBoss[nCntEx].fPos.x -= 2.1f;

			// ��
			for(int i = 0 ; i < GATE_NUM ; i++)
			{
				if((pGate+i)->bUse == true && (pGate+i)->nHp > 0)
				{
					if((pGate+i)->fPos.x + (pGate+i)->fSize.x >= g_aBulletBoss[nCntEx].fPos.x - g_aBulletBoss[nCntEx].fWidth / 2 &&
						(pGate+i)->fPos.y <= g_aBulletBoss[nCntEx].fPos.y &&
						(pGate+i)->fPos.y + (pGate+i)->fSize.y>= g_aBulletBoss[nCntEx].fPos.y)
					{
						g_aBulletBoss[nCntEx].bUse = false;
						AddLife(i , -1 * BOSSBULLET_ATTACK);
					}
				}
			}
			// ���W�̕ۑ�
			g_pVtxBufferBulletBoss[ nCntEx ]->Lock ( 0 , 0 , (void**)&pVtx , 0);				//���b�N

			//���_���W�̐ݒ�(2D���W , �E��� )
			pVtx [ 0 ] . pos = D3DXVECTOR3 (g_aBulletBoss[nCntEx].fPos.x - g_aBulletBoss[nCntEx].fWidth / 2 ,
				g_aBulletBoss[nCntEx].fPos.y - g_aBulletBoss[nCntEx].fHeight / 2 , 0.0f);
			pVtx [ 1 ] . pos = D3DXVECTOR3 (g_aBulletBoss[nCntEx].fPos.x + g_aBulletBoss[nCntEx].fWidth / 2 ,
				g_aBulletBoss[nCntEx].fPos.y - g_aBulletBoss[nCntEx].fHeight / 2, 0.0f);
			pVtx [ 2 ] . pos = D3DXVECTOR3 (g_aBulletBoss[nCntEx].fPos.x - g_aBulletBoss[nCntEx].fWidth / 2 ,
				g_aBulletBoss[nCntEx].fPos.y + g_aBulletBoss[nCntEx].fHeight / 2, 0.0f);
			pVtx [ 3 ] . pos = D3DXVECTOR3 (g_aBulletBoss[nCntEx].fPos.x + g_aBulletBoss[nCntEx].fWidth / 2 ,
				g_aBulletBoss[nCntEx].fPos.y + g_aBulletBoss[nCntEx].fHeight / 2, 0.0f);

			//�e���_�̃e�N�X�`�����W�̐ݒ�
			pVtx [ 0 ] . tex = D3DXVECTOR2 (g_aBulletBoss[nCntEx].fUV.x , g_aBulletBoss[nCntEx].fUV.y);
			pVtx [ 1 ] . tex = D3DXVECTOR2 (g_aBulletBoss[nCntEx].fUV.x  +BOSSBULLET_WIDTH, g_aBulletBoss[nCntEx].fUV.y);
			pVtx [ 2 ] . tex = D3DXVECTOR2 (g_aBulletBoss[nCntEx].fUV.x , g_aBulletBoss[nCntEx].fUV.y + BOSSBULLET_HEIGHT);
			pVtx [ 3 ] . tex = D3DXVECTOR2 (g_aBulletBoss[nCntEx].fUV.x + BOSSBULLET_WIDTH, g_aBulletBoss[nCntEx].fUV.y+ BOSSBULLET_HEIGHT);

			g_pVtxBufferBulletBoss[ nCntEx ]->Unlock ();												//���b�N����

			g_aBulletBoss[nCntEx].fUV.x += BOSSBULLET_WIDTH;
		} // EO if
	} // EO for
}//EOUpdateBulletBoss

//============================================
//
//  ���O  DrawBulletBoss�֐�
//  ����	void
//  �߂�l  void
//  ����  BulletBoss�֌W�̕`�揈��
//
//============================================
void DrawBulletBoss(void)
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = getDevice();

	// �ő吔�`�F�b�N
	for(int nCntEx = 0 ; nCntEx < MAX_BOSSBULLET ; nCntEx++)
	{
		if(g_aBulletBoss[nCntEx].bUse == true)
		{
			//�p�C�v���C���̐ݒ�
			pDevice -> SetStreamSource(0,//�X�g���[���ԍ�(���{������)
								g_pVtxBufferBulletBoss[nCntEx] ,//�f�[�^�̂���ꏊ(�擪�A�h���X)
								0,//�I�t�Z�b�g(�P�ʃo�C�g)�A�f�[�^�̂ǂ̕ӂ��玝���Ă��邩,0�͐擪
								sizeof(VERTEX2D));//�X�g���C�h��(��̒P�ʂ̑傫��)


			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice -> SetFVF( FVF_VERTEX_2D | D3DFVF_TEX1 );

			switch(g_aBulletBoss[nCntEx].nType)
			{
			case BOSSBULLET_ONE:
				pDevice -> SetTexture( 0 , g_pTextureBulletBoss[0] );
				break;
			case BOSSBULLET_TWO:
				pDevice -> SetTexture( 0 , g_pTextureBulletBoss[1] );
				break;
			case BOSSBULLET_THREE:
				pDevice -> SetTexture( 0 , g_pTextureBulletBoss[2] );
				break;
			} // EO switch
			//�v���~�e�B�u�̕`��
			pDevice -> DrawPrimitive(D3DPT_TRIANGLESTRIP,//�v���~�e�B�u�̎��
				0,//�I�t�Z�b�g(���_��)�����_�ڂ���Ƃ邩
				NUM_POLYGON);//�������_�����Ă���΂����̂��A�v���~�e�B�u�̖������������Q���B�p�C�v���C���͐��ꗬ���ɂȂ��Ă��邩��B

		} // EO if
	} // EO for
}//EODarwBulletBoss

//============================================
//
//  ���O  MakeVertexBulletBoss�֐�
//  ����	LPDIRECT3DDEVICE9 pDevice
//  �߂�l  void
//  ����  ���_�̍쐬
//
//============================================
HRESULT MakeVertexBulletBoss(LPDIRECT3DDEVICE9 pDevice)
{
	// �ő吔��
	for(int nCntEx = 0 ; nCntEx < MAX_BOSSBULLET ; nCntEx++)
	{
		//���_�o�b�t�@�쐬
		if(FAILED(
		pDevice -> CreateVertexBuffer(sizeof(VERTEX2D) * NUM_VERTEX,//�쐬���������_�o�b�t�@�̃T�C�Y = 1�̒��_�̃T�C�Y * ���_��
																	 //�ǂꂭ�炢�������ق������A�������߂�����ӂ₷��Ł[�[�[
				D3DUSAGE_WRITEONLY,									//���_�o�b�t�@�̎g�p���@�A�������ݐ�p�Ȃ̂ŁA���炭�ő�
				FVF_VERTEX_2D,										//NULL��0�ł����v�A�}�i�[�I�ɂ͏�������B���̃o�b�t�@�̒��_�t�H�[�}�b�g��₤
				D3DPOOL_MANAGED,									//�������Ǘ��ǂ�����ݒ�A���̏�Ԃ̓f�o�C�X�ɂ��C��
				&g_pVtxBufferBulletBoss[nCntEx],						//�o���オ�������_�o�b�t�@���Ǘ�����A�h���X
				NULL)												//�䂾�����NULL
		))
		{
			return E_FAIL;
		}

		//���_�o�b�t�@
		VERTEX2D* pVtx;//���z�A�h���X���擾���邽�߂̃|�C���^�[�A������hiaruyo
		//���_�o�b�t�@�����b�N���āA���z�A�h���X���擾����
		g_pVtxBufferBulletBoss[nCntEx] -> Lock(0,	//�ǂ����烍�b�N���邩
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
		g_pVtxBufferBulletBoss[nCntEx] -> Unlock();
	} // EO for
	return S_OK;

}//EOMakeVertexBulletBoss

//============================================
//
//  ���O  SetBulletBoss�֐�
//  ����	void
//  �߂�l  float fPosX ,float fPosY,float fWidth,float fHeught,EXPLOSION_MODE nMode
//  ����  �{�X�̒e���Z�b�g
//
//============================================
void    SetBulletBoss    (float fPosX , // ���S���WX
	float fPosY,					   // ���S���WY
	float fWidth,					   // ��
	float fHeught,				   // ����
	BOSSBULLET_TYPE nType
	)
{
	for(int nCntEx = 0 ; nCntEx < MAX_BOSSBULLET ; nCntEx++)
	{
		if(g_aBulletBoss[nCntEx].bUse == false)
		{
			g_aBulletBoss[nCntEx].fPos = D3DXVECTOR2(fPosX , fPosY);
			g_aBulletBoss[nCntEx].fUV = D3DXVECTOR2(0.0f , 0.0f);
			g_aBulletBoss[nCntEx].fWidth = 200;
			g_aBulletBoss[nCntEx].fHeight = 100;
			g_aBulletBoss[nCntEx].nFlame = 0;
			g_aBulletBoss[nCntEx].bUse = true;
			g_aBulletBoss[nCntEx].nLife = BOSSBULLET_LIFE;
			g_aBulletBoss[nCntEx].nType = nType;
			break;
		} // EO if
	} // EO for
} // EO SetBulletBoss

//============================================
//
//  ���O  MakeVertexBulletBoss�֐�
//  ����	LPDIRECT3DDEVICE9 pDevice
//  �߂�l  void
//  ����  ���_�̍쐬
//
//============================================
BOSSBULLET* GetBulletBoss(void)
{
	return &g_aBulletBoss[0];
} // EO GetBulletBoss

  //============================================
  //
  //  ���O  AddDmgBulletBoss�֐�
  //  ����	numBullet	�z��ԍ�
  //		damage		�_���[�W��
  //  �߂�l  void
  //  ����  ���_�̍쐬
  //
  //============================================
void AddDmgBulletBoss(int numBullet, int damage)
{
	g_aBulletBoss[numBullet].nLife -= damage;

	//���C�t0�ȉ��ō폜
	if(g_aBulletBoss[numBullet].nLife <= 0)
		g_aBulletBoss[numBullet].bUse = false;
}
