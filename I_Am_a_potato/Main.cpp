#include <windows.h>
#include <windowsx.h>
#pragma comment(lib, "winmm.lib")

#define _USE_MATH_DEFINES
#include <cmath>
#include <ctime>

typedef struct
{
    FLOAT h;
    FLOAT s;
    FLOAT l;
} HSL;
// Unused in Program 
// DWORD WINAPI icons(LPVOID lpParams) {
//     HDC hdc = GetWindowDC(GetDesktopWindow());
//     int x = GetSystemMetrics(SM_CXSCREEN);
//     int y = GetSystemMetrics(SM_CYSCREEN);
//     while (true) {
//         hdc = GetWindowDC(GetDesktopWindow());
//         x = GetSystemMetrics(SM_CXSCREEN);
//         y = GetSystemMetrics(SM_CYSCREEN);
//         DrawIcon(hdc, rand() % x, rand() % y, LoadIcon(0, IDI_ERROR));
//         Sleep(10);
//         DrawIcon(hdc, rand() % x, rand() % y, LoadIcon(0, IDI_WARNING));
//         Sleep(10);
//         DrawIcon(hdc, rand() % x, rand() % y, LoadIcon(0, IDI_APPLICATION));
//         Sleep(10);
//         DrawIcon(hdc, rand() % x, rand() % y, LoadIcon(0, IDI_SHIELD));
//         Sleep(10);
//         ReleaseDC(0, hdc);
//     }
// }

#pragma region Sound Functions
VOID WINAPI sound1() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[8000 * 30] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>(t*((t&4096?t%655368<59392?7:t>>6:32)+(1&t>>14))>>(3&t>>(t&2048?2:10))|t>>(t&16384?t&4096?4:3:2)^((t>>6|t|t>>(t>>16))*10+((t>>11)&7))+t%125&t>>8|t>>4|t*t>>8&t>>8);
    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}
VOID WINAPI sound2() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[8000 * 30] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>(t*(t>>5|t>>8)>>(t>>16));
    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}
VOID WINAPI sound3() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[8000 * 30] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>(100*((t<<2|t>>5|t^63)&(t<<10|t>>11)));
    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}
VOID WINAPI sound4() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[8000 * 30] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>(20*t*t*(t>>11)/7);
    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}
