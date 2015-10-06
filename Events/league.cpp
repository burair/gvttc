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
#include "league.h"

namespace nedges {
League::League(std::string _name): name(_name)
{

}
/**
 * @brief League::make_weekly_schedule
 *        Make a schedule for a league given a start and end date. The start date has to be before but within a week
 *        of the first planned meeting. This function takes a list of league off dates and a list of days on which the league plays.
 * @param _s -- start date: the first date on which the league can possibly start
 * @param _e -- end date: the last date on which the league can possibly end
 * @param _od -- off dates: list of dates on which the league does not play
 * @param _ld -- league days: weekdays on which the league plays (Sun = 0 to Sat = 6)
 */
void League::make_weekly_schedule(const Date &_s, const Date &_e, const date_list &_od, const std::vector<boost::date_time::weekdays> _ld) {
  typedef std::vector<boost::date_time::weekdays> ldv;
  typedef ldv::const_iterator ldv_it;
  if (_ld.empty()) { //if the list of days of the week is empty we assume the league only plays on one day every week which is the day of the start date
      make_weekly_schedule(_s,_e, _od);
      return;
    }

  Date this_date = find_league_start_date(_s,_ld); //find the league start date incase the given start date is not on one of the days the league plays
  boost::gregorian::greg_weekday swd(this_date.day_of_week());

  int scount = 0;
  while (this_date <= _e) {
    std::vector<Date> this_week_dates;
    this_week_dates.push_back(this_date);
    for (ldv_it tld = _ld.begin(); tld  != _ld.end(); ++tld ) {
        if (*tld == swd) continue;
        Date wp_date = boost::gregorian::first_day_of_the_week_after(*tld).get_date(this_date);
        if (wp_date > _e) break;
        this_week_dates.push_back(wp_date);
      }
    std::sort(this_week_dates.begin(),this_week_dates.end());
    for (std::vector<Date>::iterator twd = this_week_dates.begin(); twd !=this_week_dates.end(); ++twd) {
        for (dl_cit od = _od.begin(); od != _od.end();++od) {
            if (*twd != *od)
              schedule.push_back(std::make_pair(++scount,*twd));
          }
      }
    this_date += boost::gregorian::weeks(1);
    }
  return;
}
/**
 * @brief find_league_start_date
 * @param _s
 * @param _ld
 * @return
 */
Date find_league_start_date(const Date &_s, const std::vector<boost::date_time::weekdays> _ld) {
  typedef std::vector<boost::date_time::weekdays> ldv;
  typedef ldv::const_iterator ldv_it;
  Date start_date = _s;
  boost::gregorian::greg_weekday swd(_s.day_of_week());
  int min = 7;
  for (ldv_it tld = _ld.begin(); tld  != _ld.end(); ++tld ) {
      boost::gregorian::greg_weekday wd(*tld);
      if ((wd - _s.day_of_week()) >= 0 ) {
          if (min >  wd - _s.day_of_week()) {
            min = wd - _s.day_of_week();
            swd = wd;
            if (min > 0)
              start_date = boost::gregorian::first_day_of_the_week_after(swd).get_date(_s);
            }
        }
    }
  return start_date;
}

/**
 * @brief League::make_weekly_schedule
 * @param _start
 * @param _end
 * @param _off_dates
 */
void League::make_weekly_schedule(Date const & _start, Date const &_end, date_list const & _off_dates) {
  using namespace boost::gregorian;
  int week = 0;
  schedule.clear();
  date_duration dw(7);
  if (_end < _start + dw ) return;
  Date this_date = _start;
  while (this_date <= _end) {
      find_next_league_date(this_date, dw,_off_dates);
      schedule.push_back(std::make_pair(++week,this_date));
      this_date+=dw;
    }
  return;
}
/**
 * @brief find_next_league_date
 * @param _td -- this date: the date we are currently at in creating the schedule
 * @param _dtnm -- days to next meeting: the number of days to the next league meeting
 * @param _od -- off dates: list of dates the league does not meet
 */
void find_next_league_date(Date & _td, boost::gregorian::date_duration const & _dtnm, date_list const & _od ) {
  for (dl_cit dh = _od.begin(); dh != _od.end(); ++ dh) {
      if (_td == *dh) _td+=_dtnm;
    }
  return;
}

void League::make_schedule_from_date_list(date_list & _l_dates) {
  using namespace boost::gregorian;
  int week = 0;
  schedule.clear();
  dl_it min_so_far = _l_dates.begin();
  while (_l_dates.size() != 0) {
    for(dl_it d = _l_dates.begin();d!=_l_dates.end();++d) {
        if (*min_so_far > *d) {
            min_so_far = d;
        }
      }
    week = if_unique_add_to_schedule(*min_so_far);
    _l_dates.erase(min_so_far);
    min_so_far = _l_dates.begin();
    }
  return;
}

void League::show_schedule() const {
  for (sched_cit dl = schedule.begin(); dl!=schedule.end();++dl) {
      std::cout << "League Sesson " << dl->first << " for " << name << " falls on " << dl->second << " a " << dl->second.day_of_week().as_long_string() << std::endl;
    }
}

int League::if_unique_add_to_schedule(Date const & dt) {
  int meeting_number = (schedule.size() == 0) ? 0 : schedule.back().first;
  for (sched_it s=schedule.begin();s!=schedule.end();++s) {
      if( dt == (s->second) ) return meeting_number;
    }
  add_to_schedule(meeting_number + 1,dt);
}

void League::add_to_schedule(int meeting_number, Date const & dt) {
  schedule.push_back(std::make_pair(meeting_number,dt));
}


Date make_date_from_string(std::string const & a_date){

  return boost::gregorian::from_string(a_date);

}

Date get_league_end_day(const boost::gregorian::greg_weekday & wday, const Date & end ) {

  boost::gregorian::first_day_of_the_week_before fbdf(wday);
  return fbdf.get_date(end + boost::gregorian::date_duration(1));
}

void LadderLeague::add_player(Player & a_player, int initial_rank) {
  if (initial_rank == 0) {
      if (players.size() !=0 ) {
          initial_rank = players.rbegin()->first + 1;
        } else {
          initial_rank=1;
        }
    }
  std::pair<lrl_it,bool> r = players.insert(std::make_pair(initial_rank,&a_player));
  if (!(r.second)) add_player(a_player);
}

void LadderLeague::swap_players_at_ranks(int rp1, int rp2) {
  PlayerPtr p1 = players[rp1];
  PlayerPtr p2 = players[rp2];
  players[rp1] = p2;
  players[rp2] = p1;
}

void LadderLeague::insert_or_replace_player_at_rank(int r, PlayerPtr p) {
  players[r] = p;
}

void LadderLeague::insert_by_moving_all_players_down(int r, PlayerPtr p) {
  lrl_it p_it = players.find(r);
  if (p_it == players.end()) players[r] = p;
  else {
      for (lrl_rit p_rit = players.rbegin(); p_rit.base() != p_it; ++p_rit) {
          players[p_rit->first + 1] = players[p_rit->first];
        }
      players[r]=p;
    }
}

} //namespace nedges
