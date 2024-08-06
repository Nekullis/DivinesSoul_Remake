#include "DivineManager.h"

DivineManager::DivineManager()
{
	mTable.clear();
}

DivineManager::~DivineManager()
{
}

void DivineManager::AddTable(DivineTable* table)
{
	int num = static_cast<int>(table->GetItem()[0].GetName());
	mTable[num] = table;
}

void DivineManager::LoadDivine(DIVINENAME name)
{
}

void DivineManager::Invocation(kindDivine divine)
{
	int i = static_cast<int>(divine);
	if (mTable[i]->GetInvocationFlag())
	{
		//”­“®’†‚©‚Ç‚¤‚©‚ðtrue‚É
		mTable[i]->SetPlaying(true);
		//ƒXƒLƒ‹”­“®‰Â”\‚©‚Ç‚¤‚©‚ðfalse‚É
		mTable[i]->SetInvocationFlag(false);
	}
}

void DivineManager::Reset()
{
}

void DivineManager::Process()
{
	for (auto&& table : mTable)
	{
		table.second->Process();
	}
}

void DivineManager::Render()
{
	for (auto&& table : mTable)
	{
		table.second->Render();
	}
}
