#pragma once
#include "AppFrame.h"
#include "JsonUtility.h"

// �ŏI�I�ɂ�json�f�[�^�ł܂Ƃ߂��摜�̃A�h���X���܂Ƃ߂ēǂݍ��߂�悤�ɂ����� ���@json�f�[�^�Łh�����Ō��߂��L�[�h�Ɓh�I�u�W�F�N�g�̎��,�t�@�C���p�X�h�ł܂Ƃ߂��f�[�^������Ă������x�ǂݍ��ށi���̓s�x�ŕK�v�ƂȂ�f�[�^���j
// ���f���Ɋւ��Ă͓������̂�����ێ������񂪑����̂ŁA�T�E���h�̂悤�ɓƎ��N���X�ɂ��邩��
// objectType {environment , object ,character}�@�I�u�W�F�N�g�}�l�[�W���[�ɂ��邩�͗v�l�� ->���
// ���@���̃N���X�ɃI�u�W�F�N�g�T�[�o�[���������Ă����ŊǗ�����iattach_time, attach_index�������������������j
// IsStatic{static , dynamic}


enum class Object {
	NONE = 0, GRAPH, DIVGRAPH, MOVIE, MODEL, EFFECT
};

enum class Attribute {
	NONE, ENVIRONMENT, STRUCTURE, CHARACTER, IMAGE, MOVIE
};

// �����ObjectJson���̍��ڂɏ�����
// RN = ResourceName = std::string
// RT = ResourceType = Object
// RH = ResourceHandle,�������ɓǂݍ��񂾑f�ނ̃n���h�� = int
// AB = Attribute = Attribute
// IS  = IsStatic = bool
// AN = AnimationName = std::string
// AI  = AnimationIndex = int
// AT = AnimationTime = float
// AS = AnimationSpeed = float
enum class Reference {
	RN, RT, RH, AB, IS, AN, AI, AT, AS
};


struct BASIC_INFO {
	std::string _filepath;
	Object TYPE;
	Attribute ASSIST;
};

struct GRAPH_INFO {
	int _handle;
	Object INFO;
	Attribute  COMMON;
};

struct MODEL_INFO {
	int _handle;
	Object INFO;
	Attribute  COMMON;
};

struct ATTACH_INFO {
	int _attach_index;
	float _attach_time, _attach_speed;
};

struct EFFECT_INFO {
	std::string _filepath;
	Object INFO;
	// Attribute COMMON; ��������ۗ�
};

struct DIVGRAPH_INFO {
	int	div[5];
	int* handle;
	Object INFO;
};

class ResourceServer{
public:
	ResourceServer();
	virtual ~ResourceServer();

	// �}�b�v�z��̒��g������
	void mClearAll();
	void mClearJson();
	void mClearGraph();
	void mClearDivGraph();
	void mClearModel();
	void mClearEffect();

	// json�f�[�^���}�b�v�z��ɃC���|�[�g
	bool JsonToJMap(const std::string& filepath);

	// jsonImport�ɂ���f�[�^���e�z��Ɉړ���Amapjson����ɂ���
	void JMapToArray();
	
	// �w�肵��Json�t�@�C���̃f�[�^�Ɋ܂܂�Ă���I�u�W�F�N�g���e�}�b�v�z�񂩂�폜����
	void ExcludeObject_map(const std::string& filepath);

	// Jsonmap����w��̗v�f���e�z��ɒǉ�
	bool Add(const std::string& key);

	// �e�z�񂩂�w��̗v�f���폜
	bool Delete(const std::string& key);

protected:	
	std::unordered_map<std::string, BASIC_INFO> _mapJsonImport; 
	std::unordered_map<std::string, BASIC_INFO> _mapAdd;// �X�ɒǉ�����v�f�p��Json�z��
	std::unordered_map<std::string, BASIC_INFO> _mapDel;// �폜����悤�̂�Json�z��
	std::unordered_map<std::string, GRAPH_INFO>	_mapGraph; // movie�������Ƀn���h��������
	std::unordered_map<std::string, DIVGRAPH_INFO>	_mapDivGraph;// divgraph�Ɋւ��Ă͍���͎g�������݂������̂Ō�񂵁i�����̐��Ȃǁj
	
	std::unordered_map<std::string, MODEL_INFO> _mapModel;  // �ꉞ���u���̔z�񁨐�p�̃T�[�o�[���ŊǗ����邩��
	std::unordered_map<std::string, EFFECT_INFO> _mapEffect;   // �ꉞ���u���̔z�񁨐�p�̃T�[�o�[���ŊǗ����邩��
	std::unordered_map<std::string, ATTACH_INFO> _mapModelAttach;
	// �ꉞ���u���̔z�񁨐�p�̃T�[�o�[���ŊǗ����邩��---��p�T�[�o�[�������ۂɂ̓I�u�W�F�N�g���Ƃɏ������ɂ���[��_mapModelAttach

public:	

	Object GetTNone() { return Object::NONE; } Object GetTGraph() { return Object::GRAPH; } 	Object GetTDiv() { return Object::DIVGRAPH; } 	Object GetTModel() { return Object::MODEL; } 	Object GetTEffect() { return Object::EFFECT; }

	Attribute GetANone() { return Attribute::NONE; } Attribute GetAEnvi() { return Attribute::ENVIRONMENT; } Attribute GetAStruc() { return Attribute::STRUCTURE; } Attribute GetAChara() { return Attribute::CHARACTER; }
	Attribute GetAImage() { return Attribute::IMAGE; } Attribute GetAMovie() { return Attribute::MOVIE; }

