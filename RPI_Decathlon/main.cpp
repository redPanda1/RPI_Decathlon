//
//  main.cpp
//  RPI_Decathlon
//
//  Created by Simon Hopkins on 8/23/19.
//  Copyright © 2019 Simon Hopkins. All rights reserved.
//

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cmath>
#include "Athlete.hpp"

using namespace std;

vector<Athlete> all_athletes;

// Helper method to return existing Athlete (or NULL if not found)
// Note use of pointers not records
Athlete *get_athlete(string name) {
    for (auto& athlete : all_athletes) {
        if (athlete.get_full_name().compare(name) == 0)
            return &athlete;
    }
    return NULL;
}

// Update an athletes recored based upon results data - create a new athlete record if this is the first set of results for an athlete
void update_athlete(vector<string> results) {
    // First check if Athlete exists (use full name as the key)
    string athlete_name = results[0] + " " + results[1];
    Athlete *athlete = get_athlete(athlete_name);
    
    if (athlete) {
        // If athlete exists - update as follows:
        // results[0] - First Name
        // results[1] - Last Name
        // results[2] - Country
        // results[3] - Event score
        athlete->set_country(results[2]);
        try {
            athlete->set_score_for_event(results[4], results[3]);
        } catch (exception& e) {
            cerr << "Error: " << e.what() << endl;
        }
    } else {
        // If first results for athlete, create new athlete
        // Use constructor using results vector
        athlete = new Athlete(results);
        all_athletes.push_back(*athlete);
    }
}

// Helper method to calculate average
double calc_avg(string event_name) {
    double total_points = 0;
    int total_events = 0;
    for(int i=0; i<all_athletes.size(); ++i) {
        int points = all_athletes[i].get_points_for_event(event_name);
        if (points > 0) {
            total_points += points;
            total_events += 1;
        }
        
    }
    return total_points / total_events;
}

