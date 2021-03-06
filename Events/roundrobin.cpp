/*!************************************************************************
 *   This file is part of Nedges.                                         *
 *   A table tennis club, league and tournament management package.       *
 *                                                                        *
 *   "Wish you LOTS of nedges (Nets and Edges)."                          *
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
#include "roundrobin.h"
#include "Lib/Galois/galois.h"
#include "boost/math/common_factor.hpp"
#include <set>
#include <vector>

namespace nedges {

/*!
 * \brief RoundRobin::RoundRobin
 * \param _name
 * \param date
 * \param _player_list
 *
 *
 *
 *
 *
 */



RoundRobin::RoundRobin(std::string _name, std::string date,PlayerListPtrType _player_list)
{

}
/*!
 * \brief MatchesInRoundRobin
 * \param num_participants
 * \return
 */
int MatchesInRoundRobin(int num_participants) {
    return (num_participants * (num_participants - 1) /2);
}
/*!
 * \brief PossibleMatchups
 * \param rr_matchups
 * \param num_participants
 * \return
 */
int PossibleMatchups(RRMatchupList & rr_matchups, int num_participants ) {
    for (int i = 1; i!=num_participants+1;++i)
       for (int j = i+1; j!=num_participants + 1; ++j )
    rr_matchups.push_back(std::make_pair(i,j));
}

/*!
 * \brief ConstructStandardRoundRobinSchedule
 * \param rr_sched
 * \param num_participants
 * \param num_venues
 * \param num_rounds
 *
 * Construct a Round Robin Schedule consisting of multiple rounds of the same size
 * based on a Standard Round Robin Tournament defined in the function
 * ConstructStandardRoundRobinSchedule(RRSchedule &rr_sched, int num_participants, int num_venues, int num_rounds)
 *
 */

void ConstructStandardRoundRobinSchedule(RRSchedule & rr_sched, int num_participants, int num_venues, int num_rounds){
    ConstructStandardRoundRobinTournament(rr_sched,num_participants);
}

/*!
 * \brief ConstructStandardRoundRobinTournament
 * \param rr_sched
 * \param num_participants
 *
 * Construct Standard or Cyclic Round Robin Tournament
 *
 * this is of the form:
 *
 * r(1)   (2n,1)   (2n-1,2)   (2n-2,3) ...    (n+1,n)
 * r(2)   (2n,2)   (2n, 3)    (2n-1,4) ...    (n+2,n+1)
 * .
 * .
 * .
 * r(2n-1) (2n,n-1) ....
 *
 * Where all the numbers not in the first column above are mod (2n-1), but we replace 0 result from the mod operation with 2n-1
 */


void ConstructStandardRoundRobinTournament(RRSchedule & rr_sched, int num_participants) {
    int n = num_participants/2 + num_participants%2; /// n is the number of matchups generated in each round
    int fc = num_participants%2 + 1; /// first column to consider for the RR Tournament generated i.e. if odd neglect first generated column
    rr_sched.clear();
    RRMatchupList round;
    for (int row = 0; row != 2*n - 1; ++row ) {
        round.clear();
        for (int col = fc; col !=n+1; ++col) {

            /// first team for this matchup -- one team in the first column is always team 2*n -- the others rotate cyclically
            int t1 = (col != 1) ? ( 2*n - (col - 1) + row ) % (2*n - 1): 2*n;
            t1 = (t1==0)? 2*n - 1: t1;

            /// second team for this matchup -- cyclical rotation
            int t2 = ((col + row) % (2*n - 1));
            t2 = (t2==0)?2*n -1:t2;

            std::pair<int,int> matchup = std::make_pair(t1,t2);
            round.push_back(matchup);
        }
        rr_sched.push_back(std::make_pair(row,round));
    }
}


/*!
 * \brief DisplayModSchedule
 * \param mrs
 */

void DisplayModSchedule(ModSched const & mrs) {
  for (ModSchedCIt i=mrs.begin(); i!=mrs.end();++i) {
      std::cout << i->first;
    for (ModMatchListCIt j=i->second.begin(); j!=i->second.end(); ++j) {
        DisplayModMatch(*j);
      }
      std::cout << std::endl;
    }
}

