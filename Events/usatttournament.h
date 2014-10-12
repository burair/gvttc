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
#ifndef USATTTOURNAMENT_H
#define USATTTOURNAMENT_H

#include <vector>
#include "boost/shared_ptr.hpp"
#include "event.h"
#include "boost/date_time/gregorian/gregorian.hpp"
#include "boost/date_time/posix_time/posix_time.hpp"
#include "Players/player.h"

namespace nedges {

/*!
 * \brief The USATTournament class
 *
 * based on the USATT Tournament Guide
 * v.2014 available at:
 * http://www.teamusa.org/~/media/USA_Table_Tennis/Documents/Tournament%20Guide/2014/CH%2013%20-%20Tournament%20Reports.pdf
 */
class USATTTournament : public Event
{
    /*!
     * \brief EventPtr
     */
    typedef boost::shared_ptr<Event> EventPtr;
    /*!
     * \brief PlayerPtr
     */
    typedef boost::shared_ptr<Player> PlayerPtr;
    /*!
     * \brief EventListType
     */
    typedef std::vector<EventPtr> EventListType;
    /*!
     * \brief PlayerListType
     */
    typedef std::vector<PlayerPtr> PlayerListType;
    /*!
     * \brief EventPlayerListType
     */
    typedef std::pair<EventPtr,PlayerListType> EventPlayerListType;
    /*!
     * \brief ArrayOfEventPlayerListType
     */
    typedef std::vector<EventPlayerListType> EventsPlayerListType;

public:
    USATTTournament(std::string _name="", std::string _date="",std::string _club="",std::string _city="",
               std::string _state="", std::string _zipcode="", std::string _director="",
               std::string _contact_phone="",std::string _director_city="", std::string _director_state="",
               std::string _director_zipcode="");


    /*!
     * Setters
     */


    /*!
     * \brief setClub
     * \param _club
     */
    void setClub(const std::string & _club) {
        club=_club;
        return;
    }
    /*!
     * \brief setCity
     * \param _city
     */
    void setCity(const std::string & _city) {
        city=_city;
        return;
    }
    /*!
     * \brief setState
     * \param _state
     */
    void setState(const std::string & _state) {
        state=_state;
        return;
    }
    /*!
     * \brief setZipcode
     * \param _zipcode
     */
    void setZipcode(const std::string & _zipcode) {
        zipcode=_zipcode;
        return;
    }
    /*!
     * \brief setDirectorName
     * \param _director_name
     */
    void setDirectorName(const std::string & _director_name) {
        director_name=_director_name;
        return;
    }
    /*!
     * \brief setDirectorContactPhone
     * \param _director_contact_phone
     */
    void setDirectorContactPhone(const std::string & _director_contact_phone) {
        director_contact_phone=_director_contact_phone;
        return;
    }
    /*!
     * \brief setDirectorCity
     * \param _director_city
     */
    void setDirectorCity(const std::string & _director_city) {
        director_city=_director_city;
        return;
    }
    /*!
     * \brief setDirectorState
     * \param _director_state
     */
    void setDirectorState(const std::string & _director_state) {
        director_state=_director_state;
        return;
    }
    /*!
     * \brief setDirectorZipcode
     * \param _director_zipcode
     */
    void setDirectorZipcode(const std::string & _director_zipcode) {
        director_zipcode=_director_zipcode;
        return;
    }


    /*!
     * Getters
     */

    /*!
     * \brief getName
     * \return
     */
    std::string const & getName() const {
        return name;
    }

    /*!
     * \brief getDate
     * \return
     */
    boost::gregorian::date const & getDate() const {
        return date;
    }

    /*!
     * \brief getClub
     * \return
     */
    std::string const & getClub() const {
        return club;
    }
    /*!
     * \brief getCity
     * \return
     */
    std::string const & getCity() const {
        return city;
    }
    /*!
     * \brief getState
     * \return
     */
    std::string const & getState() const {
        return state;
    }
    /*!
     * \brief getZipcode
     * \return
     */
    std::string const & getZipcode() const {
        return zipcode;
    }
    /*!
     * \brief getDirectorName
     * \return
     */
    std::string const & getDirectorName() const {
        return director_name;
    }
    /*!
     * \brief getDirectorContactPhone
     * \return
     */
    std::string const & getDirectorContactPhone() const {
        return director_contact_phone;
    }
    /*!
     * \brief getDirectorCity
     * \return
     */
    std::string const & getDirectorCity() const {
        return director_city;
    }
    /*!
     * \brief getDirectorState
     * \return
     */
    std::string const & getDirectorState() const {
        return director_state;
    }
    /*!
     * \brief getDirectorZipcode
     * \return
     */
    std::string const & getDirectorZipcode() const {
        return director_zipcode;
    }

private:
    /*!
     * \brief name
     *
     * Full Name of Event e.g. "GVTTC Round Robin 2014"
     */
    std::string name;
    /*!
     * \brief date
     *
     * Tournament Start Date
     */
    boost::gregorian::date date;
    /*!
     * \brief event_dates
     *
     * An array of dates the events in the tournament take place
     */
    std::vector<boost::gregorian::date> event_dates;
    /*!
     * \brief club
     *
     * Tournament sponsoring club
     */
    std::string club;
    /*!
     * \brief city
     *
     * City Tournament is being held
     */
    std::string city;
    /*!
     * \brief state
     *
     * State Tournament is being held
     */
    std::string state;
    /*!
     * \brief zipcode
     *
     * Zipcode of tournament location
     */
    std::string zipcode;
    /*!
     * \brief director_name
     *
     * Full Name of Director e.g. "Raymond Mack"
     */
    std::string director_name;
    /*!
     * \brief director_contact_phone
     *
     * Director contact phone
     */
    std::string director_contact_phone;
    /*!
     * \brief director_city
     *
     * Director city
     */
    std::string director_city;
    /*!
     * \brief director_state
     *
     * Director state
     */
    std::string director_state;
    /*!
     * \brief director_zipcode
     *
     * Director Zipcode
     */
    std::string director_zipcode;
    /*!
     * \brief event_list
     *
     * An array of pointers to the events this tournament will contain
     */
    EventListType event_list;
    /*!
     * \brief player_list
     *
     * An array of pointers to the players attending the tournament
     */
     PlayerListType player_list;
    /*!
     * \brief events_players_list
     *
     * An array containing a list of events paired with the player list associated with each event
    */
    EventsPlayerListType events_players_list;

};
} //namespace nedges
#endif // USATTEVENT_H
