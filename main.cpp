#include "main.h"

int main() {
  size_t len = 1024 * 1024 * 1024;
  std::cout << "Create the 1GB file ..." << std::endl;
  auto path = "/mnt/file";
  auto fd = open(path, O_RDWR | O_CREAT | O_SYNC, 0600);
  if (fd < 0) {
    fprintf(stderr,
            "open(%s): %s\n",
            path,
            strerror(errno));
    return -1;
  }
  char *buf = (char *) malloc(len);
  auto written = write(fd, buf, len);
  free(buf);
  if (written < 0) {
    fprintf(stderr,
            "write(%s): %s , len:%lu\n",
            path,
            strerror(errno),
            len);
    return -1;
  }

  std::cout << "Press enter to continue ..." << std::endl;
  std::cin.get();

  std::cout << "Delete the file ..." << std::endl;
  if (unlink(path) < 0) {
    fprintf(stderr,
            "unlink(%s): %s\n",
            path,
            strerror(errno));
    return -1;
  }
  return 0;
}
