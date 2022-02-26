#ifndef MEANT_2B_DF_RETICLE_H
#define MEANT_2B_DF_RETICLE_H

#include "Object.h"

#define RETICLE_CHAR '+'

class Reticle : public df::Object {

private:

	df::Color color;

public:

	Reticle(df::Color color);

	int draw() override;

	int eventHandler(const df::Event *p_e) override;
};

#endif //MEANT_2B_DF_RETICLE_H
