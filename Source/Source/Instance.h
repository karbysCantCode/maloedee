

class Instance
{
public:
	enum InstanceType
	{
		OBJECT
	};

	Instance::InstanceType Type;
	bool Changed = true;
	bool PositionChanged = false;
};