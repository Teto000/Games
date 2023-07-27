//===================================================
//
// �A�v���P�[�V�����w�b�_�[
// Author : Sato Teruto
//
//===================================================
#ifndef _APPLICATION_H_
#define _APPLICATION_H_	

//------------------------------
// �C���N���[�h
//------------------------------
#include <d3dx9.h>

//------------------------------
// �O���錾
//------------------------------
class CRenderer;	//�����_���[
class CInput;		//�C���v�b�g
class CTexture;		//�e�N�X�`��
class CSound;		//�T�E���h
class CLight;		//���C�g
class CDebugProc;	//�f�o�b�O�p����

//================================
// �A�v���P�[�V�����N���X�̒�`
//================================
class CApplication
{
public:
	//--------------------------------
	// �Q�[�����[�h�̗񋓌^�̒�`
	//--------------------------------
	enum GAMEMODE
	{
		GAMEMODE_TIME = 0,
		GAMEMODE_SCORE,
		GAMEMODE_MAX
	};

	CApplication();		//�R���X�g���N�^
	~CApplication();	//�f�X�g���N�^

	//------------------
	// �����o�֐�
	//------------------
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit();
	void Update();
	void Draw();

	//------------------
	// �ÓI�����o�֐�
	//------------------
	static CRenderer*		GetRenderer()	{ return m_pRenderer; }		//�����_���[�̎擾
	static CInput*			GetInput()		{ return m_pInput; }		//�C���v�b�g�̎擾
	static CTexture*		GetTexture()	{ return m_pTexture; }		//�e�N�X�`���̎擾
	static CSound*			GetSound()		{ return m_pSound; }		//�T�E���h�̎擾
	static CLight*			GetLight()		{ return m_pLight; }		//���C�g�̎擾

private:
	//------------------
	// �ÓI�����o�ϐ�
	//------------------
	static GAMEMODE		m_gameMode;		//�Q�[�����[�h
	static CRenderer*	m_pRenderer;	//�����_���[�N���X
	static CInput*		m_pInput;		//�C���v�b�g�N���X
	static CTexture*	m_pTexture;		//�e�N�X�`���N���X
	static CSound*		m_pSound;		//�T�E���h�N���X
	static CLight*		m_pLight;		//���C�g�N���X
	static CDebugProc*	m_pDebugproc;	//�f�o�b�O�p����
};

#endif // !_APPLICATION_H_