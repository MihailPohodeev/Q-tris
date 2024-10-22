#include "DoubleFrame.hxx"

// constructor.
DoubleFrame::DoubleFrame()
{
	_workingMatrix  = new Matrix;
	_readyMatrix    = new Matrix;
}

// swap two buffers for information exchanging.
void DoubleFrame::swap_buffers()
{
	std::lock_guard<std::mutex> lock(_mtx);
	Matrix* t = _workingMatrix;
	_workingMatrix = _readyMatrix;
	_readyMatrix = t;
}

// return ready matrix.
Matrix* DoubleFrame::get_matrix() const
{
	std::lock_guard<std::mutex> lock(_mtx);
	return _readyMatrix->clone();
}

// destructor.
DoubleFrame::~DoubleFrame()
{
	delete _workingMatrix;
	delete _readyMatrix;
}

