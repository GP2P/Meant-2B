#ifndef MEANT_2B_DF_FRAGILEBLOCK_H
#define MEANT_2B_DF_FRAGILEBLOCK_H

#include "Block.h"

class FragileBlock : public Block {

private:

	int timeLeft;

public:

	FragileBlock(df::Vector position, char character, df::Color color, int time);

	int eventHandler(const df::Event *p_e) override;
};

// limited to build only on integer coordinates, will convert floats to ints
void
buildFragileBlocks(df::Vector start, df::Vector end, char character = '#', df::Color color = df::GREEN, int time = 150);

// limited to build only a platform, not a block
void buildFragileBlockPlatform(df::Vector start, df::Vector end, char character = '#', df::Color color = df::GREEN,
                               int time = 150);

#endif //MEANT_2B_DF_FRAGILEBLOCK_H