#pragma endregion
#pragma region Graphics Functions
DWORD sines(LPVOID lpVoid) {
    HDC desk = GetDC(0); HWND wnd = GetDesktopWindow();
    int sw = GetSystemMetrics(0), sh = GetSystemMetrics(1);
    double angle = 0;
    while (1) {
        desk = GetDC(0);
        for (float i = 0; i < sw + sh; i += 0.99f) {
            int a = sin(angle) * 20;
            BitBlt(desk, 0, i, sw, 1, desk, a, i, SRCCOPY);
            angle += M_PI / 40;
            DeleteObject(&i); DeleteObject(&a);
        }
        ReleaseDC(wnd, desk);
        DeleteDC(desk); DeleteObject(&sw); DeleteObject(&sh); DeleteObject(&angle);
    }
}
VOID WINAPI ci(int x, int y, int w, int h)
{
    HDC hdc = GetDC(0);
    HRGN hrgn = CreateEllipticRgn(x, y, w + x, h + y);
    SelectClipRgn(hdc, hrgn);
    BitBlt(hdc, x, y, w, h, hdc, x, y, PATINVERT);
    DeleteObject(hrgn);
    ReleaseDC(NULL, hdc);
}
DWORD fun1(LPVOID lpVoid)
{
    RECT rect;
    GetWindowRect(GetDesktopWindow(), &rect);
    int w = rect.right - rect.left - 500, h = rect.bottom - rect.top - 500;

    for (int t = 0;; t++)
    {
        const int size = 1000;
        int x = rand() % (w + size) - size / 2, y = rand() % (h + size) - size / 2;

        for (int i = 0; i < size; i += 100)
        {
            ci(x - i / 2, y - i / 2, i, i);
        }
    }
    return 0x00;
}
DWORD fun2(LPVOID lpVoid)
{
    int w = GetSystemMetrics(0);
    int h = GetSystemMetrics(1);

    for (int t = 0;; t++)
    {
        HDC hdc = GetDC(0);
        BitBlt(hdc, 0, 0, w, h, hdc, -30, 0, SRCCOPY);
        BitBlt(hdc, 0, 0, w, h, hdc, w - 30, 0, SRCCOPY);
        BitBlt(hdc, 0, 0, w, h, hdc, 0, -30, SRCCOPY);
        BitBlt(hdc, 0, 0, w, h, hdc, 0, h - 30, SRCCOPY);
        BitBlt(hdc, 
            rand() % 25, 
            rand() % 25,
            w, 
            h, 
            hdc, 
            rand() % 25,
            rand() % 25,
            NOTSRCERASE
        );
        HPEN hPen = CreatePen(PS_SOLID, 2, RGB(rand() % 256, rand() % 256, rand() % 256));
        HPEN hOldPen = SelectPen(hdc, hPen);
        HBRUSH hBrush = CreateSolidBrush(RGB(rand() % 256, rand() % 256, rand() % 256));
        HBRUSH hOldBrush = SelectBrush(hdc, hBrush);
        POINT vertices[] = { 
            {
                rand() % w, 
                rand() % h
            }, 
            {
                rand() % w, 
                rand() % h
            }, 
            {
                rand() % w, 
                rand() % h
            } 
        };
        Polygon(hdc, vertices, sizeof(vertices) / sizeof(vertices[0]));
        SelectBrush(hdc, hOldBrush);
        DeleteObject(hBrush);
        SelectPen(hdc, hOldPen);
        DeleteObject(hPen);
        ReleaseDC(0, hdc);
    }
    return 0x00;
}
DWORD fun3(LPVOID lpVoid) {
    int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
    int signX = 1;
    int signY = 1;
    int signX1 = 1;
    int signY1 = 1;
    int incrementor = 10;
    int x = 10;
    int y = 10;
    while (1) {
        HDC hdc = GetDC(0);
        x += incrementor * signX;
        y += incrementor * signY;
        int top_x = 0 + x;
        int top_y = 0 + y;
        int bottom_x = 100 + x;
        int bottom_y = 100 + y;
        HBRUSH brush = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
        SelectObject(hdc, brush);
        Ellipse(hdc, top_x, top_y, bottom_x, bottom_y);
        if (y >= GetSystemMetrics(SM_CYSCREEN))
        {
            signY = -1;
        }

        if (x >= GetSystemMetrics(SM_CXSCREEN))
        {
            signX = -1;
        }

        if (y == 0)
        {
            signY = 1;
        }

        if (x == 0)
        {
            signX = 1;
        }
        Sleep(10);
        DeleteObject(brush);
        brush = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
        SelectObject(hdc, brush);
        BitBlt(hdc, 0, 0, w, h, hdc, -30, 0, 0x1900ac010e);
        BitBlt(hdc, 0, 0, w, h, hdc, w - 30, 0, 0x1900ac010e);
        BitBlt(hdc, 0, 0, w, h, hdc, 0, -30, 0x1900ac010e);
        BitBlt(hdc, 0, 0, w, h, hdc, 0, h - 30, 0x1900ac010e);
        DeleteObject(brush);
        ReleaseDC(0, hdc);
    }
}
DWORD fun4(LPVOID lpVoid)
{
    while (1) {
        HDC hdc = GetDC(NULL);
        int w = GetSystemMetrics(SM_CXSCREEN),
            h = GetSystemMetrics(SM_CYSCREEN),
            rx = rand() % w;
        BitBlt(hdc,
            rand() % 25,
            rand() % 25,
            w,
            h,
            hdc,
            rand() % 25,
            rand() % 25,
            NOTSRCERASE
        );
        BitBlt(hdc, rx, 10, 100, h, hdc, rx, 0, SRCCOPY);
        HPEN hPen = CreatePen(PS_SOLID, 2, RGB(rand() % 256, rand() % 256, rand() % 256));
        HPEN hOldPen = SelectPen(hdc, hPen);
        HBRUSH hBrush = CreateSolidBrush(RGB(rand() % 256, rand() % 256, rand() % 256));
        HBRUSH hOldBrush = SelectBrush(hdc, hBrush);
        POINT vertices[] = {
            {
                rand() % w,
                rand() % h
            },
            {
                rand() % w,
                rand() % h
            },
            {
                rand() % w,
                rand() % h
            }
        };
        Polygon(hdc, vertices, sizeof(vertices) / sizeof(vertices[0]));
        SelectBrush(hdc, hOldBrush);
        DeleteObject(hBrush);
        SelectPen(hdc, hOldPen);
        DeleteObject(hPen);
        ReleaseDC(0, hdc);
    }
    return 0x00;
}
#pragma endregion


int main()
{
    time_t rawtime;
    time(&rawtime);
    srand(rawtime);
    FreeConsole();

    sound1();
    HANDLE hFun1 = CreateThread(0, 0, fun1, 0, 0, 0);
    Sleep(30000);
    TerminateThread(hFun1, 0x00);
    CloseHandle(hFun1);
    MessageBoxW(
        NULL,
        L"$D$Sa%yk@#tp!oj@e,a##$",
        L"Potato.exe",
        MB_ICONERROR | MB_OK
    );
    sound2();
    HANDLE hFun2 = CreateThread(0, 0, fun2, 0, 0, 0);
    Sleep(30000);
    TerminateThread(hFun2, 0x00);
    CloseHandle(hFun2);
    MessageBoxW(
        NULL,
        L"AIOIOo)U-KH%&*(kjlY&^KLKH&*",
        L"Potato.exe",
        MB_ICONERROR | MB_OK
    );
    sound3();
    HANDLE hFun3 = CreateThread(0, 0, fun3, 0, 0, 0);
    Sleep(30000);
    TerminateThread(hFun3, 0x00);
    CloseHandle(hFun3);
    MessageBoxW(
        NULL,
        L"4p3-INUUI9u89n&*y98OIKL{PO{L",
        L"Potato.exe",
        MB_ICONERROR | MB_OK
    );
    sound4();
    HANDLE hFun4 = CreateThread(0, 0, fun4, 0, 0, 0);
    HANDLE hSines = CreateThread(0, 0, sines, 0, 0, 0);
    Sleep(30000);
    TerminateThread(hFun4, 0x00);
    CloseHandle(hFun4);
    TerminateThread(hSines, 0x00);
    CloseHandle(hSines);
}
