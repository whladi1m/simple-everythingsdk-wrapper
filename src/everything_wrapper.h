#pragma once
// First include Windows.h with proper definitions
#define WIN32_LEAN_AND_MEAN
#define _WIN32_WINNT 0x0600
#include <windows.h>

// Define calling convention for Everything SDK
#ifndef EVERYTHINGAPI
#define EVERYTHINGAPI __stdcall
#endif

// Now include Everything.h
#include "Everything.h"

#include <string>
#include <vector>
#include <stdexcept>
/**
 * @class EverythingWrapper
 * @brief C++ wrapper for Everything SDK search functionality
 */
class EverythingWrapper {
public:
    EverythingWrapper();
    ~EverythingWrapper();

    /**
     * Set the search query
     * @param query Search string (supports Everything pattern matching)
     * @return true if successful
     */
    bool setSearch(const std::string& query);

    /**
     * Enable or disable regex search
     * @param enable true to enable regex search
     * @return true if successful
     */
    bool setRegex(bool enable);

    /**
     * Execute the search query
     * @return true if search executed successfully
     */
    bool execute();

    /**
     * Get all result paths from the last search
     * @return Vector of file paths
     */
    std::vector<std::string> getResults();

    /**
     * Get the number of results from the last search
     * @return Number of results
     */
    unsigned long getResultCount() const;

    /**
     * Clear the current search
     */
    void reset();

private:
    bool checkError();
    std::string getLastError() const;
};