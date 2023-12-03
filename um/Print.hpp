#pragma once
// Icon Solution for Includes
#include <Windows.h>
#include <iostream>
#include <fcntl.h>
#include <thread>
#include <random>
#include <vector>
#include <string>
#include <io.h>
#include "Skicript.hpp"

HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
int num = 5, num2 = 3;

const char* SetWhite()
{
	SetConsoleTextAttribute(h, 7);
	return "";
}

const char* SetGreen()
{
	SetConsoleTextAttribute(h, 10);
	return "";
}

const char* SetBlue()
{
	SetConsoleTextAttribute(h, 3);
	return "";
}

const char* SetGold()
{
	SetConsoleTextAttribute(h, 6);
	return "";
}

const char* SetRed()
{
	SetConsoleTextAttribute(h, 4);
	return "";
}

void Log(const char* text)
{
	SetGreen();
	std::cout << E(">> ");
	SetWhite();
	std::cout << text;
}

void Log2(const char* text)
{
	SetGold();
	std::cout << E(">> ");
	SetWhite();
	std::cout << text;
}

void Log3(const char* text)
{
	SetBlue();
	std::cout << E(">> ");
	SetWhite();
	std::cout << text;
}

void Log4(const char* text)
{
	SetRed();
	std::cout << E(">> ");
	SetWhite();
	std::cout << text;
}

void Opti(const char* text)
{
	SetBlue();
	std::cout << E(" 1} ");
	SetWhite();
	std::cout << text << std::endl;
}

void Opt2(const char* text)
{
	SetBlue();
	std::cout << E(" 2} ");
	SetWhite();
	std::cout << text << std::endl;
}

void CountDown()
{
	std::cout << E("\n");
	while (num > -1)
	{
		SetBlue();
		std::cout << E("\r>> ");
		SetWhite();
		std::cout << E("Closing in ");

		SetBlue();
		std::cout << num;
		SetWhite();

		std::cout << E(" seconds! Please start your game...");
		Sleep(1000);
		num--;
	}
}

void Green(const char* text)
{
	SetGreen();
	std::cout << text << std::endl;
	SetWhite();
}

void Blue(const char* text)
{
	SetBlue();
	std::cout << text << std::endl;
	SetWhite();
}

void system_no_output(std::string command)
{
	command.insert(0, "/C ");

	SHELLEXECUTEINFOA ShExecInfo = { 0 };
	ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
	ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
	ShExecInfo.hwnd = NULL;
	ShExecInfo.lpVerb = NULL;
	ShExecInfo.lpFile = "cmd.exe";
	ShExecInfo.lpParameters = command.c_str();
	ShExecInfo.lpDirectory = NULL;
	ShExecInfo.nShow = SW_HIDE;
	ShExecInfo.hInstApp = NULL;

	if (ShellExecuteExA(&ShExecInfo) == FALSE)

		WaitForSingleObject(ShExecInfo.hProcess, INFINITE);

	DWORD rv;
	GetExitCodeProcess(ShExecInfo.hProcess, &rv);
	CloseHandle(ShExecInfo.hProcess);
}

std::string tm_to_readable_time(tm ctx)
{
	char buffer[80];

	strftime(buffer, sizeof(buffer), E("%m/%d/%y"), &ctx);

	return std::string(buffer);
}

static std::time_t string_to_timet(std::string timestamp)
{
	auto cv = strtol(timestamp.c_str(), NULL, 10);

	return (time_t)cv;
}

static std::tm timet_to_tm(time_t timestamp)
{
	std::tm context;

	localtime_s(&context, &timestamp);

	return context;
}