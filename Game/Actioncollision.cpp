#include "ActionCollision.h"
ActionCollision::ActionCollision()
{
	//初期化
	mDisDivinetoCap = 0;
	mStageModel= gGlobal.mGetModel()["ForCollison"]._handle;
	mAttackID = 0;
}
ActionCollision::~ActionCollision()
{
	
}
bool ActionCollision::MapColPlayer(Player* pl)
{
	float radius = pl->GetRadius();
	VECTOR capsule[2] =
	{
		pl->GetPos(),
		VAdd(pl->GetPos(),VGet(0,pl->GetSeg(),0)),
	};
	capsule[0] = VAdd(capsule[0], pl->GetMove());
	capsule[1] = VAdd(capsule[0], pl->GetMove());
	for (int i = 0; i < 17; i++)
	{
		MV1_COLL_RESULT_POLY_DIM hit_poly_chara;
		hit_poly_chara = MV1CollCheck_Capsule(mStageModel, i, capsule[0], capsule[1], radius);
		if (hit_poly_chara.HitNum >= 1)
		{
			const int hit_num = hit_poly_chara.HitNum;
			int j = 0;
			// 当たったポリゴンの数だけ繰り返し
			for (j = 0; j < hit_num; j++)
			{
				//線分と三角形の最近点二つもらう
				tagSEGMENT_TRIANGLE_RESULT result;
				Segment_Triangle_Analyse(&capsule[0], &capsule[1], &hit_poly_chara.Dim[j].Position[0], &hit_poly_chara.Dim[j].Position[1], &hit_poly_chara.Dim[j].Position[2], &result);
				//ベクトルの引き算で押し出す角度を取る
				VECTOR sub_dir = VSub(result.Seg_MinDist_Pos, result.Tri_MinDist_Pos);
				//線分と三角形の最近点間
				float near_point = Segment_Triangle_MinLength(capsule[0], capsule[1], hit_poly_chara.Dim[j].Position[0], hit_poly_chara.Dim[j].Position[1], hit_poly_chara.Dim[j].Position[2]);
				//プレイヤーの押しだす距離
				float sub_len = radius - near_point;
				//法線方向に上で求めた距離を掛ける
				VECTOR push_vec = VScale(VNorm(sub_dir), sub_len + 1.0f);
				if (VSize(pl->GetPos()) != VSize(VAdd(pl->GetPos(), push_vec)))
				{

				}
				if (i != 6)
				{
					pl->SetPos(VAdd(pl->GetPos(), VGet(push_vec.x, 0, push_vec.z)));
				}
			}
		}
		MV1CollResultPolyDimTerminate(hit_poly_chara);
	}
	return true;
}

bool ActionCollision::MapColEnemy(EnemyManager* _enemy)
{
	std::list<Enemy*> list = _enemy->GetEnemyList();
	for (auto&& enemy : list)
	{
		float radius = enemy->GetRadius();
		//エネミーの判定カプセル
		VECTOR vcap_enemy[2] =
		{	//[0]が頭部分、[1]が足元部分
			{ VAdd(enemy->GetPos(), VGet(0.0f, enemy->GetSeg(), 0.0f))},
			{ VAdd(enemy->GetPos(), VGet(0.0f, enemy->GetRadius(), 0.0f))},
		};
		for (int i = 0; i < 17; i++)
		{
			MV1_COLL_RESULT_POLY_DIM hit_poly_chara;
			hit_poly_chara = MV1CollCheck_Capsule(mStageModel, i, vcap_enemy[0], vcap_enemy[1], radius);
			if (hit_poly_chara.HitNum >= 1)
			{
				const int hit_num = hit_poly_chara.HitNum;
				int j = 0;
				// 当たったポリゴンの数だけ繰り返し
				for (j = 0; j < hit_num; j++)
				{
					//線分と三角形の最近点二つもらう
					tagSEGMENT_TRIANGLE_RESULT result;
					Segment_Triangle_Analyse(&vcap_enemy[0], &vcap_enemy[1], &hit_poly_chara.Dim[j].Position[0], &hit_poly_chara.Dim[j].Position[1], &hit_poly_chara.Dim[j].Position[2], &result);
					//ベクトルの引き算で押し出す角度を取る
					VECTOR sub_dir = VSub(result.Seg_MinDist_Pos, result.Tri_MinDist_Pos);
					//線分と三角形の最近点間
					float near_point = Segment_Triangle_MinLength(vcap_enemy[0], vcap_enemy[1], hit_poly_chara.Dim[j].Position[0], hit_poly_chara.Dim[j].Position[1], hit_poly_chara.Dim[j].Position[2]);
					//プレイヤーの押しだす距離
					float sub_len = radius - near_point;
					//法線方向に上で求めた距離を掛ける
					VECTOR push_vec = VScale(VNorm(sub_dir), sub_len);
					if (VSize(enemy->GetPos()) != VSize(VAdd(enemy->GetPos(), push_vec)))
					{

					}
					if (i != 6)
					{
						enemy->SetPos(VAdd(enemy->GetPos(), VGet(push_vec.x, 0, push_vec.z)));
					}
				}
			}
			MV1CollResultPolyDimTerminate(hit_poly_chara);
		}
	}
	
	return true;
}