/*!
 * \brief ConstructFactoredBalancedRoundRobinTournament2x2kplus1
 * \param rr_sched
 * \param num_participants
 *
 * This algorithm comes from Ian Anderson, Combinatorial Designs and Tournaments, Oxford 1997
 * Ch 10: Balanced Tournament Designs.
 *
 * The algorithm constructs tournament schedules for n_particpants = 2*(2k+1) i.e. twice an odd number
 * by constructing a "patterned starter" then swapping elements to get to a factored balanced round robin
 * schedule.
 *
 */

void ConstructFactoredBalancedRoundRobinTournament2x2kplus1(RRSchedule & rr_sched, int num_participants) {
  if (num_participants%2 != 0) return;
  if ((num_participants/2)%2 != 1) return;

  int n = num_participants/2;
  int k = (n-1) / 2;

  ModSched mrs;
  ////////////////////////////////////////////////////////////////////////
  /// The two functions below construct the patterned starter for a 2*(2k+1)
  /// FBTD.
  ///
  /// \brief ConstructColumn1EFBTD
  ///
  ///
  ConstructColumn1EFBTD(mrs,n,k);
  ///
  /// \brief ConstructRowsEFBTD
  ///
  ConstructRowsEFBTD(mrs,n,k);
  /////////////////////////////////////////////////////////////////////////

  /////////////////////////////////////////////////////////////////////////
  ///
  /// \brief FixRowsEFBTD
  ///
  FixRowsEFBTD(mrs,k);
  /////////////////////////////////////////////////////////////////////////

  /////////////////////////////////////////////////////////////////////////
  ///
  /// \brief UnModSchedule
  ///
  ///
  UnModSchedule(rr_sched, mrs, k);
  /////////////////////////////////////////////////////////////////////////
}

/*!
 * \brief UnModSchedule
 * \param rr_sched
 * \param mrs
 * \param k
 */
void UnModSchedule(RRSchedule & rr_sched, ModSched const & mrs, int k) {
  for (ModSchedCIt mm=mrs.begin(); mm!=mrs.end(); ++mm) {
      RRRound r;
      r.first=mm->first;
      for (ModMatchListCIt ml = mm->second.begin(); ml!=mm->second.end(); ++ml) {
          RRMatch m;
          m.first = ml->first.first + (2*k+1)*(ml->first.second - 1);
          m.second = ml->second.first + (2*k+1)*(ml->second.second - 1);
          r.second.push_back(m);
        }
      rr_sched.push_back(r);
    }
  return;
}


/*!
 * \brief FixRowsEFBTD
 * \param mrs
 * \param k
 */

void FixRowsEFBTD(ModSched & mrs,int k) {
  for (ModSchedIt i = mrs.begin(); i!=mrs.end(); ++i) {
      if(i->first > k) break;
      if(i->first == 0) continue;
      /*!
       * \brief t
       *
       * The period of the ith row mod 2k+1, this is the number of terms before a sequence
       * of element pairs cycles back to the first element in the first pair
       */
      int t = FindPeriod(k, i->first);

      /*!
       * \brief np
       * The number of sets of each cyclic sequence of repeating elements in a
       * row
       * Factored BTD construction
       */
      int np = (2*k+1)/t;

      std::vector<std::map<int,int> > csi;
      CalculateCosetIndices(csi,k,i->first,t);
      SwapCosetElements(mrs,csi,k ,i->first);
    }
}
/*!
 * \brief SwapCosetElements
 * \param mrs
 * \param csi
 * \param k
 * \param i
 */
