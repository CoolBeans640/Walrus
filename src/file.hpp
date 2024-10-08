#pragma once
/// @file file.h
/// @brief Utilities for dealing with the filesystem

#include <cstdint>
#include <vector>

/// Check if a path exists (doesn't necessarily mean it's a file)
bool file_exists(const char* path);

/// Check if a path exists and is a file
bool path_is_file(const char* path);

/// Check if a path exists and is a directory
bool path_is_dir(const char* path);

/// @brief Find the size of a file
/// @return Size of the file. A value of 0 could mean the path doesn't exist,
/// or that the file is empty.
uint32_t file_size(const char* path);

/// @brief Read an entire file into a buffer. Caller must free the resource.
/// @param path Filepath
/// @note This allocates memory!
/// @return Pointer to buffer, or NULL on failure.
std::vector<char> file_load(const char* path);

/// @brief Read an entire file into an existing buffer.
/// @param path Filepath
/// @param buf Buffer to read file into
/// @param size Size of buffer
/// @return Returns false if anything goes wrong (can't open file, buffer is
/// NULL, not enough space)
bool file_load_existing(const char* path, char* buf, uint32_t size);
