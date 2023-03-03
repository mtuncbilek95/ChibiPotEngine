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
    enum class FeatureTypesDX : uint8
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

    /// @brief Initializer for Graphics API Interfaces.
    class GraphicsDevice
    {
        friend class ShaderObject;
    public:
        /**
         * @brief Construct a new Graphics Program object
        */
        GraphicsDevice();
        /**
         * @brief Runs all the sub-initializing functions such as CreateDeviceContext, CreateSwapchain.
         * @param handle the window Handle comes from WindowClass.
         * @return if returns false Window will be aborted without hesitation.
        */
        bool Initialize(const HWND handle, int m_width, int m_height);
        /**
         * @brief Runs all the upper system elements frame by frame.
         * @param DeltaTime the time between two frames in seconds.
         * @return if returns false Window will be aborted without hesitation.
        */
        bool Update(float DeltaTime);
        /**
         * @brief Renders the specified color for the window.
        */
        void ClearFrame();

    protected:
        /**
         * @brief Create a Device Context for ID3D11DeviceContext.
         * @param typeValue DirectX driver types. The default parameter for related function uses Hardware.
         * @param featureValue Definition for the current DirectX API which is being used by ID3D11Device.
         * @return if returns false Window will be aborted without hesitation.
        */
        bool CreateDeviceContext(const DriverTypes driverValue = DriverTypes::Hardware, const FeatureTypesDX featureValue = FeatureTypesDX::Dx11);
        /**
         * @brief Create a Swap Chain for IDXGISwapChain
         * @param handle the window Handle comes from WindowClass.
         * @return if returns false Window will be aborted without hesitation.
        */
        bool CreateSwapChain(const HWND handle);
        /**
         * @brief Create a Render Target View for ID3D11RenderTargetView.
         * @return if returns false Window will be aborted without hesitation.
        */
        bool CreateRenderTargetView();
        bool CreateViewport(int width, int height);

    private:
        ComPtr<ID3D11Device> m_Device;
        ComPtr<ID3D11DeviceContext> m_Context;
        ComPtr<IDXGISwapChain> m_Swapchain;
        ComPtr<ID3D11RenderTargetView> m_RenderTargetView;

        D3D11_VIEWPORT Viewport;

        ShaderObject* Shader;
    private:
        // TODO: Use single Vertex Shader structure for now, but it will be transform into multiple shader structure.
        ComPtr<ID3D11VertexShader> m_VertexShader;
        // TODO: Use single Pixel Shader structure for now, but it will be transform into multiple shader structure.
        ComPtr<ID3D11PixelShader> m_PixelShader;
        // TODO: Use single Input Layout structure for now.
        ComPtr<ID3D11InputLayout> m_InputLayout;
        // TODO: Use this in here for now.
        ComPtr<ID3DBlob> m_Blob;
    };
}