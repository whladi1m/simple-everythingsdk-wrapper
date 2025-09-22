#include "everything_wrapper.h"
#include <Windows.h>
#include <codecvt>
#include <locale>

EverythingWrapper::EverythingWrapper() {
    // There is no Everything_Initialize in the SDK – just set up defaults.
    Everything_SetSearchW(L"");
    Everything_SetMatchPath(FALSE);
    Everything_SetMatchCase(FALSE);
    Everything_SetMatchWholeWord(FALSE);
    Everything_SetRegex(FALSE);
    Everything_SetMax(1000); // Default max results
}

EverythingWrapper::~EverythingWrapper() {
    // There is no Everything_CleanUp either – nothing to do here.
}

bool EverythingWrapper::setSearch(const std::string& query) {
    // Convert UTF-8 string to wide string
    int len = MultiByteToWideChar(CP_UTF8, 0, query.c_str(), -1, NULL, 0);
    std::wstring wquery(len, 0);
    MultiByteToWideChar(CP_UTF8, 0, query.c_str(), -1, &wquery[0], len);

    Everything_SetSearchW(wquery.c_str());
    return true;
}

bool EverythingWrapper::setRegex(bool enable) {
    Everything_SetRegex(enable);
    return true;
}

bool EverythingWrapper::execute() {
    return Everything_Query(TRUE) != FALSE;
}

std::vector<std::string> EverythingWrapper::getResults() {
    std::vector<std::string> results;
    unsigned long count = getResultCount();

    for (unsigned long i = 0; i < count; i++) {
        // First get the length of the full path
        DWORD len = Everything_GetResultFullPathNameW(i, NULL, 0);

        if (len > 0) {
            std::wstring wpath(len + 1, L'\0');
            Everything_GetResultFullPathNameW(i, &wpath[0], len + 1);

            // Convert wide string to UTF-8
            int utf8len = WideCharToMultiByte(CP_UTF8, 0, wpath.c_str(), -1, NULL, 0, NULL, NULL);
            std::string result(utf8len - 1, 0);
            WideCharToMultiByte(CP_UTF8, 0, wpath.c_str(), -1, &result[0], utf8len, NULL, NULL);

            results.push_back(result);
        }
    }

    return results;
}


unsigned long EverythingWrapper::getResultCount() const {
    return Everything_GetNumResults();
}

void EverythingWrapper::reset() {
    Everything_SetSearchW(L"");
}

bool EverythingWrapper::checkError() {
    DWORD error = Everything_GetLastError();
    return error == EVERYTHING_OK; // Correct constant
}

std::string EverythingWrapper::getLastError() const {
    DWORD error = Everything_GetLastError();

    switch (error) {
    case EVERYTHING_OK:
        return "No error";
    case EVERYTHING_ERROR_MEMORY:
        return "Memory error";
    case EVERYTHING_ERROR_IPC:
        return "IPC error - Is Everything running?";
    case EVERYTHING_ERROR_REGISTERCLASSEX:
        return "RegisterClassEx error";
    case EVERYTHING_ERROR_CREATEWINDOW:
        return "CreateWindow error";
    case EVERYTHING_ERROR_INVALIDINDEX:
        return "Invalid index";
    case EVERYTHING_ERROR_INVALIDCALL:
        return "Invalid API call";
    case EVERYTHING_ERROR_INVALIDREQUEST:
        return "Invalid request";
    default:
        return "Unknown error";
    }
}
