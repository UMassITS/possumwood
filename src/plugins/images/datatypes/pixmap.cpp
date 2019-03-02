#include "pixmap.h"

namespace possumwood {

template<typename BASE>
Pixel<BASE>::Pixel(const value_t& value) : m_value(value) {
}

template<typename BASE>
const typename Pixel<BASE>::value_t& Pixel<BASE>::value() const {
	return m_value;
}

template<typename BASE>
void Pixel<BASE>::setValue(const value_t& rgb) {
	m_value = rgb;
}

template<typename BASE>
constexpr std::size_t Pixel<BASE>::size() {
	return sizeof(Pixel) / sizeof(channel_t);
}

template<typename BASE>
Pixel<BASE>& Pixel<BASE>::operator = (const value_t& rgb) {
	m_value = rgb;
	return *this;
}

template<typename BASE>
const typename Pixel<BASE>::value_t& Pixel<BASE>::operator*() const {
	return *this;
}

template<typename BASE>
Pixel<BASE>::operator const value_t&() const {
	return m_value;
}

template<typename PIXEL>
Pixmap<PIXEL>::Pixmap(std::size_t width, std::size_t height, const Pixmap<PIXEL>::pixel_t& defaultValue) :
m_width(width), m_height(height) {
	m_scanline = width * sizeof(PIXEL);

	m_scanline = (m_scanline / 4 + (m_scanline % 4 > 0)) * 4;

	m_data = std::vector<uint8_t>(m_scanline*height*sizeof(PIXEL));
}

template<typename PIXEL>
const typename Pixmap<PIXEL>::pixel_t& Pixmap<PIXEL>::operator()(std::size_t x, std::size_t y) const {
	assert(x < m_width);
	assert(y < m_height);

	const uint8_t* ptr = &(*m_data.begin()) + (x*sizeof(PIXEL) + y*m_scanline);
	return *reinterpret_cast<const Pixmap<PIXEL>::pixel_t*>(ptr);
}

template<typename PIXEL>
typename Pixmap<PIXEL>::pixel_t& Pixmap<PIXEL>::operator()(std::size_t x, std::size_t y) {
	assert(x < m_width);
	assert(y < m_height);

	uint8_t* ptr = &(*m_data.begin()) + (x*sizeof(PIXEL) + y*m_scanline);
	return *reinterpret_cast<Pixmap<PIXEL>::pixel_t*>(ptr);
}

template<typename PIXEL>
std::size_t Pixmap<PIXEL>::width() const {
	return m_width;
}

template<typename PIXEL>
std::size_t Pixmap<PIXEL>::height() const {
	return m_height;
}

template<typename PIXEL>
bool Pixmap<PIXEL>::empty() const {
	return m_width == 0 && m_height == 0;
}

// explicit instantiation
template class Pixel<uint8_t>;
template class Pixel<float>;

template class Pixmap<Pixel<uint8_t>>;
template class Pixmap<Pixel<float>>;

}
