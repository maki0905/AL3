﻿#pragma once

#include <iostream>
#include <variant>
#include <string>
#include <map>

#include "MathFunction.h"


/// <summary>
/// グローバル変数
/// </summary>
class GlobalVariables {
public:
	static GlobalVariables* GetInstance();

	/// <summary>
	/// グループの作成
	/// </summary>
	/// <param name="groupName">グループ名</param>
	void CreateGroup(const std::string& groupName);

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Updata();

	/// <summary>
	/// ファイルに書き出し
	/// </summary>
	/// <param name="GroupName">グループ</param>
	void SaveFile(const std::string& groupName);

	// 値のセット(int)
	void SetValue(const std::string& groupName, const std::string& key, int32_t value);
	// 値のセット(float)
	void SetValue(const std::string& groupName, const std::string& key, float value);
	// 値のセット(Vector3)
	void SetValue(const std::string& groupName, const std::string& key, Vector3 value);



private:
	GlobalVariables() = default;
	~GlobalVariables() = default;
	GlobalVariables(const GlobalVariables& src) = default;
	GlobalVariables& operator=(const GlobalVariables& src) = default;

	// 項目
	struct Item {
		// 項目の値
		std::variant<int32_t, float, Vector3> value;
	};

	// グループ
	struct Group {
		std::map<std::string, Item> items;
	};

	// 全データ
	std::map<std::string, Group> datas_;

	// グローバル変数の保存先ファイルパス
	const std::string kDirectoryPath = "Resources/GlobalVariables/";

};
