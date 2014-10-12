/*!************************************************************************
 *   This file is part of Nedges.                                         *
 *   A table tennis club, league and tournament management package.       *
 *                                                                        *
 *   "May your game be full of nedges (Nets and Edges).                   *
 *                                                -- Ray Mack             *
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
