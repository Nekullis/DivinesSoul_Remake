//----------------------------------------------------------------------
// @filename ModeTitle.h
// @author: Fukuma Kyohei
// @explanation
// �^�C�g���摜��`�悷�郂�[�h
//----------------------------------------------------------------------
class ModeTitle : public ModeBase
{
	typedef ModeBase base;
public:
	virtual bool Initialize();
	virtual bool Terminate();
	virtual bool Process();
	virtual bool Render();

protected:
	int _cg;
};

