#pragma once
#include <windows.h>
#include <winternl.h>
#include <process.h>
#include <tlhelp32.h>
#include <inttypes.h>
#include <iostream>
#include <random>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <chrono>
#include <sstream>
#include <d3d9.h>
#include "directx9/d3dx9.h"

#pragma comment (lib, "d3d9.lib")

#include "Imgui/imgui.h"
#include "Imgui/imgui_impl_dx9.h"
#include "Imgui/imgui_impl_win32.h"
#include "defs.h"

#include "ud.h"

namespace librarys
{
	HMODULE user32;
	HMODULE win32u;
	bool init()
	{
		HMODULE user32_lib = LoadLibraryA("user32.dll");
		if (!user32_lib) return false;
		HMODULE win32u_lib = LoadLibraryA("win32u.dll");
		if (!win32u_lib) return false;
		user32 = GetModuleHandleA("user32.dll");
		if (!user32) return false;
		win32u = GetModuleHandleA("win32u.dll");
		if (!win32u) return false;
		return true;
	}
}

class _driver
{
private:
	typedef __int64(*NtUserFunction)(uintptr_t);
	NtUserFunction nt_user_function = 0;
	enum REQUEST_TYPE : int
	{
		NONE,
		BASE,
		WRITE,
		READ
	};
	typedef struct _DRIVER_REQUEST
	{
		REQUEST_TYPE type;
		HANDLE pid;
		PVOID address;
		PVOID buffer;
		SIZE_T size;
		PVOID base;
	} DRIVER_REQUEST, * PDRIVER_REQUEST;
	void send_request(PDRIVER_REQUEST out)
	{
		RtlSecureZeroMemory(out, 0);
		nt_user_function(reinterpret_cast<uintptr_t>(out));
	}
public:
	int process_id;
	uintptr_t base_address;
	DWORD get_process_id(LPCTSTR process_name)
	{
		PROCESSENTRY32 pt{};
		HANDLE hsnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
		pt.dwSize = sizeof(PROCESSENTRY32);
		if (Process32First(hsnap, &pt))
		{
			do {
				if (!lstrcmpi(pt.szExeFile, process_name))
				{
					CloseHandle(hsnap);
					return pt.th32ProcessID;
				}
			} while (Process32Next(hsnap, &pt));
		}
		CloseHandle(hsnap);
		return 0;
	}
	bool setup()
	{
		nt_user_function = reinterpret_cast<NtUserFunction>(GetProcAddress(librarys::user32, "NtUserGetPointerDeviceProperties"));
		if (!nt_user_function)
		{
			nt_user_function = reinterpret_cast<NtUserFunction>(GetProcAddress(librarys::win32u, "NtUserGetPointerDeviceProperties"));
			if (!nt_user_function) return false;
		}
		return true;
	}
	uintptr_t get_base_address()
	{
		DRIVER_REQUEST out{};
		out.type = BASE;
		out.pid = (HANDLE)process_id;
		send_request(&out);
		return (uintptr_t)out.base;
	}
	void writem(PVOID address, PVOID buffer, DWORD size)
	{
		DRIVER_REQUEST out{};
		out.type = WRITE;
		out.pid = (HANDLE)process_id;
		out.address = address;
		out.buffer = buffer;
		out.size = size;
		send_request(&out);
	}
	void readm(PVOID address, PVOID buffer, DWORD size)
	{
		DRIVER_REQUEST out{};
		out.type = READ;
		out.pid = (HANDLE)process_id;
		out.address = address;
		out.buffer = buffer;
		out.size = size;
		send_request(&out);
	}
	template<typename T> void write(uintptr_t address, T value)
	{
		writem((PVOID)address, &value, sizeof(T));
	}
	template<typename T> T read(uintptr_t address)
	{
		T buffer{};
		readm((PVOID)address, &buffer, sizeof(T));
		return buffer;
	}
};
_driver driver;

uint64_t base_address;
HWND hwnd = NULL;
DWORD processID;

int Width;
int Height;

#define M_PI 3.14159265358979323846264338327950288419716939937510

typedef struct info_t {
	int pid = 0;
	DWORD_PTR address;
	void* value;
	SIZE_T size;
	void* data;
}info, * p_info;

