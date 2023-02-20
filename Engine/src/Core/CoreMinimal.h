#pragma once 

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <string>
#include <unordered_map>

#include <iostream>
#include <filesystem>
#include <fstream>

#include <d3dcompiler.h>
#include <d3d11.h>
#include <DirectXPackedVector.h>

#include <wrl.h>

using std::string;
using namespace Microsoft::WRL;
using namespace DirectX;
using namespace DirectX::PackedVector;

typedef signed char			int8;
typedef signed short		int16;
typedef signed int			int32;
typedef signed long			int64;
typedef unsigned char		uint8, byte;
typedef unsigned short		uint16;
typedef unsigned int		uint32;
typedef unsigned long		uint64;