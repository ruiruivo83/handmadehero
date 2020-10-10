
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

// myhandmadehero.cpp : This file contains the 'main' function. Program execution begins and ends there.


#include <Windows.h>

#define internal static
#define local_persist static
#define global_variable static

// TODO(Rui): This is a global for now.
global_variable bool Running;

internal void ResizeDIBSection(int Width, int Height)
{

}

LRESULT CALLBACK MainWindowCallBack(
    HWND Window,
    UINT Message,
    WPARAM WParam,
    LPARAM LParam
) {
    LRESULT Result = 0;


    switch (Message)
    {


    case WM_SIZE:
    {
        // Gets th area in wish we can draw, witheout the borders.
        RECT ClientRect;
        GetClientRect(Window, &ClientRect);
        int Width = ClientRect.right - ClientRect.left;
        int Height = ClientRect.bottom - ClientRect.top;
        ResizeDIBSection(Width, Height);        
    } break;

    case WM_CLOSE:
    {
        // TODO(Rui): Handle this with a message to the user
        Running = false;
        PostQuitMessage(0);
        OutputDebugStringA("WM_CLOSE\n");
    } break;

    case WM_ACTIVATEAPP:
    {
        OutputDebugStringA("WM_ACTIVATEAPP\n");
    } break;

    case WM_DESTROY:
    {

        // TODO(Rui): Handle this as error
        Running = false;
        OutputDebugStringA("WM_DESTROY\n");
    } break;

    case WM_PAINT:
    {
        PAINTSTRUCT Paint;
        HDC DeviceContext = BeginPaint(Window, &Paint);
        int X = Paint.rcPaint.left;
        int Y = Paint.rcPaint.top;
        int Width = Paint.rcPaint.right - Paint.rcPaint.left;
        int Height = Paint.rcPaint.bottom - Paint.rcPaint.top;
        local_persist DWORD Operation = WHITENESS;
        PatBlt(DeviceContext, X, Y, Width, Height, Operation);
        if (Operation == WHITENESS) {
            Operation = BLACKNESS;
        }
        else {
            Operation = WHITENESS;
        }
        EndPaint(Window, &Paint);

    } break;

    default:
    {
        OutputDebugStringA("default\n");
        Result = DefWindowProc(Window, Message, WParam, LParam);
    } break;

    }


    return(Result);
}



int main(
    HINSTANCE Instance,
    HINSTANCE PrevInstance,
    LPSTR CommandLine,
    int ShowCode
)
{

    // Simple MEssage Box 
    // MessageBoxA(0, "Hand Made Hero Message", "Hand Made Hero Title", MB_OK | MB_ICONINFORMATION);


    WNDCLASS WindowClass = {};

    // TODO - 
    WindowClass.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
    WindowClass.lpfnWndProc = MainWindowCallBack;
    WindowClass.hInstance = Instance;
    // WindowClass.hIcon;    
    WindowClass.lpszClassName = L"HandMadeHeroWindowClass";

    if (RegisterClass(&WindowClass))
    {
        HWND WindowHandle = CreateWindowEx(
            0,
            WindowClass.lpszClassName,
            L"Hand Made Hero",
            WS_OVERLAPPEDWINDOW | WS_VISIBLE,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            0,
            0,
            Instance,
            0);
        if (WindowHandle)
        {
            Running = true;
            while (Running) {
                MSG Message;
                BOOL MessageResult = GetMessage(&Message, 0, 0, 0);
                if (MessageResult > 0)
                {
                    // Translate and dispatch this message
                    TranslateMessage(&Message);
                    DispatchMessage(&Message);
                }
                else {
                    break;
                }
            }
        }
        else {
            // TODO(Rui): Logging
        }
    }
    else
    {
        // TODO(Rui): Logging
    }

    return (0);
}
