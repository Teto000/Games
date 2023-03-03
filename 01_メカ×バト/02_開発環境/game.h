//===================================================
//
// �Q�[���w�b�_�[
// Author : Sato Teruto
//
//====================================================
#ifndef _GAME_H_
#define _GAME_H_	

//--------------------------------
// �C���N���[�h
//--------------------------------
#include <d3dx9.h>
#include "application.h"

//--------------------------------
// �O���錾
//--------------------------------
class CCamera;		//�J����
class CPlayer;		//�v���C���[
class CEnemy;		//�G�l�~�[
class CMeshField;	//���b�V���t�B�[���h
class CPolygon;		//2D�|���S��
class CSky;			//�X�J�C
class CStage;		//�X�e�[�W
class CItem;		//�A�C�e��
class CTime;		//�^�C��
class CMessage;		//���b�Z�[�W
class CBg;			//�w�i

//================================
// �Q�[���N���X�̒�`
//================================
class CGame
{
public:
	CGame();	//�R���X�g���N�^
	~CGame();	//�f�X�g���N�^

	//------------------
	// �����o�֐�
	//------------------
	HRESULT Init();
	void Uninit();
	void Update();

	//------------------
	// �Z�b�^�[
	//------------------
	static void SetDeathEnemy() { m_bDeathEnemny = true; }	//�G������ł��Ԃɂ���
	static void SetDeathPlayer() { m_bDeathPlayer = true; }	//�v���C���[������ł��Ԃɂ���
	static void SubNum() { nNum--; }

	//------------------
	// �Q�b�^�[
	//------------------
	static bool GetFinish()			   { return m_bFinish; }		//�I���t���O���擾
	static bool GetStart()			   { return m_bStart; }			//�J�n�t���O���擾
	static bool GetDeathEnemy()		   { return m_bDeathEnemny;}	//�G�����񂾂��ǂ������擾
	static bool GetDeathPlayer()	   { return m_bDeathPlayer; }	//�v���C���[�����񂾂��ǂ������擾
	static CCamera*	GetCamera()		   { return m_pCamera; }		//�J�����̎擾
	static CPlayer*	GetPlayer()		   { return m_pPlayer; }		//�v���C���[�̎擾
	static CEnemy*	GetEnemy()		   { return m_pEnemy; }			//�G�l�~�[�̎擾
	static CMeshField*	GetMeshField() { return m_pMeshField; }		//���b�V���t�B�[���h�̎擾

private:
	//------------------
	// �v���C�x�[�g�֐�
	//------------------
	void Finish();		//�Q�[���I������
	void SetMessage();	//�J�E���g�_�E���̕\��
	void SetItem();		//�A�C�e���̐���

private:
	//-------------------
	// �����o�ϐ�
	//-------------------
	int m_nCntFinish;		//�I�����ԃJ�E���g
	int m_nCntItem;			//�A�C�e���������ԃJ�E���g
	int m_nCntMessage;		//���b�Z�[�W��\������܂ł̎���
	int m_nNumMessage;		//�\�����郁�b�Z�[�W�ԍ�
	CItem*		m_pItem;	//�A�C�e��
	CMessage*	m_pMessage;	//���b�Z�[�W
	CBg*		m_pBg;		//�w�i

	//-------------------
	// �ÓI�����o�ϐ�
	//-------------------
	static int nNum;
	static bool m_bDeathEnemny;	//�G������ł��邩
	static bool m_bDeathPlayer;	//�v���C���[������ł��邩
	static bool m_bFinish;		//�I���t���O
	static bool m_bStart;		//�J�n�t���O

	static CCamera*		m_pCamera;		//�J����
	static CPlayer*		m_pPlayer;		//�v���C���[
	static CEnemy*		m_pEnemy;		//�G�l�~�[
	static CMeshField*	m_pMeshField;	//���b�V���t�B�[���h
	static CPolygon*	m_pPolygon;		//2D�|���S��
	static CSky*		m_pSky;			//�X�J�C
	static CStage*		m_pStage;		//�X�e�[�W
	static CTime*		m_pTime;		//�^�C�}�[
};

#endif