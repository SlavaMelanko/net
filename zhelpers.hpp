#ifndef __ZHELPERS_HPP_INCLUDED__
#define __ZHELPERS_HPP_INCLUDED__

//  Include a bunch of headers that we will need in the examples

#include <zmq.hpp> // https://github.com/zeromq/cppzmq

#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

#include <assert.h>
#include <signal.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h> // random()  RAND_MAX
#include <time.h>
#if (!defined(WIN32))
#include <sys/time.h>
#include <unistd.h>
#endif

//  Bring Windows MSVC up to C99 scratch
#if (defined(WIN32))
typedef unsigned long ulong;
typedef unsigned int uint;
typedef __int64 int64_t;
#endif

//  On some version of Windows, POSIX subsystem is not installed by default.
//  So define srandom and random ourself.
//
#if (defined(WIN32))
#define srandom srand
#define random rand
#endif

//  Provide random number from 0..(num-1)
#define within(num) (int)((float)((num)*random()) / (RAND_MAX + 1.0))

//  Receive 0MQ string from socket and convert into string
inline static std::string s_recv(zmq::socket_t& socket,
                                 zmq::recv_flags flags = zmq::recv_flags::none)
{
  zmq::recv_result_t rc;
  zmq::message_t message;
  rc = socket.recv(message, flags);

  return std::string(static_cast<char*>(message.data()), message.size());
}

//  Convert string to 0MQ string and send to socket
inline static bool s_send(zmq::socket_t& socket,
                          const std::string& string,
                          zmq::send_flags flags = zmq::send_flags::none)
{
  zmq::message_t message(string.size());
  memcpy(message.data(), string.data(), string.size());

  auto rc = socket.send(message, flags);
  return (rc.value() > 0);
}

//  Sends string as 0MQ string, as multipart non-terminal
inline static bool s_sendmore(zmq::socket_t& socket, const std::string& string)
{
  zmq::message_t message(string.size());
  memcpy(message.data(), string.data(), string.size());

  auto rc = socket.send(message, zmq::send_flags::sndmore);
  return (rc.value());
}

//  Receives all message parts from socket, prints neatly
inline static void s_dump(zmq::socket_t& socket)
{
  std::cout << "----------------------------------------" << std::endl;

  while (1) {
    //  Process all parts of the message
    zmq::recv_result_t rc;
    zmq::message_t message;
    rc = socket.recv(message, zmq::recv_flags::none);

    //  Dump the message as text or binary
    size_t size = message.size();
    std::string data(static_cast<char*>(message.data()), size);

    bool is_text = true;

    size_t char_nbr;
    unsigned char byte;
    for (char_nbr = 0; char_nbr < size; char_nbr++) {
      byte = data[char_nbr];
      if (byte < 32 || byte > 127)
        is_text = false;
    }
    std::cout << "[" << std::setfill('0') << std::setw(3) << size << "]";
    for (char_nbr = 0; char_nbr < size; char_nbr++) {
      if (is_text)
        std::cout << (char)data[char_nbr];
      else
        std::cout << std::setfill('0') << std::setw(2) << std::hex << (unsigned int)data[char_nbr];
    }
    std::cout << std::endl;

    int more = 0; //  Multipart detection
    size_t more_size = sizeof(more);
    socket.getsockopt(ZMQ_RCVMORE, &more, &more_size);
    if (!more)
      break; //  Last message part
  }
}

//  Report 0MQ version number
inline static std::string s_version()
{
  int major, minor, patch;
  zmq_version(&major, &minor, &patch);

  std::string version = std::to_string(major);
  version += ".";
  version += std::to_string(minor);
  version += ".";
  version += std::to_string(patch);

  return version;
}

inline static void s_version_assert(int want_major, int want_minor)
{
  int major, minor, patch;
  zmq_version(&major, &minor, &patch);
  if (major < want_major || (major == want_major && minor < want_minor)) {
    std::cout << "Current 0MQ version is " << major << "." << minor << std::endl;
    std::cout << "Application needs at least " << want_major << "." << want_minor
              << " - cannot continue" << std::endl;
    exit(EXIT_FAILURE);
  }
}

//  Return current system clock as milliseconds
inline static int64_t s_clock(void)
{
#if (defined(WIN32))
  FILETIME fileTime;
  GetSystemTimeAsFileTime(&fileTime);
  unsigned __int64 largeInt = fileTime.dwHighDateTime;
  largeInt <<= 32;
  largeInt |= fileTime.dwLowDateTime;
  largeInt /= 10000; // FILETIME is in units of 100 nanoseconds
  return (int64_t)largeInt;
#else
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return (int64_t)(tv.tv_sec * 1000 + tv.tv_usec / 1000);
#endif
}

//  Sleep for a number of milliseconds
inline static void s_sleep(int msecs)
{
#if (defined(WIN32))
  Sleep(msecs);
#else
  struct timespec t;
  t.tv_sec = msecs / 1000;
  t.tv_nsec = (msecs % 1000) * 1000000;
  nanosleep(&t, NULL);
#endif
}

inline static void s_console(const char* format, ...)
{
  time_t curtime = time(NULL);
  struct tm* loctime = localtime(&curtime);
  char* formatted = new char[20];
  strftime(formatted, 20, "%y-%m-%d %H:%M:%S ", loctime);
  printf("%s", formatted);
  delete[] formatted;

  va_list argptr;
  va_start(argptr, format);
  vprintf(format, argptr);
  va_end(argptr);
  printf("\n");
}

#endif