void SwapCosetElements(ModSched &mrs, std::vector<std::map<int,int> > const & csi, int k, int i) {
    int t = FindPeriod(k,i);
    for (std::vector<std::map<int,int> >::const_iterator j = csi.begin(); j!=csi.end(); ++j) {
      for (int r = 1; r !=t;r+=2 ) {
        ModMatch & s1 = mrs[i].second[j->at(r)];
        ModMatch & s2 = mrs[i+k].second[j->at(r)];
        SwapModMatch (s1,s2);
      }
      ModMatch & s1 = mrs[i+k].second[j->at(0)];
      ModMatch & s2 = mrs[i+2*k].second[j->at(0)];
      SwapModMatch(s1,s2);
      ModMatch & s3 = mrs[i].second[j->at(t-1)];
      ModMatch & s4 = mrs[i+2*k].second[j->at(t-1)];
      SwapModMatch(s3,s4);
  }
  return;
}
/*!
 * \brief SwapModMatch
 * \param s1
 * \param s2
 */
void SwapModMatch(ModMatch &s1, ModMatch &s2) {
  ModMatch tmp;
  tmp = s1;
  s1 = s2;
  s2 = tmp;
  return;

}


/*!
 * \brief CalculateCosetIndices
 * \param ind
 * \param k
 * \param i
 * \param t
 *
 * Identifies the set of matches (coset) which need to be swapped between rounds in the schedule
 * generated by the ConstructFactoredBalancedRoundRobinTournament2x2kplus1 function. To do this
 * we first need to identify the matches which contain common elements (participants) in the same
 * row (round). The pattern for these matches depends on the cyclical period the  matches repeat (\param t).
 * This in turn depends on the round number (\param i) in conjuction with the # of participants (4 * \param k + 2).
 * This process follows steps outlined in Anderson: Combinatorial Design and Tournaments; Oxford 1997
 * pp. 197-200
 *
 */

void CalculateCosetIndices(std::vector<std::map<int,int> > & ind,int k,int i, int t) {
    ind.clear();
    int column = 0 ; int col = 0;
    int n = 2*k +1;
    std::set<int> Zn;
    for (int n=0;n!=2*k+1;++n) Zn.insert(n);
    while (Zn.find(column) != Zn.end()) {
        std::map<int,int> m;
        for (int c=0; c!=t; ++c) {
          Zn.erase(col);
          m[c] = col;
          col = (col + ((( -2 * i) % n) + n) % n) % n;
          }
        ind.push_back(m);
        col=++column;
      }
    return;
}

/*!
 * \brief DisplayModMatch
 * \param mm
 */
void DisplayModMatch(ModMatch const & mm) {
  std::cout << "(" << mm.first.first <<"_" << mm.first.second << "," <<mm.second.first << "_"<< mm.second.second << ") ";
}

/*!
 * \brief FindPeriod
 * \param k
 * \param i
 * \return
 */

int FindPeriod(int k, int i) {
    int mt = (2*(2*k+1) - (2 * i) )%(2*k+1);
    return boost::math::lcm(2*k+1,mt)/mt;
}


/*!
 * \brief ConstructRowsEFBTD
 * \param mrs
 * \param n
 * \param k
 */

void ConstructRowsEFBTD(ModSched & mrs, int n, int k) {
  for (ModSchedIt r=mrs.begin(); r!=mrs.end();++r){
      for (int i=1; i!=2*k+1; ++i) {
          ModMatch const & mp = r->second.back();
          ModMatch m(std::make_pair(std::make_pair((mp.first.first +1) % (2*k+1),mp.first.second),
                                    std::make_pair((mp.second.first+1)%(2*k+1),mp.second.second)));
          r->second.push_back(m);
        }
    }
  return;
}

/*!
 * \brief ConstructColumn1EFBTD
 * \param mrs
 * \param n
 * \param k
 */

