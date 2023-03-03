//=====================================
//
// レベルヘッダー
// Author : Sato Teruto
//
//=====================================
#ifndef _LEVEL_H_
#define _LEVEL_H_	

//--------------------------
// インクルード
//--------------------------
#include "object2D.h"

//--------------------------
// 前方宣言
//--------------------------
class CExp;		//経験値

//--------------------------
// レベルクラス
//--------------------------
class CLevel : public CObject2D
{
public:
	CLevel();			//コンストラクタ
	~CLevel() override;	//デストラクタ

	//------------------
	// メンバ関数
	//------------------
	HRESULT Init(D3DXVECTOR3 pos) override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	//------------------
	// 静的メンバ関数
	//------------------
	static CLevel *Create();
	static void AddExp(int nValue);
	
	int GetLevel();

private:
	void LevelUp();

private:
	//------------------
	// 定数
	//------------------
	static const int nMaxLevel = 5;	//最大レベル

	//------------------
	// メンバ変数
	//------------------
	D3DXVECTOR3 m_pos;	//位置
	D3DXVECTOR3 m_rot;	//回転
	int m_nLevel;		//レベルの値
	float m_fLength;	//幅
	CExp* m_pExp;		//経験値

	//------------------
	// 静的メンバ変数
	//------------------
	static int m_nExpPoint;		//経験値の値
};

#endif // !_LEVEL_H_