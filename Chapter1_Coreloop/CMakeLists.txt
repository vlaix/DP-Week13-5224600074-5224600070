cmake_minimum_required(VERSION 3.10)

project(Balator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(CHAPTER1_CORELOOP
    main.cpp

    BlindRule.cpp
    FiveOfAKindChecker.cpp
    FlushChecker.cpp
    FlushFiveChecker.cpp
    FlushHouseChecker.cpp
    FourOfAKindChecker.cpp
    FullHouseChecker.cpp
    GameManager.cpp
    HandGenerator.cpp
    HandPlayer.cpp
    PairChecker.cpp
    PokerHandChecker.cpp
    RewardRule.cpp
    RoyalFlushChecker.cpp
    ScoringRule.cpp
    StraightChecker.cpp
    StraightFlushChecker.cpp
    ThreeOfKindChecker.cpp
    TwoPairChecker.cpp
)