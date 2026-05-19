#pragma once
#include "Hand.h"
#include "PokerHandChecker.h"
#include "FlushFiveChecker.h"
#include "FlushHouseChecker.h"
#include "FiveOfAKindChecker.h"
#include "RoyalFlushChecker.h"
#include "StraightFlushChecker.h"
#include "FourOfAKindChecker.h"
#include "FullHouseChecker.h"
#include "FlushChecker.h"
#include "StraightChecker.h"
#include "ThreeOfKindChecker.h"
#include "TwoPairChecker.h"
#include "PairChecker.h"
#include "JokerObserver.h"

class ScoringRule {
public:
    ScoringRule();
    int scoreHand(const Hand& hand);
    HandRank getLastRank() const;

private:
    FlushFiveChecker    flushfivechecker;
    FlushHouseChecker   flushhousechecker;
    FiveOfAKindChecker  fiveofakindchecker;
    RoyalFlushChecker   royalflushchecker;
    StraightFlushChecker straightflushchecker;
    FourOfAKindChecker  fourofakindchecker;
    FullHouseChecker    fullhousechecker;
    FlushChecker        flushchecker;
    StraightChecker     straightchecker;
    ThreeOfKindChecker  threeofakindchecker;
    TwoPairChecker      twopairchecker;
    PairChecker         pairchecker;

    HandRank lastRank = HandRank::HIGH_CARD;
    int convertRankToScore(HandRank rank);
};