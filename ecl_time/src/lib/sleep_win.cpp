/**
 * @file /src/lib/sleep_win.cpp
 *
 * @brief Implementation of the sleep classes.
 *
 * @date April 2013
 **/
/*****************************************************************************
** Platform Check
*****************************************************************************/

#include <ecl/config.hpp>
#if defined(ECL_IS_WIN32)

/*****************************************************************************
** Includes
*****************************************************************************/

#include <ecl/errors/macros.hpp>
#include "../../include/ecl/time/duration.hpp"
#include "../../include/ecl/time/sleep_win.hpp"

#include <iostream>
#include <ecl/time_lite/functions.hpp>

/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace ecl {

/*****************************************************************************
** Implementation [Sleep]
*****************************************************************************/
Sleep::Sleep(const Duration &duration) {
	required.tv_sec = duration.sec();
	required.tv_nsec = duration.nsec();
}

Sleep::Sleep(const unsigned long &seconds) {
	required.tv_sec = seconds;
	required.tv_nsec = 0;
}

void Sleep::operator ()() ecl_assert_throw_decl(StandardException) {
    TimeError result = sleep(required);
#ifdef _WIN32
	ecl_assert_throw( result.Equals(TimeError(NoError)), time::throwSleepException(LOC) );
#else
	ecl_assert_throw(result == TimeError(NoError), time::throwSleepException(LOC));
#endif
}

void Sleep::operator ()(const Duration &duration) ecl_assert_throw_decl(StandardException) {
	required.tv_sec = duration.sec();
	required.tv_nsec = duration.nsec();
	TimeError result = sleep(required);
#ifdef _WIN32
	ecl_assert_throw(result.Equals(TimeError(NoError)), time::throwSleepException(LOC));
#else
	ecl_assert_throw(result == TimeError(NoError), time::throwSleepException(LOC));
#endif
}

void Sleep::operator ()(const unsigned long &seconds) ecl_assert_throw_decl(StandardException) {
	required.tv_sec = seconds;
	required.tv_nsec = 0;
	TimeError result = sleep(required);
#ifdef _WIN32
	ecl_assert_throw(result.Equals(TimeError(NoError)), time::throwSleepException(LOC));
#else
	ecl_assert_throw(result == TimeError(NoError), time::throwSleepException(LOC));
#endif
}

/*****************************************************************************
** Implementation [MilliSleep]
*****************************************************************************/

MilliSleep::MilliSleep(const unsigned long &milliseconds) {
	required.tv_sec = milliseconds/1000; // integer division
	required.tv_nsec = (milliseconds%1000)*1000000;
}

void MilliSleep::operator ()() ecl_assert_throw_decl(StandardException) {
	TimeError result = sleep(required);
#ifdef _WIN32
	ecl_assert_throw(result.Equals(TimeError(NoError)), time::throwSleepException(LOC));
#else
	ecl_assert_throw(result == TimeError(NoError), time::throwSleepException(LOC));
#endif
}

void MilliSleep::operator ()(const unsigned long &milliseconds) ecl_assert_throw_decl(StandardException) {
	required.tv_sec = milliseconds/1000; // integer division
	required.tv_nsec = (milliseconds%1000)*1000000;
//    required.tv_nsec = 1000000*milli_seconds;
	TimeError result = sleep(required);
#ifdef _WIN32
	ecl_assert_throw(result.Equals(TimeError(NoError)), time::throwSleepException(LOC));
#else
	ecl_assert_throw(result == TimeError(NoError), time::throwSleepException(LOC));
#endif
}

/*****************************************************************************
** Implementation [MicroSleep]
*****************************************************************************/

MicroSleep::MicroSleep(const unsigned long &microseconds) {
	required.tv_sec = microseconds/1000000; // integer division
	required.tv_nsec = (microseconds%1000000)*1000;
}

void MicroSleep::operator ()() ecl_assert_throw_decl(StandardException) {
	TimeError result = sleep(required);
#ifdef _WIN32
	ecl_assert_throw(result.Equals(TimeError(NoError)), time::throwSleepException(LOC));
#else
	ecl_assert_throw(result == TimeError(NoError), time::throwSleepException(LOC));
#endif
}

void MicroSleep::operator ()(const unsigned long &micro_seconds) ecl_assert_throw_decl(StandardException) {
    required.tv_nsec = 1000*micro_seconds;
    TimeError result = sleep(required);
#ifdef _WIN32
	ecl_assert_throw(result.Equals(TimeError(NoError)), time::throwSleepException(LOC));
#else
	ecl_assert_throw(result == TimeError(NoError), time::throwSleepException(LOC));
#endif
}

/*****************************************************************************
** Implementation [NanoSleep]
*****************************************************************************/

NanoSleep::NanoSleep(const unsigned long &nanoseconds) {
	required.tv_sec = nanoseconds/1000000000; // integer division
	required.tv_nsec = nanoseconds%1000000000;
}

void NanoSleep::operator ()() ecl_assert_throw_decl(StandardException) {
	TimeError result = sleep(required);
#ifdef _WIN32
	ecl_assert_throw(result.Equals(TimeError(NoError)), time::throwSleepException(LOC));
#else
	ecl_assert_throw(result == TimeError(NoError), time::throwSleepException(LOC));
#endif
}

void NanoSleep::operator ()(const unsigned long &nanoseconds) ecl_assert_throw_decl(StandardException) {
    required.tv_nsec = nanoseconds;
    TimeError result = sleep(required);
#ifdef _WIN32
	ecl_assert_throw(result.Equals(TimeError(NoError)), time::throwSleepException(LOC));
#else
	ecl_assert_throw(result == TimeError(NoError), time::throwSleepException(LOC));
#endif
}

} // namespace ecl

#endif /* ECL_IS_WIN32 */

