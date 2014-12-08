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

#include <new>
#include <FApp.h>
#include <FIo.h>
#include <FSystem.h>
#include <math.h>
#include <FBase.h>
#include <FUi.h>
#include <FMedia.h>
#include <FUix.h>

#include "GlesCube.h"
#include "fragment.h"
#include "vertex.h"


using namespace Tizen::Base;
using namespace Tizen::Base::Runtime;
using namespace Tizen::Graphics;
using namespace Tizen::Locales;
using namespace Tizen::System;
using namespace Tizen::App;
using namespace Tizen::System;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Graphics::Opengl;
using namespace Tizen::Ui::Scenes;
using namespace Tizen::Uix::Sensor;




const int TIME_OUT = 10;
const float PI = 3.1415926535897932384626433832795f;
//#define DISPLAY_FPS

class GlesForm
	: public Tizen::Ui::Controls::Form
	, public Tizen::Ui::Controls::IFormBackEventListener
 	, public Tizen::Ui::Scenes::ISceneEventListener
 	, public Tizen::Uix::Sensor::ISensorEventListener
{
public:
	GlesForm(GlesCube* pApp)
		: __pApp(pApp), __sensorMgr()
	{

	}

	virtual ~GlesForm(void)
	{
	}

	virtual result OnDraw(void)
	{
		return E_SUCCESS;
	}

	virtual result OnInitializing(void){

		__sensorMgr.Construct();
		AppLog("INITAIL!!");
		/* Check for the Sensors is supported in the current device or not */
		if (!__sensorMgr.IsAvailable(SENSOR_TYPE_GYRO))
		{
			AppLog("[Fail] SENSOR_TYPE_GYRO Sensor type does not supported. This sample cannot be activated.");

			SceneManager* pSceneManager = SceneManager::GetInstance();
			AppAssert(pSceneManager);
			//AppAssert(pSceneManager->GoBackward(BackwardSceneTransition(MainScene)) == E_SUCCESS);
			AppLog("FAILURE");
			return E_FAILURE;
		}
		StartSensor();
		AppLog("SUCCESS");
		return E_SUCCESS;
	}

	virtual result OnTerminating(void){
		AppLog("TERMINATING");
		StopSensor();
		return E_SUCCESS;
	}



	virtual void OnFormBackRequested(Tizen::Ui::Controls::Form& source){
		SceneManager* pSceneManager = SceneManager::GetInstance();
		AppAssert(pSceneManager);
		//AppAssert(pSceneManager->GoBackward(BackwardSceneTransition(MainScene)) == E_SUCCESS);
	}
	virtual void OnSceneActivatedN(const Tizen::Ui::Scenes::SceneId& previousSceneId,
								   const Tizen::Ui::Scenes::SceneId& currentSceneId, Tizen::Base::Collection::IList* pArgs){
		AppLog("ACTIVE");
			StartSensor();
	}
	virtual void OnSceneDeactivated(const Tizen::Ui::Scenes::SceneId& currentSceneId,
									const Tizen::Ui::Scenes::SceneId& nextSceneId){
		AppLog("DEACTIVE");
		StopSensor();
	}

	virtual void OnDataReceived(Tizen::Uix::Sensor::SensorType sensorType, Tizen::Uix::Sensor::SensorData& sensorData, result r){

		String strX, strY, strZ;

		TryReturnVoid(!IsFailed(r), "[%s] Invalid sensor data.", GetErrorMessage(r));
		AppLog("ON DATA RECIEVE");
		GyroSensorData& data = static_cast<GyroSensorData&>(sensorData);

		xxx = data.x;
		yyy = data.y;
		zzz = data.z;


		Invalidate(true);
	}


	void StartSensor(void)
	{
		long interval = 0L;

		AppLog("START SENSOR");
		AppLog("Adding the listener SensorsAppGyroForm...");

		__sensorMgr.GetMaxInterval(SENSOR_TYPE_GYRO, interval);
		__sensorMgr.AddSensorListener(*this, SENSOR_TYPE_GYRO, interval, false);
	}

	void StopSensor(void)
	{
		AppLog("STOP SENSOR");
		AppLog("Removing the listener SensorsAppGyroForm...");
		__sensorMgr.RemoveSensorListener(*this);
	}



	float getXX(){
		return this->xxx;
	}

	float getYY(){
			return this->yyy;
		}

	float getZZ(){
			return this->zzz;
	}


private:
	GlesCube* __pApp;
	Tizen::Uix::Sensor::SensorManager __sensorMgr;
	float __scaleValue;
	float xxx = 10.0F , yyy = 20.0F, zzz = 30.0F;

};




