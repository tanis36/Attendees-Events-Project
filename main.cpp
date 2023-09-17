#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <memory>
#include <algorithm>
#include <unordered_map>

#include "event.h"

std::vector<std::shared_ptr<Event>> create_event_list() {
    std::ifstream ifs {"../events.txt"};
    std::string s;

    std::vector<std::shared_ptr<Event>> events;

    while (getline(ifs, s)) {
        std::string delimiter = "|";
        std::string event_name = s.substr(0, s.find(delimiter));
        std::string org_name = s.substr(s.find(delimiter) + 1);

        events.push_back(std::make_shared<Event>(event_name, org_name));
    }

    return events;
}

std::unordered_map<std::string, std::vector<std::shared_ptr<Event>>> create_student_map(std::vector<std::shared_ptr<Event>>& events) {
    std::ifstream ifs {"../attendees.txt"};
    std::string s;

    std::unordered_map<std::string, std::vector<std::shared_ptr<Event>>> students;

    while (getline(ifs, s)) {
        std::string delimiter = "|";
        std::string attendee_name = s.substr(0, s.find(delimiter));
        std::string event_name = s.substr(s.find(delimiter) + 1);

        for (auto& e : events) {
            if (e->get_event_name() == event_name) {
                e->add_attendee(attendee_name);
                students[attendee_name].push_back(e);
            }
        }
    }

    return students;
}

int main() {
    std::vector<std::shared_ptr<Event>> events = create_event_list();
    std::unordered_map<std::string, std::vector<std::shared_ptr<Event>>> students = create_student_map(events);

    std::cout << "Please enter your choice: " << std::endl;
    int choice;
    std::cout << "1 = Attendees at event" <<std::endl;
    std::cout << "2 = Events student is attending" <<std::endl;
    std::cout << "3 = Organization of event student is attending" <<std::endl;
    std::cin >> choice;

    if (choice == 1) {
        std::cout << "Enter an event name: " << std::endl;
        std::string event_name;
        std::cin.ignore();
        std::getline(std::cin, event_name);

        std::cout << "\nStudents attending the " << event_name << ": " << std::endl;
        for (auto& s : students) {
            for (auto& e : s.second) {
                if (e->get_event_name() == event_name) {
                    std::cout << "\t" << s.first << std::endl; 
                }
            }
        }
    }

    if (choice == 2) {
        std::cout << "Enter a student's name: " << std::endl;
        std::string student_name;
        std::cin.ignore();
        std::getline(std::cin, student_name);

        std::cout << "\nEvents " << student_name << " is attending: " << std::endl;
        for (auto& s : students) {
            if (student_name == s.first) {
                for (auto& e : s.second) {
                    std::cout << "\t" << e->get_event_name() << std::endl;
                    std::cout << "\t\t" << "Number of attendees: " << e->num_attending() << std::endl;
                }
            }
        }
    }

    if (choice == 3) {
        std::cout << "Enter a student's name: " << std::endl;
        std::string student_name;
        std::cin.ignore();
        std::getline(std::cin, student_name);

        std::vector<std::string> orgs;

        std::cout << "\nOrganizations sponsoring events attended by " << student_name << ": " << std::endl;
        for (auto& s : students) {
            if (student_name == s.first) {
                for (auto& e : s.second) {
                    orgs.push_back(e->organization());
                }
            }
        }

        std::sort(orgs.begin(), orgs.end());
        orgs.erase(unique(orgs.begin(), orgs.end()), orgs.end());

        for (auto& org : orgs) {
            std::cout << "\t" << org << std::endl;
        }
    }

}