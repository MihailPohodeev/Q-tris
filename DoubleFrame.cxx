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

// copy constructor.
DoubleFrame::DoubleFrame(const DoubleFrame& df)
{
	_workingMatrix  = df._workingMatrix->clone();
	_readyMatrix    = df._readyMatrix->clone();
}

// operator =.
DoubleFrame& DoubleFrame::operator=(DoubleFrame df)
{
	Matrix* temp 	= _workingMatrix;
	_workingMatrix 	= df._workingMatrix;
	df._workingMatrix = temp;

	temp = _readyMatrix;
	_readyMatrix	= df._readyMatrix;
	df._readyMatrix = temp;
	return *this;
}

// destructor.
DoubleFrame::~DoubleFrame()
{
	delete _workingMatrix;
	delete _readyMatrix;
}