static const char* aimkeys[]
{
	"Left Mouse Button",
	"Right Mouse Button",
	"Middle Mouse Button",
	"Mouse Side 1",
	"Mouse Side 2",
	"Control-Break Processing",
	"Backspace",
	"Tab",
	"Clear",
	"Enter",
	"SHIFT",
	"CTRL",
	"ALT",
	"Caps Lock",
	"Esc",
	"Space",
	"0",
	"1",
	"2",
	"3",
	"4",
	"5",
	"6",
	"7",
	"8",
	"9",
	"A",
	"B",
	"C",
	"D",
	"E",
	"F",
	"G",
	"H",
	"I",
	"J",
	"K",
	"L",
	"M",
	"N",
	"O",
	"P",
	"Q",
	"R",
	"S",
	"T",
	"U",
	"V",
	"W",
	"X",
	"Y",
	"Z",
	"Numpad 0",
	"Numpad 1",
	"Numpad 2",
	"Numpad 3",
	"Numpad 4",
	"Numpad 5",
	"Numpad 6",
	"Numpad 7",
	"Numpad 8",
	"Numpad 9",
	"Multiply"
};

static const char* hitboxes[]
{
	"Head",
	"Neck",
	"Chest",
	"Pelvis"
};

class Vector3
{
public:
	Vector3() : x(0.f), y(0.f), z(0.f)
	{

	}

	Vector3(double _x, double _y, double _z) : x(_x), y(_y), z(_z)
	{

	}
	~Vector3()
	{

	}

	double x;
	double y;
	double z;

	inline float Dot(Vector3 v)
	{
		return x * v.x + y * v.y + z * v.z;
	}

	inline float Distance(Vector3 v)
	{
		return float(sqrtf(powf(v.x - x, 2.0) + powf(v.y - y, 2.0) + powf(v.z - z, 2.0)));
	}

	Vector3 operator+(Vector3 v)
	{
		return Vector3(x + v.x, y + v.y, z + v.z);
	}

	Vector3 operator-(Vector3 v)
	{
		return Vector3(x - v.x, y - v.y, z - v.z);
	}

	Vector3 operator*(float number) const {
		return Vector3(x * number, y * number, z * number);
	}
};

struct FQuat
{
	double x;
	double y;
	double z;
	double w;
};

struct FTransform
{
	FQuat Rotation; // 0x00(0x10)
	Vector3 Translation; // 0x10(0x0c)
	uint32_t pad0001; // 0x1c(0x04)
	Vector3 Scale3D; // 0x20(0x0c)
	uint32_t pad0002; // 0x2c(0x04)

	FTransform() : Rotation{ (0.f, 0.f, 0.f, 0.f) }, Translation(0.f, 0.f, 0.f), Scale3D(0.f, 0.f, 0.f), pad0001(0), pad0002(0) { }

	FTransform(const FQuat& rot, const Vector3& translation, const Vector3& scale)
	{
		Rotation = rot;
		Translation = translation;
		Scale3D = scale;

		pad0001 = 0;
		pad0002 = 0;
	}

	D3DMATRIX ToMatrixWithScale()
	{
		D3DMATRIX m;

		m._41 = Translation.x;
		m._42 = Translation.y;
		m._43 = Translation.z;

		float x2 = Rotation.x + Rotation.x;
		float y2 = Rotation.y + Rotation.y;
		float z2 = Rotation.z + Rotation.z;

		float xx2 = Rotation.x * x2;
		float yy2 = Rotation.y * y2;
		float zz2 = Rotation.z * z2;
		m._11 = (1.0f - (yy2 + zz2)) * Scale3D.x;
		m._22 = (1.0f - (xx2 + zz2)) * Scale3D.y;
		m._33 = (1.0f - (xx2 + yy2)) * Scale3D.z;


		float yz2 = Rotation.y * z2;
		float wx2 = Rotation.w * x2;
		m._32 = (yz2 - wx2) * Scale3D.z;
		m._23 = (yz2 + wx2) * Scale3D.y;


		float xy2 = Rotation.x * y2;
		float wz2 = Rotation.w * z2;
		m._21 = (xy2 - wz2) * Scale3D.y;
		m._12 = (xy2 + wz2) * Scale3D.x;


		float xz2 = Rotation.x * z2;
		float wy2 = Rotation.w * y2;
		m._31 = (xz2 + wy2) * Scale3D.z;
		m._13 = (xz2 - wy2) * Scale3D.x;

		m._14 = 0.0f;
		m._24 = 0.0f;
		m._34 = 0.0f;
		m._44 = 1.0f;

		return m;
	}
};

