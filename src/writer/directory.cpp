#include "writer/directory.hpp"

#include <assert.h>
#include <stdlib.h>
#include <string.h>
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

std::string join_path(std::string dir, std::string filename) {
  return dir + filename;
}

inline void file_keepSync(std::string dirPath,
                          std::string filename,
                          File* memFile) {
  std::string filePath = join_path(dirPath, filename);
  std::ofstream* file = new std::ofstream();
  file->open(filePath, std::ios::out | std::ios::trunc);
  if (!file->is_open()) {
    std::cerr << "Cannot access " << filePath << std::endl;
    exit(-1);
  }
  memFile->keepSync(file);
}

void Directory::bind(std::string path) {
  if (path == fsPath)
    return;

  // Check and see if we're not binded to any directory at the moment.
  assert(fsPath == "");

  // Check if twe have access.
  if (!markus_mkpath(path)) {
    std::cerr << "Cannot access " << path << std::endl;
    exit(-1);
  }

  std::map<std::string, File*>::iterator filesIter;
  std::map<std::string, Directory*>::iterator dirsIter;
  ;

  for (filesIter = files.begin(); filesIter != files.end(); ++filesIter)
    file_keepSync(path, filesIter->first, filesIter->second);

  for (dirsIter = dirs.begin(); dirsIter != dirs.end(); ++dirsIter) {
    std::string dirPath = join_path(path, filesIter->first);
    dirsIter->second->bind(dirPath);
  }
}

Directory::Directory() {}

Directory::Directory(std::string path) {
  bind(path);
}

File* Directory::createFile(std::string name) {
  assert(!has(name));
  File* file = new File();
  if (!fsPath.empty())
    file_keepSync(fsPath, name, file);
  files.insert(std::pair<std::string, File*>(name, file));
  return file;
}

void Directory::addFile(std::string name, File* file) {
  assert(!has(name));
  if (!fsPath.empty())
    file_keepSync(fsPath, name, file);
  files.insert(std::pair<std::string, File*>(name, file));
}

Directory* Directory::createDirectory(std::string name) {
  assert(!has(name));
  Directory* dir = new Directory();
  if (!fsPath.empty())
    dir->bind(join_path(fsPath, name));
  dirs.insert(std::pair<std::string, Directory*>(name, dir));
  return dir;
}

void Directory::addDirectory(std::string name, Directory* dir) {
  assert(!has(name));
  if (!fsPath.empty())
    dir->bind(join_path(fsPath, name));
  dirs.insert(std::pair<std::string, Directory*>(name, dir));
}

inline bool Directory::has(std::string name) {
  return files.count(name) > 0 || dirs.count(name) > 0;
}

}  // namespace Writer