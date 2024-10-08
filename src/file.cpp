#include <cstdio>

#include <filesystem>
#include <vector>

#include "file.hpp"

std::vector<char> file_load(const char* path) {
    if (!std::filesystem::exists(path)) {
        printf("File \"%s\" doesn't exist.\n", path);
        return std::vector<char>();
    }
    else if (std::filesystem::is_directory(path)) {
        printf("\"%s\" is a directory.\n", path);
        return std::vector<char>();
    }

    const uint32_t size = std::filesystem::file_size(path);
    // Allocate 1 extra byte for a bit of wiggle room
    std::vector<char> buffer(size + 1);

    file_load_existing(path, &buffer[0], size);
    return buffer;
}

bool file_load_existing(const char* path, char* buf, uint32_t size) {
    if (buf == nullptr) {
        printf("Caller gave a NULL buffer. Check your allocations!\n");
        return false;
    }
    if (!std::filesystem::exists(path)) {
        printf("Requested file \"%s\" does not exist.\n", path);
        return false;
    }

    const uint32_t filesize = std::filesystem::file_size(path);
    if (filesize > size) {
        printf("Not enough space for file %s\n", path);
        return false;
    }

    FILE* resource = fopen(path, "rb");
    if (resource == nullptr) {
        return false;
    }

    fread(buf, size, 1, resource);
    fclose(resource);
    return true;
}
