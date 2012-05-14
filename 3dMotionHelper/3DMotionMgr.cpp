#include "StdAfx.h"

#include "BaseCode/BaseFunc.h"

#include "3DMotionMgr.h"

// ============================================================================
// ==============================================================================

C3DMotionMgr::C3DMotionMgr(void)
{
	//~~~~~~~~~~~~~~~~~~~~~~~
	char szWorkDir[MAX_STRING];
	//~~~~~~~~~~~~~~~~~~~~~~~

	::GetCurrentDirectory(sizeof(szWorkDir), szWorkDir);

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~
	std::string strDir = szWorkDir;
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~

	LoadPathInfo((strDir + "\\ini\\WeaponTransSet.ini").c_str(), m_mapWeaponTrans);
	LoadPathInfo((strDir + "\\ini\\ActTypeTransSet.ini").c_str(), m_mapActTypeTrans);
}

// ============================================================================
// ==============================================================================
C3DMotionMgr::~C3DMotionMgr(void)
{
}

// ============================================================================
// ==============================================================================
void C3DMotionMgr::SetPath(const char *pszPath)
{
	if (NULL == pszPath) {
		return;
	}

	m_strOrgEnv = pszPath;
	FormatPath(m_strOrgEnv);

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	std::string strOrgFile = m_strOrgEnv + "ini\\3DMotion.ini";
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	this->Ana(strOrgFile.c_str());
}

// ============================================================================
// ==============================================================================
bool C3DMotionMgr::Ana(const char *pszFile)
{
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	FILE *pFile = fopen(pszFile, "r");
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	if (NULL == pFile) {
		LogInfoIn("open %s failed", pszFile);
		return false;
	}

	LogInfoIn("open %s suc", pszFile);

	//~~~~~~~~~~~~~~~~~~~~
	char szLine[MAX_STRING];
	char szPath[MAX_STRING];
	__int64 i64Index;
	int nMount;
	int nLook;
	int nWeapon;
	int nActType;
	//~~~~~~~~~~~~~~~~~~~~

	while (fgets(szLine, sizeof(szLine), pFile)) {
		if (2 == sscanf(szLine, "%I64d=%s", &i64Index, szPath)) {
			m_mapOrg3DMotion[i64Index] = szPath;
			nActType = i64Index % 10000;
			i64Index /= 10000;
			nWeapon = i64Index % 1000;
			i64Index /= 1000;
			nLook = i64Index % 1000;
			i64Index /= 1000;
			m_mapAct[nActType] = 1;
			m_mapWeapon[nWeapon] = 1;
			m_mapLook[nLook] = 1;

			if (nLook >= 1000) {
				OutputDebugString(szLine);
			}

			if (nActType != 713) {
				nMount = static_cast<int>(i64Index);
				m_mapMount[nMount] = 1;
			}
		}
	}

	LogInfoIn("%s info:\n Index %d  Mount %d Look %d Weapon %d ActType %d", pszFile, m_mapOrg3DMotion.size(),
			  m_mapMount.size(), m_mapLook.size(), m_mapWeapon.size(), m_mapAct.size());

	// m_mapDest3DMotion = m_mapOrg3DMotion;
	return true;
}

// ============================================================================
// ==============================================================================
bool C3DMotionMgr::AddActType(int nActType)
{
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	std::map<int, int>::const_iterator itMount;
	std::map<int, int>::const_iterator itLook;
	std::map<int, int>::const_iterator itWeapon;
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	for (itLook = m_mapLook.begin(); itLook != m_mapLook.end(); ++itLook) {
		if (this->IsMonster(itLook->first)) {
			this->Add2Dest3DMotion(0, itLook->first, 0, nActType);
		} else {
			for (itMount = m_mapMount.begin(); itMount != m_mapMount.end(); ++itMount) {
				for (itWeapon = m_mapWeapon.begin(); itWeapon != m_mapWeapon.end(); ++itWeapon) {
					this->Add2Dest3DMotion(itMount->first, itLook->first, itWeapon->first, nActType);
				}
			}
		}
	}

	//~~~~~~~~~~~~~~~~~~~~~~~
	char szWorkDir[MAX_STRING];
	//~~~~~~~~~~~~~~~~~~~~~~~

	::GetCurrentDirectory(sizeof(szWorkDir), szWorkDir);

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~
	std::string strDir = szWorkDir;
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~

	Save3DMotionIni((strDir + "\\test.txt").c_str(), m_mapDest3DMotion);

	return true;
}

