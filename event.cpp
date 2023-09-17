#include <string>

#include "event.h"

Event::Event(const std::string& n, const std::string& o)
        : name{n}, org{o}
{}

void Event::add_attendee(const std::string& attendee) {
    attendees.push_back(attendee);
}

bool Event::is_attending(const std::string& attendee) const {
    bool attending = false;
    for (auto& a : attendees) {
        if (attendee == a) {
            attending = true;
            break;
        }
    }
    return attending;
}

int Event::num_attending() const {
    int number_of_attendees = 0;
    auto attendee_size = attendees.size();
    number_of_attendees += attendee_size;
    return number_of_attendees;
}

std::string Event::organization() const {
    return org;
}

std::string Event::get_event_name() {
    return name;
}
