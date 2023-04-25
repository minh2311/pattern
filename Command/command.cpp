#include <iostream>
#include <sstream>
using namespace std;

//Command to execute
class command 
{
    public:
        virtual void execute() = 0;
        virtual string getClassName() = 0;
        virtual void undo() = 0;
};

class NoCommand : public command
{
    void execute()
    {
        cout << "No command" << endl;
    }
    string getClassName() { return "  No Command   "; }
    void undo()
    {
        cout << "No command" << endl;
    }
};

//Receiver (the one who knows how to do the job)
class light
{
    public:
        light(){}
        void on()
        {
            cout << "Light is on" << endl;
        }
        void off()
        {
            cout << "Light is off" << endl;
        }
};

class stereo
{
    public:
        void on()
        {
            cout << "Stereo is on" << endl;
        }
        void setCD(string name)
        {   
            cout << "Stereo is set to: " << name << endl;
        }
        void setVolume(int volume)
        {
            cout << "Stereo volume is set to: " << volume << endl;
        }
        void off()
        {
            cout << "Stereo is off" << endl;
        }
};

class garageDoor
{
    public:
        void up()
        {
            cout << "Garage door is up" << endl;
        }
        void down()
        {
            cout << "Garage door is down" << endl;
        }
        void stop()
        {
            cout << "Garage door is stopped" << endl;
        }
        void lightOn()
        {
            cout << "Garage door light is on" << endl;
        }
        void lightOff()
        {
            cout << "Garage door light is off" << endl;
        }
};

// Concrete Command (the one to deliver the execution to the receiver)
class lightOnCommand : public command
{
    private:
        light* Light;
    public:
        lightOnCommand(light* Light): Light(Light){}
        void execute()
        {
            Light->on();
        }
        string getClassName()
        {
            return "lightOnCommand";
        }
        void undo()
        {
            Light->off();
        }
};

class lightOffCommand : public command
{
    private:
        light* Light;
    public:
        lightOffCommand(light* Light): Light(Light){}
        void execute()
        {
            Light->off();
        }
        string getClassName()
        {
            return "lightOffCommand";
        }
        void undo()
        {
            Light->on();
        }
};

class stereoOnCommand : public command
{
    private:
        stereo* Stereo;
    public:
        stereoOnCommand(stereo* Stereo): Stereo(Stereo){}
        void execute()
        {
            Stereo->on();
            Stereo->setCD("Never Gonna Give You Up");
            Stereo->setVolume(7);
        }
        string getClassName()
        {
            return "stereoOnCommand";
        }
        void undo()
        {
            Stereo->off();
        }
};

class stereoOffCommand : public command
{
    private:
        stereo* Stereo;
    public:
        stereoOffCommand(stereo* Stereo): Stereo(Stereo){}
        void execute()
        {
            Stereo->off();
        }
        string getClassName()
        {
            return "stereoOffCommand";
        }
        void undo()
        {
            Stereo->on();
            Stereo->setCD("Never Gonna Give You Up");
            Stereo->setVolume(7);
        }
};

class garageDoorOnCommand : public command
{
    private:
        garageDoor* GarageDoor;
    public:
        garageDoorOnCommand(garageDoor* GarageDoor): GarageDoor(GarageDoor){}
        void execute()
        {
            GarageDoor->up();
            GarageDoor->lightOn();
        }
        string getClassName()
        {
            return "garageDoorOnCommand";
        }
        void undo()
        {
            GarageDoor->down();
            GarageDoor->lightOff();
        }
};

class garageDoorOffCommand : public command
{
    private:
        garageDoor* GarageDoor;
    public:
        garageDoorOffCommand(garageDoor* GarageDoor): GarageDoor(GarageDoor){}
        void execute()
        {
            GarageDoor->lightOff();
            GarageDoor->down();
        }
        string getClassName()
        {
            return "garageDoorOffCommand";
        }
        void undo()
        {
            GarageDoor->lightOn();
            GarageDoor->up();
        }
};

