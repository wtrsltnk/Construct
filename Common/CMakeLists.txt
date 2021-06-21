
add_library(Common)

target_sources(Common
    PUBLIC
        cmdlib.cpp
        cmdlib.h
        GameArguments.cpp
        GameArguments.h
        GameRoot.cpp
        GameRoot.h
        mathlib.cpp
        mathlib.h
        Tokenizer.cpp
        Tokenizer.h
        Utility.cpp
        Utility.h
)

target_compile_features(Common
    PRIVATE cxx_std_17
)
