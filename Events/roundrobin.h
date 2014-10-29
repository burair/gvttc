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
  typedef std::pair<int,int> RRMatch;
  typedef std::vector<RRMatch> RRMatchupList;
  typedef RRMatchupList::iterator RRMatchupListIt;
  typedef RRMatchupList::const_iterator RRMatchupListCIt;
  typedef std::vector<std::pair<int,RRMatchupList> > RRSchedule;
  typedef RRSchedule::iterator RRScheduleIt;
  typedef RRSchedule::const_iterator RRScheduleCIt;


  typedef std::pair<int,int> ModElement;
  typedef std::pair< ModElement, ModElement> ModMatch;
  typedef std::vector<ModMatch> ModMatchList;
  typedef std::pair<int, ModMatchList> ModRound;
  typedef std::vector<ModRound> ModSched;
  typedef ModMatchList::iterator ModMatchListIt;
  typedef ModMatchList::const_iterator ModMatchListCIt;
  typedef ModSched::iterator ModSchedIt;
  typedef ModSched::const_iterator ModSchedCIt;

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

  /*!
   * \brief ScheduleRoundRobin
   * \param num_participants
   * \param num_venues
   */
  void ScheduleRoundRobin(int num_participants, int num_venues);

  /*!
   * \brief MatchesInRoundRobin
   * \param num_participants
   * \return
   */
  int MatchesInRoundRobin(int num_participants);

  /*!
   * \brief PossibleMatchups
   * \param rr_matchups
   * \param num_participants
   * \return
   */
  int PossibleMatchups( RRMatchupList & rr_matchups, int num_participants);

  /*!
   * \brief ConstructStandardRoundRobinSchedule
   * \param rr_sched
   * \param num_participants
   * \param num_venues
   * \param num_rounds
   */
  void ConstructStandardRoundRobinSchedule(RRSchedule & rr_sched, int num_participants, int num_venues, int num_rounds);

  /*!
   * \brief ConstructStandardRoundRobinTournament
   * \param rr_sched
   * \param num_participants
   */
  void ConstructStandardRoundRobinTournament(RRSchedule & rr_sched, int num_participants);

  /*!
   * \brief CounstructFactoredBalancedRoundRobinTournment
   * \param rr_sched
   * \param num_participants
   */
  void CounstructFactoredBalancedRoundRobinTournment(RRSchedule & rr_sched, int num_participants);

  /*!
   * \brief ConstructFactoredBalancedRoundRobinTournament2n
   * \param rr_sched
   * \param num_participants
   */
  void ConstructFactoredBalancedRoundRobinTournament2n(RRSchedule & rr_sched, int num_participants);


  void ConstructFactoredBalancedRoundRobinTournament2x2kplus1(RRSchedule & rr_sched, int num_participants);

  void FixRowsEFBTD(ModSched & mrs, int k);

  void FindCosetSets(ModSched const & mrs, int k, int i, ModMatchList const & ml);

  int FindPeriod(int k, int i);

  void ConstructRowsEFBTD(ModSched & mrs, int n, int k);

  void ConstructColumn1EFBTD(ModSched & mrs, int n, int k);

  void DisplayModSchedule(ModSched const & mrs);

  void InitializeRoundEFBTD(ModRound & R, int round,  ModElement & M11, ModElement & M12);

  /*!
   * \brief BalanceStandardRoundRobinTournamentHaselgroveLeech
   * \param rr_sched
   * \return
   */


  bool BalanceStandardRoundRobinTournamentHaselgroveLeech(RRSchedule & rr_sched);

  /*!
   * \brief IsBalancedStandardRoundRobinTournament
   * \param rr_sched
   * \return
   */
  bool IsBalancedStandardRoundRobinTournament (RRSchedule const & rr_sched);

  /*!
   * \brief ReOrderRoundRobinRows
   * \param rr_sched
   * \return
   */
  bool ReOrderRoundRobinRows(RRSchedule & rr_sched);

  /*!
   * \brief ExchangeElementsForBalanceHaselgroveLeech
   * \param rr_sched
   */
  void ExchangeElementsForBalanceHaselgroveLeech(RRSchedule &rr_sched);

  /*!
   * \brief ExchangeElements
   * \param fm
   * \param sm
   */
  void ExchangeElements(RRMatch & fm, RRMatch & sm );

  /*!
   * \brief GetNumberOfRoundsInRoundRobinSchedule
   * \param rr_sched
   * \return
   */
  int GetNumberOfRoundsInRoundRobinSchedule(RRSchedule const & rr_sched);

  /*!
   * \brief GetNumberOfVenuesInRoundRobinSchedule
   * \param rr_sched
   * \return
   */
  int GetNumberOfVenuesInRoundRobinSchedule(RRSchedule const & rr_sched);

  /*!
   * \brief GetNumberOfParticipantssInRoundRobinSchedule
   * \param rr_sched
   * \return
   */
  int GetNumberOfParticipantsInRoundRobinSchedule(RRSchedule const & rr_sched);

  /*!
   * \brief ValidStandardRoundRobinTournament
   * \param rr_sched
   * \return
   */
  bool ValidStandardRoundRobinTournament(RRSchedule const & rr_sched);

  /*!
   * \brief GetMaximalVenuesForStandardRoundRobinTournament
   * \param rr_sched
   * \return
   */
  int GetMaximalVenuesForStandardRoundRobinTournament(RRSchedule const & rr_sched);

  /*!
   * \brief CheckRoundRobinRound
   * \param rr_mlist
   * \return
   */
  bool CheckRoundRobinRound(RRMatchupList const & rr_mlist);

  /*!
   * \brief ValidCompleteRoundRobinTournament
   * \param rr_sched
   * \return
   */
  bool ValidCompleteRoundRobinTournament(RRSchedule const & rr_sched);
  /*!
   * \brief ValidRoundRobinTournament
   * \param rr_sched
   * \return
   */
  bool ValidRoundRobinTournament(RRSchedule const & rr_sched);

} //namespace nedges

#endif // ROUNDROBIN_H