// Nut bam 1 lan nhieu lenh se chay
class macroCommand : public command
{
    private:
        command** commands;
        int numberOfCommands;
    public:
        macroCommand(command** commands, int numberOfCommands): commands(commands), numberOfCommands(numberOfCommands){}
        void execute()
        {
            for (int i = 0; i < numberOfCommands; i++)
            {
                commands[i]->execute();
            }
        }
        string getClassName()
        {
            return "macroCommand";
        }
        void undo()
        {
            for (int i = 0; i < numberOfCommands; i++)
            {
                commands[i]->undo();
            }
        }
};

// Invoker (ke trung gian)
class remoteControl
{
    private:
        command* onCommands[7];
        command* offCommands[7];
        command* noCommand;
        command* undoCommand;
        command* MacroCommands[7];
    public: 
        remoteControl()
        {
            noCommand = new NoCommand();
            for (int i = 0; i<7; i++)
            {
                onCommands[i] = noCommand;
                offCommands[i] = noCommand;
            }
            undoCommand = noCommand;
        }
        void setCommand(int slot, command* onCommand, command* offCommand)
        {
            onCommands[slot] = onCommand;
            offCommands[slot] = offCommand;
        }
        void onButtonPress(int slot)
        {
            onCommands[slot]->execute();
            undoCommand = onCommands[slot];
        }
        void offButtonPress(int slot)
        {
                offCommands[slot]->execute();
                undoCommand = offCommands[slot];
        }
        void undoButtonPress() // undo 1 command 
        {
            undoCommand->undo();
        }
        void undoMacroButtonPressed() // undo all command in macro
        {
            for (int i = 0; i < 7; i++)
            {
                MacroCommands[i]->undo();
            }
        }
        string toString()
        {
            stringstream stringBuff;
            stringBuff << "\n------ Remote Control -------\n";
            for (int i = 0; i < 7; i++)
            {
                stringBuff << "[slot " << i << "] " << onCommands[i]->getClassName() << "    " << offCommands[i]->getClassName() << "\n";
            }
            return stringBuff.str();

        }            
    
};

int main()
{
    remoteControl* remote = new remoteControl();
    
    //insert light
    light* livingRoomLight = new light();
    lightOnCommand* livingRoomLightOn = new lightOnCommand(livingRoomLight);
    lightOffCommand* livingRoomLightOff = new lightOffCommand(livingRoomLight);
    remote->setCommand(0, livingRoomLightOn, livingRoomLightOff);
    
    // insert stereo
    stereo* livingRoomStereo = new stereo();
    stereoOnCommand* livingRoomStereoOn = new stereoOnCommand(livingRoomStereo);
    stereoOffCommand* livingRoomStereoOff = new stereoOffCommand(livingRoomStereo);
    remote->setCommand(1, livingRoomStereoOn, livingRoomStereoOff);
    
    // insert garage door
    garageDoor* GarageDoor = new garageDoor();
    garageDoorOnCommand* garageDoorOn= new garageDoorOnCommand(GarageDoor);
    garageDoorOffCommand* garageDoorOff = new garageDoorOffCommand(GarageDoor);
    remote->setCommand(2, garageDoorOn, garageDoorOff);
    cout << remote->toString();

    command* CommandsOn[] = {livingRoomLightOn, livingRoomStereoOn, garageDoorOn};
    command* CommandsOff[] = {livingRoomLightOff, livingRoomStereoOff, garageDoorOff};
    
    macroCommand* macroOn = new macroCommand(CommandsOn, 3);
    macroCommand* macroOff = new macroCommand(CommandsOff, 3);

    remote->setCommand(0, macroOn, macroOff);
    remote->onButtonPress(0); // all is on
    remote->offButtonPress(0); // all is off
    remote->undoMacroButtonPressed();// undo all button
    return 0;

}   
