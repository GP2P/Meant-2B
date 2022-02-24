#ifndef DF_BLOCK_H
#define DF_BLOCK_H

#include "Object.h"

class Block : public df::Object {
public:
	Block();

	Block(df::Vector position);

	int draw();
};

#endif //DF_BLOCK_H
