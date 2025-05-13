// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "dirent.h"
#include <vector>
#include <string>
#pragma comment(linker, "/export:curl_easy_cleanup=actualcurl.curl_easy_cleanup")
#pragma comment(linker, "/export:curl_easy_duphandle=actualcurl.curl_easy_duphandle")
#pragma comment(linker, "/export:curl_easy_escape=actualcurl.curl_easy_escape")
#pragma comment(linker, "/export:curl_easy_getinfo=actualcurl.curl_easy_getinfo")
#pragma comment(linker, "/export:curl_easy_init=actualcurl.curl_easy_init")
#pragma comment(linker, "/export:curl_easy_pause=actualcurl.curl_easy_pause")
#pragma comment(linker, "/export:curl_easy_perform=actualcurl.curl_easy_perform")
#pragma comment(linker, "/export:curl_easy_recv=actualcurl.curl_easy_recv")
#pragma comment(linker, "/export:curl_easy_reset=actualcurl.curl_easy_reset")
#pragma comment(linker, "/export:curl_easy_send=actualcurl.curl_easy_send")
#pragma comment(linker, "/export:curl_easy_setopt=actualcurl.curl_easy_setopt")
#pragma comment(linker, "/export:curl_easy_strerror=actualcurl.curl_easy_strerror")
#pragma comment(linker, "/export:curl_easy_unescape=actualcurl.curl_easy_unescape")
#pragma comment(linker, "/export:curl_escape=actualcurl.curl_escape")
#pragma comment(linker, "/export:curl_formadd=actualcurl.curl_formadd")
#pragma comment(linker, "/export:curl_formfree=actualcurl.curl_formfree")
#pragma comment(linker, "/export:curl_formget=actualcurl.curl_formget")
#pragma comment(linker, "/export:curl_free=actualcurl.curl_free")
#pragma comment(linker, "/export:curl_getdate=actualcurl.curl_getdate")
#pragma comment(linker, "/export:curl_getenv=actualcurl.curl_getenv")
#pragma comment(linker, "/export:curl_global_cleanup=actualcurl.curl_global_cleanup")
#pragma comment(linker, "/export:curl_global_init=actualcurl.curl_global_init")
#pragma comment(linker, "/export:curl_global_init_mem=actualcurl.curl_global_init_mem")
#pragma comment(linker, "/export:curl_maprintf=actualcurl.curl_maprintf")
#pragma comment(linker, "/export:curl_mfprintf=actualcurl.curl_mfprintf")
#pragma comment(linker, "/export:curl_mprintf=actualcurl.curl_mprintf")
#pragma comment(linker, "/export:curl_msnprintf=actualcurl.curl_msnprintf")
#pragma comment(linker, "/export:curl_msprintf=actualcurl.curl_msprintf")
#pragma comment(linker, "/export:curl_multi_add_handle=actualcurl.curl_multi_add_handle")
#pragma comment(linker, "/export:curl_multi_assign=actualcurl.curl_multi_assign")
#pragma comment(linker, "/export:curl_multi_cleanup=actualcurl.curl_multi_cleanup")
#pragma comment(linker, "/export:curl_multi_fdset=actualcurl.curl_multi_fdset")
#pragma comment(linker, "/export:curl_multi_info_read=actualcurl.curl_multi_info_read")
#pragma comment(linker, "/export:curl_multi_init=actualcurl.curl_multi_init")
#pragma comment(linker, "/export:curl_multi_perform=actualcurl.curl_multi_perform")
#pragma comment(linker, "/export:curl_multi_remove_handle=actualcurl.curl_multi_remove_handle")
#pragma comment(linker, "/export:curl_multi_setopt=actualcurl.curl_multi_setopt")
#pragma comment(linker, "/export:curl_multi_socket=actualcurl.curl_multi_socket")
#pragma comment(linker, "/export:curl_multi_socket_action=actualcurl.curl_multi_socket_action")
#pragma comment(linker, "/export:curl_multi_socket_all=actualcurl.curl_multi_socket_all")
#pragma comment(linker, "/export:curl_multi_strerror=actualcurl.curl_multi_strerror")
#pragma comment(linker, "/export:curl_multi_timeout=actualcurl.curl_multi_timeout")
#pragma comment(linker, "/export:curl_mvaprintf=actualcurl.curl_mvaprintf")
#pragma comment(linker, "/export:curl_mvfprintf=actualcurl.curl_mvfprintf")
#pragma comment(linker, "/export:curl_mvprintf=actualcurl.curl_mvprintf")
#pragma comment(linker, "/export:curl_mvsnprintf=actualcurl.curl_mvsnprintf")
#pragma comment(linker, "/export:curl_mvsprintf=actualcurl.curl_mvsprintf")
#pragma comment(linker, "/export:curl_share_cleanup=actualcurl.curl_share_cleanup")
#pragma comment(linker, "/export:curl_share_init=actualcurl.curl_share_init")
#pragma comment(linker, "/export:curl_share_setopt=actualcurl.curl_share_setopt")
#pragma comment(linker, "/export:curl_share_strerror=actualcurl.curl_share_strerror")
#pragma comment(linker, "/export:curl_slist_append=actualcurl.curl_slist_append")
#pragma comment(linker, "/export:curl_slist_free_all=actualcurl.curl_slist_free_all")
#pragma comment(linker, "/export:curl_strequal=actualcurl.curl_strequal")
#pragma comment(linker, "/export:curl_strnequal=actualcurl.curl_strnequal")
#pragma comment(linker, "/export:curl_unescape=actualcurl.curl_unescape")
#pragma comment(linker, "/export:curl_version=actualcurl.curl_version")
#pragma comment(linker, "/export:curl_version_info=actualcurl.curl_version_info")

