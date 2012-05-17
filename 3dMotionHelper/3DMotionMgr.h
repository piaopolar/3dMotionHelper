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

	void LoadPathInfo(const char *pszFile, OUT std::map<int, std::vector<std::string>>& rMapPath, bool bAddSelf = true);
	void SetPath(const char *pszPath);
	bool Ana(const char *pszFile);
	bool AddActType(int nActType);
	bool AddMonsterType(int nMonsterType);
	bool AddMountType(int nMountType);
	bool AddWeaponType(int nWeaponType);
	bool Add2Dest3DMotion(int nMount, int nLook, int nWeapon, int nActionType);
	bool Add2Dest3DMotionSingle(int nMountWidthLev, int nLook, int nWeapon, int nActionType);
	bool Save3DMotionIni(std::string strFilePath, const std::map<__int64, std::string> &mapData);
	void ResetDestMotion(void);
private:
	bool IsMonster(int nLook) const;
	bool IsMountLevAction(int nActType) const;
	std::string GetMountLevActionFileName(int nMountLev, int nActType) const;
private:
	std::string m_strOrgEnv;
	std::map<__int64, std::string> m_mapOrg3DMotion;
	std::map<__int64, std::string> m_mapDest3DMotion;
	std::map<int, int> m_mapAct;
	std::map<int, int> m_mapWeapon;
	std::map<int, int> m_mapLook;
	std::map<int, int> m_mapMount;
	std::map<int, std::vector<std::string>> m_mapLookTrans;
	std::map<int, std::vector<std::string>> m_mapWeaponTrans;
	std::map<int, std::vector<std::string>> m_mapActTypeTrans;
	std::map<int, std::vector<std::string>> m_mapMountTypeTrans;
};
