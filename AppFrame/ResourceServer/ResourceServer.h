#pragma once
#include	<unordered_map>
#include <string>

// ���\�[�X�Ǘ��T�[�o
// ���ׂĐÓI�����o�ō\������
class ResourceServer {
public:
	static void	Init();
	static void	Release();

	static void	ClearGraph();
	static int	LoadGraph(const TCHAR* FileName);
	static int	LoadDivGraph(const TCHAR* FileName, int AllNum,
		int XNum, int YNum,
		int XSize, int YSize, int* HandleBuf);
	static int LoadModel(const TCHAR* FileName);

	static int	LoadSoundMem(const TCHAR* FileName);

	static void DeleteGraph(int GraphHandle);
	static void DeleteModel(int ModelHandle);

 private:
	 static std::unordered_map<std::string, int>	_mapGraph;
	typedef struct {
		int		AllNum;
		int* handle;
	} DIVGRAPH;
	static std::unordered_map<std::string, DIVGRAPH>	_mapDivGraph;
	// _mapModel�Ɋւ��Ă̓��f���̃n���h�����g���܂킹�邩�A�������i���f���̕ێ��ɂ�胁�������������ꂽ�肷��悤�ł���Γs�x�l����j
	static std::unordered_map<std::string, int> _mapModel;

	static std::unordered_map<std::string, int>	_mapSound;
};

