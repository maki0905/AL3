﻿#include "Player.h"
#include <cassert>
#include <cmath>
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include "ImGuiManager.h"

//void Player::Initialize(std::vector<Model*> model) {
//	for (Model* model : model) {
//		assert(model);
//	}
//	model_ = model;
//	worldTransformBase_.Initialize();
//	worldTransformBody_.Initialize();
//	worldTransformHead_.Initialize();
//	worldTransformL_arm_.Initialize();
//	worldTransformR_arm_.Initialize();
//
//	
//	// シングルトンインスタンスを取得
//	input_ = Input::GetInstance();
//
//	InitializeFloatingGimmick();
//}

void Player::Initialize(Model* modeBody, Model* modelHead, Model* modelL_arm, Model* modelR_arm) {
	assert(modeBody);
	assert(modelHead);
	assert(modelL_arm);
	assert(modelR_arm);

	modelBody_ = modeBody;
	modelHead_ = modelHead;
	modelL_arm_ = modelL_arm;
	modelR_arm_ = modelR_arm;
	
	worldTransformBase_.Initialize();
	worldTransformBody_.Initialize();
	worldTransformHead_.Initialize();
	worldTransformL_arm_.Initialize();
	worldTransformR_arm_.Initialize();

	worldTransformBase_.translation_.y = 2.0f;
	worldTransformHead_.translation_.y = 4.4f;
	worldTransformL_arm_.translation_ = Vector3(-2.2f, 5.4f, 0.0f);
	worldTransformR_arm_.translation_ = Vector3(2.2f, 5.4f, 0.0f);

	// シングルトンインスタンスを取得
	input_ = Input::GetInstance();

	InitializeFloatingGimmick();
}

void Player::Update() {
	
	// 押した方向で移動ベクトルを変更(左右)
	if (input_->PushKey(DIK_LEFT)) {
		// 速さ
		const float speed = 0.3f;

		// 移動量
		Vector3 move = {-1.0f, 0, 0};
		
		// 移動量に速さを反映
		move = Multiply(speed, Normalize(move));

		Matrix4x4 rotate = MakeRotateYMatrix(viewProjection_->rotation_.y);

		move = Transform(move, rotate);

		// Y軸周り角度(θy)
		worldTransformBase_.rotation_.y = std::atan2(move.x, move.z);

		// 横軸方向の長さを求める
		float lenghtXZ = Length(Vector3(move.x, 0.0f, move.z));
		// X軸周りの角度(θx)
		worldTransformBase_.rotation_.x = std::atan2(-move.y, lenghtXZ);

		// 移動
		worldTransformBase_.translation_ = Add(worldTransformBase_.translation_, move);



	} else if (input_->PushKey(DIK_RIGHT)) {
		// 速さ
		const float speed = 0.3f;

		// 移動量
		Vector3 move = {1.0f, 0, 0};

		// 移動量に速さを反映
		move = Multiply(speed, Normalize(move));

		Matrix4x4 rotate = MakeRotateYMatrix(viewProjection_->rotation_.y);

		move = Transform(move, rotate);

		// Y軸周り角度(θy)
		worldTransformBase_.rotation_.y = std::atan2(move.x, move.z);

		// 横軸方向の長さを求める
		float lenghtXZ = Length(Vector3(move.x, 0.0f, move.z));
		// X軸周りの角度(θx)
		worldTransformBase_.rotation_.x = std::atan2(-move.y, lenghtXZ);

		// 移動
		worldTransformBase_.translation_ = Add(worldTransformBase_.translation_, move);
	}

	// 押した方向で移動ベクトルを変更(前後)
	if (input_->PushKey(DIK_UP)) {
		// 速さ
		const float speed = 0.3f;

		// 移動量
		Vector3 move = {0, 0, 1.0f};

		// 移動量に速さを反映
		move = Multiply(speed, Normalize(move));

		Matrix4x4 rotate = MakeRotateYMatrix(viewProjection_->rotation_.y);

		move = Transform(move, rotate);

		// Y軸周り角度(θy)
		worldTransformBase_.rotation_.y = std::atan2(move.x, move.z);

		// 横軸方向の長さを求める
		float lenghtXZ = Length(Vector3(move.x, 0.0f, move.z));
		// X軸周りの角度(θx)
		worldTransformBase_.rotation_.x = std::atan2(-move.y, lenghtXZ);

		// 移動
		worldTransformBase_.translation_ = Add(worldTransformBase_.translation_, move);
	} else if (input_->PushKey(DIK_DOWN)) {
		// 速さ
		const float speed = 0.3f;

		// 移動量
		Vector3 move = {0, 0, -1.0f};

		// 移動量に速さを反映
		move = Multiply(speed, Normalize(move));

		Matrix4x4 rotate = MakeRotateYMatrix(viewProjection_->rotation_.y);

		move = Transform(move, rotate);

		// Y軸周り角度(θy)
		worldTransformBase_.rotation_.y = std::atan2(move.x, move.z);

		// 横軸方向の長さを求める
		float lenghtXZ = Length(Vector3(move.x, 0.0f, move.z));
		// X軸周りの角度(θx)
		worldTransformBase_.rotation_.x = std::atan2(-move.y, lenghtXZ);

		// 移動
		worldTransformBase_.translation_ = Add(worldTransformBase_.translation_, move);
	}

	// ゲームパッドの状態を得る変数(XINPUT)
	XINPUT_STATE joyState;
	// ジョイスティック状態取得
	if (Input::GetInstance()->GetJoystickState(0, joyState)) {
		// 速さ
		const float speed = 0.3f;

		// 移動量
		Vector3 move = {(float)joyState.Gamepad.sThumbLX, 0, (float)joyState.Gamepad.sThumbLY};

		// 移動量に速さを反映
		move = Multiply(speed, Normalize(move));

		// 移動
		worldTransformBase_.translation_ = Add(worldTransformBase_.translation_, move);

	}

	UpdateFloatingGimmick();
	Matrix4x4 worldMatrix = MakeAffineMatrix(
	    worldTransformBody_.scale_, worldTransformBody_.rotation_, worldTransformBody_.translation_);
	worldTransformBody_.matWorld_ = Multiply(worldMatrix, worldTransformBase_.matWorld_);
	worldMatrix = MakeAffineMatrix(
	    worldTransformHead_.scale_, worldTransformHead_.rotation_, worldTransformHead_.translation_);

	worldTransformHead_.matWorld_ = Multiply(worldMatrix, worldTransformBody_.matWorld_);
	worldMatrix = MakeAffineMatrix(
	    worldTransformL_arm_.scale_, worldTransformL_arm_.rotation_, worldTransformL_arm_.translation_);
	worldTransformL_arm_.matWorld_ = Multiply(worldMatrix, worldTransformBody_.matWorld_);
	worldMatrix = MakeAffineMatrix(
	    worldTransformR_arm_.scale_, worldTransformR_arm_.rotation_, worldTransformR_arm_.translation_);
	worldTransformR_arm_.matWorld_ = Multiply(worldMatrix, worldTransformBody_.matWorld_);

	// 　行列を更新
	worldTransformBase_.UpdateMatrix();
	worldTransformBody_.TransferMatrix();
	worldTransformHead_.TransferMatrix();
	worldTransformL_arm_.TransferMatrix();
	worldTransformR_arm_.TransferMatrix();
}

