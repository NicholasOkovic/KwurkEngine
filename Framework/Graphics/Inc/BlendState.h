#pragma once


namespace KwurkEngine::Graphics
{
	class BlendState final
	{
	public:
		static void ClearState();

		enum class Mode
		{
			Opaque,
			AlphaBlend,
			AlphaPremulitplied,
			Additive
		};

		BlendState() = default;
		~BlendState();

		BlendState(const BlendState&) = delete;
		void Set();

		void Initialize(Mode mode);
		void Terminate();


	private:
		ID3D11BlendState* mBlendState = nullptr;

	};
}