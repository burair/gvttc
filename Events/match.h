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

class Match
{
public:
  Match();


  virtual ~Match();

protected:
  match_score score;
};
/*!
 * \brief The singlesMatch class
 */
class SinglesMatch: public Match
{
public:
  SinglesMatch();

private:
  Player player1;
  Player player2;
};
/*!
 * \brief The doublesMatch class
 */
class DoublesMatch: public Match
{
  DoublesMatch();
private:
  Player player1a;
  Player player2a;
  Player player1b;
  Player player2b;
};

/*!
 * \brief The TeamMatch class
 */
class TeamMatch
{
 public:
  TeamMatch();

  virtual ~TeamMatch();
 protected:
  team_match_score match_score;
 private:

};

/*!
 * \brief The TeamMatchSwaythling class
 */
class TeamMatchSwaythling : public TeamMatch {
 public:
  TeamMatchSwaythling();

};

/*!
 * \brief The TeamMatchCorbillon class
 */
class TeamMatchCorbillon : public TeamMatch {
public:
  TeamMatchCorbillon();
};

/*!
 * \brief The TeamMatchCorbillonPara class
 */
class TeamMatchCorbillonPara : public TeamMatch {
public:
  TeamMatchCorbillonPara();
};

/*!
 * \brief The TeamMatchOlympic class
 */
class TeamMatchOlympic : public TeamMatch {
public:
  TeamMatchOlympic();
};

/*!
 * \brief The TeamMatchBo7 class
 */
class TeamMatchBo7 : public TeamMatch {
public:
  TeamMatchBo7();
};

/*!
 * \brief The TeamMatchBo9 class
 */
class TeamMatchBo9 : public TeamMatch {
public:
  TeamMatchBo9();
};

/*!
 * \brief The teamMatchBo9d class
 */
class TeamMatchBo9d : public TeamMatch {
public:
  TeamMatchBo9d();
};

/*!
 * \brief The teamMatch4pBo12 class
 */
class TeamMatch4pBo12 : public TeamMatch {
public:
  TeamMatch4pBo12();
};

} //namespace nedges
#endif // MATCH_H
