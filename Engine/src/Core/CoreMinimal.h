#pragma once 

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

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