	Reference GetRRN() { return Reference::RN; } Reference GetRRT() { return Reference::RT; } Reference GetRRH() { return Reference::RH; }Reference GetRAB() { return Reference::AB; } Reference GetRIS() { return Reference::IS; } 
	Reference GetRAN() { return Reference::AN; } Reference GetRAI() { return Reference::AI; } Reference GetRAT() { return Reference::AT; } Reference GetRAS() { return Reference::AS; }

	std::unordered_map<std::string, GRAPH_INFO> mGetGraph() { return _mapGraph; }
	std::unordered_map<std::string, DIVGRAPH_INFO>	mGetDivGraph() { return _mapDivGraph; }
	std::unordered_map<std::string, MODEL_INFO> mGetModel() { return _mapModel; }
	std::unordered_map<std::string, EFFECT_INFO> mGetEffect() { return _mapEffect; }
	std::unordered_map<std::string, ATTACH_INFO> mGetAttach() { return _mapModelAttach; }

	// map�z��Ɏw�肵���L�[���^�C�v�̃I�u�W�F�N�g�����݂��邩�m�F����
// �Ԃ�l�̓T�[�o�[���݂��Ȃ� = -1, graph = 1, divgraph= 2, model = 3, effect = 4,
	int SearchInArray(const std::string& key, const Object TYPE);

	// ResourceServer���̃I�u�W�F�N�g�̎Q�Ƃ������l�������Ă���
	// TYPE = Object::NONE�ɂ����ꍇ�̓��f���ɃA�^�b�`�������[�V�����̌����ɂȂ�
	//template <typename T>
	//T GetRef(std::string& key, Object TYPE, Reference ELEMENT);
};



//
//template <typename T> // DivGraph�͂�������ۗ�
//T ResourceServer::GetRef(std::string& key, Object TYPE, Reference ELEMENT) {
//	if (TYPE != Object::NONE) {
//		if (ELEMENT == Reference::AN || ELEMENT == Reference::AI || ELEMENT == Reference::AT || ELEMENT == Reference::AS) {
//			return -1;
//		}
//		switch (SearchInArray(key, TYPE)) {
//		case 1: {
//			auto itr = _mapGraph.find(key);
//			switch (ELEMENT) {
//			case RN: {
//				return key;
//				break;
//			}
//			case RT: {
//				std::string rType = itr->second.INFO;
//				return rType;
//				break;
//			}
//			case RH: {
//				int handle = itr->second._handle;
//				return handle;
//				break;
//			}
//			case AB: {
//				Object common = itr->second.COMMON;
//				return common;
//				break;
//			}
//			}
//			break;
//		}
//		case 2: {
//			auto itr = _mapDivGraph.find(key);
//			//switch (ELEMENT) {
//			//case RN: {
//			//	return key;
//			//	break;
//			//}
//			//case RT: {
//			//	std::string rType = itr->second.INFO;
//			//	return rType;
//			//	break;
//			//}
//			//case RH: {
//			//	int handle = itr->second._handle;
//			//	return handle;
//			//	break;
//			//}
//			//case AB: {
//			//	Object common = itr->second.COMMON;
//			//	return common;
//			//	break;
//			//}
//			//}
//			break;
//		}
//		case 3: {
//			auto itr = _mapModel.find(key);
//			auto attach_itr = _mapModelAttach(key);
//			switch (ELEMENT) {
//			case RN: {
//				return key;
//				break;
//			}
//			case RT: {
//				std::string rType = itr->second.INFO;
//				return rType;
//				break;
//			}
//			case RH: {
//				int handle = itr->second._handle;
//				return handle;
//				break;
//			}
//			case AB: {
//				Object common = itr->second.COMMON;
//				return common;
//				break;
//			}
//			}
//			break;
//		}
//		case 4: {
//			auto itr = _mapEffect.find(key);
//			switch (ELEMENT) {
//			case RN: {
//				return key;
//				break;
//			}
//			case RT: {
//				std::string rType = itr->second.INFO;
//				return rType;
//				break;
//			}
//			case RH: {
//				std::string filepath = itr->second._filepath;
//				return filepath;
//				break;
//			}
//			//case AB: {
//			//	Object common = itr->second.COMMON;
//			//	return common;
//			//	break;
//			//}
//			}
//			break;
//		}
//		case -1: {
//			return -1;
//			break;
//		}
//		}
//	}
//	else {
//		if (ELEMENT == Reference::AN && ELEMENT == Reference::AI && ELEMENT == Reference::AT && ELEMENT == Reference::AS) {
//			return -1;
//		}
//		auto itr = _mapModelAttach(key);
//		switch (ELEMENT) {
//		case IS: {
//			if (itr != _mapModelAttach.end()) {
//				return true;
//			}
//			else {
//				return false;
//			}
//			break;
//		}
//		case AN: {
//			return key;
//			break;
//		}
//		case AI: {
//			int index = itr->second._attach_index;
//			return  index;
//			break;
//		}
//		case AT: {
//			float time = itr->second._attach_time;
//			return time;
//			break;
//		}
//		case AS: {
//			float speed = itr->second._attach_speed;
//			return speed;
//			break;
//		}		
//		}
//	}
//}