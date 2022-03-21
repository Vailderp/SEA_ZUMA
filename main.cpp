
#ifdef _DEBUG
#pragma comment(lib, "sfml-graphics-d.lib")
#pragma comment(lib, "sfml-audio-d.lib")
#pragma comment(lib, "sfml-network-d.lib")
#pragma comment(lib, "sfml-system-d.lib")
#pragma comment(lib, "sfml-window-d.lib")
#else
#ifndef SFML_STATIC
#define SFML_STATIC
#endif
#pragma comment(lib, "sfml-graphics-s.lib")
#pragma comment(lib, "freetype.lib")
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "sfml-window-s.lib")
#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "sfml-audio-s.lib")
#pragma comment(lib, "flac.lib")
#pragma comment(lib, "vorbisenc.lib")
#pragma comment(lib, "vorbisfile.lib")
#pragma comment(lib, "vorbis.lib")
#pragma comment(lib, "ogg.lib")
#pragma comment(lib, "openal32.lib")
#pragma comment(lib, "sfml-system-s.lib")
#pragma comment(lib, "winmm.lib")
#endif
#include <iostream>
#include "VGui_sfml.h"

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/Audio.hpp"

#include "Game.h"

#pragma once
#define _VGUI_BEGIN namespace vgui {
#define _VGUI_END }
#define _VGUI vgui::
#define _VGUI_UTILITIES_BEGIN namespace vgui_utilities {
#define _VGUI_UTILITIES_END }
#define _VGUI_UTILITIES vgui_utilities::
#include <list>
#include <string>
#include <vector>

#pragma once
#include <chrono>

class StepTimer
{
public:

	StepTimer() :
		m_last_time(0.),
		m_this_time(0.)
	{
		
	}

	void tick() const
	{
		m_last_time = std::chrono::duration<double>(std::chrono::system_clock::now().time_since_epoch()).count();
	}

	[[nodiscard]]
	float getElapsedSeconds() const
	{
		m_this_time = std::chrono::duration<double>(std::chrono::system_clock::now().time_since_epoch()).count() -
			m_last_time;
		return m_this_time;
	}

	[[nodiscard]]
	double getFPS() const
	{
		return 1. / (std::chrono::duration<double>(std::chrono::system_clock::now().time_since_epoch()).count() -
			m_last_time);
	}

private:

	mutable double m_last_time;

	mutable double m_this_time;

};


_VGUI_BEGIN
template <typename... _Va_user_data_types>
struct UserDataTuple;

template <typename _Va_user_data_type>
struct UserDataTuple<_Va_user_data_type>
{

	explicit UserDataTuple(
		_Va_user_data_type arg
	) :
		arg(arg)
	{
	
	}

	_Va_user_data_type arg;

};

template<
	typename _Va_user_data_type,
	typename... _Va_user_data_types		>
	struct UserDataTuple<_Va_user_data_type, _Va_user_data_types...>
{

	constexpr explicit UserDataTuple(
		_Va_user_data_type arg,
		_Va_user_data_types... args
	) :
		arg(arg),
		next_args(args...)
	{

	}

	_Va_user_data_type arg;

	UserDataTuple<_Va_user_data_types...> next_args;

};

template<typename... _Va_user_data_types>
void* make_user_data(
	_Va_user_data_types... args
)
{
	return new UserDataTuple<_Va_user_data_types...>(args...);
}
_VGUI_END

_VGUI_BEGIN
class WidgetBase;
typedef void(*event_lambda)(WidgetBase&, void*);
_VGUI_END

_VGUI_UTILITIES_BEGIN
inline void __fastcall call_lambdas(
	const std::list<_VGUI event_lambda>& lambdas, 
	_VGUI WidgetBase& widget,
	void* user_data
)
{
	for (decltype(auto) lambda : lambdas)
	{
		lambda(widget, user_data);
	}
}
_VGUI_UTILITIES_END

_VGUI_BEGIN
enum class MouseButton : unsigned char
{
	Left,
	Right,
	Middle,
	XButton1,
	XButton2
};
_VGUI_END

_VGUI_BEGIN
template <typename _Type>
struct Vector2
{

	Vector2() = default;

	Vector2(
		_Type x,
		_Type y
	) :
		x(x), y(y)
	{
		
	}

	_Type x;

	_Type y;

};
_VGUI_END

_VGUI_BEGIN
struct Color
{
	Color() = default;
	Color(
		const unsigned char r,
		const unsigned char g, 
		const unsigned char b, 
		const unsigned char a = 255
	) :
		r(r),
		g(g),
		b(b),
		a(a)
	{
		
	}

	uint8_t r{};

	uint8_t g{};

	uint8_t b{};

	uint8_t a{};
};
_VGUI_END

_VGUI_UTILITIES_BEGIN
template <typename _Backend_texture_type>
class Textureable
{
public:
	virtual ~Textureable() = default;

	template<typename _Backend_texture_type>
	void setBackendTexture(_Backend_texture_type* texture)
	{
		m_backend_texture = texture;
		onSetTexture();
	}

	[[nodiscard]]
	_Backend_texture_type*& getBackendTexture()
	{
		return m_backend_texture;
	}

protected:

	virtual void onSetTexture() = 0;

protected:

	_Backend_texture_type* m_backend_texture = nullptr;

};
_VGUI_UTILITIES_END

_VGUI_UTILITIES_BEGIN
template<typename _Backend_text_type>
class Textable
{
public:
	virtual ~Textable() = default;

	void setBackendText(_Backend_text_type* text)
	{
		m_backend_text = text;
		onSetText();
	}

	[[nodiscard]]
	_Backend_text_type*& getBackendText() 
	{
		return m_backend_text;
	}

protected:

	virtual void onSetText() = 0;

protected:

	_Backend_text_type* m_backend_text = nullptr;

};
_VGUI_UTILITIES_END

_VGUI_UTILITIES_BEGIN
template<typename _Backend_shader_type>
class Shaderable
{
public:
	virtual ~Shaderable() = default;

	void setBackendShader(_Backend_shader_type* shader)
	{
		m_backend_shader = shader;
		onSetShader();
	}

	[[nodiscard]]
	_Backend_shader_type*& getBackendShader()
	{
		return m_backend_shader;
	}

protected:

	virtual void onSetShader() = 0;

protected:

	_Backend_shader_type* m_backend_shader = nullptr;

};
_VGUI_UTILITIES_END

_VGUI_BEGIN
class Transformable;
class Transform
{

	friend class Transformable;

protected:

	Vector2<float> m_position;

	Vector2<float> m_size;

};

class Transformable : public Transform
{
public:
	Transformable() = default;

	[[nodiscard]]
	Vector2<float> getPosition() const
	{
		return m_position;
	}

	void setPosition(const Vector2<float> position)
	{
		m_position = position;
		onSetPosition();
	}

	void setPosition(
		const float x,
		const float y
	)
	{
		m_position.x = x;
		m_position.y = y;
		onSetPosition();
	}

	void setPosition(
		const Vector2<float> position,
		const Vector2<float> display_size
	)
	{
		m_position.x = static_cast<float>(display_size.x) * position.x;
		m_position.y = static_cast<float>(display_size.y) * position.y;
		onSetPosition();
	}

	void setPosition(
		const float position_x,
		const float position_y,
		const float display_size_x,
		const float display_size_y
	)
	{
		m_position.x = static_cast<float>(display_size_x) * position_x;
		m_position.y = static_cast<float>(display_size_y) * position_y;
		onSetPosition();
	}

	void move(const Vector2<float> position)
	{
		m_position.x += position.x;
		m_position.y += position.y;
		onSetPosition();
	}

	void move(
		const float x,
		const float y)
	{
		m_position.x += x;
		m_position.y += y;
		onSetPosition();
	}

	void move(
		const Vector2<float> position,
		const Vector2<float> display_size
	)
	{
		m_position.x += static_cast<float>(display_size.x) * position.x;
		m_position.y += static_cast<float>(display_size.y) * position.y;
		onSetPosition();
	}

	void move(
		const float position_x,
		const float position_y,
		const float display_size_x,
		const float display_size_y
	)
	{
		m_position.x = static_cast<float>(display_size_x) * position_x;
		m_position.y = static_cast<float>(display_size_y) * position_y;
		onSetPosition();
	}

	[[nodiscard]]
	Vector2<float> getSize() const
	{
		return m_size;
	}

	void setSize(const Vector2<float> size)
	{
		m_size = size;
		onSetSize();
	}

	void setSize(const float x, const float y)
	{
		m_size.x = x;
		m_size.y = y;
		onSetSize();
	}

	void setSize(
		const Vector2<float> size,
		const Vector2<float> display_size
	)
	{
		m_size.x = static_cast<float>(display_size.x) * size.x;
		m_size.y = static_cast<float>(display_size.y) * size.y;
		onSetSize();
	}

	void setSize(
		const float size_x,
		const float size_y,
		const float display_size_x,
		const float display_size_y
	)
	{
		m_size.x = static_cast<float>(display_size_x) * size_x;
		m_size.y = static_cast<float>(display_size_y) * size_y;
		onSetSize();
	}

	[[nodiscard]]
	const Transform& getTransform() const
	{
		return *this;
	}

protected:

	virtual void onSetPosition() = 0;

	virtual void onSetSize() = 0;
};
_VGUI_END

_VGUI_BEGIN
class WidgetBase : public Transformable
{
public:
	virtual ~WidgetBase() = default;

	WidgetBase() = default;

	WidgetBase(
		const Vector2<float> position,
		const Vector2<float> size
	)
	{
		this->setPosition(position);
		this->setSize(size);
	}

	void setColor(const Color color)
	{
		m_color = color;
		onSetColor();
	}


	[[nodiscard]]
	Color getColor() const
	{
		return m_color;
	}

	void setUserData(void* user_data)
	{
		m_user_data = user_data;
	}

	[[nodiscard]]
	void* getUserData() const
	{
		return m_user_data;
	}

	void addOnMouseEnteredLambda(const event_lambda lambda_mouse_entered)
	{
		m_lambdas_mouse_entered.push_back(lambda_mouse_entered);
	}

	void addOnMouseLeftLambda(const event_lambda lambda_mouse_left)
	{
		m_lambdas_mouse_left.push_back(lambda_mouse_left);
	}

	void setOnMouseEnteredLambdas(const std::list<event_lambda>& lambdas_mouse_entered)
	{
		m_lambdas_mouse_entered = lambdas_mouse_entered;
	}

	void setOnMouseLeftLambdas(const std::list<event_lambda>& lambdas_mouse_left)
	{
		m_lambdas_mouse_left = lambdas_mouse_left;
	}

	[[nodiscard]]
	const std::list<event_lambda>& getOnMouseEnteredLambdas() const
	{
		return m_lambdas_mouse_entered;
	}

	[[nodiscard]]
	const std::list<event_lambda>& getOnMouseLeftLambdas() const
	{
		return m_lambdas_mouse_left;
	}

	void removeOnMouseEnteredLambda(const event_lambda lambda_mouse_entered)
	{
		m_lambdas_mouse_entered.remove(lambda_mouse_entered);
	}

	void removeOnMouseLeftLambda(const event_lambda lambda_mouse_left)
	{
		m_lambdas_mouse_left.remove(lambda_mouse_left);
	}

protected:

	virtual void mouseEnteredWidget()
	{
		_VGUI_UTILITIES call_lambdas(this->m_lambdas_mouse_entered, *this, this->m_user_data);
	}

	virtual void mouseLeftWidget()
	{
		_VGUI_UTILITIES call_lambdas(this->m_lambdas_mouse_left, *this, this->m_user_data);
	}

protected:

	virtual void onSetColor() = 0;

protected:

	Color m_color;

	bool m_is_mouse_already_entered = false;

	void* m_user_data = nullptr;

	std::list<event_lambda> m_lambdas_mouse_entered;

	std::list<event_lambda> m_lambdas_mouse_left;

};
_VGUI_END

_VGUI_BEGIN
class ButtonBase : public virtual WidgetBase
{
public:

	ButtonBase() = default;

	ButtonBase(
		const Vector2<float> position,
		const Vector2<float> size
	) :
		WidgetBase(position, size)
	{

	}

	ButtonBase(
		const float pos_x,
		const float pos_y,
		const float size_x,
		const float size_y
	) :
		WidgetBase(
			Vector2(pos_x, pos_y), 
			Vector2(size_x, size_y)
		)
	{

	}

	void setBorderThickness(const float border_thickness)
	{
		m_border_thickness = border_thickness;
		onSetBorderThickness();
	}

	[[nodiscard]]
	float getBorderThickness() const
	{
		return m_border_thickness;
	}

	void setBorderColor(const Color border_color)
	{
		m_border_color = border_color;
		onSetBorderColor();
	}

	[[nodiscard]]
	Color getBorderColor() const
	{
		return m_border_color;
	}

	// Add event lambda
	void addOnMouseDownLambda(const event_lambda lambda_mouse_down)
	{
		m_lambdas_mouse_down.push_back(lambda_mouse_down);
	}

	void addOnMouseUpLambda(const event_lambda lambda_mouse_up)
	{
		m_lambdas_mouse_up.push_back(lambda_mouse_up);
	}

	// Set event lambda list
	void setOnMouseDownLambdas(const std::list<event_lambda>& lambdas_mouse_down)
	{
		m_lambdas_mouse_down = lambdas_mouse_down;
	}

	void setOnMouseUpLambdas(const std::list<event_lambda>& lambdas_mouse_up)
	{
		m_lambdas_mouse_up = lambdas_mouse_up;
	}

	// Get event lambda list
	[[nodiscard]]
	const std::list<event_lambda>& getOnMouseDownLambdas() const
	{
		return m_lambdas_mouse_down;
	}

