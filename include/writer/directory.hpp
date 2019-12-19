#ifndef __MARKUS_WRITER_DIRECTORY__
#define __MARKUS_WRITER_DIRECTORY__

#include <map>
#include <string>

#include "writer/file.hpp"

namespace Writer {
/**
 * A directory contains a set of files or another directories.
 */
class Directory {
 private:
  /**
   * Path of the current directory in the real file system.
   */
  std::string fsPath;

  /**
   * Bind this directory to the file system.
   */
  void bind(std::string path);

  /**
   * Map of all the files in the current directory.
   */
  std::map<std::string, File*> files;

  /**
   * Directories in the current directory.
   */
  std::map<std::string, Directory*> dirs;

  /**
   * Whatever the current directory is closed or not.
   */
  bool closed;

 public:
  /**
   * Creates a new in memory directory.
   */
  Directory();

  /**
   * Creates a new directory that is mapped to the file system.
   */
  Directory(std::string path);

  /**
   * Create a new file with the given name in this directory.
   */
  File* createFile(std::string name);

  /**
   * Add the given file to this directory.
   */
  void addFile(std::string name, File* file);

  /**
   * Creates a new directory inside the current directory, returns the created
   * directory.
   */
  Directory* createDirectory(std::string name);

  /**
   * Adds the given **in memory** directory to this dir.
   */
  void addDirectory(std::string name, Directory* dir);

  /**
   * Returns whatever the given name exists in this directory.
   */
  bool has(std::string name);

  /**
   * Close the current directory.
   */
  void close();
};
}  // namespace Writer

#endif