#include "appframe.h"
#include <string>
#include "SoundItem.h"
#include "ApplicationGlobal.h"


// ���[�h
class ModeSound : public ModeBase
{
	typedef ModeBase base;

public:
	virtual bool Initialize();
	virtual bool Terminate();
	virtual bool Process();
	virtual bool Render();

protected:



};