	[[nodiscard]]
	const std::list<event_lambda>& getOnMouseUpLambdas() const
	{
		return m_lambdas_mouse_up;
	}

	// Remove event lambda
	void removeOnMouseDownLambda(const event_lambda lambda_mouse_down)
	{
		m_lambdas_mouse_down.remove(lambda_mouse_down);
	}

	void removeOnMouseUpLambda(const event_lambda lambda_mouse_up)
	{
		m_lambdas_mouse_up.remove(lambda_mouse_up);
	}

protected:

	virtual void onMouseDown(const Vector2<int>& position, MouseButton mouse)
	{
		_VGUI_UTILITIES call_lambdas(this->m_lambdas_mouse_down, *this, this->m_user_data);
	}

	virtual void onMouseUp(const Vector2<int>& position, MouseButton mouse)
	{
		_VGUI_UTILITIES call_lambdas(this->m_lambdas_mouse_up, *this, this->m_user_data);
	}

protected:

	virtual void onSetBorderThickness() = 0;

	virtual void onSetBorderColor() = 0;

	float m_border_thickness;

	Color m_border_color;

	std::list<event_lambda> m_lambdas_mouse_down;

	std::list<event_lambda> m_lambdas_mouse_up;

};
_VGUI_END

_VGUI_BEGIN
template <typename _Backend_shape_slider>
class SliderBase : public virtual WidgetBase
{
public:

	SliderBase() = default;

	SliderBase(
		const Vector2<float> position,
		const Vector2<float> size
	) :
		WidgetBase(position, size)
	{

	}

	SliderBase(
		const float pos_x,
		const float pos_y,
		const float size_x,
		const float size_y
	) :
		WidgetBase(
			Vector2(pos_x, pos_y),
			Vector2(size_x, size_y)
		)
	{

	}

	virtual _Backend_shape_slider& getBackendShapeSliderBody() = 0;

	virtual _Backend_shape_slider& getBackendShapeSliderHandle() = 0;

	void setHandleTextureWidth(const uint16_t handle_texture_width)
	{
		m_handle_texture_width = handle_texture_width;
		onSetHandleTextureWidth();
	}

	[[nodiscard]]
	const uint16_t& getHandleTextureWidth() const
	{
		return m_handle_texture_width;
	}

	void setMinimalSliderValue(const float minimal_slider_value)
	{
		m_minimal_slider_value = minimal_slider_value;
		onSetMinimalSliderValue();
	}

	[[nodiscard]]
	const float& getMinimalSliderValue() const
	{
		return m_minimal_slider_value;
	}

	void setMaximalSliderValue(const float maximal_slider_value)
	{
		m_maximal_slider_value = maximal_slider_value;
		onSetMaximalSliderValue();
	}

	[[nodiscard]]
	const float& getMaximalSliderValue() const
	{
		return m_maximal_slider_value;
	}

	void setSliderValue(const float slider_value)
	{
		m_slider_value = slider_value;
		onSetSliderValue();
	}

	[[nodiscard]]
	const float& getSliderValue() const
	{
		return m_slider_value;
	}

	void setTextLabelPosition(const Vector2<float> text_label_position)
	{
		m_text_label_position = text_label_position;
		onSetTextLabelPosition();
	}

	void setTextLabelPosition(
		const float text_label_position_x, 
		const float text_label_position_y
	)
	{
		m_text_label_position.x = text_label_position_x;
		m_text_label_position.y = text_label_position_y;
		onSetTextLabelPosition();
	}

	[[nodiscard]]
	const Vector2<float>& getTextLabelPosition() const
	{
		return m_text_label_position;
	}

	void setHandleSize(const Vector2<float> handle_size)
	{
		m_handle_size = handle_size;
	}

	void setHandleSize(const float handle_size_x, const float handle_size_y)
	{
		m_handle_size.x = handle_size_x;
		m_handle_size.y = handle_size_y;
	}

	[[nodiscard]]
	const Vector2<float>& getHandleSize() const
	{
		return m_handle_size;
	}

	// Add event lambda
	void addOnHandleMoveLambda(const event_lambda lambda_mouse_down)
	{
		m_lambdas_handle_move.push_back(lambda_mouse_down);
	}

	// Set event lambda list
	void setOnHandleMoveLambdas(const std::list<event_lambda>& lambdas_mouse_down)
	{
		m_lambdas_handle_move = lambdas_mouse_down;
	}


	// Get event lambda list
	[[nodiscard]]
	const std::list<event_lambda>& getOnHandleMoveLambdas() const
	{
		return m_lambdas_handle_move;
	}


	// Remove event lambda
	void removeOnHandleMoveLambda(const event_lambda lambda_mouse_down)
	{
		m_lambdas_handle_move.remove(lambda_mouse_down);
	}


protected:

	virtual void mouseEnteredWidget()
	{
		_VGUI_UTILITIES call_lambdas(this->m_lambdas_mouse_entered, *this, this->m_user_data);
	}

	virtual void mouseLeftWidget()
	{
		_VGUI_UTILITIES call_lambdas(this->m_lambdas_mouse_left, *this, this->m_user_data);
	}

	virtual void onHandleMove()
	{
		_VGUI_UTILITIES call_lambdas(this->m_lambdas_handle_move, *this, this->m_user_data);
	}


protected:

	virtual void onSetHandleTextureWidth() = 0;

	virtual void onSetSliderValue() = 0;

	virtual void onSetMinimalSliderValue() = 0;

	virtual void onSetMaximalSliderValue() = 0;

	virtual void onSetTextLabelPosition() = 0;

protected:

	uint16_t m_handle_texture_width;

	float m_slider_value;

	float m_minimal_slider_value;

	float m_maximal_slider_value;

	Vector2<float> m_text_label_position;

	Vector2<float> m_handle_size;

	std::list<event_lambda> m_lambdas_mouse_entered;

	std::list<event_lambda> m_lambdas_mouse_left;

	std::list<event_lambda> m_lambdas_handle_move;

};
_VGUI_END

_VGUI_BEGIN
class CheckBoxBase : public virtual WidgetBase
{
public:

	CheckBoxBase() = default;

	CheckBoxBase(
		const Vector2<float> position,
		const Vector2<float> size
	) :
		WidgetBase(position, size)
	{

	}

	CheckBoxBase(
		const float pos_x,
		const float pos_y,
		const float size_x,
		const float size_y
	) :
		WidgetBase(
			Vector2(pos_x, pos_y),
			Vector2(size_x, size_y)
		)
	{

	}

public:

	void setTextLabelPosition(const Vector2<float> text_label_position)
	{
		m_text_label_position = text_label_position;
		onSetTextLabelPosition();
	}

	void setTextLabelPosition(
		const float text_label_position_x,
		const float text_label_position_y
	)
	{
		m_text_label_position.x = text_label_position_x;
		m_text_label_position.y = text_label_position_y;
		onSetTextLabelPosition();
	}

	[[nodiscard]]
	const Vector2<float>& getTextLabelPosition() const
	{
		return m_text_label_position;
	}

	// Add event lambda
	void addOnTrue(const event_lambda lambdas_true)
	{
		m_lambdas_true.push_back(lambdas_true);
	}

	void addOnFalse(const event_lambda lambdas_false)
	{
		m_lambdas_false.push_back(lambdas_false);
	}

	// Set event lambda list
	void setOnTrue(const std::list<event_lambda>& lambdas_true)
	{
		m_lambdas_true = lambdas_true;
	}

	void setOnFalse(const std::list<event_lambda>& lambdas_false)
	{
		m_lambdas_false = lambdas_false;
	}

	// Get event lambda list
	[[nodiscard]]
	const std::list<event_lambda>& getOnTrue() const
	{
		return m_lambdas_true;
	}

	[[nodiscard]]
	const std::list<event_lambda>& getOnFalse() const
	{
		return m_lambdas_false;
	}

	// Remove event lambda
	void removeOnTrue(const event_lambda lambdas_true)
	{
		m_lambdas_true.remove(lambdas_true);
	}

	void removeOnFalse(const event_lambda lambdas_false)
	{
		m_lambdas_false.remove(lambdas_false);
	}

	[[nodiscard]]
	const bool& getBool() const
	{
		return m_bool;
	}

protected:

	virtual void onTrue()
	{
		_VGUI_UTILITIES call_lambdas(this->m_lambdas_true, *this, this->m_user_data);
	}

	virtual void onFalse()
	{
		_VGUI_UTILITIES call_lambdas(this->m_lambdas_false, *this, this->m_user_data);
	}

protected:

	virtual void onSetTextLabelPosition() = 0;

protected:

	bool m_bool = false;

	Vector2<float> m_text_label_position;

	std::list<event_lambda> m_lambdas_mouse_entered;

	std::list<event_lambda> m_lambdas_mouse_left;

	std::list<event_lambda> m_lambdas_true;

	std::list<event_lambda> m_lambdas_false;

};
_VGUI_END

_VGUI_BEGIN
class TextBoxBase : public virtual WidgetBase
{
public:

	TextBoxBase() = default;

	TextBoxBase(
		const Vector2<float> position,
		const Vector2<float> size
	) :
		WidgetBase(position, size)
	{

	}

	TextBoxBase(
		const float pos_x,
		const float pos_y,
		const float size_x,
		const float size_y
	) :
		WidgetBase(
			Vector2(pos_x, pos_y),
			Vector2(size_x, size_y)
		)
	{

	}

	// Add event lambda
	void addOnMouseEnteredLambda(const event_lambda lambda_mouse_entered)
	{
		m_lambdas_mouse_entered.push_back(lambda_mouse_entered);
	}

	void addOnMouseLeftLambda(const event_lambda lambda_mouse_left)
	{
		m_lambdas_mouse_left.push_back(lambda_mouse_left);
	}

	void addOnKeyboardInputLambda(const event_lambda lambda_mouse_down)
	{
		m_lambdas_keyboard_input.push_back(lambda_mouse_down);
	}

	// Set event lambda list
	void setOnMouseEnteredLambdas(const std::list<event_lambda>& lambdas_mouse_entered)
	{
		m_lambdas_mouse_entered = lambdas_mouse_entered;
	}

	void setOnMouseLeftLambdas(const std::list<event_lambda>& lambdas_mouse_left)
	{
		m_lambdas_mouse_left = lambdas_mouse_left;
	}

	void setOnKeyboardInputLambdas(const std::list<event_lambda>& lambdas_mouse_down)
	{
		m_lambdas_keyboard_input = lambdas_mouse_down;
	}


	// Get event lambda list
	[[nodiscard]]
	const std::list<event_lambda>& getOnMouseEnteredLambdas() const
	{
		return m_lambdas_mouse_entered;
	}

	[[nodiscard]]
	const std::list<event_lambda>& getOnMouseLeftLambdas() const
	{
		return m_lambdas_mouse_left;
	}

	[[nodiscard]]
	const std::list<event_lambda>& getOnKeyboardInputLambdas() const
	{
		return m_lambdas_keyboard_input;
	}


	// Remove event lambda
	void removeOnMouseEnteredLambda(const event_lambda lambda_mouse_entered)
	{
		m_lambdas_mouse_entered.remove(lambda_mouse_entered);
	}

	void removeOnMouseLeftLambda(const event_lambda lambda_mouse_left)
	{
		m_lambdas_mouse_left.remove(lambda_mouse_left);
	}

	void removeOnKeyboardInputLambda(const event_lambda lambda_mouse_down)
	{
		m_lambdas_keyboard_input.remove(lambda_mouse_down);
	}

public:

	void setMaximalSymbolsCount(const uint16_t maximal_symbols_count)
	{
		m_maximal_symbols_count = maximal_symbols_count;
	}

	[[nodiscard]]
	const uint16_t& getMaximalSymbolsCount() const
	{
		return m_maximal_symbols_count;
	}

	void setTextPosition(const Vector2<float> text_position)
	{
		m_text_position = text_position;
		onSetTextPosition();
	}

	void setTextPosition(const float text_position_x, const float text_position_y)
	{
		m_text_position.x = text_position_x;
		m_text_position.y = text_position_y;
		onSetTextPosition();
	}

	[[nodiscard]]
	const Vector2<float>& getTextPosition() const
	{
		return m_text_position;
	}

protected:

	virtual void mouseEnteredWidget()
	{
		_VGUI_UTILITIES call_lambdas(this->m_lambdas_mouse_entered, *this, this->m_user_data);
	}

	virtual void mouseLeftWidget()
	{
		_VGUI_UTILITIES call_lambdas(this->m_lambdas_mouse_left, *this, this->m_user_data);
	}

	virtual void onKeyboardInput()
	{
		_VGUI_UTILITIES call_lambdas(this->m_lambdas_keyboard_input, *this, this->m_user_data);
	}

protected:

	virtual void onSetTextPosition() = 0;

protected:

	uint16_t m_symbols_count;

	uint16_t m_maximal_symbols_count;

	Vector2<float> m_text_position;

	std::list<event_lambda> m_lambdas_mouse_entered;

	std::list<event_lambda> m_lambdas_mouse_left;

	std::list<event_lambda> m_lambdas_keyboard_input;

};
_VGUI_END


_VGUI_BEGIN
template<	
			typename _Backend_event_type,
			typename... _Backend_event_arg_types	>
class HandlerBase
{
public:

	virtual ~HandlerBase() = default;

	virtual void handleEvent(
		_Backend_event_type event,
		_Backend_event_arg_types... backend_event_args
	) = 0;

	[[nodiscard]]
	virtual bool isMouseEntered(
		const Vector2<int>& mouse
	) const = 0;

};
_VGUI_END

_VGUI_BEGIN
template <
			typename _Backend_widget_type,
			typename _Backend_event_type,
			typename... _Backend_event_arg_types	>
