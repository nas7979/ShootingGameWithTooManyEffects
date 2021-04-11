#pragma once
#include <math.h>
#include <Windows.h>
#include <time.h>
#include <ddraw.h>
#include <functional>
#include <string>
#include <vector>
#include <map>
#include <list>
#include <algorithm>

#pragma comment(lib, "dsound.lib")
#include "SDKsound.h"

const float WINSIZEX = 1280;
const float WINSIZEY = 720;


using Vec2 = D3DXVECTOR2;
using Vec3 = D3DXVECTOR3;
using Matrix = D3DXMATRIX;
#include "cMath.h"
using namespace std;
using namespace Math;

#define g_Device DXUTGetD3D9Device()
#define DeltaTime DXUTGetElapsedTime()

#include "cSceneManager.h"
#include "cImageManager.h"
#include "cObjectManager.h"
#include "cInputManager.h"
#include "cParticleManager.h"
#include "cSystemManager.h"
#include "cSoundManager.h"
#include "cCameraManager.h"

#include "cRenderer.h"
#include "cPath.h"
#include "cCollider.h"
#include "cAnimation.h"
#include "cTimeLine.h"