D3DMATRIX MatrixMultiplication(D3DMATRIX pM1, D3DMATRIX pM2)
{
	D3DMATRIX pOut;
	pOut._11 = pM1._11 * pM2._11 + pM1._12 * pM2._21 + pM1._13 * pM2._31 + pM1._14 * pM2._41;
	pOut._12 = pM1._11 * pM2._12 + pM1._12 * pM2._22 + pM1._13 * pM2._32 + pM1._14 * pM2._42;
	pOut._13 = pM1._11 * pM2._13 + pM1._12 * pM2._23 + pM1._13 * pM2._33 + pM1._14 * pM2._43;
	pOut._14 = pM1._11 * pM2._14 + pM1._12 * pM2._24 + pM1._13 * pM2._34 + pM1._14 * pM2._44;
	pOut._21 = pM1._21 * pM2._11 + pM1._22 * pM2._21 + pM1._23 * pM2._31 + pM1._24 * pM2._41;
	pOut._22 = pM1._21 * pM2._12 + pM1._22 * pM2._22 + pM1._23 * pM2._32 + pM1._24 * pM2._42;
	pOut._23 = pM1._21 * pM2._13 + pM1._22 * pM2._23 + pM1._23 * pM2._33 + pM1._24 * pM2._43;
	pOut._24 = pM1._21 * pM2._14 + pM1._22 * pM2._24 + pM1._23 * pM2._34 + pM1._24 * pM2._44;
	pOut._31 = pM1._31 * pM2._11 + pM1._32 * pM2._21 + pM1._33 * pM2._31 + pM1._34 * pM2._41;
	pOut._32 = pM1._31 * pM2._12 + pM1._32 * pM2._22 + pM1._33 * pM2._32 + pM1._34 * pM2._42;
	pOut._33 = pM1._31 * pM2._13 + pM1._32 * pM2._23 + pM1._33 * pM2._33 + pM1._34 * pM2._43;
	pOut._34 = pM1._31 * pM2._14 + pM1._32 * pM2._24 + pM1._33 * pM2._34 + pM1._34 * pM2._44;
	pOut._41 = pM1._41 * pM2._11 + pM1._42 * pM2._21 + pM1._43 * pM2._31 + pM1._44 * pM2._41;
	pOut._42 = pM1._41 * pM2._12 + pM1._42 * pM2._22 + pM1._43 * pM2._32 + pM1._44 * pM2._42;
	pOut._43 = pM1._41 * pM2._13 + pM1._42 * pM2._23 + pM1._43 * pM2._33 + pM1._44 * pM2._43;
	pOut._44 = pM1._41 * pM2._14 + pM1._42 * pM2._24 + pM1._43 * pM2._34 + pM1._44 * pM2._44;

	return pOut;
}

std::string string_To_UTF8(const std::string& str)
{
	int nwLen = ::MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0);

	wchar_t* pwBuf = new wchar_t[nwLen + 1];
	ZeroMemory(pwBuf, nwLen * 2 + 2);

	::MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.length(), pwBuf, nwLen);

	int nLen = ::WideCharToMultiByte(CP_UTF8, 0, pwBuf, -1, NULL, NULL, NULL, NULL);

	char* pBuf = new char[nLen + 1];
	ZeroMemory(pBuf, nLen + 1);

	::WideCharToMultiByte(CP_UTF8, 0, pwBuf, nwLen, pBuf, nLen, NULL, NULL);

	std::string retStr(pBuf);

	delete[]pwBuf;
	delete[]pBuf;

	pwBuf = NULL;
	pBuf = NULL;

	return retStr;
}



static ImFont* Verdana, * Verdana2, * DefaultFont;

