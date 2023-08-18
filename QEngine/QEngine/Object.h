#pragma once


namespace QEngine
{
	class Object
	{
	public:
		int id;
		static int instances;
	public:
		Object();
		~Object();
	public:
		int GetID();

		bool operator ==(const Object& rhdObj) {
			return (this->id == rhdObj.id);
		}
		bool operator !=(const Object& rhdObj) {
			return (this->id != rhdObj.id);
		}
	};
}

