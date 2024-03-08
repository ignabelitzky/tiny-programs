#include <iostream>
#include <vector>
#include <string>
#include "../include/menu.hpp"
#include "../include/message_box.hpp"
#include "../include/audio.hpp"
#define MINIAUDIO_IMPLEMENTATION
#include "../include/miniaudio.hpp"

int main()
{
    std::string title = " [Console Audio Player] ";
    std::vector<std::string> options = {
        "James Bond soundrack",
        "Mission Impossible soundtrack",
        "Pirates of the Caribbean soundtrack",
        "Exit"};
    std::string selection = "";
    std::string soundtrackFile = "";
    do
    {
        try
        {
            Menu *menu = new Menu(title, options);
            selection = menu->show();
            delete menu;
        }
        catch (const std::runtime_error &e)
        {
            std::cerr << e.what() << std::endl;
            return 1;
        }
        if (selection == options.at(0))
        {
            soundtrackFile = "resources/tracks/james-bond.mp3";
        }
        else if (selection == options.at(1))
        {
            soundtrackFile = "resources/tracks/mission-impossible.mp3";
        }
        else if (selection == options.at(2))
        {
            soundtrackFile = "resources/tracks/pirates-of-the-caribbean.mp3";
        }
        if (selection != options.at(options.size() - 1))
        {
            try
            {
                Audio *audio = new Audio(soundtrackFile);
                audio->play();
                try
                {
                    MessageBox *messageBox = new MessageBox(" [Audio Playing] ",
                        "Playing " + selection + "\n\nPlease press enter to go to the Main Menu.",
                        {"Go to Main Menu"});
                    messageBox->show();
                    delete messageBox;
                }
                catch (const std::runtime_error &e)
                {
                    std::cerr << e.what() << std::endl;
                    return 1;
                }
                delete audio;
            }
            catch (const std::runtime_error &e)
            {
                std::cerr << e.what() << std::endl;
                return 1;
            }
        }
    } while (selection != options.at(options.size() - 1));

    return 0;
}