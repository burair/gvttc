/*!************************************************************************
 *   This file is part of Nedges.                                         *
 *   A table tennis club, league and tournament management package.       *
 *                                                                        *
 *   "Wish you LOTS of nedges (Nets and Edges)!!."                        *
 *                                          -- Wayne Carney, Ray Mack     *
 *   Author: Burair Kothari 2014                                          *
 *                Genesee Valley Table Tennis CLub 2014                   *
 *                http://www.gvttc.com                                    *
 *                                                                        *
 *                                                                        *
 *   Nedges is free software: you can redistribute it and/or modify       *
 *   it under the terms of the GNU General Public License as published by *
 *   the Free Software Foundation, either version 3 of the License, or    *
 *   (at your option) any later version.                                  *
 *                                                                        *
 *   Nedges is distributed in the hope that it will be useful,            *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of       *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the        *
 *   GNU General Public License for more details.                         *
 *                                                                        *
 *   You should have received a copy of the GNU General Public License    *
 *   along with Nedges.  If not, see <http://www.gnu.org/licenses/>.      *
 *                                                                        *
 **************************************************************************/
#ifndef NEDGES_EVENT_H
#define NEDGES_EVENT_H

#include <string>
#include "boost/date_time/posix_time/posix_time.hpp"
#include "boost/date_time/gregorian/gregorian.hpp"

namespace nedges {

typedef boost::gregorian::date Date;

/*!
 * \brief The Event class
 *
 * Base interface for defining all kinds of Table Tennis Events.
 * These may include RoundRobin events, Leagues, Multi Event Tournaments etc.
 * An Event must have a start date (and optionally a start time) and a title.
 * This class implements the virtual functions in EventBase
 */

class Event
{
public:

    virtual ~Event();

    /*!
     * \brief setEventTime
     *        set/modify the Event start date/time independently of the constructor with a string.
     * \param _start_time
     *        A string with the Event date/time
     */

    void setEventTime(std::string const & _start_time) {
        boost::posix_time::ptime time = boost::posix_time::time_from_string(_start_time);
        date = time.date();
        return;
    }

    /*!
     * \brief setEventTitle
     *          set/modify the Event Title
     * \param _event_title
     *          Non-Null string with event title
     */


    void setEventTitle(const std::string & _event_title) {
        setName(_event_title);
        return;
    }
    /*!
     * \brief setName
     * \param _name
     */
    void setName(const std::string & _name) {
        name=_name;
        return;
    }
private:
    Date date;
    std::string name;
};



} // namespace nedges
#endif // NEDGES_EVENT_H
