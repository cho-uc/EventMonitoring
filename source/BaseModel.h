#pragma once

#include "IModel.h"

class BaseModel : public IModel
{
public:
	void Terminate() override;

protected:
	bool m_RunningMainWindow{ true };
};