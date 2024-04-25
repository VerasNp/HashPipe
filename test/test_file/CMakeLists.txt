add_executable(test_file_app
        test_file_read.c
)

target_link_libraries(test_file_app
        file
        Unity
)

add_test(
        file_test
        test_file_app)