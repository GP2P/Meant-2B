
#ifndef MEANT_2B_DF_BOSSPART_H
#define MEANT_2B_DF_BOSSPART_H


#include "Object.h"
#include "Boss.h"


class BossPart : public df::Object {
private:
	Boss *boss;
	int stage;
public:

	BossPart(Boss *Boss);

	int eventHandler(const df::Event *p_e) override;

	void setStage(int stage);
};


#endif //MEANT_2B_DF_BOSSPART_H
