#include <fstream>
#include <iostream>
#include "CFile.h"

// �ǂݍ���
CFile::CFile(const std::string filename) {
	// �����o�̏�����
	Init();
	_filename = filename;

	// �t�@�C�����J��
	std::ifstream ifs(filename, std::ios::in | std::ios::binary);	// ���͂��o�C�i���`����
	if (!ifs) {
		// �J���̎��s
		return;
	}

	// �t�@�C���T�C�Y�̎擾
	ifs.seekg(0, std::ios_base::end);
	_size = (int)ifs.tellg();
	ifs.seekg(0, std::ios_base::beg);

	// ���������m��
	// ������Ƃ��ė��p�ł���悤�ɁA+1byte�]�v�Ɋm��
	_data = new char[_size + 1];

	// �t�@�C�������[�h
	ifs.read(_data, _size);

	// �t�@�C�������
	ifs.close();

	// ������Ƃ��ė��p�ł���悤�ɁA�f�[�^�̖��[��\0��t����
	_data[_size] = '\0';

	// ��������
	_success = true;
}

// ��������
CFile::CFile(const std::string filename, void* data, int size) {
	// �����o�̏�����
	Init();
	_filename = filename;

	// �t�@�C�����J��
	std::ofstream ofs(filename, std::ios::out | std::ios::binary);	// �o�͂��o�C�i���`����
	if (!ofs) {
		// �J���̎��s
		return;
	}

	// �f�[�^�̏�������
	ofs.write((char*)data, size);

	// �t�@�C�������
	ofs.close();

	// ��������
	_success = true;
}

// ��������


CFile::~CFile() {
	delete _data;
	_data = nullptr;
}

void CFile::Init() {
	_size = 0;
	_data = NULL;
	_filename = "";
	_success = false;
}

// �w��̕�����������܂Ői�߂�
int FindString(const char* p, const char find, const void* last)
{
	int c = 0;
	while (p[c] != find && (!last || &p[c] < last)) { c++; }
	return c;
}

// �󔒂�R���g���[���R�[�h���X�L�b�v����
int SkipSpace(const char* p, const void* last)
{
	int c = 0;
	while (p[c] != '\0' && p[c] != '\r\n' && p[c] <= ' ' && (!last || &p[c] < last)) { c++; }
	return c;
}

// ","�܂ł̕�������擾����
// csv�p
int GetString(const char* p, std::string* out)
{
	int c = 0;
	c += GetString(p, ',', out);
	return c;
}

int GetString(const char* p, const char find, std::string* out)
{
	int c = 0;
	int len = FindString(&p[c], find, NULL);	// ","�܂ł̒����𓾂�
	std::string s(&p[c], &p[c + len]);	// �������string��
	*out = s;
	c += len;	// ","�܂Ői�߂�
	return c;
}

int GetString(const char* p, const char find, std::string* out, int maxSize)
{
	int c = 0;
	int len = FindString(&p[c], find, &p[maxSize]);	// ","�܂ł̒����𓾂�
	std::string s(&p[c], &p[c + len]);	// �������string��
	*out = s;
	c += len;	// ","�܂Ői�߂�
	return c;
}

// 10�i���̐����l���擾����
int GetDecNum(const char* p, int* answer, int* digits) {
	int c = 0;
	c += SkipSpace(&p[c], NULL);	// �󔒂��X�L�b�v

	// �}�C�i�X�l�ȂǋL�����擾
	int mul = 1;
	int dig = 1;
	if (p[c] == '-') { mul = -1; c++; }
	else if (p[c] == '+') { mul = 1; c++; }

	// 10�i�����擾����
	int n = 0;
	while ('0' <= p[c] && p[c] <= '9') {
		n = n * 10 + (p[c] - '0');
		dig *= 10;
		c++;
	}

	// �L���������ē����Ɋi�[
	*answer = n * mul;

	if (digits != nullptr) {
		*digits = dig;
	}

	// �ǂݐi�񂾕�������Ԃ�
	return c;
}

// 10�i���̕��������_�����܂߂��l���擾����
int GetFloatNum(const char* p, float* answer) {
	int c = 0;
	c += SkipSpace(&p[c], NULL);	// �󔒂��X�L�b�v

	// �}�C�i�X�l�ȂǋL�����擾
	int mul = 1;
	if (p[c] == '-') { mul = -1; c++; }
	else if (p[c] == '+') { mul = 1; c++; }

	// 10�i�����擾����
	int n = 0;
	while ('0' <= p[c] && p[c] <= '9') {
		n = n * 10 + (p[c] - '0');
		c++;
	}

	//�����_���������ꍇ�̏���
	int decimalPoint = 0;
	int digits = 1;
	if (p[c] == '.') { c++; c += GetDecNum(&p[c], &decimalPoint, &digits); }

	// �L���������ē����Ɋi�[
	*answer = (n + static_cast<float>(decimalPoint) / digits) * mul;

	// �ǂݐi�񂾕�������Ԃ�
	return c;
}