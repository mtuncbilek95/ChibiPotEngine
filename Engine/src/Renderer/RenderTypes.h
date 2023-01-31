#pragma once

#include <Core/CoreMinimal.h>

enum class DriverTypes : uint8 {
    Hardware,
    Warp,
    Reference,
    Software
};  

enum class FeatureTypes : uint8 {
    Dx11,
    Dx12
};