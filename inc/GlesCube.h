//
// Tizen C++ SDK
// Copyright (c) 2012-2013 Samsung Electronics Co., Ltd.
//
// Licensed under the Flora License, Version 1.1 (the License);
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://floralicense.org/license/
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an AS IS BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

#ifndef _GLES_CUBE_H_
#define _GLES_CUBE_H_


#include <new>
#include <FBase.h>
#include <FSystem.h>
#include <FGraphics.h>
#include <FUi.h>
#include <FApp.h>
#include <FGraphicsOpengl2.h>
#include <FGrpFloatMatrix4.h>

class GlesCube
	: public Tizen::App::Application
	, public Tizen::System::IScreenEventListener
	, public Tizen::Ui::IKeyEventListener
	, public Tizen::Base::Runtime::ITimerEventListener
{
public:
	static Tizen::App::Application* CreateInstance(void);

	GlesCube(void);
	~GlesCube(void);

	virtual bool OnAppInitializing(Tizen::App::AppRegistry& appRegistry);
	virtual bool OnAppTerminating(Tizen::App::AppRegistry& appRegistry, bool forcedTermination = false);
	virtual void OnForeground(void);
	virtual void OnBackground(void);
	virtual void OnLowMemory(void);
	virtual void OnBatteryLevelChanged(Tizen::System::BatteryLevel batteryLevel);
	virtual void OnKeyPressed(const Tizen::Ui::Control& source, Tizen::Ui::KeyCode keyCode);
	virtual void OnKeyReleased(const Tizen::Ui::Control& source, Tizen::Ui::KeyCode keyCode);
	virtual void OnKeyLongPressed(const Tizen::Ui::Control& source, Tizen::Ui::KeyCode keyCode);

	virtual void OnScreenOn(void);
	virtual void OnScreenOff(void);

	virtual void OnTimerExpired(Tizen::Base::Runtime::Timer& timer);

	bool Draw(void);

private:
	bool InitEGL(void);
	bool InitGL(void);
	void DestroyGL(void);
	void Update(void);
	void Cleanup(void);

	void Frustum(Tizen::Graphics::FloatMatrix4* pResult, float left, float right, float bottom, float top, float near, float far);
	void Perspective(Tizen::Graphics::FloatMatrix4* pResult, float fovY, float aspect, float near, float far);
	void Translate(Tizen::Graphics::FloatMatrix4* pResult, float tx, float ty, float tz);
	void Rotate(Tizen::Graphics::FloatMatrix4* pResult, float angle, float x, float y, float z);

private:
	Tizen::Graphics::Opengl::EGLDisplay  __eglDisplay;
	Tizen::Graphics::Opengl::EGLSurface  __eglSurface;
	Tizen::Graphics::Opengl::EGLConfig   __eglConfig;
	Tizen::Graphics::Opengl::EGLContext  __eglContext;
	Tizen::Graphics::Opengl::GLuint      __programObject;
	Tizen::Graphics::Opengl::GLint       __idxPosition;
	Tizen::Graphics::Opengl::GLint       __idxColor;
	Tizen::Graphics::Opengl::GLint       __idxMVP;
	Tizen::Graphics::Opengl::GLfloat     __angle;
	Tizen::Base::Runtime::Timer*         __pTimer;
	Tizen::Graphics::FloatMatrix4        __matMVP;

	Tizen::Ui::Controls::Form*           __pForm;
};

#endif // __GLES_CUBE_H__

