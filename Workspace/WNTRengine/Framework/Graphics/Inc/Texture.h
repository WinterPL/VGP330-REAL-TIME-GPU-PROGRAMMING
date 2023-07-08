#pragma once
namespace WNTRengine::Graphics
{
	class Texture {
	public:
		static void UnbindPS(uint32_t slot);

		enum class Format {
			RGBA_U8,
			RGBA_U32
		};
		Texture() = default;
		virtual ~Texture();

		//delete the copy
		Texture(const Texture&) = delete;
		Texture& operator=(const Texture&&) = delete;

		// allow moving
		Texture(Texture&& rhs) noexcept;
		Texture& operator=(Texture&&) noexcept;

		virtual void Initialize(const std::filesystem::path& filename);
		virtual void Initialize(uint32_t width, uint32_t height, Format format);
		virtual void Terminate();

		void BindVS(uint32_t slot)const;
		void BindPS(uint32_t slot)const;
		
		void* GetRawData()const { return mShaderResourceView; }
		
	protected:
		DXGI_FORMAT GetDXGIFormat(Format format);

		ID3D11ShaderResourceView* mShaderResourceView = nullptr;
	};
}