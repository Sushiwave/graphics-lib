#pragma once
#include <ThirdParty/CPPLib/Math/Vector/Vector4D.hpp>
#include <GraphicsLib/Graphics/GPUResource/ShaderResource/Texture/Texture2D/Components/TextureFormat.hpp>

#include <vector>
#include <functional>



namespace cg
{
	class ImageXY
	{
	public:
		using Pixel = cpp::Vector4D<float>;
		using Pixels = std::vector<std::vector<Pixel>>;
	private:
		Pixels m_pixels;
		cpp::Vector2D<int> m_size;
	public:
		 Pixel get(int x, int y) const;

		 template <typename T>
		 void storeIn(T* pDest, int colorDimension, bool isFloatingPoint) const
		 {
			 auto byteStride = sizeof(T);

			 T color;
			 std::function<void(float, T*)> encodeColor;
			 if (isFloatingPoint)
			 {
				 encodeColor = [&](float src, T* out) { *out = static_cast<T>(src); };
			 }
			 else
			 {
				 encodeColor = [&](float src, T* out) { *out = static_cast<T>(src*(std::numeric_limits<T>::max)()); };
			 }

			 for (int y = 0; y < m_size.y; ++y)
			 {
				 for (int x = 0; x < m_size.x; ++x)
				 {
					 auto colorV4Float = m_pixels[x][y];
					 for (int d = 0; d < colorDimension; ++d)
					 {
						 encodeColor(colorV4Float.at(d+1), &color);
						 memcpy(pDest, &color, byteStride);

						 pDest += byteStride;
					 }
				 }
			 }
		 }

		 template <typename T>
		 std::shared_ptr<T> create1DArray(int colorDimension, bool isFloatingPoint) const
		 {
			 std::shared_ptr<T> memory(new T[m_size.x*m_size.y*colorDimension], std::default_delete<T[]>());
			 storeIn(memory.get(), colorDimension, isFloatingPoint);
			 return memory;
		 }

		 cpp::Vector2D<int> getSize() const;
	};
}