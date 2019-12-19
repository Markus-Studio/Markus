#include "writer/directory.hpp"

#include <assert.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <iostream>

namespace Writer {

// Creates a directory on both POSIX and windows.
bool markus_mkdir(std::string path) {
  mode_t nMode = 0733;
  int nError = 0;

#if defined(_WIN32)
  nError = _mkdir(path.c_str());
#else
  nError = mkdir(path.c_str(), nMode);
#endif

  return nError == 0;
}

// Make sure a path exists, "mkdir -p"
bool markus_mkpath(std::string path) {
  struct stat info;

  char* cPath = strdup(path.c_str());
  char *end, *last;
  last = cPath;
  while (*last)
    last++;
  end = last;

  bool existed = false;
  for (; last != cPath; --last) {
    if (*last != '/' && *last != 0)
      continue;

    *last = 0;

    if (cPath[0] == '.' && cPath[1] == 0) {
      existed = true;
      break;
    }

    if (stat(cPath, &info) == 0) {
      if (info.st_mode & S_IFDIR) {
        existed = true;
        break;
      }

      free(cPath);
      return false;
    }
  }

  if (!existed) {
    if (!markus_mkdir(cPath)) {
      free(cPath);
      return false;
    }
  }

  for (; last != end; ++last) {
    if (*last != 0)
      continue;

    *last = '/';
    if (!markus_mkdir(cPath)) {
      free(cPath);
      return false;
    }
  }

  free(cPath);
  return true;
}

void Directory::bind(std::string path) {
  if (path == fsPath)
    return;

  // Check and see if we're not binded to any directory at the moment.
  assert(fsPath == "");

  const char* cPath = path.c_str();
  struct stat info;

  // Check if twe have access.
  if (!markus_mkpath(path)) {
    std::cout << "Cannot access " << path << std::endl;
    exit(-1);
  }
}
}  // namespace Writer