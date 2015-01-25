
#ifndef CommandHandle_H
#define CommandHandle_H

enum class InputCommand {
    None,
    Up,
    Down,
    Left,
    Right,
    Select,
    Brightness,
    PlayMode,
    Palette,
    Clock,
    Power,
    Back,
    BrightnessUp,
    BrightnessDown,
    Menu,
};

class CommandHandle {
    Stream* stream_;

    InputCommand lastCommand = InputCommand::None;

    unsigned int holdStartTime = 0;
    bool isHolding_ = false;

    unsigned int zeroStartTime = 0;
    unsigned int zeroDelay = 120;

public:
    CommandHandle(Stream* stream) : stream_(stream) { }

    bool isHolding() { return isHolding_; }
    void heldButtonHasBeenHandled() {
        lastCommand = InputCommand::None;
        isHolding_ = false;
        holdStartTime = 0;
    }

    InputCommand readCommand(unsigned int holdDelay=500) {
        if (stream_->available()) {
            String rx = stream_->readStringUntil('\n');
            return getCommand(rx);
        }
        return InputCommand::None; //getCommand(readIRCode(holdDelay));
    }

    InputCommand getCommand(String in) {
        if (in.equalsIgnoreCase("Up")) { return InputCommand::Up; }
        else if (in.equalsIgnoreCase("Down")) { return InputCommand::Down; }
        else if (in.equalsIgnoreCase("Left")) { return InputCommand::Left; }
        else if (in.equalsIgnoreCase("Right")) { return InputCommand::Right; }
        else if (in.equalsIgnoreCase("Select")) { return InputCommand::Select; }
        else if (in.equalsIgnoreCase("Brightness")) { return InputCommand::Brightness; }
        else if (in.equalsIgnoreCase("PlayMode")) { return InputCommand::PlayMode; }
        else if (in.equalsIgnoreCase("Palette")) { return InputCommand::Palette; }
        else if (in.equalsIgnoreCase("Clock")) { return InputCommand::Clock; }
        else if (in.equalsIgnoreCase("Power")) { return InputCommand::Power; }
        else if (in.equalsIgnoreCase("Back")) { return InputCommand::Back; }
        else if (in.equalsIgnoreCase("BrightnessUp")) { return InputCommand::BrightnessUp; }
        else if (in.equalsIgnoreCase("BrightnessDown")) { return InputCommand::BrightnessDown; }
        else if (in.equalsIgnoreCase("Menu")) { return InputCommand::Menu; }
        Serial.print("unrecognized command: ");
        Serial.println(in);
        return InputCommand::None;
    }
};


#endif
