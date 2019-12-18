#ifndef __MARKUS_WRITER_FILE__
#define __MARKUS_WRITER_FILE__

#include <fstream>
#include <sstream>
#include <string>
#include <vector>

namespace Writer {
/**
 * A file is a writable stream.
 */
class File {
 private:
  /**
   * The in memory representation of the file.
   */
  std::stringstream inMemory;

  /**
   * File streams that are synced with this file.
   */
  std::vector<std::ofstream> files;

  /**
   * Links this file against a real file on disk with the given path.
   */
  void addPath(std::string path);

  /**
   * Whatever this file is closed or not.
   */
  bool closed;

 public:
  /**
   * Writes the current content of this file into the given stream.
   */
  void writeTo(std::stringstream& stream);

  /**
   * Writes the current content of this file into the given file stream.
   */
  void writeTo(std::ofstream& stream);

  /**
   * Writes the current content of this file into the given file stream.
   */
  void writeTo(File& file);

  /**
   * Returns the currnet content of the file in form of a string.
   */
  std::string str();

  /**
   * Close the file.
   */
  void close();

  /**
   * Write the given data into this file.
   */
  void operator<<(std::string data);

  /**
   * Read the data from the given string stream.
   */
  void operator<<(std::stringstream& stream);

  /**
   * Write the given buffer into this file.
   */
  void operator<<(std::stringbuf* buf);

  /**
   * Write the given number to the data.
   */
  void operator<<(int number);

  friend class Directory;
};
}  // namespace Writer

#endif