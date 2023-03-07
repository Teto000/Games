//=====================================
//
// プレイヤーヘッダー
// Author : Sato Teruto
//
//=====================================
#ifndef _PLAYER_H_
#define _PLAYER_H_	

//--------------------------
// インクルード
//--------------------------
#include "object2D.h"

//--------------------------
// 前方宣言
//--------------------------
class CHp;		//HPクラス
class CMp;		//MPクラス
class CLevel;	//レベルクラス
class CBullet;	//弾クラス
class CHpFream;	//HPフレームクラス
class CBarrier;	//バリアクラス

//--------------------------
// プレイヤークラス
//--------------------------
class CPlayer : public CObject2D
{
public:
	enum PLAYERSTATE
	{
		PLAYERSTATE_NORMAL = 0,	//通常
		PLAYERSTATE_INVINCIBLE,	//無敵
		PLAYERSTATE_MAX
	};

	CPlayer();				//コンストラクタ
	~CPlayer() override;	//デストラクタ

	//------------------
	// メンバ関数
	//------------------
	HRESULT Init(D3DXVECTOR3 pos) override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	void SetSkill();
	void AddLife(int nAttack);	//HPの減少
	void AddMagic(int nValue);	//MPの減少

	//ゲッター
	D3DXVECTOR3 GetMove();
	int GetLife();
	int GetRemLife();
	int GetAttack();
	int GetMagic() { return m_nMagic; }
	bool GetUsedSkill(int nNum) { return m_bSlill[nNum]; }
	PLAYERSTATE GetState();

	//------------------
	// 静的メンバ関数
	//------------------
	static CPlayer *Create();
	static void SetCol(D3DXCOLOR col);	//色の設定

private:
	D3DXVECTOR3 OperationPlayer();	//操作
	D3DXVECTOR3 MoveJoypad();
	void InvincibleTime();			//無敵時間
	void Animation();				//テクスチャアニメーション

private:
	//------------------
	// 定数定義
	//------------------
	static const float fPlayerSpeed;		//プレイヤーの速度
	static const int nPlayerLife = 300;		//プレイヤーの体力
	static const int nMaxLife = 100;		//最大体力(%)
	static const int nMaxSkill = 4;			//スキルの最大数

	//------------------
	// メンバ変数
	//------------------
	D3DXVECTOR3 m_pos;			//位置
	D3DXVECTOR3 m_move;			//移動量
	D3DXVECTOR3 m_rot;			//移動量
	int m_nLife;				//体力
	int m_nMaxLife;				//最大体力
	int m_nRemLife;				//残り体力
	int m_nMagic;				//MP
	int m_nMaxMagic;			//最大MP
	int m_nRemMagic;			//残りMP
	int m_nAttack;				//攻撃力
	int m_nLevel;				//レベル
	int m_nShotTime;			//弾の発射時間
	int m_nCntShotTime;			//弾の発射時間を数える
	int m_nCntInvincible;		//無敵時間を数える
	int m_nCntSkill[nMaxSkill];	//スキルの使用可能時間を数える
	int m_nCntTime;				//テクスチャアニメーションカウント
	float m_nSpeed;				//速度
	float m_fWidth;				//幅
	float m_fHeight;			//高さ
	bool m_bSlill[nMaxSkill];	//スキル使用可能かどうか

	PLAYERSTATE m_type;			//状態
	CHp* m_Hp;					//HPクラス
	CMp* m_Mp;					//MPクラス
	CLevel* m_Level;			//レベルクラス
	CBullet* m_Bullet;			//弾クラス
	CHpFream*m_pHpFream;		//HPフレームクラス
	CBarrier*m_pBarrier;		//バリアクラス

	//------------------
	// 静的メンバ変数
	//------------------
	static D3DXCOLOR m_col;
};

#endif // !_PLAYER_H_