class GuiTargetBase : public HandlerBase<_Backend_event_type, _Backend_event_arg_types...>
{
public:
	void addWidget(_Backend_widget_type& widget)
	{
		m_widgets.push_back(&widget);
	}

	void removeWidget(_Backend_widget_type& widget)
	{
		m_widgets.remove(&widget);
	}


	void handleEvent(
		_Backend_event_type event,
		_Backend_event_arg_types... backend_event_args
	) override = 0;

protected:

	std::list<_Backend_widget_type*> m_widgets;

protected:

	[[nodiscard]]
	bool isMouseEntered(
		const Vector2<int>& mouse
	) const override = 0;

};
_VGUI_END

_VGUI_BEGIN
template <typename _Gui_target_type>
class WindowBase :
					public Transformable,
					public _Gui_target_type
{
	template <	
		typename _Gui_target_type,
		typename _Backend_window_type  >
		friend class GuiBase;

public:

	WindowBase() :
		m_is_active(true)
	{
		
	}

	void setTitlePosition(const Vector2<float> title_position)
	{
		m_title_position = title_position;
	}

	void setTitlePosition(
		const float title_position_x, 
		const float title_position_y
	)
	{
		m_title_position.x = title_position_x;
		m_title_position.y = title_position_y;
	}

	[[nodiscard]]
	Vector2<float> getTitlePosition() const
	{
		return m_title_position;
	}

	void setHandleHeight(const float handle_height)
	{
		m_handle_height = handle_height;
	}


	[[nodiscard]]
	float getHandleHeight() const
	{
		return m_handle_height;
	}

	void setActive(const bool is_active = true)
	{
		m_is_active = is_active;
	}

	[[nodiscard]]
	bool getActive() const
	{
		return m_is_active;
	}

	void hide()
	{
		m_is_hided = true;
	}

	void show()
	{
		m_is_hided = false;
	}

protected:

	Vector2<float> m_title_position;

	float m_handle_height;

	bool m_is_active;

	bool m_is_hided;

};
_VGUI_END

_VGUI_BEGIN
template <	typename _Gui_target_type,
			typename _Backend_window_type  >
	class GuiBase :
	public _Gui_target_type
{
public:
	GuiBase() = default;

	void addWindow(_Backend_window_type* window)
	{
		m_windows.push_back(window);
	}

	void removeWindow(_Backend_window_type* window)
	{
		m_windows.remove(window);
	}

	void setActiveWindow(_Backend_window_type* window)
	{
		window->m_is_active = true;
		m_windows.remove(window);
		for (decltype(auto) widget_window : m_windows)
		{
			widget_window->m_is_active = false;
		}
		m_windows.push_back(window);
	}

protected:

	std::list<_Backend_window_type*> m_windows;

};
_VGUI_END


_VGUI_UTILITIES_BEGIN
[[nodiscard]]
inline bool is_mouse_entered(
	const _VGUI Vector2<int>& mouse,
	const _VGUI Vector2<float>& pos,
	const _VGUI Vector2<float>& size
)
{
	if (
		static_cast<float>(mouse.x) > static_cast<float>(pos.x) &&
		static_cast<float>(mouse.y) > static_cast<float>(pos.y) &&
		static_cast<float>(mouse.x) < static_cast<float>(pos.x) + static_cast<float>(size.x) &&
		static_cast<float>(mouse.y) < static_cast<float>(pos.y) + static_cast<float>(size.y)
		)
	{
		return true;
	}
	return false;
}
_VGUI_UTILITIES_END

#pragma once
#include <thread>
#include <utility>

#include "VGui.h"
#include "SFML/Graphics.hpp"
#include <mutex>


_VGUI_BEGIN
class GuiSFML;
class WindowSFML;
class WidgetSFML :
					virtual public WidgetBase,
					public sf::Drawable,
					public HandlerBase<const sf::Event&, const sf::Window&>
{

	friend class GuiSFML;
	friend class WindowSFML;

public:

	WidgetSFML() = default;

	WidgetSFML(
		const Vector2<float> position,
		const Vector2<float> size
	) :
		WidgetBase(position, size)
	{

	}

	void handleEvent(
		const sf::Event& event, 
		const sf::Window& window
	) override = 0;

	[[nodiscard]]
	bool isMouseEntered(
		const Vector2<int>& mouse
	) const override = 0;

};
_VGUI_END

_VGUI_UTILITIES_BEGIN
using GuiTargetSFML = _VGUI GuiTargetBase<_VGUI WidgetSFML, const sf::Event&, const sf::Window&>;
_VGUI_UTILITIES_END

_VGUI_BEGIN
class GuiSFML;
class ButtonSFML final :
				public ButtonBase,
				public WidgetSFML,
				public _VGUI_UTILITIES Textureable<sf::Texture>,
				public _VGUI_UTILITIES Textable<sf::Text>,
				public _VGUI_UTILITIES Shaderable<sf::Shader>
{
public:

	ButtonSFML(
		const Vector2<float> position = {},
		const Vector2<float> size = {}
	) :
		ButtonBase(position, size)
	{

	}

	ButtonSFML(
		const float pos_x,
		const float pos_y,
		const float size_x,
		const float size_y
	) :
		ButtonBase(pos_x, pos_y, size_x, size_y)
	{

	}

	bool isMouseEntered(
		const Vector2<int>& mouse
	) const override
	{
		if (
			(float)mouse.x > (float)this->m_position.x &&
			(float)mouse.y > (float)this->m_position.y &&
			(float)mouse.x < (float)this->m_position.x + (float)this->m_size.x &&
			(float)mouse.y < (float)this->m_position.y + (float)m_size.y
			)
		{
			return true;
		}
		return false;
	}

	void handleEvent(
		const sf::Event& event,
		const sf::Window& window
	) override
	{
		if (this->m_is_mouse_already_entered == false)
		{
			this->mouseEnteredWidget();
			m_is_mouse_already_entered = true;
			return;
		}
		if (this->m_is_mouse_already_entered == true)
		{
			if (
				event.mouseButton.button == sf::Mouse::Button::Left &&
				!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)
				)
			{
				this->onMouseUp(
					{ event.mouseButton.x, event.mouseButton.y },
					_VGUI MouseButton::Left
				);
				return;
			}
			if (
				event.mouseButton.button == sf::Mouse::Button::Left &&
				sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)
				)
			{
				this->onMouseDown(
					{ event.mouseButton.x, event.mouseButton.y },
					_VGUI MouseButton::Left
				);
				return;
			}
		}
	}

protected:

	void draw(
		sf::RenderTarget& target,
		const sf::RenderStates states
	) const override
	{
		target.draw(m_rectangle_shape_button);
		if (this->m_backend_text)
		{
			target.draw(*this->m_backend_text);
		}
	}

	void onSetShader() override
	{
		// NONE
	}

	void onSetSize() override
	{
		m_rectangle_shape_button.setSize(sf::Vector2f(this->m_size.x, this->m_size.y));
		if (this->m_backend_text)
		{
			this->m_backend_text->setPosition(
				m_position.x + m_rectangle_shape_button.getSize().x / 2 - 
				this->m_backend_text->getGlobalBounds().width,
				m_position.y + m_rectangle_shape_button.getSize().y / 2 - 
				this->m_backend_text->getGlobalBounds().height
			);
		}
	}

	void onSetPosition() override
	{
		m_rectangle_shape_button.setPosition(this->m_position.x, this->m_position.y);
		if (this->m_backend_text)
		{
			this->m_backend_text->setPosition(
				m_position.x + m_rectangle_shape_button.getSize().x / 2 - 
				this->m_backend_text->getGlobalBounds().width,
				m_position.y + m_rectangle_shape_button.getSize().y / 2 - 
				this->m_backend_text->getGlobalBounds().height
			);
		}
	}

	void onSetColor() override
	{
		m_rectangle_shape_button.setFillColor(*reinterpret_cast<sf::Color*>(&this->m_color));
	}

	void onSetTexture() override
	{
		m_rectangle_shape_button.setTexture(this->m_backend_texture);
	}

	void onSetText() override
	{
		
		this->m_backend_text->setOrigin(
			this->m_backend_text->getGlobalBounds().width / 2, 
			this->m_backend_text->getGlobalBounds().height / 1.20F
		);
		this->m_backend_text->setPosition(
			m_position.x + m_rectangle_shape_button.getSize().x / 2,
			m_position.y + m_rectangle_shape_button.getSize().y / 2
		);
	}

	void onSetBorderThickness() override
	{
		m_rectangle_shape_button.setOutlineThickness(this->m_border_thickness);
	}

	void onSetBorderColor() override
	{
		m_rectangle_shape_button.setOutlineColor(*reinterpret_cast<sf::Color*>(&this->m_border_color));
	}

private:

	sf::RectangleShape m_rectangle_shape_button;

};
_VGUI_END

_VGUI_BEGIN
class SliderSFML final :
					public SliderBase<sf::Shape>,
					public WidgetSFML,
					public _VGUI_UTILITIES Textureable<sf::Texture>,
					public _VGUI_UTILITIES Textable<sf::Text>,
					public _VGUI_UTILITIES Shaderable<sf::Shader>
{
public:

	SliderSFML() = default;

	SliderSFML(
		const Vector2<float> position,
		const Vector2<float> size
	) :
		SliderBase(position, size)
	{

	}

	SliderSFML(
		const float pos_x,
		const float pos_y,
		const float size_x,
		const float size_y
	) :
		SliderBase(pos_x, pos_y, size_x, size_y)
	{

	}

	bool isMouseEntered(
		const Vector2<int>& mouse
	) const override
	{
		sf::Vector2f position = sf::Vector2f(
			m_rectangle_shape_handle.getGlobalBounds().left, 
			m_rectangle_shape_handle.getGlobalBounds().top
		);
		sf::Vector2f size = sf::Vector2f(
			m_rectangle_shape_handle.getGlobalBounds().width,
			m_rectangle_shape_handle.getGlobalBounds().height
		);
		if (
			(float)mouse.x > position.x &&
			(float)mouse.y > position.y &&
			(float)mouse.x < position.x + size.x &&
			(float)mouse.y < position.y + size.y
			)
		{
			return true;
		}
		return false;
	}

	void mouseLeftWidget() override
	{
		if (!this->m_thread_wnd_movement_started)
		{
			_VGUI_UTILITIES call_lambdas(this->m_lambdas_mouse_left, *this, this->m_user_data);
		}
	}

	void handleEvent(
		const sf::Event& event, 
		const sf::Window& window
	) override
	{
		if (this->m_is_mouse_already_entered == false)
		{
			if (!this->m_thread_wnd_movement_started)
			{
				this->mouseEnteredWidget();
				m_is_mouse_already_entered = true;
				return;
			}
		}
		if (this->m_is_mouse_already_entered == true)
		{
			if (
				event.mouseButton.button == sf::Mouse::Button::Left &&
				!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)
				)
			{
				//up
				return;
			}
			if (
				event.mouseButton.button == sf::Mouse::Button::Left &&
				sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)
				)
			{
				if (!this->m_thread_wnd_movement_started)
				{
					std::thread thread_wnd_movement(
						[&]
						{
							this->m_thread_wnd_movement_started = true;
							const float origin_x = sf::Mouse::getPosition(window).x - m_rectangle_shape_handle.getPosition().x;
							const float old_handle_origin_x = m_rectangle_shape_handle.getOrigin().x;
							while (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
							{
								const float new_position_x = sf::Mouse::getPosition(window).x - origin_x;
								const float shape_body_position_x = m_rectangle_shape_body.getPosition().x;
								
								// If the cursor is located outside the slider on the left
								if (new_position_x < shape_body_position_x + old_handle_origin_x - m_rectangle_shape_handle.getSize().x / 2.F)
								{
									m_rectangle_shape_handle.setOrigin(
										m_rectangle_shape_handle.getSize().x / 2.F,
										m_rectangle_shape_handle.getOrigin().y
									);
								}

								// If the cursor is located outside the slider on the right
								else if (new_position_x > shape_body_position_x + m_rectangle_shape_body.getSize().x + old_handle_origin_x - m_rectangle_shape_handle.getSize().x / 2.F)
								{
									m_rectangle_shape_handle.setOrigin(
										m_rectangle_shape_handle.getSize().x / 2.F - m_rectangle_shape_body.getSize().x,
										m_rectangle_shape_handle.getOrigin().y
									);
								}

								// If the cursor has not gone beyond the slider
								else 
								{
									m_rectangle_shape_handle.setOrigin(
										m_rectangle_shape_handle.getPosition().x + old_handle_origin_x - new_position_x,
										m_rectangle_shape_handle.getOrigin().y
									);
								}

								// Set the slider value
								const float delta = m_maximal_slider_value - m_minimal_slider_value;
								const float scale = (-m_rectangle_shape_handle.getOrigin().x + m_rectangle_shape_handle.getSize().x / 2.F) / this->m_size.x * delta;
								this->m_slider_value = scale + m_minimal_slider_value;
								this->onHandleMove();

								// Sleep this thread
								std::this_thread::sleep_for(std::chrono::milliseconds(1000 / 165));
							}
							this->m_thread_wnd_movement_started = false;
						}
						);
					thread_wnd_movement.detach();
				}
				return;
			}
		}
	}

	sf::Shape& getBackendShapeSliderBody() override
	{
		return this->m_rectangle_shape_body;
	}

	sf::Shape& getBackendShapeSliderHandle() override
	{
		return this->m_rectangle_shape_handle;
	}

protected:
	

	void draw(
		sf::RenderTarget& target, 
		sf::RenderStates states
	) const override
	{
		target.draw(m_rectangle_shape_body);
		target.draw(m_rectangle_shape_handle);
		if (this->m_backend_text)
		{
			target.draw(*this->m_backend_text);
		}
	}

