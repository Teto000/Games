//=====================================
//
// HPヘッダー
// Author : Sato Teruto
//
//=====================================
#ifndef _HP_H_
#define _HP_H_	

//--------------------------
// インクルード
//--------------------------
#include "object2D.h"

//--------------------------
// 前方宣言
//--------------------------
class CHpFream;	//HPフレームクラス

//--------------------------
// HPクラス
//--------------------------
class CHp : public CObject2D
{
public:
	CHp();				//コンストラクタ
	~CHp() override;	//デストラクタ

	//------------------
	// メンバ関数
	//------------------
	HRESULT Init(D3DXVECTOR3 pos) override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	void SetLife(int nLife, int nRemLife);
	void SubHP();	//HP減少時の処理
	void SetMove(D3DXVECTOR3 move);		//移動量の設定

	//------------------
	// 静的メンバ関数
	//------------------
	static CHp *Create(D3DXVECTOR3 pos, float fWidth, float fHeight);

private:
	//------------------
	// メンバ変数
	//------------------
	D3DXVECTOR3 m_pos;	//位置
	D3DXVECTOR3 m_move;	//移動量
	int m_nLife;		//体力受け取り用
	int m_nRemLife;		//残り体力受け取り用
	float m_fWidth;		//幅
	float m_fHeight;	//高さ
	float m_fLength;	//HPバーの長さ
};

#endif // !_HP_H_