// Output header line for all types
void output_header(string output_type) {
    if (output_type.compare("POINTS") == 0) {
        std::cout << setw(25) << left << "DECATHLETE POINTS" << std::setw(8) << right << "Country"
        << std::setw(7) << right << "100"
        << std::setw(7) << right << "LJ"
        << std::setw(7) << right << "SP"
        << std::setw(7) << right << "HJ"
        << std::setw(7) << right << "400"
        << std::setw(7) << right << "110H"
        << std::setw(7) << right << "DT"
        << std::setw(7) << right << "PV"
        << std::setw(7) << right << "JT"
        << std::setw(7) << right << "1500"
        << std::setw(9) << right << "TOTAL" << endl;
    } else if (output_type.compare("SCORES") == 0) {
        std::cout << setw(25) << left << "DECATHLETE SCORES" << std::setw(8) << right << "Country"
        << std::setw(7) << right << "100"
        << std::setw(7) << right << "LJ"
        << std::setw(7) << right << "SP"
        << std::setw(7) << right << "HJ"
        << std::setw(7) << right << "400"
        << std::setw(7) << right << "110H"
        << std::setw(7) << right << "DT"
        << std::setw(7) << right << "PV"
        << std::setw(7) << right << "JT"
        << std::setw(10) << right << "1500" << endl;
    } else {
        std::cout << setw(25) << left << "AVERAGES" << std::setw(8) << right << "Country"
        << std::setw(7) << right << "100"
        << std::setw(7) << right << "LJ"
        << std::setw(7) << right << "SP"
        << std::setw(7) << right << "HJ"
        << std::setw(7) << right << "400"
        << std::setw(7) << right << "110H"
        << std::setw(7) << right << "DT"
        << std::setw(7) << right << "PV"
        << std::setw(7) << right << "JT"
        << std::setw(7) << right << "1500"
        << std::setw(7) << right << "TRACK"
        << std::setw(7) << right << "FIELD"
        << std::setw(9) << right << "OVERALL" << endl;
    }
}
// Output times and distances
void output_scores() {
    for(int i=0; i<all_athletes.size(); ++i) {
        cout << setw(25) << left << all_athletes[i].get_full_name();
        cout << setw(8) << right << all_athletes[i].get_country();
        cout.precision(2);
        cout << setw(7) << fixed << all_athletes[i].get_score_for_event("100_METERS");
        cout << setw(7) << fixed << all_athletes[i].get_score_for_event("LONG_JUMP");
        cout << setw(7) << fixed << all_athletes[i].get_score_for_event("SHOT_PUT");
        cout << setw(7) << fixed << all_athletes[i].get_score_for_event("HIGH_JUMP");
        cout << setw(7) << fixed << all_athletes[i].get_score_for_event("400_METERS");
        cout << setw(7) << fixed << all_athletes[i].get_score_for_event("110_METERS_HURDLES");
        cout << setw(7) << fixed << all_athletes[i].get_score_for_event("DISCUS_THROW");
        cout << setw(7) << fixed << all_athletes[i].get_score_for_event("POLE_VAULT");
        cout << setw(7) << fixed << all_athletes[i].get_score_for_event("JAVELIN_THROW");
        // Special formatting for minutes/seconds
        int minutes = all_athletes[i].get_score_for_event("1500_METERS") / 60;
        double seconds = fmod(all_athletes[i].get_score_for_event("1500_METERS"), 60);
        stringstream ss;
        ss << std::setw(5) << setprecision(4) << setfill('0') << seconds;
        string secondsString = ss.str();
        cout << setw(4) << right << minutes << ":" << right << secondsString << endl;
    }
}
// Output points
void output_points() {
    for(int i=0; i<all_athletes.size(); ++i) {
        cout << setw(25) << left << all_athletes[i].get_full_name();
        cout << setw(8) << right << all_athletes[i].get_country();
        cout << setw(7) << right << all_athletes[i].get_points_for_event("100_METERS");
        cout << setw(7) << right << all_athletes[i].get_points_for_event("LONG_JUMP");
        cout << setw(7) << right << all_athletes[i].get_points_for_event("SHOT_PUT");
        cout << setw(7) << right << all_athletes[i].get_points_for_event("HIGH_JUMP");
        cout << setw(7) << right << all_athletes[i].get_points_for_event("400_METERS");
        cout << setw(7) << right << all_athletes[i].get_points_for_event("110_METERS_HURDLES");
        cout << setw(7) << right << all_athletes[i].get_points_for_event("DISCUS_THROW");
        cout << setw(7) << right << all_athletes[i].get_points_for_event("POLE_VAULT");
        cout << setw(7) << right << all_athletes[i].get_points_for_event("JAVELIN_THROW");
        cout << setw(7) << right << all_athletes[i].get_points_for_event("1500_METERS");
        cout << setw(9) << right << all_athletes[i].get_total_points() << endl;
    }
}
// Output averages
void output_averages() {
    double average_100m = calc_avg("100_METERS");
    double average_LJ = calc_avg("LONG_JUMP");
    double average_SP = calc_avg("SHOT_PUT");
    double average_HJ = calc_avg("HIGH_JUMP");
    double average_400m = calc_avg("400_METERS");
    double average_110mH = calc_avg("110_METERS_HURDLES");
    double average_DT = calc_avg("DISCUS_THROW");
    double average_PV = calc_avg("POLE_VAULT");
    double average_JT = calc_avg("JAVELIN_THROW");
    double average_1500m = calc_avg("1500_METERS");
    double average_track = (average_100m + average_400m + average_110mH + average_1500m) / 4.0;
    double average_field = (average_LJ + average_SP + average_HJ + average_DT + average_PV + average_JT) / 6.0;
    double average_total = (average_100m + average_LJ + average_SP + average_HJ + average_400m + average_110mH + average_DT + average_PV + average_JT + average_1500m) / 10.0;

    
    for(int i=0; i<all_athletes.size(); ++i) {
        cout << setw(25) << left << all_athletes[i].get_full_name();
        cout << setw(8) << right << all_athletes[i].get_country();
        cout.precision(1);
        cout << setw(6) << fixed << ((all_athletes[i].get_points_for_event("100_METERS") - average_100m) / average_100m) * 100 << "%";
        cout << setw(6) << right << ((all_athletes[i].get_points_for_event("LONG_JUMP") - average_LJ) / average_LJ) * 100 << "%";
        cout << setw(6) << right << ((all_athletes[i].get_points_for_event("SHOT_PUT") - average_SP) / average_SP) * 100 << "%";
        cout << setw(6) << right << ((all_athletes[i].get_points_for_event("HIGH_JUMP") - average_HJ) / average_HJ) * 100 << "%";
        cout << setw(6) << right << ((all_athletes[i].get_points_for_event("400_METERS") - average_400m) / average_400m) * 100 << "%";
        cout << setw(6) << right << ((all_athletes[i].get_points_for_event("110_METERS_HURDLES") - average_110mH) / average_110mH) * 100 << "%";
        cout << setw(6) << right << ((all_athletes[i].get_points_for_event("DISCUS_THROW") - average_DT) / average_DT) * 100 << "%";
        cout << setw(6) << right << ((all_athletes[i].get_points_for_event("POLE_VAULT") - average_PV) / average_PV) * 100 << "%";
        cout << setw(6) << right << ((all_athletes[i].get_points_for_event("JAVELIN_THROW") - average_JT) / average_JT) * 100 << "%";
        cout << setw(6) << right << ((all_athletes[i].get_points_for_event("1500_METERS") - average_1500m) / average_1500m) * 100 << "%";
        cout << setw(6) << right << ((all_athletes[i].get_avg_points_for_area(true) - average_track) / average_track) << "%";
        cout << setw(6) << right << ((all_athletes[i].get_avg_points_for_area(false) - average_field) / average_field) << "%";
        cout << setw(8) << right << (((all_athletes[i].get_total_points() / 10) - average_total) / average_total) * 100 << "%" << endl;
    }
}



