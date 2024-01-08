#include <stdarg.h>
#include <sys/time.h>
#include <time.h>
#include <fstream>
#include <iostream>

using namespace std;

/**
 * @brief 可变参数的传入
 *
 * @param buf
 * @param format
 * @param ...
 */
void format_t(char buf[], char format[], ...) {
  struct timeval now = {0, 0};
  gettimeofday(&now, NULL);
  time_t t = now.tv_sec;
  struct tm* sys_tm = localtime(&t);
  struct tm my_tm = *sys_tm;

  va_list valst;
  va_start(valst, format);

  int n = snprintf(buf, 48, "%d-%02d-%02d %02d:%02d:%02d.%06d %s ", my_tm.tm_year + 1900, my_tm.tm_mon + 1,
                   my_tm.tm_mday, my_tm.tm_hour, my_tm.tm_min, my_tm.tm_sec, now.tv_usec, "[debug]");
  int m = vsnprintf(buf + n, 1024, format, valst);
  buf[n + m] = '\n';
  buf[n + m + 1] = '\0';
  printf("%s", buf);
}

int main(int argc, char const* argv[]) {
  char output[1024];
  format_t(output, "Your format string here: %s %s", "Hello", "World");
  return 0;
}