const GLfloat VERTICES[] =
{
	-0.5f, -0.5f, -0.5f,
	-0.5f, -0.5f,  0.5f,
	 0.5f, -0.5f,  0.5f,
	 0.5f, -0.5f, -0.5f,
	-0.5f,  0.5f, -0.5f,
	-0.5f,  0.5f,  0.5f,
	 0.5f,  0.5f,  0.5f,
	 0.5f,  0.5f, -0.5f,
	-0.5f, -0.5f, -0.5f,
	-0.5f,  0.5f, -0.5f,
	 0.5f,  0.5f, -0.5f,
	 0.5f, -0.5f, -0.5f,
	-0.5f, -0.5f,  0.5f,
	-0.5f,  0.5f,  0.5f,
	 0.5f,  0.5f,  0.5f,
	 0.5f, -0.5f,  0.5f,
	-0.5f, -0.5f, -0.5f,
	-0.5f, -0.5f,  0.5f,
	-0.5f,  0.5f,  0.5f,
	-0.5f,  0.5f, -0.5f,
	 0.5f, -0.5f, -0.5f,
	 0.5f, -0.5f,  0.5f,
	 0.5f,  0.5f,  0.5f,
	 0.5f,  0.5f, -0.5f
};

const GLshort INDICES[] =
{
	 0,  2,  1,
	 0,  3,  2,
	 4,  5,  6,
	 4,  6,  7,
	 8,  9, 10,
	 8, 10, 11,
	12, 15, 14,
	12, 14, 13,
	16, 17, 18,
	16, 18, 19,
	20, 23, 22,
	20, 22, 21
};

const int numIndices = 36;

const GLfloat COLORS[] =
{
	1.0, 0.0, 0.0, 1.0,
	0.0, 1.0, 0.0, 1.0,
	0.0, 0.0, 1.0, 1.0,
	1.0, 0.0, 0.0, 1.0,
	0.0, 1.0, 0.0, 1.0,
	0.0, 0.0, 1.0, 1.0,
	1.0, 0.0, 0.0, 1.0,
	0.0, 1.0, 0.0, 1.0,
	0.0, 0.0, 1.0, 1.0,
	1.0, 0.0, 0.0, 1.0,
	0.0, 1.0, 0.0, 1.0,
	0.0, 0.0, 1.0, 1.0,
	1.0, 0.0, 0.0, 1.0,
	0.0, 1.0, 0.0, 1.0,
	0.0, 0.0, 1.0, 1.0,
	1.0, 0.0, 0.0, 1.0,
	0.0, 1.0, 0.0, 1.0,
	0.0, 0.0, 1.0, 1.0,
	1.0, 0.0, 0.0, 1.0,
	0.0, 1.0, 0.0, 1.0,
	0.0, 0.0, 1.0, 1.0,
	1.0, 0.0, 0.0, 1.0,
	0.0, 1.0, 0.0, 1.0,
	0.0, 0.0, 1.0, 1.0,
};


GlesCube::GlesCube(void)
	: __eglDisplay(EGL_NO_DISPLAY)
	, __eglSurface(EGL_NO_SURFACE)
	, __eglConfig(null)
	, __eglContext(EGL_NO_CONTEXT)
	, __programObject(0)
	, __idxPosition(0)
	, __idxColor(0)
	, __idxMVP(0)
	, __angle(0.0f)
	, __pTimer(null)
	, __pForm(null)
{
}


GlesCube::~GlesCube(void)
{
}


void
GlesCube::Cleanup(void)
{
	if (__pTimer != null)
	{
		__pTimer->Cancel();
		delete __pTimer;
		__pTimer = null;
	}

	DestroyGL();
}


