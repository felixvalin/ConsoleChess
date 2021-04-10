#pragma once
class HasMoved
{
private:
	bool m_HasMoved;

public:
	HasMoved();

	inline bool GetHasMoved() const { return m_HasMoved; }
	inline void SetHasMoved(bool value) { m_HasMoved = value; }

	void CheckFirstMove();
};

