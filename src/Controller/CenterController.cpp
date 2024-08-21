#include "CenterController.h"

CenterController::CenterController(CenterModule* mod ,View* v) : module(mod), view(v) 
{
    mediaController = new MediaController(mod);
    playlistController = new PlaylistController(mod, mediaController);
    usbController = new USBController(mod);
    playbackController = new PlaybackController(mod);
}

CenterController::~CenterController() {
    delete mediaController;
    delete playlistController;
    delete usbController;
    delete playbackController;
}

void CenterController::Playback(){
    char choice = view->choicePlayback();
    switch (choice){
        case AUDIO_PLAY_FILE:
            Playback_Audiofile();
            break;
        case AUDIO_PLAY_PLAYLIST:
            Playback_Playlist();
            break;
        case VIDEO_PLAY:
            Playback_Video();
            break;
        case EXIT:
            break;
    }
}

void CenterController::Playback_Playlist(){
    if (module->getAllPlaylists().empty()) {
        std::cout << "No playlists available.\n";
        return;
    }
    view->playback_Playlist();
    std::string name;
    do{
        std::getline(std::cin, name);
        if(name == "exit") return;
    }
    while(module->getAllPlaylists().count(name) == 0);

    playbackController->setCurrentPlaylist(module->getAllPlaylists()[name]);

    int count = view->displayPlaylist(module->getAllPlaylists()[name]);
    if(count != PLAY_EXIT){
        playbackController->setCurrentFile(module->getAllPlaylists()[name]->getFiles()[count]);
        playbackController->setCurrentIndex(count);
        view->display_currentPlay(module->getAllPlaylists()[name]->getFiles()[count]);
        playbackController->play();
        playbackController->startMonitor();
        char choice;
        do{
            choice = view->playback_Menu();
            switch(choice){
                case PAUSE:
                    playbackController->pause();
                    break;
                case NEXT:
                    playbackController->next(PlaybackType::Audio);
                    view->display_currentPlay(playbackController->getCurrentFile());
                    break;
                case RESUME:
                    playbackController->resume();
                    break;
                case PREVIOUS:
                    playbackController->previous(PlaybackType::Audio);
                    view->display_currentPlay(playbackController->getCurrentFile());
                    break;
                case INCRE_VOL:
                    playbackController->increaseVolume();
                    break;
                case DECRE_VOL:
                    playbackController->decreaseVolume();
                    break;
                case CURRENT_TIME:
                    view->display_currentTime(playbackController->getcurrentTime(),playbackController->getCurrentFile());
                    break;
                }
        }
        while(choice!=EXIT);

        playbackController->stop();
    }
    else
    std::cout<<"backed";

}

void CenterController::Playback_Audiofile(){
    int count = view->playback_Audio_list();
    if(count != PLAY_EXIT && module->getAllMediaFiles()[count]->isAudio()){
        playbackController->setCurrentFile(module->getAllMediaFiles()[count]);
        playbackController->setCurrentIndex(count);
        view->display_currentPlay(module->getAllMediaFiles()[count]);
        playbackController->play();
        playbackController->startMonitor();
        char choice;
        do{
            choice = view->playback_Menu();
            switch(choice){
                case PAUSE:
                    playbackController->pause();
                    break;
                case NEXT:
                    playbackController->next(PlaybackType::Audio);
                    view->display_currentPlay(playbackController->getCurrentFile());
                    break;
                case RESUME:
                    playbackController->resume();
                    break;
                case PREVIOUS:
                    playbackController->previous(PlaybackType::Audio);
                    view->display_currentPlay(playbackController->getCurrentFile());
                    break;
                case INCRE_VOL:
                    playbackController->increaseVolume();
                    break;
                case DECRE_VOL:
                    playbackController->decreaseVolume();
                    break;
                case CURRENT_TIME:
                    view->display_currentTime(playbackController->getcurrentTime(),playbackController->getCurrentFile());
                    break;
                }
        }
        while(choice!=EXIT);

        playbackController->stop();
    }
    else
    std::cout<<"Invalid\n";

}
void CenterController::Playback_Video(){
  int count = view->playback_Video_list();
    if(count != PLAY_EXIT && (!module->getAllMediaFiles()[count]->isAudio())){
        playbackController->setCurrentFile(module->getAllMediaFiles()[count]);
        playbackController->setCurrentIndex(count);
        view->display_currentPlay(module->getAllMediaFiles()[count]);
        playbackController->play();
        playbackController->startMonitor();
        char choice;
        do{
            choice = view->playback_Menu();
            switch(choice){
                case PAUSE:
                    playbackController->pause();
                    break;
                case NEXT:
                    playbackController->next(PlaybackType::Video);
                    view->display_currentPlay(playbackController->getCurrentFile());
                    break;
                case RESUME:
                    playbackController->resume();
                    break;
                case PREVIOUS:
                    playbackController->previous(PlaybackType::Video);
                    view->display_currentPlay(playbackController->getCurrentFile());
                    break;
                case INCRE_VOL:
                    playbackController->increaseVolume();
                    break;
                case DECRE_VOL:
                    playbackController->decreaseVolume();
                    break;
                case CURRENT_TIME:
                    view->display_currentTime(playbackController->getcurrentTime(),playbackController->getCurrentFile());
                    break;
                }
        }
        while(choice!=EXIT);

        playbackController->stop();
    }
    else
    std::cout<<"back to menu";
}