bool ActionCollision::MapColProcess(Player* pl, EnemyManager* _enemy)
{
	
	MapColPlayer(pl);
	//MapColEnemy(_enemy);
	return true;
}

bool ActionCollision::PtoEColProcess(Player* pl, EnemyManager* _enemy)
{
	//最短距離初期化
	float distCaptoCap = 0.f;
	float distCaptoWeapon = 0.f;
	float weapon_rad = 50.f;
	int frame = 0.f;
	int cnt = pl->GetAttackManager()->GetAttackCount();
	int max = pl->GetAttackManager()->GetMaxCount();
	int old_attack_id = -1;
	std::list<Enemy*> list = _enemy->GetEnemyList();
	//各カプセルの最短線の端点と線分長さの割合は入っていなくても問題ないので0にする
	VECTOR p1 = VGet(0, 0, 0);
	VECTOR p2 = VGet(0, 0, 0);
	float t1 = 0;
	float t2 = 0;
	//プレイヤーの判定カプセル
	VECTOR vcap_player[2] =
	{	
		//[0]が頭部分、[1]が足元部分
		{ VAdd(pl->GetPos(), VGet(0.0f, pl->GetSeg() , 0.0f))},
		{ VAdd(pl->GetPos(), VGet(0.0f, pl->GetRadius(), 0.0f))},
	};
	//武器判定
	VECTOR vcap_pl_weapon[2] =
	{
		{pl->GetWeaponPos(0)},
		{pl->GetWeaponPos(1)},
	};
	for (auto&& enemy : list)
	{
		//エネミーの判定カプセル
		VECTOR vcap_enemy[2] =
		{	//[0]が頭部分、[1]が足元部分
			{ VAdd(enemy->GetPos(), VGet(0.0f, enemy->GetSeg(), 0.0f))},
			{ VAdd(enemy->GetPos(), VGet(0.0f, enemy->GetRadius(), 0.0f))},
		};
		distCaptoCap = MathCollision::DisSegAndSeg(vcap_player[0], vcap_player[1], p1, t1, vcap_enemy[0], vcap_enemy[1], p2, t2);
		//カプセルの判定
		//プレイヤーと敵の移動時の押し出し判定
		//半径の合計
		float add_r_pltoen = pl->GetRadius() + enemy->GetRadius();
		//線分の最短距離よりも半径の合計が大きければ衝突している
		if (distCaptoCap <= add_r_pltoen)
		{	
			//位置の差分を計算
			VECTOR v = VSub(enemy->GetPos(), pl->GetPos());
			//差分をベクトルのサイズに変換
			float len = VSize(v);
			//合計の半径からサイズを引く
			len = add_r_pltoen - len;
			//引いた長さを正規化し、各要素にかけたあとあとエネミーの位置に加算する
			enemy->SetPos(VScale(VNorm(v), len));
		}
		//武器と敵のダメージ判定
		//カウントが攻撃判定発生時間内
		if (pl->GetAttackManager()->GetTable()->GetItem()[cnt].GetIsColAttack())
		{
			//IDを攻撃情報から取得
			mAttackID = pl->GetAttackManager()->GetTable()->GetItem()[cnt].GetAttackID();
			//攻撃中なのでtrueに
			pl->SetAttackFlag(true);
			//カプセルの最短距離の計算
			distCaptoWeapon = MathCollision::DisSegAndSeg(vcap_pl_weapon[0], vcap_pl_weapon[1], p1, t1, vcap_enemy[0], vcap_enemy[1], p2, t2);
			//武器と敵の当たり判定の半径を足す
			float add_r_weptoen = weapon_rad + enemy->GetRadius();
			//最短距離が半径より大きければ
			if (distCaptoWeapon <= add_r_weptoen)
			{
				if (mAttackID != old_attack_id)
				{
					enemy->Damage(pl->GetPos(), pl->GetAtk(), 10);
					old_attack_id = mAttackID;
				}
				
			}
		}
		else
		{
			pl->SetAttackFlag(false);
		}
		if (enemy->GetAttackFlag())
		{	//プレイヤーがダメージを負う
			if (!pl->GetAvoidFlag())
			{
				if (!pl->GetInvincible())
				{
					//敵のタイプが人型
					if (enemy->GetEnemyType() == Enemy::ENEMYTYPE::OSERO || enemy->GetEnemyType() == Enemy::ENEMYTYPE::ROMANOFF)
					{
						//敵武器判定
						VECTOR vcap_en_weapon[2] =
						{
							{enemy->GetWeaponPos(0)},
							{enemy->GetWeaponPos(1)},
						};
						//カプセルの最短距離の計算
						distCaptoWeapon = MathCollision::DisSegAndSeg(vcap_en_weapon[0], vcap_en_weapon[1], p1, t1, vcap_player[0], vcap_player[1], p2, t2);
						//武器と敵の当たり判定の半径を足す
						float add_r_weptoen = enemy->GetWeaponSize() + pl->GetRadius();
						//最短距離が半径より大きければ
						if (distCaptoWeapon <= add_r_weptoen)
						{
							//ダメージを受ける
							pl->Damage(enemy->GetPos(), enemy->GetATK());
							pl->SetInvincible(true);
						}
					}
					//敵タイプがクラブ
					if (enemy->GetEnemyType() == Enemy::ENEMYTYPE::CRAB)
					{
						if (distCaptoCap <= add_r_pltoen)
						{
							enemy->SetStatus(EN_Crab::STATUS::REST);
							pl->Damage(enemy->GetPos(), enemy->GetATK());
							pl->SetInvincible(true);
						}
					}
				}
			}
		}
	}
	return true;
}

