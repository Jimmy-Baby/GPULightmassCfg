#include "LightmassCfg.h"

#include <Windows.h>

namespace LightmassCfg
{
	std::string UnrealVersion;

	struct LightmassCfgSettings
	{
		char PrimaryGiSamples[8];
		char SecondaryGiSamples[8];
	};

	LightmassCfgSettings PreviewCfg
	{
		"16",
		"8"
	};

	LightmassCfgSettings LowCfg
	{
		"32",
		"16"
	};

	LightmassCfgSettings MediumCfg
	{
		"64",
		"16"
	};

	LightmassCfgSettings HighCfg
	{
		"128",
		"32"
	};

	LightmassCfgSettings ProductionCfg
	{
		"256",
		"64"
	};

	bool GetUnrealInstallDirectory(const std::string& VersionString, std::string& DirectoryOut)
	{
		std::string KeyName = R"(Software\EpicGames\Unreal Engine\)";
		KeyName += VersionString;

		HKEY Key;
		if (const LSTATUS Result = RegOpenKeyExA(HKEY_LOCAL_MACHINE, KeyName.c_str(), NULL, KEY_READ, &Key);
			Result != ERROR_SUCCESS)
		{
			return false;
		}

		DWORD Type = REG_SZ;
		char Value[1024] = "";
		DWORD ValueSize = sizeof Value;
		if (const LSTATUS Result = RegQueryValueExA(Key, "InstalledDirectory", nullptr, &Type, reinterpret_cast<LPBYTE>(&Value), &ValueSize);
			Result != ERROR_SUCCESS)
		{
			return false;
		}

		DirectoryOut = Value;
		return true;
	}

	bool SetQualitySettings(const std::string& Quality)
	{
		LightmassCfgSettings* Settings;

		if (Quality == "Preview")
		{
			Settings = &PreviewCfg;
		}
		else if (Quality == "Low")
		{
			Settings = &LowCfg;
		}
		else if (Quality == "Medium")
		{
			Settings = &MediumCfg;
		}
		else if (Quality == "High")
		{
			Settings = &HighCfg;
		}
		else if (Quality == "Production")
		{
			Settings = &ProductionCfg;
		}
		else
		{
			return false;
		}

		std::string Directory;
		if (!GetUnrealInstallDirectory(UnrealVersion, Directory))
		{
			return false;
		}

		const std::string IniFilePath = Directory + R"(\Engine\Config\BaseLightmass.ini)";
		WritePrivateProfileStringA("DevOptions.GPULightmass", "NumPrimaryGISamples", Settings->PrimaryGiSamples, IniFilePath.c_str());
		WritePrivateProfileStringA("DevOptions.GPULightmass", "NumSecondaryGISamples", Settings->SecondaryGiSamples, IniFilePath.c_str());

		return true;
	}
}