bool endsWith(const std::string& fullString,
    const std::string& ending)
{
    // Check if the ending string is longer than the full
    // string
    if (ending.size() > fullString.size())
        return false;

    // Compare the ending of the full string with the target
    // ending
    return fullString.compare(fullString.size()
        - ending.size(),
        ending.size(), ending)
        == 0;
}

DWORD WINAPI modLoaderThread(void* hModule) {
    MessageBoxA(nullptr, "You are running M21ModLoader v1.0.", "M21ModLoader", MB_OK);
    DIR* dir;
    struct dirent* ent;
    std::vector<std::string> mods = {};
    HMODULE hLib = LoadLibraryA("m21lcrashlog.dll");
    if (hLib == NULL) {
        MessageBoxA(nullptr, "An error occured while trying to load the M21ModLoader crash logger. Restart Geometry Dash and try again.", "M21ModLoader", MB_ICONERROR);
    }

    if ((dir = opendir("mods")) != NULL) {
        /* print all the files and directories within directory */
        while ((ent = readdir(dir)) != NULL) {
            if (endsWith(ent->d_name, ".dll")) {
                mods.push_back(ent->d_name);
            }
        }
        closedir(dir);
    }
    else {
        /* could not open directory */
        perror("");
        MessageBeep(SOUND_SYSTEM_BEEP);
        MessageBoxA(nullptr, "An error occured while trying to load your mods. Restart Geometry Dash and try again.", "M21ModLoader", MB_ICONERROR);
    }
    for (size_t i = 0; i < mods.size(); i++) {
        std::string modPath = "mods\\" + mods[i];
        std::wstring wModPath = std::wstring(modPath.begin(), modPath.end());
        HMODULE hLib = LoadLibraryA(modPath.c_str());

        if (hLib == NULL) {
            MessageBoxA(nullptr, "An error occured while trying to load your mods. Restart Geometry Dash and try again.", "M21ModLoader", MB_ICONERROR);
        }
    }
    return true;
}


BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
       CreateThread(0, 0x1000, modLoaderThread, hModule, 0, 0);
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

