//===================================================
//
// �`���[�g���A���w�b�_�[
// Author : Sato Teruto
//
//===================================================
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_	

//-------------------------------
// �C���N���[�h
//--------------------------------
#include <d3dx9.h>

//--------------------------------
// �O���錾
//--------------------------------
class CBg;			//�w�i

//================================
// �`���[�g���A���N���X�̒�`
//================================
class CTutorial
{
public:
	//�w�i�̎��
	enum TYPE
	{
		TYPE_MANUAL = 0,
		TYPE_TUTORIAL1,
		TYPE_TUTORIAL2,
		TYPE_GAME,
		TYPE_MAX
	};

	CTutorial();	//�R���X�g���N�^
	~CTutorial();	//�f�X�g���N�^

	//------------------
	// �����o�֐�
	//------------------
	HRESULT Init();
	void Uninit();
	void Update();

private:
	//------------------
	// �萔
	//------------------
	static const int nMaxBg = 3;	//�w�i�̍ő吔

	//------------------
	// �����o�ϐ�
	//------------------
	int m_nNumber;			//�ԍ�
	CBg* m_pBg[nMaxBg];		//�w�i
};

#endif