void ConstructColumn1EFBTD(ModSched & mrs, int n, int k) {
  ModElement M001(std::make_pair(0,1));
  ModElement M002(std::make_pair(0,2));
  ModRound R;

  InitializeRoundEFBTD(R,0,M001,M002);
  mrs.push_back(R);
  for(int m = 1; m!=5;++m)
    for(int r=1; r!=k+1; ++r) {
        /*!
         * \brief MI01
         *
         * In each of rounds 1..k and 2k+1 .. 3k the first element in the match
         * in the first column has the subscript 1 (i.e. its 1_1 ... k_1).
         * In each of rounds k+1..2k and 3k+1 .. 4k the first element in the match
         * in the first column has the subscript 2 (i.2. its 1_2 .. k_2).
         * This is modeled by: 1 + (x - 1) mod 2 which is 1,2,1,2 for x={1,2,3,4}
         */
        ModElement MI01(std::make_pair(r,(m-1)%2 + 1));
        /*!
         * \brief MI02
         *
         * In each of rounds 1..k and 3k+1 .. 4k the second element in the match
         * in the first column has the subscript 1 (i.e. its (2k)_1 ... (k+1)_1).
         * In each of rounds k+1..2k and 2k+1 .. 3k the second element in the match
         * in the first column has the subscript 2 (i.2. its (2k)_2 .. (k+1)_2).
         * This is modeled by the quadratic: (4 + (x-2) - (x-2)^2)/2 which is 1,2,2,1 for x={1,2,3,4}
         *
         */
        ModElement MI02(std::make_pair(2*k -r + 1,(4 + (m - 2) - 1*(m - 2)*(m - 2) )/2 ));
        InitializeRoundEFBTD(R,(m-1)*k + r,MI01,MI02);
        mrs.push_back(R);
      }
  return;
}

/*!
 * \brief InitializeRoundEFBTD
 * \param R
 * \param round
 * \param M11
 * \param M12
 */

void InitializeRoundEFBTD(ModRound & R, int round,  ModElement & M11, ModElement & M12) {
  ModMatch M1(std::make_pair(M11,M12));
  ModMatchList RL;
  RL.clear();
  RL.push_back(M1);
  R.first = round;
  R.second = RL;
}

/*!
 * \brief BalanceStandardRoundRobinTournamentHaselgroveLeech
 * \param rr_sched
 * \return
 *
 * Follows the methods outlined in article below
 *
 * A Tournament Design Problem
 * Jenifer Haselgrove and John Leech
 * The American Mathematical Monthly, Vol. 84, No. 3 (Mar., 1977), pp. 198-201
 * Article Stable URL: http://www.jstor.org/stable/2319491
 */

bool BalanceStandardRoundRobinTournamentHaselgroveLeech(RRSchedule & rr_sched) {
  if (!ValidStandardRoundRobinTournament(rr_sched)) return false;
  bool bal = IsBalancedStandardRoundRobinTournament(rr_sched);
  if(!bal) {
      ExchangeElementsForBalanceHaselgroveLeech(rr_sched);
  }
  else return bal;
  return IsBalancedStandardRoundRobinTournament(rr_sched);
}

/*!
 * \brief IsBalancedStandardRoundRobinTournament
 * \param rr_sched
 * \return
 *
 * Check for a balanced round robin tournament design following definitions found here:
 *
 * E.R. Lamken, S.A. Vanstone, Balanced Tournament Designs and Related Topics,
 * In: A. Hartman, Editor(s), Annals of Discrete Mathematics, Elsevier, 1989, Volume 42, Pages 159-176,
 * ISSN 0167-5060, ISBN 9780444881151, http://dx.doi.org/10.1016/S0167-5060(08)70104-3.
 * (http://www.sciencedirect.com/science/article/pii/S0167506008701043)
 * Abstract: A balanced tournament design of order n, BTD(n), is an n x (2n – 1) array defined on a set of 2n elements V such that (1)
 * each cell of the array contains a pair of distinct elements from V, (2) every pair of distinct elements from V is contained in some cell,
 * (3) each element is contained in each column, and (4) no element is contained in more than 2 cells of each row.
 * BTD(n)s are very useful for scheduling certain types of round robin tournaments such as tennis and curling.
 * Their existence has been completely settled. In this paper we survey the known results and discuss various extensions and generalizations.
 *
 */

