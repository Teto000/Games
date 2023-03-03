//=====================================
//
// エネミーヘッダー
// Author : Sato Teruto
//
//=====================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

//--------------------------
// インクルード
//--------------------------
#include "object2D.h"

//--------------------------
// 前方宣言
//--------------------------
class CHp;				//HPクラス
class CEnemyBullet;		//敵の弾クラス
class CExplosion;		//爆発
class CBarrier;			//バリア
class CHpFream;			//HPフレームクラス
class CItem;			//アイテムクラス

//--------------------------
// エネミークラス
//--------------------------
class CEnemy : public CObject2D
{
public:
	//---------------------------
	// 敵の列挙型の定義
	//---------------------------
	enum ENEMYTYPE
	{
		ENEMYTYPE_NORMAL = 0,	//直進する敵
		ENEMYTYPE_HORMING,		//ホーミングしてくる敵
		ENEMYTYPE_HPITEM,		//HP回復アイテムを落とす敵
		ENEMYTYPE_MPITEM,		//MP回復アイテムを落とす敵
		ENEMYTYPE_BIG,			//ボス敵
		ENEMYTYPE_MAX
	};

	CEnemy();			//コンストラクタ
	~CEnemy() override;	//デストラクタ

	//----------------
	// メンバ関数
	//----------------
	HRESULT Init(D3DXVECTOR3 pos) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	void SetLife(int nLife);	//体力の設定
	void SubLife(int nLife);	//体力の減少

	//ゲッター
	D3DXVECTOR3 GetMove();
	int GetLife();
	int GetRemLife();
	int GetAttack();

	//----------------
	// 静的メンバ関数
	//----------------
	static CEnemy *Create(D3DXVECTOR3 pos, CEnemy::ENEMYTYPE type);
	static void AddLevel();	//レベルアップ

private:
	void Animation();	//テクスチャアニメーション
	void Move();		//移動処理
	void CntAttack();	//攻撃までの時間を数える
	void Attack();		//攻撃処理
	bool Destroy();		//消える処理
	D3DXVECTOR3 Homing(float& posX, float& posY,
					float& moveX, float& moveY);	//ホーミング弾

private:
	//----------------
	// 定数定義
	//----------------
	static const int nMaxTexTime = 80;
	static const int nHalfTexTime = (nMaxTexTime / 2);
	static const int nShotTime = 130;		//弾の発射時間
	static const float fBulletSpeed_Homing;	//ホーミング弾の速度

	//----------------
	// メンバ変数
	//----------------
	D3DXVECTOR3 m_pos;				//位置
	D3DXVECTOR3 m_Tirget;			//ホーミング目標の位置
	D3DXVECTOR3 m_targetPos;		//目的の位置
	D3DXVECTOR3 m_move;				//移動量
	D3DXVECTOR3 m_rot;				//回転
	int m_nLife;					//体力
	int m_nMaxLife;					//最大体力
	int m_nRemLife;					//残り体力
	int m_nCntShotTime;				//弾の発射時間を数える
	int m_nCntTime;					//テクスチャ切り替え時間のカウント
	int m_nAttack;					//攻撃力
	int m_nCntHorming;				//ホーミング時間のカウント
	float m_fWidth;					//幅
	float m_fHeight;				//高さ
	float m_fTargetRot;				//プレイヤーまでの角度
	float m_fChangeAngle;			//変動する移動量
	float m_fTexLeft;				//テクスチャ座標左側
	float m_fTexRight;				//テクスチャ座標右側
	bool m_bChangeAttack;			//攻撃変化するかどうか
	ENEMYTYPE m_type;				//種類

	CHp* m_pHp;						//寿命
	CEnemyBullet*	m_pEnemyBullet;	//敵の弾
	CExplosion*		m_pExplosion;	//爆発
	CBarrier*		m_pBarrier;		//バリア
	CHpFream*		m_pHpFream;		//HPフレームクラス
	CItem*			m_pItem;		//アイテムクラス

	//----------------
	// 静的メンバ変数
	//----------------
	static int m_nLevel;	//レベル
};

#endif // !_ENEMY_H_