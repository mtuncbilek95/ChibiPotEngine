#pragma once

#include <Core/CoreMinimal.h>

#define RED			"\033[0;31m"
#define GREEN		"\033[0;32m"
#define YELLOW		"\033[0;33m"
#define BLUE		"\033[0;34m"
#define PURPLE		"\033[0;35m"
#define CYAN		"\033[0;36m"
#define WHITE		"\033[0;37m"
#define WHITE_END	"\033[0;37m\n"

#define CB_Success		GREEN "Success: "
#define CB_Warning		YELLOW "Warning: " 
#define CB_Error		RED "Error: " 
#define CB_Display		WHITE "Display: "

#define CONSOLE_LOG(color,message,...) printf(color message WHITE_END,__VA_ARGS__);

namespace Logger {
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

    static string GetCurrentDir()
    {
        std::filesystem::path directoryPath = std::filesystem::current_path();
        string path = directoryPath.generic_string();
        return path;
    }
}


/*
    std::cout << argumentValue[0] << std::endl;
    Absolute Path of Exe
*/