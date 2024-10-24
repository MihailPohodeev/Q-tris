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
Matrix DoubleFrame::get_matrix() const
{
	std::lock_guard<std::mutex> lock(_mtx);
	return Matrix(*_readyMatrix);
}

// set matrix to working matrix;
void DoubleFrame::set_matrix(const Matrix& mat)
{
	std::lock_guard<std::mutex> lock(_mtx);
	delete _workingMatrix;
	_workingMatrix = new Matrix(mat);
}

// destructor.
DoubleFrame::~DoubleFrame()
{
	delete _workingMatrix;
	delete _readyMatrix;
}