void Player::Draw(ViewProjection& viewProjection) { 
	modelBody_->Draw(worldTransformBody_, viewProjection);
	modelHead_->Draw(worldTransformHead_, viewProjection);
	modelL_arm_->Draw(worldTransformL_arm_, viewProjection);
	modelR_arm_->Draw(worldTransformR_arm_, viewProjection);
}

void Player::InitializeFloatingGimmick() { 
	floatingParameter_ = 0.0f;

}

void Player::UpdateFloatingGimmick() {
	// 浮遊移動のサイクル<frame>
	int period = 60;
	// 1フレームでのパラメータ加算値
	const float step = 2.0f * float(M_PI) / period;
	// パラメータを1ステップ分加算
	floatingParameter_ += step;
	// 2πを超えたらθに戻す
	floatingParameter_ = std::fmod(floatingParameter_, float(2.0f * M_PI));
	// 浮遊の振幅<m>
	float amplitude = 1.0f;
	// 浮遊を座標に反映
	worldTransformBody_.translation_.y = std::sin(floatingParameter_) * amplitude;
	worldTransformL_arm_.rotation_.x = std::sin(floatingParameter_) * (amplitude / 2.0f);
	worldTransformR_arm_.rotation_.x = std::sin(floatingParameter_) * (amplitude / 2.0f);
	ImGui::Begin("Player");
	ImGui::SliderFloat3("Head Translation", &worldTransformHead_.translation_.x, -100.0f, 100.0f);
	ImGui::SliderFloat3("ArmL Trasnlation", &worldTransformL_arm_.translation_.x, -100.0f, 100.0f);
	ImGui::SliderFloat3("ArmR Trasnlation", &worldTransformR_arm_.translation_.x, -100.0f, 100.0f);
	ImGui::SliderInt("周期", &period, 0, 120);
	ImGui::SliderFloat("浮遊の振幅", &amplitude, -2.0f, 2.0f);
	
	ImGui::End();
}
