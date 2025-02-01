#ifndef _DOUBLE_FRAME_HXX_
#define _DOUBLE_FRAME_HXX_

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
	Matrix get_matrix() const;
	// set Matrix to working matrix :
	void set_matrix(const Matrix&);
	//destructor.
	~DoubleFrame();
};

#endif
