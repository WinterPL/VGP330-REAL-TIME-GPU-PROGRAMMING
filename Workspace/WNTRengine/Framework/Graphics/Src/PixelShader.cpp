#include "Precompiled.h"
#include "../Inc/PixelShader.h"
#include "Graphics.h"

using namespace WNTRengine;
using namespace WNTRengine::Graphics;

void PixelShader::Initialize(const std::filesystem::path& filePath,const char* entryPoint) {

    auto device = GraphicsSystem::Get()->GetDevice();

    DWORD shaderFlags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG;
    ID3DBlob* shaderBlob = nullptr;
    ID3DBlob* errorBlob = nullptr;
    //===============================================================
    //Create a pixel shader
   HRESULT hr = D3DCompileFromFile(
        filePath.c_str(),
        nullptr,
        D3D_COMPILE_STANDARD_FILE_INCLUDE,
       entryPoint, "ps_5_0",
        shaderFlags, 0,
        &shaderBlob,
        &errorBlob
    );

    if (errorBlob && errorBlob->GetBufferPointer())
    {
        LOG("%s", static_cast<const char*>(errorBlob->GetBufferPointer()));
    }

    ASSERT(SUCCEEDED(hr), "Failed to compile pixel shader");

    hr = device->CreatePixelShader(
        shaderBlob->GetBufferPointer(),
        shaderBlob->GetBufferSize(),
        nullptr,
        &mPixelShader);
    ASSERT(SUCCEEDED(hr), "Failed to create input layout");
    SafeRelease(shaderBlob);
    SafeRelease(errorBlob);
}
void PixelShader::Terminate() {
    SafeRelease(mPixelShader);
}

void PixelShader::Bind() {
    auto context = GraphicsSystem::Get()->GetContext();
    context->PSSetShader(mPixelShader, nullptr, 0);
}