Application*
GlesCube::CreateInstance(void)
{
	return new (std::nothrow) GlesCube();
}


bool
GlesCube::OnAppInitializing(AppRegistry& appRegistry)
{
	result r = E_SUCCESS;
	Frame* pAppFrame = new (std::nothrow) Frame();
	TryReturn(pAppFrame != null, E_FAILURE, "[GlesCube] Generating a frame failed.");

	r = pAppFrame->Construct();
	TryReturn(!IsFailed(r), E_FAILURE, "[GlesCube] pAppFrame->Construct() failed.");

	this->AddFrame(*pAppFrame);

	__pForm = new (std::nothrow) GlesForm(this);
	TryCatch(__pForm != null, , "[GlesCube] Allocation of GlesForm failed.");

	r = __pForm->Construct(FORM_STYLE_NORMAL);
	TryCatch(!IsFailed(r), delete __pForm, "[GlesCube] __pForm->Construct(FORM_STYLE_NORMAL) failed.");

	r = GetAppFrame()->GetFrame()->AddControl(__pForm);
	TryCatch(!IsFailed(r), delete __pForm, "[GlesCube] GetAppFrame()->GetFrame()->AddControl(__pForm) failed.");

	__pForm->AddKeyEventListener(*this);

	TryCatch(InitEGL(), , "[GlesCube] GlesCube::InitEGL() failed.");

	TryCatch(InitGL(), , "[GlesCube] GlesCube::InitGL() failed.");

	__pTimer = new (std::nothrow) Timer;
	TryCatch(__pTimer != null, , "[GlesCube] Failed to allocate memory.");

	r = __pTimer->Construct(*this);
	TryCatch(!IsFailed(r), , "[GlesCube] __pTimer->Construct(*this) failed.");

	// Comment the following statement to stop listen to the screen on/off events.
	PowerManager::AddScreenEventListener(*this);

	return true;

CATCH:

	AppLog("[GlesCube] GlesCube::OnAppInitializing eglError : %#x\n"
			"[GlesCube] GlesCube::OnAppInitializing glError : %#x\n"
			"[GlesCube] GlesCube::OnAppInitializing VENDOR : %s\n"
			"[GlesCube] GlesCube::OnAppInitializing GL_RENDERER : %s\n"
			"[GlesCube] GlesCube::OnAppInitializing GL_VERSION : %s\n ",
			static_cast<unsigned int>(eglGetError()),
			static_cast<unsigned int>(glGetError()),
			glGetString(GL_VENDOR),
			glGetString(GL_RENDERER),
			glGetString(GL_VERSION));

	Cleanup();

	return false;
}


bool
GlesCube::OnAppTerminating(AppRegistry& appRegistry, bool forcedTermination)
{
	Cleanup();

	return true;
}


void
GlesCube::OnForeground(void)
{
	if (__pTimer != null)
	{
		__pTimer->Start(TIME_OUT);
	}
}


void
GlesCube::OnBackground(void)
{
	if (__pTimer != null)
	{
		__pTimer->Cancel();
	}
}


void
GlesCube::OnBatteryLevelChanged(BatteryLevel batteryLevel)
{
}


void
GlesCube::OnLowMemory(void)
{
}

void
GlesCube::OnKeyPressed(const Control& source, KeyCode keyCode)
{
}


void
GlesCube::OnKeyReleased(const Control& source, KeyCode keyCode)
{
	if (keyCode == Tizen::Ui::KEY_BACK || keyCode == Tizen::Ui::KEY_ESC)
	{
		Terminate();
	}
}


void
GlesCube::OnKeyLongPressed(const Control& source, KeyCode keyCode)
{
}

void
GlesCube::OnTimerExpired(Timer& timer)
{
	if (__pTimer == null)
	{
		return;
	}

	__pTimer->Start(TIME_OUT);

	Update();

	if (!Draw())
	{
		AppLog("[GlesCube] GlesCube::Draw() failed.");
	}
}


