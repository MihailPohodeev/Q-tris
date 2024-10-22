#ifndef _DOUBLE_FRAME_H_
#define _DOUBLE_FRAME_H_

#include <mutex>
#include "Matrix.hxx"

class DoubleFrame
{
	mutable std::mutex _mtx;
	Matrix* _workingMatrix;
	Matrix* _readyMatrix;
public:
	//constructor.
	DoubleFrame();
	// swap buffers for info exchanging.
	void swap_buffers();
	// return ready Matrix.
	Matrix* get_matrix() const;
	//destructor.
	~DoubleFrame();
};

#endif
