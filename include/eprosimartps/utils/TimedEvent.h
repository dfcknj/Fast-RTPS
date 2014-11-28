/*************************************************************************
 * Copyright (c) 2014 eProsima. All rights reserved.
 *
 * This copy of eProsima RTPS is licensed to you under the terms described in the
 * EPROSIMARTPS_LIBRARY_LICENSE file included in this distribution.
 *
 *************************************************************************/

/**
 * @file TimedEvent.h
 *
 */



#ifndef PERIODICEVENT_H_
#define PERIODICEVENT_H_


//#define BOOST_ASIO_DYN_LINK

#include <boost/asio/deadline_timer.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/system/error_code.hpp>
#include <boost/asio/placeholders.hpp>
#include <boost/asio/io_service.hpp>
#include <boost/bind.hpp>
#include <boost/interprocess/sync/interprocess_semaphore.hpp>

#include "eprosimartps/common/types/Time_t.h"



namespace eprosima {
namespace rtps{

/**
 * Timed Event class used to define any timed events.
 * All timedEvents must be a specification of this class, implementing the event method.
 * @ingroup MANAGEMENTMODULE
 */
class TimedEvent {
public:
	virtual ~TimedEvent(){};
	//! A io_service must be provided as well as the interval of the timedEvent.
	TimedEvent(boost::asio::io_service* serv,boost::posix_time::milliseconds interval);
	//! Pure abstract virtual method used to perform the event.
	virtual void event(const boost::system::error_code& ec)=0;


protected:
	//!Pointer to the timer.
	boost::asio::deadline_timer* timer;
	//!Interval to be used in the timed Event.
	boost::posix_time::milliseconds m_interval_msec;
public:
	bool m_isWaiting;
	//!Method to restart the timer.
	void restart_timer();
	//! TO update the interval, the timer is not restarted and the new interval will onyl be used the next time you call restart_timer().
	bool update_interval(const Duration_t& time);
	bool update_interval_millisec(int64_t time_millisec);
	//!Stop the timer
	void stop_timer();

	const boost::posix_time::milliseconds& getIntervalMsec() const {
		return m_interval_msec;
	}

	double getRemainingTimeMilliSec()
	{
		return (double)timer->expires_from_now().total_milliseconds();
	}
	//Duration_t m_timeInfinite;
	//!Semaphore to wait for the listen thread creation.
	boost::interprocess::interprocess_semaphore* mp_stopSemaphore;
};




}
} /* namespace eprosima */

#endif /* PERIODICEVENT_H_ */