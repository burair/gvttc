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

namespace nedges {

typedef std::pair<int,Date> league_date;
typedef std::vector<league_date> league_schedule;

typedef std::vector<Team> teams;
class League : public Event
{
public:
  League();

  virtual ~League();
protected:
  league_schedule schedule;
};

class TeamLeague: public League
{
public:
  TeamLeague();

private:

};

class LadderLeague: public League
{
public:
  LadderLeague();

private:

};
} //namespace nedges
#endif // LEAGUE_H
