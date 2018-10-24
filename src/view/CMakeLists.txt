add_library(view STATIC ListPanel.cpp ListPanel.h FileMenu.cpp FileMenu.h MainWindow.cpp Widget.cpp Widget.h DisplayManager.cpp DisplayManager.h)
target_link_libraries(view ncurses format)