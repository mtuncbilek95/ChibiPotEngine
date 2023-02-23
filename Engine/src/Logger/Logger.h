#pragma once

#include <Core/CoreMinimal.h>

#define RED			"\033[0;31m"
#define GREEN		"\033[0;32m"
#define YELLOW		"\033[0;33m"
#define WHITE		"\033[0;37m"

#define CB_Success		"\033[0;32mSuccess: "
#define CB_Warning		"\033[0;33mWarning: "
#define CB_Error		"\033[0;31mError: "
#define CB_Display		"\033[0;37mDisplay: "

namespace Logger {

	enum class PrintType : byte {
		Success,
		Warning,
		Error,
		Display
	};

	//Pre-post Build events 
	static string GetShaderData(string shaderName) {
		std::filesystem::path directoryPath = std::filesystem::current_path().parent_path().parent_path().parent_path();
		string fullPath = directoryPath.generic_string() + "/Engine/src/HLSL/" + shaderName + ".hlsl";

		HANDLE fileHandle;

		bool bIsFileOk;
		DWORD countByte;

		fileHandle = CreateFileA(fullPath.c_str(), GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_ALWAYS,
			FILE_ATTRIBUTE_READONLY, nullptr);

		const DWORD fileSize = GetFileSize(fileHandle, nullptr);

		char* stringFile = new char[fileSize + 1];
		stringFile[fileSize] = { '\0' };

		try
		{
			if (bIsFileOk = ReadFile(fileHandle, stringFile, fileSize, &countByte, nullptr))
			{
				return string(stringFile);
			}
			else
			{
				throw "Unexpected file or path.";
			}
		}
		catch (const string exception)
		{
			printf("Error: %s", (char*)&exception);
			return nullptr;
		}
	}

	static string GetInitialDir()
	{
		std::filesystem::path directoryPath = std::filesystem::current_path().parent_path().parent_path().parent_path();
		string path = directoryPath.generic_string();
		return path;
	}

	static void PrintLog(PrintType type, string message) {
		string messageFinal{};

		switch (type)
		{
		case PrintType::Success:
			messageFinal += CB_Success + message + WHITE;
			break;
		case PrintType::Warning:
			messageFinal += CB_Warning + message + WHITE;
			break;
		case PrintType::Error:
			messageFinal += CB_Error + message + WHITE;
			break;
		case PrintType::Display:
			messageFinal += CB_Display + message + WHITE;
			break;
		default:
			messageFinal += WHITE + message + WHITE;
			break;
		}

		std::cout << messageFinal << std::endl;
	}
}


/*
	std::cout << argumentValue[0] << std::endl;
	Absolute Path of Exe
*/