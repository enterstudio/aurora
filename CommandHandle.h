
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
    Stream* stream_, * stream2_;

    InputCommand lastCommand = InputCommand::None;

    unsigned int holdStartTime = 0;
    bool isHolding_ = false;

    unsigned int zeroStartTime = 0;
    unsigned int zeroDelay = 120;

public:


    void setInput(Stream* stream, Stream* stream2=NULL) {
        stream_ = stream;
        stream2_ = stream2;
        stream_->setTimeout(8);
        stream2_->setTimeout(8);
    }

    bool isHolding() { return isHolding_; }
    void heldButtonHasBeenHandled() {
        lastCommand = InputCommand::None;
        isHolding_ = false;
        holdStartTime = 0;
    }

    InputCommand readCommand(unsigned int holdDelay=500) {
        if (stream_->available()) {
            String rx = stream_->readString();
            InputCommand ret = getCommand(rx);
            stream_->println(rx + "!");
            return ret;
        }
        if (stream2_->available()) {
            String rx = stream2_->readString();
            InputCommand ret = getCommand(rx);
            stream2_->println(rx + "!");
            return ret;
        }
        return InputCommand::None; //getCommand(readIRCode(holdDelay));
    }

    InputCommand getCommand(String in) {
        InputCommand ret = InputCommand::None;
        if (in.equalsIgnoreCase("Up")) { ret = InputCommand::Up; }
        else if (in.equalsIgnoreCase("Down")) { ret = InputCommand::Down; }
        else if (in.equalsIgnoreCase("Left")) { ret = InputCommand::Left; }
        else if (in.equalsIgnoreCase("Right")) { ret = InputCommand::Right; }
        else if (in.equalsIgnoreCase("Select")) { ret = InputCommand::Select; }
        else if (in.equalsIgnoreCase("Brightness")) { ret = InputCommand::Brightness; }
        else if (in.equalsIgnoreCase("PlayMode")) { ret = InputCommand::PlayMode; }
        else if (in.equalsIgnoreCase("Palette")) { ret = InputCommand::Palette; }
        else if (in.equalsIgnoreCase("Clock")) { ret = InputCommand::Clock; }
        else if (in.equalsIgnoreCase("Power")) { ret = InputCommand::Power; }
        else if (in.equalsIgnoreCase("Back")) { ret = InputCommand::Back; }
        else if (in.equalsIgnoreCase("BrightnessUp")) { ret = InputCommand::BrightnessUp; }
        else if (in.equalsIgnoreCase("BrightnessDown")) { ret = InputCommand::BrightnessDown; }
        else if (in.equalsIgnoreCase("Menu")) { ret = InputCommand::Menu; }
        return ret;
    }
};


#endif