bool
GlesCube::InitEGL(void)
{
	EGLint numConfigs = 1;

	EGLint eglConfigList[] =
	{
		EGL_RED_SIZE,	8,
		EGL_GREEN_SIZE,	8,
		EGL_BLUE_SIZE,	8,
		EGL_ALPHA_SIZE,	8,
		EGL_DEPTH_SIZE, 8,
		EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
		EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
		EGL_NONE
	};

	EGLint eglContextList[] = 
	{
		EGL_CONTEXT_CLIENT_VERSION, 2,
		EGL_NONE
	};

	eglBindAPI(EGL_OPENGL_ES_API);

	__eglDisplay = eglGetDisplay((EGLNativeDisplayType)EGL_DEFAULT_DISPLAY);
	TryCatch(__eglDisplay != EGL_NO_DISPLAY, , "[GlesCube] eglGetDisplay() failed.");

	TryCatch(!(eglInitialize(__eglDisplay, null, null) == EGL_FALSE || eglGetError() != EGL_SUCCESS), , "[GlesCube] eglInitialize() failed.");

	TryCatch(!(eglChooseConfig(__eglDisplay, eglConfigList, &__eglConfig, 1, &numConfigs) == EGL_FALSE ||
			eglGetError() != EGL_SUCCESS), , "[GlesCube] eglChooseConfig() failed.");

	TryCatch(numConfigs, , "[GlesCube] eglChooseConfig() failed. because of matching config doesn't exist");

	__eglSurface = eglCreateWindowSurface(__eglDisplay, __eglConfig, (EGLNativeWindowType)__pForm, null);
	TryCatch(!(__eglSurface == EGL_NO_SURFACE || eglGetError() != EGL_SUCCESS), , "[GlesCube] eglCreateWindowSurface() failed.");

	__eglContext = eglCreateContext(__eglDisplay, __eglConfig, EGL_NO_CONTEXT, eglContextList);
	TryCatch(!(__eglContext == EGL_NO_CONTEXT || eglGetError() != EGL_SUCCESS), , "[GlesCube] eglCreateContext() failed.");

	TryCatch(!(eglMakeCurrent(__eglDisplay, __eglSurface, __eglSurface, __eglContext) == EGL_FALSE ||
			eglGetError() != EGL_SUCCESS), , "[GlesCube] eglMakeCurrent() failed.");

	return true;

CATCH:
	{
		AppLog("[GlesCube] GlesCube can run on systems which supports OpenGL ES(R) 2.0.");
		AppLog("[GlesCube] When GlesCube does not correctly execute, there are a few reasons.");
		AppLog("[GlesCube]    1. The current device(real-target or emulator) does not support OpenGL ES(R) 2.0.\n"
				" Check the Release Notes.");
		AppLog("[GlesCube]    2. The system running on emulator cannot support OpenGL(R) 2.1 or later.\n"
				" Try with other system.");
		AppLog("[GlesCube]    3. The system running on emulator does not maintain the latest graphics driver.\n"
				" Update the graphics driver.");
	}

	DestroyGL();

	return false;
}


bool
GlesCube::InitGL(void)
{
    GLint linked = GL_FALSE;
    GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(fragShader, 1, static_cast<const char**> (&FRAGMENT_TEXT), null);
    glCompileShader(fragShader);
    GLint bShaderCompiled = GL_FALSE;
    glGetShaderiv(fragShader, GL_COMPILE_STATUS, &bShaderCompiled);

    TryCatch(bShaderCompiled != GL_FALSE, , "[GlesCube] bShaderCompiled = GL_FALSE");

    glShaderSource(vertShader, 1, static_cast<const char**> (&VERTEX_TEXT), null);
    glCompileShader(vertShader);
    glGetShaderiv(vertShader, GL_COMPILE_STATUS, &bShaderCompiled);

    TryCatch(bShaderCompiled != GL_FALSE, , "[GlesCube] bShaderCompiled == GL_FALSE");

	__programObject = glCreateProgram();
	glAttachShader(__programObject, fragShader);
	glAttachShader(__programObject, vertShader);
	glLinkProgram(__programObject);
	glGetProgramiv(__programObject, GL_LINK_STATUS, &linked);

	if (linked == GL_FALSE)
	{
		GLint infoLen = 0;
		glGetProgramiv(__programObject, GL_INFO_LOG_LENGTH, &infoLen);

		if (infoLen > 1)
		{
			char* infoLog = new (std::nothrow) char[infoLen];
			glGetProgramInfoLog(__programObject, infoLen, null, infoLog);
			AppLog("[GlesCube] Linking failed. log: %s", infoLog);
			delete [] infoLog;
		}

		TryCatch(false, , "[GlesCube] linked == GL_FALSE");
	}

	__idxPosition = glGetAttribLocation(__programObject, "a_position");
	__idxColor = glGetAttribLocation(__programObject, "a_color");
	__idxMVP = glGetUniformLocation(__programObject, "u_mvpMatrix");

	glUseProgram(__programObject);

	glEnable(GL_DEPTH_TEST);

	__angle = 45.0f;

	glDeleteShader(vertShader);
	glDeleteShader(fragShader);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	return true;

CATCH:
	glDeleteShader(vertShader);
	glDeleteShader(fragShader);

	return false;
}


