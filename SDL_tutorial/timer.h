#ifndef TIMER_H
#define TIMER_H

/**
*  A simple timer
*/
class Timer {
public:
    Timer();
    ///Start the timer
    void start();
    ///Stop the timer
    void stop();
    ///Pause the timer
    void pause();
    ///Unpause the timer
    void unpause();
    /**
    *  Restart the timer and return the elapsed ticks
    *  @return The elapsed ticks
    */
    int restart();
    /**
    *  Get the elapsed ticks
    *  @return The elapsed ticks
    */
    int ticks() const;
    ///Check if Timer is started
    bool started() const;
    ///Check if Timer is paused
    bool paused() const;

private:
    int mStartTicks, mPausedTicks;
    bool mStarted, mPaused;
};

#endif