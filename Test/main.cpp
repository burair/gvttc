/*!************************************************************************
 *   This file is part of Nedges.                                         *
 *   A table tennis club, league and tournament management package.       *
 *                                                                        *
 *   "May your game be full of nedges (Nets and Edges)."                  *
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
#include <iostream>
#include "Participants/player.h"
#include "Events/roundrobin.h"
#include "hpdf.h"
#include "hpdf_types.h"

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
/*
    ConstructStandardRoundRobinSchedule(st_sched,num_participants,num_venues, num_rounds);
    for (RRScheduleIt rit = st_sched.begin(); rit != st_sched.end(); ++rit) {
        for (RRMatchupListIt mlit = rit->second.begin(); mlit != rit->second.end(); ++mlit) {
            std::cout << " (" << mlit->first << "," << mlit->second << ")";
        }
        std::cout << std::endl;
    }
    if (BalanceStandardRoundRobinTournamentHaselgroveLeech(st_sched)) {
        std::cout << "This is a balanced rr" << std::endl;
    } else {
        std::cout << "Not a balanced rr" << std::endl;
    }
    for (RRScheduleIt rit = st_sched.begin(); rit != st_sched.end(); ++rit) {
        for (RRMatchupListIt mlit = rit->second.begin(); mlit != rit->second.end(); ++mlit) {
            std::cout << " (" << mlit->first << "," << mlit->second << ")";
        }
        std::cout << std::endl;
    }
    */

    //ConstructFactoredBalancedRoundRobinTournament2n(st_sched, 6);
    ConstructFactoredBalancedRoundRobinTournament2x2kplus1(st_sched,10);
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

void error_handler (HPDF_STATUS error_no, HPDF_STATUS detail_no, void *user_data)
{
    printf ("ERROR: error_no=%04X, detail_no=%d\n",
      (unsigned int) error_no, (int) detail_no);
//    longjmp (env, 1); /* invoke longjmp() on error */
}

int main()
{
    nedges::ScheduleRoundRobin(6,3);
    HPDF_Doc pdf;

    pdf = HPDF_New (error_handler, NULL);

    if (!pdf) {
        std::cout << "ERROR:Cannot create pdf object" << std::endl;
        return 1;
      }

    HPDF_Page page_1;

    page_1 = HPDF_AddPage (pdf);

    HPDF_Image logo;

    logo = HPDF_LoadPngImageFromFile(pdf,"Table_tennis.png");

    std::cout << HPDF_Image_GetWidth(logo) << " " << HPDF_Image_GetHeight(logo) << std::endl;

    HPDF_Page_DrawImage(page_1,logo, 200, HPDF_Page_GetHeight(page_1) - 500,HPDF_Image_GetWidth(logo),HPDF_Image_GetHeight(logo));

    HPDF_SaveToFile (pdf, "test.pdf");


    HPDF_Free (pdf);
}

