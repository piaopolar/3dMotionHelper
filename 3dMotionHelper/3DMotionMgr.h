#pragma once

#include <map>
#include <string>
#include <vector>

#include "BaseCode/Singleton.h"

class C3DMotionMgr : public Singleton<C3DMotionMgr>
{
public:
	C3DMotionMgr(void);
	~C3DMotionMgr(void);

	void LoadPathInfo(const char *pszFile, OUT std::map<int, std::vector<std::string>>& rMapPath);
	void SetPath(const char *pszPath);
	bool Ana(const char *pszFile);
	bool AddActType(int nActType);
	bool Add2Dest3DMotion(int nMount, int nLook, int nWeapon, int nActionType);
	bool Save3DMotionIni(std::string strFilePath, const std::map<__int64, std::string> &mapData);
private:
	bool IsMonster(int nLook) const;
private:
	std::string m_strOrgEnv;
	std::map<__int64, std::string> m_mapOrg3DMotion;
	std::map<__int64, std::string> m_mapDest3DMotion;
	std::map<int, int> m_mapAct;
	std::map<int, int> m_mapWeapon;
	std::map<int, int> m_mapLook;
	std::map<int, int> m_mapMount;
	std::map<int, std::vector<std::string>> m_mapWeaponTrans;
	std::map<int, std::vector<std::string>> m_mapActTypeTrans;
};
