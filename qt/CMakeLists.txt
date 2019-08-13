add_library(SQtWidgets
  sqcombobox.h
  sqdatefield.cpp sqdatefield.h
  sqlabel.cpp sqlabel.h
  sqpushbutton.cpp sqpushbutton.h
)
target_include_directories(SQtWidgets PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${Boost_INCLUDE_DIR})
target_link_libraries(SQtWidgets PUBLIC SodiumCxx Qt5::Widgets)