bool ActionCollision::EntoEnColProcess(EnemyManager* _enemy)
{
	//最短距離初期化
	float _distCaptoCap = 0;
	std::list<Enemy*> list = _enemy->GetEnemyList();
	//各カプセルの最短線の端点と線分長さの割合は入っていなくても問題ないので0にする
	VECTOR p1 = VGet(0, 0, 0);
	VECTOR p2 = VGet(0, 0, 0);
	float t1 = 0;
	float t2 = 0;
	if (list.size() > 1)
	{
		for (auto&& enemy_i : list)
		{
			for (auto&& enemy_j : list)
			{
				if (enemy_i == enemy_j) { continue; }
				//エネミーの判定カプセル
				VECTOR _vcap_i[2] =
				{	//[0]が頭部分、[1]が足元部分
					{ VAdd(enemy_i->GetPos(), VGet(0.0f, enemy_i->GetSeg() , 0.0f))},
					{ VAdd(enemy_i->GetPos(), VGet(0.0f, enemy_i->GetRadius(), 0.0f))},
				};
				VECTOR _vcap_j[2] =
				{	//[0]が頭部分、[1]が足元部分
					{ VAdd(enemy_j->GetPos(), VGet(0.0f, enemy_j->GetSeg() , 0.0f))},
					{ VAdd(enemy_j->GetPos(), VGet(0.0f, enemy_j->GetRadius(), 0.0f))},
				};
				//プレイヤーと敵の移動時の押し出し判定
				_distCaptoCap = MathCollision::DisSegAndSeg(_vcap_i[0], _vcap_i[1], p1, t1, _vcap_j[0], _vcap_j[1], p2, t2);
				//半径の合計
				float add_r_pltoen = enemy_i->GetRadius() + enemy_j->GetRadius();
				//線分の最短距離よりも半径の合計が大きければ衝突している
				if (_distCaptoCap <= add_r_pltoen)
				{	//位置の差分を計算
					VECTOR v = VSub(p1, p2);
					//差分をベクトルのサイズに変換
					float len = VSize(v);
					//合計の半径からサイズを引く
					len = add_r_pltoen - len;
					//引いた長さを正規化し、各要素にかけたあとあとエネミーの位置に加算する
					enemy_i->SetPos(VScale(VNorm(v), len));
				}
			}
		}
	}
	return true;
}

