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
#ifndef NEDGES_LEAGUE_H
#define NEDGES_LEAGUE_H

#include "event.h"
#include "Participants/player.h"
#include "Participants/team.h"
#include <map>

namespace nedges {

typedef std::pair<int,Date> league_date;
typedef std::vector<league_date> league_schedule;
typedef league_schedule::const_iterator sched_cit;
typedef league_schedule::iterator sched_it;
typedef std::vector<Date> date_list;
typedef date_list::const_iterator dl_cit;
typedef date_list::iterator dl_it;
typedef std::map<int,PlayerPtr> ladder_ranking_list;
typedef std::pair<int,PlayerPtr> ladder_player;
typedef ladder_ranking_list::iterator lrl_it;
typedef ladder_ranking_list::const_iterator lrl_cit;
typedef ladder_ranking_list::reverse_iterator lrl_rit;
typedef ladder_ranking_list::const_reverse_iterator lrl_crit;

typedef std::vector<Team> teams;
class League : public Event
{
public:
  League(std::string _name="");

  virtual ~League() {}

  void setName(std::string _name) { name = _name; }

  std::string const getName() { return name; }

  void make_weekly_schedule(const Date &_start, const Date &_end, const date_list &_off_dates, const std::vector<boost::date_time::weekdays> _league_days);

  void make_weekly_schedule(Date const &_start, Date const &_end, date_list const & _off_dates);

  void make_schedule_from_date_list(date_list & _l_dates);

  void add_to_schedule(int _m_no, Date const & _dt);

  int if_unique_add_to_schedule(Date const & _dt);

  void show_schedule() const;
protected:
  std::string name;
  league_schedule schedule;
};

class TeamLeague: public League
{
public:
  TeamLeague();


private:
  teams teamlist;
};

class LadderLeague: public League
{
public:
  LadderLeague();

  void add_player(Player & a_player, int initial_rank=0);
  Player & get_player_by_rank(int _rank=0) const;
  void swap_players_at_ranks(int rp1,int rp2);
  void insert_or_replace_player_at_rank(int r, PlayerPtr p);
  void insert_by_moving_all_players_down(int r, PlayerPtr p);

private:
  ladder_ranking_list players;
};

Date find_league_start_date(const Date &_s, const std::vector<boost::date_time::weekdays> _ld);

Date make_date_from_string(std::string const & a_date);

Date get_league_end_day(const boost::gregorian::greg_weekday & wday, const Date & end );

void find_next_league_date(Date & _td, boost::gregorian::date_duration const & _dtnm, date_list const & _od );

} //namespace nedges
#endif // LEAGUE_H