void
GlesCube::DestroyGL(void)
{
	if (__programObject)
	{
		glDeleteProgram(__programObject);
	}

	if (__eglDisplay)
	{
		eglMakeCurrent(__eglDisplay, null, null, null);

		if (__eglContext)
		{
			eglDestroyContext(__eglDisplay, __eglContext);
			__eglContext = EGL_NO_CONTEXT;
		}

		if (__eglSurface)
		{
			eglDestroySurface(__eglDisplay, __eglSurface);
			__eglSurface = EGL_NO_SURFACE;
		}

		eglTerminate(__eglDisplay);
		__eglDisplay = EGL_NO_DISPLAY;
	}

	return;
}


void
GlesCube::Update(void)
{
	FloatMatrix4 matPerspective;
	FloatMatrix4 matModelview;

	//__angle += 5.0f;
float xx,yy,zz;
GlesForm* glesform = (GlesForm*)__pForm;
	xx = glesform->getXX();
	yy = glesform->getYY();
	zz = glesform->getZZ();
	if (__angle >= 360.0f)
	{
		__angle -= 360.0f;
	}

	int x, y, width, height;
	__pForm->GetBounds(x, y, width, height);

	float aspect = float(width) / float(height);

	Perspective(&matPerspective, 60.0f, aspect, 1.0f, 20.0f);

	Translate(&matModelview, 0.0f, 0.0f, -2.5f);
	Rotate(&matModelview, __angle, xx, yy, zz);

	__matMVP = matPerspective * matModelview;
}


bool
GlesCube::Draw(void)
{
	if (eglMakeCurrent(__eglDisplay, __eglSurface, __eglSurface, __eglContext) == GL_FALSE ||
			eglGetError() != EGL_SUCCESS)
	{
		AppLog("[GlesCube] eglMakeCurrent() failed.");

		return false;
	}

	int x, y, width, height;
	__pForm->GetBounds(x, y, width, height);

	glViewport(0, 0, width, height);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glVertexAttribPointer(__idxPosition, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), VERTICES);
	glVertexAttribPointer(__idxColor, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GL_FLOAT), COLORS);

	glEnableVertexAttribArray(__idxPosition);
	glEnableVertexAttribArray(__idxColor);

	glUniformMatrix4fv(__idxMVP, 1, GL_FALSE, (GLfloat*)__matMVP.matrix);

	glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_SHORT, INDICES);

	eglSwapBuffers(__eglDisplay, __eglSurface);

#ifdef DISPLAY_FPS
	static float     fps = 0.0f;
	static float     updateInterval = 100.0f;
	static float     timeSinceLastUpdate = 0.0f;
	static float     frameCount = 0;
	static long long currentTick;
	static long long lastTick;
	static bool      isFirst = true;

	if (isFirst)
	{
		SystemTime::GetTicks(currentTick);
		lastTick = currentTick;
		isFirst = false;
	}

	frameCount++;
	SystemTime::GetTicks(currentTick);

	float elapsed = currentTick - lastTick;

	lastTick = currentTick;
	timeSinceLastUpdate += elapsed;

	if (timeSinceLastUpdate > updateInterval)
	{
		if (timeSinceLastUpdate)
		{
			fps = (frameCount / timeSinceLastUpdate) * 1000.f;
			AppLog("[GlesCube] FPS: %f frames/sec", fps);

			frameCount = 0;
			timeSinceLastUpdate -= updateInterval;
		}
	}
