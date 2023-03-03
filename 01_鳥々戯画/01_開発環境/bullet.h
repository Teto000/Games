//=====================================
//
// バレットヘッダー
// Author : Sato Teruto
//
//=====================================
#ifndef _BULLET_H_
#define _BULLET_H_	

//--------------------------
// インクルード
//--------------------------
#include "object2D.h"

//--------------------------
// 前方宣言
//--------------------------
class CExplosion;	//爆発
class CDamage;		//ダメージ

//--------------------------
// バレットクラス
//--------------------------
class CBullet : public CObject2D
{
public:
	//---------------------------
	// 弾の列挙型の定義
	//---------------------------
	enum BULLETTYPE
	{
		BULLETTYPE_NORMAL = 0,
		BULLETTYPE_HORMING,
		BULLETTYPE_CHARGE,
		BULLETTYPE_OPTION,
		BULLETTYPE_MAX
	};

	CBullet();				//コンストラクタ
	~CBullet() override;	//デストラクタ

	//----------------
	// メンバ関数
	//----------------
	HRESULT Init(D3DXVECTOR3 pos) override;
	void Uninit() override;
	void Update() override;
	void Draw()	  override;

	D3DXVECTOR3 Homing(float& posX, float& posY, float& moveX, float& moveY);	//ホーミング弾
	
	//セッター
	void SetBulletSize(float fLength);

	//ゲッター
	BULLETTYPE GetType();

	//----------------
	// 静的メンバ関数
	//----------------
	static CBullet *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, BULLETTYPE type);
	void ShotBullet(D3DXVECTOR3 pos, int nLevel, int nShotTime);

private:
	void CollisionBullet(CObject::EObjType ObjType);	//当たった処理

private:
	//----------------
	// 定数定義
	//----------------
	static const int nMaxHoming = 3;		//ホーミング弾発射の最大数
	static const int nDefaultLife = 80;		//弾の寿命の基準値
	static const float fBulletSpeed;		//弾の速度
	static const float fBulletSpeed_Homing;	//ホーミング弾の速度
	static const float nDefaultSize;		//弾の大きさの基準値

	//----------------
	// メンバ変数
	//----------------s
	D3DXVECTOR3 m_pos;		//位置
	D3DXVECTOR3 m_Tirget;	//ホーミング目標の位置
	D3DXVECTOR3 m_move;		//移動量
	D3DXVECTOR3 m_rot;		//回転
	int m_nLife;			//寿命
	int m_nPlayerAttack;	//プレイヤーの攻撃力
	float m_fWidth;			//幅
	float m_fHeight;		//高さ
	BULLETTYPE m_type;		//種類
	CExplosion* pExplosion;	//爆発
	CDamage*	pDamage;	//ダメージ

	//----------------
	// 静的メンバ変数
	//----------------
	static int m_nChageTime;	//弾のチャージ時間
	static int m_nCntHorming;	//ホーミング弾の発射カウント

};

#endif // !_BULLET_H_