#ifndef PANEL_H
#define PANEL_H

#include <windows.h>
#include <windowsx.h>
#include <d2d1.h>
#pragma comment(lib, "d2d1")

#include <vector>

class Panel
{
public:
	Panel();
	~Panel();

protected:


private:
	std::vector<Panel*> cmp;
};

#endif