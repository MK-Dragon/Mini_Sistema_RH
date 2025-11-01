// Model/Dates.h

#pragma once

struct Date {
    int day;
    int month;
    int year;
};

inline bool operator==(const Date& lhs, const Date& rhs) {
    return (lhs.day == rhs.day) && 
           (lhs.month == rhs.month) && 
           (lhs.year == rhs.year);
}