bool ActionCollision::DivineColCircle(VECTOR p_pos, float p_r, VECTOR e_pos, float e_r)
{
	//合計半径を出す
	float add_radius = p_r + e_r;
	//線分と線分の最短距離を出す
	mDisDivinetoCap = VSize(VSub(p_pos, e_pos));
	//距離が合計半径より小さい
	if (mDisDivinetoCap <= add_radius)
	{
		return true;
	}
	return false;
}

bool ActionCollision::DivineColBreath(VECTOR p_pos, VECTOR p_fvec, VECTOR e_pos, float cos)
{
	float size = 500;
	float len = VSize(VSub(e_pos, p_pos));
	//方向ベクトルのためにマトリクス作成
	MATRIX m = MGetRotY(p_fvec.y);
	//マトリクスの成分からフォワードベクトルを作成
	VECTOR fvec = VScale(VGet(m.m[2][0], m.m[2][1], m.m[2][2]), -1);
	//敵位置とプレイヤー位置の差分ベクトルを求める
	VECTOR sub_vec = VSub(e_pos, p_pos);
	if (MathCollision::CollisionPointAndFan(fvec, sub_vec, cos))
	{
		if (len <= size)
		{
			return true;
		}
	}
	return false;
}

bool ActionCollision::DivineColLaser(VECTOR p_s_pos, VECTOR p_e_pos, float p_r, VECTOR e_s_pos, VECTOR e_e_pos, float e_r)
{
	VECTOR p1 = VGet(0, 0, 0);
	VECTOR p2 = VGet(0, 0, 0);
	float t1 = 0;
	float t2 = 0;
	//合計半径を出す
	float add_radius = p_r + e_r;
	//線分と線分の最短距離を出す
	mDisDivinetoCap = MathCollision::DisSegAndSeg(p_e_pos, p_s_pos, p1, t1, e_s_pos, e_e_pos, p2, t2);
	//距離が合計半径より小さい
	if (mDisDivinetoCap <= add_radius)
	{
		return true;
	}
	return false;
}

bool ActionCollision::DivineColSlash(VECTOR p_pos, float p_r, VECTOR e_pos, float e_r)
{
	//合計半径を出す
	float add_radius = p_r + e_r;
	//線分と線分の最短距離を出す
	mDisDivinetoCap = VSize(VSub(p_pos, e_pos));
	//距離が合計半径より小さい
	if (mDisDivinetoCap <= add_radius)
	{
		return true;
	}
	return false;
}