bool IsBalancedStandardRoundRobinTournament(RRSchedule const & rr_sched) {
  int nr = rr_sched.size(); /// number of rows in RR Schedule
  if (nr < 1) return false;
  RRMatchupList const & r1 = rr_sched.at(0).second; /// Get the first row (or first round)
  int c = r1.size(); /// size of the first row (later we check if all rows -- i.e. rounds -- are the same in size)
  int np1 = c * 2; /// number of participants playing in the first round

  /// if the number of rounds is 1 bigger than the number of players in the first round (one player has a bye) than this should be an
  /// odd round robin. If the number of rounds is one less than the number of players than this is an even round robin. Any other result is not
  /// a balanced round robin tournament when the maximal number of players play each round.
  bool odd = false;
  if (np1  == (nr - 1) ) odd = true;
  else if (np1 == (nr +1) ) odd = false;
  else return false;

  int np=odd?np1+1:np1; /// add bye player to the number of players

  std::map<int,int> ecount;
  for (int v=0;v!=c;++v) {
      for (int i=1;i!=np+1;++i) ecount[i] = 0;
      for (RRScheduleCIt s = rr_sched.begin(); s!=rr_sched.end();++s) {
          RRMatchupList const & ml = s->second;
          if (c!= ml.size()) return false;
          ecount[ml.at(v).first]++;
          ecount[ml.at(v).second]++;
        }
      for (int i=1; i!=np+1;++i) if(ecount[i] > 2) return false;
    }
  return true;
}

/*!
 * \brief ReOrderRoundRobinRows
 * \param rr_sched
 * \return
 */
bool ReOrderRoundRobinRows(RRSchedule & rr_sched) {
    return true;
}

/*!
 * \brief ExchangeElementsForBalanceHaselgroveLeech
 * \param rr_sched
 */
void ExchangeElementsForBalanceHaselgroveLeech(RRSchedule & rr_sched) {

  int nr = GetNumberOfRoundsInRoundRobinSchedule(rr_sched);
  int nv = GetNumberOfVenuesInRoundRobinSchedule(rr_sched);
  int np = GetNumberOfParticipantsInRoundRobinSchedule(rr_sched);

  for(int round = 1; round!=nr+1; ++round) {
      int xelem = (3*round - 1) % (np - 1);
      if (xelem == 0) xelem = np - 1;
      RRMatchupList & mround = rr_sched.at(round -1).second;
      for (RRMatchupListIt m = mround.begin(); m!=mround.end();++m) {
          if((m->first == xelem) || (m->second == xelem)) {
              //RRMatch xm = std::make_pair(m->first,m->second);
              ExchangeElements(mround.front(),*m);
            }
        }
    }

  return;
}

/*!
 * \brief ExchangeElements
 * \param fm
 * \param sm
 */
void ExchangeElements(RRMatch & fm, RRMatch & sm ) {
  RRMatch e(fm);

  fm = sm;
  sm = e;

  return;
}

/*!
 * \brief GetNumberOfRoundsInRoundRobinSchedule
 * \param rr_sched
 * \return
 */
int GetNumberOfRoundsInRoundRobinSchedule(RRSchedule const & rr_sched) {
  return rr_sched.size();
}
/*!
 * \brief GetNumberOfVenuesInRoundRobinSchedule
 * \param rr_sched
 * \param max
 * \param min
 * \return
 */
int GetNumberOfVenuesInRoundRobinSchedule(RRSchedule const & rr_sched, int & max, int & min) {
  min = 999999;
  max = 0;
  for (RRScheduleCIt rit = rr_sched.begin(); rit!=rr_sched.end(); ++rit) {
      int v = rit->second.size();
      if (v<min) min = v;
      if (v>max) max = v;
    }
  return (max==min)?max:0;
}

/*!
 * \brief GetNumberOfVenuesInRoundRobinSchedule
 * \param rr_sched
 * \return
 */
int GetNumberOfVenuesInRoundRobinSchedule(RRSchedule const & rr_sched) {
  int min = 999999;
  int max = 0;
  return GetNumberOfVenuesInRoundRobinSchedule(rr_sched, min, max);
}

