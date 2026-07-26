#include "timer_session.h"
#include "bnf.h"
#include <ctime>
#include <chrono>

using namespace std::chrono;

TimerSession::TimerSession(boost::asio::io_context& io_service)
    : SessionBase(io_service, SessionBase::TIMER_SESSION)
    , timer_(io_service)
{
    running_ = true;
    bnf::instance()->timer_session_seq_.pop(handle_);
}

TimerSession::~TimerSession()
{
    bnf::instance()->timer_session_seq_.push(handle_);
}

void TimerSession::Close()
{
    boost::asio::post(io_service_,
        [this]()
        {
            Stop();
        });
}

void TimerSession::Stop()
{
    timer_.cancel();
    running_ = false;
}

//////////////////////////////////////////////////////////////////////////
// MSecTimerSession
MSecTimerSession::MSecTimerSession(boost::asio::io_context& io_service, int start_msec, int period_msec)
    : TimerSession(io_service)
{
    millisecond_ = period_msec;

    timer_.expires_after(milliseconds(start_msec));
    timer_.async_wait([this](const boost::system::error_code& ec)
        {
            handle_process(ec);
        });

    LOG_INFO("bnf - create timer. handle: %X, start_msec: %d, period_msec: %d",
        handle_, start_msec, period_msec);
}

MSecTimerSession::~MSecTimerSession()
{
    LOG_INFO("bnf - delete timer. handle: %X", handle_);
}

void MSecTimerSession::handle_process(const boost::system::error_code& error)
{
    if (error || running_ == false)
    {
        delete this;
        return;
    }

    bnf::instance()->PutSessionEvent(SessionEvent::ON_TIMER, this);

    timer_.expires_after(milliseconds(millisecond_));
    timer_.async_wait([this](const boost::system::error_code& ec)
        {
            handle_process(ec);
        });
}

//////////////////////////////////////////////////////////////////////////
// SecTimerSession
SecTimerSession::SecTimerSession(boost::asio::io_context& io_service, int start_sec, int period_sec)
    : TimerSession(io_service)
{
    second_ = period_sec;

    timer_.expires_after(seconds(start_sec));
    timer_.async_wait([this](const boost::system::error_code& ec)
        {
            handle_process(ec);
        });

    LOG_INFO("bnf - create timer. handle: %X, start_sec: %d, period_sec: %d",
        handle_, start_sec, period_sec);
}

SecTimerSession::~SecTimerSession()
{
    LOG_INFO("bnf - delete timer. handle: %X", handle_);
}

void SecTimerSession::handle_process(const boost::system::error_code& error)
{
    if (error || running_ == false)
    {
        delete this;
        return;
    }

    bnf::instance()->PutSessionEvent(SessionEvent::ON_TIMER, this);

    timer_.expires_after(seconds(second_));
    timer_.async_wait([this](const boost::system::error_code& ec)
        {
            handle_process(ec);
        });
}

//////////////////////////////////////////////////////////////////////////
// AbsoluteTimerSession
//
// Old code used deadline_timer + posix_time absolute (system clock).
// New code uses steady_timer absolute scheduling (monotonic).
// Semantics: first fires after start_sec, then every period_sec, without drift.
AbsoluteTimerSession::AbsoluteTimerSession(boost::asio::io_context& io_service, int start_sec, int period_sec)
    : TimerSession(io_service)
{
    second_ = period_sec;

    // schedule first tick at now + start_sec, then tick_ += period
    next_tick_ = boost::asio::steady_timer::clock_type::now() + seconds(start_sec);

    timer_.expires_at(next_tick_);
    timer_.async_wait([this](const boost::system::error_code& ec)
        {
            handle_process(ec);
        });

    LOG_INFO("bnf - create timer. handle: %X, start_sec: %d, period_sec: %d",
        handle_, start_sec, period_sec);
}

AbsoluteTimerSession::~AbsoluteTimerSession()
{
    LOG_INFO("bnf - delete timer. handle: %X", handle_);
}

void AbsoluteTimerSession::handle_process(const boost::system::error_code& error)
{
    if (error || running_ == false)
    {
        delete this;
        return;
    }

    bnf::instance()->PutSessionEvent(SessionEvent::ON_TIMER, this);

    // move to next slot (prevents drift)
    next_tick_ += seconds(second_);

    timer_.expires_at(next_tick_);
    timer_.async_wait([this](const boost::system::error_code& ec)
        {
            handle_process(ec);
        });
}
