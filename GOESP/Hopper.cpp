
#include <Windows.h>

bool bunnyHop = false;

DWORD dwClient = (DWORD)GetModuleHandle("client.dll");
DWORD m_dwLocalPlayer = 0x000000;
DWORD m_dwForceJump = 0x000000;
DWORD m_onAir = 0x100;

void toggleBunny();

struct MyPlayer_t
{
    DWORD CBase;
    int onAir;

    void PlayerInfo()
    {
        CBase = *(DWORD*)(dwClient + m_dwLocalPlayer); // Player Base Pointer
        if (CBase > 0)
        {
            onAir = *(int*)(CBase + m_onAir); // Player On Air Pointer
            if (bunnyHop)
                toggleBunny();
        }

    }
}Player;

void toggleBunny()
{
    if (Player.onAir == 256) // if player is in the air
        *(int*)(dwClient + m_dwForceJump) = 4; // dont jump
    else
        *(int*)(dwClient + m_dwForceJump) = 5; // jump
}

void keyPress()
{
    if (GetAsyncKeyState(VK_SPACE))
        bunnyHop = true;
    else
        bunnyHop = false;
}

BOOL WINAPI myStuff()
{
    do
    {
        keyPress(); // Checking keypress
        Player.PlayerInfo(); // retrieving player info
    } while (true);
    return 0;
}


BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    if (fdwReason == DLL_PROCESS_ATTACH)
        CreateThread(0, 0, (LPTHREAD_START_ROUTINE)myStuff, 0, 0, 0);
    return 1;
}