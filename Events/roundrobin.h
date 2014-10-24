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
#ifndef ROUNDROBIN_H
#define ROUNDROBIN_H

#include "boost/shared_ptr.hpp"
#include "boost/make_shared.hpp"
#include "boost/date_time/posix_time/posix_time.hpp"
#include <vector>
#include <string>
#include "Participants/player.h"
#include "event.h"

namespace nedges {

typedef std::vector<std::pair<int,int> > RRMatchupList;
typedef RRMatchupList::iterator RRMatchupListIt;
typedef RRMatchupList::const_iterator RRMatchupListCIt;
typedef std::vector<std::pair<int,RRMatchupList> > RRSchedule;
typedef RRSchedule::iterator RRScheduleIt;
typedef RRSchedule::const_iterator RRScheduleCIt;

class RoundRobin : public Event
{
    /*!
     * \brief PlayerPtr
     */
    typedef boost::shared_ptr<Player> PlayerPtr;
    /*!
     * \brief PlayerListType
     */
    typedef std::vector<PlayerPtr> PlayerListType;
    typedef boost::shared_ptr<PlayerListType> PlayerListPtrType;

public:
    /*!
     * \brief RoundRobin
     * \param _name
     * \param date
     * \param _player_list
     */
    RoundRobin(std::string _name="", std::string date="", PlayerListPtrType _player_list=boost::make_shared<PlayerListType>());

    /*!
     * \brief AddPlayer
     * \param _player
     */
    void AddPlayer(PlayerPtr _player);

    /*!
     * \brief getPlayerList
     * \return
     */
    PlayerListType & getPlayerList() const;


private:
    /*!
     * \brief player_list
     */
    PlayerListType player_list;

}; //class RoundRobin

void ScheduleRoundRobin(int num_participants, int num_venues);

int MatchesInRoundRobin(int num_participants);

int PossibleMatchups( RRMatchupList & rr_matchups, int num_participants);

void ConstructStandardRoundRobinSchedule(RRSchedule & rr_sched, int num_participants, int num_venues);

void ConstructStandardRoundRobinTournament(RRSchedule & rr_sched, int num_participants);

bool BalanceStandardRoundRobinTournament(RRSchedule & rr_sched);

bool IsBalancedStandardRoundRobinTournament (RRSchedule const & rr_sched);

bool ReOrderRoundRobinRows(RRSchedule const & rr_sched);

void ExchangeElementsForBalance(RRSchedule const & rr_sched);

bool ValidStandardRoundRobinTournament(RRSchedule const & rr_sched);

bool CheckRoundRobinRow(RRMatchupList const & rr_mlist);

bool ValidRoundRobinSchedule(RRSchedule const & rr_sched);

}
#endif // ROUNDROBIN_H