void CenterController::managePlaylists(){
    MediaController mediaController(module);
    PlaylistController playlistController(module, &mediaController);
    USBController usb(module);
    std::string playlistName, folderPath, filePath, pathUSB;

    char choice;
    do {
        std::cout << "\n";
        std::cout << "=== Playlist Management Menu ===\n";
        std::cout << "1. Create a new playlist\n";
        std::cout << "2. Select folder add to playlist\n";
        std::cout << "3. View playlist\n";
        std::cout << "4. Add file to playlist\n";
        std::cout << "5. Delete playlist\n";
        std::cout << "6. Remove a file from a playlist\n";
        std::cout << "7: Add all file to mediafile\n";
        std::cout << "8: USB manage \n";
        std::cout << "9: Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        std::cin.ignore();

        switch (choice) {
            case CREATE_PLAYLIST: {
                std::cout << "Enter the name of the new playlist: ";
                std::getline(std::cin, playlistName);
                playlistController.createPlaylist(playlistName);
                break;
            }
            case SELECT_FOLDER_AND_ADD_TO_PLAYLIST: {
                std::cout << "Enter the name of the playlist: ";
                std::getline(std::cin, playlistName);
                
                if (playlistName.empty()) {
                    std::cout << "Playlist name cannot be empty.\n";
                    break;
                }

                std::cout << "Enter the file path or folder path to add: ";
                std::getline(std::cin, folderPath);
                
                if (folderPath.empty()) {
                    std::cout << "File or folder path cannot be empty.\n";
                    break;
                }

                if (std::filesystem::is_directory(folderPath))
                    {
                    mediaController.selectFolderMedia(folderPath);
                    auto selectedFiles = mediaController.getSelectedFiles();
                    if (selectedFiles.empty()) {
                        std::cout << "No valid media files found in the selected folder.\n";
                    }
                    else {
                        for (const auto& file : selectedFiles) {
                            playlistController.addFileToPlaylist(playlistName, file->getPath());
                        }
                        std::cout << "Files added to playlist '" << playlistName << "' successfully.\n";
                    }
                } else if (std::filesystem::is_regular_file(folderPath)) {
                    
                    playlistController.addFileToPlaylist(playlistName, folderPath);
                    std::cout << "File added to playlist '" << playlistName << "' successfully.\n";
                } else {
                    std::cout << "The provided path is neither a valid file nor a directory.\n";
                }

                break;
            }

            case VIEW_PLAYLIST: {
                std::cout << "Enter the name of the playlist to view: ";
                std::getline(std::cin, playlistName);
                std::cout << std::endl;
                playlistController.viewPlaylist(playlistName);
                break;
            }
            case ADD_PLAYLIST: {
                std::cout << "Enter the name of the playlist to update: ";
                std::getline(std::cin, playlistName);
                auto existingPlaylist = module->getPlaylist(playlistName);
                if (existingPlaylist) 
                {
                    std::cout << "Enter the file path to add to the playlist: ";
                    std::getline(std::cin, filePath);
                    auto mediaFile = mediaController.parseFileMedia(filePath);
                    if (mediaFile) {
                        existingPlaylist->addFile(mediaFile);
                        playlistController.updatePlaylist(existingPlaylist);
                        std::cout << "Playlist '" << playlistName << "' updated successfully.\n";
                    } else {
                        std::cout << "Failed to parse the media file.\n";
                    }
                } else {
                    std::cout << "Playlist not found.\n";
                }
                break;
            }
            case DELETE_PLAYLIST: {
                std::cout << "Enter the name of the playlist to delete: ";
                std::getline(std::cin, playlistName);
                playlistController.deletePlaylist(playlistName);
                break;
            }
            case REMOVE_FILE_FROM_PLAYLIST: {
                std::cout << "Enter the name of the playlist: ";
                std::getline(std::cin, playlistName);
                std::cout << "Enter the file path to remove: ";
                std::getline(std::cin, filePath);
                playlistController.removeFileFromPlaylist(playlistName, filePath);
                break;
            }
            case ADD_MEDIA:{
                std::cout<< "Add all to mediafile: ";
                std::cin>> folderPath;
                mediaController.selectFolderMedia(folderPath);
                break;
            }
            case USB:{
                std::cout<< "Add path device file: ";
                std::cin>> pathUSB;
                std::cout<< std::endl;
                std::cout<< "Add path folder file: ";
                std::cin>> folderPath;
                usb.mountDevice(pathUSB,folderPath);
                break;
            }
            case EXIT_MANAGE_PLAYLISTS: {
                std::cout << "Exiting the menu.\n";
                break;
            }
            default: {
                std::cout << "Invalid choice, please try again.\n";
                break;
            }
        }
    } while (choice != EXIT_MANAGE_PLAYLISTS);
}
