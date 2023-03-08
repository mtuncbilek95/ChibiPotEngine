#pragma once

#include <Core/CoreMinimal.h>

#define RED			"\033[0;31m"
#define GREEN		"\033[0;32m"
#define YELLOW		"\033[0;33m"
#define BLUE		"\033[0;34m"
#define CYAN		"\033[0;36m"
#define WHITE		"\033[0;37m"

#define CB_Success		"\033[0;32mSuccess: "
#define CB_Warning		"\033[0;33mWarning: "
#define CB_Error		"\033[0;31mError: "
#define CB_Info			"\033[0;36mInfo: "
#define CB_Display		"\033[0;37mDisplay: "

namespace Logger {

	enum class PrintType : byte {
		Success,
		Warning,
		Error,
		Info,
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

	template<class... Args>
	static void PrintLog(PrintType type = PrintType::Display, Args... args) {

		string messageFinal{};

		switch (type)
		{
		case PrintType::Success:
			messageFinal += CB_Success;
			break;
		case PrintType::Warning:
			messageFinal += CB_Warning;
			break;
		case PrintType::Error:
			messageFinal += CB_Error;
			break;
		case PrintType::Display:
			messageFinal += CB_Display;
			break;
		case PrintType::Info:
			messageFinal += CB_Info;
			break;
		default:
			messageFinal += WHITE;
			break;
		}

		std::cout << messageFinal << WHITE;
		(std::cout << ... << args) << std::endl;
	}
}


/*
	std::cout << argumentValue[0] << std::endl;
	Absolute Path of Exe
*/