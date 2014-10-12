#ifndef EVENTBASE_H
#define EVENTBASE_H

#include <string>

namespace nedges {

/*!
 * \brief The EventBase class
 *
 * Abstract base interface for defining all kinds of Table Tennis Events.
 * These may include RoundRobin events, Leagues, Multi Event Tournaments etc.
 * An Event must have a start date (and optionally a start time) and a title.
 */

class EventBase
{
public:

    virtual ~EventBase();

    /*!
     * \brief setEventTime
     *        set/modify the Event start date/time independently of the constructor with a string.
     * \param _start_time
     *        A string with the Event date/time
     */

    virtual void setEventTime(std::string const & _start_time)=0;

    /*!
     * \brief setEventTitle
     *          set/modify the Event Title
     * \param _event_title
     *          Non-Null string with event title
     */

    virtual void setEventTitle(std::string const & _event_title)=0;

};

} // namespace nedges


#endif // EVENTBASE_H
