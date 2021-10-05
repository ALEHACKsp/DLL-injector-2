#include "include.h"

int inject()
{
    GetFullPathName("refo.dll", MAX_PATH, yol, NULL);
    exe = find_process("notepad.exe");


    auto* const acc = OpenProcess(PROCESS_ALL_ACCESS, 0, exe);

    if (acc && acc != INVALID_HANDLE_VALUE)
    {
        const LPVOID enayi = GetProcAddress(LoadLibraryA(L"ntdll.dll"), "NtSetSystemTime"); /* ->Windows Global Time Hook
EAC & BE Undetected But this topic is not covered here because it is the injector ring 3.*/
        if (enayi)
        {
            char byte[5];
            memcpy(byte, enayi, 5);
            WriteProcessMemory(acc, enayi, byte, 5, nullptr);
        }

        auto* alls = VirtualAllocEx(acc, nullptr, MAX_PATH, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
        WriteProcessMemory(acc, alls, yol, strlen(yol) + 1, nullptr);
        auto* const thread = CreateRemoteThread(acc, nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(LoadLibraryA), alls, 0, nullptr);

        if (thread) CloseHandle(thread);
    }

    if (acc) CloseHandle(acc);

    std::cout << ("[+] Injected") << std::endl;
    Sleep(1500);
    return 0;
}

std::uint32_t find_process(const std::string& name)
{
    const auto snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (snap == INVALID_HANDLE_VALUE) {
        return 0;
    }

    PROCESSENTRY32 proc_entry{};
    proc_entry.dwSize = sizeof proc_entry;

    auto found_process = false;
    if (!!Process32First(snap, &proc_entry)) {
        do {
            if (name == proc_entry.szExeFile) {
                found_process = true;
                break;
            }
        } while (!!Process32Next(snap, &proc_entry));
    }

    CloseHandle(snap);
    return found_process
        ? proc_entry.th32ProcessID
        : 0;
}
