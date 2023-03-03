//===================================================
//
// �^�C�g���w�b�_�[
// Author : Sato Teruto
//
//===================================================
#ifndef _TITLE_H_
#define _TITLE_H_	

//--------------------------------
// �C���N���[�h
//--------------------------------
#include <d3dx9.h>

//--------------------------------
// �O���錾
//--------------------------------
class CBg;			//�w�i
class CTitleCamera;	//�J����
class CStage;		//�X�e�[�W
class CMeshField;	//���b�V���t�B�[���h
class CSky;			//��

//================================
// �^�C�g���N���X�̒�`
//================================
class CTitle
{
public:
	CTitle();	//�R���X�g���N�^
	~CTitle();	//�f�X�g���N�^

	//------------------
	// �����o�֐�
	//------------------
	HRESULT Init();
	void Uninit();
	void Update();

	//------------------
	// �Q�b�^�[
	//------------------
	static CTitleCamera* GetCamera() { return m_pCamera; }		//�J�����̎擾

private:
	//------------------
	// �����o�ϐ�
	//------------------
	CBg*	m_pBg;		//�w�i
	CStage* m_pStage;	//�X�e�[�W
	CSky*	m_pSky;		//��

	//------------------
	// �ÓI�����o�ϐ�
	//------------------
	static CTitleCamera* m_pCamera;
	static CMeshField*	m_pMeshField;	//���b�V���t�B�[���h
};

#endif