bool ActionCollision::DivineColExplosion(VECTOR p_s_pos, VECTOR p_e_pos, float p_r, VECTOR e_s_pos, VECTOR e_e_pos, float e_r)
{
	VECTOR p1 = VGet(0, 0, 0);
	VECTOR p2 = VGet(0, 0, 0);
	float t1 = 0;
	float t2 = 0;
	//合計半径を出す
	float add_radius = p_r + e_r;
	//線分と線分の最短距離を出す
	mDisDivinetoCap = MathCollision::DisSegAndSeg(p_s_pos, p_e_pos, p1, t1, e_s_pos, e_e_pos, p2, t2);
	if (mDisDivinetoCap <= add_radius)
	{
		return true;
	}
	return false;
}

bool ActionCollision::DivineColDash(VECTOR p_s_pos, VECTOR p_e_pos, float p_r, VECTOR e_s_pos, VECTOR e_e_pos, float e_r)
{
	VECTOR p1 = VGet(0, 0, 0);
	VECTOR p2 = VGet(0, 0, 0);
	float t1 = 0;
	float t2 = 0;
	//合計半径を出す
	float add_radius = p_r + e_r;
	//線分と線分の最短距離を出す
	mDisDivinetoCap = MathCollision::DisSegAndSeg(p_s_pos, p_e_pos, p1, t1, e_s_pos, e_e_pos, p2, t2);
	if (mDisDivinetoCap <= add_radius)
	{
		return true;
	}
	return false;
}

bool ActionCollision::DivineColVacuum(VECTOR p_pos, VECTOR p_fvec, VECTOR e_pos, float cos)
{
	float size = 700;
	float len = VSize(VSub(e_pos, p_pos));
	//方向ベクトルのためにマトリクス作成
	MATRIX m = MGetRotY(p_fvec.y);
	//マトリクスの成分からフォワードベクトルを作成
	VECTOR fvec = VScale(VGet(m.m[2][0], m.m[2][1], m.m[2][2]), -1);
	//敵位置とプレイヤー位置の差分ベクトルを求める
	VECTOR sub_vec = VSub(e_pos, p_pos);
	if (MathCollision::CollisionPointAndFan(fvec, sub_vec, cos))
	{
		if (len <= size)
		{
			return true;
		}
	}
	return false;
}

bool ActionCollision::DivineColSonic(VECTOR p_pos, float p_r, VECTOR e_pos, float e_r)
{
	//合計半径を出す
	float add_radius = p_r + e_r;
	//線分と線分の最短距離を出す
	mDisDivinetoCap = VSize(VSub(p_pos, e_pos));
	//距離が合計半径より小さい
	if (mDisDivinetoCap <= add_radius)
	{
		return true;
	}
	return false;
}

