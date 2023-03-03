//===================================================
//
// ���[�V�����w�b�_�[
// Author:Teruto Sato
//
//===================================================
#ifndef _MOTION_H_
#define _MOTION_H_	//��d�C���N���[�h�h�~

//--------------------------------
// �C���N���[�h
//--------------------------------
#include "object.h"

//--------------------------------
// �O���錾
//--------------------------------
class CModel;		//���f��

//--------------------------------
// �}�N����`
//--------------------------------
#define MAX_PARTS	(7)		//���f���p�[�c�̍ő吔
#define MAX_KEY		(5)		//�L�[�̍ő吔

//================================
// ���[�V�����N���X�̒�`
//================================
class CMotion
{
public:
	//------------------------
	// �L�[�v�f
	//------------------------
	struct KEY
	{
		D3DXVECTOR3 pos;	//�ʒu
		D3DXVECTOR3 rot;	//����
	};

	//------------------------
	// �L�[���
	//------------------------
	struct KEY_SET
	{
		int nFrame;	//�t���[����
		KEY aKey[MAX_PARTS];
	};

	//------------------------
	// ���[�V�������
	//------------------------
	struct MOTION_SET
	{
		bool bLoop;					//���[�v���邩�ǂ���
		int nNumKey;				//�L�[�̍ő吔
		KEY_SET aKeySet[MAX_KEY];	//�L�[�Z�b�g���

		int nStartCollision;		//�����蔻��̊J�n����
		int nNextAtkTime;			//���̍U���̓��͊J�n����
		int nNumPoint;				//����|�C���g��
		int nCritical;				//�N���e�B�J����
		int nNumHit;				//�q�b�g��
		int nHitInterval;			//�q�b�g�Ԋu
		float fDamageMag;			//�_���[�W�{��(magnification)
	};

	//------------------------
	// ���[�V�����̎��
	//------------------------
	enum MOTION_TYPE
	{
		MOTION_IDOL = 0,	//�ҋ@
		MOTION_MOVE,		//�ړ�
		MOTION_ATTACK_1,	//�ʏ�U��(1�i��)
		MOTION_ATTACK_2,	//�ʏ�U��(2�i��)
		MOTION_MAX
	};

	CMotion();	//�R���X�g���N�^
	~CMotion();	//�f�X�g���N�^

	//------------------------
	// �����o�֐�
	//------------------------
	void Uninit();
	void Update();
	void Draw(D3DXMATRIX mtxWorld);

	void SetModel();											//���f���̐ݒ�
	void SetMotion(MOTION_TYPE type, bool bLoop, int nNumKey);	//���[�V�����̐ݒ�
	CMotion::MOTION_TYPE ChangeMotion(MOTION_TYPE type);		//���[�V�����̕ύX
	void GetFileMotion();										//�t�@�C�����g�������[�V�����̎擾

	//------------------------
	// �Q�b�^�[
	//------------------------
	MOTION_SET GetMotionSet() { return motionSet; }

private:
	//------------------------
	// �����o�ϐ�
	//------------------------
	int m_nCurrentKey;						//���݂̃L�[�ԍ�
	int m_nCntMotion;						//���[�V�����J�E���^�[
	MOTION_SET m_aMotionSet[MOTION_MAX];	//���[�V�������
	MOTION_TYPE m_type;						//���݂̃��[�V����
	CModel*  m_pModel[MAX_PARTS];			//���f��
	MOTION_SET motionSet;
};

#endif