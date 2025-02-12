#include <windows.h>

const char* dotFlac = ".flac";
const char* flac = "flac";

bool Hook(char* src, char* dst, int len, const char* op, int opSize) {
    if (len < 4 + opSize) return false;

    DWORD curProtection;
    VirtualProtect(src, len, PAGE_EXECUTE_READWRITE, &curProtection);
    memset(src, 0x90, len);

    uintptr_t relativeAddress = (uintptr_t)(dst - src - (4 + opSize));

    for (int i = 0; i < opSize; i++)
        *(src + i) = op[i];
    *(uintptr_t*)(src + opSize) = (uintptr_t)relativeAddress;

    DWORD temp;
    VirtualProtect(src, len, curProtection, &temp);

    return true;
}

void WriteMemory(LPVOID address, LPVOID value, int byteNum) {
    unsigned long oldProtection;

    VirtualProtect(address, byteNum, PAGE_EXECUTE_READWRITE, &oldProtection);
    memcpy(address, value, byteNum);
    VirtualProtect(address, byteNum, oldProtection, &oldProtection);
}

DWORD sub_43B280 = 0x43B280;
DWORD sub_43B210 = 0x43B210;
DWORD sub_43B3C0 = 0x43B3C0;
DWORD sub_43B650 = 0x43B650;
DWORD LoadFile = 0x439510;
DWORD checkWav = 0x43A75E;
DWORD lr2strlen = 0x43AD90;
DWORD loc_43A711 = 0x43A711;

__declspec(naked) void hkFlac() {
    __asm {
        push dotFlac
        lea ecx, [esp + 0x28]
        call sub_43B280
        cmp eax, esi
        jnz doWav

        lea ecx, [esp + 0xc]
        call lr2strlen
        sub eax, 3
        push eax
        lea ecx, [esp + 0x10]
        call sub_43B210
        push flac
        lea ecx, [esp + 0x10]
        call sub_43B3C0
        push ecx
        mov ecx, esp
        mov DWORD PTR[esp + 0x14], esp
        push ebx
        lea edx, [esp + 0x14]
        push edx
        call sub_43B650
        call LoadFile
        add esp, 4
        cmp al, bl
        jnz fileLoaded

    doWav:
        jmp checkWav

    fileLoaded:
        jmp loc_43A711
    }
}

__declspec(naked) void hkTrampFlac() {
    __asm {
        add esp, 4
        cmp al, bl
        jz hkFlac

        jmp loc_43A711
    }
}

DWORD WINAPI Setup(HMODULE hModule) {
    Hook((char*)0x43A70A, (char*)hkTrampFlac, 7, "\xE9", 1);
    WriteMemory((char*)0x43A779, (char*)"\x83\xE8\x04", 3);
    Hook((char*)0x43A6C9, (char*)hkFlac, 6, "\x0F\x85", 2);

    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
)
{
    HANDLE hThread;
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        hThread = CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)Setup, hModule, 0, nullptr);
        if (hThread == nullptr) {
            return FALSE;
        }

        CloseHandle(hThread);
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}