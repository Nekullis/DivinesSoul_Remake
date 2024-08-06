#include "JsonUtility.h"

JsonUtility::JsonUtility() {
	json = nullptr;
	// jsonstring = nullptr;
}

JsonUtility::~JsonUtility() {

}

nlohmann::json JsonUtility::Import(const std::string& filepath) {
	std::ifstream file(filepath);
	file >> json;
	return json;
}

void JsonUtility::strWrite(const std::string& jdata) {
	// �N���X����json�f�[�^�ɏ�������
	// Init();���K�v�Ƃ���Όʂ�
	json = nlohmann::json::parse(jdata);
}

void JsonUtility::Save(const std::string& filepath) {
	std::ofstream file(filepath);
	file << std::setw(3) << json << std::endl;
}

