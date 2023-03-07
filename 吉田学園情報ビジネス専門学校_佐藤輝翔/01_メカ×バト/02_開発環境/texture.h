//**************************************************
// 
// texture.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _TEXTURE_H_	//���̃}�N����`������ĂȂ�������
#define _TEXTURE_H_	//�Q�d�C���N���[�h�h�~�̃}�N����`

//==================================================
// �C���N���[�h
//==================================================
#include <d3dx9.h>

//==================================================
// ��`
//==================================================
class CTexture
{
public: /* ��` */
	enum TEXTURE
	{
		TEXTURE_TITLE = 0,		//�^�C�g��
		TEXTURE_RESULT,			//���U���g
		TEXTURE_GROUND,			//�n��
		TEXTURE_AIM,			//�Ə�
		TEXTURE_NUMBER,			//���l
		TEXTURE_SKY,			//��
		TEXTURE_BULLET,			//�e

		/* �� ���b�Z�[�W �� */
		TEXTURE_CLEAR,			//�N���A
		TEXTURE_GAMEOVER,		//�Q�[���I�[�o�[
		TEXTURE_BREAK,			//�u���C�N
		TEXTURE_START,			//�X�^�[�g
		TEXTURE_1,				//1
		TEXTURE_2,				//2
		TEXTURE_3,				//3

		/* �� �A�C�e�� �� */
		TEXTURE_ITEM_HEAL,		//��

		/* �� �w�i �� */
		TEXTURE_BG_PRESS,		//Press AnyKey
		TEXTURE_BG_COMBO,		//�R���{�w�i
		TEXTURE_BG_TIMER,		//�^�C�}�[�w�i
		TEXTURE_BG_PLAYER_HP,	//�v���C���[�w�i
		TEXTURE_BG_ENEMY_HP,	//�G�l�~�[HP�w�i
		TEXTURE_BG_BLACK,		//������
		TEXTURE_BG_MANUAL,		//�}�j���A��
		TEXTURE_BG_TUTORIAL1,	//�`���[�g���A��1
		TEXTURE_BG_TUTORIAL2,	//�`���[�g���A��2

		TEXTURE_MAX,
		TEXTURE_NONE,			//�g�p���Ȃ�
	};

	static const char* s_FileName[];	// �t�@�C���p�X

public:
	CTexture();		// �f�t�H���g�R���X�g���N�^
	~CTexture();	// �f�X�g���N�^

public: /* �����o�֐� */
	void LoadAll();										// �S�Ă̓ǂݍ���
	void Load(TEXTURE inTexture);						// �w��̓ǂݍ���
	void ReleaseAll();									// �S�Ă̔j��
	void Release(TEXTURE inTexture);					// �w��̔j��
	LPDIRECT3DTEXTURE9 GetTexture(TEXTURE inTexture);	// ���̎擾

private: /* �����o�ϐ� */
	LPDIRECT3DTEXTURE9 s_pTexture[TEXTURE_MAX];	// �e�N�X�`���̏��
};

#endif // !_TEXTURE_H_
