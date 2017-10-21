file(GLOB_RECURSE ALL_SOURCE_FILES src/*.cpp src/rule/*.cpp include/*.h test/*.cpp)

add_custom_target(
        check
        COMMAND /usr/local/bin/cppcheck
        --enable=warning,performance,portability,information,missingInclude
        --std=c++11
        --language=c++
        --library=std.cfg
        --template="[{severity}][{id}] {message} {callstack} \(On {file}:{line}\)"
        --verbose
        --quiet
        ${ALL_SOURCE_FILES}
)

add_custom_target(
        format
        COMMAND /usr/local/bin/clang-format
        -style=file
        -i
        ${ALL_SOURCE_FILES}
)