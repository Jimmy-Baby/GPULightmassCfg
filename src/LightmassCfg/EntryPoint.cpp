#include "LightmassCfg.h"

#include <Windows.h>
#include <iostream>

int main(int Argc, char* Argv[])
{
	while (true)
	{
		puts("Welcome to Unreal GPULightmass Configurator!");
		puts("Enter your version number, excluding patch number. e.g. '4.27' is ok, '4.27.2' is NOT ok.");

		std::string VersionString;
		std::cin >> VersionString;

		LightmassCfg::UnrealVersion = VersionString;

		puts("Enter your desired quality setting, options are: Preview, Low, Medium, High, Production.");
		std::string QualityString;
		std::cin >> QualityString;

		if (!LightmassCfg::SetQualitySettings(QualityString))
		{
			puts("Failed to set quality settings");
		}
		else
		{
			puts("Quality set!");
		}

		Sleep(2000);
	}

	return 0;
}
