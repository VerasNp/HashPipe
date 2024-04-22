add_executable(test_hash_app
        test_hash_func.c
)

target_link_libraries(test_hash_app
        hash
        Unity
)

add_test(
        hash_test
        test_hash_app)