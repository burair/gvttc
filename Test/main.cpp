/*!************************************************************************
 *   This file is part of Nedges.                                         *
 *   A table tennis club, league and tournament management package.       *
 *                                                                        *
 *   "Wish you LOTS of nedges (Nets and Edges)."                          *
 *                                        -- Wayne Carney, Ray Mack       *
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
#include <iostream>
#include "Participants/player.h"
#include "Events/roundrobin.h"
#include "Events/league.h"
using namespace std;

namespace nedges {


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

    ConstructStandardRoundRobinSchedule(st_sched,num_participants,num_venues, num_rounds);
    for (RRScheduleIt rit = st_sched.begin(); rit != st_sched.end(); ++rit) {
        for (RRMatchupListIt mlit = rit->second.begin(); mlit != rit->second.end(); ++mlit) {
            std::cout << " (" << mlit->first << "," << mlit->second << ")";
        }
        std::cout << std::endl;
    }
    if (BalanceStandardRoundRobinTournamentHaselgroveLeech(st_sched)) {
        std::cout << "Below is the balanced rr constructed from the Standard RR" << std::endl;
    } else {
        std::cout << "Could not construct a balanced rr" << std::endl;
    }
    for (RRScheduleIt rit = st_sched.begin(); rit != st_sched.end(); ++rit) {
        for (RRMatchupListIt mlit = rit->second.begin(); mlit != rit->second.end(); ++mlit) {
            std::cout << " (" << mlit->first << "," << mlit->second << ")";
        }
        std::cout << std::endl;
    }

    st_sched.clear();
    ConstructFactoredBalancedRoundRobinTournament2x2kplus1(st_sched,6);
    for (RRScheduleIt rit = st_sched.begin(); rit != st_sched.end(); ++rit) {
        for (RRMatchupListIt mlit = rit->second.begin(); mlit != rit->second.end(); ++mlit) {
            std::cout << " (" << mlit->first << "," << mlit->second << ")";
        }
        std::cout << std::endl;
    }
    if (IsBalancedStandardRoundRobinTournament(st_sched)) {
        std::cout << "This is a balanced rr" << std::endl;
    } else {
        std::cout << "Not a balanced rr" << std::endl;
    }
}

} //namespace nedges

int main()
{
    nedges::ScheduleRoundRobin(12,5);

    nedges::League my_league("Summer 2015");
//    nedges::Date start=nedges::make_date_from_string("2015-Jun-12");
    nedges::Date start = boost::gregorian::nth_day_of_the_week_in_month(boost::gregorian::nth_day_of_the_week_in_month::second, boost::gregorian::Monday,boost::gregorian::Jun).get_date(2015);
    nedges::Date end=nedges::make_date_from_string("2015-Aug-14");
    nedges::date_list breaks;
    breaks.push_back(nedges::make_date_from_string("2015-Jul-1"));
    std::vector<boost::date_time::weekdays> league_days;
 //   league_days.push_back(boost::date_time::Monday);
    league_days.push_back(boost::date_time::Tuesday);
    league_days.push_back(boost::date_time::Wednesday);
 //   league_days.push_back(boost::date_time::Thursday);
 //   league_days.push_back(boost::date_time::Friday);
    league_days.push_back(boost::date_time::Saturday);
 //   league_days.push_back(boost::date_time::Sunday);

    my_league.make_weekly_schedule(start,end,breaks,league_days);
    my_league.show_schedule();
}