bool ActionCollision::DivineColProcess(Player* pl, EnemyManager* _enemy)
{
	//プレイヤー用当たり判定カプセル
	VECTOR cap[2] =
	{
		{0,0,0},
		{0,0,0},
	};
	//ローカルのコンテナ
	std::list<Enemy*> _list = _enemy->GetEnemyList();
	//判定用ローカル変数
	bool iscol = false;
	int frame = 20;
	int attack = 0;
	//コンテナのエネミーの数だけ範囲for文を回す
	for (auto&& enemy : _list)
	{
		//エネミー用当たり判定カプセル
		VECTOR encap[2] =
		{
			enemy->GetPos(),
			VAdd(enemy->GetPos(),VGet(0,enemy->GetSeg(),0)),
		};
		//総スキル数分繰り返す
		for (auto i = 0; i < MAX_SKILL_NUM; i++)
		{
			if (pl->GetDivine()->GetSkill(i).colCnt >= pl->GetDivine()->GetSkill(i).startColFrame && pl->GetDivine()->GetSkill(i).colCnt <= pl->GetDivine()->GetSkill(i).endColFrame)
			{
				//各スキルで処理を変更
				switch (pl->GetDivine()->GetSkill(i).skillName)
				{
				//ブレス
				case Divine::SKILLNAME::BREATH:
					cap[0] = pl->GetPos();
					iscol = DivineColBreath(cap[0], pl->GetDir(), encap[0], 30);
					attack = pl->GetDivine()->GetSkill(i).atkPoint;
					break;
				//サークル
				case Divine::SKILLNAME::CIRCLE:
					//プレイヤーの位置
					cap[0] = pl->GetPos();
					iscol = DivineColCircle(cap[0], pl->GetDivine()->GetSkill(i).size, encap[0], enemy->GetRadius());
					attack = pl->GetDivine()->GetSkill(i).atkPoint;
					break;
				//レーザー
				case Divine::SKILLNAME::LASER:
					//プレイヤーの位置
					cap[0] = pl->GetPos();
					//設定しておいたスキルの位置
					cap[1] = pl->GetDivine()->GetSkill(i).vPos;
					iscol = DivineColLaser(cap[0], cap[1], pl->GetDivine()->GetSkill(i).size, encap[0], encap[1], enemy->GetRadius());
					attack = pl->GetDivine()->GetSkill(i).atkPoint;
					break;
				//スラッシュ
				case Divine::SKILLNAME::SLASH:
					//プレイヤーの位置
					cap[0] = pl->GetPos();
					iscol = DivineColSlash(cap[0], pl->GetDivine()->GetSkill(i).size, encap[0], enemy->GetRadius());
					attack = pl->GetDivine()->GetSkill(i).atkPoint;
					break;
				//エクスプロージョン
				case Divine::SKILLNAME::EXPLOSION:
					//設定していたスキルの位置
					cap[0] = pl->GetDivine()->GetSkill(i).vPos;
					cap[1] = pl->GetDivine()->GetSkill(i).vPos;
					iscol = DivineColExplosion(cap[0], cap[1], pl->GetDivine()->GetSkill(i).size, encap[0], encap[1], enemy->GetRadius());;
					attack = pl->GetDivine()->GetSkill(i).atkPoint;
					break;
				//ダッシュ
				case Divine::SKILLNAME::DASH:
					//プレイヤーの位置
					cap[0] = pl->GetPos();
					//身長を足して縦カプセルに
					cap[1] = VAdd(pl->GetPos(), VGet(0, pl->GetSeg(), 0));
					//線分の最短距離を出す
					iscol = DivineColDash(cap[0], cap[1], pl->GetDivine()->GetSkill(i).size, encap[0], encap[1], enemy->GetRadius());
					attack = pl->GetDivine()->GetSkill(i).atkPoint;
					break;
				//バキューム
				case Divine::SKILLNAME::VACUUM:
					cap[0] = pl->GetDivine()->GetSkill(i).vPos;
					iscol = DivineColVacuum(cap[0], pl->GetDir(), encap[0], 30);
					attack = pl->GetDivine()->GetSkill(i).atkPoint;
					break;
				//ソニックウェーブ
				case Divine::SKILLNAME::SONIC:
					//プレイヤーの位置
					cap[0] = pl->GetPos();
					//プレイヤーの敵の距離を出す
					iscol = DivineColSonic(cap[0], pl->GetDivine()->GetSkill(i).size, encap[0], enemy->GetRadius());
					attack = pl->GetDivine()->GetSkill(i).atkPoint;
					break;
				}
				//当たっている
				if (iscol)
				{
					if (pl->GetDivine()->GetSkill(i).skillName == Divine::SKILLNAME::VACUUM)
					{
						enemy->Suction(cap[0], 20);
					}
					else
					{
						//ダメージを負う
						enemy->Damage(cap[0], attack, 20);
					}
				}
			}
		}
	}
	return true;
}


bool ActionCollision::ActionColProcess(Player* pl, EnemyManager* _enemy)
{
	PtoEColProcess(pl, _enemy);
	EntoEnColProcess(_enemy);
	return true;
}

bool ActionCollision::Process(Player* pl, EnemyManager* _enemy)
{
	ActionColProcess(pl, _enemy);
	DivineColProcess(pl, _enemy);
	MapColProcess(pl, _enemy);
	return true;
}

bool ActionCollision::Debug(Player* pl) 
{
	clsDx();
	printfDx("%f",pl->GetDivine()->GetSkill(2).vPos.z);
	return false;
}