#include <iostream>
#include <string>
using namespace std;
class DvdPlayer
{
public:
    void on() { cout << "DVD player on\n"; }
    void off() { cout << "DVD player off\n"; }
    void eject() { cout << "Ejecting DVD\n"; }
    void play(string movie) { cout << "Playing " << movie << " on DVD player\n"; }
    void stop() { cout << "Stopping DVD player\n"; }
};
class Amplifier
{
public:
    void on() { cout << "Amplifier on\n"; }
    void off() { cout << "Amplifier off\n"; }
    void setDvd(DvdPlayer *dvd) { cout << "Setting DVD player to amplifier\n"; }
    void setSurroundSound() { cout << "Setting surround sound on amplifier\n"; }
    void setVolume(int level) { cout << "Setting amplifier volume to " << level << "\n"; }
};
class Tuner
{
public:
    void on() { cout << "Tuner on\n"; }
    void off() { cout << "Tuner off\n"; }
};
class CdPlayer
{
public:
    void on() { cout << "CD player on\n"; }
    void off() { cout << "CD player off\n"; }
};
class Projector
{
public:
    void on() { cout << "Projector on\n"; }
    void off() { cout << "Projector off\n"; }
    void setInput(DvdPlayer *dvd) { cout << "Setting DVD player to projector\n"; }
    void setWideScreenMode() { cout << "Setting widescreen mode on projector\n"; }
};
class TheaterLights
{
public:
    void on() { cout << "Lights on\n"; }
    void off() { cout << "Lights off\n"; }
    void dim(int level) { cout << "Dimming lights to " << level << "\n"; }
};
class Screen
{
public:
    void up() { cout << "Screen up\n"; }
    void down() { cout << "Screen down\n"; }
};
class PopcornPopper
{
public:
    void on() { cout << "Popcorn popper on\n"; }
    void off() { cout << "Popcorn popper off\n"; }
    void pop() { cout << "Popping popcorn\n"; }
};

class HomeTheaterFacade
{
private:
    Amplifier *amp;
    Tuner *tuner;
    DvdPlayer *dvd;
    CdPlayer *cd;
    Projector *projector;
    Screen *screen;
    TheaterLights *lights;
    PopcornPopper *popper;

public:
    HomeTheaterFacade(Amplifier *amp, Tuner *tuner, DvdPlayer *dvd, CdPlayer *cd, Projector *projector,
     Screen *screen, TheaterLights *lights, PopcornPopper *popper)
    {
        this->amp = amp;
        this->tuner = tuner;
        this->dvd = dvd;
        this->cd = cd;
        this->projector = projector;
        this->screen = screen;
        this->lights = lights;
        this->popper = popper;
    }

    void watchMovie(string movie)
    {
        cout << "Get ready to watch a movie...\n";
        popper->on();
        popper->pop();
        lights->dim(10);
        screen->down();
        projector->on();
        projector->setWideScreenMode();
        amp->on();
        amp->setDvd(dvd);
        amp->setSurroundSound();
        amp->setVolume(5);
        dvd->on();
        dvd->play(movie);
    }

    void endMovie()
    {
        cout << "Shutting movie theater down...\n";
        popper->off();
    }
};

int main()
{
    Amplifier *amp = new Amplifier();
    Tuner *tuner = new Tuner();
    DvdPlayer *dvd = new DvdPlayer(); // thêm dòng này
    CdPlayer *cd = new CdPlayer();
    Projector *projector = new Projector();
    Screen *screen = new Screen();
    TheaterLights *lights = new TheaterLights();
    PopcornPopper *popper = new PopcornPopper();

    amp->setDvd(dvd);
    projector->setInput(dvd);

    HomeTheaterFacade *homeTheater = new HomeTheaterFacade(amp, tuner, dvd, cd, projector, screen, lights, popper);
    homeTheater->watchMovie("Raiders of the Lost Ark");
    homeTheater->endMovie();

    delete amp;
    delete tuner;
    delete dvd;
    delete cd;
    delete projector;
    delete screen;
    delete lights;
    delete popper;
    delete homeTheater;

    return 0;
}