protected:

	void onSetShader() override
	{
		// NONE
	}

	void onSetText() override
	{
		// Set slider text label position
		this->m_backend_text->setPosition(
			m_text_label_position.x,
			m_text_label_position.y
		);
	}

	void onSetPosition() override
	{
		// Set slider body and handle position
		m_rectangle_shape_body.setPosition(this->m_position.x, this->m_position.y);
		m_rectangle_shape_handle.setPosition(this->m_position.x, this->m_position.y);
	}

	void onSetSize() override
	{
		// Set slider handle size
		m_rectangle_shape_handle.setSize(sf::Vector2f(this->m_handle_size.x, this->m_handle_size.y));

		// Set slider body size
		m_rectangle_shape_body.setSize(sf::Vector2f(this->m_size.x, this->m_size.y));
		m_rectangle_shape_body.setOrigin(0, -this->m_handle_size.y / 2.F + this->m_rectangle_shape_body.getSize().y / 2.F);
	}

	void onSetTexture() override
	{
		//Set slider handle texture
		m_rectangle_shape_handle.setTexture(this->m_backend_texture);

		// Set slider body texture
		m_rectangle_shape_body.setTexture(this->m_backend_texture);

		// Update texture rects
		onSetHandleTextureWidth();
	}

	void onSetColor() override
	{
		m_rectangle_shape_body.setFillColor(*reinterpret_cast<sf::Color*>(&this->m_color));
		m_rectangle_shape_handle.setFillColor(*reinterpret_cast<sf::Color*>(&this->m_color));
	}

	void onSetHandleTextureWidth() override
	{
		// Set slider handle texture rect
		m_rectangle_shape_handle.setTextureRect(sf::IntRect(
			0,
			0,
			this->m_handle_texture_width,
			this->m_backend_texture->getSize().y
		));

		// Set slider body texture rect
		m_rectangle_shape_body.setTextureRect(sf::IntRect(
			this->m_handle_texture_width,
			0,
			this->m_backend_texture->getSize().x - this->m_handle_texture_width,
			this->m_backend_texture->getSize().y
		));
	}

	void onSetTextLabelPosition() override
	{
		if (this->m_backend_text)
		{
			onSetText();
		}
	}

	void onSetSliderValue() override
	{
		const float delta = m_maximal_slider_value - m_minimal_slider_value;
		if (delta <= 0)
		{
			return;
		}
		const float scale =  m_rectangle_shape_body.getSize().x / -delta;
		m_rectangle_shape_handle.setOrigin(
			m_slider_value * scale + m_rectangle_shape_handle.getSize().x / 2,
		      m_rectangle_shape_handle.getOrigin().y
		);
		this->onHandleMove();
	}

	void onSetMaximalSliderValue() override
	{
		onSetSliderValue();
	}

	void onSetMinimalSliderValue() override
	{
		onSetSliderValue();
	}

private:

	sf::RectangleShape m_rectangle_shape_body;

	sf::RectangleShape m_rectangle_shape_handle;

	bool m_thread_wnd_movement_started;

};
_VGUI_END

_VGUI_BEGIN
class CheckBoxSFML final :
	public CheckBoxBase,
	public WidgetSFML,
	public _VGUI_UTILITIES Textureable<sf::Texture>,
	public _VGUI_UTILITIES Textable<sf::Text>,
	public _VGUI_UTILITIES Shaderable<sf::Shader*>
{
public:

	CheckBoxSFML() = default;

	CheckBoxSFML(
		const Vector2<float> position,
		const Vector2<float> size
	) :
		CheckBoxBase(position, size)
	{

	}

	CheckBoxSFML(
		const float pos_x,
		const float pos_y,
		const float size_x,
		const float size_y
	) :
		CheckBoxBase(pos_x, pos_y, size_x, size_y)
	{

	}

	void onSetTextLabelPosition() override
	{
		if (this->m_backend_text)
		{
			onSetText();
		}
	}

	void onSetColor() override
	{
		m_rectangle_shape_checkbox.setFillColor(*reinterpret_cast<sf::Color*>(&this->m_color));
	}

	void onSetPosition() override
	{
		m_rectangle_shape_checkbox.setPosition(this->m_position.x, this->m_position.y);
	}

	void onSetSize() override
	{
		m_rectangle_shape_checkbox.setSize(sf::Vector2f(this->m_size.x, this->m_size.y));
	}

	void handleEvent(
		const sf::Event& event, 
		const sf::Window& window
	) override
	{
		if (this->m_is_mouse_already_entered == false)
		{
			this->mouseEnteredWidget();
			m_is_mouse_already_entered = true;
			return;
		}
		if (this->m_is_mouse_already_entered == true)
		{
			if (
				event.mouseButton.button == sf::Mouse::Button::Left &&
				!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)
				)
			{
				if (this->m_bool == true)
				{
					this->m_bool = false;
					if (m_backend_texture)
					{
						m_rectangle_shape_checkbox.setTextureRect(sf::IntRect(
							0,
							0,
							this->m_backend_texture->getSize().x / 2,
							this->m_backend_texture->getSize().y
						));
					}
					this->onFalse();
				}
				else
				{
					this->m_bool = true;
					if (m_backend_texture)
					{
						m_rectangle_shape_checkbox.setTextureRect(sf::IntRect(
							this->m_backend_texture->getSize().x / 2,
							0,
							this->m_backend_texture->getSize().x / 2,
							this->m_backend_texture->getSize().y
						));
					}
					this->onTrue();
				}
				return;
			}
		}
	}

	bool isMouseEntered(
		const Vector2<int>& mouse
	) const override
	{
		if (
			(float)mouse.x > (float)this->m_position.x &&
			(float)mouse.y > (float)this->m_position.y &&
			(float)mouse.x < (float)this->m_position.x + (float)this->m_size.x &&
			(float)mouse.y < (float)this->m_position.y + (float)m_size.y
			)
		{
			return true;
		}
		return false;
	}

	void draw(
		sf::RenderTarget& target, 
		sf::RenderStates states
	) const override
	{
		if (m_backend_shader)
		{
			target.draw(m_rectangle_shape_checkbox, m_backend_shader[0]);
			if (m_backend_text)
			{
				target.draw(*m_backend_text, m_backend_shader[1]);
			}
		}
		else
		{
			target.draw(m_rectangle_shape_checkbox);
			if (m_backend_text)
			{
				target.draw(*m_backend_text);
			}
		}
	}

	void onSetTexture() override
	{
		this->m_rectangle_shape_checkbox.setTexture(this->m_backend_texture);
		m_rectangle_shape_checkbox.setTextureRect(sf::IntRect(
			0,
			0,
			this->m_backend_texture->getSize().x / 2,
			this->m_backend_texture->getSize().y
		));
	}

	void onSetText() override
	{
		// Set slider text label position
		this->m_backend_text->setPosition(
			m_text_label_position.x,
			m_text_label_position.y
		);
	}

	void onSetShader() override
	{
		throw std::logic_error("The method or operation is not implemented.");
	}

protected:

	sf::RectangleShape m_rectangle_shape_checkbox;

};
_VGUI_END

_VGUI_BEGIN
class TextBoxSFML final : 
	public TextBoxBase, 
	public WidgetSFML,
	public _VGUI_UTILITIES Textureable<sf::Texture>,
	public _VGUI_UTILITIES Textable<sf::Text>,
	public _VGUI_UTILITIES Shaderable<sf::Shader*>
{
public:

	TextBoxSFML(
		const uint16_t textbox_resolution_width, 
		const uint16_t textbox_resolution_height
	) 
	{
		Initialize(textbox_resolution_width, textbox_resolution_height);
	}

	~TextBoxSFML()
	{
		m_line_thread_atomic_ready.store(true, std::memory_order_relaxed);
	}

protected:

	void onSetTextPosition() override
	{
		if (this->m_backend_text != nullptr)
		{
			onSetText();
		}
	}

	void onSetColor() override
	{
		m_rectangle_shape_textbox.setFillColor(*reinterpret_cast<sf::Color*>(&this->m_color));
	}

	void onSetPosition() override
	{
		m_rectangle_shape_textbox.setPosition(this->m_position.x, this->m_position.y);
	}

	void onSetSize() override
	{
		m_rectangle_shape_textbox.setSize(sf::Vector2f(this->m_size.x, this->m_size.y));
	}

	void onSetTexture() override
	{
		m_rectangle_shape_textbox_textured.setTexture(this->m_backend_texture);
	}

	void onSetText() override
	{
		this->m_backend_text->setPosition(this->m_text_position.x, this->m_text_position.y);
		m_line.setFillColor(this->m_backend_text->getFillColor());
		m_line.setSize(sf::Vector2f(
			this->m_backend_text->getLetterSpacing(),
			this->m_backend_text->getCharacterSize()
		));
		m_line.setPosition(this->m_text_position.x, this->m_text_position.y);
	}

	void onSetShader() override
	{
		
	}

private:

	void Initialize(
		const uint16_t textbox_resolution_width,
		const uint16_t textbox_resolution_height
	)
	{
		m_render_texture_textbox.create(textbox_resolution_width, textbox_resolution_height);
		m_rectangle_shape_textbox.setTexture(&m_render_texture_textbox.getTexture());
		m_rectangle_shape_textbox_textured.setSize(sf::Vector2f(textbox_resolution_width, textbox_resolution_height));
		m_line_thread = std::thread(
			[&]()
			{
				static bool is_line_visable = true;
				constexpr int delim = 4;
				while (!m_line_thread_atomic_ready.load(std::memory_order_relaxed))
				{
					if (this->m_is_mouse_already_entered != true)
					{
						this->m_line.setFillColor(sf::Color(0, 0, 0, 0));
						std::this_thread::sleep_for(std::chrono::milliseconds(1000 / delim));
						continue;
					}

					if (is_line_visable == true)
					{
						this->m_line.setFillColor(sf::Color(0, 0, 0, 0));
						is_line_visable = false;
					}

					else
					{
						if (this->m_backend_text != nullptr)
						{
							this->m_line.setFillColor(this->m_backend_text->getFillColor());
						}
						is_line_visable = true;
					}

					std::this_thread::sleep_for(std::chrono::milliseconds(1000 / delim));
				} 
			}
		);
		if (m_line_thread.joinable())
		{
			m_line_thread.detach();
		}
	}

protected:

	void handleEvent(
		const sf::Event& event,
		const sf::Window& window
	) override
	{
		if (this->m_is_mouse_already_entered == false)
		{
			this->mouseEnteredWidget();
			m_is_mouse_already_entered = true;
			return;
		}
		if (this->m_is_mouse_already_entered == true)
		{
			if (event.type == event.TextEntered)
			{
				if (this->m_backend_text != nullptr)
				{
					if (event.text.unicode == 8)
					{
						this->m_backend_text->setString(
							this->m_backend_text->getString().substring(0, this->m_backend_text->getString().getSize() - 1)
						);
					}
					else if (event.text.unicode == 13)
					{
						this->m_backend_text->setString(this->m_backend_text->getString() + L"\n");
					}
					else if (event.text.unicode == 22)
					{
						this->m_backend_text->setString(this->m_backend_text->getString() + sf::Clipboard::getString());
					}
					else
					{
						this->m_backend_text->setString(this->m_backend_text->getString() + event.text.unicode);
					}
					this->m_line.setOrigin(-(this->m_backend_text->getGlobalBounds().width + this->m_backend_text->getLetterSpacing()), 0);
					std::cout << (int)event.text.unicode << std::endl;
				}
			}
		}
	}

	bool isMouseEntered(
		const Vector2<int>& mouse
	) const override
	{
		if (
			(float)mouse.x > (float)this->m_position.x &&
			(float)mouse.y > (float)this->m_position.y &&
			(float)mouse.x < (float)this->m_position.x + (float)this->m_size.x &&
			(float)mouse.y < (float)this->m_position.y + (float)m_size.y
			)
		{
			return true;
		}
		return false;
	}

	void draw(
		sf::RenderTarget& target,
		sf::RenderStates states
	) const override
	{
		//m_rectangle_shape_textbox_textured.setSize(sf::Vector2f(target.getSize().x, target.getSize().y));
		m_render_texture_textbox.clear();
		if (m_backend_shader != nullptr)
		{
			m_render_texture_textbox.draw(m_rectangle_shape_textbox_textured, m_backend_shader[0]);
			if (m_backend_text)
			{
				m_render_texture_textbox.draw(*m_backend_text, m_backend_shader[1]);
			}
		}
		else
		{
			m_render_texture_textbox.draw(m_rectangle_shape_textbox_textured);
			if (m_backend_text)
			{
				m_render_texture_textbox.draw(*m_backend_text);
			}
		}
		m_render_texture_textbox.draw(m_line);
		m_render_texture_textbox.display();		
		target.draw(m_rectangle_shape_textbox);
	}

private:

	mutable sf::RenderTexture m_render_texture_textbox;

	sf::RectangleShape m_rectangle_shape_textbox;

	sf::RectangleShape m_rectangle_shape_textbox_textured;

	sf::RectangleShape m_line;

	std::thread m_line_thread;

	std::atomic<bool> m_line_thread_atomic_ready{ false };

};
_VGUI_END

