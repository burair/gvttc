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
League::League()
{

}

void League::make_weekly_schedule(Date const & _start, Date const &_end, date_list const & _off_dates) {
  using namespace boost::gregorian;
  int week = 0;
  schedule.clear();
  date_duration dw(7);
  if (_end < _start + dw ) return;
  Date this_date = _start;
  while (this_date < _end) {
      for (dl_cit dh = _off_dates.begin(); dh != _off_dates.end(); ++dh) {
          if (this_date == *dh) this_date+=dw;
        }
      if(this_date >= _end) break;
      schedule.push_back(std::make_pair(++week,this_date));
      this_date+=dw;
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
      std::cout << "League Sesson: " << dl->first << " falls on " << dl->second << std::endl;
    }
}

int League::if_unique_add_to_schedule(Date const & dt) {
  int m_no = (schedule.size() == 0) ? 0 : schedule.back().first;
  for (sched_it s=schedule.begin();s!=schedule.end();++s) {
      if( dt == (s->second) ) return m_no;
    }
  add_to_schedule(m_no + 1,dt);
}

void League::add_to_schedule(int m_no, Date const & dt) {
  schedule.push_back(std::make_pair(m_no,dt));
}


Date make_date_from_string(std::string const & a_date){

  return boost::gregorian::from_string(a_date);

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
