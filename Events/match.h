/*!************************************************************************
 *   This file is part of Nedges.                                         *
 *   A table tennis club, league and tournament management package.       *
 *                                                                        *
 *   "Wish you LOTS of nedges (Nets and Edges)!!."                        *
 *                                          -- Wayne Carney, Ray Mack     *
 *   Author: Burair Kothari, 2014                                         *
 *                Genesee Valley Table Tennis CLub                        *
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
#ifndef NEDGES_MATCH_H
#define NEDGES_MATCH_H

#include <vector>
#include "Participants/player.h"
#include "boost/shared_ptr.hpp"
#include "boost/make_shared.hpp"

namespace nedges {

typedef std::vector<std::pair<int,int> > game_score;
typedef std::vector<game_score> match_score;
typedef std::vector<match_score> team_match_score;

  /*!
 * \brief The match class
 */

class match
{
public:
  match();

  virtual ~match();

private:
  match_score score;
};

/*!
 * \brief The teamMatch class
 */
class teamMatch
{
 public:
  teamMatch();

  virtual ~teamMatch();
 protected:
  team_match_score match_score;
};

/*!
 * \brief The teamMatchSwaythling class
 */
class teamMatchSwaythling : public teamMatch {
 public:
  teamMatchSwaythling();

};

/*!
 * \brief The teamMatchCorbillon class
 */
class teamMatchCorbillon : public teamMatch {
public:
  teamMatchCorbillon();
};

/*!
 * \brief The teamMatchCorbillonPara class
 */
class teamMatchCorbillonPara : public teamMatch {
public:
  teamMatchCorbillonPara();
};

/*!
 * \brief The teamMatchOlympic class
 */
class teamMatchOlympic : public teamMatch {
public:
  teamMatchOlympic();
};

/*!
 * \brief The teamMatchBo7 class
 */
class teamMatchBo7 : public teamMatch {
public:
  teamMatchBo7();
};

/*!
 * \brief The teamMatchBo9 class
 */
class teamMatchBo9 : public teamMatch {
public:
  teamMatchBo9();
};

/*!
 * \brief The teamMatchBo9d class
 */
class teamMatchBo9d : public teamMatch {
public:
  teamMatchBo9d();
};

/*!
 * \brief The teamMatch4pBo12 class
 */
class teamMatch4pBo12 : public teamMatch {
public:
  teamMatch4pBo12();
};

} //namespace nedges
#endif // MATCH_H