_VGUI_BEGIN
class WindowSFML :
					public sf::Drawable,
					public WindowBase<_VGUI_UTILITIES GuiTargetSFML>,
					public _VGUI_UTILITIES Textureable<sf::Texture>,
					public _VGUI_UTILITIES Textable<sf::Text>,
					public _VGUI_UTILITIES Shaderable<sf::Shader*>
{

	friend class GuiSFML;

public:

	WindowSFML(const Vector2<float> window_size)
	{
		initialize(window_size.x, window_size.y);
	}

	WindowSFML(
		const float window_size_x,
		const float window_size_y
	)
	{
		initialize(window_size_x, window_size_y);
	}

	bool isMouseEntered(
		const Vector2<int>& mouse
	) const override
	{
		if (
			(float)mouse.x > (float)this->m_position.x &&
			(float)mouse.y > (float)this->m_position.y &&
			(float)mouse.x < (float)this->m_position.x + (float)this->m_size.x &&
			(float)mouse.y < (float)this->m_position.y + (float)m_size.y
			)
		{
			return true;
		}
		return false;
	}

protected:

	void draw(
		sf::RenderTarget& target,
		const sf::RenderStates
	) const override
	{
		m_render_texture.clear(sf::Color(0, 0, 0, 0));
		if (this->m_backend_shader != nullptr)
		{
			m_render_texture.draw(m_rectangle_shape_render_texture, this->m_backend_shader[0]);
			m_render_texture.draw(*this->m_backend_text, this->m_backend_shader[1]);
		}
		else
		{
			m_render_texture.draw(m_rectangle_shape_render_texture);
			m_render_texture.draw(*this->m_backend_text);
		}
		for (decltype(auto) widget : this->m_widgets)
		{
			m_render_texture.draw(*widget, m_inner_transform.getTransform());
		}
		m_render_texture.display();
		target.draw(m_rectangle_shape_window);
	}


	void handleEvent(
		const sf::Event& event,
		const sf::Window& window
	) override
	{

		const auto mouse_pos_int = Vector2<int>(
			sf::Mouse::getPosition(window).x - (m_rectangle_shape_window.getPosition().x),
			sf::Mouse::getPosition(window).y - (m_rectangle_shape_window.getPosition().y)
			);

		const auto window_size = window.getSize();

		if (
			mouse_pos_int.x > 0 && mouse_pos_int.y > 0 &&
			mouse_pos_int.x < window_size.x &&
			mouse_pos_int.y < window_size.y
			)
		{
			for (decltype(auto) widget : this->m_widgets)
			{
				if (widget != nullptr)
				{
					const auto widget_position = Vector2<float>(
						widget->getPosition().x,
						widget->getPosition().y
						);

					const auto widget_size = Vector2<float>(
						widget->getSize().x,
						widget->getSize().y
						);

					if (widget->isMouseEntered(mouse_pos_int))
					{
						widget->handleEvent(event, window);
					}
					else
					{
						if (widget->m_is_mouse_already_entered)
						{
							widget->mouseLeftWidget();
							widget->m_is_mouse_already_entered = false;
						}
					}
				}
			}
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		{
			if (!this->m_thread_wnd_movement_started)
			{
				if (_VGUI_UTILITIES is_mouse_entered(mouse_pos_int, {}, Vector2(this->getSize().x, this->m_handle_height)))
				{
					std::thread thread_wnd_movement(
						[&]
						{
							this->m_thread_wnd_movement_started = true;
							const float origin_x = sf::Mouse::getPosition(window).x - this->m_rectangle_shape_window.getPosition().x;
							const float origin_y = sf::Mouse::getPosition(window).y - this->m_rectangle_shape_window.getPosition().y;
							while (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
							{
								this->setPosition(
									sf::Mouse::getPosition(window).x - origin_x, 
									sf::Mouse::getPosition(window).y - origin_y
								);
								std::this_thread::sleep_for(std::chrono::milliseconds(1000/165));
							}
							this->m_thread_wnd_movement_started = false;
						}
						);
					thread_wnd_movement.detach();
				}
			}
		}
	}

private:

	void onSetShader() override
	{
		// NONE
	}

	void onSetPosition() override
	{
		m_inner_transform.setOrigin(this->m_position.x, this->m_position.y);
		m_rectangle_shape_window.setPosition(this->m_position.x, this->m_position.y);
	}

	void onSetSize() override
	{
		m_rectangle_shape_window.setSize(sf::Vector2f(this->m_size.x, this->m_size.y));
	}

	void onSetTexture() override
	{
		m_rectangle_shape_render_texture.setTexture(this->m_backend_texture);
	}

	void onSetText() override
	{
		this->m_backend_text->setPosition(m_title_position.x, m_title_position.y);
	}

private:

	void initialize(
		const float window_size_x, 
		const float window_size_y
	)
	{
		m_render_texture.create(window_size_x, window_size_y);
		m_rectangle_shape_render_texture.setSize(sf::Vector2f(window_size_x, window_size_y));
		m_rectangle_shape_window.setTexture(&m_render_texture.getTexture());
	}

private:

	sf::Transformable m_inner_transform;

	mutable sf::RectangleShape m_rectangle_shape_window;

	mutable sf::RenderTexture m_render_texture;

	sf::RectangleShape m_rectangle_shape_render_texture;

	bool m_thread_wnd_movement_started = false;

};
_VGUI_END

_VGUI_BEGIN
class GuiSFML :
	public GuiBase<_VGUI_UTILITIES GuiTargetSFML, WindowSFML>,
		public sf::Drawable
{
public:

	GuiSFML(
		const unsigned width, 
		const unsigned height, 
		const sf::ContextSettings& context_settings = sf::ContextSettings()
	)
	{
		m_render_texture_gui.create(width, height, context_settings);
		m_rectangle_shape_gui.setTexture(&m_render_texture_gui.getTexture());
		m_rectangle_shape_gui.setScale(1, -1);
	}

	void draw(
		sf::RenderTarget& target, 
		const sf::RenderStates states
	) const override
	{
		m_render_texture_gui.clear(sf::Color(0, 0, 0, 0));
		for (decltype(auto) widget : this->m_widgets)
		{
			m_render_texture_gui.draw(*widget);
		}
		for (decltype(auto) widget_window : this->m_windows)
		{
			if (!widget_window->m_is_hided)
			{
				m_render_texture_gui.draw(*widget_window);
			}
		}

		m_rectangle_shape_gui.setSize(sf::Vector2f(target.getSize()));
		m_rectangle_shape_gui.setOrigin(1, m_rectangle_shape_gui.getSize().y);

		target.draw(m_rectangle_shape_gui);
	}

	bool isMouseEntered(
		const Vector2<int>& mouse
	) const override
	{
		return true;
	}

public:
	void handleEvent(
		const sf::Event& event, 
		const sf::Window& window
	) override
	{
		const auto mouse_pos = Vector2<int>(
			sf::Mouse::getPosition(window).x, 
			sf::Mouse::getPosition(window).y
		);
		const auto window_size = window.getSize();

		if (
			mouse_pos.x > 0 && mouse_pos.y > 0 &&
			mouse_pos.x < window_size.x &&
			mouse_pos.y < window_size.y
			)
		{
			for (decltype(auto) widget : this->m_widgets)
			{
				if (widget != nullptr)
				{
					const auto widget_position = Vector2<float>(
						widget->getPosition().x,
						widget->getPosition().y
						);

					const auto widget_size = Vector2<float>(
						widget->getSize().x,
						widget->getSize().y
						);


					if (widget->isMouseEntered(mouse_pos))
					{
						widget->handleEvent(event, window);
					}
					else
					{
						if (widget->m_is_mouse_already_entered)
						{
							widget->mouseLeftWidget();
							widget->m_is_mouse_already_entered = false;
						}
					}
				}
			}
		}

		for (decltype(auto) widget_window : this->m_windows)
		{
			if (widget_window->m_is_active)
			{
				widget_window->handleEvent(
					event,
					window
				);
				break;
			}
		}
	}

private:

	mutable sf::RectangleShape m_rectangle_shape_gui;

	mutable sf::RenderTexture m_render_texture_gui;

};
_VGUI_END

_VGUI_BEGIN
class TextRenderer
{
public:

	TextRenderer() = default;

	TextRenderer(
		const sf::String& text, 
		const sf::Font& font, 
		unsigned int character_size = 30
	) : 
		m_text(text, font, character_size)
	{

	}

	[[nodiscard]]
	const sf::Texture& getRenderedTexture() const
	{
		return m_render_texture.getTexture();
	}

	void setString(std::wstring text)
	{
		m_text.setString(text);
	}


	void setString(std::string text)
	{
		m_text.setString(text);
	}

	[[nodiscard]]
	sf::Text& getText()
	{
		return m_text;
	}

	virtual void render() = 0;

protected:
	
	sf::RenderTexture m_render_texture;

	sf::Text m_text;

};
_VGUI_END
	
	#pragma once
#include "VGui_sfml.h"
#include <map>
#include <fstream>
#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/OpenGL.hpp>


using config_map_t = std::map<std::string, std::string>;

class ConfigReader
{
public:
	[[nodiscard]]
	static config_map_t readConfFile(const std::string& path)
	{
		std::fstream file;
		file.open(path);
		std::string time_t;
		std::string filetxt;
		while (getline(file, time_t)) 
		{
			filetxt += time_t;
		}
		config_map_t output;
		std::string t;
		std::string tt;
		for (size_t i = 0; i < filetxt.length(); i++)
		{
			if (filetxt[i] != ' ')
			{
				while (filetxt[i] != '=')
				{
					if (filetxt[i] != ' ')
					{
						t += filetxt[i];
					}
					i++;
				}
				i++;
				while (filetxt[i] != ';')
				{
					if (filetxt[i] != ' ')
					{
						tt += filetxt[i];
					}
					i++;
				}
				output[t] = tt;
				t = "";
				tt = "";
			}
		}
		file.close();
		return output;
	}

	static void writeConfFile(const config_map_t& input, const std::string& path)
	{
		std::fstream file;
		file.open(path);
		std::string output;
		for (auto& item : input)
		{
			output += item.first + "=" + item.second + ";";
		}
		file << output;
		file.close();
	}

};

inline sf::Texture* __fastcall load_texture_sfml_with_mask(
	const std::string& path, 
	const sf::Color& mask
)
{
	sf::Image img;
	if (!img.loadFromFile(path))
	{
		return nullptr;
	}

	for (int y = 0; y < img.getSize().y; y++)
	{
		for (int x = 0; x < img.getSize().x; x++)
		{
			if (img.getPixel(x, y).r > mask.r && img.getPixel(x, y).g > mask.g && img.getPixel(x, y).b > mask.b)
			{
				img.setPixel(x, y, sf::Color(0, 0, 0, 0));
			}
		}
	}

	const auto tex = new sf::Texture;

	if (!tex->loadFromImage(img))
	{
		return nullptr;
	}

	return tex;
}

inline sf::Texture* __fastcall load_texture_sfml(
	const std::string& path
)
{
	const auto texture = new sf::Texture;
	if (!texture->loadFromFile(path))
	{
		return nullptr;
	}
	return texture;
}

template <
	typename _Lambda_error_type,
	typename _Boolable_type		>
	inline void show_error_if_failed(
		_Lambda_error_type lambda_error,
		_Boolable_type boolable_arg
	)
{
	if (!boolable_arg)
	{
		lambda_error();
	}
}

template <
			typename _Lambda_error_type, 
			typename _Boolable_type,
			typename... _Boolable_types		>
inline void show_error_if_failed(
	_Lambda_error_type lambda_error,
	_Boolable_type boolable_arg,
	_Boolable_types... boolable_args
)
{
	if (!boolable_arg)
	{
		lambda_error();
	}
	else
	{
		show_error_if_failed(lambda_error, boolable_args...);
	}
}

class PageResources
{
public:

	static inline std::string setings_path = "settings/default.txt";

	static inline bool is_init = false;

	static inline sf::Color default_mask = sf::Color(240, 240, 240);

	static inline config_map_t config_map;

	static inline sf::Cursor cursor;

	static inline sf::Font font;

	static inline sf::Texture* slider_texture;

	static inline sf::Texture* text_texture;

	static inline sf::Texture* checkbox_texture;

	static inline sf::Texture* textbox_texture;

	static inline sf::Texture* button_green_texture;

	static inline sf::Texture* button_purple_texture;

	static inline sf::Texture* button_orange_texture;

	static inline uint8_t fps = 165;

	static void initialize()
	{
		if (!is_init)
		{
			// Load settings file
			config_map = ConfigReader::readConfFile(setings_path);

			// Load default window's cursor
			const sf::Image image_cursor = load_texture_sfml_with_mask(config_map["cursor"], default_mask)->copyToImage();
			bool is_default_cursor_loaded = cursor.loadFromPixels(image_cursor.getPixelsPtr(), image_cursor.getSize(), {});
				
			// Load default font
			bool is_default_font_loaded = font.loadFromFile(config_map["font"]);

			// Load the default slider texture
			slider_texture = load_texture_sfml_with_mask(config_map["slider_texture"], default_mask);

			text_texture = load_texture_sfml_with_mask(config_map["text_texture"], default_mask);
			text_texture->setRepeated(true);

			checkbox_texture = load_texture_sfml_with_mask(config_map["checkbox_texture"], default_mask);

			textbox_texture = load_texture_sfml_with_mask(config_map["textbox_texture"], default_mask);

			button_green_texture = load_texture_sfml_with_mask(config_map["button_green_texture"], default_mask);
			button_purple_texture = load_texture_sfml_with_mask(config_map["button_purple_texture"], default_mask);
			button_orange_texture = load_texture_sfml_with_mask(config_map["button_orange_texture"], default_mask);

			// Deallocate config_map's memory
			config_map.clear();

			show_error_if_failed(
				[]() {

				}, 
				is_default_cursor_loaded, 
				is_default_font_loaded, 
				slider_texture,
				text_texture
			);

			is_init = true;
		}
	}

	class MainMenu
	{
	public:
		
		static inline std::string setings_path = "settings/main_menu.txt";

		static inline bool is_init = false;

		static inline config_map_t config_map;

		static inline sf::Texture* texture_window;

		static inline sf::Texture* texture_background;

		static inline sf::Sound sound_main_menu;
		static inline sf::SoundBuffer sound_buffer_main_menu;

		static void initialize()
		{
			if (!is_init)
			{
				// Load settings file of main menu
				config_map = ConfigReader::readConfFile(setings_path);

				// Load textures of main menu
				texture_window = load_texture_sfml_with_mask(config_map["texture_window"], default_mask);
				texture_background = load_texture_sfml(config_map["texture_background"]);

				// Load music of main menu
				sound_buffer_main_menu.loadFromFile(config_map["sound_main_menu"]);
				sound_main_menu.setBuffer(sound_buffer_main_menu);
				sound_main_menu.setLoop(true);

				// Deallocate config_map's memory
				config_map.clear();
				is_init = true;
			}
		}

	};

};

class PageBase : public sf::Drawable
{
public:

	PageBase(
		const unsigned width,
		const unsigned height,
		const sf::ContextSettings& context_settings = sf::ContextSettings()
	) :
		m_gui(width, height, context_settings),
		m_is_active(false)
	{

	}

	virtual void handleEvent(
		const sf::Event& event,
		const sf::Window& window
	) = 0;

	[[nodiscard]]
	vgui::GuiSFML* getGui()
	{
		return &m_gui;
	}

	[[nodiscard]]
	bool isActive() const 
	{
		return m_is_active;
	}

	void setActive(const bool is_active)
	{
		m_is_active = is_active;
	}

protected:

	vgui::GuiSFML m_gui;

	bool m_is_active;

};

class WindowBase
{
public:

	WindowBase(
		float width,
		float height
	) : 
		m_window(vgui::Vector2<float>(width, height))
	{

	}

	virtual void create(
		vgui::GuiSFML* gui
	) = 0;

	[[nodiscard]]
	vgui::WindowSFML* getWindow()
	{
		return &m_window;
	}

protected:

	vgui::WindowSFML m_window;

};

class MultithreadShaderRenderer
{
public:

	using multithread_shader_render_lambda = bool(*)(sf::Shader* shader);

	~MultithreadShaderRenderer() = default;

	MultithreadShaderRenderer() = default;

	MultithreadShaderRenderer(
		sf::Shader* shader, 
		multithread_shader_render_lambda* multithread_shader_render_lambda = nullptr
	) :
		m_shader(shader),
		m_multithread_shader_render_lambda(multithread_shader_render_lambda)
	{

	}

	void bindMultithreadShaderRenderLambda(
		multithread_shader_render_lambda* multithread_shader_render_lambda
	)
	{
		m_multithread_shader_render_lambda = multithread_shader_render_lambda;
	}

	void startRendering()
	{
		m_thread = std::thread(
			[&]()
			{
				while((*m_multithread_shader_render_lambda)(m_shader));
			}
		);
		m_thread.detach();
	}

private:

	sf::Shader* m_shader = nullptr;

	multithread_shader_render_lambda* m_multithread_shader_render_lambda = nullptr;

	std::thread m_thread;

};

///////////////////// GUI PAGES AND WINDOWS ///////////////////////
class PageMainMenu;
class WindowSettings;
class WindowSettingsVolume;
///////////////////// PAGE MANAGER ///////////////////////

class PagesAndWindows
{
public:

	static void Initialize(
		sf::Window& sfml_window
	);

	static void setCurrentPage(
		PageBase* current_page
	)
	{
		if (m_current_page != nullptr)
		{
			m_current_page->setActive(false);
		}
		m_current_page = current_page;
		if (m_current_page != nullptr)
		{
			m_current_page->setActive(true);
		}
	}

	[[nodiscard]]
	static PageBase* getCurrentPage()
	{
		return m_current_page;
	}

	static inline std::unique_ptr<PageBase> page_main_menu				= nullptr;

	static inline std::unique_ptr<PageBase> page_game					= nullptr;

	static inline std::unique_ptr<PageBase> page_level_redactor			= nullptr;

	static inline std::unique_ptr<WindowBase> window_main_menu			= nullptr;

	static inline std::unique_ptr<WindowBase> window_settings			= nullptr;

	static inline std::unique_ptr<WindowBase> window_settings_volume	= nullptr;

	static inline std::unique_ptr<WindowBase> window_settings_display	= nullptr;

	static inline sf::Window* sfml_window;

private:

	static inline PageBase* m_current_page				= nullptr;

};

class GuiLambdas
{
public:

	static void onMouseEntered(vgui::WidgetBase& widget, void*)
	{
		widget.setColor(vgui::Color(200, 200, 200, 255));
	}

	static void onMouseLeft(vgui::WidgetBase& widget, void*)
	{
		widget.setColor(vgui::Color(255, 255, 255, 255));
	}

	static void onMouseDown(vgui::WidgetBase& widget, void*)
	{
		widget.setColor(vgui::Color(100, 100, 100, 255));
	}

	static void onMouseUp(vgui::WidgetBase& widget, void*)
	{
		widget.setColor(vgui::Color(255, 255, 255, 255));
	}

	static void onMouseClose(vgui::WidgetBase&, void*)
	{
		exit(1);
	}

	static void onEnableVSync(vgui::WidgetBase&, void*)
	{
		PagesAndWindows::sfml_window->setVerticalSyncEnabled(true);
	}

	static void onDisableVSync(vgui::WidgetBase&, void*)
	{
		PagesAndWindows::sfml_window->setVerticalSyncEnabled(false);
	}

	static void onClickButtonOpenSettings(vgui::WidgetBase& widget, void*)
	{
		PagesAndWindows::window_main_menu->getWindow()->setActive(false);
		PagesAndWindows::getCurrentPage()->getGui()->setActiveWindow(PagesAndWindows::window_settings->getWindow());
		PagesAndWindows::window_settings->getWindow()->show();
		PagesAndWindows::window_settings->getWindow()->setActive(true);
	}

	static void onClickButtonOpenWindowVolumeSettings(vgui::WidgetBase& widget, void*)
	{
		PagesAndWindows::window_settings->getWindow()->setActive(false);
		PagesAndWindows::getCurrentPage()->getGui()->setActiveWindow(PagesAndWindows::window_settings_volume->getWindow());
		PagesAndWindows::window_settings_volume->getWindow()->show();
		PagesAndWindows::window_settings_volume->getWindow()->setActive(true);
	}

	static void onClickButtonOpenWindowDisplaySettings(vgui::WidgetBase& widget, void*)
	{
		PagesAndWindows::window_settings->getWindow()->setActive(false);
		PagesAndWindows::getCurrentPage()->getGui()->setActiveWindow(PagesAndWindows::window_settings_display->getWindow());
		PagesAndWindows::window_settings_display->getWindow()->show();
		PagesAndWindows::window_settings_display->getWindow()->setActive(true);
	}

	static void onClickButtonSaveSettings(vgui::WidgetBase& widget, void*)
	{
		PagesAndWindows::window_settings->getWindow()->setActive(false);
		PagesAndWindows::window_settings->getWindow()->hide();
		PagesAndWindows::getCurrentPage()->getGui()->setActiveWindow(PagesAndWindows::window_main_menu->getWindow());
		PagesAndWindows::window_main_menu->getWindow()->show();
		PagesAndWindows::window_main_menu->getWindow()->setActive(true);
	}

	static void onClickButtonAcceptVolume(vgui::WidgetBase& widget, void*)
	{
		PagesAndWindows::window_settings_volume->getWindow()->setActive(false);
		PagesAndWindows::window_settings_volume->getWindow()->hide();
		PagesAndWindows::getCurrentPage()->getGui()->setActiveWindow(PagesAndWindows::window_settings->getWindow());
		PagesAndWindows::window_settings->getWindow()->show();
		PagesAndWindows::window_settings->getWindow()->setActive(true);
	}

	static void onClickButtonAcceptDisplay(vgui::WidgetBase& widget, void*)
	{
		PagesAndWindows::window_settings_display->getWindow()->setActive(false);
		PagesAndWindows::window_settings_display->getWindow()->hide();
		PagesAndWindows::getCurrentPage()->getGui()->setActiveWindow(PagesAndWindows::window_settings->getWindow());
		PagesAndWindows::window_settings->getWindow()->show();
		PagesAndWindows::window_settings->getWindow()->setActive(true);
	}

	static void onSliderVolumeMove(vgui::WidgetBase& , void* ptr_slider)
	{
		auto slider = reinterpret_cast<vgui::SliderSFML*>(ptr_slider);
		if (slider)
		{
			PageResources::MainMenu::sound_main_menu.setVolume(slider->getSliderValue());
			std::wstring l_str = L"ГРОМКОСТЬ МУЗЫКИ: ";
			l_str += std::to_wstring((uint16_t)PageResources::MainMenu::sound_main_menu.getVolume());
			slider->getBackendText()->setString(l_str);
		}
	}

	static void onSliderVolumeEffMove(vgui::WidgetBase&, void* ptr_slider)
	{
		auto slider = reinterpret_cast<vgui::SliderSFML*>(ptr_slider);
		if (slider)
		{
			PageResources::MainMenu::sound_main_menu.setVolume(slider->getSliderValue());
			std::wstring l_str = L"ГРОМКОСТЬ ЭФФЕКТОВ: ";
			l_str += std::to_wstring((uint16_t)PageResources::MainMenu::sound_main_menu.getVolume());
			slider->getBackendText()->setString(l_str);
		}
	}

	static void onSliderFPSMove(vgui::WidgetBase&, void* ptr_slider)
	{
		auto slider = reinterpret_cast<vgui::SliderSFML*>(ptr_slider);
		if (slider)
		{
			PageResources::fps = slider->getSliderValue();
			PagesAndWindows::sfml_window->setFramerateLimit(PageResources::fps);
			std::wstring l_str = L"FPS: ";
			l_str += std::to_wstring((uint16_t)slider->getSliderValue());
			slider->getBackendText()->setString(l_str);
		}
	}

	static void onClickButtonPlayZumaGame(vgui::WidgetBase&, void*)
	{
		PagesAndWindows::setCurrentPage(PagesAndWindows::page_game.get());
	}

	static inline MultithreadShaderRenderer::multithread_shader_render_lambda rendererOfWindow = 
	[](sf::Shader* shader) -> bool
	{
		static float ticks = 0;	
		shader->setUniform("ticks", ticks);
		ticks++;
		std::this_thread::sleep_for(std::chrono::milliseconds(1000/(PageResources::fps + 1)));
		return true;
	};

};

class WindowSettingsVolume final : public WindowBase
{
public:

	WindowSettingsVolume() :
		WindowBase(500.0F, 400.0F)
	{
		// Main menu initialization
		PageResources::MainMenu::initialize();

		// Slider "Volume" initialization
		m_slider_volume.setPosition(140, 100);
		m_slider_volume.setHandleSize(25, 50);
		m_slider_volume.setSize(225, 50);
		m_slider_volume.addOnMouseEnteredLambda(GuiLambdas::onMouseEntered);
		m_slider_volume.addOnMouseLeftLambda(GuiLambdas::onMouseLeft);
		m_slider_volume.addOnHandleMoveLambda(GuiLambdas::onSliderVolumeMove);
		m_slider_volume.setTextLabelPosition(m_slider_volume.getPosition().x, m_slider_volume.getPosition().y - 25);
		sf::Text* text_slider_volume = new sf::Text(L"ГРОМКОСТЬ МУЗЫКИ: 20", PageResources::font, 20);
		m_slider_volume.setBackendText(text_slider_volume);
		m_slider_volume.getBackendText()->setFillColor(sf::Color::Red);
		m_slider_volume.setMinimalSliderValue(0);
		m_slider_volume.setMaximalSliderValue(100);
		m_slider_volume.setSliderValue(20);
		m_slider_volume.setBackendTexture(PageResources::slider_texture);
		m_slider_volume.setHandleTextureWidth(43);
		m_slider_volume.setUserData(&m_slider_volume);

		// Slider "Volume of effects" initialization
		m_slider_volume_eff.setPosition(140, 100 + 85);
		m_slider_volume_eff.setHandleSize(25, 50);
		m_slider_volume_eff.setSize(225, 50);
		m_slider_volume_eff.addOnMouseEnteredLambda(GuiLambdas::onMouseEntered);
		m_slider_volume_eff.addOnMouseLeftLambda(GuiLambdas::onMouseLeft);
		m_slider_volume_eff.addOnHandleMoveLambda(GuiLambdas::onSliderVolumeEffMove);
		m_slider_volume_eff.setTextLabelPosition(m_slider_volume_eff.getPosition().x, m_slider_volume_eff.getPosition().y - 25);
		sf::Text* text_slider_volume_eff = new sf::Text(L"ГРОМКОСТЬ ЭФФЕКТОВ: 20", PageResources::font, 20);
		m_slider_volume_eff.setBackendText(text_slider_volume_eff);
		m_slider_volume_eff.getBackendText()->setFillColor(sf::Color::Red);
		m_slider_volume_eff.setMinimalSliderValue(0);
		m_slider_volume_eff.setMaximalSliderValue(100);
		m_slider_volume_eff.setSliderValue(20);
		m_slider_volume_eff.setBackendTexture(PageResources::slider_texture);
		m_slider_volume_eff.setHandleTextureWidth(43);
		m_slider_volume_eff.setUserData(&m_slider_volume_eff);

		// Button "Accept"
		m_button_accept.setSize(225, 60);
		m_button_accept.setPosition(135, 400 - 125);
		m_button_accept.setBackendTexture(PageResources::button_green_texture);
		m_button_accept.addOnMouseEnteredLambda(GuiLambdas::onMouseEntered);
		m_button_accept.addOnMouseLeftLambda(GuiLambdas::onMouseLeft);
		m_button_accept.addOnMouseDownLambda(GuiLambdas::onMouseDown);
		m_button_accept.addOnMouseUpLambda(GuiLambdas::onMouseUp);
		m_button_accept.addOnMouseUpLambda(GuiLambdas::onClickButtonAcceptVolume);
		m_button_accept.setBackendText(new sf::Text(L"ПРИНЯТЬ", PageResources::font, 30));
		m_button_accept.getBackendText()->setFillColor(sf::Color::Black);
		m_button_accept.setUserData(this);

		// Gui-Window initialization
		m_window.setSize(500, 400);
		m_window.setBackendTexture(PageResources::MainMenu::texture_window);
		m_window.setPosition(300, 100);
		m_window.setTitlePosition(60, 17);
		m_window.setHandleHeight(50);
		m_window.setBackendText(new sf::Text(L"НАСТРОЙКИ ЗВУКА", PageResources::font, 25));
		m_window.getBackendText()->setFillColor(sf::Color::Cyan);

		// Adding widgets
		m_window.addWidget(m_slider_volume);
		m_window.addWidget(m_slider_volume_eff);
		m_window.addWidget(m_button_accept);
	}

	void create(vgui::GuiSFML* gui) override
	{
		gui->addWindow(getWindow());
		m_window.hide();
	}

private:

	vgui::SliderSFML m_slider_volume;

	vgui::SliderSFML m_slider_volume_eff;

	vgui::ButtonSFML m_button_accept;

};

class WindowSettingsDisplay final : public WindowBase
{
public:

	WindowSettingsDisplay() :
		WindowBase(500.0F, 400.0F)
	{
		// Main menu initialization
		PageResources::MainMenu::initialize();

		// Slider "Volume" initialization
		m_slider_fps.setPosition(140, 100);
		m_slider_fps.setHandleSize(25, 50);
		m_slider_fps.setSize(225, 50);
		m_slider_fps.addOnMouseEnteredLambda(GuiLambdas::onMouseEntered);
		m_slider_fps.addOnMouseLeftLambda(GuiLambdas::onMouseLeft);
		m_slider_fps.addOnHandleMoveLambda(GuiLambdas::onSliderFPSMove);
		m_slider_fps.setTextLabelPosition(m_slider_fps.getPosition().x, m_slider_fps.getPosition().y - 25);
		sf::Text* text_slider_fps = new sf::Text(L"FPS: 20", PageResources::font, 30);
		m_slider_fps.setBackendText(text_slider_fps);
		m_slider_fps.getBackendText()->setFillColor(sf::Color::Red);
		m_slider_fps.setMinimalSliderValue(30);
		m_slider_fps.setMaximalSliderValue(244);
		m_slider_fps.setSliderValue(165);
		m_slider_fps.setBackendTexture(PageResources::slider_texture);
		m_slider_fps.setHandleTextureWidth(43);
		m_slider_fps.setUserData(&m_slider_fps);

		// CheckBox "V-SYNC" initialization
		m_chechbox_vsync.setPosition(140, m_slider_fps.getPosition().y + 50);
		m_chechbox_vsync.setSize(50, 50);
		m_chechbox_vsync.setTextLabelPosition(m_chechbox_vsync.getPosition().x + 60, m_chechbox_vsync.getPosition().y + 10);
		m_chechbox_vsync.setBackendTexture(PageResources::checkbox_texture);
		sf::Text* text_m_chechbox_vsync = new sf::Text(L"V-SYNC", PageResources::font, 30);
		m_chechbox_vsync.setBackendText(text_m_chechbox_vsync);
		m_chechbox_vsync.getBackendText()->setFillColor(sf::Color::Red);
		m_chechbox_vsync.addOnTrue(GuiLambdas::onEnableVSync);
		m_chechbox_vsync.addOnFalse(GuiLambdas::onDisableVSync);

		// Button "Accept"
		m_button_accept.setSize(225, 60);
		m_button_accept.setPosition(135, 400 - 125);
		m_button_accept.setBackendTexture(PageResources::button_green_texture);
		m_button_accept.addOnMouseEnteredLambda(GuiLambdas::onMouseEntered);
		m_button_accept.addOnMouseLeftLambda(GuiLambdas::onMouseLeft);
		m_button_accept.addOnMouseDownLambda(GuiLambdas::onMouseDown);
		m_button_accept.addOnMouseUpLambda(GuiLambdas::onMouseUp);
		m_button_accept.addOnMouseUpLambda(GuiLambdas::onClickButtonAcceptDisplay);
		m_button_accept.setBackendText(new sf::Text(L"ПРИНЯТЬ", PageResources::font, 30));
		m_button_accept.getBackendText()->setFillColor(sf::Color::Black);
		m_button_accept.setUserData(this);

		// Gui-Window initialization
		m_window.setSize(500, 400);
		m_window.setBackendTexture(PageResources::MainMenu::texture_window);
		m_window.setPosition(300, 100);
		m_window.setTitlePosition(60, 17);
		m_window.setHandleHeight(50);
		m_window.setBackendText(new sf::Text(L"НАСТРОЙКИ ЗВУКА", PageResources::font, 25));
		m_window.getBackendText()->setFillColor(sf::Color::Cyan);

		// Adding widgets
		m_window.addWidget(m_slider_fps);
		m_window.addWidget(m_chechbox_vsync);
		m_window.addWidget(m_button_accept);
	}

	void create(vgui::GuiSFML* gui) override
	{
		gui->addWindow(getWindow());
		m_window.hide();
	}

private:

	vgui::SliderSFML m_slider_fps;

	vgui::ButtonSFML m_button_accept;

	vgui::CheckBoxSFML m_chechbox_vsync;

};

class WindowSettings final : public WindowBase
{

	friend class PageMainMenu;
	friend class WindowSettingsVolume;

public:

	WindowSettings() :
		WindowBase(500.0F, 400.0F)
	{
		// Main menu initialization
		PageResources::MainMenu::initialize();

		// Button "Volume" initialization
		m_button_settings_volume.setSize(225, 60);
		m_button_settings_volume.setPosition(135, 100);
		m_button_settings_volume.setBackendTexture(PageResources::button_purple_texture);
		m_button_settings_volume.addOnMouseEnteredLambda(GuiLambdas::onMouseEntered);
		m_button_settings_volume.addOnMouseLeftLambda(GuiLambdas::onMouseLeft);
		m_button_settings_volume.addOnMouseDownLambda(GuiLambdas::onMouseDown);
		m_button_settings_volume.addOnMouseUpLambda(GuiLambdas::onMouseUp);
		m_button_settings_volume.addOnMouseUpLambda(GuiLambdas::onClickButtonOpenWindowVolumeSettings);
		m_button_settings_volume.setBackendText(new sf::Text(L"Громкость", PageResources::font, 30));
		m_button_settings_volume.getBackendText()->setFillColor(sf::Color::Black);

		// Button "Display" initialization
		m_button_settings_display.setSize(225, 60);
		m_button_settings_display.setPosition(135, m_button_settings_volume.getPosition().y + 85);
		m_button_settings_display.setBackendTexture(PageResources::button_orange_texture);
		m_button_settings_display.addOnMouseEnteredLambda(GuiLambdas::onMouseEntered);
		m_button_settings_display.addOnMouseLeftLambda(GuiLambdas::onMouseLeft);
		m_button_settings_display.addOnMouseDownLambda(GuiLambdas::onMouseDown);
		m_button_settings_display.addOnMouseUpLambda(GuiLambdas::onMouseUp);
		m_button_settings_display.addOnMouseUpLambda(GuiLambdas::onClickButtonOpenWindowDisplaySettings);
		m_button_settings_display.setBackendText(new sf::Text(L"ДИСПЛЕЙ", PageResources::font, 30));
		m_button_settings_display.getBackendText()->setFillColor(sf::Color::Black);

		// Button "Save" initialization
		m_button_save.setSize(225, 60);
		m_button_save.setPosition(135, 400 - 125);
		m_button_save.setBackendTexture(PageResources::button_green_texture);
		m_button_save.addOnMouseEnteredLambda(GuiLambdas::onMouseEntered);
		m_button_save.addOnMouseLeftLambda(GuiLambdas::onMouseLeft);
		m_button_save.addOnMouseDownLambda(GuiLambdas::onMouseDown);
		m_button_save.addOnMouseUpLambda(GuiLambdas::onMouseUp);
		m_button_save.addOnMouseUpLambda(GuiLambdas::onClickButtonSaveSettings);
		m_button_save.setBackendText(new sf::Text(L"СОХРАНИТЬ", PageResources::font, 30));
		m_button_save.getBackendText()->setFillColor(sf::Color::Black);
		m_button_save.setUserData(this);

		// Gui-Window initialization
		m_window.setSize(500, 400);
		m_window.setBackendTexture(PageResources::MainMenu::texture_window);
		m_window.setPosition(100, 100);
		m_window.setTitlePosition(60, 17);
		m_window.setHandleHeight(50);
		m_window.setBackendText(new sf::Text(L"НАСТРОЙКИ", PageResources::font, 25));
		m_window.getBackendText()->setFillColor(sf::Color::Cyan);

		// Adding widgets
		m_window.addWidget(m_button_settings_volume);
		m_window.addWidget(m_button_settings_display);
		m_window.addWidget(m_button_save);
	}

	void create(vgui::GuiSFML* gui) override
	{
		gui->addWindow(getWindow());
		m_window.hide();
	}

private:

	vgui::ButtonSFML m_button_settings_volume;

	vgui::ButtonSFML m_button_settings_display;

	vgui::ButtonSFML m_button_save;

};

class WindowMainMenu final : public WindowBase
{
public:

	WindowMainMenu() : 
		WindowBase(500, 400)
	{
		m_button_play.setSize(225, 60);
		m_button_play.setPosition(135, 100);
		m_button_play.setBackendTexture(PageResources::button_green_texture);
		m_button_play.addOnMouseEnteredLambda(GuiLambdas::onMouseEntered);
		m_button_play.addOnMouseLeftLambda(GuiLambdas::onMouseLeft);
		m_button_play.addOnMouseDownLambda(GuiLambdas::onMouseDown);
		m_button_play.addOnMouseUpLambda(GuiLambdas::onMouseUp);
		m_button_play.addOnMouseUpLambda(GuiLambdas::onClickButtonPlayZumaGame);
		m_button_play.setBackendText(new sf::Text(L"ИГРАТЬ", PageResources::font, 30));
		m_button_play.getBackendText()->setFillColor(sf::Color::Black);

		// Button "Settings" initialization
		m_button_settings.setSize(225, 60);
		m_button_settings.setPosition(135, m_button_play.getPosition().y + 85);
		m_button_settings.setBackendTexture(PageResources::button_purple_texture);
		m_button_settings.addOnMouseEnteredLambda(GuiLambdas::onMouseEntered);
		m_button_settings.addOnMouseLeftLambda(GuiLambdas::onMouseLeft);
		m_button_settings.addOnMouseDownLambda(GuiLambdas::onMouseDown);
		m_button_settings.addOnMouseUpLambda(GuiLambdas::onMouseUp);
		m_button_settings.addOnMouseUpLambda(GuiLambdas::onClickButtonOpenSettings);
		m_button_settings.setBackendText(new sf::Text(L"НАСТРОЙКИ", PageResources::font, 30));
		m_button_settings.getBackendText()->setFillColor(sf::Color::Black);
		m_button_settings.setUserData(this);

		// Button "Exit" initialization
		m_button_exit.setSize(225, 60);
		m_button_exit.setPosition(135, m_button_settings.getPosition().y + 85);
		m_button_exit.setBackendTexture(PageResources::button_orange_texture);
		m_button_exit.addOnMouseEnteredLambda(GuiLambdas::onMouseEntered);
		m_button_exit.addOnMouseLeftLambda(GuiLambdas::onMouseLeft);
		m_button_exit.addOnMouseDownLambda(GuiLambdas::onMouseDown);
		m_button_exit.addOnMouseUpLambda(GuiLambdas::onMouseUp);
		m_button_exit.addOnMouseUpLambda(GuiLambdas::onMouseClose);
		m_button_exit.setBackendText(new sf::Text(L"ВЫЙТИ", PageResources::font, 30));
		m_button_exit.getBackendText()->setFillColor(sf::Color::Black);

		// Gui-Window initialization
		m_window.setSize(500, 400);
		m_window.setBackendTexture(PageResources::MainMenu::texture_window);
		m_window.setPosition(50, 50);
		m_window.setTitlePosition(60, 17);
		m_window.setHandleHeight(50);
		auto window_text = new sf::Text(L"НУ ЧТО, ПОИГРАЕМ? ВЫБЕРИ РЕЖИМ!", PageResources::font, 25);
		window_text->setStyle(sf::Text::Bold);
		m_window.setBackendText(window_text);
		m_window.getBackendText()->setFillColor(sf::Color::White);
		m_window.addWidget(m_button_play);
		m_window.addWidget(m_button_settings);
		m_window.addWidget(m_button_exit);

		// Gui initialization

		sf::Shader* shader = new sf::Shader;
		shader->loadFromFile("vert.glsl", "frag.glsl");
		sf::Shader* shader2 = new sf::Shader;
		shader2->loadFromFile("text_vert.glsl", "text_frag.glsl");
		shader2->setUniform("texture2", *PageResources::text_texture);
		MultithreadShaderRenderer* renderer = new MultithreadShaderRenderer(shader, &GuiLambdas::rendererOfWindow);
		MultithreadShaderRenderer* renderer2 = new MultithreadShaderRenderer(shader2, &GuiLambdas::rendererOfWindow);

		sf::Shader** shaders = new sf::Shader * [2];
		shaders[0] = shader;
		shaders[1] = shader2;

		m_window.setBackendShader(shaders);
		renderer->startRendering();
		renderer2->startRendering();
	}

	void create(vgui::GuiSFML* gui) override
	{
		gui->addWindow(getWindow());
	}

private:

	vgui::ButtonSFML m_button_play;

	vgui::ButtonSFML m_button_settings;

	vgui::ButtonSFML m_button_exit;

};

class PageMainMenu final : public PageBase
{

	friend class WindowSettings;
	friend class WindowSettingsVolume;

public:

	PageMainMenu(
		const vgui::Vector2<uint16_t> first_window_size
	) :
		m_first_window_size(first_window_size),
		PageBase(first_window_size.x, first_window_size.y)
	{
		// Main menu initialization
		PageResources::MainMenu::initialize();
		m_rectangle_shape_main_menu_background.setSize(sf::Vector2f(first_window_size.x, first_window_size.y));

		// Main menu background initialization
		m_rectangle_shape_main_menu_background.setTexture(PageResources::MainMenu::texture_background);

	}

	void handleEvent(
		const sf::Event& event,
		const sf::Window& window
	) override
	{
		m_gui.handleEvent(event, window);
	}

protected:

	void draw(
		sf::RenderTarget& target, 
		const sf::RenderStates states
	) const override
	{
		target.draw(m_rectangle_shape_main_menu_background);
		target.draw(m_gui, states);
	}

private:

	vgui::Vector2<uint16_t> m_first_window_size;

	sf::RectangleShape m_rectangle_shape_main_menu_background;

};

class PageLevelEditor
{
public:

private:

};

inline void PagesAndWindows::Initialize(
	sf::Window& sfml_window
)
{
	const _VGUI Vector2<uint16_t> first_window_size = _VGUI Vector2<uint16_t>(
		sfml_window.getSize().x,
		sfml_window.getSize().y
	);

	// Initialize the static main sf::Window
	PagesAndWindows::sfml_window = &sfml_window;

	//Initialize the pages and windows
	PagesAndWindows::page_main_menu				= std::make_unique<PageMainMenu>(first_window_size);
	PagesAndWindows::window_main_menu			= std::make_unique<WindowMainMenu>();
	PagesAndWindows::window_settings			= std::make_unique<WindowSettings>();
	PagesAndWindows::window_settings_volume		= std::make_unique<WindowSettingsVolume>();
	PagesAndWindows::window_settings_display	= std::make_unique<WindowSettingsDisplay>();

	//Adding windows in main page

	//The main and first window
	window_main_menu		->create(page_main_menu->getGui());
	window_main_menu		->getWindow()->show();
	window_main_menu		->getWindow()->setActive(true);

	//The windows of settings
	window_settings			->create(page_main_menu->getGui());
	window_settings_volume	->create(page_main_menu->getGui());
	window_settings_display	->create(page_main_menu->getGui());
}

#pragma once
#include "Pages.h"
#include <SFML/OpenGL.hpp>
#include <gl/GLU.h>
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#include <filesystem>
#include <fstream>
/////////////////// The settings of game ////////////////////////////

// 3 << 6 == 2^6 * 3 == 192
constexpr const uint16_t limit_of_bezier_curves = 3 << 4;

// Count of the ball's textures of animation
constexpr const uint8_t count_of_the_ball_anim_tex = 360 / 5;

constexpr const float rotation_ball_scale = 360.f / (float)count_of_the_ball_anim_tex;

class ZumaMath final
{
public:

	static inline float PI = acosf(-1);

	static inline float RAD = PI / 180.f;

	static inline float DEG = 180.f / PI;

	[[nodiscard]]
	static constexpr inline float __fastcall toRad(
		const float deg
	)
	{
		return deg * RAD;
	}

	[[nodiscard]]
	static constexpr inline float __fastcall toDeg(
		const float rad
	)
	{
		return rad * DEG;
	}

};

class BallSFML final : public sf::Drawable
{
public:

	BallSFML( 
		const std::string& texture_path
	) : 
		m_ball_texture(load_texture_sfml_with_mask(texture_path, sf::Color(245, 245, 245))),
		m_ball_rectangle_shapes(),
		m_ball_rectangle_shape_curr(m_ball_rectangle_shapes[0])
	{
		if (m_ball_texture == nullptr)
		{
			throw std::runtime_error("ball's texture is nullptr!");
		}
		const uint16_t m_ball_texture_rect_height = m_ball_texture->getSize().y / count_of_the_ball_anim_tex;
		for (uint8_t i = 0; i < count_of_the_ball_anim_tex; i++)
		{
			m_ball_rectangle_shapes[i].setTexture(m_ball_texture);
			m_ball_rectangle_shapes[i].setTextureRect(sf::IntRect(
				0, 
				i * m_ball_texture_rect_height,
				m_ball_texture->getSize().x,
				count_of_the_ball_anim_tex
			));
		}
	}

	void setRotation(const float angle)
	{
		const uint8_t ball_index = angle / rotation_ball_scale;
		m_ball_rectangle_shape_curr = m_ball_rectangle_shapes[ball_index];
	}

protected:

	void draw(
		sf::RenderTarget& target,
		sf::RenderStates states
	) const override
	{
		throw std::logic_error("The method or operation is not implemented.");
	}

private:

	sf::Texture* m_ball_texture;

	sf::RectangleShape m_ball_rectangle_shapes[count_of_the_ball_anim_tex];

	sf::RectangleShape& m_ball_rectangle_shape_curr;

};

struct ZumaGameLevelDat final
{

	struct BeizerCurve final
	{

		// The count of points at this beizer curve
		uint8_t points_count;

		// The points at texture in float
		float points[4];

	};

	// The name of level on russian language
	wchar_t level_name[16];

	// The texture name of level on russian language
	wchar_t texture_name[16];

	// The Frog position in this_level at size of texture
	sf::Vector2f frog_position;

	// The Gulf position in this_level at size of texture
	sf::Vector2f gulf_position;

	// The beizer curves
	uint16_t count_of_bezier_curves;

	// The limit of bezier_curves - is 
	float BeizerCurve[limit_of_bezier_curves];

	static ZumaGameLevelDat loadLevelDatFromFile(
		const std::string& path
	)
	{
		std::ifstream is;
		is.open(path, std::ios::binary);

		if (!is.is_open())
		{
			return {};
		}

		// Get length of file:
		is.seekg(0, std::ios::end);
		const auto length = is.tellg();
		is.seekg(0, std::ios::beg);

		// Allocate memory:
		char* const buffer = new char[length];

		// Read data as a block:
		is.read(buffer, length);

		// Cast binary buffer to level data
		ZumaGameLevelDat level_dat_buffer = *reinterpret_cast<ZumaGameLevelDat*>(buffer);
		is.close();
		return level_dat_buffer;
	}

};

class ZumaGameResources final
{
public:

	static inline std::string setings_path = "settings/zuma_game.txt";

	static inline sf::Color default_mask = sf::Color(230, 230, 230);

	static inline sf::Color frog_mask = sf::Color(210, 210, 210);

	static inline sf::Texture* texture_frog;

	//static inline sf::Texture* textures_level;

	static inline config_map_t config_map;

	static inline bool is_init = false;

	static bool Initialize()
	{
		if (!is_init)
		{
			// Load settings file of main menu
			config_map = ConfigReader::readConfFile(setings_path);

			// Load textures of game
			texture_frog = load_texture_sfml_with_mask(config_map["texture_frog"], default_mask);
			texture_frog->setSmooth(true);

			// Load levels
			loadLevelDats();

			// Load the balls

			// Deallocate config_map's memory
			config_map.clear();
			is_init = true;
		}
		return true;
	}

	static void loadLevelDats()
	{
		constexpr auto leveldat_filename = "leveldat.txt";
		std::string level_dir = config_map["levels_dir"];
		for (decltype(auto) dir_entry : std::filesystem::directory_iterator(config_map["levels_dir"]))
		{
			if (!dir_entry.is_directory())
			{
				continue;
			}
			std::string dir_path = dir_entry.path().filename().string();
			m_workable_levels[dir_path] = ZumaGameLevelDat::loadLevelDatFromFile(
				level_dir + dir_path + '/' + leveldat_filename
			);
		}
	}

	static constexpr BallSFML& getBallAt(
		const uint32_t ball_type
	)
	{
		return *m_balls[ball_type];
	}

private:

	static inline std::map<std::string, ZumaGameLevelDat> m_workable_levels;

	static inline BallSFML* m_balls[5] = {};

};

class ZumaBall
{
public:

	enum class Type : uint32_t
	{
		Red,
		Yellow,
		Green,
		Purple,
		Gray
	};

	ZumaBall()
	{

	}

};

class ZumaFrog final : public sf::Drawable
{
public:

	explicit ZumaFrog()
	{
		ZumaGameResources::Initialize();
		m_rectangle_shape_frog.setTexture(ZumaGameResources::texture_frog);
	}

	void setSize(
		const sf::Vector2f& frog_size
	)
	{
		m_rectangle_shape_frog.setSize(frog_size);
		m_rectangle_shape_frog.setOrigin(
			m_rectangle_shape_frog.getSize().x / 2,
			m_rectangle_shape_frog.getSize().y / 2
		);
	}

	void setSize(
		const float frog_size_x, 
		const float frog_size_y
	)
	{
		this->setSize(sf::Vector2f(frog_size_x, frog_size_y));
	}

	void setPosition(
		const sf::Vector2f& frog_position
	)
	{
		m_rectangle_shape_frog.setPosition(frog_position);
	}

	void setPosition(
		const float frog_position_x, 
		const float frog_position_y
	)
	{
		this->setPosition(sf::Vector2f(frog_position_x, frog_position_y));
	}

	void setRotation(
		const float rotation
	)
	{
		m_rectangle_shape_frog.setRotation(rotation);
	}

	void rotate(
		const float rotation
	)
	{
		m_rectangle_shape_frog.rotate(rotation);
	}

	void setMajorBall(
		const ZumaBall::Type major_ball_type
	)
	{
		m_major_ball = major_ball_type;
	}

	void setMinorBall(
		const ZumaBall::Type minor_ball_type
	)
	{
		m_minor_ball = minor_ball_type;
	}

	void lookAtCursor(const sf::Vector2i& cursor_position)
	{
		const float delta_x = cursor_position.x - m_rectangle_shape_frog.getPosition().x;
		const float delta_y = cursor_position.y - m_rectangle_shape_frog.getPosition().y;
		float rotation = ZumaMath::toDeg(atan2f(delta_x, -delta_y));
		this->setRotation(rotation + 180);
	}

	void draw(
		sf::RenderTarget& target, 
		sf::RenderStates states
	) const override
	{
		target.draw(m_rectangle_shape_frog);
	}

private:

	// The rectangle shape of frog
	sf::RectangleShape m_rectangle_shape_frog;

	// The major ball
	ZumaBall::Type m_major_ball;

	// The minor ball
	ZumaBall::Type m_minor_ball;

};

class ZumaLevel final : public sf::Drawable
{
public:

	explicit ZumaLevel()
	{
		ZumaGameResources::Initialize();
		//m_rectangle_shape_level.setTexture(ZumaGameResources::texture_levels[]);
	}

	void setSize(
		const sf::Vector2f& frog_size
	)
	{
		m_rectangle_shape_level.setSize(frog_size);
	}

	void setSize(
		const float frog_size_x,
		const float frog_size_y
	)
	{
		this->setSize(sf::Vector2f(frog_size_x, frog_size_y));
	}

	void draw(
		sf::RenderTarget& target,
		sf::RenderStates states
	) const override
	{
		target.draw(m_rectangle_shape_level);
	}

private:

	// The rectangle shape of the level
	sf::RectangleShape m_rectangle_shape_level;


};

class ZumaGame final : public PageBase
{
private:

	sf::RenderWindow window;

	sf::ContextSettings context_settings;

	sf::Event event;

	ZumaFrog frog;

public:

	ZumaGame()  :
		PageBase(
			sf::VideoMode::getFullscreenModes()[6].width, 
			sf::VideoMode::getFullscreenModes()[6].height
		),
		event{}
	{
		
	}

	void start()
	{
		this->initialize();
		while (window.isOpen())
		{
			while (window.pollEvent(event))
			{
				handleEvent(event);
			}

			if (this->m_is_active)
			{
				this->update();
			}

			this->draw();
		}
	}

private:

	void initialize()
	{
		context_settings.antialiasingLevel = 1;
		window.create(sf::VideoMode::VideoMode(800, 800), "TGUI Window", sf::Style::Default, context_settings);
		window.setVerticalSyncEnabled(true);
		window.setFramerateLimit(165);

		PageResources::initialize();

		window.setMouseCursor(PageResources::cursor);
		PagesAndWindows::Initialize(window);
		PagesAndWindows::setCurrentPage(PagesAndWindows::page_main_menu.get());

		frog.setSize(130, 130);
		frog.setPosition(400, 400);

	}

	void draw()
	{
		window.clear();
		window.draw(*PagesAndWindows::getCurrentPage());
		window.display();
	}

	// Draw the Zuma Game
	void draw(
		sf::RenderTarget& target,
		sf::RenderStates states
	) const override
	{
		target.draw(frog);
	}

	void update()
	{
		frog.lookAtCursor(sf::Mouse::getPosition(window));
	}

	void handleEvent(
		const sf::Event& event
	)
	{
		if (event.type == sf::Event::Closed)
		{
			window.close();
		}
		PagesAndWindows::getCurrentPage()->handleEvent(event, window);
	}

	void handleEvent(
		const sf::Event& event, 
		const sf::Window& window
	) override
	{
		//"The method or operation is not implemented.";
	}

};