typedef struct
{
	DWORD R;
	DWORD G;
	DWORD B;
	DWORD A;
}RGBA;
class Color
{
public:
	RGBA red = { 255,0,0,255 };
	RGBA redlol = { 255,0,0,200 };
	RGBA Magenta = { 255,0,255,255 };
	RGBA yellow = { 255,255,0,255 };
	RGBA grayblue = { 128,128,255,255 };
	RGBA green = { 128,224,0,255 };
	RGBA darkgreen = { 0,224,128,255 };
	RGBA brown = { 192,96,0,255 };
	RGBA pink = { 255,168,255,255 };
	RGBA DarkYellow = { 216,216,0,255 };
	RGBA SilverWhite = { 236,236,236,255 };
	RGBA purple = { 144,0,255,255 };
	RGBA Navy = { 88,48,224,255 };
	RGBA skyblue = { 0,136,255,255 };
	RGBA graygreen = { 128,160,128,255 };
	RGBA blue = { 0,96,192,255 };
	RGBA orange = { 255,128,0,255 };
	RGBA peachred = { 255,80,128,255 };
	RGBA reds = { 255,128,192,255 };
	RGBA darkgray = { 96,96,96,255 };
	RGBA Navys = { 0,0,128,255 };
	RGBA cyan = { 0,255,255,255 };
	RGBA darkgreens = { 0,128,0,255 };
	RGBA darkblue = { 0,128,128,255 };
	RGBA redbrown = { 128,0,0,255 };
	RGBA purplered = { 128,0,128,255 };
	RGBA greens = { 0,255,0,255 };
	RGBA envy = { 0,255,255,255 };
	RGBA black = { 100,0,0,0 };
	RGBA gray = { 128,128,128,255 };
	RGBA white = { 255,255,255,255 };
	RGBA blues = { 30,144,255,255 };
	RGBA lightblue = { 135,206,250,160 };
	RGBA Scarlet = { 220, 20, 60, 160 };
	RGBA white_ = { 255,255,255,200 };
	RGBA gray_ = { 128,128,128,200 };
	RGBA black_ = { 100,000, 000, 000 };
	RGBA red_ = { 255,0,0,200 };
	RGBA Magenta_ = { 255,0,255,200 };
	RGBA yellow_ = { 255,255,0,200 };
	RGBA grayblue_ = { 128,128,255,200 };
	RGBA green_ = { 128,224,0,200 };
	RGBA darkgreen_ = { 0,224,128,200 };
	RGBA brown_ = { 192,96,0,200 };
	RGBA pink_ = { 255,168,255,200 };
	RGBA darkyellow_ = { 216,216,0,200 };
	RGBA silverwhite_ = { 236,236,236,200 };
	RGBA purple_ = { 144,0,255,200 };
	RGBA Blue_ = { 88,48,224,200 };
	RGBA skyblue_ = { 0,136,255,200 };
	RGBA graygreen_ = { 128,160,128,200 };
	RGBA blue_ = { 0,96,192,200 };
	RGBA orange_ = { 255,128,0,200 };
	RGBA pinks_ = { 255,80,128,200 };
	RGBA Fuhong_ = { 255,128,192,200 };
	RGBA darkgray_ = { 96,96,96,200 };
	RGBA Navy_ = { 0,0,128,200 };
	RGBA darkgreens_ = { 0,128,0,200 };
	RGBA darkblue_ = { 0,128,128,200 };
	RGBA redbrown_ = { 128,0,0,200 };
	RGBA purplered_ = { 128,0,128,200 };
	RGBA greens_ = { 0,255,0,200 };
	RGBA envy_ = { 0,255,255,200 };

	RGBA glassblack = { 0, 0, 0, 160 };
	RGBA GlassBlue = { 65,105,225,80 };
	RGBA glassyellow = { 255,255,0,160 };
	RGBA glass = { 200,200,200,60 };

	RGBA filled = { 0, 0, 0, 150 };

	RGBA Plum = { 221,160,221,160 };

	RGBA VisibleColor = { 255 / 255, 0, 0 };
	RGBA InvisibleColor = { 0, 255 / 255, 0 };
	RGBA FilledFov = { 0,0,0,160 };

	RGBA rainbow() {

		static float x = 0, y = 0;
		static float r = 0, g = 0, b = 0;

		if (y >= 0.0f && y < 255.0f) {
			r = 255.0f;
			g = 0.0f;
			b = x;
		}
		else if (y >= 255.0f && y < 510.0f) {
			r = 255.0f - x;
			g = 0.0f;
			b = 255.0f;
		}
		else if (y >= 510.0f && y < 765.0f) {
			r = 0.0f;
			g = x;
			b = 255.0f;
		}
		else if (y >= 765.0f && y < 1020.0f) {
			r = 0.0f;
			g = 255.0f;
			b = 255.0f - x;
		}
		else if (y >= 1020.0f && y < 1275.0f) {
			r = x;
			g = 255.0f;
			b = 0.0f;
		}
		else if (y >= 1275.0f && y < 1530.0f) {
			r = 255.0f;
			g = 255.0f - x;
			b = 0.0f;
		}

		float rainbow_speed = 0.25f;

		x += rainbow_speed; //increase this value to switch colors faster
		if (x >= 255.0f)
			x = 0.0f;

		y += rainbow_speed; //increase this value to switch colors faster
		if (y > 1530.0f)
			y = 0.0f;


		return RGBA{ (DWORD)r, (DWORD)g, (DWORD)b, 255 };
	}


};
static Color Col;

uint32_t g_local_team_id;
uint64_t g_local_player_controller;
uint64_t g_local_player_pawn;
uint64_t g_local_player_array;
uint64_t g_local_rootcomponent;
Vector3 g_local_relativelocation;
uint64_t g_local_currweapon;