void output_results(string output_type) {
    // Sort in desired order
    sort(all_athletes.begin(), all_athletes.end(), [ ]( auto& rec1, auto& rec2 ) {
        return rec1.get_last_name() < rec2.get_last_name();
         });
    
    // Show desired output
    if (output_type.compare("POINTS") == 0) {
        output_header("POINTS");
        output_points();
    } else if (output_type.compare("SCORES") == 0) {
        output_header("SCORES");
        output_scores();
    } else {
        output_header("CUSTOM");
        output_averages();
    }

    
}


// Main
int main(int argc, char* argv[]) {
    // Check for correct number of parameters passed
    if (argc != 4) {
        throw invalid_argument("Incorrect number of parameters:");
    }
    
    // Populate files and output type
    string input_file = argv[1];
    string output_file = argv[2];
    string output_type = argv[3];

    // Temp variables
    string text_line;
    string event_name;
    
    // Read in file and process line
    ifstream olympic_file (input_file);
    if (olympic_file.is_open())
    {
        while (getline (olympic_file, text_line)) {
            // Check for start of event data & populate event name
            if (text_line.substr(0, 5).compare("event") == 0) {
                event_name = text_line.substr(6);
            } else if (text_line.length() > 0) {
                // Check for results line & parse line into vector and add event name. Resulting in format:
                // results[0] - First Name
                // results[1] - Last Name
                // results[2] - Country
                // results[3] - Event score
                istringstream restlts_line(text_line);
                vector<string> results((istream_iterator<string>(restlts_line)), istream_iterator<string>());
                results.push_back(event_name);
                update_athlete(results);
            }
        }
        olympic_file.close();
        
        // Output results
        output_results(output_type);
    }
    
    else cout << "Unable to open file";
    
    return 0;
    
}