// ============================================================================
// ==============================================================================
bool C3DMotionMgr::Add2Dest3DMotion(int nMount, int nLook, int nWeapon, int nActionType)
{
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	__int64 i64Index = (__int64) 10000000000 *
		nMount +
		(__int64) 10000000 *
		nLook +
		(__int64) 10000 *
		nWeapon +
		nActionType;
	std::string strPath;
	char szTmp[MAX_STRING];
	bool bMonster = this->IsMonster(nLook);
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	if (1030000110 == i64Index) {
		OutputDebugString("break here");
	}

	if (bMonster) {
		switch (nLook) {
		case 140:
		case 132:
			_snprintf(szTmp, sizeof(szTmp), "c3/monster/%dn/", nLook);
			break;
		default:
			_snprintf(szTmp, sizeof(szTmp), "c3/monster/%d/", nLook);
			break;
		}
	} else {
		_snprintf(szTmp, sizeof(szTmp), "c3/%d%03d/", nMount, nLook);
	}

	strPath += szTmp;

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	std::map<int, std::vector<std::string> >::const_iterator itActVec = m_mapActTypeTrans.find(nActionType);
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	if (itActVec == m_mapActTypeTrans.end()) {
		_snprintf(szTmp, sizeof(szTmp), "%03d", nActionType);
		m_mapActTypeTrans[nActionType].push_back(szTmp);
		itActVec = m_mapActTypeTrans.find(nActionType);
	}

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	std::vector<std::string>::const_iterator itActStr = itActVec->second.begin();
	std::string strFile;
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	if (!bMonster) {

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		std::map<int, std::vector<std::string> >::const_iterator itWeaponVec = m_mapWeaponTrans.find(nWeapon);
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

		if (itWeaponVec == m_mapWeaponTrans.end()) {
			_snprintf(szTmp, sizeof(szTmp), "%03d", nWeapon);
			m_mapWeaponTrans[nWeapon].push_back(szTmp);
			itWeaponVec = m_mapWeaponTrans.find(nWeapon);
		}

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		std::vector<std::string>::const_iterator itWeaponStr;
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

		for (; itActStr != itActVec->second.end(); ++itActStr) {
			for (itWeaponStr = itWeaponVec->second.begin(); itWeaponStr != itWeaponVec->second.end(); ++itWeaponStr) {
				strFile = strPath +*itWeaponStr;
				strFile += "/";
				strFile += *itActStr;
				strFile += ".c3";
				if (IsFileExist((m_strOrgEnv + strFile).c_str())) {
					m_mapDest3DMotion[i64Index] = strFile;
					return true;
				}
			}
		}
	} else {
		for (; itActStr != itActVec->second.end(); ++itActStr) {
			strFile = strPath +*itActStr;
			strFile += ".c3";
			if (IsFileExist((m_strOrgEnv + strFile).c_str())) {
				m_mapDest3DMotion[i64Index] = strFile;
				return true;
			}
		}
	}

	return false;
}

// ============================================================================
// ==============================================================================
void C3DMotionMgr::LoadPathInfo(const char *pszFile, OUT std::map<int, std::vector<std::string> > &rMapTrans)
{
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	FILE *pFile = fopen(pszFile, "r");
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	if (NULL == pFile) {
		return;
	}

	//~~~~~~~~~~~~~~~~~~~~~
	int nIndex;
	char *pPos;
	char szLine[MAX_STRING];
	char szTmp[MAX_STRING];
	char szSeps[] = " ,\t\n";
	//~~~~~~~~~~~~~~~~~~~~~

	while (fgets(szLine, sizeof(szLine), pFile)) {
		pPos = strstr(szLine, "=");
		if (NULL == pPos) {
			continue;
		}

		if (1 != sscanf(szLine, "%d", &nIndex)) {
			continue;
		}

		_snprintf(szTmp, sizeof(szTmp), "%03d", nIndex);
		rMapTrans[nIndex].push_back(szTmp);

		for (pPos = strtok(pPos + 1, szSeps); pPos; pPos = strtok(NULL, szSeps)) {
			rMapTrans[nIndex].push_back(pPos);
		}
	}

	fclose(pFile);
}

// ============================================================================
// ==============================================================================
bool C3DMotionMgr::Save3DMotionIni(std::string strFilePath, const std::map<__int64, std::string> &mapData)
{
	MyMakeSureDirectoryPathExists(strFilePath);

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	FILE *pFile = fopen(strFilePath.c_str(), "w");
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	if (NULL == pFile) {
		LogInfoIn("!!!!! create %s error", strFilePath.c_str());
		return false;
	}

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	bool b3DMotion = strstr(strFilePath.c_str(), "3dmotion.ini") ? true : false;
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	if (b3DMotion) {
		for (std::map < __int64, std::string >::const_iterator itData = mapData.begin(); itData != mapData.end();
			 ++itData) {
			if (itData->first >= 1000000000000) {
				fprintf(pFile, "%014I64d=%s\n", itData->first, itData->second.c_str());
			} else {
				fprintf(pFile, "%011I64d=%s\n", itData->first, itData->second.c_str());
			}
		}
	} else {
		for (std::map < __int64, std::string >::const_iterator itData = mapData.begin(); itData != mapData.end();
			 ++itData) {
			fprintf(pFile, "%I64d=%s\n", itData->first, itData->second.c_str());
		}
	}

	fclose(pFile);
	LogInfoIn("***** save %s ok", strFilePath.c_str());
	return true;
}

// ============================================================================
// ==============================================================================
bool C3DMotionMgr::IsMonster(int nLook) const
{
	return(nLook >= 100);
}

// ============================================================================
// ==============================================================================
bool C3DMotionMgr::AddWeaponType(int nWeaponType)
{
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	std::map<int, int>::const_iterator itMount;
	std::map<int, int>::const_iterator itLook;
	std::map<int, int>::const_iterator itActType;
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	for (itLook = m_mapLook.begin(); itLook != m_mapLook.end(); ++itLook) {
		if (this->IsMonster(itLook->first)) {
			continue;
		} else {
			for (itMount = m_mapMount.begin(); itMount != m_mapMount.end(); ++itMount) {
				for (itActType = m_mapAct.begin(); itActType != m_mapAct.end(); ++itActType) {
					this->Add2Dest3DMotion(itMount->first, itLook->first, nWeaponType, itActType->first);
				}
			}
		}
	}

	//~~~~~~~~~~~~~~~~~~~~~~~
	char szWorkDir[MAX_STRING];
	//~~~~~~~~~~~~~~~~~~~~~~~

	::GetCurrentDirectory(sizeof(szWorkDir), szWorkDir);

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~
	std::string strDir = szWorkDir;
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~

	Save3DMotionIni((strDir + "\\testWeapon.txt").c_str(), m_mapDest3DMotion);

	return true;
}