/*!
 * \brief GetNumberOfParticipantsInRoundRobinSchedule
 * \param rr_sched
 * \return
 */
int GetNumberOfParticipantsInRoundRobinSchedule(RRSchedule const & rr_sched) {
  std::set<int> pts;
  for(RRScheduleCIt rit = rr_sched.begin();rit!=rr_sched.end();++rit) {
      RRMatchupList const & r = rit->second;
      for (RRMatchupListCIt vit = r.begin(); vit != r.end(); ++vit) {
          if(pts.find(vit->first) == pts.end()) pts.insert(vit->first);
          if(pts.find(vit->second) == pts.end()) pts.insert(vit->second);
        }
    }
  return pts.size();
}

/*!
 * \brief ValidStandardRoundRobinTournament
 * \param rr_sched
 * \return
 *
 * A Standard Round Robin Tournament has the same number of venues equal to
 * the maximum needed to get all or all but one participants involved in each round.
 * The tournament matches all possible pairs of participants, and has each participant
 * playing exactly once per round.
 *
 */
bool ValidStandardRoundRobinTournament(RRSchedule const & rr_sched) {
    bool valid = false;
    int n = GetMaximalVenuesForStandardRoundRobinTournament(rr_sched);
    if (n==0) return false;
    for (RRScheduleCIt sit = rr_sched.begin(); sit!=rr_sched.end();++sit) {
        int m = sit->second.size();
        if ( (m != n) && (m != (n-1))) return false;
        valid = CheckRoundRobinRound(sit->second);
    }
    valid = ValidRoundRobinTournament(rr_sched);
    return valid;
}

/*!
 * \brief GetMaximalVenuesForStandardRoundRobinTournament
 * \param rr_sched
 * \return
 *
 * There are (2*[nvenues_max] - 1) rounds i.e. the number of rounds must be an odd number in a standard schedule
 * nvenues_max is the number of venues it would take to match all participants if we include the bye-ghost match
 * i.e. if n(participants) is odd the number of actual venues requires is one less than the maximal number.
 *
 */

int GetMaximalVenuesForStandardRoundRobinTournament(RRSchedule const & rr_sched) {
    int rounds = rr_sched.size();
    if (rounds%2 != 1) return 0;
    return (rounds+1)/2;
}

/*!
 * \brief CheckRoundRobinRound
 * \param rr_mlist
 * \return
 *
 * Check if all the elements in a round or row are unique
 * the function counts all the unique elements and compares them to the size of the row
 */

bool CheckRoundRobinRound(RRMatchupList const & rr_mlist) {
    std::set<int> elements;
    elements.clear();
    for (RRMatchupListCIt mit = rr_mlist.begin(); mit != rr_mlist.end(); ++mit ) {
        if (elements.find(mit->first) == elements.end() )
            elements.insert(mit->first);
        else std::cout << "Found two elements " << mit->first;
        if (elements.find(mit->second) == elements.end() )
            elements.insert(mit->second);
        else std::cout <<"Found two elements " << mit->second;

    }
    if (elements.size() == 2 * rr_mlist.size()) return true;
    return false;
}


/*!
 * \brief ValidCompleteRoundRobinTournament
 * \param rr_sched
 * \return
 */
bool ValidCompleteRoundRobinTournament(RRSchedule const & rr_sched) {
  return ValidRoundRobinTournament(rr_sched);
}

/*!
 * \brief ValidRoundRobinTournament
 * \param rr_sched
 * \return
 *
 * Checks if all matches in a round robin tournament are unique
 */

bool ValidRoundRobinTournament(RRSchedule const & rr_sched) {
    std::set<std::pair<int,int> > match_set;
    for (RRScheduleCIt mit = rr_sched.begin(); mit!=rr_sched.end(); ++mit) {
        RRMatchupList const & ml = mit->second;
        for (RRMatchupListCIt lit = ml.begin();lit != ml.end(); ++lit) {
            if (! (match_set.insert(*lit)).second) return false;
        }
    }
    return true;
}

} //namespace nedges
