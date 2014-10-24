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
#include "roundrobin.h"
#include <set>


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

void ScheduleRoundRobin(int num_participants, int num_venues_available) {
    int num_matches = MatchesInRoundRobin(num_participants);
    int num_venues = num_venues_available;
    if (num_venues > (num_participants/2) ) {
        num_venues = num_participants / 2;
        std::cout << "There are " << num_venues_available - num_venues << " extra tables allocated" << std::endl;
    }
    int num_rounds = ceil((double) num_matches / num_venues);
    int nbyes = num_participants - (num_venues * 2);

    RRMatchupList rr_matchups;
    PossibleMatchups(rr_matchups, num_participants);

    std::cout << "There are " << num_matches << " matches with " << num_rounds
              << " rounds, and " << num_venues << " matches per round." << std::endl;
    std::cout << "In each round there are " << nbyes << " players with a bye." << std::endl;

    std::cout << "Here are all possible matchups" << std::endl;

    for (RRMatchupListIt rr_it = rr_matchups.begin(); rr_it!=rr_matchups.end(); ++rr_it)
        std::cout << "(" <<  rr_it->first << ", " << rr_it->second << "); ";
    std::cout << std::endl;

    if(num_matches != rr_matchups.size()) {
        std::cerr << "Error! matchups not the same as num_matches" << std::endl;
    }

    int odd = num_participants % 2;
    int np = num_participants + odd;

    RRSchedule st_sched;

    ConstructStandardRoundRobinSchedule(st_sched,num_participants,num_venues);
    for (RRScheduleIt rit = st_sched.begin(); rit != st_sched.end(); ++rit) {
        for (RRMatchupListIt mlit = rit->second.begin(); mlit != rit->second.end(); ++mlit) {
            std::cout << " (" << mlit->first << "," << mlit->second << ")";
        }
        std::cout << std::endl;
    }
    if (BalanceStandardRoundRobinTournament(st_sched)) {
        std::cout << "This is a balanced rr" << std::endl;
    } else {
        std::cout << "Not a balanced rr" << std::endl;
    }

}

int MatchesInRoundRobin(int num_participants) {
    return (num_participants * (num_participants - 1) /2);
}

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
 *
 * Follows the methods outlined in article below
 *
 * A Tournament Design Problem
 * Jenifer Haselgrove and John Leech
 * The American Mathematical Monthly, Vol. 84, No. 3 (Mar., 1977), pp. 198-201
 * Article Stable URL: http://www.jstor.org/stable/2319491
 */

void ConstructStandardRoundRobinSchedule(RRSchedule & rr_sched, int num_participants, int num_venues){
    ConstructStandardRoundRobinTournament(rr_sched,num_participants);
}

/*!
 * \brief ConstructStandardRoundRobinTournament
 * \param rr_sched
 * \param num_participants
 *
 * Construct Standard or cyclic round robin schedule
 * Follows the methods outlined in article below
 *
 * A Tournament Design Problem
 * Jenifer Haselgrove and John Leech
 * The American Mathematical Monthly, Vol. 84, No. 3 (Mar., 1977), pp. 198-201
 * Article Stable URL: http://www.jstor.org/stable/2319491
 */


void ConstructStandardRoundRobinTournament(RRSchedule & rr_sched, int num_participants) {
    int n = num_participants/2 + num_participants%2; // n is the number of matchups generated in each round
    int fc = num_participants%2 + 1; // first column to consider for the RR Tournament generated i.e. if odd neglect first generated column
    rr_sched.clear();
    RRMatchupList round;
    for (int row = 0; row != 2*n - 1; ++row ) {
        round.clear();
        for (int col = fc; col !=n+1; ++col) {
            // first team for this matchup -- one team in the first column is always team 2*n -- the others rotate cyclically
            int t1 = (col != 1) ? ( 2*n - (col - 1) + row ) % (2*n - 1): 2*n;
            t1 = (t1==0)? 2*n - 1: t1;
            // second team for this matchup -- cyclical rotation
            int t2 = ((col + row) % (2*n - 1));
            t2 = (t2==0)?2*n -1:t2;
            std::pair<int,int> matchup = std::make_pair(t1,t2);
            round.push_back(matchup);
        }
        rr_sched.push_back(std::make_pair(row,round));
    }
}

/*!
 * \brief BalanceStandardRoundRobinTournament
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

bool BalanceStandardRoundRobinTournament(RRSchedule & rr_sched) {
    if (!ValidStandardRoundRobinTournament(rr_sched)) return false;
    bool bal = IsBalancedStandardRoundRobinTournament(rr_sched);
    if(!bal) {
        bal = ReOrderRoundRobinRows(rr_sched);
        if (bal) {
            ExchangeElementsForBalance(rr_sched);
        }
        else return bal;
    }
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
    int nr = rr_sched.size(); // number of rows in RR Schedule
    RRMatchupList const & r1 = rr_sched.at(0).second; // Get the first row (or first round)
    int c = r1.size(); // size of the first row (later we check if all rows -- i.e. rounds -- are the same in size)
    int np1 = c * 2; // number of participants playing in the first round

    // if the number of rounds is 1 bigger than the number of players in the first round (one player has a bye) than this should be an
    // odd round robin. If the number of rounds is one less than the number of players than this is an even round robin. Any other result is not
    // a balanced round robin tournament when the maximal number of players play each round.

    bool odd = false;
    if (np1  == (nr - 1) ) odd = true;
    else if (np1 == (nr +1) ) odd = false;
    else return false;

    int np = 0;
    if (odd) np = np1 + 1;
    else np = np1;

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

bool ReOrderRoundRobinRows(RRSchedule const & rr_sched) {
    bool valid = true;
    return valid;
}

void ExchangeElementsForBalance(RRSchedule const & rr_sched) {
    return;
}

bool ValidStandardRoundRobinTournament(RRSchedule const & rr_sched) {
    bool valid = false;
    int rounds = rr_sched.size();
    if (rounds%2 != 1) return false;
    int n = (rounds+1)/2;
    for (RRScheduleCIt sit = rr_sched.begin(); sit!=rr_sched.end();++sit) {
        int m = sit->second.size();
        if ( (m != n) && (m != (n-1))) {
            std::cout << m << n << std::endl;
            return false;
        }
        valid = CheckRoundRobinRow(sit->second);
    }
    valid = ValidRoundRobinSchedule(rr_sched);
    return valid;
}

bool CheckRoundRobinRow(RRMatchupList const & rr_mlist) {
    std::set<int> elements;
    for (RRMatchupListCIt mit = rr_mlist.begin(); mit != rr_mlist.end(); ++mit ) {
        elements.clear();
        if (elements.find(mit->first) != elements.end() )
            elements.insert(mit->first);
        if (elements.find(mit->second) != elements.end() )
            elements.insert(mit->second);

    }
    if (elements.size() == 2 * rr_mlist.size()) return true;
    return false;
}

bool ValidRoundRobinSchedule(RRSchedule const & rr_sched) {
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
