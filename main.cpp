#include <iostream>
#include "CenterModule.h"
#include "CenterController.h"
#include "View.h"
#include "USBController.h"
#define MANAGE '1'
#define PLAY '2'
#define EXIT_MENU '3'
int main() {
    CenterModule module;
    View view(module);  
    CenterController controller(&module, &view);
    MediaController media(&module);
    PlaylistController playlist(&module, &media);
    USBController usbController(&module);


    char choice;
    do {
        view.displayMenu();
        std::cin >> choice;
        std::cerr << "\n";

        switch (choice) {
            case MANAGE: 
                controller.managePlaylists();
                break;
            case PLAY: 
                controller.Playback();
                break;
            case EXIT_MENU: 
                std::cerr << "Exiting...\n";
                break;
            default:
                std::cerr << "Invalid choice, please try again.";
        }
        std::cerr << "\n";
    } while (choice != '0');

    return 0;
}
