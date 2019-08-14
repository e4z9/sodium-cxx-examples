add_executable(airline1 airline1.cpp)
target_link_libraries(airline1 SodiumCxx Qt5::Widgets SQtWidgets)

add_executable(airline2 airline2.cpp)
target_link_libraries(airline2 SodiumCxx Qt5::Widgets SQtWidgets)

add_executable(clearfield clearfield.cpp)
target_link_libraries(clearfield SodiumCxx Qt5::Widgets SQtWidgets)

add_executable(noglitches noglitches.cpp)
target_link_libraries(noglitches SodiumCxx)
