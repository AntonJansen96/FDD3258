#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <iostream>
#include <chrono>

typedef std::chrono::time_point<std::chrono::system_clock> timePoint;

// Additional function that maybe be used for profiling functions/lambdas.
// Make sure to inline the function to be tested.
void profile(size_t iterations, void (*func)());

class Stopwatch
{
    // DATA MEMBERS ////////////////////////////////////////////////////////////

    timePoint   d_start;
    timePoint   d_stop;
    double      d_diff;
    std::string d_description;
    bool        d_stopped = false;
    
    public:
        // CONSTRUCTORS ////////////////////////////////////////////////////////

        // Construct Stopwatch object and start.
        Stopwatch();
        
        // Construct Stopwatch object, specify description and start.
        explicit Stopwatch(std::string const &description);

        // Copy constructor.
        Stopwatch(Stopwatch const &other);

        // Move constructor.
        Stopwatch(Stopwatch &&tmp);

        // MEMBER FUNCTIONS ////////////////////////////////////////////////////

        // Start Stopwatch.
        void start();

        // Stop Stopwatch.
        void stop();

        // Reset Stopwatch.
        void reset();

        // Return/edit Stopwatch description.
        std::string &description();

        // Check whether Stopwatch is running.
        bool isrunning() const;

        // Stop Stopwatch and insert fancy time into stream (default std::cout).
        void time(std::ostream &out = std::cout);

        // Stop Stopwatch and return raw time (value of d_diff) in ns.
        size_t rawtime();

        // OVERLOADED OPERATORS ////////////////////////////////////////////////

        // Copy assignment operator.
        Stopwatch &operator=(Stopwatch const &other);

        // Move assignment operator.
        Stopwatch &operator=(Stopwatch &&tmp);

        // Insert Stopwatch time into stream.
        friend std::ostream &operator<<(std::ostream &out, Stopwatch &obj);

        // Insert Stopwatch time into stream.
        friend std::ostream &operator<<(std::ostream &out, Stopwatch &&obj);

        // Add Stopwatch objects (times).
        Stopwatch &operator+=(Stopwatch const &rhs);

        // Subtract Stopwatch objects (times).
        Stopwatch &operator-=(Stopwatch const &rhs);

        // Multiply Stopwatch object's time by scalar.
        Stopwatch &operator*=(size_t scalar);

        // Divide Stopwatch object's time by scalar.
        Stopwatch &operator/=(size_t scalar);

        // Compare two Stopwatch objects.
        bool operator==(Stopwatch const &other) const;

        // Compare two Stopwatch objects.
        bool operator!=(Stopwatch const &other) const;

        // Compare two Stopwatch objects.
        bool operator<(Stopwatch const &other) const;

        // Compare two Stopwatch objects.
        bool operator>(Stopwatch const &other) const;
            
    private:
        // HELPER FUNCTIONS ////////////////////////////////////////////////////

        // Dedicated swap member. Used by move assignment operator.
        void swap(Stopwatch &other);
        
        // Private accessor for d_diff. Used by rawtime() function.
        size_t accessdiff() const;
};

// Return/edit Stopwatch description.
inline std::string &Stopwatch::description()
{
    return d_description;
}

// Check whether Stopwatch is running.
inline bool Stopwatch::isrunning() const
{
    return !d_stopped;
}

// Stop Stopwatch and return raw time (value of d_diff) in ns.
inline size_t Stopwatch::rawtime()
{
    this->stop();
    return accessdiff();
}

// Compare two Stopwatch objects.
inline bool Stopwatch::operator==(Stopwatch const &other) const
{
    return d_diff == other.d_diff ? true : false;
}

// Compare two Stopwatch objects.
inline bool Stopwatch::operator!=(Stopwatch const &other) const
{
    return d_diff != other.d_diff ? true : false;
}

// Compare two Stopwatch objects.
inline bool Stopwatch::operator<(Stopwatch const &other) const
{
    return d_diff < other.d_diff ? true : false;
}

// Compare two Stopwatch objects.
inline bool Stopwatch::operator>(Stopwatch const &other) const
{
    return d_diff > other.d_diff ? true : false;
}

// Private accessor for d_diff. Used by rawtime() function.
inline size_t Stopwatch::accessdiff() const
{
    return d_diff;
}

// Add Stopwatch objects (times).
inline Stopwatch operator+(Stopwatch const &lhs, Stopwatch const &rhs)
{
    return Stopwatch{lhs} += rhs;
}

// Subtract Stopwatch objects (times).
inline Stopwatch operator-(Stopwatch const &lhs, Stopwatch const &rhs)
{
    return Stopwatch{lhs} -= rhs;
}

// Multiply Stopwatch object's time by scalar.
inline Stopwatch operator*(Stopwatch const &lhs, size_t scalar)
{
    return Stopwatch{lhs} *= scalar;
}

// Multiply Stopwatch object's time by scalar.
inline Stopwatch operator*(size_t scalar, Stopwatch const &rhs)
{
    return Stopwatch{rhs} *= scalar;
}

// Divide Stopwatch object's time by scalar.
inline Stopwatch operator/(Stopwatch const &lhs, size_t scalar)
{
    return Stopwatch{lhs} /= scalar;
}

#endif
