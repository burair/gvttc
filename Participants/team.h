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
#ifndef NEDGES_TEAM_H
#define NEDGES_TEAM_H

#include "player.h"
#include <vector>

namespace nedges {

class Team
{
public:
  Team();
  int insert_player(PlayerPtr & _player) {
    players.push_back(_player);
    return players.size();
  }
  void set_team_name(std::string const & _name) {
    name = _name;
  }
  std::string get_name() const {
    return name;
  }
  void set_size (int _sz) {
    size=_sz;
  }
  int get_size () const {
    return size;
  }
  void set_team_number(int _tn) {
    team_number = _tn;
  }
  int get_team_number() const {
    return team_number;
  }

private:
  PlayerListType players;
  int size;
  std::string name;
  int team_number;
};

} // namespace nedges
#endif // NEDGES_TEAM_H
