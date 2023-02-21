#pragma once

#include <Core/CoreMinimal.h>

namespace Engine
{
    /// @brief DirectX driver types. The default parameter for related function uses Hardware.
    enum class DriverTypes : uint8
    {
        Hardware,
        Warp,
        Reference,
        Software
    };

    /// @brief Definition for the current DirectX API which is being used by ID3D11Device.
    enum class FeatureTypes : uint8
    {
        Dx11,
        Dx12
    };

    /// @brief Definition for multi graphics API (RHI) support.
    enum class GraphicsType : uint8
    {
        DirectX11,
        DirectX12,
        OpenGL,
        Vulkan
    };

    /// @brief Forward Declaration for Shaders in Materials.
    class ShaderProgram;

    /// @brief Initializer for Graphics API Interfaces.
    class GraphicsProgram
    {
    public:
        /**
         * @brief Construct a new Graphics Program object
         * 
         * @param ViewportSize Parameter to get the Windowsize from Windows API which will be used in D3D11_VIEWPORT.
         */
        GraphicsProgram(RECT ViewportSize);
        /**
         * @brief Runs all the sub-initializing functions such as CreateDeviceContext, CreateSwapchain.
         * 
         * @param handle the window Handle comes from WindowClass.
         * @return if returns false Window will be aborted without hesitation.
         */
        bool Initialize(const HWND handle);
        /**
         * @brief Runs all the upper system elements frame by frame.
         * 
         * @param DeltaTime the time between two frames in seconds.
         * @return if returns false Window will be aborted without hesitation.
         */
        bool UpdateFrame(float DeltaTime);

         
        /// @return 
        std::vector<ShaderProgram>& GetShaders() { return Shaders; }
    protected:
        /**
         * @brief Create a Device Context for ID3D11DeviceContext.
         * 
         * @param typeValue DirectX driver types. The default parameter for related function uses Hardware. \p Engine::DriverTypes.
         * @param featureValue Definition for the current DirectX API which is being used by ID3D11Device. \p Engine::FeatureTypes.
         * @return if returns false Window will be aborted without hesitation.
         */
        bool CreateDeviceContext(const DriverTypes typeValue = DriverTypes::Hardware, const FeatureTypes featureValue = FeatureTypes::Dx11);
        /**
         * @brief Create a Swap Chain for IDXGISwapChain
         * 
         * @param handle the window Handle comes from WindowClass.
         * @return if returns false Window will be aborted without hesitation.
         */
        bool CreateSwapChain(const HWND handle);
        /**
         * @brief Create a Render Target View for ID3D11RenderTargetView.
         * 
         * @return if returns false Window will be aborted without hesitation.
         */
        bool CreateRenderTargetView();

    private:
        std::vector<ShaderProgram> Shaders;
    };
}