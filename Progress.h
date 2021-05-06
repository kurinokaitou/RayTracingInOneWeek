#ifndef PROGRESS_H
#define PROGRESS_H
class Progress
{
public:
	virtual void updateProgress(double value) = 0;
	virtual ~Progress(){}
};
#endif