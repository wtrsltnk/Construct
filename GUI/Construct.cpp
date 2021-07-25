#include "Construct.h"
#include "../GL/WorldRenderer.h"
#include "../Textures/StubTexture.h"
#include "../Textures/bmploader.h"
#include <stdio.h>

Construct::Construct()
{
    this->userinput = std::make_unique<UserInput>(Construct::GetWindowsKeyMap());
    this->console = Console::Instance();
    this->userinput->AddHook(Console::UserInputKey);
    this->font = 0;

    this->strWindowClassName = "Construct";
    this->strWindowTitle = "Construct";
    this->dwWidth = 800;
    this->dwHeight = 600;
}

Construct::~Construct() = default;

void Construct::PreShow()
{
    printf("[Pre show]\n");
}

void Construct::OnInitialize()
{
    printf("[Initialize Game]\n");

    tVidProps p = {(int)this->dwWidth, (int)this->dwHeight, 32, true};

    this->SetVideoProps(p);

    if (!this->world.LoadWorld("C:\\Games\\Counter-strike Beta 7.1\\cstrike\\maps\\de_dust.bsp"))
    {
        printf("failed to load bsp");
    }

    this->font = this->context.CreateFont("Courier New", 14);
    this->console->SetFont(this->font);

    this->cam.Move(-20.0f, -5.0f, -5.0f);

    this->console->AddEntry("Loading textures...");
    LPTexture *texs = this->world.GetTextures();

    for (int i = 0; i < this->world.GetTextureCount(); i++)
    {
        texs[i]->UploadTexture();
    }

    ::glPolygonMode(GL_FRONT, GL_FILL);
    ::glShadeModel(GL_SMOOTH);
    ::glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    ::glEnable(GL_BLEND);

    this->renderer.SetupRenderer(this->world.VertList());
}

void Construct::OnIdle()
{
    this->ticker.UpdateTicker();

    this->context.OpenFrame();

    this->view.Setup3D();

    this->cam.Run();

    ::glColor3f(1.0f, 1.0f, 1.0f);
    ::glEnable(GL_TEXTURE_2D);
    ::glBindTexture(GL_TEXTURE_2D, 34);

    ::glBegin(GL_QUADS);
    ::glTexCoord2f(0.0f, 0.0f);
    ::glVertex3f(6.0f, 6.0f, 0.0f);
    ::glTexCoord2f(0.0f, 1.0f);
    ::glVertex3f(0.0f, 6.0f, 0.0f);
    ::glTexCoord2f(1.0f, 1.0f);
    ::glVertex3f(0.0f, 0.0f, 0.0f);
    ::glTexCoord2f(1.0f, 0.0f);
    ::glVertex3f(6.0f, 0.0f, 0.0f);
    ::glEnd();

    this->renderer.Render(this->world.FirstFace());
    this->view.Setup2D();

    this->console->Render(this->view.GetWidth(), this->view.GetHeight());

    this->context.CloseFrame();
}

void Construct::OnDestroy()
{
    printf("[Destroy Game]\n");

    this->context.DestroyGL();
}

void Construct::SetArguments(GameArguments *args)
{
    (void)args;
}

void Construct::SetVideoProps(tVidProps props)
{
    if (props.fullscreen)
    {
        this->SetWindowStyle(WS_POPUP, WS_EX_APPWINDOW);
    }
    else
    {
        this->SetWindowStyle(WS_OVERLAPPEDWINDOW, WS_EX_APPWINDOW | WS_EX_WINDOWEDGE);
    }

    int midx = ::GetSystemMetrics(SM_CXSCREEN) / 2;
    int midy = ::GetSystemMetrics(SM_CYSCREEN) / 2;

    this->SetSize(props.resx, props.resy);
    this->SetPosition(midx - (props.resx / 2), midy - (props.resy / 2));
}

LRESULT Construct::ObjectProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
        case WM_CREATE:
        {
            this->context.Initialize(this->hWnd);
            break;
        }
        case WM_SIZE:
        {
            this->view.Resize(LOWORD(lParam), HIWORD(lParam));
            break;
        }
        case WM_ACTIVATE:
        {
            WORD state = LOWORD(wParam);
            WORD minimized = HIWORD(wParam);

            this->bActive = (state != WA_INACTIVE) && (minimized == 0);
            break;
        }
        case WM_KEYDOWN:
        {
            if (wParam == VK_F1)
            {
                static bool b = false;
                static tVidProps p = {(int)this->dwWidth, (int)this->dwHeight, 32, false};

                p.fullscreen = b;
                b = !b;

                this->SetVideoProps(p);
            }
            else if (wParam == VK_ESCAPE)
            {
                ::PostQuitMessage(0);
            }
            /*
			char str[234] = {0};
			sprintf(str, "key: %d", wParam);MessageBox(hWnd, str, "", MB_OK);
			*/
            this->userinput->ChangeKeyState(wParam, true);
            break;
        }
        case WM_KEYUP:
        {
            this->userinput->ChangeKeyState(wParam, false);
            break;
        }
        case WM_LBUTTONDOWN:
        {
            this->userinput->ChangeKeyState(VK_LBUTTON, true);
            break;
        }
        case WM_LBUTTONUP:
        {
            this->userinput->ChangeKeyState(VK_LBUTTON, false);
            break;
        }
        case WM_RBUTTONDOWN:
        {
            this->userinput->ChangeKeyState(VK_RBUTTON, true);
            break;
        }
        case WM_RBUTTONUP:
        {
            this->userinput->ChangeKeyState(VK_RBUTTON, false);
            break;
        }
        case WM_MBUTTONDOWN:
        {
            this->userinput->ChangeKeyState(VK_MBUTTON, true);
            break;
        }
        case WM_MBUTTONUP:
        {
            this->userinput->ChangeKeyState(VK_MBUTTON, false);
            break;
        }
    }
    return ::DefWindowProc(hWnd, msg, wParam, lParam);
}
