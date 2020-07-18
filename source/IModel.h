#pragma once

class IModel
{
	public:
		virtual void StartButton() = 0;
		virtual void StopButton() = 0;
		virtual void Terminate() = 0;
		virtual ~IModel() = default;

};