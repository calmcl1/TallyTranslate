#pragma once
#ifndef TALLYTRANSLATE_H
#define TALLYTRANSLATE_H

#ifdef _WIN32
#include "targetver.h"
// ASIO uses LEAN_AND_MEAN by default, but this causes the BMD API include to fail.
#define BOOST_ASIO_NO_WIN32_LEAN_AND_MEAN
#endif // _WIN32

#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>


int main();

#endif // TALLYTRANSLATE_H