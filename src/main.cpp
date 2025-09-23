#include "everything_wrapper.h"
#include <iostream>
#include <windows.h>

bool checkEverythingDLL() {
    HMODULE hMod = LoadLibraryW(L"Everything64.dll");
    if (!hMod) {
        std::cerr << "[ERROR] Everything64.dll not found!" << std::endl;
        std::cerr << "Please copy Everything64.dll from your Everything SDK folder into the same directory as search_tool.exe." << std::endl;
        return false;
    }
    FreeLibrary(hMod);
    return true;
}

int main() {
    if (!checkEverythingDLL()) {
        return 1;
    }

    try {
        EverythingWrapper searcher;

        // Basic search
        searcher.setSearch("*.pdf");
        if (searcher.execute()) {
            auto results = searcher.getResults();
            std::cout << "Found " << results.size() << " PDF files:" << std::endl;
            for (size_t i = 0; i < std::min(results.size(), size_t(10)); i++) {
                std::cout << "- " << results[i] << std::endl;
            }
        }

        // Regex search
        searcher.reset();
        searcher.setSearch("[^\s]*\.someThing(?:\.[^\s]*)*");
        searcher.setRegex(true);
        if (searcher.execute()) {
            std::cout << "\nRegex search found " << searcher.getResultCount() << " results" << std::endl;
        }

    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
