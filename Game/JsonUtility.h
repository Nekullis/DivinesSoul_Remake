#pragma once
#include "nlohmann/json.hpp"
#include <fstream>

class JsonUtility
{
public:
	JsonUtility();
	virtual ~JsonUtility();

	void Init() { json = nullptr; }
	// 読み込み・書き込み
	// このクラスのjsonデータに外部のjsonファイルを読み込み 
	nlohmann::json Import(const std::string& filepath); 
	// jsonデータの中の一要素を指定したメンバ変数に代入
	template <typename T>
	void Read(const std::string& jmem, T &mem);

	// 他のクラスで変更されたデータをこのクラスで保持しているjsonデータに上書きもしくは追加する
	// std::string jdata = R"({ ~通常のjsonファイルの記述~ })"; 　　をつくって記述する
	void strWrite(const std::string& jdata);  
	template <typename T>
	// このクラスで保有しているjsonファイルに一要素を上書きもしくは追加
	void jsonWrite(const std::string& name, const T& variable); 
	void Save(const std::string& filename);
	// Importで直接、外のjson型のデータに渡したくなかったらこちらを使ってください
	nlohmann::json Getjson() { return json; }  
protected:
	// 情報を保持するためのファイル(読み書き出し兼用なのでセーブする前に読みだして置きたいデータがあれば別に移しておく)
	nlohmann::json json; 

};

template <typename T>
void JsonUtility::jsonWrite(const std::string& name, const T& variable) {
	// このクラスで保有しているjsonファイルに要素を上書きもしくは追加
	json[name] = variable;
}

template <typename T>
void JsonUtility::Read(const std::string& jmem,  T &mem) {
	// このクラスで保有しているjsonファイルにからjmemと同名のデータを渡す
	json.at(jmem).get_to(mem);
}