import qbs

CppApplication {
    consoleApplication: true
    files: [
        "ArraySequence.h",
        "DynamicArray.h",
        "LinkedList.h",
        "ListSequence.h",
        "Sequence.h",
        "interface.h",
        "main.cpp",
        "sort.h",
        "tests.hpp",
        "time_measurement.h",
    ]

    Group {     // Properties for the produced executable
        fileTagsFilter: "application"
        qbs.install: true
        qbs.installDir: "bin"
    }

    Properties {
        cpp.cxxLanguageVersion: "c++17"
    }
}
