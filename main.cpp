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

#include <Windows.h>

#include "Pages.h"
#include "resource.h"
#include "StepTimer.h"

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

	Vector2<float> m_origin;

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

	void setOrigin(const Vector2<float> origin)
	{
		m_origin = origin;
		onSetOrigin();
	}


	void setOrigin(
		const float x,
		const float y
	)
	{
		m_origin.x = x;
		m_origin.y = y;
		onSetOrigin();
	}

	void setTransform(const Transform& transform)
	{
		setOrigin(transform.m_origin);
		setPosition(transform.m_position);
		setSize(transform.m_size);
	}

	[[nodiscard]]
	const Transform& getTransform() const
	{
		return *this;
	}

protected:

	virtual void onSetPosition() = 0;

	virtual void onSetOrigin() = 0;

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

	[[nodiscard]]
	Vector2<float> getOrigin() const
	{
		return m_origin;
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
	uint16_t getHandleTextureWidth() const
	{
		return m_handle_texture_width;
	}

	void setMinimalSliderValue(const float minimal_slider_value)
	{
		m_minimal_slider_value = minimal_slider_value;
		onSetMinimalSliderValue();
	}

	[[nodiscard]]
	float getMinimalSliderValue() const
	{
		return m_minimal_slider_value;
	}

	void setMaximalSliderValue(const float maximal_slider_value)
	{
		m_maximal_slider_value = maximal_slider_value;
		onSetMaximalSliderValue();
	}

	[[nodiscard]]
	float getMaximalSliderValue() const
	{
		return m_maximal_slider_value;
	}

	void setSliderValue(const float slider_value)
	{
		m_slider_value = slider_value;
		onSetSliderValue();
	}

	[[nodiscard]]
	float getSliderValue() const
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
	void addOnMouseEnteredLambda(const event_lambda lambda_mouse_entered)
	{
		m_lambdas_mouse_entered.push_back(lambda_mouse_entered);
	}

	void addOnMouseLeftLambda(const event_lambda lambda_mouse_left)
	{
		m_lambdas_mouse_left.push_back(lambda_mouse_left);
	}

	void addOnHandleMoveLambda(const event_lambda lambda_mouse_down)
	{
		m_lambdas_handle_move.push_back(lambda_mouse_down);
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

	void setOnHandleMoveLambdas(const std::list<event_lambda>& lambdas_mouse_down)
	{
		m_lambdas_handle_move = lambdas_mouse_down;
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
	const std::list<event_lambda>& getOnHandleMoveLambdas() const
	{
		return m_lambdas_handle_move;
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

	void addWindow(_Backend_window_type& window)
	{
		m_windows.push_back(&window);
	}

	void removeWindow(_Backend_window_type& window)
	{
		m_windows.remove(&window);
	}

	void setActiveWindow(_Backend_window_type& window)
	{
		window.m_is_active = true;
		m_windows.remove(&window);
		for (decltype(auto) widget_window : m_windows)
		{
			widget_window->m_is_active = false;
		}
		m_windows.push_back(&window);
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

	void onSetOrigin() override
	{
		m_rectangle_shape_button.setOrigin(this->m_origin.x, this->m_origin.y);
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
								this->m_slider_value = scale;
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

	void onSetOrigin() override
	{
		// Origin is bad
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
class WindowSFML :
					public sf::Drawable,
					public WindowBase<_VGUI_UTILITIES GuiTargetSFML>,
					public _VGUI_UTILITIES Textureable<sf::Texture>,
					public _VGUI_UTILITIES Textable<sf::Text>,
					public _VGUI_UTILITIES Shaderable<sf::Shader>
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
		m_render_texture.draw(m_rectangle_shape_render_texture, this->m_backend_shader);
		m_render_texture.draw(*this->m_backend_text);
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

	void onSetOrigin() override
	{
		m_rectangle_shape_window.setOrigin(this->m_origin.x, this->m_origin.y);
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

	GuiSFML(const unsigned width, const unsigned height, const sf::ContextSettings& context_settings = sf::ContextSettings())
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

inline sf::Texture& __fastcall load_texture_sfml_with_mask(
	const std::string& path, 
	const sf::Color& mask
)
{
	sf::Image img;
	img.loadFromFile(path);
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
	tex->loadFromImage(img);
	return *tex;
}

inline sf::Texture& __fastcall load_texture_sfml(
	const std::string& path
)
{
	const auto texture = new sf::Texture;
	texture->loadFromFile(path);
	return *texture;
}

class Resources
{
public:

	static inline bool is_init = false;

	static inline sf::Color default_mask = sf::Color(240, 240, 240);

	static inline config_map_t config_map;

	static inline sf::Cursor default_cursor;

	static inline sf::Font default_font;

	static inline sf::Texture default_slider_texture;

	static void initialize()
	{
		if (!is_init)
		{
			// Load settings file
			config_map = ConfigReader::readConfFile("settings/default.txt");

			// Load default window's cursor
			const sf::Image image_cursor = load_texture_sfml_with_mask(config_map["default_cursor"], default_mask).copyToImage();
			default_cursor.loadFromPixels(image_cursor.getPixelsPtr(), image_cursor.getSize(), {});
				
			// Load default font
			default_font.loadFromFile(config_map["default_font"]);

			// Load the default slider texture
			default_slider_texture = load_texture_sfml_with_mask(config_map["default_slider_texture"], default_mask);

			// Deallocate config_map's memory
			config_map.clear();
			is_init = true;
		}
	}

	class MainMenu
	{
	public:

		static inline bool is_init = false;

		static inline config_map_t config_map;

		static inline sf::Texture texture_window;

		static inline sf::Texture texture_button_play;

		static inline sf::Texture texture_button_settings;

		static inline sf::Texture texture_button_exit;

		static inline sf::Texture texture_background;

		static inline sf::Sound sound_main_menu;
		static inline sf::SoundBuffer sound_buffer_main_menu;

		static void initialize()
		{
			if (!is_init)
			{
				// Load settings file of main menu
				config_map = ConfigReader::readConfFile("settings/main_menu.txt");

				// Load textures of main menu
				texture_window = load_texture_sfml_with_mask(config_map["texture_window"], default_mask);
				texture_button_play = load_texture_sfml_with_mask(config_map["texture_button_play"], default_mask);
				texture_button_settings = load_texture_sfml_with_mask(config_map["texture_button_settings"], default_mask);
				texture_button_exit = load_texture_sfml_with_mask(config_map["texture_button_exit"], default_mask);
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

	virtual void handleEvent(
		const sf::Event& event,
		const sf::Window& window
	) = 0;

};

class WindowBase
{
public:

	virtual void create(
		vgui::GuiSFML* gui
	) = 0;

};

class ShaderRenderer
{

};

///////////////////// GUI PAGES AND WINDOWS ///////////////////////
class PageMainMenu;
class WindowSettings;
class WindowSettingsVolume;
///////////////////// PAGE MANAGER ///////////////////////

class PageManager
{
public:

	static void setCurrentPage(PageBase& current_page)
	{
		m_current_page = &current_page;
	}

	[[nodiscard]]
	static PageBase& getCurrentPage()
	{
		return *m_current_page;
	}

private:

	static inline PageBase* m_current_page = nullptr;

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

	static void onMouseOpenSettings(vgui::WidgetBase& widget, void*)
	{
		//PageManager::setCurrentPage();
	}

	static void onSliderVolumeMove(vgui::WidgetBase&, void* ptr_slider)
	{
		Resources::MainMenu::sound_main_menu.setVolume(reinterpret_cast<vgui::SliderSFML*>(ptr_slider)->getSliderValue());
		std::wstring l_str = L"ГРОМКОСТЬ МУЗЫКИ: ";
		l_str += std::to_wstring((uint16_t)Resources::MainMenu::sound_main_menu.getVolume());
		reinterpret_cast<sf::Text*>(reinterpret_cast<vgui::SliderSFML*>(ptr_slider)->getBackendText())->setString(l_str);
	}

};

class WindowSettingsVolume final : public WindowBase
{

	friend class WindowSettings;

public:

	WindowSettingsVolume(WindowSettings* window_settings) :
		m_window(500.0F, 400.0F),
		m_window_settings(window_settings)
	{
		// Main menu initialization
		Resources::MainMenu::initialize();

		// Slider "Volume" initialization
		m_slider_volume.setPosition(140, 100);
		m_slider_volume.setHandleSize(25, 50);
		m_slider_volume.setSize(200, 50);
		m_slider_volume.addOnMouseEnteredLambda(GuiLambdas::onMouseEntered);
		m_slider_volume.addOnMouseLeftLambda(GuiLambdas::onMouseLeft);
		m_slider_volume.addOnHandleMoveLambda(GuiLambdas::onSliderVolumeMove);
		m_slider_volume.setTextLabelPosition(m_slider_volume.getPosition().x, m_slider_volume.getPosition().y - 25);
		sf::Text* text_slider_volume = new sf::Text(L"ГРОМКОСТЬ МУЗЫКИ: 20", Resources::default_font, 20);
		m_slider_volume.setUserData(&m_slider_volume);
		m_slider_volume.setBackendText(text_slider_volume);
		m_slider_volume.getBackendText()->setFillColor(sf::Color::Red);
		m_slider_volume.setMinimalSliderValue(0);
		m_slider_volume.setMaximalSliderValue(100);
		m_slider_volume.setSliderValue(20);
		m_slider_volume.setBackendTexture(&Resources::default_slider_texture);
		m_slider_volume.setHandleTextureWidth(43);

		// Button "Accept"
		m_button_accept.setSize(225, 60);
		m_button_accept.setPosition(135, 400 - 125);
		m_button_accept.setBackendTexture(&Resources::MainMenu::texture_button_settings);
		m_button_accept.addOnMouseEnteredLambda(GuiLambdas::onMouseEntered);
		m_button_accept.addOnMouseLeftLambda(GuiLambdas::onMouseLeft);
		m_button_accept.addOnMouseDownLambda(GuiLambdas::onMouseDown);
		m_button_accept.addOnMouseUpLambda(GuiLambdas::onMouseUp);
		m_button_accept.addOnMouseUpLambda(onAccept);
		m_button_accept.setBackendText(new sf::Text(L"ПРИНЯТЬ", Resources::default_font, 30));
		m_button_accept.getBackendText()->setFillColor(sf::Color::Black);
		m_button_accept.setUserData(this);

		// Gui-Window initialization
		m_window.setSize(500, 400);
		m_window.setBackendTexture(&Resources::MainMenu::texture_window);
		m_window.setPosition(300, 100);
		m_window.setTitlePosition(60, 17);
		m_window.setHandleHeight(50);
		m_window.setBackendText(new sf::Text(L"НАСТРОЙКИ ЗВУКА", Resources::default_font, 25));
		m_window.getBackendText()->setFillColor(sf::Color::Cyan);

		// Adding widgets
		m_window.addWidget(m_slider_volume);
		m_window.addWidget(m_button_accept);
	}

	void create(vgui::GuiSFML* gui) override
	{
		gui->addWindow(m_window);
		m_window.hide();
	}

private:

	static void onAccept(
		vgui::WidgetBase& widget,
		void* ptr_page_main_menu
	);

private:

	WindowSettings* m_window_settings;

	vgui::SliderSFML m_slider_volume;

	vgui::ButtonSFML m_button_accept;

	vgui::WindowSFML m_window;

};

class WindowSettings final : public WindowBase
{

	friend class PageMainMenu;
	friend class WindowSettingsVolume;

public:

	WindowSettings(PageMainMenu* page_main_menu) :
		m_window(500.0F, 400.0F),
		m_page_main_menu(page_main_menu),
		m_window_settings_volume(this)
	{
		// Main menu initialization
		Resources::MainMenu::initialize();

		// Button "Save" initialization
		m_button_settings_volume.setSize(225, 60);
		m_button_settings_volume.setPosition(135, 100);
		m_button_settings_volume.setBackendTexture(&Resources::MainMenu::texture_button_settings);
		m_button_settings_volume.addOnMouseEnteredLambda(GuiLambdas::onMouseEntered);
		m_button_settings_volume.addOnMouseLeftLambda(GuiLambdas::onMouseLeft);
		m_button_settings_volume.addOnMouseDownLambda(GuiLambdas::onMouseDown);
		m_button_settings_volume.addOnMouseUpLambda(GuiLambdas::onMouseUp);
		m_button_settings_volume.addOnMouseUpLambda(onMouseVolume);
		m_button_settings_volume.setBackendText(new sf::Text(L"Громкость", Resources::default_font, 30));
		m_button_settings_volume.getBackendText()->setFillColor(sf::Color::Black);

		// Button "Save" initialization
		m_button_save.setSize(225, 60);
		m_button_save.setPosition(135, 400 - 125);
		m_button_save.setBackendTexture(&Resources::MainMenu::texture_button_play);
		m_button_save.addOnMouseEnteredLambda(GuiLambdas::onMouseEntered);
		m_button_save.addOnMouseLeftLambda(GuiLambdas::onMouseLeft);
		m_button_save.addOnMouseDownLambda(GuiLambdas::onMouseDown);
		m_button_save.addOnMouseUpLambda(GuiLambdas::onMouseUp);
		m_button_save.addOnMouseUpLambda(onMouseSave);
		m_button_save.setBackendText(new sf::Text(L"СОХРАНИТЬ", Resources::default_font, 30));
		m_button_save.getBackendText()->setFillColor(sf::Color::Black);
		m_button_save.setUserData(this);

		// Gui-Window initialization
		m_window.setSize(500, 400);
		m_window.setBackendTexture(&Resources::MainMenu::texture_window);
		m_window.setPosition(100, 100);
		m_window.setTitlePosition(60, 17);
		m_window.setHandleHeight(50);
		m_window.setBackendText(new sf::Text(L"НАСТРОЙКИ", Resources::default_font, 25));
		m_window.getBackendText()->setFillColor(sf::Color::Cyan);

		// Adding widgets
		m_window.addWidget(m_button_settings_volume);
		m_window.addWidget(m_button_save);
	}

	void create(vgui::GuiSFML* gui) override
	{
		m_button_settings_volume.setUserData(vgui::make_user_data(this, gui));
		gui->addWindow(m_window);
		m_window.hide();
		m_window_settings_volume.create(gui);
	}

private:

	static void onMouseSave(
		vgui::WidgetBase& widget, 
		void* ptr_window_settings
	);

	static void onMouseVolume(
		vgui::WidgetBase& widget,
		void* ptr_window_settings
	);

private:

	WindowSettingsVolume m_window_settings_volume;

	PageMainMenu* m_page_main_menu;

	vgui::ButtonSFML m_button_save;

	vgui::ButtonSFML m_button_settings_volume;

	vgui::WindowSFML m_window;

};

class PageMainMenu final : public PageBase
{

	friend class WindowSettings;
	friend class WindowSettingsVolume;

public:

	PageMainMenu(const vgui::Vector2<uint16_t> first_window_size) :
		m_first_window_size(first_window_size),
		m_window(500.0F, 400.0F),
		m_window_settings(this),
		m_gui(first_window_size.x, first_window_size.y)
	{
		// Main menu initialization
		Resources::MainMenu::initialize();

		// Button "Play" initialization
		m_button_play.setSize(225, 60);
		m_button_play.setPosition(135, 100);
		m_button_play.setBackendTexture(&Resources::MainMenu::texture_button_play);
		m_button_play.addOnMouseEnteredLambda(GuiLambdas::onMouseEntered);
		m_button_play.addOnMouseLeftLambda(GuiLambdas::onMouseLeft);
		m_button_play.addOnMouseDownLambda(GuiLambdas::onMouseDown);
		m_button_play.addOnMouseUpLambda(GuiLambdas::onMouseUp);
		m_button_play.setBackendText(new sf::Text(L"ИГРАТЬ", Resources::default_font, 30));
		m_button_play.getBackendText()->setFillColor(sf::Color::Black);

		// Button "Settings" initialization
		m_button_settings.setSize(225, 60);
		m_button_settings.setPosition(135, m_button_play.getPosition().y + 85);
		m_button_settings.setBackendTexture(&Resources::MainMenu::texture_button_settings);
		m_button_settings.addOnMouseEnteredLambda(GuiLambdas::onMouseEntered);
		m_button_settings.addOnMouseLeftLambda(GuiLambdas::onMouseLeft);
		m_button_settings.addOnMouseDownLambda(GuiLambdas::onMouseDown);
		m_button_settings.addOnMouseUpLambda(GuiLambdas::onMouseUp);
		m_button_settings.addOnMouseUpLambda(onMouseShowWindowSettings);
		m_button_settings.setBackendText(new sf::Text(L"НАСТРОЙКИ", Resources::default_font, 30));
		m_button_settings.getBackendText()->setFillColor(sf::Color::Black);
		m_button_settings.setUserData(this);

		// Button "Exit" initialization
		m_button_exit.setSize(225, 60);
		m_button_exit.setPosition(135, m_button_settings.getPosition().y + 85);
		m_button_exit.setBackendTexture(&Resources::MainMenu::texture_button_exit);
		m_button_exit.addOnMouseEnteredLambda(GuiLambdas::onMouseEntered);
		m_button_exit.addOnMouseLeftLambda(GuiLambdas::onMouseLeft);
		m_button_exit.addOnMouseDownLambda(GuiLambdas::onMouseDown);
		m_button_exit.addOnMouseUpLambda(GuiLambdas::onMouseUp);
		m_button_exit.addOnMouseUpLambda(GuiLambdas::onMouseClose);
		m_button_exit.setBackendText(new sf::Text(L"ВЫЙТИ", Resources::default_font, 30));
		m_button_exit.getBackendText()->setFillColor(sf::Color::Black);

		// Gui-Window initialization
		m_window.setSize(500, 400);
		m_window.setBackendTexture(&Resources::MainMenu::texture_window);
		m_window.setPosition(50, 50);
		m_window.setTitlePosition(60, 17);
		m_window.setHandleHeight(50);
		auto window_text = new sf::Text(L"НУ ЧТО, ПОИГРАЕМ? ВЫБЕРИ РЕЖИМ!", Resources::default_font, 25);
		m_window.setBackendText(window_text);
		m_window.getBackendText()->setFillColor(sf::Color::Cyan);
		m_window.addWidget(m_button_play);
		m_window.addWidget(m_button_settings);
		m_window.addWidget(m_button_exit);

		// Gui initialization
		m_gui.addWindow(m_window);
		m_window_settings.create(&m_gui);
		m_gui.setActiveWindow(m_window);

		sf::Shader* shader = new sf::Shader;
		shader->loadFromFile("vert.glsl", "frag.glsl");
		m_window.setBackendShader(shader);

		// Play the main menu music
		Resources::MainMenu::sound_main_menu.play();
		Resources::MainMenu::sound_main_menu.setLoop(true);

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
		target.draw(m_gui, states);
	}

private:

	static void onMouseShowWindowSettings(vgui::WidgetBase& widget, void* ptr_page_main_menu);

private:

	WindowSettings m_window_settings;

	vgui::Vector2<uint16_t> m_first_window_size;

	vgui::ButtonSFML m_button_play;

	vgui::ButtonSFML m_button_settings;

	vgui::ButtonSFML m_button_exit;

	vgui::WindowSFML m_window;

	vgui::GuiSFML m_gui;

};

inline void WindowSettings::onMouseVolume(
	vgui::WidgetBase& widget,
	void* ptr_args
)
{
	auto args = *static_cast<vgui::UserDataTuple<WindowSettings*, vgui::GuiSFML*>*>(ptr_args);
	args.next_args.arg->setActiveWindow(args.arg->m_window_settings_volume.m_window);
	args.arg->m_window_settings_volume.m_window.show();
}

inline void WindowSettingsVolume::onAccept(
	vgui::WidgetBase& widget,
	void* ptr_args
)
{
	WindowSettingsVolume& window_settings_volume = *static_cast<WindowSettingsVolume*>(ptr_args);
	window_settings_volume.m_window.hide();
	window_settings_volume.m_window_settings->m_page_main_menu->m_gui.setActiveWindow(window_settings_volume.m_window_settings->m_window);
}

inline void WindowSettings::onMouseSave(
	vgui::WidgetBase& widget,
	void* ptr_window_settings
)
{
	WindowSettings& window_settings = *static_cast<WindowSettings*>(ptr_window_settings);
	window_settings.m_window.hide();
	window_settings.m_page_main_menu->m_gui.setActiveWindow(window_settings.m_page_main_menu->m_window);
}

inline void PageMainMenu::onMouseShowWindowSettings(
	vgui::WidgetBase& widget, 
	void* ptr_page_main_menu
)
{
	PageMainMenu& page_main_menu = *static_cast<PageMainMenu*>(ptr_page_main_menu);
	page_main_menu.m_gui.setActiveWindow(page_main_menu.m_window_settings.m_window);
	page_main_menu.m_window_settings.m_window.show();
}


int main()
{
	ShowWindow(::GetConsoleWindow(), SW_SHOW);
	sf::ContextSettings context_settings;
	context_settings.antialiasingLevel = 1;
	sf::RenderWindow window(sf::VideoMode::getFullscreenModes()[10], "TGUI Window", sf::Style::Default, context_settings);
	vgui::Vector2<uint16_t> first_window_size = vgui::Vector2<uint16_t>(window.getSize().x, window.getSize().y);
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(165);

	Resources::initialize();
	window.setMouseCursor(Resources::default_cursor);
	PageMainMenu page_main_menu(first_window_size);
	PageManager::setCurrentPage(page_main_menu);

	sf::RectangleShape rs_main_menu_bg;
	rs_main_menu_bg.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));
	rs_main_menu_bg.setTexture(&Resources::MainMenu::texture_background);

	vgui::SliderSFML slider;
	slider.setPosition(50, 50);
	slider.setHandleSize(15, 50);
	slider.setSize(200, 50);
	slider.setMinimalSliderValue(0);
	slider.setMaximalSliderValue(100);
	slider.setSliderValue(50);
	slider.addOnMouseEnteredLambda(GuiLambdas::onMouseEntered);
	slider.addOnMouseLeftLambda(GuiLambdas::onMouseLeft);
	vgui::GuiSFML gui(first_window_size.x, first_window_size.y);
	gui.addWidget(slider);

	//vgui::TextRenderer text;


	StepTimer step_timer;

	while (window.isOpen())
	{
		sf::Event event{};
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			PageManager::getCurrentPage().handleEvent(event, window);
			gui.handleEvent(event, window);
		}

		//window_sfml.move(1.5, 0);

		//std::cout << "FPS = " << step_timer.getFPS() << std::endl;

		step_timer.tick();

		window.clear();
		window.draw(rs_main_menu_bg);
		window.draw(gui);
		window.draw(PageManager::getCurrentPage());
		window.display();
	}
	return EXIT_SUCCESS;
}