#endif

	return true;
}

void
GlesCube::Frustum(FloatMatrix4* pResult, float left, float right, float bottom, float top, float near, float far)
{
    float diffX = right - left;
    float diffY = top - bottom;
    float diffZ = far - near;

    if ((near <= 0.0f) || (far <= 0.0f) ||
        (diffX <= 0.0f) || (diffY <= 0.0f) || (diffZ <= 0.0f))
	{
    	return;
	}

    pResult->matrix[0][0] = 2.0f * near / diffX;
    pResult->matrix[1][1] = 2.0f * near / diffY;
    pResult->matrix[2][0] = (right + left) / diffX;
    pResult->matrix[2][1] = (top + bottom) / diffY;
    pResult->matrix[2][2] = -(near + far) / diffZ;
    pResult->matrix[2][3] = -1.0f;
    pResult->matrix[3][2] = -2.0f * near * far / diffZ;

    pResult->matrix[0][1] = pResult->matrix[0][2] = pResult->matrix[0][3] = 0.0f;
    pResult->matrix[1][0] = pResult->matrix[1][2] = pResult->matrix[1][3] = 0.0f;
    pResult->matrix[3][0] = pResult->matrix[3][1] = pResult->matrix[3][3] = 0.0f;
}

void
GlesCube::Perspective(FloatMatrix4* pResult, float fovY, float aspect, float near, float far)
{
	float fovRadian = fovY / 360.0f * PI;
	float top = tanf(fovRadian) * near;
	float right = top * aspect;

	Frustum(pResult, -right, right, -top, top, near, far);
}

void
GlesCube::Translate(FloatMatrix4* pResult, float tx, float ty, float tz)
{
	pResult->matrix[3][0] += (pResult->matrix[0][0] * tx + pResult->matrix[1][0] * ty + pResult->matrix[2][0] * tz);
	pResult->matrix[3][1] += (pResult->matrix[0][1] * tx + pResult->matrix[1][1] * ty + pResult->matrix[2][1] * tz);
    pResult->matrix[3][2] += (pResult->matrix[0][2] * tx + pResult->matrix[1][2] * ty + pResult->matrix[2][2] * tz);
    pResult->matrix[3][3] += (pResult->matrix[0][3] * tx + pResult->matrix[1][3] * ty + pResult->matrix[2][3] * tz);
}

void
GlesCube::Rotate(FloatMatrix4* pResult, float angle, float x, float y, float z)
{
	FloatMatrix4 rotate;

	float cos = cosf(angle * PI / 180.0f);
	float sin = sinf(angle * PI / 180.0f);
	float cos1 = 1.0f - cos;

	FloatVector4 vector(x, y, z, 0.0f);
	vector.Normalize();
	x = vector.x;
	y = vector.y;
	z = vector.z;



	rotate.matrix[0][0] = (x * x) * cos1 + cos;
	rotate.matrix[0][1] = (x * y) * cos1 - z * sin;
	rotate.matrix[0][2] = (z * x) * cos1 + y * sin;
	rotate.matrix[0][3] = 0.0f;

	rotate.matrix[1][0] = (x * y) * cos1 + z * sin;
	rotate.matrix[1][1] = (y * y) * cos1 + cos;
	rotate.matrix[1][2] = (y * z) * cos1 - x * sin;
	rotate.matrix[1][3] = 0.0f;

	rotate.matrix[2][0] = (z * x) * cos1 - y * sin;
	rotate.matrix[2][1] = (y * z) * cos1 + x * sin;
	rotate.matrix[2][2] = (z * z) * cos1 + cos;

	rotate.matrix[2][3] = rotate.matrix[3][0] = rotate.matrix[3][1] = rotate.matrix[3][2] = 0.0f;
	rotate.matrix[3][3] = 1.0f;

	*pResult *= rotate;
}

void
GlesCube::OnScreenOn(void)
{
}

void
GlesCube::OnScreenOff(void)
{
}

