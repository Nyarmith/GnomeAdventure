file(COPY assets DESTINATION ${CMAKE_BINARY_DIR}/tests/)
add_executable(sfml_sanity_test sfml_test.cpp)
add_executable(GameApp_sanity_test sanity_test.cpp)
add_executable(basic_handling_test GameObject_handling_test.cpp)
add_executable(audio_bg_and_events AudioStore_test.cpp)
#add_executable(menu_test menu_test.cpp)
#add_executable(animation_test animation_test.cpp)
target_link_libraries(sfml_sanity_test sfml-graphics sfml-audio sfml-window sfml-system pthread)
target_link_libraries(GameApp_sanity_test sfml-graphics sfml-audio sfml-window sfml-system pthread)
target_link_libraries(basic_handling_test sfml-graphics sfml-audio sfml-window sfml-system pthread)
target_link_libraries(audio_bg_and_events sfml-graphics sfml-audio sfml-window sfml-system pthread)
#target_link_libraries(menu_test          ${ALL_SFML_LIBS})
#target_link_libraries(animation_test     ${ALL_SFML_LIBS})

#TODO: Implement below in adventure-game specific scenario
#add_executable(single_scene_test single_scene_test.cpp)
#add_executable(multiscene_test multiscene_test.cpp)
#target_link_libraries(single_scene_test  ${ALL_SFML_LIBS})
#target_link_libraries(multiscene_test    ${ALL_SFML_LIBS})
